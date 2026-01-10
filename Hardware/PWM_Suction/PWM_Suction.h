#ifndef __PWM_SUCTION_H__
#define __PWM_SUCTION_H__

#include "Bsp_pwm.h"
#include "tim.h"
#include "stdint.h"

typedef struct {
    uint8_t Suction_id;
    TIM_HandleTypeDef *htim;
    uint32_t Channel;
    uint16_t Suction_PWM;

} Suction_t;

extern Suction_t Suction1;

void PWM_Suction_Init(Suction_t *Suction , TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t id);
void Set_PWM(Suction_t *Suction, float PWM_value);

#endif // __PWM_SUCTION_H__

