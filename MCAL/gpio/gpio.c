/************************** INCLUDE SECTION ************************/

#include "gpio.h"


/************************** STATIC FUNCITONS DECLARTION SECTION ************************/
/*******************************************************************************/
/* Function: GPIO_configureOutputConnection    @written by: Mahmoud Sharf-Eldin*/
/* I/P Parameters: str_pinConfig_t pointer                           		   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function configure tje connection of output GPIO pin      */
/*******************************************************************************/
static enu_gpioErrorState_t GPIO_configureOutputConnection(const str_pinConfig_t* str_a_pin);
static void (* ptr_callbackFunction)();
/************************** FUNCTIONS DEFINITION ************************/

/*******************************************************************************/
/* Function: GPIO_init    @written by: Mahmoud Sharf-Eldin                     */
/* I/P Parameters: str_pinConfig_t pointer  								   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function initialize a GPIO                                */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_init(const str_pinConfig_t* str_a_pin){
	enu_gpioErrorState_t enu_a_ret = GPIO_OK;
	if(str_a_pin == NULL){
		enu_a_ret = GPIO_NOK;
	}
	else{
		//configure in normal mode state
		if(str_a_pin->port_index >= MIN_PORT_INDEX && str_a_pin->port_index <= MAX_PORT_INDEX)
		{
			if(str_a_pin->pin_index >= MIN_PIN_INDEX && str_a_pin->pin_index <= MAX_PIN_INDEX)
			{
				SET_BIT(SYSCTL_RCGCGPIO_R,str_a_pin->port_index);
				enu_a_ret|= GPIO_setPinDirection(str_a_pin,str_a_pin->pin_direction);
				CLEAR_BIT(GPIO_PORT_AFSEL(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
				if(str_a_pin->pin_MADrive == GPIO_TWO_MA_DRIVE)
				{
					SET_BIT(GPIO_PORT_DR2R(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
				}
				else if(str_a_pin->pin_MADrive == GPIO_FOUR_MA_DRIVE)
				{
					SET_BIT(GPIO_PORT_DR4R(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
				}
				else if(str_a_pin->pin_MADrive == GPIO_EIGHT_MA_DRIVE)
				{
					SET_BIT(GPIO_PORT_DR8R(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
				}
				else
				{
					enu_a_ret = GPIO_INVALID_DATA;
				}
				SET_BIT(GPIO_PORT_DEN(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
				
				if(str_a_pin->enable_interrupt == GPIO_ENABLE_INTERRUPT)
				{
					
					CLEAR_BIT(GPIO_PORT_IM(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
					if(str_a_pin->interrupt_trigger == GPIO_FALLING_EDGE_TRIGGER)
					{
						CLEAR_BIT(GPIO_PORT_IS(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
						CLEAR_BIT(GPIO_PORT_IBE(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
						CLEAR_BIT(GPIO_PORT_IEV(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
					}
					else if(str_a_pin->interrupt_trigger == GPIO_RAISING_EDGE_TRIGGER)
					{
						CLEAR_BIT(GPIO_PORT_IS(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
						CLEAR_BIT(GPIO_PORT_IBE(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
						SET_BIT(GPIO_PORT_IEV(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
					}
					else if(str_a_pin->interrupt_trigger == GPIO_LOW_LEVEL_TRIGGER)
					{
						SET_BIT(GPIO_PORT_IS(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
						CLEAR_BIT(GPIO_PORT_IBE(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
						CLEAR_BIT(GPIO_PORT_IEV(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
					}
					else if(str_a_pin->interrupt_trigger == GPIO_HIGH_LEVEL_TRIGGER)
					{
						SET_BIT(GPIO_PORT_IS(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
						CLEAR_BIT(GPIO_PORT_IBE(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
						SET_BIT(GPIO_PORT_IEV(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
					}
					else
					{
						enu_a_ret = GPIO_INVALID_DATA;
					}
					ptr_callbackFunction = str_a_pin->gpioInterruptHandler;
					CLEAR_BIT(GPIO_PORT_RIS(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
					SET_BIT(GPIO_PORT_IM(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
					NVIC_SetPriority(GPIO_IRQ(str_a_pin->port_index), str_a_pin->interrupt_priority);
					NVIC_EnableIRQ(GPIO_IRQ(str_a_pin->port_index));
					__enable_irq();
				}
				else if(str_a_pin->enable_interrupt == GPIO_DISABLE_INTERRUPT)
				{
					// TEMPRARY CONFIGURE INTERRUPTS FOR PORTF
					NVIC_DisableIRQ(GPIO_IRQ(str_a_pin->port_index));
					CLEAR_BIT(GPIO_PORT_IM(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
				}
				else
				{
					enu_a_ret = GPIO_INVALID_DATA;
				}
				
				
			}
			else
			{
				enu_a_ret = GPIO_INVALID_DATA;
			}
		}
		else
		{
			enu_a_ret = GPIO_INVALID_DATA;
		}
	}
	return enu_a_ret;
}
/*******************************************************************************/
/* Function: GPIO_setPinDirection    @written by: Mahmoud Sharf-Eldin          */
/* I/P Parameters: str_pinConfig_t pointer & enu_pinDirection_t  			   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function configure a GPIO pin as output or input          */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_setPinDirection(const str_pinConfig_t* str_a_pin,enu_pinDirection_t direction)
{
	enu_gpioErrorState_t enu_a_ret = GPIO_OK;
	if(str_a_pin == NULL){
		enu_a_ret = GPIO_NOK;
	}
	else{
		if(str_a_pin->port_index >= MIN_PORT_INDEX && str_a_pin->port_index <= MAX_PORT_INDEX)
		{
			if(str_a_pin->pin_index >= MIN_PIN_INDEX && str_a_pin->pin_index <= MAX_PIN_INDEX)
			{
				if(str_a_pin->pin_direction == GPIO_DIRECTION_INPUT)
				{
					CLEAR_BIT(GPIO_PORT_DIR(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
					enu_a_ret|= GPIO_configureOutputConnection(str_a_pin);
				}
				else if(str_a_pin->pin_direction == GPIO_DIRECTION_OUTPUT)
				{
					SET_BIT(GPIO_PORT_DIR(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
				}
				else
				{
					enu_a_ret = GPIO_INVALID_DATA;
				}
			
			}
			else
			{
				enu_a_ret = GPIO_INVALID_DATA;
			}
		}
		else
		{
			enu_a_ret = GPIO_INVALID_DATA;
		}
	}
	return enu_a_ret;
}
/*******************************************************************************/
/* Function: GPIO_outputHigh    @written by: Mahmoud Sharf-Eldin               */
/* I/P Parameters: str_pinConfig_t pointer  								   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function output high on  a GPIO pin                       */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_outputHigh(const str_pinConfig_t* str_a_pin){
	enu_gpioErrorState_t enu_a_ret = GPIO_OK;
	if(str_a_pin == NULL){
		enu_a_ret = GPIO_NOK;
	}
	else{
		SET_BIT(GPIO_PORT_DATA(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
	}
	return enu_a_ret;
}
/*******************************************************************************/
/* Function: GPIO_outputLow    @written by: Mahmoud Sharf-Eldin                */
/* I/P Parameters: str_pinConfig_t pointer  								   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function output low on  a GPIO pin                        */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_outputLow(const str_pinConfig_t* str_a_pin){
	enu_gpioErrorState_t enu_a_ret = GPIO_OK;
	if(str_a_pin == NULL){
		enu_a_ret = GPIO_NOK;
	}
	else{
		CLEAR_BIT(GPIO_PORT_DATA(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
	}
	return enu_a_ret;
}
/*******************************************************************************/
/* Function: GPIO_setPinStatus    @written by: Mahmoud Sharf-Eldin             */
/* I/P Parameters: str_pinConfig_t pointer & enu_bitLogic_t      			   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function set a GPIO pin status to enu_a_status argument   */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_setPinStatus(str_pinConfig_t* str_a_pin,enu_bitLogic_t enu_a_status)
{
	enu_gpioErrorState_t enu_a_ret = GPIO_OK;
	if(str_a_pin == NULL){
		enu_a_ret = GPIO_NOK;
	}
	else{
		//configure in normal mode state
		if(str_a_pin->port_index >= MIN_PORT_INDEX && str_a_pin->port_index <= MAX_PORT_INDEX)
		{
			if(str_a_pin->pin_index >= MIN_PIN_INDEX && str_a_pin->pin_index <= MAX_PIN_INDEX)
			{
				if(enu_a_status == GPIO_HIGH)
				{
					GPIO_outputHigh(str_a_pin);
					str_a_pin->pin_state = GPIO_HIGH;
				}
				else if(enu_a_status == GPIO_LOW)
				{
					GPIO_outputLow(str_a_pin);
					str_a_pin->pin_state = GPIO_LOW;
				}
				else
				{
					enu_a_ret = GPIO_INVALID_DATA;
				}
			}
			else
			{
				enu_a_ret = GPIO_INVALID_DATA;
			}
		}
		else
		{
			enu_a_ret = GPIO_INVALID_DATA;
		}
	}
	return enu_a_ret;
}
/*******************************************************************************/
/* Function: GPIO_configureOutputConnection    @written by: Mahmoud Sharf-Eldin*/
/* I/P Parameters: str_pinConfig_t pointer                           		   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function configure tje connection of output GPIO pin      */
/*******************************************************************************/
static enu_gpioErrorState_t GPIO_configureOutputConnection(const str_pinConfig_t* str_a_pin)
{
	enu_gpioErrorState_t enu_a_ret = GPIO_OK;
	if(str_a_pin == NULL){
		enu_a_ret = GPIO_NOK;
	}
	else{
		//configure in normal mode state
		if(str_a_pin->port_index >= MIN_PORT_INDEX && str_a_pin->port_index <= MAX_PORT_INDEX)
		{
			if(str_a_pin->pin_index >= MIN_PIN_INDEX && str_a_pin->pin_index <= MAX_PIN_INDEX)
			{
				if(str_a_pin->pin_connection == GPIO_PULL_UP)
				{
					SET_BIT(GPIO_PORT_PUR(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
				}
				else if(str_a_pin->pin_connection == GPIO_PULL_DOWN)
				{
					SET_BIT(GPIO_PORT_PDR(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
				}
				else{
					enu_a_ret = GPIO_INVALID_DATA;
				}
			}
			else
			{
				enu_a_ret = GPIO_INVALID_DATA;
			}
		}
		else
		{
			enu_a_ret = GPIO_INVALID_DATA;
		}
	}
	return enu_a_ret;
}
/*******************************************************************************/
/* Function: GPIO_togglePinStatus    @written by: Mahmoud Sharf-Eldin          */
/* I/P Parameters: str_pinConfig_t pointer  								   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function toggle status of a GPIO pin                      */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_togglePinStatus(str_pinConfig_t* str_a_pin)
{
	enu_gpioErrorState_t enu_a_ret = GPIO_OK;
	if(str_a_pin == NULL){
		enu_a_ret = GPIO_NOK;
	}
	else{
		//configure in normal mode state
		if(str_a_pin->port_index >= MIN_PORT_INDEX && str_a_pin->port_index <= MAX_PORT_INDEX)
		{
			if(str_a_pin->pin_index >= MIN_PIN_INDEX && str_a_pin->pin_index <= MAX_PIN_INDEX)
			{
				if(str_a_pin->pin_state == GPIO_HIGH)
				{
					GPIO_outputLow(str_a_pin);
					str_a_pin->pin_state = GPIO_LOW;
				}
				else if(str_a_pin->pin_state == GPIO_LOW)
				{
					GPIO_outputHigh(str_a_pin);
				}
				else
				{
					enu_a_ret = GPIO_INVALID_DATA;
				}
			}
			else
			{
				enu_a_ret = GPIO_INVALID_DATA;
			}
		}
		else
		{
			enu_a_ret = GPIO_INVALID_DATA;
		}
	}
	return enu_a_ret;
}
/*******************************************************************************/
/* Function: GPIO_getPinStatus    @written by: Mahmoud Sharf-Eldin             */
/* I/P Parameters: str_pinConfig_t pointer & enu_bitLogic_t pointer  		   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function get a GPIO pin status                            */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_getPinStatus(const str_pinConfig_t* str_a_pin,enu_bitLogic_t* enu_a_status)
{
	enu_gpioErrorState_t enu_a_ret = GPIO_OK;
	if(str_a_pin == NULL || enu_a_status == NULL){
		enu_a_ret = GPIO_NOK;
	}
	else{
		//configure in normal mode state
		if(str_a_pin->port_index >= MIN_PORT_INDEX && str_a_pin->port_index <= MAX_PORT_INDEX)
		{
			if(str_a_pin->pin_index >= MIN_PIN_INDEX && str_a_pin->pin_index <= MAX_PIN_INDEX)
			{
				*enu_a_status = GET_BIT(GPIO_PORT_DATA(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
			}
			else
			{
				enu_a_ret = GPIO_INVALID_DATA;
			}
		}
		else
		{
			enu_a_ret = GPIO_INVALID_DATA;
		}
	}
	return enu_a_ret;
}
/*******************************************************************************/
/* Function: GPIO_enableInterrupt    @written by: Mahmoud Sharf-Eldin          */
/* I/P Parameters: str_pinConfig_t pointer  								   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function enable interrupt  on  a GPIO pin                 */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_enableInterrupt(const str_pinConfig_t* str_a_pin)
{
	enu_gpioErrorState_t enu_a_ret = GPIO_OK;
	if(str_a_pin == NULL){
		enu_a_ret = GPIO_NOK;
	}
	else{
		//configure in normal mode state
		if(str_a_pin->port_index >= MIN_PORT_INDEX && str_a_pin->port_index <= MAX_PORT_INDEX)
		{
			if(str_a_pin->pin_index >= MIN_PIN_INDEX && str_a_pin->pin_index <= MAX_PIN_INDEX)
			{
				if(str_a_pin->enable_interrupt == GPIO_ENABLE_INTERRUPT)
				{
					CLEAR_BIT(GPIO_PORT_IM(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
					if(str_a_pin->interrupt_trigger == GPIO_FALLING_EDGE_TRIGGER)
					{
						CLEAR_BIT(GPIO_PORT_IS(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
						CLEAR_BIT(GPIO_PORT_IBE(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
						CLEAR_BIT(GPIO_PORT_IEV(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
					}
					else if(str_a_pin->interrupt_trigger == GPIO_RAISING_EDGE_TRIGGER)
					{
						CLEAR_BIT(GPIO_PORT_IS(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
						CLEAR_BIT(GPIO_PORT_IBE(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
						SET_BIT(GPIO_PORT_IEV(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
					}
					else if(str_a_pin->interrupt_trigger == GPIO_LOW_LEVEL_TRIGGER)
					{
						SET_BIT(GPIO_PORT_IS(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
						CLEAR_BIT(GPIO_PORT_IBE(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
						CLEAR_BIT(GPIO_PORT_IEV(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
					}
					else if(str_a_pin->interrupt_trigger == GPIO_HIGH_LEVEL_TRIGGER)
					{
						SET_BIT(GPIO_PORT_IS(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
						CLEAR_BIT(GPIO_PORT_IBE(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
						SET_BIT(GPIO_PORT_IEV(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
					}
					else
					{
						enu_a_ret = GPIO_INVALID_DATA;
					}
					ptr_callbackFunction = str_a_pin->gpioInterruptHandler;
					CLEAR_BIT(GPIO_PORT_RIS(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
					SET_BIT(GPIO_PORT_IM(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
					NVIC_SetPriority(GPIO_IRQ(str_a_pin->port_index), str_a_pin->interrupt_priority);
					NVIC_EnableIRQ(GPIO_IRQ(str_a_pin->port_index));
					__enable_irq();
				}
				else
				{
					enu_a_ret = GPIO_INVALID_DATA;
				}
			}
			else
			{
				enu_a_ret = GPIO_INVALID_DATA;
			}
		}
		else
		{
			enu_a_ret = GPIO_INVALID_DATA;
		}
	}
	return enu_a_ret;
}
/*******************************************************************************/
/* Function: GPIO_disableInterrupt    @written by: Mahmoud Sharf-Eldin         */
/* I/P Parameters: str_pinConfig_t pointer  								   */
/* Returns: enu_gpioErrorState_t         				                       */
/* Description: This Function disable interrupt  on  a GPIO pin                */
/*******************************************************************************/
enu_gpioErrorState_t GPIO_disableInterrupt(const str_pinConfig_t* str_a_pin)
{
	enu_gpioErrorState_t enu_a_ret = GPIO_OK;
	if(str_a_pin == NULL){
		enu_a_ret = GPIO_NOK;
	}
	else{
		//configure in normal mode state
		if(str_a_pin->port_index >= MIN_PORT_INDEX && str_a_pin->port_index <= MAX_PORT_INDEX)
		{
			if(str_a_pin->pin_index >= MIN_PIN_INDEX && str_a_pin->pin_index <= MAX_PIN_INDEX)
			{
				if(str_a_pin->enable_interrupt == GPIO_DISABLE_INTERRUPT)
				{
					NVIC_DisableIRQ(GPIO_IRQ(str_a_pin->port_index));
					CLEAR_BIT(GPIO_PORT_IM(PORT_OFFSET(str_a_pin->port_index)),str_a_pin->pin_index);
				}
				else
				{
					enu_a_ret = GPIO_INVALID_DATA;
				}
			}
			else
			{
				enu_a_ret = GPIO_INVALID_DATA;
			}
		}
		else
		{
			enu_a_ret = GPIO_INVALID_DATA;
		}
	}
	return enu_a_ret;
}
//WE JUST DEFINE THE NEEDED INTERRUPT HANDLER
void GPIOF_Handler(void)
{
	if(ptr_callbackFunction != NULL)
		ptr_callbackFunction();
	
}