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
}
