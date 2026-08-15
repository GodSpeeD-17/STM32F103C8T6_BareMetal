/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Timer Polling Delay Demo
 * @version	v1.0
 * @date	15-08-2026
 *
 * @details
 * Configures TIM2 as a dedicated 1 MHz blocking polling-delay source. The application
 * toggles the on-board LED once per blocking delay interval and treats any
 * Timer status failure as terminal.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "main.h"

// ==================================================================================================== //
//										Local Helpers											//
// ==================================================================================================== //

/**
 * @brief Enters the application error-indication loop
 * @details
 * The Blue Pill on-board LED is active-low. The handler switches it on and
 * stops application progress after a Timer operation fails.
 */
static void App_ErrorHandler(void)
{
	OB_LED_Set();
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
static driver_status_t App_Init(void)
{
	//! Explicitly enable the application-owned TIM2 clock before configuring the blocking-delay service.
	ASSERT_DRIVER_STATUS(RCC_APB1_ClockEnable(RCC_APB1ENR_TIM2EN));
	//! Apply the canonical dedicated blocking-delay configuration for the established 72 MHz clock tree.
	return TIM_ConfigForBlockingDelay(TIM2);
}

// ==================================================================================================== //
//										Main Entry Point										//
// ==================================================================================================== //

/**
 * @brief Runs the TIM2 blocking polling-delay demonstration
 * @returns Process status
 * @retval - `0`: The function returned normally, which is not expected in this
 * bare-metal application.
 */
int main(void)
{
	if (App_Init() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}

	while (1)
	{
		//! Toggle on-board LED
		OB_LED_Toggle();

		//! Stop the demo on timeout or lost Timer ownership instead of hiding the status.
		if (TIM_BlockingDelayMs(TIM2, LOOP_DELAY_MS) != DRIVER_STATUS_SUCCESS)
		{
			App_ErrorHandler();
		}
	}

	return 0;
}
