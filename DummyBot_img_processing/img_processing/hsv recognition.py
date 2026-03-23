import cv2
import numpy as np

# start webcam (0 or 1 depending on device)
cap = cv2.VideoCapture(2)

# set frame size (optional)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

while True:
    success, frame = cap.read()
    if not success:
        break

    # convert BGR to HSV
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # get height and width
    height, width, _ = frame.shape
    cx = int(width / 2)
    cy = int(height / 2)

    # get HSV and BGR at center
    pixel_center = hsv_frame[cy, cx]
    hue_value = pixel_center[0]
    saturation_value = pixel_center[1]
    brightness_value = pixel_center[2]
    hue_str = str(hue_value)
    saturation_str = str(saturation_value)
    brightness_str = str(brightness_value)

    # get BGR at center
    b, g, r = int(frame[cy, cx][0]), int(frame[cy, cx][1]), int(frame[cy, cx][2])

    # draw UI on frame: white info panel at top-left
    panel_x, panel_y = 5, 5
    panel_w, panel_h = 120, 110
    # filled white rectangle as panel background
    cv2.rectangle(frame, (panel_x, panel_y), (panel_x + panel_w, panel_y + panel_h), (255, 255, 255), -1)
    cv2.putText(frame, 'H: ' + hue_str, (panel_x + 10, panel_y + 30), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 0, 0), 2)
    cv2.putText(frame, 'S: ' + saturation_str, (panel_x + 10, panel_y + 65), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 0, 0), 2)
    cv2.putText(frame, 'V: ' + brightness_str, (panel_x + 10, panel_y + 100), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 0, 0), 2)
    cv2.circle(frame, (cx, cy), 5, (25, 25, 25), 3)

    # show frame
    cv2.imshow("Color Recognition", frame)

    # exit on ESC
    key = cv2.waitKey(1)
    if key == 27:
        break

cap.release()
cv2.destroyAllWindows()
