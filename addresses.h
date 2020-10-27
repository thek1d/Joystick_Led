/*
 * macros.h
 *
 *  Created on: Oct 26, 2020
 *      Author: thek1d
 */

#ifndef SRC_ADDRESSES_H_
#define SRC_ADDRESSES_H_

#define PORT_A_BASE			0x48000000
#define PORT_B_BASE			0x48000400
#define PORT_E_BASE			0x48001000

#define GPIO_X_IDR_OFFSET	0x10
// Input data register
#define GPIO_A_IDR			PORT_A_BASE + GPIO_X_IDR_OFFSET
#define GPIO_B_IDR			PORT_B_BASE + GPIO_X_IDR_OFFSET
#define GPIO_E_IDR			PORT_E_BASE + GPIO_X_IDR_OFFSET

#define GPIO_X_ODR_OFFSET	0x14
// Output data register
#define GPIO_A_ODR			PORT_A_BASE + GPIO_X_ODR_OFFSET
#define GPIO_B_ODR			PORT_B_BASE + GPIO_X_ODR_OFFSET
#define GPIO_E_ODR			PORT_E_BASE + GPIO_X_ODR_OFFSET

#define GPIO_X_MODE_OFFSET  0x00000000
// 00 Input mode... 01...Output mode... 10 Alternate function... 11 Analog mode
#define GPIO_A_MODER 		PORT_A_BASE + GPIO_X_MODE_OFFSET
#define GPIO_B_MODER 		PORT_B_BASE + GPIO_X_MODE_OFFSET
#define GPIO_E_MODER 		PORT_E_BASE + GPIO_X_MODE_OFFSET

#define GPIO_X_PUPDR_OFFSET	0x0C
// Pull-up/Pull-down	00 No pull up, pull down... 01 Pull-up... 10 Pull-down
#define GPIO_A_PUPDR		PORT_A_BASE + GPIO_X_PUPDR_OFFSET
#define GPIO_B_PUPDR		PORT_B_BASE + GPIO_X_PUPDR_OFFSET
#define GPIO_E_PUPDR		PORT_E_BASE + GPIO_X_PUPDR_OFFSET

#define GPIO_X_BSRR_OFFSET	0x18
#define GPIO_A_BSRR			PORT_A_BASE + GPIO_X_BSRR_OFFSET
#define GPIO_B_BSRR			PORT_B_BASE + GPIO_X_BSRR_OFFSET
#define GPIO_E_BSRR			PORT_E_BASE + GPIO_X_BSRR_OFFSET

#define PB2 				2				// PB2 -> Red led
#define PE8 				8				// PE8 -> Green led
#define PA1					1				// PA1 -> Joystick left
#define PA0					0				// PA0 -> Joystick center(pulldown already included!)
#define PA5					5				// PA5 -> Joystick down
#define PA3					3				// PA3 -> Joystick up
#define PA2					2				// PA2 -> Joystick right

#endif /* SRC_ADDRESSES_H_ */
