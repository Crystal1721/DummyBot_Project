/*
 * Bsp_usart.h
 *
 *  Created on: Nov 21, 2025
 *      Author: oscar
 */
#ifndef BSP_USART_H__
#define BSP_USART_H__

#include "main.h"
#include "usart.h"
#include "dma.h"

#define USE_idle_DMA_RECEIVE 1

#define USART1_RxBufferSize  256
extern uint8_t USART1_RxBuffer[USART1_RxBufferSize];

void BSP_USART_IT_INIT(UART_HandleTypeDef *huart);
void BSP_USART_DMA_INIT(UART_HandleTypeDef *huart);
void BSP_USART_IDLE_DMA_INIT(UART_HandleTypeDef *huart);

#endif /* BSP_USART_H__ */