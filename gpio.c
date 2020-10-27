/*
 * gpio.c
 *
 *  Created on: Oct 21, 2020
 *      Author: thek1d
 */
#include "gpio.h"


/* "HAL services" */
static void gpio_writeToRegister 				(GPIO_HANDLER_LED_t *handler_led, GPIO_HANDLER_JOYSTICK_t *handler_joy)
{
	if(handler_led != NULL)
		STORE_TO_REGISTER(handler_led->_register) |= (handler_led->value) << (handler_led->pin);

	if(handler_joy != NULL)
		STORE_TO_REGISTER(handler_joy->_register) |= ( ( (handler_joy->bit.up)     << (handler_joy->pin.up)     ) |
												     ( (handler_joy->bit.down)   << (handler_joy->pin.down)   ) |
												     ( (handler_joy->bit.left)   << (handler_joy->pin.left)   ) |
												     ( (handler_joy->bit.right)  << (handler_joy->pin.right)  ) |
												     ( (handler_joy->bit.center) << (handler_joy->pin.center) )
												   );
}

static void gpio_readFromRegister				(GPIO_HANDLER_JOYSTICK_t *handler_joy)
{
	handler_joy->input.valueUp 	   =
			(READ_PIN_REGISTER(handler_joy->_register, handler_joy->pin.up)) == HIGH ? IS_PRESSED : !IS_PRESSED;

	handler_joy->input.valueDown   =
			(READ_PIN_REGISTER(handler_joy->_register, handler_joy->pin.down)) == HIGH ? IS_PRESSED : !IS_PRESSED;

	handler_joy->input.valueLeft   =
			(READ_PIN_REGISTER(handler_joy->_register, handler_joy->pin.left)) == HIGH ? IS_PRESSED : !IS_PRESSED;

	handler_joy->input.valueRight  =
			(READ_PIN_REGISTER(handler_joy->_register, handler_joy->pin.right)) == HIGH ? IS_PRESSED : !IS_PRESSED;

	handler_joy->input.valueCenter =
			(READ_PIN_REGISTER(handler_joy->_register, handler_joy->pin.center)) == HIGH ? IS_PRESSED : !IS_PRESSED;
}

static void gpio_writeLed	     				(GPIO_HANDLER_LED_t *handler_led)
{
	STORE_TO_REGISTER(handler_led->_register) ^= (handler_led->value) << (handler_led->pin);
}

static void gpio_configIOJoystick				(GPIO_HANDLER_JOYSTICK_t *handler_joy)
{
	if(handler_joy->mode == IN)
	{
		handler_joy->bit.center = INPUT;
		handler_joy->bit.down   = INPUT;
		handler_joy->bit.left   = INPUT;
		handler_joy->bit.right  = INPUT;
		handler_joy->bit.up     = INPUT;
	}
	else /* makes no sense to configure joystick as output */
	{
		handler_joy->bit.center = OUTPUT;
		handler_joy->bit.down   = OUTPUT;
		handler_joy->bit.left   = OUTPUT;
		handler_joy->bit.right  = OUTPUT;
		handler_joy->bit.up     = OUTPUT;
	}

	handler_joy->_register  = GPIO_A_MODER;

}

static void gpio_pinMappingJoystick				(GPIO_HANDLER_JOYSTICK_t *handler_joy)
{
	handler_joy->pin.center = PA0;
	handler_joy->pin.down   = PA5;
	handler_joy->pin.left   = PA1;
	handler_joy->pin.right  = PA2;
	handler_joy->pin.up     = PA3;
}

static void gpio_selectPulldownResistorsJoystick(GPIO_HANDLER_JOYSTICK_t *handler_joy)
{
	handler_joy->bit.center = PULLD_OFF;			// done in hardware
	handler_joy->bit.down   = PULLD_ON;
	handler_joy->bit.left   = PULLD_ON;
	handler_joy->bit.right  = PULLD_ON;
	handler_joy->bit.up     = PULLD_ON;

	handler_joy->_register = GPIO_A_PUPDR;
}

