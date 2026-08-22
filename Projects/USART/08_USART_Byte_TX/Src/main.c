/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Implements the USART byte-TX demo application behavior
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior implementation
 * - Called by: Layer 4 Reset_Handler() after App_Init() succeeds
 * - Uses: Layer 2 `app_delay` and Layer 1 USART Driver
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * Configures USART1 at 115200 baud and repeatedly transmits one incrementing
 * byte from 'A' to 'Z' once its TX buffer is ready.
 *
 * @section MAIN_C_BOUNDARY Dependency Boundary
 * Application behavior belongs here. Processor startup, clock configuration,
 * and service initialization do not.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "main.h"
#include "app_delay.h"
#include "usart.h"

// ==================================================================================================== //
// Private Defines
// ==================================================================================================== //

/** @brief USART instance used by the demo @def APP_USART */
#define APP_USART						USART_1
/** @brief Main-loop TX pacing delay in milliseconds @def LOOP_DELAY_MS */
#define LOOP_DELAY_MS					((uint32_t) 1000UL)

// ==================================================================================================== //
// Application Entry Point
// ==================================================================================================== //

int main(void)
{
	usart_config_t usartConfig;
	uint8_t counter = 'A';

	USART_Default_Config(&usartConfig);
	//! Override the default baud rate with the demo's target rate.
	usartConfig.baud_rate = USART_BAUD_115200;
	USART_Config(APP_USART, &usartConfig);
	USART_Enable(APP_USART);

	while (1)
	{
		if (USART_TX_Ready(APP_USART) != 0x00)
		{
			USART_TX_Byte(APP_USART, counter++);
			if (counter > 'Z')
			{
				counter = 'A';
			}
		}

		(void) App_DelayMs(LOOP_DELAY_MS);
	}
}
