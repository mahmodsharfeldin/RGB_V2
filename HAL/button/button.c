/*
* button.c
*
*  Created on: Oct 04, 2023
*      Author: msharfeldin
*     Version: 0.1
*/

/***************************** INCLUDES SECTION ***********************************/


#include "../../MCAL/gpio/gpio.h"
#include "button.h"

/************************* FUNCTIONS DEFINEITIONS SECTION *****************************/

/*****************************************************************************/
/* Function: BUTTON_init    @written by: Mahmoud Sharf-Eldin				 */
/* I/P Parameters: st_button pointer										 */
/* Returns: en_buttonError				                                     */
/* Description: This Function initialize a pin to connect button on it       */
/*****************************************************************************/
/* Options														             */
/*****************************************************************************/
/* port     : PORTA....PORTD                                                 */
/* pin      : PIN0....PIN7        						                     */
/*****************************************************************************/
/*

*/

enu_buttonError_t BUTTON_init(str_button_t *str_a_buttton){
	enu_buttonError_t enu_a_retFunction = BUTTON_OK;
	if(str_a_buttton == NULL)
	{
		enu_a_retFunction = BUTTON_WRONG_INPUT;
	}
	else
	{
		if(str_a_buttton->port <= MAX_PORT_INDEX && str_a_buttton->pin <= MAX_PIN_INDEX &&
		str_a_buttton->port >= MIN_PORT_INDEX && str_a_buttton->pin >= MIN_PIN_INDEX
		)
		{
			str_pinConfig_t str_a_butttonPin = {str_a_buttton->port, str_a_buttton->pin, GPIO_LOW 
				,GPIO_DIRECTION_INPUT,GPIO_TWO_MA_DRIVE, str_a_buttton->connection,str_a_buttton->enable_interrupt,
				str_a_buttton->interrupt_trigger,str_a_buttton->btnInterruptHandler,str_a_buttton->interrupt_priority};
			if(GPIO_init(&str_a_butttonPin) == GPIO_OK)
			{
				enu_a_retFunction = BUTTON_OK;
			} 
			else 
			{
				enu_a_retFunction = BUTTON_OP_FAILED;
			}
		}
		else
		{
			enu_a_retFunction = BUTTON_WRONG_INPUT;
		}
	}
	return enu_a_retFunction;
}
/*****************************************************************************/
/* Function: BUTTON_getValue    @written by: Mahmoud Sharf-Eldin			 */
/* I/P Parameters: st_button pointer, uint8_t *uint8_a_buttonValue					 */
/* Returns: en_buttonError				                                     */
/* Description: This Function get value of connected button                  */
/*****************************************************************************/
/* Options														             */
/*****************************************************************************/
/* port     : PORTA....PORTD                                                 */
/* pin      : PIN0....PIN7        						                     */
/*****************************************************************************/
enu_buttonError_t BUTTON_getValue(str_button_t *str_a_buttton, uint8_t *uint8_a_buttonValue){
	enu_buttonError_t enu_a_retFunction = BUTTON_OK;
	if(str_a_buttton == NULL)
	{
		enu_a_retFunction = BUTTON_WRONG_INPUT;
	}
	else
	{
		if(str_a_buttton->port <= MAX_PORT_INDEX && str_a_buttton->pin <= MAX_PIN_INDEX &&
		str_a_buttton->port >= MIN_PORT_INDEX && str_a_buttton->pin >= MIN_PIN_INDEX
		)
		{
			str_pinConfig_t str_a_butttonPin = {str_a_buttton->port, str_a_buttton->pin, GPIO_LOW ,GPIO_DIRECTION_INPUT,GPIO_TWO_MA_DRIVE, str_a_buttton->connection};
			if(GPIO_getPinStatus(&str_a_butttonPin,uint8_a_buttonValue) == GPIO_OK)
			{
				enu_a_retFunction = BUTTON_OK;
			} 
			else 
			{
				enu_a_retFunction = BUTTON_OP_FAILED;
			}
		}
		else
		{
			enu_a_retFunction = BUTTON_WRONG_INPUT;
		}
	}
	return enu_a_retFunction;
}