static void gpio_writeConfig				 	(GPIO_HANDLER_JOYSTICK_t *handler_joy)
{
	// ToDO  GPIO_HANDLER_LED_t *handler_led
	*((uint16_t*)(handler_joy->_register)) |= ( ( (handler_joy->bit.up)     << (handler_joy->pin.up     ) )|
												( (handler_joy->bit.down)   << (handler_joy->pin.down   ) )|
												( (handler_joy->bit.left)   << (handler_joy->pin.left   ) )|
												( (handler_joy->bit.right)  << (handler_joy->pin.right  ) )|
												( (handler_joy->bit.center) << (handler_joy->pin.center ) )
											   );
}

static void gpio_prepareWriteConfig				(GPIO_HANDLER_JOYSTICK_t *handler_joy)
{
	uint8_t resetValue = 0x02;

	//multiply by 2 for alignment
	STORE_TO_REGISTER(handler_joy->_register) &=  ~( ( (resetValue) << (handler_joy->pin.center * 2) )|
													 ( (resetValue) << (handler_joy->pin.left   * 2) )|
													 ( (resetValue) << (handler_joy->pin.right  * 2) )|
													 ( (resetValue) << (handler_joy->pin.up     * 2) )|
													 ( (resetValue) << (handler_joy->pin.down   * 2) )

											       );

//	-------------------------------test------------------------------------
//	uint16_t temp = ~( ( (resetValue) << (handler_joy->pin.center * 2) )|
//			 ( (resetValue) << (handler_joy->pin.left   * 2) )|
//			 ( (resetValue) << (handler_joy->pin.right  * 2) )|
//			 ( (resetValue) << (handler_joy->pin.up     * 2) )|
//			 ( (resetValue) << (handler_joy->pin.down   * 2) )
//
//	       );
//
//	uint16_t *temp_address = ((uint16_t *)handler_joy->_register);
//
//	uint16_t valueOfPUPDR = ~(*temp_address & temp);
//
//	*temp_address =  valueOfPUPDR;

}

/* "Middleware" */
void 		gpio_initLed	     (GPIO_HANDLER_LED_t *handler_led)
{
	if(handler_led->color == LED_GREEN)
	{
		handler_led->pin   		= PE8;
		handler_led->_register  = (uint32_t)GPIO_E_MODER;
		handler_led->value 		= handler_led->mode == OUT ? OUTPUT : INPUT;
		gpio_writeToRegister(handler_led, NULL);
	}

	else // LED_RED
	{
		handler_led->pin 		= PB2;
		handler_led->_register  =  (uint32_t)GPIO_B_MODER;
		handler_led->value 		= handler_led->mode == OUT ? OUTPUT : INPUT;
		gpio_writeToRegister(handler_led, NULL);
	}

}

void 		gpio_switchLed	     (GPIO_HANDLER_LED_t *handler_led)
{
	if(!(handler_led->isMapped))
	{
		if(handler_led->color == LED_GREEN)
		{
			handler_led->pin   		= PE8;
			handler_led->_register  = (uint32_t)GPIO_E_ODR;
			handler_led->value 		= ON;
			handler_led->isMapped	= TRUE;
			gpio_writeLed(handler_led);
		}
		else // LED_RED
		{
			handler_led->pin  	   = PB2;
			handler_led->_register = (uint32_t)GPIO_B_ODR;
			handler_led->value 	   = ON;
			handler_led->isMapped  = TRUE;
			gpio_writeLed(handler_led);
		}
	}
	else gpio_writeLed(handler_led);
}

void 		gpio_initJoystick    (GPIO_HANDLER_JOYSTICK_t *handler_joy)
{

	gpio_pinMappingJoystick				(handler_joy);
	gpio_configIOJoystick  				(handler_joy);				// Set data direction
	gpio_prepareWriteConfig				(handler_joy);
	gpio_writeConfig   					(handler_joy);
	gpio_selectPulldownResistorsJoystick(handler_joy);
	gpio_prepareWriteConfig				(handler_joy);				// Set pulldown resistors
	gpio_writeConfig   					(handler_joy);

}

void		gpio_readJoystick	 (GPIO_HANDLER_JOYSTICK_t *handler_joy)
{
	handler_joy->_register = GPIO_A_IDR;
	gpio_readFromRegister(handler_joy);
}
