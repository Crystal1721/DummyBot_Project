#include "Bsp_pwm.h"
#include "stm32f4xx_hal_tim.h"
#include "tim.h"


void PWM_Init(void)
{
    // PWM initialization code goes here
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);

}


