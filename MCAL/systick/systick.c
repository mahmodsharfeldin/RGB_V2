/************************** INCLUDE SECTION ************************/
#include "systick.h"
#include "../../LIB/BIT_MATH.h"

/************************** GLOBAL VARIABLE SECTION ************************/
static void (* ptr_callbackFunction)();
extern uint32_t SystemCoreClock;

/************************** FUNCTION DEFINITION ************************/

/*******************************************************************************/
/* Function: SYSTICK_init    @written by: Mahmoud Sharf-Eldin                  */
/* I/P Parameters: str_systick_t pointer  							     	   */
/* Returns: enu_systickErrorState_t         				                   */
/* Description: This Function initialize a systick                             */
/*******************************************************************************/
enu_systickErrorState_t SYSTICK_init(str_systick_t* str_a_systick)
{
	enu_systickErrorState_t enu_a_retFunction = SYSTICK_OK;
	if(NULL == str_a_systick)
	{
		enu_a_retFunction = SYSTICK_NOK;
	}
	else
	{
		SYSTICK_reloadValue(str_a_systick,str_a_systick->period_ms);
		STCURRENT =0 ;
		//SET_BIT(STCTRL,ENABLE_POS);
		if(str_a_systick->interrupt_enable == SYSTICK_ENABLE_INTERRUPT)
		{
			SET_BIT(STCTRL,INTEN_POS);
			ptr_callbackFunction = str_a_systick->SysTickHandler;
		}
		else
		{
			CLEAR_BIT(STCTRL,INTEN_POS);
		}
		
		if(str_a_systick->clock_source == SYSTICK_INTERNAL_OSCILLATOR)
		{
			CLEAR_BIT(STCTRL,CLK_SRC_POS);
		}
		else if(str_a_systick->clock_source == SYSTICK_SYSTEM_CLOCK)
		{
			SET_BIT(STCTRL,CLK_SRC_POS);
		}
		else
		{
			enu_a_retFunction = SYSTICK_NOK;
		}	
	}
	return enu_a_retFunction;
}
/*******************************************************************************/
/* Function: SYSTICK_reloadValue    @written by: Mahmoud Sharf-Eldin           */
/* I/P Parameters: str_systick_t pointer & uint16_a_msPeriod		     	   */
/* Returns: enu_systickErrorState_t         				                   */
/* Description: This Function reload systick with value                        */
/*******************************************************************************/
enu_systickErrorState_t SYSTICK_reloadValue(str_systick_t* str_a_systick ,uint16_t uint16_a_msPeriod)
{
	
	enu_systickErrorState_t enu_a_retFunction = SYSTICK_OK;
	if(str_a_systick->clock_source == SYSTICK_SYSTEM_CLOCK)
	{
		STRELOAD = (uint32_t)(uint16_a_msPeriod * (SystemCoreClock / 1000))-1;
	}	
	else if(str_a_systick->clock_source == SYSTICK_INTERNAL_OSCILLATOR)
	{
		STRELOAD = (uint32_t)(uint16_a_msPeriod * (INTERNAL_OSCILLATOR_FREQ_DIV_4 / 1000))-1;
	}	
	else
	{
		enu_a_retFunction = SYSTICK_NOK;
	}
		
	return enu_a_retFunction;
}

/*******************************************************************************/
/* Function: SYSTICK_getValue    @written by: Mahmoud Sharf-Eldin              */
/* I/P Parameters: uint32_a_value pointer  							     	   */
/* Returns: enu_systickErrorState_t         				                   */
/* Description: This Function get the current value of systick register        */
/*******************************************************************************/enu_systickErrorState_t SYSTICK_getValue(uint32_t* uint32_a_value)
{
	enu_systickErrorState_t enu_a_retFunction = SYSTICK_OK;
	if(NULL == uint32_a_value)
	{
		enu_a_retFunction = SYSTICK_NOK;
	}
	else
	{
		*uint32_a_value = STCURRENT;
	}
	return enu_a_retFunction;
}
/*******************************************************************************/
/* Function: SYSTICK_start    @written by: Mahmoud Sharf-Eldin                 */
/* Returns: enu_systickErrorState_t         				                   */
/* Description: This Function start the  systick                               */
/*******************************************************************************/
enu_systickErrorState_t SYSTICK_start()
{
	enu_systickErrorState_t enu_a_retFunction = SYSTICK_OK;
	SET_BIT(STCTRL,ENABLE_POS);
	return enu_a_retFunction;
}
/*******************************************************************************/
/* Function: SYSTICK_stop     @written by: Mahmoud Sharf-Eldin                 */
/* Returns: enu_systickErrorState_t         				                   */
/* Description: This Function stop  the  systick                               */
/*******************************************************************************/
enu_systickErrorState_t SYSTICK_stop()
{
	enu_systickErrorState_t enu_a_retFunction = SYSTICK_OK;
	CLEAR_BIT(STCTRL,ENABLE_POS);
	return enu_a_retFunction;
}


/*******************************************************************************/
/* Function: SYSTICK_enableInterrupt     @written by: Mahmoud Sharf-Eldin      */
/* Returns: enu_systickErrorState_t         				                   */
/* Description: This Function enable interrupts for systick                    */
/*******************************************************************************/
enu_systickErrorState_t SYSTICK_enableInterrupt()
{
	enu_systickErrorState_t enu_a_retFunction = SYSTICK_OK;
	SET_BIT(STCTRL,INTEN_POS);
	return enu_a_retFunction;
}
/*******************************************************************************/
/* Function: SYSTICK_disableInterrupt     @written by: Mahmoud Sharf-Eldin     */
/* Returns: enu_systickErrorState_t         				                   */
/* Description: This Function disable interrupts for systick                   */
/*******************************************************************************/
enu_systickErrorState_t SYSTICK_disableInterrupt()
{
	enu_systickErrorState_t enu_a_retFunction = SYSTICK_OK;
	CLEAR_BIT(STCTRL,INTEN_POS);
	return enu_a_retFunction;
}


void SysTick_Handler(void) {
    if(ptr_callbackFunction != NULL)
		ptr_callbackFunction();
}
