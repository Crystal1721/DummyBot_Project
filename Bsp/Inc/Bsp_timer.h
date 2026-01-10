/*
 * Bsp_timer.h
 *
 *  Created on: Nov 21, 2025
 *      Author: oscar
 */

#ifndef INC_BSP_TIMER_H_
#define INC_BSP_TIMER_H_

#include "main.h"

void BSP_Timer_Init(void);

void BSP_Timer_Handler(TIM_HandleTypeDef *htim);

#endif /* INC_BSP_TIMER_H_ */
