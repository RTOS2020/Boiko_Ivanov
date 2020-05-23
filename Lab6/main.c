#include "STM32F10x.h"
#include <cmsis_os.h>
#include "STM32F10x_gpio.h"
#include "STM32F10x_rcc.h"
#include "delay.h"

void led_thread1(void const *argument) // Flash LED 1
{
    for (;;) {
        GPIO_SetBits(GPIOA, GPIO_Pin_2);
        delay(1000);
        GPIO_ResetBits(GPIOA, GPIO_Pin_2);
        delay(1000);
    }
}

void led_thread2(void const *argument) // Flash LED 2

{
    for (;;) {
        GPIO_SetBits(GPIOA, (GPIO_Pin_1));
        delay(1000);
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
        delay(1000);
    }
}

osThreadId main_ID, led_ID1, led_ID2, led_ID3;
osThreadDef(led_thread2, osPriorityNormal, 1, 512);
osThreadDef(led_thread1, osPriorityNormal, 1, 512);

int main(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

		GPIO_InitTypeDef GPIO_A;
    GPIO_StructInit(&GPIO_A);
    GPIO_A.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_1;
    GPIO_A.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_A.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_A);
	
    osKernelInitialize();                   
    led_ID1 = osThreadCreate(osThread(led_thread1), NULL);
    led_ID2 = osThreadCreate(osThread(led_thread2), NULL);
    osKernelStart();                         
	
    while (1) { ; }
}