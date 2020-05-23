//#include "timers.h"

//int TIM1_Counter = 1;
//int TIM2_Counter = 1;

//osTimerDef(ProgTimer1, osProgTimer1Callback);
//osTimerDef(ProgTimer2, osProgTimer2Callback);	

//void init_Clocks() {
//		// Update SystemCoreClock value
//		SystemCoreClockUpdate();
//		// Configure the SysTick timer to overflow every 1 us
//		SysTick_Config(SystemCoreClock / 1000000);
//}

//void init_timers() {	
//		TIM2_Counter = 1;
//		osProgTimer1 = osTimerCreate(osTimer(ProgTimer1), osTimerPeriodic, NULL);

//		osProgTimer2 = osTimerCreate(osTimer(ProgTimer2), osTimerPeriodic, NULL);
//}