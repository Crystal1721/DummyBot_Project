/*
 * Bsp_delay.h
 *
 *  Created on: Oct 15, 2025
 *      Author: oscar
 */

#ifndef INC_BSP_DELAY_H_
#define INC_BSP_DELAY_H_

#include <stdint.h>
#include <stdbool.h>

extern void delay_init(void);
extern void delay_us(uint16_t nus);
extern void delay_ms(uint16_t nms);


#endif /* INC_BSP_DELAY_H_ */
