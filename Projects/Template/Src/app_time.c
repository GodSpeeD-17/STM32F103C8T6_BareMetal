/**
 * @file	app_time.c
 * @author	Shrey Shah
 * @brief	Implements the application monotonic millisecond service
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section APP_TIME_C_HIERARCHY Hierarchy
 * - Position: Layer 2 - Application service implementation
 * - Called by: Layer 3 `main`, Layer 2 `app_delay`, and the SysTick exception
 * - Uses: Layer 1 shared SysTick Driver
 *
 * @section APP_TIME_C_RESPONSIBILITY Responsibility
 * This module converts the configured processor clock into a register-semantic
 * SysTick configuration, owns elapsed milliseconds, and supplies the minimal
 * strong interrupt handler required by the application timebase.
 *
 * @section APP_TIME_C_BOUNDARY Dependency Boundary
 * This module performs no direct register access. The SysTick Driver owns
 * hardware state and never includes or calls this application service.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //

#include "app_time.h"

#if (APP_ENABLE_SYSTICK_TIMEBASE == 1U)
#include "systick.h"
#endif /* APP_ENABLE_SYSTICK_TIMEBASE */

#if (APP_ENABLE_SYSTICK_TIMEBASE == 1U)

// ==================================================================================================== //
// Private Data
// ==================================================================================================== //

/** @brief Application milliseconds incremented only by SysTick_Handler() */
static volatile uint32_t appTickMs = 0UL;

// ==================================================================================================== //
// Application Timebase Initialization API
// ==================================================================================================== //

driver_status_t App_TimeInit(const frequency_t inputClockHz)
{
	frequency_t reloadPeriod = 0UL;
	systick_config_t config = {0};

	//! Reject an inexact millisecond period before changing any hardware state.
	if
	(
		(inputClockHz == 0UL) ||
		(APP_SYSTICK_TICK_HZ == 0UL) ||
		(APP_SYSTICK_TICK_HZ > inputClockHz) ||
		((inputClockHz % APP_SYSTICK_TICK_HZ) != 0UL)
	)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	reloadPeriod = inputClockHz / APP_SYSTICK_TICK_HZ;

	//! LOAD stores period-minus-one, so admit periods through the full 24-bit range plus one.
	if (reloadPeriod > (SYSTICK_RELOAD_VALUE_MAX + 1UL))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	config.clock_source = SYSTICK_CLOCK_SOURCE_PROCESSOR;
	config.reload_value = (systick_reload_value_t) (reloadPeriod - 1UL);

	//! Teardown precedes setup so stale IRQ, operation, and partial-period state cannot leak forward.
	ASSERT_DRIVER_STATUS(SysTick_DeConfig());
	ASSERT_DRIVER_STATUS(SysTick_SetConfig(&config));

	//! Establish both software and hardware origins before exception delivery begins.
	appTickMs = 0UL;
	SysTick_ResetCurrentValue();
	ASSERT_DRIVER_STATUS(SysTick_SetIRQState(DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS(SysTick_SetOperationState(DRIVER_STATUS_ON));

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
// Application Timebase Operation State APIs
// ==================================================================================================== //

// ---------------------------------------------------------------------------------------------------- //
// Application Timebase Operation State Pair
// ---------------------------------------------------------------------------------------------------- //

driver_status_t App_TimeGetOperationState(void)
{
	//! Preserve the Driver's exact OFF/ON state without duplicating hardware interpretation.
	return SysTick_GetOperationState();
}

driver_status_t App_TimeSetOperationState(const driver_status_t operationState)
{
	//! Delegate state validation and mutation to the hardware-owning Driver.
	return SysTick_SetOperationState(operationState);
}

// ==================================================================================================== //
// Application Time Observation APIs
// ==================================================================================================== //

uint32_t App_TimeGetTickMs(void)
{
	//! An aligned 32-bit read is atomic on Cortex-M3, so no interrupt masking is required.
	return appTickMs;
}

uint32_t App_TimeGetElapsedMs(const uint32_t startTickMs)
{
	//! Unsigned subtraction preserves elapsed duration across one 32-bit wrap.
	return App_TimeGetTickMs() - startTickMs;
}

// ==================================================================================================== //
// Application Timebase Interrupt Handler
// ==================================================================================================== //

void SysTick_Handler(void)
{
	//! Keep IRQ work bounded to one publication; scheduling and callbacks remain in main context.
	appTickMs++;
}

#endif /* APP_ENABLE_SYSTICK_TIMEBASE */
