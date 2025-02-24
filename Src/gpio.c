/*
 * gpio.c
 *
 *  Created on: 25 Oct 2024
 *      Author: monicapinheiro
 */

#include "gpio.h"
#include "timebase.h"
#include <stdint.h>
#include <stdbool.h>

void LedInit(void)
{
	/* enable clock access to GPIOA */
	RCC->IOPENR |= RCC_IOPENR_IOPAEN;
	/* enable clock access to GPIOB*/
	RCC->IOPENR |= RCC_IOPENR_IOPBEN;

	/* set PA8 mode to output mode (the green external led) */
	GPIOA->MODER |= GPIO_MODER_MODE8_0;  //bit 16
	GPIOA->MODER &= ~ GPIO_MODER_MODE8_1; //bit 17

	/* set PB3 mode to output (the embedded led) */
	GPIOB->MODER |= GPIO_MODER_MODE3_0;  //6;
	GPIOB->MODER &= ~GPIO_MODER_MODE3_1;   //7;

}

void ButtonInit(void)
{
	/* enable clock access to PORTB - done in LedInit*/
	/* set PB4 as an input pin */
	GPIOB->MODER &= ~GPIO_MODER_MODE4_0;  //bit 8
	GPIOB->MODER &= ~GPIO_MODER_MODE4_1;  //bit 9
}

void LedToggle(uint32_t dly)
{
	GPIOA->ODR ^= GPIO_ODR_OD8;
	delay(dly);
}

void GreenLedOn(void)
{
	/* set PA8 high */
	GPIOA->ODR |= GPIO_ODR_OD8;
}

void GreenLedOff(void)
{
	/* set PA8 low */
	GPIOA->ODR &= ~GPIO_ODR_OD8;
}

void EmbeddedLedOn(void)
{
	/* set PB3 high */
	GPIOB->ODR |= GPIO_ODR_OD3;
}

void EmbeddedLedOff(void)
{
	/* set PB3 low */
	GPIOB->ODR &= ~GPIO_ODR_OD3;
}

_Bool GetButtonState(void)
{
	/* check if the button is pressed.
	 * the button is active low, meaning it is
	 * normally 1. When pressed, it becomes 0. */
	if(GPIOB->IDR & GPIO_IDR_ID4)
	{
		return false;
	}
	else
	{
		return true;
	}
}

