#include "Bsp_EXTI.h"
#include "stm32f4xx_hal.h"
#include "RRR_Bot.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_3) 
    {
        if(Dummy_bot.auto_mode == 0)
        {
            // Dummy_bot.x_EE = 300.0f;
            // Dummy_bot.y_EE = 100.0f;
            // Dummy_bot.z_EE = 200.0f;  

            //  pick position
            // Dummy_bot.x_EE = 250.0f;
            // Dummy_bot.y_EE = 0.0f;
            // Dummy_bot.z_EE = 90.0f;  

            // place position B
            Dummy_bot.x_EE = 250.0f;
            Dummy_bot.y_EE = 170.0f;
            Dummy_bot.z_EE = 85.0f;

        }


    } else if(GPIO_Pin == GPIO_PIN_4) 
    {
        if(Dummy_bot.auto_mode == 0)
        {
            // Dummy_bot.x_EE = 120.0f;
            // Dummy_bot.y_EE = -85.0f;
            // Dummy_bot.z_EE = 150.0f;

            // original position
            // Dummy_bot.x_EE = 239.47f;
            // Dummy_bot.y_EE = -16.68f;
            // Dummy_bot.z_EE = 210.74f;


            // transfer position
            // Dummy_bot.x_EE = 250.0f;
            // Dummy_bot.y_EE = -170.0f;
            // Dummy_bot.z_EE = 210.0f;

            // place position A
            Dummy_bot.x_EE = 250.0f;
            Dummy_bot.y_EE = -170.0f;
            Dummy_bot.z_EE = 85.0f;


        }
    }
}
