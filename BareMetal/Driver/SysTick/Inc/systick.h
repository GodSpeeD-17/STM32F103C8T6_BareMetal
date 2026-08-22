/**
 * @file	systick.h
 * @author	Shrey Shah
 * @brief	SysTick Driver public interface
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section SYSTICK_H_HIERARCHY Hierarchy
 * - Position: Layer 1 - Shared hardware Driver interface
 * - Used by: Layer 2 application services such as `app_time.c`
 * - Uses: Core SysTick register-semantic types and fields
 *
 * @section SYSTICK_H_RESPONSIBILITY Responsibility
 * This header exposes the reusable Layer 1 SysTick hardware contract. The
 * Driver owns register-semantic configuration, IRQ-source state, counter
 * operation state, and current-value reset. It deliberately owns no software
 * tick counter and no `SysTick_Handler()`; those policies belong to the
 * consuming application.
 *
 * @section SYSTICK_H_BOUNDARY Dependency Boundary
 * The complete include/call direction is:
 * - Application service -> `systick.h`
 * - SysTick Driver -> `systick_ll.h`
 * - SysTick LL -> Core register layer
 * - SysTick Driver -> no application header
 */

// Header Guard
#ifndef SYSTICK_H_
#define SYSTICK_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "stm32f1xx_data_types.h"
#include "stm32f1xx_systick.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup SYSTICK_03_Driver SysTick Driver
 * @ingroup SYSTICK
 * @brief Public SysTick configuration and control interface
 * @details
 * The Driver exposes hardware state without selecting an application time
 * unit or callback policy. See @ref SYSTICK_Peripheral_Guide for the complete
 * hardware and layer-ownership model.
 * @{
 */

// ==================================================================================================== //
// SysTick Driver Data Types
// ==================================================================================================== //

/** @brief SysTick clock-source selector type @typedef systick_clock_source_t */
typedef reg								systick_clock_source_t;
/** @brief SysTick 24-bit reload-register value type @typedef systick_reload_value_t */
typedef reg								systick_reload_value_t;

/**
 * @brief Complete supported SysTick root configuration
 * @details
 * The object represents every hardware configuration domain admitted by the
 * Driver. IRQ-source and operation states remain deliberately separate.
 */
typedef struct _systick_config_t
{
	systick_clock_source_t	clock_source;	/**< `SysTick_CTRL.CLKSOURCE` selector */
	systick_reload_value_t	reload_value;	/**< `SysTick_LOAD.RELOAD` value */
} systick_config_t;

// ==================================================================================================== //
// SysTick Driver Defines
// ==================================================================================================== //

/** @brief Selects the processor clock divided by eight @def SYSTICK_CLOCK_SOURCE_PROCESSOR_DIV8 */
#define SYSTICK_CLOCK_SOURCE_PROCESSOR_DIV8		((systick_clock_source_t) 0x00000000UL)
/** @brief Selects the undivided processor clock @def SYSTICK_CLOCK_SOURCE_PROCESSOR */
#define SYSTICK_CLOCK_SOURCE_PROCESSOR			((systick_clock_source_t) SysTick_CTRL_CLKSOURCE)
/** @brief Maximum supported SysTick reload-register value @def SYSTICK_RELOAD_VALUE_MAX */
#define SYSTICK_RELOAD_VALUE_MAX				((systick_reload_value_t) SysTick_LOAD_RELOAD)

// ==================================================================================================== //
// SysTick Root Configuration APIs
// ==================================================================================================== //

/**
 * @brief Restores the complete SysTick register bank to its reset state
 * @details
 * Disables counter operation and exception requests, selects the divided
 * processor clock, clears the reload value, and clears the current value.
 * The application-owned software tick count is outside this transaction.
 * @returns @ref driver_status_t "SysTick root-deconfiguration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: SysTick hardware state was reset
 * @note SysTick is a Cortex-M3 Core peripheral and requires no RCC clock gate
 */
driver_status_t SysTick_DeConfig(void);

// ---------------------------------------------------------------------------------------------------- //
// SysTick Configuration Pair
// ---------------------------------------------------------------------------------------------------- //

/**
 * @brief Returns the complete supported SysTick root configuration
 * @param[out] pConfig Destination for the observed SysTick configuration
 * Expected values:
 * - Non-`NULL`: Current clock-source and reload values are published
 * @returns @ref driver_status_t "SysTick configuration extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: SysTick configuration was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pConfig` is `NULL`
 * @note Reading `SysTick_CTRL` clears the hardware `COUNTFLAG`; the Driver does
 * not expose `COUNTFLAG` as persistent state
 */
driver_status_t SysTick_GetConfig(systick_config_t* const pConfig);

/**
 * @brief Applies the complete supported SysTick root configuration
 * @details
 * Validates the complete object before writing `SysTick_LOAD.RELOAD` and
 * `SysTick_CTRL.CLKSOURCE`. Counter operation and exception-request state are
 * preserved. The current counter value is not cleared; call
 * SysTick_ResetCurrentValue() explicitly when establishing a new origin.
 * @param[in] pConfig Complete SysTick root configuration
 * Accepted values:
 * - Non-`NULL`: Valid clock-source selector and reload value in `0U..0xFFFFFFU`
 * @returns @ref driver_status_t "SysTick configuration operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: SysTick configuration was applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pConfig` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A configuration field is invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: SysTick counter operation is enabled
 * @pre Counter operation is @ref `DRIVER_STATUS_OFF`
 * @note This API never enables the SysTick exception request
 * @note Internal `SysTick_CTRL` reads clear the hardware `COUNTFLAG`
 */
driver_status_t SysTick_SetConfig(const systick_config_t* const pConfig);

// ==================================================================================================== //
// SysTick IRQ Source State APIs
// ==================================================================================================== //

// ---------------------------------------------------------------------------------------------------- //
// SysTick IRQ Source State Pair
// ---------------------------------------------------------------------------------------------------- //

/**
 * @brief Returns the SysTick exception-request source state
 * @returns @ref driver_status_t "SysTick IRQ-source state"
 * @retval - @ref `DRIVER_STATUS_OFF`: SysTick exception requests are disabled
 * @retval - @ref `DRIVER_STATUS_ON`: SysTick exception requests are enabled
 * @note SysTick is a Core exception and has no separate NVIC enable bit
 * @note Reading `SysTick_CTRL` clears the hardware `COUNTFLAG`
 */
driver_status_t SysTick_GetIRQState(void);

/**
 * @brief Sets the SysTick exception-request source state
 * @param[in] irqState Requested SysTick exception-request source state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disable SysTick exception requests
 * - @ref `DRIVER_STATUS_ON`: Enable SysTick exception requests
 * @returns @ref driver_status_t "SysTick IRQ-source state operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: SysTick IRQ-source state was updated
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `irqState` is invalid
 * @note Counter operation remains unchanged
 * @note The `SysTick_CTRL` read-modify-write clears the hardware `COUNTFLAG`
 */
driver_status_t SysTick_SetIRQState(const driver_status_t irqState);

// ==================================================================================================== //
// SysTick Operation State APIs
// ==================================================================================================== //

// ---------------------------------------------------------------------------------------------------- //
// SysTick Operation State Pair
// ---------------------------------------------------------------------------------------------------- //

/**
 * @brief Returns the SysTick counter-operation state
 * @returns @ref driver_status_t "SysTick operation state"
 * @retval - @ref `DRIVER_STATUS_OFF`: SysTick counter operation is disabled
 * @retval - @ref `DRIVER_STATUS_ON`: SysTick counter operation is enabled
 * @note Reading `SysTick_CTRL` clears the hardware `COUNTFLAG`
 */
driver_status_t SysTick_GetOperationState(void);

/**
 * @brief Sets the SysTick counter-operation state
 * @param[in] operationState Requested SysTick counter-operation state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disable SysTick counter operation
 * - @ref `DRIVER_STATUS_ON`: Enable configured SysTick counter operation
 * @returns @ref driver_status_t "SysTick operation-state operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: SysTick operation state was updated
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `operationState` is invalid
 * @note Clock-source, reload, and IRQ-source states remain unchanged
 * @note The `SysTick_CTRL` read-modify-write clears the hardware `COUNTFLAG`
 */
driver_status_t SysTick_SetOperationState(const driver_status_t operationState);

// ==================================================================================================== //
// SysTick Current Value API
// ==================================================================================================== //

/**
 * @brief Clears the current SysTick counter value and `COUNTFLAG`
 * @details
 * Writes zero to `SysTick_VAL`. The register is an asymmetric hardware action
 * port: any write clears the current value, so an arbitrary value setter would
 * be misleading and no Get/Set conjugate is exposed.
 * @returns Nothing
 * @pre Counter operation is @ref `DRIVER_STATUS_OFF` when a deterministic new
 * timing origin is required
 */
void SysTick_ResetCurrentValue(void);

/** @} */ // SYSTICK_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SYSTICK_H_ */
