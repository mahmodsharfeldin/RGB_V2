#ifndef  GPOI_h_
#define   GPOI_h_

/************************** INCLUDE SECTION ************************/
#include "../../lib/STD_TYPES.h"
#include "../../lib/BIT_MATH.h"
#include "TM4C123.h"
/************************** MACROS DEFINITION SECTION ************************/
#define APB   0
#define AHB   1
#define USED_BUS   APB
#define PORT_OFFSET(x) 				(x<4? ( 0x40000000 + ((x)* 0x1000)) : ( 0x40024000 + ((x-4)* 0x1000) ))

#define GPIO_PORTA_OFFSET   	0x40004000
#define GPIO_PORTB_OFFSET   	0x40005000
#define GPIO_PORTC_OFFSET   	0x40006000
#define GPIO_PORTD_OFFSET   	0x40007000
#define GPIO_PORTE_OFFSET   	0x40024000
#define GPIO_PORTF_OFFSET   	0x40025000
#define MIN_PIN_INDEX   0
#define MAX_PIN_INDEX   7
#define MIN_PORT_INDEX   0
#define MAX_PORT_INDEX   5
#define GPIO_PORT_DATA(PORT_OFFSET)       (*((volatile unsigned long *)(0x3FC + PORT_OFFSET)))
#define GPIO_PORT_DIR(PORT_OFFSET)        (*((volatile unsigned long *)(0x400 + PORT_OFFSET)))
#define GPIO_PORT_IS(PORT_OFFSET)         (*((volatile unsigned long *)(0x404 + PORT_OFFSET)))
#define GPIO_PORT_IBE(PORT_OFFSET)        (*((volatile unsigned long *)(0x408 + PORT_OFFSET)))
#define GPIO_PORT_IEV(PORT_OFFSET)        (*((volatile unsigned long *)(0x40C + PORT_OFFSET)))
#define GPIO_PORT_IM(PORT_OFFSET)         (*((volatile unsigned long *)(0x410 + PORT_OFFSET)))
#define GPIO_PORT_RIS(PORT_OFFSET)        (*((volatile unsigned long *)(0x414 + PORT_OFFSET)))
#define GPIO_PORT_MIS(PORT_OFFSET)        (*((volatile unsigned long *)(0x418 + PORT_OFFSET)))
#define GPIO_PORT_ICR(PORT_OFFSET)        (*((volatile unsigned long *)(0x41C + PORT_OFFSET)))
#define GPIO_PORT_AFSEL(PORT_OFFSET)      (*((volatile unsigned long *)(0x420 + PORT_OFFSET)))
#define GPIO_PORT_DR2R(PORT_OFFSET)       (*((volatile unsigned long *)(0x500 + PORT_OFFSET)))
#define GPIO_PORT_DR4R(PORT_OFFSET)       (*((volatile unsigned long *)(0x504 + PORT_OFFSET)))
#define GPIO_PORT_DR8R(PORT_OFFSET)       (*((volatile unsigned long *)(0x508 + PORT_OFFSET)))
#define GPIO_PORT_ODR(PORT_OFFSET)        (*((volatile unsigned long *)(0x50C + PORT_OFFSET)))
#define GPIO_PORT_PUR(PORT_OFFSET)        (*((volatile unsigned long *)(0x510 + PORT_OFFSET)))
#define GPIO_PORT_PDR(PORT_OFFSET)        (*((volatile unsigned long *)(0x514 + PORT_OFFSET)))
#define GPIO_PORT_SLR(PORT_OFFSET)        (*((volatile unsigned long *)(0x518 + PORT_OFFSET)))
#define GPIO_PORT_DEN(PORT_OFFSET)        (*((volatile unsigned long *)(0x51C + PORT_OFFSET)))
#define GPIO_PORT_LOCK(PORT_OFFSET)       (*((volatile unsigned long *)(0x520 + PORT_OFFSET)))
#define GPIO_PORT_CR(PORT_OFFSET)         (*((volatile unsigned long *)(0x524 + PORT_OFFSET)))
#define GPIO_PORT_AMSEL(PORT_OFFSET)      (*((volatile unsigned long *)(0x528 + PORT_OFFSET)))
#define GPIO_PORT_PCTL(PORT_OFFSET)       (*((volatile unsigned long *)(0x52C + PORT_OFFSET)))
#define GPIO_PORT_ADCCTL(PORT_OFFSET)     (*((volatile unsigned long *)(0x530 + PORT_OFFSET)))
#define GPIO_PORT_DMACTL(PORT_OFFSET)     (*((volatile unsigned long *)(0x534 + PORT_OFFSET)))
#define SYSCTL_RCGCGPIO_R       		  (*((volatile unsigned long *)0x400FE608))	
#define NVIC_EN0              			  (*((volatile unsigned long *)0xE000E100))
#define NVIC_EN1                		  (*((volatile unsigned long *)0xE000E104))
#define NVIC_DIS0                         (*((volatile unsigned long *)0xE000E180))
#define NVIC_DIS1                         (*((volatile unsigned long *)0xE000E184))
//#define NVIC_PRI11                        (*((volatile unsigned long *)0xE000E42C))
#define GPIO_PORTF_INT_OFFSET  			  25
#define GPIO_IRQ(PORT_OFFSET)  			  ((PORT_OFFSET > 4) ? ( PORT_OFFSET + GPIO_PORTF_INT_OFFSET) : (PORT_OFFSET))


