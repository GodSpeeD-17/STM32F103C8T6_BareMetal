/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Implements the Timer polling-delay demo application behavior
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior implementation
 * - Called by: Layer 4 Reset_Handler() after App_Init() succeeds
 * - Uses: Layer 1 Timer/BSP Drivers directly
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * Configures TIM2 as a dedicated 1 MHz blocking polling-delay source. The
 * application toggles the on-board LED once per blocking delay interval and
 * treats any Timer status failure as terminal. TIM2 is owned directly by this
 * demo rather than through `app_time`, since demonstrating the Timer
 * driver's own blocking-delay API is the point of this project.
 *
 * @section MAIN_C_BOUNDARY Dependency Boundary
 * Application behavior belongs here. Processor startup, clock configuration,
 * and service initialization do not.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "main.h"
#include "bsp_gpio.h"
#include "rcc.h"
#include "timer.h"

// ==================================================================================================== //
// Private Defines
// ==================================================================================================== //

/** @brief Polling-delay demonstration interval in milliseconds @def LOOP_DELAY_MS */
#define LOOP_DELAY_MS		((uint32_t) 1000UL)

// ==================================================================================================== //
// Local Helpers
// ==================================================================================================== //

/**
 * @brief Enters the application error-indication loop
 * @details
 * App_Init() already configures and forces off the BSP on-board LED, so this
 * handler only needs to set it once after a Timer operation fails.
 */
static void App_ErrorHandler(void)
{
	BSP_OB_LED_Set();
	while (1)
	{
		//! Preserve the visible error state until the board is reset.
	}
}

/**
 * @brief Initializes TIM2 as the polling demo's dedicated delay source
 * @returns @ref driver_status_t "Polling-Timer initialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: TIM2 was configured with a 1 MHz counter tick
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: TIM2 or the canonical delay configuration was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The TIM2 clock gate or kernel clock was unavailable, or the kernel clock was not 72 MHz
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: The TIM2 counter was running
 * @note The application explicitly enables the TIM2 clock gate before Timer
 * configuration, which leaves counter operation disabled for @ref TIM_BlockingDelayMs
 */
static driver_status_t App_ConfigTimer(void)
{
	//! Explicitly enable the application-owned TIM2 clock before configuring the blocking-delay service.
	ASSERT_DRIVER_STATUS
(
	RCC_SetPeripheralClockState
	(
		RCC_APB1_BUS,
		RCC_APB1ENR_TIM2EN,
		DRIVER_STATUS_ON
	)
);
	//! Apply the canonical dedicated blocking-delay configuration for the established 72 MHz clock tree.
	return TIM_ConfigForBlockingDelay(TIM2);
}

// ==================================================================================================== //
// Application Entry Point
// ==================================================================================================== //

int main(void)
{
	if (App_ConfigTimer() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}

	while (1)
	{
		//! Toggle on-board LED
		BSP_OB_LED_Toggle();

		//! Stop the demo on timeout or lost Timer ownership instead of hiding the status.
		if (TIM_BlockingDelayMs(TIM2, LOOP_DELAY_MS) != DRIVER_STATUS_SUCCESS)
		{
			App_ErrorHandler();
		}
	}
}
