from time import sleep
import serial
from dualsense_controller import DualSenseController
import threading
import cv2
import numpy as np
from ultralytics import YOLO
import img_processing.colortrack as colortrack

ser = serial.Serial("/dev/ttyUSB0", 115200, timeout=0.1, write_timeout=0.1, rtscts=False, dsrdtr=False) 

# list availabe devices and throw exception when tzhere is no device detected
device_infos = DualSenseController.enumerate_devices()
if len(device_infos) < 1:
    raise Exception('No DualSense Controller available.')

# flag, which keeps program alive
is_running = True

# create an instance, use fiŕst available device
controller = DualSenseController()

global auto
auto = False

global rst
rst = False

global start_detect
start_detect = False

# switches the keep alive flag, which stops the below loop
def stop():
    global is_running
    is_running = False

def on_r1_btn_pressed():
    print('R1 button pressed')

def on_r1_btn_released():
    print('R1 button released')

def on_triangle_btn_pressed():
    print('Triangle button pressed')
    global rst
    rst = True

def on_triangle_btn_released():
    print('Triangle button released')
    global rst
    rst = False

def on_cross_btn_pressed():
    print('Cross button pressed')
    global auto
    auto = not auto

def on_circle_btn_pressed():
    print('Circle button pressed')
    global start_detect
    start_detect = not start_detect


# def on_left_trigger(value):
#     print(f'left trigger changed: {value}') # L2 with analog value


def on_left_stick_x_changed(left_stick_x):
    # print(f'on_left_stick_x_changed: {left_stick_x}')
    try:
        ser.write(f'x: {left_stick_x}\n'.encode())
        ser.flush()
    except Exception as e:
        print('Serial write error:', e)


def on_left_stick_y_changed(left_stick_y):
    # print(f'on_left_stick_y_changed: {left_stick_y}')
    try:
        ser.write(f'y: {left_stick_y}\n'.encode())
        ser.flush()
    except Exception as e:
        print('Serial write error:', e)

    
def on_right_stick_y_changed(right_stick_y):
    # print(f'on_right_stick_y_changed: {right_stick_y}')
    try:
        ser.write(f'z: {right_stick_y}\n'.encode())
        ser.flush()
    except Exception as e:
        print('Serial write error:', e)

# callback, when PlayStation button is pressed
# stop program
def on_ps_btn_pressed():
    print('PS button released -> stop')
    stop()



# callback, when unintended error occurs,
# i.e. physically disconnecting the controller during operation
# stop program
def on_error(error):
    print(f'Opps! an error occured: {error}')
    stop()


# register the button callbacks
controller.btn_ps.on_down(on_ps_btn_pressed)
controller.btn_r1.on_down(on_r1_btn_pressed)
controller.btn_r1.on_up(on_r1_btn_released)
controller.btn_cross.on_down(on_cross_btn_pressed)
controller.btn_triangle.on_down(on_triangle_btn_pressed)
controller.btn_triangle.on_up(on_triangle_btn_released)
controller.btn_circle.on_down(on_circle_btn_pressed)
# controller.left_trigger.on_change(on_left_trigger)
controller.left_stick_x.on_change(on_left_stick_x_changed)
controller.left_stick_y.on_change(on_left_stick_y_changed)
controller.right_stick_y.on_change(on_right_stick_y_changed)

# register the error callback
controller.on_error(on_error)

# enable/connect the device
controller.activate()

def map_stick_to_byte(val):
    """
    Map joystick value -1.0..1.0 to 0..255
    """
    val = max(min(val, 1.0), -1.0)  # clamp
    return int((val + 1) / 2 * 255)


detect_flag = 0
detect_lock = threading.Lock()

def yolo_thread():
    global detect_flag

    model = YOLO("best.pt")
    
    cap = cv2.VideoCapture(2)

    if not cap.isOpened():
        print("Camera open failed")
        return

    while is_running:
        ret, frame = cap.read()
        if not ret:
            continue

        results = model(frame, conf=0.5, verbose=False)

        local_flag = 0 # 0: none, 1: blue, 2: yellow

        for r in results:
            for box in r.boxes:
                cls_id = int(box.cls[0])
                label = model.names[cls_id].lower()
                confidence = box.conf[0].item()
                # print(f'Detected {label} with confidence {confidence:.2f}')

                # draw bounding box
                x1, y1, x2, y2 = map(int, box.xyxy[0])
                cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
                # calculate area of bounding box
                area = (x2 - x1) * (y2 - y1)
                # print(area)
                if area < 80000:
                    continue  # skip small boxes
                cv2.putText(frame, label + f" {confidence:.2f}", (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (36,255,12), 2)
                if label == "blue":
                    local_flag = 1
                elif label == "yellow":
                    local_flag = 2

                colortrack.displayFlagStatus(frame, local_flag)
 
        # thread-safe update
        with detect_lock:
            detect_flag = local_flag

        cv2.imshow("YOLO", frame)
        if cv2.waitKey(1) & 0xFF == 27:
            break

    cap.release()
    cv2.destroyAllWindows()

# start YOLO thread
yolo_thread_instance = threading.Thread(target=yolo_thread)
yolo_thread_instance.start()
# start keep alive loop, controller inputs and callbacks are handled in a second thread

while is_running:
    # --- suction ---
    suction = 1 if controller.btn_r1.pressed else 0

    # --- joystick ---
    lx = controller.left_stick_x.value
    ly = controller.left_stick_y.value
    ry = controller.right_stick_y.value

    # deadzone
    DEADZONE = 0.05
    lx = 0 if abs(lx) < DEADZONE else lx
    ly = 0 if abs(ly) < DEADZONE else ly
    ry = 0 if abs(ry) < DEADZONE else ry

    # map -1..1 -> 0..255
    byte_x = int((lx + 1) * 127.5)
    byte_y = int((-ly + 1) * 127.5)   # invert Y if needed
    byte_z = int((-ry + 1) * 127.5)

    # clamp
    byte_x = max(0, min(255, byte_x))
    byte_y = max(0, min(255, byte_y))
    byte_z = max(0, min(255, byte_z))

    # --- checksum ---
    checksum = auto ^ rst ^ suction ^ byte_x ^ byte_y ^ byte_z ^ detect_flag ^ start_detect

    frame = bytes([
        auto,
        rst,
        suction,
        byte_x,
        byte_y,
        byte_z,
        detect_flag,  
        start_detect,
        checksum
    ])

    print(f'Sending frame: {list(frame)}')
    try:
        ser.write(frame)
        ser.flush()
    except Exception as e:
        print('Serial write error:', e)

    # --- optional lightbar / rumble ---
    if suction:
        controller.left_rumble.set(128)
        controller.right_rumble.set(128)
    else:
        controller.left_rumble.set(0)
        controller.right_rumble.set(0)

    if auto:
        controller.player_leds.set_brightness_high()
        controller.lightbar.set_color(255, 182, 193)
    else:
        controller.player_leds.set_brightness_low()
        controller.lightbar.set_color(0, 0, 255)

    if rst:
        controller.lightbar.set_color(255, 0, 0)
        controller.left_rumble.set(255)
        controller.right_rumble.set(255)

    if start_detect:
        # lightblue 
        controller.lightbar.set_color(173, 216, 230)



    sleep(0.02)  # 50 Hz




# disable/disconnect controller device
controller.deactivate()