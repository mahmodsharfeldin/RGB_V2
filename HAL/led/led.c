/*
* led.c
*
*  Created on: Oct 13, 2023
*      Author: Mahmoud Sharf
*     Version: 0.1
*/

#include "../../MCAL/gpio/gpio.h"
#include "led.h"
/************************* FUNCTIONS DEFINEITIONS SECTION *****************************/

/*******************************************************************************/
/* Function: LED_init    @written by: Mahmoud Sharf-Eldin                      */
/* I/P Parameters: str_a_led pointer  										   */
/* Returns: enu_ledError_t         				                               */
/* Description: This Function initialize a led                                 */
/*******************************************************************************/
enu_ledError_t LED_init(str_led_t *str_a_led)
{
	enu_ledError_t enu_a_retFunction = LED_OK;
	if(NULL == str_a_led)
	{
		enu_a_retFunction = LED_WRONG_INPUT;
	}
	else
	{
		if(str_a_led->port <= MAX_PORT_INDEX && str_a_led->pin <= MAX_PIN_INDEX &&
		str_a_led->port >= MIN_PORT_INDEX && str_a_led->pin >= MIN_PIN_INDEX
		)
		{
			str_pinConfig_t str_a_ledPin = {str_a_led->port, str_a_led->pin, str_a_led->state, GPIO_DIRECTION_OUTPUT, GPIO_TWO_MA_DRIVE};
			if (GPIO_init(&str_a_ledPin) == GPIO_OK )
			{
				str_a_led->state = LED_OFF;
				enu_a_retFunction = LED_OK;
			} 
			else 
			{
				enu_a_retFunction = LED_OPERATION_FAILED;
			}
		}
		 else {
			enu_a_retFunction = LED_WRONG_INPUT;
		}
	}
	
	return enu_a_retFunction;
}
/*******************************************************************************/
/* Function: LED_on    @written by: Mahmoud Sharf-Eldin                        */
/* I/P Parameters: str_a_led pointer  										   */
/* Returns: enu_ledError_t         				                               */
/* Description: This Function turn a led on                                    */
/*******************************************************************************/
enu_ledError_t LED_on(str_led_t *str_a_led)
{
	enu_ledError_t enu_a_retFunction = LED_OK;
	if(NULL == str_a_led)
	{
		enu_a_retFunction = LED_WRONG_INPUT;
	}
	else
	{
		if(str_a_led->port <= MAX_PORT_INDEX && str_a_led->pin <= MAX_PIN_INDEX &&
		str_a_led->port >= MIN_PORT_INDEX && str_a_led->pin >= MIN_PIN_INDEX
		)
		{
			str_pinConfig_t str_a_ledPin = {str_a_led->port, str_a_led->pin, str_a_led->state, GPIO_DIRECTION_OUTPUT, GPIO_TWO_MA_DRIVE};
			if (GPIO_setPinStatus(&str_a_ledPin,GPIO_HIGH) == GPIO_OK )
			{
				str_a_led->state = LED_ON;
				enu_a_retFunction = LED_OK;
			} 
			else 
			{
				enu_a_retFunction = LED_OPERATION_FAILED;
			}
		}
		 else {
			enu_a_retFunction = LED_WRONG_INPUT;
		}
	}
	
	return enu_a_retFunction;
}
/*******************************************************************************/
/* Function: LED_off    @written by: Mahmoud Sharf-Eldin                       */
/* I/P Parameters: str_a_led pointer  										   */
/* Returns: enu_ledError_t         				                               */
/* Description: This Function turn a led off                                   */
/*******************************************************************************/
enu_ledError_t LED_off(str_led_t *str_a_led)
{
	enu_ledError_t enu_a_retFunction = LED_OK;
	if(NULL == str_a_led)
	{
		enu_a_retFunction = LED_WRONG_INPUT;
	}
	else
	{
		if(str_a_led->port <= MAX_PORT_INDEX && str_a_led->pin <= MAX_PIN_INDEX &&
		str_a_led->port >= MIN_PORT_INDEX && str_a_led->pin >= MIN_PIN_INDEX
		)
		{
			str_pinConfig_t str_a_ledPin = {str_a_led->port, str_a_led->pin, str_a_led->state, GPIO_DIRECTION_OUTPUT, GPIO_TWO_MA_DRIVE};
			if (GPIO_setPinStatus(&str_a_ledPin,GPIO_LOW) == GPIO_OK )
			{
				str_a_led->state = LED_OFF;
				enu_a_retFunction = LED_OK;
			} 
			else 
			{
				enu_a_retFunction = LED_OPERATION_FAILED;
			}
		}
		 else {
			enu_a_retFunction = LED_WRONG_INPUT;
		}
	}
	
	return enu_a_retFunction;
}
/*******************************************************************************/
/* Function: LED_toggle    @written by: Mahmoud Sharf-Eldin                    */
/* I/P Parameters: str_a_led pointer  										   */
/* Returns: enu_ledError_t         				                               */
/* Description: This Function toggle a led                                     */
/*******************************************************************************/
enu_ledError_t LED_toggle(str_led_t *str_a_led)
{
	enu_ledError_t enu_a_retFunction = LED_OK;
	if(NULL == str_a_led)
	{
		enu_a_retFunction = LED_WRONG_INPUT;
	}
	else
	{
		if(str_a_led->port <= MAX_PORT_INDEX && str_a_led->pin <= MAX_PIN_INDEX &&
		str_a_led->port >= MIN_PORT_INDEX && str_a_led->pin >= MIN_PIN_INDEX
		)
		{
			str_pinConfig_t str_a_ledPin = {str_a_led->port, str_a_led->pin, str_a_led->state , GPIO_DIRECTION_OUTPUT, GPIO_TWO_MA_DRIVE};
			if (GPIO_togglePinStatus(&str_a_ledPin) == GPIO_OK )
			{
				str_a_led->state ^= LED_ON;
				enu_a_retFunction = LED_OK;
			} 
			else 
			{
				enu_a_retFunction = LED_OPERATION_FAILED;
			}
		}
		 else {
			enu_a_retFunction = LED_WRONG_INPUT;
		}
	}
	
	return enu_a_retFunction;
}
