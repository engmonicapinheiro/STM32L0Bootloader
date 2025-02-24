#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stm32l031xx.h"
#include "gpio.h"
#include "uart.h"
#include "timebase.h"

#define CUSTOM_FUNCTION  __attribute__((section (".custom_section")))
#define RAM_FUNCTION  __attribute__((section (".RamFunc")))


/* Modules developed:
 * PFU - STM32L0 doesn't have this pheripheral
 * UART
 * GPIO
 * TIMEBASE
 */

_Bool buttonState;

//from GNU:
unsigned char __attribute__((section (".custom_ram_block"))) customRamBuffer[20];
unsigned char __attribute__((section (".custom_flash_block"))) customFlashBuffer[10];

void RAM_FUNCTION _led_toggle(uint32_t dly);
//void CUSTOM_FUNCTION _led_toggle2(uint32_t dly);

/* the bootloader contants */
#define APPLICATION_ADDRESS 	0x08000080
#define EMPTY_MEMORY			0x00000000

#define MEM_CHECKK_V2

typedef void (*func_ptr)(void);

void jump_to_default_app(void)
{
	uint32_t app_start_address;
	func_ptr jump_to_app;

	printf("Bootloader started.....\n\r");
	//delay(300);

	if((*(uint32_t *)APPLICATION_ADDRESS) != EMPTY_MEMORY)
	{
		//delay(3);
		printf("Starting application...\n\r");
		delay(10);
		app_start_address = *(uint32_t *)(APPLICATION_ADDRESS + 4);
		jump_to_app = (func_ptr) app_start_address;

		/*initialise the main stack pointer */
		__set_MSP(*(uint32_t *)APPLICATION_ADDRESS);

		/* jump */
		jump_to_app();
	}
	else
	{
		printf("No application found at location. \n\r");
	}
}

#if 0
struct bootloaderCommonAPIs
{
	void(*LedInit)(void);
	void(*GreenLedOn)(void);
	void(*GreenLedOff)(void);
	void(*UartInit)(void);
	void (*LedToggle)(uint32_t dly);
	_Bool(*GetButtonState)(void);
};

struct bootloaderCommonAPIs commonAPIs __attribute((section(".custom_section"))) =
{
		LedInit,
		GreenLedOn,
		GreenLedOff,
		UartInit,
		LedToggle,
		GetButtonState
};
#endif

int main()
{
	/* initialise the timebase */
	TimebaseInit();

	/* initialise the UART */
	UartInit();

	/* Initialise the Leds and the buttons */
	LedInit();
	ButtonInit();

	jump_to_default_app();


	while(1)
	{

		//_led_toggle2(2);

		//GreenLedOn();
		//EmbeddedLedOn();
		//delay(1);
		//GreenLedOff();
		//EmbeddedLedOff();
		//delay(1);

#if 0
		buttonState = GetButtonState();
		//delay(1);
		if(buttonState == 0)
		{
			//printf("Is the button on? %d\n\r", GetButtonState());
			GreenLedOn();
		}
		else
		{
			GreenLedOff();
		}

		//printf("Hello from STM32L0\n\r");
		//printf("Is the button on? %d\n\r", buttonState);
		//delay(1);
#endif
	}
}

void RAM_FUNCTION _led_toggle(uint32_t dly)
{
	GPIOA->ODR ^= GPIO_ODR_OD8;
	delay(dly);
}

#if 0
void CUSTOM_FUNCTION _led_toggle2(uint32_t dly)
{
	GPIOA->ODR ^= GPIO_ODR_OD8;
	delay(dly);
}
#endif
