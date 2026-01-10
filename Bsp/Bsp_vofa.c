#include "Bsp_vofa.h"
#if (USE_USB_VOFA == 1)

#include "usbd_cdc_if.h"
#include "usbd_core.h"
#include "usbd_cdc.h"
#include "usb_device.h"

#endif

#include "Bsp_usart.h"

#define MAX_BUFFER_SIZE 1024
uint8_t send_buf[MAX_BUFFER_SIZE];
uint16_t cnt = 0;
/**
***********************************************************************
* @brief:      vofa_start(void)
* @param:		   void
* @retval:     void
* @details:    发送数据给上位机
***********************************************************************
**/
void vofa_start(void)   //在freertos 的默认任务里调用发送
{
#if (USE_USB_VOFA == 1)

	MX_USB_DEVICE_Init();
	
#endif
	// vofa_demo();
}

/**
***********************************************************************
* @brief:      vofa_transmit(uint8_t* buf, uint16_t len)
* @param:		void
* @retval:     void
* @details:    修改通信工具，USART或者USB
***********************************************************************
**/
void vofa_transmit(uint8_t* buf, uint16_t len)
{
#if (USE_USB_VOFA == 1)
		CDC_Transmit_FS((uint8_t *)buf, len);
	
#else
		HAL_UART_Transmit_DMA(&huart1, (uint8_t *)buf, len);
#endif	
	
}
/**
***********************************************************************
* @brief:      vofa_send_data(float data)
* @param[in]:  num: 数据编号 data: 数据 
* @retval:     void
* @details:    将浮点数据拆分成单字节
***********************************************************************
**/
void vofa_send_data(uint8_t num, float data) 
{
	send_buf[cnt++] = byte0(data);
	send_buf[cnt++] = byte1(data);
	send_buf[cnt++] = byte2(data);
	send_buf[cnt++] = byte3(data);
}
/**
***********************************************************************
* @brief      vofa_sendframetail(void)
* @param      NULL 
* @retval     void
* @details:   给数据包发送帧尾
***********************************************************************
**/
void vofa_sendframetail(void) 
{
	send_buf[cnt++] = 0x00;
	send_buf[cnt++] = 0x00;
	send_buf[cnt++] = 0x80;
	send_buf[cnt++] = 0x7f;
	
	/* 将数据和帧尾打包发送 */
	vofa_transmit((uint8_t *)send_buf, cnt);
	cnt = 0;// 每次发送完帧尾都需要清零
}
/**
***********************************************************************
* @brief      vofa_demo(void)
* @param      NULL 
* @retval     void
* @details:   demo示例
***********************************************************************
**/
void vofa_demo(void) 
{
	//ekf姿态解算的值
	vofa_send_data(0, 2.5);

	// Call the function to send the frame tail
	vofa_sendframetail();
}
