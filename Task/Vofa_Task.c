#include "Vofa_Task.h"
#include "Bsp_vofa.h"
#include "main.h"
#include "cmsis_os.h"

#include "Bsp_usart.h"

#include "RRR_Bot.h"
#include "PWM_Servo.h"


void StartVofaTask(void const * argument)
{
  /* USER CODE BEGIN StartVofaTask */
  
  vofa_start(); // testing

  /* Infinite loop */
  for(;;)
  {

    //ekf姿态解算的值
    vofa_send_data(0, Dummy_bot.current_q1);
    vofa_send_data(1, Dummy_bot.current_q2);
    vofa_send_data(2, Dummy_bot.current_q3);
    vofa_send_data(3, Dummy_bot.servoAngle_q1);
    vofa_send_data(4, Dummy_bot.servoAngle_q2);
    vofa_send_data(5, Dummy_bot.servoAngle_q3);
    vofa_send_data(6, Dummy_bot.x_EE_FK);
    vofa_send_data(7, Dummy_bot.y_EE_FK);
    vofa_send_data(8, Dummy_bot.z_EE_FK);

    vofa_send_data(9, Servo1.Servo_PWM);
    vofa_send_data(10, Servo2.Servo_PWM);
    vofa_send_data(11, Servo3.Servo_PWM);
    // Call the function to send the frame tail
    vofa_sendframetail();

    osDelay(1);
  }
  /* USER CODE END StartVofaTask */
}