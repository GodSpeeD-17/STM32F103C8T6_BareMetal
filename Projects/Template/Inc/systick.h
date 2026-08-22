/**
 * @file	systick.h
 * @author	Shrey Shah
 * @brief	Declares the project-owned SysTick hardware service
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section SYSTICK_H_HIERARCHY Hierarchy
 * - Position: Layer 1 - Project hardware access
 * - Used by: Layer 2 `app_time` through `app_time.c`
 * - Uses: Cortex-M3 SysTick registers through `systick.c`
 *
 * @section SYSTICK_H_RESPONSIBILITY Responsibility
 * This interface controls SysTick configuration and operation, publishes the
 * tick accumulator, and declares the minimal increment-only interrupt handler.
 *
 * @section SYSTICK_H_BOUNDARY Dependency Boundary
 * Application code includes `app_time.h`, not this header. This module never
 * includes or calls `app_time`, so the hardware-to-service dependency cannot
 * become circular.
 */

// Header Guard
#ifndef SYSTICK_H_
#define SYSTICK_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "stm32f1xx_data_types.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Project-owned SysTick hardware service
 * @defgroup APP_SysTick Application SysTick
 * @ingroup APP_Template
 * @{
 */

// ==================================================================================================== //
// Configuration APIs
// ==================================================================================================== //

/**
 * @brief Configures SysTick as an interrupt-driven application timebase
 * @details
 * Stops counter operation, writes `LOAD = (inputClockHz / tickFrequencyHz) - 1`,
 * clears `VAL`, selects the processor clock, enables the SysTick interrupt
 * source, and leaves the counter disabled. SysTick is a Cortex-M exception and
 * therefore requires no NVIC enable transaction.
 * @param[in] inputClockHz SysTick processor-clock input frequency in hertz
 * Accepted values:
 * - `1U..0xFFFFFFFFU`: Non-zero processor-clock frequency
 * @param[in] tickFrequencyHz Requested application tick frequency in hertz
 * Accepted values:
 * - `1U..inputClockHz`: Exact divisor producing a reload period in `1U..0x1000000U`
 * @returns @ref driver_status_t "SysTick configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: SysTick was configured and left disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A frequency was zero, inexact, or outside the 24-bit reload range
 * @note The software tick count is preserved; call @ref SysTick_ResetTicks when a zero origin is required
 * @note No `SysTick_GetConfig()` conjugate is exposed because SysTick stores a
 * reload period, not the original input-clock and requested-frequency pair;
 * reconstructing that pair would require hidden state or an RCC dependency
 */
driver_status_t SysTick_SetConfig(const frequency_t inputClockHz, const frequency_t tickFrequencyHz);

// ==================================================================================================== //
// Counter Operation State APIs
// ==================================================================================================== //

// ---------------------------------------------------------------------------------------------------- //
// Counter Operation State Pair
// ---------------------------------------------------------------------------------------------------- //

/**
 * @brief Returns the current SysTick counter-operation state
 * @returns @ref driver_status_t "SysTick operation state"
 * @retval - @ref `DRIVER_STATUS_OFF`: SysTick counter operation is disabled
 * @retval - @ref `DRIVER_STATUS_ON`: SysTick counter operation is enabled
 */
driver_status_t SysTick_GetOperationState(void);

/**
 * @brief Sets the SysTick counter-operation state
 * @details
 * Clears or sets only `SysTick_CTRL.ENABLE`; clock-source and interrupt-enable
 * fields remain unchanged.
 * @param[in] operationState Requested SysTick counter-operation state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disable counter operation
 * - @ref `DRIVER_STATUS_ON`: Enable configured counter operation
 * @returns @ref driver_status_t "SysTick operation-state update status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter operation state was updated
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `operationState` was invalid
 * @pre @ref SysTick_SetConfig completed successfully before requesting
 * @ref `DRIVER_STATUS_ON`
 */
driver_status_t SysTick_SetOperationState(const driver_status_t operationState);

// ==================================================================================================== //
// Tick Accumulator APIs
// ==================================================================================================== //

// ---------------------------------------------------------------------------------------------------- //
// Tick Reset and Read Operations
// ---------------------------------------------------------------------------------------------------- //

/**
 * @brief Resets the software tick count and current SysTick counter value
 * @details Clears both the software tick accumulator and `SysTick_VAL`.
 * @returns Nothing
 * @pre Counter operation is @ref `DRIVER_STATUS_OFF`
 */
void SysTick_ResetTicks(void);

/**
 * @brief Returns the application tick count accumulated by SysTick
 * @returns Current 32-bit application tick count
 * @note An aligned 32-bit read is atomic on the Cortex-M3
 * @note No arbitrary `SysTick_SetTicks()` conjugate is exposed because only
 * SysTick_Handler() may advance the monotonic count; SysTick_ResetTicks()
 * establishes its zero origin while counter operation is disabled
 */
uint32_t SysTick_GetTicks(void);

// ==================================================================================================== //
// Interrupt Handler API
// ==================================================================================================== //

/**
 * @brief Advances the application timebase by one tick
 * @details Increments only the software tick accumulator and performs no other work.
 * @returns Nothing
 * @note Interrupt work is intentionally limited to one counter increment
 */
void SysTick_Handler(void);

/** @} */ // APP_SysTick

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SYSTICK_H_ */
