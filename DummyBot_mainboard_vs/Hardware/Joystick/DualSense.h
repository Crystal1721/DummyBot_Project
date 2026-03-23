#ifndef __INC_DUALSENSE_H__
#define __INC_DUALSENSE_H__

#include "stdint.h"

typedef struct {
    uint8_t id;
    float left_stick_x;
    float left_stick_y;
    float right_stick_x;
    float right_stick_y;
    float left_trigger;
    float right_trigger;
    uint8_t button_square;
    uint8_t button_cross;
    uint8_t button_circle;
    uint8_t button_triangle;
    uint8_t button_l1;
    uint8_t button_r1;
    uint8_t button_l2;
    uint8_t button_r2;
    uint8_t button_share;
    uint8_t button_options;
    uint8_t button_ps;
    uint8_t button_touchpad;
} DualSense_State_t;


#endif /* __INC_DUALSENSE_H__ */