/**
 * @file	app_time.h
 * @author	Shrey Shah
 * @brief	Declares the application monotonic millisecond service
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section APP_TIME_H_HIERARCHY Hierarchy
 * - Position: Layer 2 - Application service
 * - Used by: Layer 3 `main` and sibling Layer 2 `app_delay`
 * - Uses: Layer 1 shared SysTick Driver through `app_time.c`
 *
 * @section APP_TIME_H_RESPONSIBILITY Responsibility
 * This service converts application clock policy into a SysTick hardware
 * configuration, owns the millisecond accumulator, and publishes wrap-safe
 * elapsed-time operations. Its interrupt handler performs one increment only.
 *
 * @section APP_TIME_H_BOUNDARY Dependency Boundary
 * This header exposes application timing vocabulary and the processor-required
 * handler ABI. It never includes `systick.h`; hardware state remains below the
 * service boundary, and the SysTick Driver never includes an application file.
 */

// Header Guard
#ifndef APP_TIME_H_
#define APP_TIME_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "app_config.h"
#include "stm32f1xx_data_types.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Application monotonic millisecond service
 * @defgroup APP_Time Application Time
 * @ingroup APP_Template
 * @{
 */

#if (APP_ENABLE_SYSTICK_TIMEBASE == 1U)

// ==================================================================================================== //
// Application Timebase Initialization API
// ==================================================================================================== //

/**
 * @brief Initializes the SysTick-backed application millisecond timebase
 * @details
 * Derives the register-semantic reload value, resets SysTick hardware, applies
 * root configuration, establishes a zero software/hardware origin, enables the
 * SysTick exception source, and starts counter operation in that order.
 * @param[in] inputClockHz Undivided processor-clock frequency in hertz
 * Accepted values:
 * - `1U..0xFFFFFFFFU`: Exact multiple of @ref `APP_SYSTICK_TICK_HZ` producing a 24-bit reload value
 * @returns @ref driver_status_t "Application timebase initialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timebase hardware and software state were initialized
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `inputClockHz` cannot represent the configured millisecond tick
 */
driver_status_t App_TimeInit(const frequency_t inputClockHz);

// ==================================================================================================== //
// Application Timebase Operation State APIs
// ==================================================================================================== //

// ---------------------------------------------------------------------------------------------------- //
// Application Timebase Operation State Pair
// ---------------------------------------------------------------------------------------------------- //

/**
 * @brief Returns the application timebase operation state
 * @returns @ref driver_status_t "Application timebase operation state"
 * @retval - @ref `DRIVER_STATUS_OFF`: SysTick counter operation is disabled
 * @retval - @ref `DRIVER_STATUS_ON`: SysTick counter operation is enabled
 */
driver_status_t App_TimeGetOperationState(void);

/**
 * @brief Sets the application timebase operation state
 * @param[in] operationState Requested application timebase operation state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disable timebase counter operation
 * - @ref `DRIVER_STATUS_ON`: Enable configured timebase counter operation
 * @returns @ref driver_status_t "Application timebase operation-state update status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timebase operation state was updated
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `operationState` is invalid
 * @pre App_TimeInit() completed successfully before requesting @ref `DRIVER_STATUS_ON`
 */
driver_status_t App_TimeSetOperationState(const driver_status_t operationState);

// ==================================================================================================== //
// Application Time Observation APIs
// ==================================================================================================== //

/**
 * @brief Returns milliseconds accumulated since the application timebase origin
 * @returns Current 32-bit application millisecond tick count
 * @note The counter wraps after approximately 49.71 days at one kilohertz
 * @note An arbitrary setter is not exposed because this service is monotonic;
 * App_TimeInit() alone establishes its zero origin
 */
uint32_t App_TimeGetTickMs(void);

/**
 * @brief Calculates milliseconds elapsed from an earlier application tick
 * @param[in] startTickMs Earlier tick captured through App_TimeGetTickMs()
 * Accepted values:
 * - `0U..0xFFFFFFFFU`: Any previously captured 32-bit tick value
 * @returns Elapsed milliseconds modulo the 32-bit tick range
 * @note Unsigned subtraction remains valid across one counter wrap
 */
uint32_t App_TimeGetElapsedMs(const uint32_t startTickMs);

// ==================================================================================================== //
// Application Timebase Interrupt Handler
// ==================================================================================================== //

/**
 * @brief Advances the application millisecond timebase by one tick
 * @details
 * This strong application-owned definition overrides the weak startup fallback
 * when the timebase feature is compiled. It performs exactly one increment and
 * defers all application work to main context.
 * @returns Nothing
 */
void SysTick_Handler(void);

#endif /* APP_ENABLE_SYSTICK_TIMEBASE */

/** @} */ // APP_Time

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* APP_TIME_H_ */
