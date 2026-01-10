/*
 * Bsp_timer.c
 *
 *  Created on: Nov 21, 2025
 *      Author: oscar
 */

#include "Bsp_timer.h"
#include "Bsp_led.h"
#include "PWM_Servo.h"
#include "PWM_Suction.h"
#include "tim.h"

void BSP_Timer_Init(void){

	/* Start TIM5 and TIM9 with interrupt; if start fails, light LED3 as an error indicator */
	if (HAL_TIM_Base_Start_IT(&htim5) != HAL_OK) {
		BSP_LED_On(LED3);
	}
	if (HAL_TIM_Base_Start_IT(&htim9) != HAL_OK) {
		/* Use LED3 to indicate TIM7 failed to start */
		BSP_LED_On(LED2);
	}
}

void BSP_Timer_Handler(TIM_HandleTypeDef *htim){

	if(htim->Instance == TIM5) // 5ms
	{
		static uint8_t led = 0;
		if (++led >= 4) {
			BSP_LED_Toggle(LED4);
			led = 0;
		}

	}
	else if(htim->Instance == TIM9) // 5ms
	{
		static uint8_t led = 0;
		if (++led >= 4) {
			BSP_LED_Toggle(LED1);
			BSP_LED_Toggle(LED2);
			BSP_LED_Toggle(LED3);
			led = 0;
		}

		__HAL_TIM_SET_COMPARE(Servo1.htim, Servo1.Channel, Servo1.Servo_PWM);
		__HAL_TIM_SET_COMPARE(Servo2.htim, Servo2.Channel, Servo2.Servo_PWM);
		__HAL_TIM_SET_COMPARE(Servo3.htim, Servo3.Channel, Servo3.Servo_PWM);
		__HAL_TIM_SET_COMPARE(Suction1.htim, Suction1.Channel, Suction1.Suction_PWM);
		
		parse_PWM_to_angle(&Servo1);
		parse_PWM_to_angle(&Servo2);
		parse_PWM_to_angle(&Servo3);
	}
}
