#ifndef __PWM_SERVO_H__
#define __PWM_SERVO_H__

#include "Bsp_pwm.h"
#include "tim.h"
#include "stdint.h"

typedef struct {
    uint8_t Servo_id;
    TIM_HandleTypeDef *htim;
    uint32_t Channel;
    uint16_t Servo_PWM;
    float current_angle;
    float target_angle;
} Servo_t;

extern Servo_t Servo1, Servo2, Servo3;

void PWM_Servo_Init(Servo_t *Servo , TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t id);
void Set_Angle(Servo_t *Servo, float angle);
uint16_t parse_angle_to_PWM (float angle) ;
void parse_PWM_to_angle (Servo_t *Servo);

#endif // __PWM_SERVO_H__
