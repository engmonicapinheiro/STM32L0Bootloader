/*
 * gpio.h
 *
 *  Created on: 25 Oct 2024
 *      Author: monicapinheiro
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "stm32l031xx.h"


void LedInit(void);
void ButtonInit(void);
void GreenLedOn(void);
void GreenLedOff(void);
void EmbeddedLedOn(void);
void EmbeddedLedOff(void);
void LedToggle(uint32_t dly);
_Bool GetButtonState(void);

#endif /* GPIO_H_ */
