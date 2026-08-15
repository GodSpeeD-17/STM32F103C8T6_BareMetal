/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Timer Polling Delay Demo
 * @version	v1.0
 * @date	15-08-2026
 *
 * @details
 * Configures TIM2 as a dedicated 1 MHz polling-delay source. The application
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
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A Timer configuration selector was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The TIM2 clock or reset sequence failed
 * @note The root configuration owns the Timer clock gate and leaves counter
 * operation disabled for @ref TIM_DelayMs
 */
static driver_status_t App_Init(void)
{
	const tim_config_t config =
	{
		.timebase =
		{
			.prescaler = TIMx_DEFAULT_1MHz_PSC,
			.auto_reload = TIMx_DEFAULT_1MHz_ARR,
			.initial_count = TIMx_DEFAULT_CNT
		},
		.counter =
		{
			.digital_filter_clock_division = TIMx_DIGITAL_FILTER_CLOCK_DIV_1,
			.alignment = TIMx_MODE_NORMAL,
			.direction = TIMx_DIR_COUNT_UP,
			.one_pulse = TIMx_OPM_DISABLE,
			.auto_reload_preload = TIMx_ARPE_ENABLE,
			.update_source = TIMx_UPDATE_SOURCE_ANY
		},
		.irq_sources = TIMx_IRQ_SOURCE_NONE
	};

	//! Apply explicit Timer configuration data instead of a frequency-specific preset API.
	return TIM_Config(TIM2, &config);
}

// ==================================================================================================== //
//										Main Entry Point										//
// ==================================================================================================== //

/**
 * @brief Runs the TIM2 polling-delay demonstration
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
		OB_LED_Toggle();

		//! Stop the demo on timeout or lost Timer ownership instead of hiding the status.
		if (TIM_DelayMs(TIM2, LOOP_DELAY_MS) != DRIVER_STATUS_SUCCESS)
		{
			App_ErrorHandler();
		}
	}

	return 0;
}
