#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

//http://www.minokasago.org/STM32wiki/index.php?NVIC_IRQChannel

void TIM1_UP_IRQHandler()// Not worked
{
	
	if (TIM_GetITStatus(TIM1, TIM_IT_Update))
	{
		GPIOA->BSRR = GPIO_Pin_4;//A4 red
		// Clears the TIM2 interrupt pending bit
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}
void TIM2_IRQHandler()
{
    GPIOA->ODR ^= GPIO_Pin_6;
    // Clears the TIM2 interrupt pending bit
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	
}
void TIM3_IRQHandler()
{
	
	GPIOA->ODR ^= GPIO_Pin_7;
    // Clears the TIM2 interrupt pending bit
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	
}
void TIM4_IRQHandler()
{
	// Checks whether the TIM2 interrupt has occurred or not
	if (TIM_GetITStatus(TIM4, TIM_IT_Update))
	{
	    GPIOA->ODR ^= GPIO_Pin_5;
         // Clears the TIM2 interrupt pending bit
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}

void GPIO_Init_(void);


int main(void)
{
	// Update SystemCoreClock value
	SystemCoreClockUpdate();
	// Configure the SysTick timer to overflow every 1 us
	SysTick_Config(SystemCoreClock / 1000000);
	
	
	
	// Init struct
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	// Enable clock for TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// TIM2 initialization for overflow every 500ms
	// Update Event (Hz) = timer_clock / ((TIM_Prescaler + 1) * (TIM_Period + 1))
	// Update Event (Hz) = 72MHz / ((2399 + 1) * (9999 + 1)) = 3Hz (0.33s)
	TIM_TimeBaseInitStruct.TIM_Prescaler = 2399;
	TIM_TimeBaseInitStruct.TIM_Period = 9999;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
//    #define TIM_CKD_DIV1                       ((uint16_t)0x0000)
//    #define TIM_CKD_DIV2                       ((uint16_t)0x0100)
//    #define TIM_CKD_DIV4                       ((uint16_t)0x0200)
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	// Enable TIM2 interrupt
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	// Start TIM2
	TIM_Cmd(TIM2, ENABLE);
	
	// Nested vectored interrupt settings
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	
  
	GPIO_InitTypeDef GPIO_InitStruct;
	
  // Initialize PB12 as push-pull output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// Initialize PC13 as push-pull output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);    
	
	while (1)
	{
		GPIOC->ODR ^= GPIO_Pin_13;
		for(int i = 0; i < 1000000; i++) { }
		
		
		//// Blink LED on PC13 for all sys testing 
		//GPIOC->BRR = GPIO_Pin_13;
		//DelayMs(2500);
		//GPIOC->BSRR = GPIO_Pin_13;
		//DelayMs(2500);
	}
}


void GPIO_Init_(void)
{
   GPIO_InitTypeDef GPIO_InitStruct;
	
  // Initialize PB12 as push-pull output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// Initialize PC13 as push-pull output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);    
    
}
