#include "STM32F10x.h"
#include <cmsis_os.h>
#include "STM32F10x_gpio.h"
#include "STM32F10x_rcc.h"
#include "stm32f10x_tim.h"

#include "keyboard.h"
#include "timers.h"

osTimerDef(ProgTimer1, osProgTimer1Callback);
osTimerDef(ProgTimer2, osProgTimer2Callback);	

void init_Clocks() {
		// Update SystemCoreClock value
		SystemCoreClockUpdate();
		// Configure the SysTick timer to overflow every 1 us
		SysTick_Config(SystemCoreClock / 1000000);
}

void init_timers() {	
		TIM2_Counter = 1;
		osProgTimer1 = osTimerCreate(osTimer(ProgTimer1), osTimerPeriodic, NULL);

		osProgTimer2 = osTimerCreate(osTimer(ProgTimer2), osTimerPeriodic, NULL);
}

int LED1_Frequency = 1; // Start frequence of first LED
int LED2_Frequency = 1; // Start frequence of second LED

void timer2_thread(void const *argument) // Start timer 2
{
		for(;;) {
			if (TIM1_Counter > 10 * LED1_Frequency) {
				TIM1_Counter = 0;
				GPIOA->ODR ^= GPIO_Pin_7;
			}
		}
}

void timer3_thread(void const *argument) // Start timer 3
{
		for(;;) {
			if (TIM2_Counter > 10 * LED1_Frequency) {
				TIM2_Counter = 0;
				GPIOA->ODR ^= GPIO_Pin_7;
			}
		}
}

void keyboard_thread(void const *argument) // keyboard handler
{
	for (;;) {
		uint8_t key = read_keyboard();
		if (key == 1) {
			if (LED1_Frequency > 1)
				continue;
			LED1_Frequency -= 1;
			
			osTimerStart(osProgTimer1, LED1_Frequency * 100);
		} else if (key == 4) {
			LED1_Frequency += 1;
			
			osTimerStart(osProgTimer1, LED1_Frequency * 100);
		}
		
		if (key == 3) {
			if (LED2_Frequency > 1)
				continue;
			LED2_Frequency -= 1;
			
			osTimerStart(osProgTimer2, LED2_Frequency * 100);
		} else if (key == 6) {
			LED2_Frequency += 1;
			
			osTimerStart(osProgTimer2, LED2_Frequency * 100);
		}
	}
}

osThreadId main_ID, led_ID1, led_ID2, keyboard_ID;
osThreadDef(timer2_thread, osPriorityNormal, 1, 0);
osThreadDef(timer3_thread, osPriorityNormal, 1, 0);
osThreadDef(keyboard_thread, osPriorityNormal, 1, 0);

void initPort(GPIO_InitTypeDef GPIO_Port, uint16_t Pin) {
    GPIO_Port.GPIO_Pin = Pin;
    GPIO_Port.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Port.GPIO_Speed = GPIO_Speed_50MHz;
}

int main(void) {
    // Initialize APB2 For ports A and B
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
		keyboard_init();
		init_Clocks();
		init_timers();		
	
		osTimerStart(osProgTimer1, 100);
		osTimerStart(osProgTimer2, 100);
	
		// Initialize outputs for LED
		GPIO_InitTypeDef GPIO_Port;
		initPort(GPIO_Port, GPIO_Pin_7);
    GPIO_Init(GPIOA, &GPIO_Port);
    GPIO_Init(GPIOB, &GPIO_Port);

    osKernelInitialize();
    led_ID2 = osThreadCreate(osThread(timer2_thread), NULL);
    led_ID1 = osThreadCreate(osThread(timer3_thread), NULL);
    keyboard_ID = osThreadCreate(osThread(keyboard_thread), NULL);
    osKernelStart();

    while (1) { }
}