/*
 * Bsp_led.h
 *
 *  Created on: Oct 15, 2025
 *      Author: oscar
 */

#ifndef INC_BSP_LED_H_
#define INC_BSP_LED_H_

#define LED1_GPIO_PORT GPIOB
#define LED1_PIN GPIO_PIN_0

#define LED2_GPIO_PORT GPIOB
#define LED2_PIN GPIO_PIN_1

#define LED3_GPIO_PORT GPIOB
#define LED3_PIN GPIO_PIN_2

#define LED4_GPIO_PORT GPIOC
#define LED4_PIN GPIO_PIN_13

typedef enum
{
	LED1 = 0,
	LED2,
	LED3,
	LED4,
	LEDMAX
} LED_TypeDef;

void BSP_LED_Init(void);
void BSP_LED_On(LED_TypeDef led);
void BSP_LED_Off(LED_TypeDef led);
void BSP_LED_Toggle(LED_TypeDef led);

#endif /* INC_BSP_LED_H_ */
