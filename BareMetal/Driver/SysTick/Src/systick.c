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
	if((clockSource == SYSTICK_CLOCK_SOURCE_PROCESSOR_DIV8) || (clockSource == SYSTICK_CLOCK_SOURCE_PROCESSOR))
	{
		return DRIVER_STATUS_SUCCESS;
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
}

/**
 * @brief Validates the supported SysTick root-configuration values
 * @param[in]	clockSource	SysTick clock-source selector
 * Accepted values:
 * - @ref `SYSTICK_CLOCK_SOURCE_PROCESSOR_DIV8`
 * - @ref `SYSTICK_CLOCK_SOURCE_PROCESSOR`
 * @param[in]	reloadValue	SysTick reload-register value
 * Accepted values:
 * - `0x00000000UL..0x00FFFFFFUL`
 * @returns @ref driver_status_t "SysTick root-configuration validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `clockSource` and @p `reloadValue` are valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `clockSource` or @p `reloadValue` is invalid
 */
__STATIC_FORCEINLINE driver_status_t _SysTick_ValidateConfig(const systick_clock_source_t clockSource, const systick_reload_value_t	reloadValue)
{
	//! Validate the selector before checking the independent reload payload.
	ASSERT_DRIVER_STATUS(_SysTick_ValidateClockSource(clockSource));

	//! Reject bits outside the implemented 24-bit reload field.
	if ((reloadValue & ~SYSTICK_RELOAD_VALUE_MAX) != 0x00000000UL)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a SysTick ON/OFF state selector
 * @param[in]	state	SysTick state selector
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`
 * - @ref `DRIVER_STATUS_ON`
 * @returns @ref driver_status_t "SysTick state validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `state` is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `state` is invalid
 */
__STATIC_FORCEINLINE driver_status_t _SysTick_ValidateState(const driver_status_t state)
{
	//! Share one exact OFF/ON vocabulary across IRQ-source and operation domains.
	if ((state == DRIVER_STATUS_OFF) || (state == DRIVER_STATUS_ON))
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

driver_status_t SysTick_GetConfig(systick_clock_source_t* const pClockSource, systick_reload_value_t* const pReloadValue)
{
	reg controlRegister = 0x00000000UL;
	systick_clock_source_t clockSource = SYSTICK_CLOCK_SOURCE_PROCESSOR_DIV8;
	systick_reload_value_t reloadValue = 0x00000000UL;

	//! Validate both destinations before the destructive `CTRL` read clears `COUNTFLAG`.
	if ((pClockSource == NULL) || (pReloadValue == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	controlRegister = LL_SysTick_ReadCTRL();
	clockSource = (systick_clock_source_t) (controlRegister & SysTick_CTRL_CLKSOURCE);
	reloadValue = (systick_reload_value_t) (LL_SysTick_ReadLOAD() & SysTick_LOAD_RELOAD);

	//! Complete every hardware observation before publishing either scalar result.
	*pClockSource = clockSource;
	*pReloadValue = reloadValue;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t SysTick_SetConfig(const systick_clock_source_t clockSource, const systick_reload_value_t reloadValue)
{
	// Local Variable
	reg controlRegister = 0x00000000UL;

	//! Complete validation precedes the first hardware read or write.
	ASSERT_DRIVER_STATUS(_SysTick_ValidateConfig(clockSource, reloadValue));
	controlRegister = LL_SysTick_ReadCTRL();

	//! Reuse the one CTRL snapshot for the busy guard and final field-preserving image.
	if ((controlRegister & SysTick_CTRL_ENABLE) != 0x00000000UL)
	{
		return DRIVER_STATUS_ERROR_BUSY;
	}

	controlRegister &= ~SysTick_CTRL_CLKSOURCE;
	controlRegister |= clockSource;

	//! Commit only represented root fields while preserving the separate IRQ-source domain.
	LL_SysTick_WriteLOAD(reloadValue);
	LL_SysTick_WriteCTRL(controlRegister);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
// SysTick IRQ Source State APIs
// ==================================================================================================== //

// ---------------------------------------------------------------------------------------------------- //
// SysTick IRQ Source State Pair
// ---------------------------------------------------------------------------------------------------- //

driver_status_t SysTick_GetIRQSourceState(void)
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

driver_status_t SysTick_SetIRQSourceState(const driver_status_t sourceState)
{
	// Local Variable
	reg controlRegister = 0x00000000UL;

	//! Reject invalid state before the `CTRL` read can clear `COUNTFLAG`.
	ASSERT_DRIVER_STATUS(_SysTick_ValidateState(sourceState));
	controlRegister = LL_SysTick_ReadCTRL();

	//! Decide the relevant action based on the requested state
	if (sourceState == DRIVER_STATUS_OFF)
	{
		controlRegister &= ~SysTick_CTRL_TICKINT;
	}
	else
	{
		controlRegister |= SysTick_CTRL_TICKINT;
	}

	//! Preserve root configuration and counter operation in the staged control image.
	LL_SysTick_WriteCTRL(controlRegister);

	// Return Status
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
	// Local Variable
	reg controlRegister = 0x00000000UL;

	//! Reject invalid state before the `CTRL` read can clear `COUNTFLAG`.
	ASSERT_DRIVER_STATUS(_SysTick_ValidateState(operationState));
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
