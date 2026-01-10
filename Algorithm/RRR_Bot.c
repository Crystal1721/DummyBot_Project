#include "RRR_Bot.h"
#include <math.h>
#include "Bsp_led.h"

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
        // return 0;
        BSP_LED_On(LED1);
    } 
    
    if (temp_q2 < Dummy_bot->q2_min || temp_q2 > Dummy_bot->q2_max) {
        // return 0;
        BSP_LED_On(LED2);
    }  

    if (temp_q3 < Dummy_bot->q3_min || temp_q3 > Dummy_bot->q3_max) {
        // return 0;
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

    }

}





