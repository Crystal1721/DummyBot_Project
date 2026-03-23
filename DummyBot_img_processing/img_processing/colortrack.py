import cv2
import numpy as np

# def findColor(img,myColors,myColorValues):
#     # search for desired colour in camera view
#     imgHSV = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
#     found = 0 # flag to indicate colour found in view
#     lower = np.array(myColors[0:3])
#     upper = np.array(myColors[3:6])
#     mask = cv2.inRange(imgHSV,lower,upper)
#     x,y=getContours(mask)
#     cv2.circle(imgResult,(x,y),15,myColorValues,cv2.FILLED)
#     if x==0 and y==0:
#         found = 0
#     else:
#         found = 1
#     return found
    

# def getContours(img):
#     # draw contour on object detected
#     contours,hierarchy = cv2.findContours(img,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)
#     x,y,w,h = 0,0,0,0
#     for cnt in contours:
#         area = cv2.contourArea(cnt)
#         if area>500:
#             cv2.drawContours(imgResult, cnt, -1, (255, 0, 0), 3)
#             peri = cv2.arcLength(cnt,True)
#             approx = cv2.approxPolyDP(cnt,0.02*peri,True)
#             x, y, w, h = cv2.boundingRect(approx)
#     return x+w//2,y

def displayFlagStatus(img, flag):
    """Display which flag is active (set to 1) on the video frame"""
    # Create white panel for flag display
    panel_x, panel_y = 5, 5
    panel_w, panel_h = 120, 50
    cv2.rectangle(img, (panel_x, panel_y), (panel_x + panel_w, panel_y + panel_h), (255, 255, 255), -1)
    
    if flag == 1:
        # Display blue flag status
        blue_status = 'BLUE'
        cv2.putText(img, blue_status, (panel_x + 10, panel_y + 35), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0,0,0), 2)
    
    if flag == 2:
        # Display yellow flag status
        yellow_status = 'YELLOW'
        cv2.putText(img, yellow_status, (panel_x + 10, panel_y + 35), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0,0,0), 2)

    if flag == 0:
        # Display no flag status
        no_status = 'NONE'
        cv2.putText(img, no_status, (panel_x + 10, panel_y + 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0,0,0), 2)    
    
    return img


