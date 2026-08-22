/**
 * @file	app_time.c
 * @author	Shrey Shah
 * @brief	Adapts the project SysTick service into application milliseconds
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section APP_TIME_C_HIERARCHY Hierarchy
 * - Position: Layer 2 - Application service implementation
 * - Called by: Layer 3 `main` and Layer 2 `app_delay`
 * - Uses: Layer 1 project-owned `systick`
 *
 * @section APP_TIME_C_RESPONSIBILITY Responsibility
 * This module adapts hardware-facing SysTick operations into application-facing
 * initialization, millisecond observation, and wrap-safe elapsed-time APIs.
 *
 * @section APP_TIME_C_BOUNDARY Dependency Boundary
 * This module performs no register access. `systick` never includes or calls
 * `app_time`, keeping the service-to-hardware dependency one-way.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "app_time.h"
#include "systick.h"

// ==================================================================================================== //
// Timebase Initialization API
// ==================================================================================================== //

#if (APP_ENABLE_SYSTICK_TIMEBASE == 1U)

driver_status_t App_TimeInit(const frequency_t inputClockHz)
{
	//! Configure and reset before enabling so no partial tick interval is published.
	ASSERT_DRIVER_STATUS(SysTick_SetConfig(inputClockHz, APP_SYSTICK_TICK_HZ));
	//! Establish the application time origin while SysTick remains stopped.
	SysTick_ResetTicks();
	//! Publish the running state only after configuration and origin setup succeed.
	ASSERT_DRIVER_STATUS(SysTick_SetOperationState(DRIVER_STATUS_ON));

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
// Timebase Operation State APIs
// ==================================================================================================== //

// ---------------------------------------------------------------------------------------------------- //
// Timebase Operation State Pair
// ---------------------------------------------------------------------------------------------------- //

driver_status_t App_TimeGetOperationState(void)
{
	//! Preserve the Layer 1 OFF/ON vocabulary without duplicating register interpretation.
	return SysTick_GetOperationState();
}

driver_status_t App_TimeSetOperationState(const driver_status_t operationState)
{
	//! Delegate validation and mutation so Layer 2 owns no SysTick register policy.
	return SysTick_SetOperationState(operationState);
}

// ==================================================================================================== //
// Time Observation APIs
// ==================================================================================================== //

uint32_t App_TimeGetTickMs(void)
{
	//! One SysTick interrupt equals one millisecond under the fixed 1 kHz service contract.
	return SysTick_GetTicks();
}

uint32_t App_TimeGetElapsedMs(const uint32_t startTickMs)
{
	//! Unsigned subtraction preserves elapsed intervals across one counter wrap.
	return App_TimeGetTickMs() - startTickMs;
}

#endif /* APP_ENABLE_SYSTICK_TIMEBASE */
