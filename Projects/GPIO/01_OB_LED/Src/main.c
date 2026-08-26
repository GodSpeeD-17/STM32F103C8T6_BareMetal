/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Implements the GPIO on-board LED demo application behavior
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior implementation
 * - Called by: Layer 4 Reset_Handler() after App_Init() succeeds
 * - Uses: Layer 2 `app_time` and Layer 1 BSP Driver
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * The application toggles the BSP on-board active-low LED on a fixed period.
 * App_Init() owns LED GPIO configuration and its deterministic off state.
 *
 * @section MAIN_C_BOUNDARY Dependency Boundary
 * Application behavior belongs here. Processor startup, clock configuration,
 * and service initialization do not.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "main.h"
#include "app_time.h"
#include "bsp_gpio.h"

// ==================================================================================================== //
// Private Defines
// ==================================================================================================== //

/** @brief On-board LED toggle period in milliseconds @def LED_TOGGLE_DELAY_MS */
#define LED_TOGGLE_DELAY_MS					(2000UL)

// ==================================================================================================== //
// Application Entry Point
// ==================================================================================================== //

int main(void)
{
	while (1)
	{
		BSP_OB_LED_Toggle();
		(void) App_DelayMs(LED_TOGGLE_DELAY_MS);
	}
}
