/*
* led.h
*
*  Created on: Oct 03, 2023
*      Author: Mahmoud Sharf
*     Version: 0.1
*/
#ifndef LED_H_
#define LED_H_
/************************** INCLUDE SECTION ************************/
#include "../../LIB/STD_TYPES.h"
#include "TM4C123.h"
/************************** USER DEFINED PROTOTYPES SECTION ************************/

// error type
typedef enum __ledError{
	LED_OK,
	LED_WRONG_INPUT,
    LED_OPERATION_FAILED
}enu_ledError_t;

typedef enum __ledPin{
	LED_PIN0 = 0,
	LED_PIN1,
	LED_PIN2,
	LED_PIN3,
	LED_PIN4,
	LED_PIN5,
	LED_PIN6,
	LED_PIN7
}enu_ledPin_t;

typedef enum __lednPort{
	LED_PORTA = 0,
	LED_PORTB,
	LED_PORTC,
	LED_PORTD,
	LED_PORTE,
	LED_PORTF,
}enu_ledPort_t;
typedef enum __ledStatus{
	LED_OFF = 0,
	LED_ON
}enu_ledStatus_t;
//struct to store led attributes
typedef struct __led{
	uint8_t port;
	uint8_t pin;
	enu_ledStatus_t state;
}str_led_t;

/************************** FUNCTION DECLARATION ************************/


/*******************************************************************************/
/* Function: LED_init    @written by: Mahmoud Sharf-Eldin                      */
/* I/P Parameters: str_a_led pointer  										   */
/* Returns: enu_ledError_t         				                               */
/* Description: This Function initialize a led                                 */
/*******************************************************************************/
enu_ledError_t LED_init(str_led_t *str_a_led);
/*******************************************************************************/
/* Function: LED_on    @written by: Mahmoud Sharf-Eldin                        */
/* I/P Parameters: str_a_led pointer  										   */
/* Returns: enu_ledError_t         				                               */
/* Description: This Function turn a led on                                    */
/*******************************************************************************/
enu_ledError_t LED_on(str_led_t *str_a_led);
/*******************************************************************************/
/* Function: LED_off    @written by: Mahmoud Sharf-Eldin                       */
/* I/P Parameters: str_a_led pointer  										   */
/* Returns: enu_ledError_t         				                               */
/* Description: This Function turn a led off                                   */
/*******************************************************************************/
enu_ledError_t LED_off(str_led_t *str_a_led);
/*******************************************************************************/
/* Function: LED_toggle    @written by: Mahmoud Sharf-Eldin                    */
/* I/P Parameters: str_a_led pointer  										   */
/* Returns: enu_ledError_t         				                               */
/* Description: This Function toggle a led                                     */
/*******************************************************************************/
enu_ledError_t LED_toggle(str_led_t *str_a_led);






#endif /* LED_H_ */
