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

  /* Infinite loop */
  for(;;)
  {

    map_kinematicsToServoAngles(&Dummy_bot);
    InverseKinematics(&Dummy_bot);
    updateJointAngles(&Dummy_bot, Dummy_bot.current_q1, Dummy_bot.current_q2, Dummy_bot.current_q3);

    Forward_Kinematics(&Dummy_bot);
    
    map_kinematicsToServoAngles(&Dummy_bot);

    Set_Angle(&Servo1, Dummy_bot.servoAngle_q1);
    Set_Angle(&Servo2, Dummy_bot.servoAngle_q2);
    Set_Angle(&Servo3, Dummy_bot.servoAngle_q3);
    
    

    // Set_PWM(&Suction1, 2500);
    // osDelay(5000);
    // Set_PWM(&Suction1, 500);
    // osDelay(10000);


    osDelay(10);

  }
  /* USER CODE END StartMainTask */
}
