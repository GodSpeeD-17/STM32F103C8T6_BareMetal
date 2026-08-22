/**
 * @file	app_delay.c
 * @author	Shrey Shah
 * @brief	Implements the application's blocking-delay policy
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section APP_DELAY_C_HIERARCHY Hierarchy
 * - Position: Layer 2 - Application service implementation
 * - Called by: Layer 3 application orchestration and behavior
 * - Uses: Layer 2 `app_time` and optional Layer 1 RCC/Timer Drivers
 *
 * @section APP_DELAY_C_RESPONSIBILITY Responsibility
 * App_DelayMs() blocks against the monotonic application timebase.
 * App_DelayTimerInit() and App_DelayUs() optionally allocate and poll one
 * preconfigured Timer for microsecond waits.
 *
 * @section APP_DELAY_C_BOUNDARY Dependency Boundary
 * This module owns no interrupt handler, Timer IRQ source, or NVIC state.
 * `app_time`, RCC, and Timer never include or call this application service.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //

#include "app_delay.h"

#include "app_time.h"
#include "stm32f1xx.h"

#if (APP_ENABLE_TIMER_US_DELAY == 1U)
#include "rcc.h"
#include "timer.h"
#endif

// ==================================================================================================== //
// Private Defines
// ==================================================================================================== //

/** @brief Largest wrap-safe 32-bit millisecond delay interval @def APP_DELAY_MS_MAX */
#define APP_DELAY_MS_MAX		((uint32_t) 0x7FFFFFFFUL)

// ==================================================================================================== //
// Millisecond Blocking Delay
// ==================================================================================================== //

driver_status_t App_DelayMs(const uint32_t delayMs)
{
	uint32_t startTickMs = 0UL;

	if ((delayMs == 0UL) || (delayMs > APP_DELAY_MS_MAX))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

#if (APP_ENABLE_SYSTICK_TIMEBASE == 1U)
	//! WFI-based waiting requires a running timebase and interrupt delivery from thread mode.
	if ((App_TimeGetOperationState() != DRIVER_STATUS_ON) ||
		(__get_IPSR() != 0UL) ||
		(__get_PRIMASK() != 0UL))
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	//! Capture one stable origin and use unsigned elapsed arithmetic across counter wrap.
	startTickMs = App_TimeGetTickMs();
	while (App_TimeGetElapsedMs(startTickMs) < delayMs)
	{
		//! Sleep between tick interrupts instead of spinning for the complete blocking interval.
		__WFI();
	}

	return DRIVER_STATUS_SUCCESS;
#else
	(void) startTickMs;
	return DRIVER_STATUS_ERROR_STATE;
#endif
}

#if (APP_ENABLE_TIMER_US_DELAY == 1U)

// ==================================================================================================== //
// Microsecond Timer Delay
// ==================================================================================================== //

driver_status_t App_DelayTimerInit(void)
{
	//! Clock-gate ownership remains explicit at the application-service boundary.
	ASSERT_DRIVER_STATUS(RCC_SetAPB1ClockState(APP_DELAY_TIMER_CLOCK_MASK, DRIVER_STATUS_ON));
	//! Configure the dedicated Timer once so delay calls only perform bounded polling transactions.
	return TIM_ConfigForBlockingDelay(APP_DELAY_TIMER);
}

driver_status_t App_DelayUs(const uint32_t delayUs)
{
	uint32_t remainingDelayUs = delayUs;

	if (delayUs == 0UL)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	while (remainingDelayUs != 0UL)
	{
		uint16_t delayChunkUs = 0U;

		//! Respect the Timer Driver's 16-bit public duration contract for every transaction.
		if (remainingDelayUs > 0xFFFFUL)
		{
			delayChunkUs = 0xFFFFU;
		}
		else
		{
			delayChunkUs = (uint16_t) remainingDelayUs;
		}

		//! Reuse the retained Timer configuration and advance only after a complete chunk.
		ASSERT_DRIVER_STATUS(TIM_BlockingDelayUs(APP_DELAY_TIMER, delayChunkUs));
		remainingDelayUs -= (uint32_t) delayChunkUs;
	}

	return DRIVER_STATUS_SUCCESS;
}
#endif
