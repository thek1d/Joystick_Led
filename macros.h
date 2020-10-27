/*
 * macros.h
 *
 *  Created on: Oct 26, 2020
 *      Author: thek1d
 */

#ifndef SRC_MACROS_H_
#define SRC_MACROS_H_

#define HIGH	   1
#define IS_PRESSED 1

#define TRUE  1
#define FALSE 0

// Data direction registers
#define INPUT 0
#define OUTPUT 1

// LED
#define ON  1
#define OFF 0

// Pull down resistors
#define PULLD_OFF 0b0
#define PULLD_ON  0b10

// syntactic sugaring
#define READ_PIN_REGISTER(x,y) ((*((uint16_t *)(x)))&((1)<<(y)))
#define STORE_TO_REGISTER(x)   (*((uint16_t*)(x)))


#endif /* SRC_MACROS_H_ */
