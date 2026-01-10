#include "Bsp_usart.h"
#include "hipnuc_ch0x0.h"

uint8_t USART1_RxBuffer[USART1_RxBufferSize];

void BSP_USART_IT_INIT(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
        HAL_UART_Receive_IT(&huart1, USART1_RxBuffer, 1);
    }
}

void BSP_USART_DMA_INIT(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
        HAL_UART_Receive_DMA(&huart1, USART1_RxBuffer, 1);
    }

}

void BSP_USART_IDLE_DMA_INIT(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
        HAL_UARTEx_ReceiveToIdle_DMA(&huart1, USART1_RxBuffer, sizeof(USART1_RxBuffer));
        if (huart->hdmarx != NULL)
        {
            __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
        }
    }

}

/* USER CODE BEGIN 1 */
#if (USE_idle_DMA_RECEIVE == 0)

    void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
    {
        if (huart->Instance == USART1)
        {
            // 处理UART4接收完成的逻辑
            HAL_UART_Receive_IT(&huart1, USART1_RxBuffer, sizeof(USART1_RxBuffer));
        }

    } 

#else

    void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
    {
        if (huart->Instance == USART1)
        {   

            /* Re-arm DMA receive-to-idle */
            HAL_UARTEx_ReceiveToIdle_DMA(&huart1, USART1_RxBuffer, sizeof(USART1_RxBuffer));
            if (huart->hdmarx != NULL)
            {
                __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
            }
        }
    }

#endif
/* USER CODE END 1 */
