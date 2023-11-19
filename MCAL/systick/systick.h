#ifndef SYS_TICK_H_
#define SYS_TICK_H_
/************************** INCLUDE SECTION ************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "TM4C123.h"

/************************** MACROS DEFINITION SECTION ************************/
#define STCTRL       	(*(volatile uint32_t *)(0xE000E010))
#define COUNT_POS    	16
#define CLK_SRC_POS    	2
#define INTEN_POS    	1
#define ENABLE_POS    	0

#define STRELOAD        (*(volatile uint32_t *)(0xE000E014))
#define STCURRENT       (*(volatile uint32_t *)(0xE000E018))
#define INTERNAL_OSCILLATOR_FREQ_DIV_4       (4000000)	

/************************** USER DEFINED PROTOTYPES SECTION ************************/
typedef enum{
	SYSTICK_OK = 0,
	SYSTICK_NOK
} enu_systickErrorState_t;

typedef enum{
	SYSTICK_INTERNAL_OSCILLATOR = 0,
	SYSTICK_SYSTEM_CLOCK
} enu_systickClockSource_t;

typedef enum{
	SYSTICK_DISABLE_INTERRUPT = 0,
	SYSTICK_ENABLE_INTERRUPT
} enu_systickInterruptState_t;

typedef struct {
	uint16_t period_ms;
	enu_systickClockSource_t  clock_source ;
	enu_systickInterruptState_t interrupt_enable ;
	void (* SysTickHandler )(void);
} str_systick_t;

/************************** FUNCTION DECLARATION ************************/

/*******************************************************************************/
/* Function: SYSTICK_init    @written by: Mahmoud Sharf-Eldin                  */
/* I/P Parameters: str_systick_t pointer  							     	   */
/* Returns: enu_systickErrorState_t         				                   */
/* Description: This Function initialize a systick                             */
/*******************************************************************************/
enu_systickErrorState_t SYSTICK_init(str_systick_t* str_a_systick);
/*******************************************************************************/
/* Function: SYSTICK_start    @written by: Mahmoud Sharf-Eldin                 */
/* Returns: enu_systickErrorState_t         				                   */
/* Description: This Function start the  systick                               */
/*******************************************************************************/
enu_systickErrorState_t SYSTICK_start();
/*******************************************************************************/
/* Function: SYSTICK_stop     @written by: Mahmoud Sharf-Eldin                 */
/* Returns: enu_systickErrorState_t         				                   */
/* Description: This Function stop  the  systick                               */
/*******************************************************************************/
enu_systickErrorState_t SYSTICK_stop();
/*******************************************************************************/
/* Function: SYSTICK_enableInterrupt     @written by: Mahmoud Sharf-Eldin      */
/* Returns: enu_systickErrorState_t         				                   */
/* Description: This Function enable interrupts for systick                    */
/*******************************************************************************/
enu_systickErrorState_t SYSTICK_enableInterrupt();
/*******************************************************************************/
/* Function: SYSTICK_disableInterrupt     @written by: Mahmoud Sharf-Eldin     */
/* Returns: enu_systickErrorState_t         				                   */
/* Description: This Function disable interrupts for systick                   */
/*******************************************************************************/
enu_systickErrorState_t SYSTICK_disableInterrupt();
/*******************************************************************************/
/* Function: SYSTICK_reloadValue    @written by: Mahmoud Sharf-Eldin           */
/* I/P Parameters: str_systick_t pointer & uint16_a_msPeriod		     	   */
/* Returns: enu_systickErrorState_t         				                   */
/* Description: This Function reload systick with value                        */
/*******************************************************************************/
enu_systickErrorState_t SYSTICK_reloadValue(str_systick_t* str_a_systick ,uint16_t uint16_a_msPeriod);
/*******************************************************************************/
/* Function: SYSTICK_getValue    @written by: Mahmoud Sharf-Eldin              */
/* I/P Parameters: uint32_a_value pointer  							     	   */
/* Returns: enu_systickErrorState_t         				                   */
/* Description: This Function get the current value of systick register        */
/*******************************************************************************/
enu_systickErrorState_t SYSTICK_getValue(uint32_t* uint32_a_value);
#endif /* SYS_TICK_H_ */