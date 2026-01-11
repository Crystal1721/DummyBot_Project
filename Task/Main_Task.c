#include "Main_Task.h"
#include "Bsp_usart.h"
#include "Bsp_led.h"
#include "PWM_Servo.h"
#include "PWM_Suction.h"
#include "Inverse_Kinematics.h"
#include "Forward_Kinematics.h"
#include "RRR_Bot.h"
#include "user_lib.h"
#include "cmsis_os2.h"
#include "main.h"
#include "cmsis_os.h"

ramp_function_source_t ramp_q1, ramp_q2, ramp_q3;
Servo_t Servo1, Servo2, Servo3;
Suction_t Suction1;
RRR_Bot_t Dummy_bot;

void StartMainTask(void *argument)
{
  /* USER CODE BEGIN StartMainTask */

  osDelay(2000);

  RRR_Bot_Init(&Dummy_bot, 0.0f, 70.0f, -100.0f);

  //  DH parameters (Proximal Convention)
  Dummy_bot.L1 = 92;
  Dummy_bot.L2 = 135;
  Dummy_bot.L3 = 147;
  Dummy_bot.L4 = 87;

  // Lengths of links which attach to the hoarm
  Dummy_bot.L2A = 60;
  Dummy_bot.LAB = 140;
  Dummy_bot.LB3 = 60;

  Dummy_bot.q1_min = -40.0f;
  Dummy_bot.q1_max = 40.0f;
  Dummy_bot.q2_min = 39.0f;
  Dummy_bot.q2_max = 120.0f;

  map_kinematicsToServoAngles(&Dummy_bot);

  uint8_t test_auto = 0;
  /* Infinite loop */
  for(;;)
  {

    if(Dummy_bot.auto_mode)
    {
      switch (test_auto)
      {
      case 0:
      // original position
        Dummy_bot.x_EE = 239.47f;
        Dummy_bot.y_EE = -16.68f;
        Dummy_bot.z_EE = 210.74f;

        osDelay(3000);
        test_auto = 1;
        /* code */
        break;
      
      case 1:
      //  pick position
        Dummy_bot.x_EE = 250.0f;
        Dummy_bot.y_EE = 0.0f;
        Dummy_bot.z_EE = 90.0f;  
        osDelay(3000);
        test_auto = 2;
        break;
      case 2:
      // place position A
        Dummy_bot.x_EE = 250.0f;
        Dummy_bot.y_EE = -170.0f;
        Dummy_bot.z_EE = 85.0f;

        osDelay(3000);
        test_auto = 3;
        break;
      case 3:
        // original position
        Dummy_bot.x_EE = 239.47f;
        Dummy_bot.y_EE = -16.68f;
        Dummy_bot.z_EE = 210.74f;
        osDelay(3000);
        test_auto = 4;
        break;
      case 4:
      //  pick position
        Dummy_bot.x_EE = 250.0f;
        Dummy_bot.y_EE = 0.0f;
        Dummy_bot.z_EE = 90.0f;  
        osDelay(3000);
        test_auto = 5;
        break;
      case 5:
        // place position B
        Dummy_bot.x_EE = 250.0f;
        Dummy_bot.y_EE = 170.0f;
        Dummy_bot.z_EE = 85.0f;
        osDelay(3000);
        test_auto = 6;
        break;
      case 6:
        // original position
        Dummy_bot.x_EE = 239.47f;
        Dummy_bot.y_EE = -16.68f;
        Dummy_bot.z_EE = 210.74f;
        osDelay(3000);
        test_auto = 99;
        break;

      default:
        break;
      }
        // In auto mode, the target positions are pre-defined
    } else {
      test_auto = 0;
    }


    InverseKinematics(&Dummy_bot);
    updateJointAngles(&Dummy_bot, Dummy_bot.current_q1, Dummy_bot.current_q2, Dummy_bot.current_q3);

    Forward_Kinematics(&Dummy_bot);
    
    map_kinematicsToServoAngles(&Dummy_bot);

    Set_Angle(&Servo1, Dummy_bot.servoAngle_q1);
    Set_Angle(&Servo2, Dummy_bot.servoAngle_q2);
    Set_Angle(&Servo3, Dummy_bot.servoAngle_q3);
    
    
    if(Dummy_bot.suction_on)
    {
        Set_PWM(&Suction1, 1900);
        BSP_LED_On(LED1);
    }
    else
    {
        Set_PWM(&Suction1, 500);
        BSP_LED_Off(LED1);
    }

    osDelay(10);

  }
  /* USER CODE END StartMainTask */
}
