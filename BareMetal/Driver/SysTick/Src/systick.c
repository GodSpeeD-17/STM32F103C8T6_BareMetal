/**
 * @file	systick.c
 * @author	Shrey Shah
 * @brief	SysTick Driver implementation
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section SYSTICK_C_HIERARCHY Hierarchy
 * - Position: Layer 1 - Shared SysTick Driver implementation
 * - Called by: Application hardware services
 * - Uses: SysTick public contract and hardware-nearest LL interface
 *
 * @section SYSTICK_C_RESPONSIBILITY Responsibility
 * This module validates and orchestrates reusable SysTick hardware state over
 * the LL register-access layer.
 *
 * @section SYSTICK_C_BOUNDARY Dependency Boundary
 * It intentionally contains no application include, time unit, software tick
 * accumulator, or `SysTick_Handler()` implementation. The Driver does not call
 * upward into its consumers.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //

#include "systick.h"
#include "systick_ll.h"

// ==================================================================================================== //
// Private Validation Helpers
// ==================================================================================================== //

/**
 * @brief Validates a SysTick clock-source selector
 * @param[in] clockSource SysTick clock-source selector
 * Accepted values:
 * - @ref `SYSTICK_CLOCK_SOURCE_PROCESSOR_DIV8`
 * - @ref `SYSTICK_CLOCK_SOURCE_PROCESSOR`
 * @returns @ref driver_status_t "SysTick clock-source validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `clockSource` is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `clockSource` is invalid
 */
