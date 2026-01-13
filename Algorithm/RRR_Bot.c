#include "RRR_Bot.h"
#include <math.h>
#include "Bsp_led.h"
#include "Bsp_usart.h"

void RRR_Bot_Init (RRR_Bot_t * Dummy_bot, float init_q1, float init_q2, float init_q3) {
    Dummy_bot->current_q1 = init_q1;
    Dummy_bot->current_q2 = init_q2;
    Dummy_bot->current_q3 = init_q3;

}


void updateJointAngles (RRR_Bot_t * Dummy_bot, float q1, float q2, float q3) {

    // check errorjointLImits

    if(checkErrorJointLimits(Dummy_bot, q1, q2, q3) !=  0) {

        BSP_LED_Off(LED1);
        BSP_LED_Off(LED2);
        BSP_LED_Off(LED3);
        Dummy_bot->current_q1 = q1;
        Dummy_bot->current_q2 = q2;
        Dummy_bot->current_q3 = q3;
        // HAL_UART_Transmit_DMA(&huart1, (uint8_t *)"1\r\n",3);
    }
}

int checkErrorJointLimits (RRR_Bot_t * Dummy_bot, float q1, float q2, float q3) {
    float temp_q1, temp_q2, temp_q3;

    temp_q1 = q1;
    temp_q2 = q2;
    temp_q3 = q3;

    // find q3_min and q3_max
    q3CalcLimits(Dummy_bot, temp_q2);

    if (temp_q1 < Dummy_bot->q1_min || temp_q1 > Dummy_bot->q1_max) {
        return 0;
        BSP_LED_On(LED1);
    } 
    
    if (temp_q2 < Dummy_bot->q2_min || temp_q2 > Dummy_bot->q2_max) {
        return 0;
        BSP_LED_On(LED2);
    }  

    if (temp_q3 < Dummy_bot->q3_min || temp_q3 > Dummy_bot->q3_max) {
        return 0;
        BSP_LED_On(LED3);
    }  

    return 1;
}

void q3CalcLimits(RRR_Bot_t * Dummy_bot, float q2) {

    /*
    Calculate q3 angle limits for the EzzyBot Arm given a value for the angle q2 in degrees
    These limits have been determined experimentally
    */ 
    Dummy_bot->q3_min = (-0.6755 * q2) - 70.768;

    Dummy_bot->q3_max = (-0.7165 * q2) - 13.144;

}

void map_kinematicsToServoAngles(RRR_Bot_t * Dummy_bot) {

    float q3_a;

    if(checkErrorJointLimits(Dummy_bot, Dummy_bot->current_q1, Dummy_bot->current_q2, Dummy_bot->current_q3) !=  0) {
        BSP_LED_Off(LED1);
        BSP_LED_Off(LED2);
        BSP_LED_Off(LED3);

        Dummy_bot->servoAngle_q1 = ((-2.0497f) * Dummy_bot->current_q1) + 91.726f;

        Dummy_bot->servoAngle_q2 = (180.0f -  Dummy_bot->current_q2);

        q3_a = 180.0f - (-Dummy_bot->current_q3);
        Dummy_bot->servoAngle_q3 = Dummy_bot->current_q2 - 45.0f + q3_a;
        
        // HAL_UART_Transmit_DMA(&huart1, (uint8_t *)"1\r\n",3);
    } 

}

#define JOY_FRAME_LEN 6

void parse_joystickInput(RRR_Bot_t *Dummy_bot, uint8_t *input_buffer)
{
    uint8_t calc_checksum =
        input_buffer[0] ^
        input_buffer[1] ^
        input_buffer[2] ^
        input_buffer[3] ^
        input_buffer[4] ^
        input_buffer[5] ^
        input_buffer[6] ^
        input_buffer[7];

    if (calc_checksum != input_buffer[8])
        return;

    Dummy_bot->auto_mode = input_buffer[0];
    Dummy_bot->rst = input_buffer[1];
    // --- Suction ---
    Dummy_bot->suction_on = input_buffer[2];

    // --- Joystick ---
    Dummy_bot->joy.joy_x =
        ((float)input_buffer[3] / 255.0f) * 2.0f - 1.0f;

    Dummy_bot->joy.joy_y =
        ((float)input_buffer[4] / 255.0f) * 2.0f - 1.0f;

    Dummy_bot->joy.joy_z =
        ((float)input_buffer[5] / 255.0f) * 2.0f - 1.0f;

    Dummy_bot->detect_colour = input_buffer[6];
    Dummy_bot->start_detect = input_buffer[7];
}


static float deadzone(float v)
{
    return (fabsf(v) < DEAD) ? 0.0f : v;
}


void update_target_position(RRR_Bot_t *bot)
{
    float jx = deadzone(bot->joy.joy_x);
    float jy = deadzone(bot->joy.joy_y);
    float jz = deadzone(bot->joy.joy_z);

    // x: 125.1 … 338.8 mm
    // y: -169.4 … 169.4 mm
    // z: 52.1 … 264.3 mm

    // === 核心：增量 ===

    bot->y_EE += (-1) *jx * SPEED * DT;
    bot->x_EE += (-1) * jy * SPEED * DT;
    bot->z_EE += (-1) * jz * SPEED * DT;

    if(bot->x_EE < 125.1f) bot->x_EE = 125.1f;
    if(bot->x_EE > 338.8f) bot->x_EE = 338.8f;
    if(bot->y_EE < -169.4f) bot->y_EE = -169.4f;
    if(bot->y_EE > 169.4f) bot->y_EE = 169.4f;
    if(bot->z_EE < 52.1f) bot->z_EE = 52.1f;
    if(bot->z_EE > 264.3f) bot->z_EE = 264.3f;
}






