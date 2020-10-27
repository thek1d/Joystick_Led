/*
 * GPIO.h
 *
 *  Created on: Oct 21, 2020
 *      Author: thek1d
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

typedef enum LED
{
	LED_GREEN,
	LED_RED
}LED_t;

typedef enum MODE
{
	IN,
	OUT
}MODE_t;

/* data field */
typedef struct GPIO_HANDLER_LED
{
	MODE_t  		mode;
	uint16_t		value;
	uint32_t 		_register;
	uint16_t 		pin;
	uint8_t			isMapped;
	LED_t			color;

}GPIO_HANDLER_LED_t;

typedef struct INPUT_VALUES_JOYSTICK
{
	uint8_t			valueUp;
	uint8_t			valueLeft;
	uint8_t			valueDown;
	uint8_t			valueRight;
	uint8_t			valueCenter;
}INPUT_VALUES_JOYSTICK_t;

typedef struct JOYSTICK_PIN
{
	uint16_t	up;
	uint16_t	left;
	uint16_t	down;
	uint16_t	right;
	uint16_t	center;
}JOYSTICK_PIN_t;

typedef struct JOYSTICK_PIN_VALUE
{
	uint16_t	up;
	uint16_t	left;
	uint16_t	down;
	uint16_t	right;
	uint16_t	center;
}JOYSTICK_PIN_VALUE_t;

typedef struct GPIO_HANDLER_JOYSTICK
{
	MODE_t  					mode;
	JOYSTICK_PIN_VALUE_t		bit;					// value of that bit
	uint32_t 					_register;
	JOYSTICK_PIN_t				pin;					// number of digits of the specific bit
	INPUT_VALUES_JOYSTICK_t		input;					// value of that specific bit from reading
	uint8_t						isInit;
}GPIO_HANDLER_JOYSTICK_t;

/* function prototypes */
void gpio_initLed  (GPIO_HANDLER_LED_t 	  *handler);
void gpio_switchLed(GPIO_HANDLER_LED_t 	  *handler);

void gpio_initJoystick(GPIO_HANDLER_JOYSTICK_t *handler);
void gpio_readJoystick(GPIO_HANDLER_JOYSTICK_t *handler);
#endif /* GPIO_H_ */
