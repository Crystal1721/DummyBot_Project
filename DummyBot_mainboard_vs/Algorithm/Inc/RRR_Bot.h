#ifndef INC_RRR_BOT_H__
#define INC_RRR_BOT_H__

#include "stdint.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define DT     0.005f      // 20ms
#define SPEED  100.0f      // mm/s
#define DEAD   0.05f


typedef struct {

    uint8_t Dummy_bot_Buffer[256];

    float joy_x;
    float joy_y;
    float joy_z;

} Position_t;

typedef struct {

    uint8_t auto_mode;
    uint8_t rst;
    uint8_t detect_colour;
    uint8_t start_detect;

    float temp_current_q1;
    float temp_current_q2;
    float temp_current_q3;

    float current_q1;
    float current_q2;
    float current_q3;

    float current_servo_q1;
    float current_servo_q2;
    float current_servo_q3;

    float q1_min;
    float q1_max;
    float q2_min;
    float q2_max;
    float q3_min;
    float q3_max;

    // DH parameters (Proximal Convention)
    uint8_t L1;
    uint8_t L2;
    uint8_t L3;
    uint8_t L4;

    // Lengths of links which attach to the hoarm
    uint8_t L2A;
    uint8_t LAB;
    uint8_t LB3;

    // Servo angle
    float servoAngle_q1;
    float servoAngle_q2;
    float servoAngle_q3;

    float x_EE;
    float y_EE;
    float z_EE;

    float target_x_EE;
    float target_y_EE;
    float target_z_EE;

    float x_EE_FK;
    float y_EE_FK;
    float z_EE_FK;  
     
    Position_t joy;

    uint8_t suction_on;


} RRR_Bot_t;


extern RRR_Bot_t Dummy_bot;

void RRR_Bot_Init (RRR_Bot_t * Dummy_bot, float init_q1, float init_q2, float init_q3);
void updateJointAngles (RRR_Bot_t * Dummy_bot, float q1, float q2, float q3);
int checkErrorJointLimits (RRR_Bot_t * Dummy_bot, float q1, float q2, float q3);
void q3CalcLimits(RRR_Bot_t * Dummy_bot, float q2);
void map_kinematicsToServoAngles(RRR_Bot_t * Dummy_bot);
void parse_joystickInput(RRR_Bot_t * Dummy_bot, uint8_t* input_buffer);

static float deadzone(float v);
void update_target_position(RRR_Bot_t *bot);

#endif /* INC_RRR_BOT_H__ */
