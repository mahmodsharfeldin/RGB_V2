/*
 * button.h
 *
 *  Created on: Oct 04, 2023
 *      Author: msharfeldin
 *     Version: 0.1
 */
#ifndef BUTTON_H
#define BUTTON_H

/************************** USER DEFINED PROTOTYPES ************************/
#include "../../lib/STD_TYPES.h"

typedef enum __buttonError{
BUTTON_OK,
BUTTON_WRONG_INPUT,
BUTTON_OP_FAILED
}enu_buttonError_t;

typedef enum __buttonPin{
	 BUTTON_PIN0 = 0,
	 BUTTON_PIN1,
	 BUTTON_PIN2,
	 BUTTON_PIN3,
	 BUTTON_PIN4,
	 BUTTON_PIN5,
	 BUTTON_PIN6,
	 BUTTON_PIN7
}enu_buttonPin_t;

typedef enum {
    BUTTON_INT_PRIORITY_0 = 0,
    BUTTON_INT_PRIORITY_1,
    BUTTON_INT_PRIORITY_2,
    BUTTON_INT_PRIORITY_3,
    BUTTON_INT_PRIORITY_4,
    BUTTON_INT_PRIORITY_5,
    BUTTON_INT_PRIORITY_6,
    BUTTON_INT_PRIORITY_7
}enu_btnInterrupt_priority_t;

typedef enum __buttonPort{
	BUTTON_PORTA = 0,
	BUTTON_PORTB,
	BUTTON_PORTC,
	BUTTON_PORTD,
	BUTTON_PORTE,
	BUTTON_PORTF,
}enu_buttonPort_t;

typedef enum {
    BUTTON_PULL_UP = 0,
    BUTTON_PULL_DOWN	
}enu_buttonConnection_t;

typedef enum {
    BUTTON_DISABLE_INTERRUPT = 0,
    BUTTON_ENABLE_INTERRUPT	
}enu_btnInterrupt_t;


typedef enum {
    BUTTON_FALLING_EDGE_TRIGGER = 0,
    BUTTON_RAISING_EDGE_TRIGGER,
	BUTTON_LOW_LEVEL_TRIGGER,
	BUTTON_HIGH_LEVEL_TRIGGER	
}enu_btnInterrupt_trigger_t;

typedef struct __button{
	enu_buttonPort_t	port;
	enu_buttonPin_t		pin;
	enu_buttonConnection_t  connection;
	enu_btnInterrupt_t 			enable_interrupt;
	enu_btnInterrupt_trigger_t 	interrupt_trigger;
	void (* btnInterruptHandler) (void);
	enu_btnInterrupt_priority_t  interrupt_priority;
}str_button_t;

/************************** FUNCTION DECLARATION ************************/

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

enu_buttonError_t BUTTON_init(str_button_t *str_a_buttton);

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

enu_buttonError_t BUTTON_getValue(str_button_t *str_a_buttton, uint8_t *uint8_a_buttonValue);


#endif
