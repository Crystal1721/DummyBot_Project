/*
 * Bsp_led.c
 *
 *  Created on: Oct 15, 2025
 *      Author: oscar
 */

#include "Bsp_led.h"
#include "main.h"

typedef struct
{
	GPIO_TypeDef *port;
	uint16_t pin;
} LED_GPIO_t;

static const LED_GPIO_t LED_Table[LEDMAX] = {
		{LED1_GPIO_PORT, LED1_PIN},
		{LED2_GPIO_PORT, LED2_PIN},
		{LED3_GPIO_PORT, LED3_PIN},
		{LED4_GPIO_PORT, LED4_PIN}
};

void BSP_LED_Init(void)
{
	BSP_LED_Off(LED1);
	BSP_LED_Off(LED2);
	BSP_LED_Off(LED3);
	BSP_LED_Off(LED4);
}

void BSP_LED_On(LED_TypeDef led)
{
	if(led < LEDMAX)
	{
		HAL_GPIO_WritePin(LED_Table[led].port, LED_Table[led].pin, GPIO_PIN_SET);
	}
}

void BSP_LED_Off(LED_TypeDef led)
{
	if(led < LEDMAX)
	{
		HAL_GPIO_WritePin(LED_Table[led].port, LED_Table[led].pin, GPIO_PIN_RESET);
	}
}
void BSP_LED_Toggle(LED_TypeDef led)
{
	if(led < LEDMAX)
	{
		HAL_GPIO_TogglePin(LED_Table[led].port, LED_Table[led].pin);
	}
}
