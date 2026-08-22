/**
 * @file	systick.c
 * @author	Shrey Shah
 * @brief	Owns SysTick register access and the application tick accumulator
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section SYSTICK_C_HIERARCHY Hierarchy
 * - Position: Layer 1 - Project hardware-access implementation
 * - Called by: Layer 2 `app_time` and the SysTick exception
 * - Uses: Cortex-M3 SysTick register definitions from Core
 *
 * @section SYSTICK_C_RESPONSIBILITY Responsibility
 * This module configures and controls SysTick, stores the tick accumulator,
 * and increments that accumulator in SysTick_Handler().
 *
 * @section SYSTICK_C_BOUNDARY Dependency Boundary
 * Millisecond policy remains in `app_time`. The interrupt handler performs one
 * increment and calls no Driver or application service.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "systick.h"
#include "stm32f1xx.h"

// ==================================================================================================== //
// Private Defines
// ==================================================================================================== //

/** @brief Maximum reload period admitted by the 24-bit SysTick counter @def SYSTICK_RELOAD_PERIOD_MAX */
#define SYSTICK_RELOAD_PERIOD_MAX		((uint32_t) 0x01000000UL)

// ==================================================================================================== //
// Private Data
// ==================================================================================================== //

/** @brief Monotonic application tick count incremented by SysTick_Handler() */
static volatile uint32_t appTickCount = 0UL;

// ==================================================================================================== //
// Configuration APIs
// ==================================================================================================== //

driver_status_t SysTick_SetConfig(const frequency_t inputClockHz, const frequency_t tickFrequencyHz)
{
	frequency_t reloadPeriod = 0UL;

	if
	(
		(inputClockHz == 0UL) || (tickFrequencyHz == 0UL) ||
		(tickFrequencyHz > inputClockHz) || ((inputClockHz % tickFrequencyHz) != 0UL)
	)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	reloadPeriod = inputClockHz / tickFrequencyHz;

	// Validate Period
	if ((reloadPeriod == 0UL) || (reloadPeriod > SYSTICK_RELOAD_PERIOD_MAX))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Stop SysTick before replacing the complete timebase configuration.
	SysTick->CTRL.REG = 0x00000000UL;
	SysTick->LOAD = (reg) (reloadPeriod - 1UL);
	SysTick->VAL = 0x00000000UL;
	SysTick->CTRL.REG = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk;

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
// Counter Operation State APIs
// ==================================================================================================== //

// ---------------------------------------------------------------------------------------------------- //
// Counter Operation State Pair
// ---------------------------------------------------------------------------------------------------- //

driver_status_t SysTick_GetOperationState(void)
{
	//! Operation state is represented only by ENABLE; preserve every configuration field.
	if ((SysTick->CTRL.REG & SysTick_CTRL_ENABLE_Msk) == 0UL)
	{
		return DRIVER_STATUS_OFF;
	}

	return DRIVER_STATUS_ON;
}

driver_status_t SysTick_SetOperationState(const driver_status_t operationState)
{
	if (operationState == DRIVER_STATUS_OFF)
	{
		//! Clear only ENABLE so a stopped timebase retains its complete configuration.
		SysTick->CTRL.REG &= ~SysTick_CTRL_ENABLE_Msk;
	}
	else if (operationState == DRIVER_STATUS_ON)
	{
		//! Set only ENABLE so starting cannot alter the selected clock or IRQ source.
		SysTick->CTRL.REG |= SysTick_CTRL_ENABLE_Msk;
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
// Tick Accumulator APIs
// ==================================================================================================== //

// ---------------------------------------------------------------------------------------------------- //
// Tick Reset and Read Operations
// ---------------------------------------------------------------------------------------------------- //

void SysTick_ResetTicks(void)
{
	//! Re-establish software and hardware count origins together while operation is stopped.
	appTickCount = 0UL;
	SysTick->VAL = 0x00000000UL;
}

uint32_t SysTick_GetTicks(void)
{
	//! Use the Cortex-M3 atomic aligned-word read without masking interrupt delivery.
	return appTickCount;
}

// ==================================================================================================== //
// Interrupt Handler API
// ==================================================================================================== //

void SysTick_Handler(void)
{
	//! Keep IRQ work bounded to publishing one tick; all time policy remains in the main context.
	appTickCount++;
}
