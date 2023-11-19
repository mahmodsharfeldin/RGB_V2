#include "../HAL/led/led.h"
#include "../HAL/button/button.h"
#include "../MCAL/systick/systick.h"
#define STATE_1    1
#define STATE_2    2
#define STATE_3    3
#define STATE_4    4
#define STATE_5    5
#define STATE_6    6


#define DEBOUNCING_THRESHOLD     100 
#define NUMBER_OF_STATES		 6

void app_init();
void app_run();