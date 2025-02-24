#include "timebase.h"
#include "stm32l031xx.h"

#define ONE_SEC_LOAD  1500000
#define ONE_MILLISECOND_LOAD 1500

#define TICK_FREQ	  1
#define MAX_DELAY 	  0xFFFFFFFF


volatile uint32_t currentTick;
volatile uint32_t currentTickp;

/* delay in seconds */
void delay(uint32_t delay)
{
	uint32_t tickstart = GetTick();
	uint32_t wait = delay;

	if(wait < MAX_DELAY)
	{
		wait += (uint32_t)TICK_FREQ;
	}

	while((GetTick() - tickstart) < wait);

}


uint32_t GetTick(void)
{
	__disable_irq();
	currentTickp = currentTick;
	__enable_irq();

	return currentTickp;
}

static void TickIncrement(void)
{
	currentTick += TICK_FREQ;
}

void TimebaseInit(void)
{
	/* disable global interrupt */
	__disable_irq();

	/* load the timer with number of clock cycles per second */
	SysTick->LOAD = ONE_SEC_LOAD - 1;

	/* clear the systick current value register */
	SysTick->VAL = 0;

	/* select the internal clock source */
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;

	/* enable interrupt */
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

	/* enable systick */
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	/* enable global interrupt */
	__enable_irq();
}

void SysTick_Handler(void)
{
	TickIncrement();
}

