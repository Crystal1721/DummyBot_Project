#include "PWM_Suction.h"

void PWM_Suction_Init(Suction_t *Suction , TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t id){
    Suction->Suction_id = id;
    Suction->htim = htim;
    Suction->Channel = Channel;

    HAL_TIM_PWM_Start(Suction->htim, Suction->Channel);

    /* Initialize to default PWM value (e.g., 0) */
    Suction->Suction_PWM = 500;
    __HAL_TIM_SET_COMPARE(Suction->htim, Suction->Channel, Suction->Suction_PWM);
}

void Set_PWM(Suction_t *Suction, float PWM_value) {
    Suction->Suction_PWM = (uint16_t)PWM_value;
    if(Suction->Suction_PWM > 2500) {
        Suction->Suction_PWM = 2500; // Clamp to max value
    }else if(Suction->Suction_PWM < 500) {
        Suction->Suction_PWM = 500; // Clamp to min value
    }
    // __HAL_TIM_SET_COMPARE(Suction->htim, Suction->Channel, Suction->Suction_PWM);

}
