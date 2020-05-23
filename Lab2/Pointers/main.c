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

	// Part using pointers (Uncomment)
	char chars[] = {'.','_',' ','_','.',' ','.','_',' ','_',' ','_','_','_',' ','.','_','.','.',' ','.','.',' ','.','.'};
	char katusha[] = {'_','.','_',' ','.','_',' ','_',' ','.',' ','.','_','.',' ','_','.','_','_',' ','_','.',' ','.','_'};
	int length = sizeof(katusha) / sizeof(char);

	int *GPIO_C_CRH = (int*)(0x40011004);
	int *GPIO_C_ODR = (int*)(0x4001100C);

	int *GPIO_B_CRH = (int*)(0x40010C04);
	int *GPIO_B_ODR = (int*)(0x40010C0C);

	int *GPIO_A_CRL = (int*)(0x40010800);
	int *GPIO_A_IDR = (int*)(0x40010808);
	int *GPIO_A_ODR = (int*)(0x4001080C);

	int *apb2enr = (int*)0x40021018;
	int i;
	int j = 0;

	*apb2enr |= 0x0001C;
	*GPIO_B_CRH = 0x00000003;

	*GPIO_C_CRH = 0x00100000;
	*GPIO_C_ODR = 0x00002000;

	*GPIO_A_CRL = 0x00000011;
	*GPIO_A_ODR = 0x00000002; // 0000 0000 0000 0000 0010

	// 1s = 6666666

	for(;;j++) {
		while (!(*GPIO_A_IDR & 0x1)) {
			*GPIO_C_ODR = 0x00000000;
			delay(100);
		}
		*GPIO_C_ODR = 0x00002000;
		char element = katusha[j % length];
		if(element == '.') {
			*GPIO_B_ODR=0x00000100;
			delay(150);
		} else if(element == '_') {
			*GPIO_B_ODR=0x00000100;
			delay(600);
		} else if(element == ' ') {
			*GPIO_B_ODR=0x0000000;
			delay(300);
		}
		*GPIO_B_ODR=0x0000000;
		delay(600);
		if(j % length == length - 1) delay(3000);
	}
}
