#ifndef APP_TIME_H_
#define APP_TIME_H_

#include <stdint.h>

#include "app_config.h"
#include "stm32f1xx_data_types.h"

#if (APP_ENABLE_SYSTICK_TIMEBASE == 1U)
/**
 * @brief Initializes the SysTick-backed application millisecond timebase
 * @param[in] inputClockHz SysTick core-clock input frequency in hertz
 * Accepted values:
 * - `1U..0xFFFFFFFFU`: Clock frequency exactly divisible by APP_SYSTICK_TICK_HZ
 * @returns @ref driver_status_t "Application timebase initialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The application timebase was configured, reset, and enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The clock could not produce the configured tick frequency
 */
driver_status_t App_TimeInit(const frequency_t inputClockHz);

/**
 * @brief Returns the application timebase operation state
 * @returns @ref driver_status_t "Application timebase operation state"
 * @retval - @ref `DRIVER_STATUS_OFF`: The application timebase is disabled
 * @retval - @ref `DRIVER_STATUS_ON`: The application timebase is enabled
 */
driver_status_t App_TimeGetOperationState(void);

/**
 * @brief Returns milliseconds elapsed since the application timebase started
 * @returns Current 32-bit millisecond tick count
 * @note The counter wraps after approximately 49.7 days
 */
uint32_t App_TimeGetTickMs(void);

/**
 * @brief Calculates milliseconds elapsed from an earlier application tick
 * @param[in] startTickMs Earlier tick captured through App_TimeGetTickMs
 * @returns Milliseconds elapsed modulo the 32-bit tick range
 * @note Unsigned subtraction preserves intervals across one counter wrap
 */
uint32_t App_TimeGetElapsedMs(const uint32_t startTickMs);

#endif /* APP_ENABLE_SYSTICK_TIMEBASE */

#endif /* APP_TIME_H_ */