/************************** USER DEFINED PROTOTYPES SECTION ************************/
typedef enum{
	GPIO_OK = 0,
	GPIO_NOK,
	GPIO_INVALID_DATA,
} enu_gpioErrorState_t;

typedef enum {
    GPIO_DIRECTION_INPUT = 0,
    GPIO_DIRECTION_OUTPUT
}enu_pinDirection_t;

typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH
}enu_bitLogic_t;


typedef enum {
    GPIO_TWO_MA_DRIVE = 0,
    GPIO_FOUR_MA_DRIVE,
	GPIO_EIGHT_MA_DRIVE
}enu_MADrive_t;

typedef enum {
    GPIO_PULL_UP = 0,
    GPIO_PULL_DOWN	
}enu_pullResistor_t;

typedef enum {
    GPIO_DISABLE_INTERRUPT = 0,
    GPIO_ENABLE_INTERRUPT	
}enu_interrupt_t;


typedef enum {
    GPIO_FALLING_EDGE_TRIGGER = 0,
    GPIO_RAISING_EDGE_TRIGGER,
	GPIO_LOW_LEVEL_TRIGGER,
	GPIO_HIGH_LEVEL_TRIGGER	
}enu_interrupt_trigger_t;

typedef enum {
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}enu_pinIndex_t;

typedef enum {
    GPIO_INT_PRIORITY_0 = 0,
    GPIO_INT_PRIORITY_1,
    GPIO_INT_PRIORITY_2,
    GPIO_INT_PRIORITY_3,
    GPIO_INT_PRIORITY_4,
    GPIO_INT_PRIORITY_5,
    GPIO_INT_PRIORITY_6,
    GPIO_INT_PRIORITY_7
}enu_interrupt_priority_t;
typedef enum {
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,    
	PORTE_INDEX,
	PORTF_INDEX,
}enu_portIndex_t;

typedef struct {
	uint8_t 					port_index;
	uint8_t 					pin_index;
	uint8_t 					pin_state;
	uint8_t 					pin_direction;
	enu_MADrive_t 				pin_MADrive;
	enu_pullResistor_t 			pin_connection;
	enu_interrupt_t 			enable_interrupt;
	enu_interrupt_trigger_t 	interrupt_trigger;
	void (* gpioInterruptHandler) (void);
	enu_interrupt_priority_t    interrupt_priority; 
} str_pinConfig_t;
/************************** FUNCTION DECLARATION ************************/

/*******************************************************************************/
/* Function: GPIO_init    @written by: Mahmoud Sharf-Eldin                     */
/* I/P Parameters: str_pinConfig_t pointer  								   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function initialize a GPIO pin                            */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_init(const str_pinConfig_t* str_a_pin);
/*******************************************************************************/
/* Function: GPIO_outputHigh    @written by: Mahmoud Sharf-Eldin               */
/* I/P Parameters: str_pinConfig_t pointer  								   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function output high on  a GPIO pin                       */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_outputHigh(const str_pinConfig_t* str_a_pin);
/*******************************************************************************/
/* Function: GPIO_outputLow    @written by: Mahmoud Sharf-Eldin                */
/* I/P Parameters: str_pinConfig_t pointer  								   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function output low on  a GPIO pin                        */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_outputLow(const str_pinConfig_t* str_a_pin);
/*******************************************************************************/
/* Function: GPIO_enableInterrupt    @written by: Mahmoud Sharf-Eldin          */
/* I/P Parameters: str_pinConfig_t pointer  								   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function enable interrupt  on  a GPIO pin                 */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_enableInterrupt(const str_pinConfig_t* str_a_pin);
/*******************************************************************************/
/* Function: GPIO_disableInterrupt    @written by: Mahmoud Sharf-Eldin         */
/* I/P Parameters: str_pinConfig_t pointer  								   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function disable interrupt  on  a GPIO pin                */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_disableInterrupt(const str_pinConfig_t* str_a_pin);
/*******************************************************************************/
/* Function: GPIO_togglePinStatus    @written by: Mahmoud Sharf-Eldin          */
/* I/P Parameters: str_pinConfig_t pointer  								   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function toggle status of a GPIO pin                      */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_togglePinStatus(str_pinConfig_t* str_a_pin);
/*******************************************************************************/
/* Function: GPIO_setPinDirection    @written by: Mahmoud Sharf-Eldin          */
/* I/P Parameters: str_pinConfig_t pointer & enu_pinDirection_t  			   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function configure a GPIO pin as output or input          */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_setPinDirection(const str_pinConfig_t* str_a_pin,enu_pinDirection_t enu_a_direction);
/*******************************************************************************/
/* Function: GPIO_setPinStatus    @written by: Mahmoud Sharf-Eldin             */
/* I/P Parameters: str_pinConfig_t pointer & enu_bitLogic_t      			   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function set a GPIO pin status to enu_a_status argument   */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_setPinStatus(str_pinConfig_t* str_a_pin,enu_bitLogic_t enu_a_status);
/*******************************************************************************/
/* Function: GPIO_getPinStatus    @written by: Mahmoud Sharf-Eldin             */
/* I/P Parameters: str_pinConfig_t pointer & enu_bitLogic_t pointer  		   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function get a GPIO pin status                            */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_getPinStatus(const str_pinConfig_t* str_a_pin,enu_bitLogic_t* enu_a_status);

#endif /*  GPOI_h_*/
