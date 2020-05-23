#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "STM32F10x.h"
#include "STM32F10x_gpio.h"
#include "STM32F10x_rcc.h"

#define A0_APB_FUNC			RCC_APB2PeriphClockCmd
#define A0_APB					RCC_APB2Periph_GPIOA
#define A0_PIN					GPIO_Pin_1
#define A0_PORT					GPIOA

#define A1_APB_FUNC			RCC_APB2PeriphClockCmd
#define A1_APB					RCC_APB2Periph_GPIOA
#define A1_PIN					GPIO_Pin_2
#define A1_PORT					GPIOA

#define A2_APB_FUNC			RCC_APB2PeriphClockCmd
#define A2_APB					RCC_APB2Periph_GPIOA
#define A2_PIN					GPIO_Pin_3
#define A2_PORT					GPIOA

#define A3_APB_FUNC			RCC_APB2PeriphClockCmd
#define A3_APB					RCC_APB2Periph_GPIOA
#define A3_PIN					GPIO_Pin_4
#define A3_PORT					GPIOA


#define B0_APB_FUNC			RCC_APB2PeriphClockCmd
#define B0_APB					RCC_APB2Periph_GPIOB
#define B0_PIN					GPIO_Pin_1
#define B0_PORT					GPIOB

#define B1_APB_FUNC			RCC_APB2PeriphClockCmd
#define B1_APB					RCC_APB2Periph_GPIOB
#define B1_PIN					GPIO_Pin_2
#define B1_PORT					GPIOB

#define B2_APB_FUNC			RCC_APB2PeriphClockCmd
#define B2_APB					RCC_APB2Periph_GPIOB
#define B2_PIN					GPIO_Pin_3
#define B2_PORT					GPIOB

#define B3_APB_FUNC			RCC_APB2PeriphClockCmd
#define B3_APB					RCC_APB2Periph_GPIOB
#define B3_PIN					GPIO_Pin_4
#define B3_PORT					GPIOB


#define A0_HIGH					GPIO_SetBits(A0_PORT, A0_PIN)
#define A0_LOW					GPIO_ResetBits(A0_PORT, A0_PIN)

#define A1_HIGH					GPIO_SetBits(A1_PORT, A1_PIN)
#define A1_LOW					GPIO_ResetBits(A1_PORT, A1_PIN)

#define A2_HIGH					GPIO_SetBits(A2_PORT, A2_PIN)
#define A2_LOW					GPIO_ResetBits(A2_PORT, A2_PIN)

#define A3_HIGH					GPIO_SetBits(A3_PORT, A3_PIN)
#define A3_LOW					GPIO_ResetBits(A3_PORT, A3_PIN)


#define B0_INPUT				GPIO_ReadInputDataBit(B0_PORT, B0_PIN)
#define B1_INPUT				GPIO_ReadInputDataBit(B1_PORT, B1_PIN)
#define B2_INPUT				GPIO_ReadInputDataBit(B2_PORT, B2_PIN)
#define B3_INPUT				GPIO_ReadInputDataBit(B3_PORT, B3_PIN)

#define KEY_SENSE	3

void keyboard_init(void);
uint8_t read_keyboard(void);
#endif
