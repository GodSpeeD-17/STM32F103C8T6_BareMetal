/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Timer Update IRQ Demo
 * @version	v1.0
 * @date	15-08-2026
 *
 * @details
 * Configures TIM3 with a 10 kHz counter tick and a 10000-count period. The
 * resulting one-second update interrupt toggles the on-board LED. Application
 * code uses only the currently implemented public Timer IRQ surface.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "main.h"

// ==================================================================================================== //
//											Local Variables												//
// ==================================================================================================== //
/** @brief Flag indicating whether an action is required */
static volatile uint8_t isActionRequired = 0U;

// ==================================================================================================== //
//											Local Helpers												//
// ==================================================================================================== //

/**
 * @brief Enters the application error-indication loop
 * @details
 * The Blue Pill on-board LED is active-low. The handler switches it on and
 * prevents return into an unacknowledged or incorrectly configured IRQ path.
 */
static void APP_ErrorHandler(void)
{
	//! Indicate the error state by turning on the on-board LED
	OB_LED_Set();

	//! Infinite loop to preserve the error state until the board is reset
	while (1);
}

/**
 * @brief Initializes TIM3 for a one-second update interrupt
 * @details
 * The sequence explicitly enables the TIM3 clock gate, establishes the tick
 * and auto-reload period while TIM3 is stopped, enables the Timer update
 * source, prepares the dedicated NVIC line, and starts counter operation.
 * @returns @ref driver_status_t "IRQ-Timer initialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: TIM3 update interrupts were started
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A Timer configuration selector was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: A required Timer clock or IRQ state was unavailable
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: TIM3 was running during configuration
 */
static driver_status_t APP_Init(void)
{
	//! Configure GPIO for LED
	ASSERT_DRIVER_STATUS(GPIO_LED_Init(APP_GPIO_LED_PORT, APP_GPIO_LED_PIN));

	//! Configure TIM3
	const tim_config_t config =
	{
		.timebase =
		{
			.prescaler = APP_TIMER_PRESCALER,
			.auto_reload = APP_TIMER_AUTO_RELOAD,
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
		}
	};

	//! Explicitly enable the application-owned TIM3 clock before Timer configuration.
	ASSERT_DRIVER_STATUS(RCC_APB1_ClockEnable(APP_TIMER_ENABLE_MASK));
	//! Apply only TIM3 base configuration; IRQ-source intent remains a separate application decision.
	ASSERT_DRIVER_STATUS(TIM_Config(APP_TIMER, &config));
	//! Explicitly enable the Timer update request before enabling its independently owned NVIC line.
	ASSERT_DRIVER_STATUS(TIM_SetIRQSources(APP_TIMER, TIMx_IRQ_SOURCE_UPDATE, DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS(NVIC_ClearPendingIRQ(APP_TIMER_IRQn));
	ASSERT_DRIVER_STATUS(NVIC_EnableIRQ(APP_TIMER_IRQn));
	ASSERT_DRIVER_STATUS(TIM_SetOperationState(APP_TIMER, DRIVER_STATUS_ON));

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Main Entry Point										//
// ==================================================================================================== //

/**
 * @brief Runs the TIM3 update-interrupt demonstration
 * @returns Process status
 * @retval - `0`: The function returned normally, which is not expected in this
 * bare-metal application.
 */
int main(void)
{
	if (APP_Init() != DRIVER_STATUS_SUCCESS)
	{
		APP_ErrorHandler();
	}

	while (1)
	{
		//! All visible work is performed by the TIM3 interrupt handler.
		if (isActionRequired != 0U)
		{
			//! Toggle GPIO to indicate timer expiration
			GPIO_PinToggle(APP_GPIO_LED_PORT, APP_GPIO_LED_PIN);
			//! Clear the action-required flag so the main loop can wait for the next interrupt
			isActionRequired = 0U;
		}

		//! Blocking delay to prevent the main loop from running too fast
		TIM_BlockingDelayMs(DELAY_TIMER, 1U);
	}

	return 0;
}

// ==================================================================================================== //
//										Interrupt Handlers										//
// ==================================================================================================== //

/**
 * @brief Handles TIM3 update interrupts
 * @details
 * Reads the public pending-event mask, services only the update flag, and
 * acknowledges that flag through the public W0C-aware Timer path. A failure
 * is terminal so execution cannot return into an unacknowledged IRQ storm.
 */
void APP_TIMER_IRQHandler(void)
{
	// Local Variable
	tim_event_flag_t irqEvents = TIMx_IRQ_EVENT_NONE;
	//! Read the public pending-event mask
	if (TIM_GetIRQEvents(APP_TIMER, &irqEvents) != DRIVER_STATUS_SUCCESS)
	{
		APP_ErrorHandler();
	}
	//! Service only the update flag
	if ((irqEvents & TIMx_IRQ_EVENT_UPDATE) != TIMx_IRQ_EVENT_NONE)
	{
		//! Ask the main loop to perform the visible action
		isActionRequired = 1U;

		//! Acknowledge only the serviced update flag and preserve unrelated Timer flags.
		if (TIM_AckIRQEvents(APP_TIMER, TIMx_IRQ_EVENT_UPDATE) != DRIVER_STATUS_SUCCESS)
		{
			APP_ErrorHandler();
		}
	}
}
