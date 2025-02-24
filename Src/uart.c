/*
 * uart.h
 *
 *  Created on: 25 Oct 2024
 *      Author: monicapinheiro
 */

#include <stdint.h>
#include "uart.h"


#define DBG_UART_BAUDRATE  115200
#define SYS_FREQ           2000000
#define APB1_CLK 		   SYS_FREQ

static void UartWrite(int ch);

uint32_t SystemCoreClock = 2097000;


/* retargetting printf */
int __io_putchar(int ch)
{
	UartWrite(ch);
	return ch;
}

void UartInit(void)
{
	/* enable clock access to GPIOA */
	RCC->IOPENR |= RCC_IOPENR_IOPAEN;

	/* set the mode of PA2 to alternate function mode */
	GPIOA->MODER &= ~(1U << 4);
	GPIOA->MODER |= (1U << 5);

	/* set alternate function type to AF4 (USART2_TX) */
	   //for pin 2 (PA2), we need to configure as AF4 - 0100:
	GPIOA->AFR[0] &= ~(1U << 8);
	GPIOA->AFR[0] &= ~(1U << 9);
	GPIOA->AFR[0] |= (1U << 10);
	GPIOA->AFR[0] &= ~(1U << 11);

	/* enable clock access to UART2 */
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	/* configure the UART baudrate */
	USART2->BRR = (SystemCoreClock /2400);

	/* configure transfer direction */
	USART2->CR1 = USART_CR1_TE;

	/* enable the UART module */
	USART2->CR1 |= USART_CR1_UE;
}

static void UartWrite(int ch)
{
	/* make sure the transmit data register is empty */
	 //to read a bit in a register: &
	//if this operation returns 0, we get stuck here
	while(!(USART2->ISR & USART_ISR_TXE));

	/* write to the transmit data register */
	USART2->TDR = (ch & 0xFF);
}



