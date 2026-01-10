#include "Main_Task.h"
#include "Bsp_usart.h"
#include "Bsp_led.h"
#include "PWM_Servo.h"
#include "PWM_Suction.h"
#include "Inverse_Kinematics.h"
#include "Forward_Kinematics.h"
#include "RRR_Bot.h"
#include "cmsis_os2.h"
#include "main.h"
#include "cmsis_os.h"


void StartMainTask(void *argument)
{
  /* USER CODE BEGIN StartMainTask */

  osDelay(1000);
  
  RRR_Bot_Init(&Dummy_bot, 0.0f, 90.0f, -130.0f);

  //  DH parameters (Proximal Convention)
  Dummy_bot.L1 = 92;
  Dummy_bot.L2 = 135;
  Dummy_bot.L3 = 147;
  Dummy_bot.L4 = 87;

  // Lengths of links which attach to the hoarm
  Dummy_bot.L2A = 60;
  Dummy_bot.LAB = 140;
  Dummy_bot.LB3 = 60;

  Dummy_bot.q1_min = -30.0f;
  Dummy_bot.q1_max = 30.0f;
  Dummy_bot.q2_min = 39.0f;
  Dummy_bot.q2_max = 120.0f;

  float test_x = 240.0f;
  float test_y = 85.0f;
  float test_z = 200.0f;

  /* Infinite loop */
  for(;;)
  {
    Dummy_bot.x_EE = test_x;
    Dummy_bot.y_EE = test_y;
    Dummy_bot.z_EE = test_z;


    map_kinematicsToServoAngles(&Dummy_bot);
    InverseKinematics(&Dummy_bot);
    updateJointAngles(&Dummy_bot, Dummy_bot.current_q1, Dummy_bot.current_q2, Dummy_bot.current_q3);

    Forward_Kinematics(&Dummy_bot);

    Set_Angle(&Servo1, Dummy_bot.servoAngle_q1);
    Set_Angle(&Servo2, Dummy_bot.servoAngle_q2);
    Set_Angle(&Servo3, Dummy_bot.servoAngle_q3);
    
    map_kinematicsToServoAngles(&Dummy_bot);
    

    // Set_PWM(&Suction1, 2500);
    // osDelay(5000);
    // Set_PWM(&Suction1, 500);
    // osDelay(10000);


    osDelay(10);

  }
  /* USER CODE END StartMainTask */
}
