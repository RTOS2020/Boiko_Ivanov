#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void delay(int ms) {
	for(int i = 0; i < 6666 * ms; i++) { }
}

int main(void){ 
	// Listen port A0, if we have any input on it, then B8 is active and gives us output. Else we have C13 lamp active
	// When we have B8 active, then our lamp will get sygnals to work as morze for word 'Katerina'
	
	// Also we always have A1 as active output
	
//	// Part using pointers (Uncomment)
//	char chars[] = {'.','_',' ','_','.',' ','.','_',' ','_',' ','_','_','_',' ','.','_','.','.',' ','.','.',' ','.','.'};
//	char katusha[] = {'_','.','_',' ','.','_',' ','_',' ','.',' ','.','_','.',' ','_','.','_','_',' ','_','.',' ','.','_'};
//	int length = sizeof(katusha) / sizeof(char);
//		
//	int *GPIO_C_CRH = (int*)(0x40011004);
//	int *GPIO_C_ODR = (int*)(0x4001100C);
//		
//	int *GPIO_B_CRH = (int*)(0x40010C04);
//	int *GPIO_B_ODR = (int*)(0x40010C0C);
//		
//	int *GPIO_A_CRL = (int*)(0x40010800);
//	int *GPIO_A_IDR = (int*)(0x40010808);
//	int *GPIO_A_ODR = (int*)(0x4001080C);
//		
//	int *apb2enr = (int*)0x40021018;
//	int i;
//	int j = 0;

//	*apb2enr |= 0x0001C;
//	*GPIO_B_CRH = 0x00000003;
//		
//	*GPIO_C_CRH = 0x00100000;
//	*GPIO_C_ODR = 0x00002000;
//		
//	*GPIO_A_CRL = 0x00000011;
//	*GPIO_A_ODR = 0x00000002; // 0000 0000 0000 0000 0010
//	
//	// 1s = 6666666
//	
//	for(;;j++) {
//		while (!(*GPIO_A_IDR & 0x1)) {
//			*GPIO_C_ODR = 0x00000000;
//			delay(100);
//		}
//		*GPIO_C_ODR = 0x00002000;
//		char element = katusha[j % length];
//		if(element == '.') {
//			*GPIO_B_ODR=0x00000100;
//			delay(150);
//		} else if(element == '_') {
//			*GPIO_B_ODR=0x00000100;
//			delay(600);
//		} else if(element == ' ') {
//			*GPIO_B_ODR=0x0000000;
//			delay(300);
//		}
//		*GPIO_B_ODR=0x0000000;
//		delay(600);
//		if(j % length == length - 1) delay(3000);
//	}




//	// Part using structures
	char chars[] = {'.','_',' ','_','.',' ','.','_',' ','_',' ','_','_','_',' ','.','_','.','.',' ','.','.',' ','.','.'};
	char katusha[] = {'_','.','_',' ','.','_',' ','_',' ','.',' ','.','_','.',' ','_','.','_','_',' ','_','.',' ','.','_'};
	int length = sizeof(katusha) / sizeof(char);
		
	int i;
	int j = 0;

	RCC->APB2ENR |= 0x1C; // start A, B, C
	GPIOB->CRH = 0x3; // open port B8
		
	GPIOC->CRH = 0x100000; // open port C13 
	GPIOC->ODR = 0x2000; // Turn lamp off C13
		
	GPIOA->CRL = 0x11; // Open A1, A0
	GPIOA->ODR = 0x2; // Turn on A1 as output
	
	// 1s = 6666666 we have one seconds as aproximatly 6.666.666 ticks
	
	for(;;j++) {
		while (!(GPIOA->IDR & 0x1)) { // Check if A0 has any output
			GPIOC->ODR = 0x00000000; // If no, turn C13 on
			delay(100); // delay 100ms
		}
		GPIOC->ODR = 0x00002000; // If no, turn C13 off // 0010 0000 0000 0000
		char element = katusha[j % length];
		if(element == '.') {
			GPIOB->ODR=0x00000100; // Turn B8 on as output
			delay(150);
		} else if(element == '_') {
			GPIOB->ODR=0x00000100; // Turn B8 on as output
			delay(600);
		} else if(element == ' ') {
			GPIOB->ODR=0x00000100; // Turn B8 off
			delay(300);
		}
		GPIOB->ODR=0x0000000; // Turn B8 off
		delay(600);
		if(j % length == length - 1) delay(3000); // If this symbol is last in word make delay for 3s
	}



// Part using library
//	char chars[] = {'.','_',' ','_','.',' ','.','_',' ','_',' ','_','_','_',' ','.','_','.','.',' ','.','.',' ','.','.'};
//	char katusha[] = {'_','.','_',' ','.','_',' ','_',' ','.',' ','.','_','.',' ','_','.','_','_',' ','_','.',' ','.','_'};
//	int length = sizeof(katusha) / sizeof(char);
//		
//	int i;
//	int j = 0;

//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
//		
//		
//	GPIO_InitTypeDef GPIO_InitStructure;
//		
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//		
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
//		
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//		
//	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
//	GPIO_SetBits(GPIOA, GPIO_Pin_1);
//		
//	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
//	
//	// 1s = 6666666 we have one seconds as aproximatly 6.666.666 ticks
//	
//	for(;;j++) {
//		while (!(GPIO_ReadInputData(GPIOA) & 0x1)) { // Check if A0 has any output
//			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
//			delay(100); // delay 100ms
//		}
//		GPIO_SetBits(GPIOC, GPIO_Pin_13);
//		char element = katusha[j % length];
//		if(element == '.') {
//			GPIO_SetBits(GPIOB, GPIO_Pin_8);
//			delay(150);
//		} else if(element == '_') {
//			GPIO_SetBits(GPIOB, GPIO_Pin_8);
//			delay(600);
//		} else if(element == ' ') {
//			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
//			delay(300);
//		}
//		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
//		delay(600);
//		if(j % length == length - 1) delay(3000); // If this symbol is last in word make delay for 3s
//	}
}
