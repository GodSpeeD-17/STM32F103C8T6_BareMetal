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
//										Local Helpers											//
// ==================================================================================================== //

/**
 * @brief Enters the application error-indication loop
 * @details
 * The Blue Pill on-board LED is active-low. The handler switches it on and
 * prevents return into an unacknowledged or incorrectly configured IRQ path.
 */
static void APP_ErrorHandler(void)
{
	OB_LED_Set();
	while (1)
	{
		//! Preserve the visible error state until the board is reset.
	}
}

/**
 * @brief Initializes TIM3 for a one-second update interrupt
 * @details
 * The sequence first establishes the tick and auto-reload period while TIM3
 * is stopped, then enables the update source and starts counter operation.
 * @returns @ref driver_status_t "IRQ Timer Initialization - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`:			TIM3 update interrupts were started.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`:	A Timer selector or exact tick request was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`:		A required Timer clock or IRQ state was unavailable.
 */
static driver_status_t APP_Init(void)
{
	ASSERT_DRIVER_STATUS(TIM_ConfigTickFrequency(TIM3, APP_TIMER_TICK_FREQUENCY_HZ));
	ASSERT_DRIVER_STATUS(TIM_SetAutoReload(TIM3, APP_TIMER_AUTO_RELOAD));
	ASSERT_DRIVER_STATUS(TIM_SetIRQState(TIM3, TIMx_IRQ_OVF_UVF, DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS(TIM_SetOperationState(TIM3, DRIVER_STATUS_ON));

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
void TIM3_IRQHandler(void)
{
	tim_irq_t pendingMask = (tim_irq_t) 0U;

	if (TIM_GetPendingIRQMask(TIM3, &pendingMask) != DRIVER_STATUS_SUCCESS)
	{
		APP_ErrorHandler();
	}

	if ((pendingMask & TIMx_IRQ_OVF_UVF) != (tim_irq_t) 0U)
	{
		OB_LED_Toggle();

		//! Acknowledge only the serviced update flag and preserve unrelated Timer flags.
		if (TIM_AcknowledgeIRQ(TIM3, TIMx_IRQ_OVF_UVF) != DRIVER_STATUS_SUCCESS)
		{
			APP_ErrorHandler();
		}
	}
}
