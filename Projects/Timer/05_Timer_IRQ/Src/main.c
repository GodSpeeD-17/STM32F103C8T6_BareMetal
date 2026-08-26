/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Implements the Timer update-IRQ demo application behavior
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior implementation
 * - Called by: Layer 4 Reset_Handler() after App_Init() succeeds
 * - Uses: Layer 2 `app_time` and Layer 1 Timer/GPIO/BSP/NVIC Drivers
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * Configures TIM3 with a 10 kHz counter tick and a 10000-count period. The
 * resulting one-second update interrupt toggles a GPIO LED. Application code
 * uses only the currently implemented public Timer IRQ surface.
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
#include "gpio.h"
#include "nvic.h"
#include "rcc.h"
#include "timer.h"

// ==================================================================================================== //
// Private Defines
// ==================================================================================================== //

/** @brief Application GPIO Port @def APP_GPIO_LED_PORT */
#define APP_GPIO_LED_PORT			(GPIOA)
/** @brief Application GPIO Pin @def APP_GPIO_LED_PIN */
#define APP_GPIO_LED_PIN			(GPIO_PIN_3)
/** @brief Application-owned GPIO port clock gate for the LED @def APP_GPIO_LED_CLOCK_MASK */
#define APP_GPIO_LED_CLOCK_MASK		(RCC_APB2ENR_IOPAEN)
/** @brief Application Timer @def APP_TIMER */
#define APP_TIMER					(TIM3)
/** @brief Application Timer Clock Enable Mask @def APP_TIMER_ENABLE_MASK */
#define APP_TIMER_ENABLE_MASK		(RCC_APB1ENR_TIM3EN)
/** @brief Application Timer Interrupt Request Number @def APP_TIMER_IRQn */
#define APP_TIMER_IRQn				(TIM3_IRQn)
/** @brief Application Timer Prescaler @def APP_TIMER_PRESCALER */
#define APP_TIMER_PRESCALER			((tim_prescaler_t) 7199U)
/** @brief Application Timer Auto-Reload @def APP_TIMER_AUTO_RELOAD */
#define APP_TIMER_AUTO_RELOAD		((tim_auto_reload_t) 999U)
/** @brief Main-loop pacing delay in milliseconds @def LOOP_DELAY_MS */
#define LOOP_DELAY_MS				((uint32_t) 1UL)

// ==================================================================================================== //
// Local Variables
// ==================================================================================================== //
/** @brief Flag indicating whether an action is required */
static volatile uint8_t isActionRequired = 0U;

// ==================================================================================================== //
// Local Helpers
// ==================================================================================================== //

/**
 * @brief Enters the application error-indication loop
 * @details
 * App_Init() already configures and forces off the BSP on-board LED, so this
 * handler only needs to set it once. Used to prevent return into an
 * unacknowledged or incorrectly configured IRQ path.
 */
static void App_ErrorHandler(void)
{
	//! Indicate the error state by turning on the on-board LED
	BSP_OB_LED_Set();

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
static driver_status_t App_ConfigTimerIRQ(void)
{
	//! Explicitly enable the application-owned GPIO port clock gate before configuring the LED.
	ASSERT_DRIVER_STATUS
(
	RCC_SetPeripheralClockState
	(
		RCC_APB2_BUS,
		APP_GPIO_LED_CLOCK_MASK,
		DRIVER_STATUS_ON
	)
);
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
	ASSERT_DRIVER_STATUS
(
	RCC_SetPeripheralClockState
	(
		RCC_APB1_BUS,
		APP_TIMER_ENABLE_MASK,
		DRIVER_STATUS_ON
	)
);
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
// Application Entry Point
// ==================================================================================================== //

int main(void)
{
	if (App_ConfigTimerIRQ() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
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
		(void) App_DelayMs(LOOP_DELAY_MS);
	}
}

// ==================================================================================================== //
// Interrupt Handlers
// ==================================================================================================== //

/**
 * @brief Handles TIM3 update interrupts
 * @details
 * Reads the public pending-event mask, services only the update flag, and
 * acknowledges that flag through the public W0C-aware Timer path. A failure
 * is terminal so execution cannot return into an unacknowledged IRQ storm.
 */
void TIM3_IRQHandler(void)
{
	tim_event_flag_t irqEvents = TIMx_IRQ_EVENT_NONE;
	//! Read the public pending-event mask
	if (TIM_GetIRQEvents(APP_TIMER, &irqEvents) != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}
	//! Service only the update flag
	if ((irqEvents & TIMx_IRQ_EVENT_UPDATE) != TIMx_IRQ_EVENT_NONE)
	{
		//! Ask the main loop to perform the visible action
		isActionRequired = 1U;

		//! Acknowledge only the serviced update flag and preserve unrelated Timer flags.
		if (TIM_AckIRQEvents(APP_TIMER, TIMx_IRQ_EVENT_UPDATE) != DRIVER_STATUS_SUCCESS)
		{
			App_ErrorHandler();
		}
	}
}
