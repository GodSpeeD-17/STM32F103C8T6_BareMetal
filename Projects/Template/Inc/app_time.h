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
 * - Used by: Layer 3 `main` and Layer 2 `app_delay`
 * - Uses: Layer 1 project-owned `systick` through `app_time.c`
 *
 * @section APP_TIME_H_RESPONSIBILITY Responsibility
 * This interface provides hardware-independent initialization, operation-state
 * control, millisecond ticks, and wrap-safe elapsed-time checks. It converts
 * the hardware tick service into application timing vocabulary.
 *
 * @section APP_TIME_H_BOUNDARY Dependency Boundary
 * This header includes application configuration and shared types, but never
 * `systick.h`. Direct SysTick configuration and register access remain below
 * the application service boundary.
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

// ==================================================================================================== //
// Timebase Initialization API
// ==================================================================================================== //

#if (APP_ENABLE_SYSTICK_TIMEBASE == 1U)
/**
 * @brief Initializes the SysTick-backed application millisecond timebase
 * @details
 * Configures SysTick for @ref `APP_SYSTICK_TICK_HZ`, clears the software and
 * hardware count origins, then enables counter operation.
 * @param[in] inputClockHz SysTick processor-clock input frequency in hertz
 * Accepted values:
 * - `1U..0xFFFFFFFFU`: Frequency exactly divisible by @ref `APP_SYSTICK_TICK_HZ` with a valid 24-bit reload period
 * @returns @ref driver_status_t "Application timebase initialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The application timebase was configured, reset, and enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The input clock could not produce the configured tick frequency
 */
driver_status_t App_TimeInit(const frequency_t inputClockHz);

// ==================================================================================================== //
// Timebase Operation State APIs
// ==================================================================================================== //

// ---------------------------------------------------------------------------------------------------- //
// Timebase Operation State Pair
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
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `operationState` was invalid
 * @pre @ref App_TimeInit completed successfully before requesting
 * @ref `DRIVER_STATUS_ON`
 */
driver_status_t App_TimeSetOperationState(const driver_status_t operationState);

// ==================================================================================================== //
// Time Observation APIs
// ==================================================================================================== //

/**
 * @brief Returns milliseconds accumulated since the timebase origin
 * @returns Current 32-bit application millisecond tick count
 * @note The counter wraps after approximately 49.71 days at the configured 1 kHz rate
 * @note No arbitrary `App_TimeSetTickMs()` conjugate is exposed because
 * application time is monotonic; App_TimeInit() establishes the zero origin
 */
uint32_t App_TimeGetTickMs(void);

/**
 * @brief Calculates milliseconds elapsed from an earlier application tick
 * @param[in] startTickMs Earlier tick captured through @ref App_TimeGetTickMs
 * Accepted values:
 * - `0U..0xFFFFFFFFU`: Any previously captured 32-bit tick value
 * @returns Elapsed milliseconds modulo the 32-bit tick range
 * @note Unsigned subtraction preserves elapsed intervals across one counter wrap
 */
uint32_t App_TimeGetElapsedMs(const uint32_t startTickMs);
#endif /* APP_ENABLE_SYSTICK_TIMEBASE */

/** @} */

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* APP_TIME_H_ */
