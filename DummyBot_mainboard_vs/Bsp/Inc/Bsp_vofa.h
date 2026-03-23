#ifndef _BSP_VOFA_H_
#define _BSP_VOFA_H_
#include "stdint.h"

#define byte0(dw_temp)     (*(char*)(&dw_temp))
#define byte1(dw_temp)     (*((char*)(&dw_temp) + 1))
#define byte2(dw_temp)     (*((char*)(&dw_temp) + 2))
#define byte3(dw_temp)     (*((char*)(&dw_temp) + 3))

#define USE_USB_VOFA 1 //1: USB 0: UART

void vofa_start(void);
void vofa_send_data(uint8_t num, float data); 
void vofa_sendframetail(void);
void vofa_demo(void);

#endif // DEBUG