#ifndef APP_DELAY_H_
#define APP_DELAY_H_

#include <stdint.h>

#include "app_config.h"
#include "stm32f1xx_data_types.h"

/**
 * @brief Provides a blocking millisecond delay using the SysTick application timebase
 * @param[in] delayMs Requested delay in milliseconds
 * Accepted values:
 * - `1U..0x7FFFFFFFU`: Minimum blocking delay duration
 * @returns @ref driver_status_t "Application millisecond-delay status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The requested tick interval elapsed
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p delayMs was zero or exceeded the wrap-safe interval range
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: SysTick was disabled, the call originated in an exception, or global interrupts were disabled
 * @pre App_Init successfully configured and enabled the SysTick timebase
 * @note The 32-bit subtraction remains correct when the tick counter wraps
 */
driver_status_t App_DelayMs(const uint32_t delayMs);

#if (APP_ENABLE_TIMER_US_DELAY == 1U)
/**
 * @brief Initializes the optional dedicated Timer microsecond-delay service
 * @returns @ref driver_status_t "Application Timer-delay initialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The Timer clock and 1 MHz blocking-delay configuration were applied
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The configured Timer or clock mask was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The Timer kernel clock did not satisfy the delay contract
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: The configured Timer was running
 */
driver_status_t App_DelayTimerInit(void);

/**
 * @brief Provides a blocking microsecond delay using the optional dedicated Timer
 * @param[in] delayUs Requested delay in microseconds
 * Accepted values:
 * - `1U..0xFFFFFFFFU`: Delay composed from bounded 16-bit Timer intervals
 * @returns @ref driver_status_t "Application microsecond-delay status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Every requested Timer interval completed
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p delayUs was zero or the Timer configuration was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The dedicated Timer clock was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A Timer interval did not complete within its polling budget
 */
driver_status_t App_DelayUs(const uint32_t delayUs);
#endif /* APP_ENABLE_TIMER_US_DELAY */

#endif /* APP_DELAY_H_ */
