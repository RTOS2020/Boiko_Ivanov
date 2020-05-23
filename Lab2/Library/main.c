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

// Part using library
	char chars[] = {'.','_',' ','_','.',' ','.','_',' ','_',' ','_','_','_',' ','.','_','.','.',' ','.','.',' ','.','.'};
	char katusha[] = {'_','.','_',' ','.','_',' ','_',' ','.',' ','.','_','.',' ','_','.','_','_',' ','_','.',' ','.','_'};
	int length = sizeof(katusha) / sizeof(char);

	int i;
	int j = 0;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);


	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	GPIO_SetBits(GPIOA, GPIO_Pin_1);

	GPIO_ResetBits(GPIOB, GPIO_Pin_0);

	// 1s = 6666666 we have one seconds as aproximatly 6.666.666 ticks

	for(;;j++) {
		while (!(GPIO_ReadInputData(GPIOA) & 0x1)) { // Check if A0 has any output
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			delay(100); // delay 100ms
		}
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		char element = katusha[j % length];
		if(element == '.') {
			GPIO_SetBits(GPIOB, GPIO_Pin_8);
			delay(150);
		} else if(element == '_') {
			GPIO_SetBits(GPIOB, GPIO_Pin_8);
			delay(600);
		} else if(element == ' ') {
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			delay(300);
		}
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		delay(600);
		if(j % length == length - 1) delay(3000); // If this symbol is last in word make delay for 3s
	}
}
