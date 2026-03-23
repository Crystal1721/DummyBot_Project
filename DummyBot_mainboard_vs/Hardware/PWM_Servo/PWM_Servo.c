#include "PWM_Servo.h"

/* Servo timing constants (units: microseconds if timer tick = 1us) */
static const float SERVO_MIN_CCR = 500.0f;   /* min pulse (µs) */
static const float SERVO_MAX_CCR = 2500.0f;  /* max pulse (µs) */

void PWM_Servo_Init(Servo_t *Servo , TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t id){
    Servo->Servo_id = id;
    Servo->htim = htim;
    Servo->Channel = Channel;

    HAL_TIM_PWM_Start(Servo->htim, Servo->Channel);

    /* Initialize to neutral (90 deg) */
    Servo->target_angle = 90.0f;
    Servo->Servo_PWM = parse_angle_to_PWM(Servo->target_angle);
    __HAL_TIM_SET_COMPARE(Servo->htim, Servo->Channel, Servo->Servo_PWM);
}

void Set_Angle(Servo_t *Servo, float angle) {
    Servo->target_angle = angle;
    Servo->Servo_PWM = parse_angle_to_PWM(Servo->target_angle);
    // __HAL_TIM_SET_COMPARE(Servo->htim, Servo->Channel, Servo->Servo_PWM);
}

uint16_t parse_angle_to_PWM (float angle) {
    /* Clamp angle to valid range */
    if (angle < 0.0f) angle = 0.0f;
    if (angle > 180.0f) angle = 180.0f;

    float ccr = SERVO_MIN_CCR + (angle / 180.0f) * (SERVO_MAX_CCR - SERVO_MIN_CCR);
    return (uint16_t)(ccr + 0.5f);
}

void parse_PWM_to_angle (Servo_t *Servo) {
    /* Clamp PWM to valid range */
    if (Servo->Servo_PWM < (uint16_t)SERVO_MIN_CCR) Servo->Servo_PWM = (uint16_t)SERVO_MIN_CCR;
    if (Servo->Servo_PWM > (uint16_t)SERVO_MAX_CCR) Servo->Servo_PWM = (uint16_t)SERVO_MAX_CCR;

    float angle = ((float)(Servo->Servo_PWM - SERVO_MIN_CCR) / (SERVO_MAX_CCR - SERVO_MIN_CCR)) * 180.0f;
    Servo->current_angle = angle;
}

