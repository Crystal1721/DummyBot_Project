#include "Bsp_EXTI.h"
#include "stm32f4xx_hal.h"
#include "RRR_Bot.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_3) 
    {
        Dummy_bot.x_EE = 300.0f;
        Dummy_bot.y_EE = 100.0f;
        Dummy_bot.z_EE = 200.0f;

    } else if(GPIO_Pin == GPIO_PIN_4) 
    {
        Dummy_bot.x_EE = 120.0f;
        Dummy_bot.y_EE = -85.0f;
        Dummy_bot.z_EE = 150.0f;
    }
}
