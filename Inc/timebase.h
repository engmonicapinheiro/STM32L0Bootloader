/*
 * timebase.h
 *
 *  Created on: 2 Nov 2024
 *      Author: monicapinheiro
 */

#ifndef TIMEBASE_H_
#define TIMEBASE_H_

#include <stdint.h>

void TimebaseInit(void);
uint32_t GetTick(void);
void delay(uint32_t delay);


#endif /* TIMEBASE_H_ */
