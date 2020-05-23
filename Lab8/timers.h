#include "stm32f10x_tim.h"
#include <cmsis_os.h>

#ifndef counters
#define counters
int TIM1_Counter = 1; // Additional variable for counting timer 	
int TIM2_Counter = 1;
#endif

osTimerId osProgTimer1, osProgTimer2;

static void osProgTimer1Callback(void const *argument)
{
		TIM2_Counter++;
}

static void osProgTimer2Callback(void const *argument)
{
		TIM1_Counter++;
}

void init_timers(void);
void init_Clocks(void);