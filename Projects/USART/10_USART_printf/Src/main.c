/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Implements the USART printf demo application behavior
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
 * Configures USART1 at its default baud rate and repeatedly prints an
 * incrementing counter via USART_printf().
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
/** @brief Main-loop print pacing delay in milliseconds @def LOOP_DELAY_MS */
#define LOOP_DELAY_MS					((uint32_t) 1000UL)

// ==================================================================================================== //
// Application Entry Point
// ==================================================================================================== //

int main(void)
{
	usart_config_t usartConfig = { 0 };
	uint16_t count = 0U;
	char* const pStr = "Hello World";

	USART_Default_Config(&usartConfig);
	USART_Config(APP_USART, &usartConfig);
	USART_Enable(APP_USART);

	while (1)
	{
		USART_printf(APP_USART, "%s: %d\t0x%.4X\n", pStr, count, count);
		count++;

		(void) App_DelayMs(LOOP_DELAY_MS);
	}
}
