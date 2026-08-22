#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>

#include "stm32f1xx_data_types.h"

/**
 * @brief Configures SysTick as an interrupt-driven application timebase
 * @details
 * Leaves the counter disabled after programming the clock source, interrupt
 * source, reload value, and current counter state.
 * @param[in] inputClockHz SysTick core-clock input frequency in hertz
 * Accepted values:
 * - `1U..0xFFFFFFFFU`: Non-zero core-clock frequency
 * @param[in] tickFrequencyHz Requested application tick frequency in hertz
 * Accepted values:
 * - `1U..inputClockHz`: Exact divisor producing a reload value of `1U..0x1000000U`
 * @returns @ref driver_status_t "SysTick configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: SysTick was configured and left disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A frequency was zero, inexact, or outside the 24-bit reload range
 */
driver_status_t SysTick_Config
(
	const frequency_t inputClockHz,
	const frequency_t tickFrequencyHz
);

/** @brief Enables the configured SysTick counter @returns Nothing */
void SysTick_Enable(void);

/** @brief Disables the SysTick counter @returns Nothing */
void SysTick_Disable(void);

/**
 * @brief Returns the application tick count accumulated by SysTick
 * @returns Current 32-bit application tick count
 * @note An aligned 32-bit read is atomic on the Cortex-M3
 */
uint32_t SysTick_GetTicks(void);

/**
 * @brief Resets the application tick count and current SysTick counter value
 * @returns Nothing
 * @pre SysTick is disabled
 */
void SysTick_ResetTicks(void);

/**
 * @brief Returns the current SysTick counter-operation state
 * @returns @ref driver_status_t "SysTick operation state"
 * @retval - @ref `DRIVER_STATUS_OFF`: SysTick counter operation is disabled
 * @retval - @ref `DRIVER_STATUS_ON`: SysTick counter operation is enabled
 */
driver_status_t SysTick_GetOperationState(void);

/**
 * @brief Advances the application timebase by one tick
 * @returns Nothing
 * @note Interrupt work is intentionally limited to the tick increment
 */
void SysTick_Handler(void);

#endif /* SYSTICK_H_ */
