#include "app.h"


static uint8_t uint8_gs_state =0;
static uint32_t uint32_gs_counter =0;
static str_led_t str_gs_blueLed;
static str_led_t str_gs_greenLed;
static str_led_t str_gs_redLed;
static str_button_t str_gs_button;
static str_systick_t str_gs_sys;

void preesed_button()
{
	uint32_gs_counter++;
}
void systick_call_back()
{
	LED_off(&str_gs_blueLed);
	LED_off(&str_gs_redLed);
	LED_off(&str_gs_greenLed);
	SYSTICK_stop();
}

void app_init()
{
	
	str_gs_blueLed.port   =	LED_PORTF;
	str_gs_blueLed.pin    = LED_PIN2;
	str_gs_blueLed.state  = LED_OFF;

	str_gs_redLed.port  = LED_PORTF;
	str_gs_redLed.pin   = LED_PIN1;
	str_gs_redLed.state = LED_OFF;

	str_gs_greenLed.port  = LED_PORTF;
	str_gs_greenLed.pin   = LED_PIN3;
	str_gs_greenLed.state = LED_OFF;
	
	str_gs_button.port = BUTTON_PORTF;
	str_gs_button.pin   = BUTTON_PIN4;
	str_gs_button.connection = BUTTON_PULL_UP;
	str_gs_button.enable_interrupt = BUTTON_ENABLE_INTERRUPT;
	str_gs_button.interrupt_trigger = BUTTON_LOW_LEVEL_TRIGGER;
	str_gs_button.btnInterruptHandler = preesed_button;
	str_gs_button.interrupt_priority = BUTTON_INT_PRIORITY_0;
	
	LED_init(&str_gs_blueLed);
	LED_init(&str_gs_redLed);
	LED_init(&str_gs_greenLed);
	LED_off(&str_gs_blueLed);
	LED_off(&str_gs_redLed);
	LED_off(&str_gs_greenLed);
	BUTTON_init(&str_gs_button);
	
	str_gs_sys.period_ms = 1000;
	str_gs_sys.interrupt_enable = SYSTICK_ENABLE_INTERRUPT;
	str_gs_sys.clock_source = SYSTICK_INTERNAL_OSCILLATOR;
	str_gs_sys.SysTickHandler =systick_call_back;
	
	SYSTICK_init(&str_gs_sys);
}
void app_run()
{
	if(uint32_gs_counter >= DEBOUNCING_THRESHOLD)
	{
		uint8_gs_state = (uint8_gs_state+1)% NUMBER_OF_STATES;
		uint32_gs_counter=0;
		SYSTICK_reloadValue(&str_gs_sys,str_gs_sys.period_ms);
	}
	
	switch(uint8_gs_state)
	{
		case STATE_1 :
			LED_on(&str_gs_redLed);
			SYSTICK_start();
			while(uint32_gs_counter < DEBOUNCING_THRESHOLD);
			break;
		case STATE_2 :
			LED_on(&str_gs_greenLed);
			SYSTICK_start();
			while(uint32_gs_counter < DEBOUNCING_THRESHOLD);
			break;
		case STATE_3 :
			LED_on(&str_gs_blueLed);
			SYSTICK_start();
			while( uint32_gs_counter < DEBOUNCING_THRESHOLD);
			break;
		case STATE_4 :
			LED_on(&str_gs_redLed);
			LED_on(&str_gs_greenLed);
			LED_on(&str_gs_blueLed);
			SYSTICK_start();
			while(uint32_gs_counter < DEBOUNCING_THRESHOLD);
			break;
		case STATE_5 :
			LED_off(&str_gs_redLed);
			LED_off(&str_gs_greenLed);
			LED_off(&str_gs_blueLed);
			SYSTICK_start();
			while(uint32_gs_counter < DEBOUNCING_THRESHOLD);
			break;
		case STATE_6 : 
			SYSTICK_start();
			while( uint32_gs_counter < DEBOUNCING_THRESHOLD);
			break;
		default : break;
			
	}
}