__STATIC_FORCEINLINE driver_status_t _SysTick_ValidateClockSource(const systick_clock_source_t clockSource)
{
	//! Admit only complete raw values of the one-bit `CLKSOURCE` field.
	if
	(
		(clockSource == SYSTICK_CLOCK_SOURCE_PROCESSOR_DIV8) ||
		(clockSource == SYSTICK_CLOCK_SOURCE_PROCESSOR)
	)
	{
		return DRIVER_STATUS_SUCCESS;
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
}

/**
 * @brief Validates a complete SysTick root configuration
 * @param[in] pConfig SysTick root configuration
 * Accepted values:
 * - Non-`NULL`: Valid clock-source selector and 24-bit reload value
 * @returns @ref driver_status_t "SysTick root-configuration validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `pConfig` is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pConfig` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A configuration field is invalid
 */
__STATIC_FORCEINLINE driver_status_t _SysTick_ValidateConfig(const systick_config_t* const pConfig)
{
	//! Reject the pointer before inspecting either caller-owned configuration field.
	if (pConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_SysTick_ValidateClockSource(pConfig->clock_source));

	//! Reject bits outside the implemented 24-bit reload field.
	if ((pConfig->reload_value & ~SYSTICK_RELOAD_VALUE_MAX) != 0x00000000UL)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a binary Driver state selector
 * @param[in] requestedState Requested binary Driver state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`
 * - @ref `DRIVER_STATUS_ON`
 * @returns @ref driver_status_t "Binary-state validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `requestedState` is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `requestedState` is invalid
 */
__STATIC_FORCEINLINE driver_status_t _SysTick_ValidateBinaryState(const driver_status_t requestedState)
{
	//! Share one exact OFF/ON vocabulary across IRQ-source and operation domains.
	if ((requestedState == DRIVER_STATUS_OFF) || (requestedState == DRIVER_STATUS_ON))
	{
		return DRIVER_STATUS_SUCCESS;
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
}

// ==================================================================================================== //
// SysTick Root Configuration APIs
// ==================================================================================================== //

driver_status_t SysTick_DeConfig(void)
{
	//! Stop exception delivery and counting before clearing dependent reload/current state.
	LL_SysTick_WriteCTRL(0x00000000UL);
	LL_SysTick_WriteLOAD(0x00000000UL);
	LL_SysTick_ResetVAL();

	return DRIVER_STATUS_SUCCESS;
}

// ---------------------------------------------------------------------------------------------------- //
// SysTick Configuration Pair
// ---------------------------------------------------------------------------------------------------- //

driver_status_t SysTick_GetConfig(systick_config_t* const pConfig)
{
	reg controlRegister = 0x00000000UL;
	systick_config_t config = {0};

	//! Validate the destination before the destructive `CTRL` read clears `COUNTFLAG`.
	if (pConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	controlRegister = LL_SysTick_ReadCTRL();
	config.clock_source = (systick_clock_source_t) (controlRegister & SysTick_CTRL_CLKSOURCE);
	config.reload_value = (systick_reload_value_t) (LL_SysTick_ReadLOAD() & SysTick_LOAD_RELOAD);

	//! Publish only the complete extracted object to avoid partially updated output.
	*pConfig = config;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t SysTick_SetConfig(const systick_config_t* const pConfig)
{
	reg controlRegister = 0x00000000UL;

	//! Complete validation precedes the first hardware read or write.
	ASSERT_DRIVER_STATUS(_SysTick_ValidateConfig(pConfig));

	//! Configuration is rejected while the counter is consuming the current state.
	if (SysTick_GetOperationState() == DRIVER_STATUS_ON)
	{
		return DRIVER_STATUS_ERROR_BUSY;
	}

	controlRegister = LL_SysTick_ReadCTRL();
	controlRegister &= ~SysTick_CTRL_CLKSOURCE;
	controlRegister |= pConfig->clock_source;

	//! Commit only represented root fields while preserving the separate IRQ-source domain.
	LL_SysTick_WriteLOAD(pConfig->reload_value);
	LL_SysTick_WriteCTRL(controlRegister);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
// SysTick IRQ Source State APIs
// ==================================================================================================== //

// ---------------------------------------------------------------------------------------------------- //
// SysTick IRQ Source State Pair
// ---------------------------------------------------------------------------------------------------- //

driver_status_t SysTick_GetIRQState(void)
{
	//! Interpret only `TICKINT`; configuration and operation bits are independent domains.
	if ((LL_SysTick_ReadCTRL() & SysTick_CTRL_TICKINT) == 0x00000000UL)
	{
		return DRIVER_STATUS_OFF;
	}
	else
	{
		return DRIVER_STATUS_ON;
	}
}

driver_status_t SysTick_SetIRQState(const driver_status_t irqState)
{
	reg controlRegister = 0x00000000UL;

	//! Reject invalid state before the `CTRL` read can clear `COUNTFLAG`.
	ASSERT_DRIVER_STATUS(_SysTick_ValidateBinaryState(irqState));
	controlRegister = LL_SysTick_ReadCTRL();

	if (irqState == DRIVER_STATUS_OFF)
	{
		controlRegister &= ~SysTick_CTRL_TICKINT;
	}
	else
	{
		controlRegister |= SysTick_CTRL_TICKINT;
	}

	//! Preserve root configuration and counter operation in the staged control image.
	LL_SysTick_WriteCTRL(controlRegister);
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
// SysTick Operation State APIs
// ==================================================================================================== //

// ---------------------------------------------------------------------------------------------------- //
// SysTick Operation State Pair
// ---------------------------------------------------------------------------------------------------- //

driver_status_t SysTick_GetOperationState(void)
{
	//! Interpret only `ENABLE`; root configuration and IRQ-source state remain independent.
	if ((LL_SysTick_ReadCTRL() & SysTick_CTRL_ENABLE) == 0x00000000UL)
	{
		return DRIVER_STATUS_OFF;
	}
	else
	{
		return DRIVER_STATUS_ON;
	}
}

driver_status_t SysTick_SetOperationState(const driver_status_t operationState)
{
	reg controlRegister = 0x00000000UL;

	//! Reject invalid state before the `CTRL` read can clear `COUNTFLAG`.
	ASSERT_DRIVER_STATUS(_SysTick_ValidateBinaryState(operationState));
	controlRegister = LL_SysTick_ReadCTRL();

	if (operationState == DRIVER_STATUS_OFF)
	{
		controlRegister &= ~SysTick_CTRL_ENABLE;
	}
	else
	{
		controlRegister |= SysTick_CTRL_ENABLE;
	}

	//! Preserve root configuration and IRQ-source state in the staged control image.
	LL_SysTick_WriteCTRL(controlRegister);
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
// SysTick Current Value API
// ==================================================================================================== //

void SysTick_ResetCurrentValue(void)
{
	//! Delegate the asymmetric write-to-clear action directly to the named LL primitive.
	LL_SysTick_ResetVAL();
}
