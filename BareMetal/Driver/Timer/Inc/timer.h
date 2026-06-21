/**
 * @file	timer.h
 * @author	Shrey Shah
 * @brief	Timer Driver Public Interface
 * @version	v1.0
 * @date	20-06-2026
 *
 * @details
 * This header exposes the public Timer driver API for the first Timer
 * refactor pass. Public code sees Timer configuration structures, public
 * selectors, validation macros, and driver entry points. Low-level register
 * access and codec image staging remain private to `timer.c`.
 *
 * This API pass is intentionally limited to the fields owned by
 * @ref `timer_config_t`:
 * - `TIMx_CR1` counter behavior fields
 * - `TIMx_PSC` counter tick prescaler
 * - `TIMx_ARR` auto-reload value
 * - `TIMx_CNT` counter value
 *
 * Channel/PWM, IRQ/NVIC, DMA, master/slave, and delay helper APIs are outside
 * this public header scope for this pass.
 */

#ifndef TIMER_H_
#define TIMER_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "timer_config.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup TIM_03_Driver
 * @{
 */

// ==================================================================================================== //
//										Timer Clock State APIs											//
// ==================================================================================================== //

// -------------------------------------- Timer Clock State Pair -------------------------------------- //

/**
 * @brief Gets the APB1 clock-gate state for one supported Timer instance
 * @details
 * Reads only the RCC APB1 clock-enable bit for @p TIMx. This API does not read
 * or write Timer registers, does not modify `TIMx_CR1.CEN`, and does not reset
 * the Timer peripheral.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @returns Timer clock-gate state or driver error status
 * @retval - @ref `DRIVER_STATUS_OFF`: Timer APB1 clock gate is disabled.
 * @retval - @ref `DRIVER_STATUS_ON`: Timer APB1 clock gate is enabled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 */
driver_status_t TIM_GetClockState(TIM_TypeDef* const TIMx);

/**
 * @brief Sets the APB1 clock-gate state for one supported Timer instance
 * @details
 * Sets or clears only the RCC APB1 clock-enable bit for @p TIMx. This API
 * makes Timer registers accessible when @p clockState is @ref `DRIVER_STATUS_ON`,
 * but it does not start or stop the Timer counter and does not modify Timer
 * configuration registers.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[in] clockState Requested Timer clock-gate state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disable the APB1 Timer clock gate.
 * - @ref `DRIVER_STATUS_ON`: Enable the APB1 Timer clock gate.
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer APB1 clock gate was updated.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p clockState was invalid.
 */
driver_status_t TIM_SetClockState(TIM_TypeDef* const TIMx, const driver_status_t clockState);

// ==================================================================================================== //
//										Timer Operation State APIs										//
// ==================================================================================================== //

// ------------------------------------ Timer Operation State Pair ------------------------------------ //

/**
 * @brief Gets the counter operation state for one supported Timer instance
 * @details
 * Reads only `TIMx_CR1.CEN` through the codec layer. This API does not enable
 * or disable the APB1 Timer clock gate and does not modify Timer configuration
 * registers.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @returns Timer counter operation state or driver error status
 * @retval - @ref `DRIVER_STATUS_OFF`: Timer counter operation is disabled.
 * @retval - @ref `DRIVER_STATUS_ON`: Timer counter operation is enabled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 * @pre @ref `TIM_SetClockState` has enabled the APB1 clock gate for @p TIMx.
 */
driver_status_t TIM_GetOperationState(TIM_TypeDef* const TIMx);

/**
 * @brief Sets the counter operation state for one supported Timer instance
 * @details
 * Sets or clears only `TIMx_CR1.CEN` through the codec layer while preserving
 * all other `TIMx_CR1` fields. This API does not enable or disable the APB1
 * Timer clock gate.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[in] operationState Requested Timer counter operation state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disable Timer counter operation.
 * - @ref `DRIVER_STATUS_ON`: Enable Timer counter operation.
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer counter operation state was updated.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p operationState was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 * @pre @ref `TIM_SetClockState` has enabled the APB1 clock gate for @p TIMx.
 */
driver_status_t TIM_SetOperationState(TIM_TypeDef* const TIMx, const driver_status_t operationState);

// ==================================================================================================== //
//										Timer Root Configuration APIs									//
// ==================================================================================================== //

// ---------------------------------- Timer Root Configuration Pair ----------------------------------- //

/**
 * @brief Restores the Timer configuration fields owned by this API pass
 * @details
 * Restores the register fields represented by @ref `timer_config_t` back to
 * their reset/default raw values. The driver validates @p TIMx, enables the
 * APB1 Timer clock gate with @ref `TIM_SetClockState`, disables the counter
 * with @ref `TIM_SetOperationState`, stages reset images, writes only changed
 * register images, and disables the Timer clock gate with
 * @ref `TIM_SetClockState` when de-configuration completes.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer configuration fields were restored.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 * @note This API is limited to the fields represented by @ref `timer_config_t`.
 * Channel/PWM, IRQ/NVIC, DMA, master/slave, and delay-helper state are not part
 * of this de-configuration scope.
 * @note This API does not issue an RCC peripheral reset.
 */
driver_status_t TIM_DeConfig(TIM_TypeDef* const TIMx);

/**
 * @brief Configures one supported general-purpose Timer instance
 * @details
 * Applies every field contained in @ref `timer_config_t`. The driver validates
 * @p TIMx, enables the APB1 Timer clock gate with @ref `TIM_SetClockState`,
 * disables the counter with @ref `TIM_SetOperationState`, stages register
 * images through the codec layer, and writes only changed register images.
 * `TIMx_CR1`, `TIMx_PSC`, and `TIMx_ARR` are applied before a software update
 * event is generated with `TIMx_EGR.UG`; `TIMx_CNT` is applied after that
 * update event so the requested initial counter value is preserved.
 *
 * The generated update event latches the prescaler and any preloaded
 * auto-reload value into the active Timer logic. If `TIMx_SR.UIF` was clear
 * before the generated update event and becomes pending afterward, the driver
 * clears that generated update flag before returning. A pre-existing pending
 * `TIMx_SR.UIF` flag is preserved.
 *
 * This API stages:
 * - `TIMx_CR1` fields represented by @ref `timer_config_counter_t`
 * - `TIMx_PSC` from @ref `timer_config_timebase_t::prescaler`
 * - `TIMx_ARR` from @ref `timer_config_timebase_t::auto_reload`
 * - `TIMx_CNT` from @ref `timer_config_timebase_t::initial_count`
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[in] pConfig Timer root configuration
 * Accepted values:
 * - Non-`NULL`: Complete Timer configuration object
 * - @ref `timer_config_t::timebase`: Timer prescaler, auto-reload, and initial counter values
 * - @ref `timer_config_t::counter`: Timer counter behavior selectors
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer configuration was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pConfig was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or one or more configuration fields were invalid.
 * @note This API does not configure channel/PWM, IRQ/NVIC, DMA, master/slave,
 * or delay-helper state.
 * @note This API leaves the Timer counter disabled. Use
 * @ref `TIM_SetOperationState` with @ref `DRIVER_STATUS_ON` to start the
 * counter after configuration.
 */
driver_status_t TIM_Config(TIM_TypeDef* const TIMx, const timer_config_t* const pConfig);

// ==================================================================================================== //
//										Timer Group Configuration APIs									//
// ==================================================================================================== //

// -------------------------------- Timer TimeBase Configuration Pair --------------------------------- //

/**
 * @brief Extracts the Timer timebase configuration
 * @details
 * Reads only the Timer registers required for @ref `timer_config_timebase_t`.
 * The current `TIMx_PSC`, `TIMx_ARR`, and `TIMx_CNT` values are returned
 * through @ref `timer_config_timebase_t`. Use @ref `TIM_GetFrequency` when the
 * derived counter tick frequency is required.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[out] pTimeBase Destination for the current Timer timebase configuration
 * Expected values:
 * - Non-`NULL`: TimeBase configuration is written to @p pTimeBase
 * - @ref `timer_config_timebase_t::prescaler`: Current `TIMx_PSC` value
 * - @ref `timer_config_timebase_t::auto_reload`: Current `TIMx_ARR` value
 * - @ref `timer_config_timebase_t::initial_count`: Current `TIMx_CNT` value
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: TimeBase configuration was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pTimeBase was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetTimeBaseConfig
(
	TIM_TypeDef* const					TIMx,
	timer_config_timebase_t* const		pTimeBase
);

/**
 * @brief Configures the Timer timebase fields
 * @details
 * Applies @ref `timer_config_timebase_t::prescaler` to `TIMx_PSC`,
 * @ref `timer_config_timebase_t::auto_reload` to `TIMx_ARR`, and
 * @ref `timer_config_timebase_t::initial_count` to `TIMx_CNT`. Each register is
 * written only when the staged value differs from the current hardware image.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[in] pTimeBase Timer timebase configuration
 * Accepted values:
 * - Non-`NULL`: TimeBase configuration to apply
 * - @ref `timer_config_timebase_t::prescaler`: Value staged into `TIMx_PSC`
 * - @ref `timer_config_timebase_t::auto_reload`: Value staged into `TIMx_ARR`
 * - @ref `timer_config_timebase_t::initial_count`: Value staged into `TIMx_CNT`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: TimeBase configuration was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pTimeBase was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or one or more timebase fields were invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 * @note This API does not modify `TIMx_CR1` counter behavior fields.
 */
driver_status_t TIM_SetTimeBaseConfig
(
	TIM_TypeDef* const						TIMx,
	const timer_config_timebase_t* const	pTimeBase
);

// --------------------------------- Timer Counter Configuration Pair --------------------------------- //

/**
 * @brief Extracts the Timer counter behavior configuration
 * @details
 * Reads `TIMx_CR1` and extracts only the fields represented by
 * @ref `timer_config_counter_t`.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[out] pCounter Destination for the current Timer counter configuration
 * Expected values:
 * - Non-`NULL`: Counter configuration is written to @p pCounter
 * - @ref `timer_config_counter_t::direction`: @ref `TIMx_DIR_COUNT_UP` or @ref `TIMx_DIR_COUNT_DOWN`
 * - @ref `timer_config_counter_t::alignment`: @ref `TIMx_MODE_NORMAL`,
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING`,
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING`, or
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING`
 * - @ref `timer_config_counter_t::one_pulse`: @ref `TIMx_OPM_DISABLE` or @ref `TIMx_OPM_ENABLE`
 * - @ref `timer_config_counter_t::auto_reload_preload`: @ref `TIMx_ARPE_DISABLE` or @ref `TIMx_ARPE_ENABLE`
 * - @ref `timer_config_counter_t::update_source`: @ref `TIMx_UPDATE_SOURCE_ANY` or @ref `TIMx_UPDATE_SOURCE_OVF_DMA`
 * - @ref `timer_config_counter_t::clock_division`: @ref `TIMx_CKD_CLK_FREQ`,
 *   @ref `TIMx_CKD_CLK_2_FREQ`, or @ref `TIMx_CKD_CLK_4_FREQ`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter configuration was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCounter was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid, or `TIMx_CR1` contained a field value outside the public Timer vocabulary.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 * @note Counter enable state and update-event enable state are not part of
 * @ref `timer_config_counter_t`.
 */
driver_status_t TIM_GetCounterConfig
(
	TIM_TypeDef* const					TIMx,
	timer_config_counter_t* const		pCounter
);

/**
 * @brief Configures the Timer counter behavior fields
 * @details
 * Stages @ref `timer_config_counter_t` into the `TIMx_CR1` image and writes
 * `TIMx_CR1` only when the staged image differs from the current hardware
 * image. Counter enable state and update-event enable state are preserved.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[in] pCounter Timer counter configuration
 * Accepted values:
 * - Non-`NULL`: Counter configuration to apply
 * - @ref `timer_config_counter_t::direction`: @ref `TIMx_DIR_COUNT_UP` or @ref `TIMx_DIR_COUNT_DOWN`
 * - @ref `timer_config_counter_t::alignment`: @ref `TIMx_MODE_NORMAL`,
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING`,
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING`, or
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING`
 * - @ref `timer_config_counter_t::one_pulse`: @ref `TIMx_OPM_DISABLE` or @ref `TIMx_OPM_ENABLE`
 * - @ref `timer_config_counter_t::auto_reload_preload`: @ref `TIMx_ARPE_DISABLE` or @ref `TIMx_ARPE_ENABLE`
 * - @ref `timer_config_counter_t::update_source`: @ref `TIMx_UPDATE_SOURCE_ANY` or @ref `TIMx_UPDATE_SOURCE_OVF_DMA`
 * - @ref `timer_config_counter_t::clock_division`: @ref `TIMx_CKD_CLK_FREQ`,
 *   @ref `TIMx_CKD_CLK_2_FREQ`, or @ref `TIMx_CKD_CLK_4_FREQ`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter configuration was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCounter was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or one or more counter fields were invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_SetCounterConfig
(
	TIM_TypeDef* const						TIMx,
	const timer_config_counter_t* const		pCounter
);

// ==================================================================================================== //
//										Timer TimeBase Field APIs										//
// ==================================================================================================== //

/**
 * @brief Returns the current Timer counter tick frequency
 * @details
 * Reads `TIMx_PSC` and derives the counter tick frequency from the Timer input
 * clock and prescaler value.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[out] pFrequency Destination for the derived counter tick frequency in hertz
 * Expected values:
 * - Non-`NULL`: Derived counter tick frequency in hertz is written to @p pFrequency
 * - `0U..0xFFFFFFFFU`: Any value representable by @ref `timer_frequency_t`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter tick frequency was derived.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pFrequency was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled, or the Timer input clock could not be derived.
 * @note This is a derived convenience getter. Frequency is not stored in
 * @ref `timer_config_t`.
 */
driver_status_t TIM_GetFrequency
(
	TIM_TypeDef* const			TIMx,
	timer_frequency_t* const	pFrequency
);

// --------------------------------------- Timer Prescaler Pair --------------------------------------- //

/**
 * @brief Returns the current Timer prescaler value
 * @details
 * Reads the register-backed `TIMx_PSC` value directly. Use
 * @ref `TIM_GetFrequency` when the derived counter tick frequency is required.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[out] pPrescaler Destination for the current `TIMx_PSC` value
 * Expected values:
 * - Non-`NULL`: Current `TIMx_PSC[15:0]` value is written to @p pPrescaler
 * - `0x0000U..0xFFFFU`: Any value representable by @ref `timer_prescaler_t`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Prescaler value was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPrescaler was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetPrescaler
(
	TIM_TypeDef* const			TIMx,
	timer_prescaler_t* const	pPrescaler
);

/**
 * @brief Configures the Timer prescaler value
 * @details
 * Writes only `TIMx_PSC` if @p prescaler differs from the current hardware
 * image.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[in] prescaler Prescaler value staged into `TIMx_PSC`
 * Accepted values:
 * - `0x0000U..0xFFFFU`: Any value representable by @ref `timer_prescaler_t`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Prescaler value was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p prescaler was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 * @note This API updates only `TIMx_PSC`; it does not modify `TIMx_ARR`,
 * `TIMx_CNT`, or `TIMx_CR1`.
 */
driver_status_t TIM_SetPrescaler
(
	TIM_TypeDef* const			TIMx,
	const timer_prescaler_t		prescaler
);

// -------------------------------------- Timer Auto-Reload Pair -------------------------------------- //

/**
 * @brief Returns the current Timer auto-reload value
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[out] pAutoReload Destination for the current `TIMx_ARR` value
 * Expected values:
 * - Non-`NULL`: Current `TIMx_ARR[15:0]` value is written to @p pAutoReload
 * - `0x0000U..0xFFFFU`: Any value representable by @ref `timer_auto_reload_t`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload value was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pAutoReload was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetAutoReload
(
	TIM_TypeDef* const			TIMx,
	timer_auto_reload_t* const	pAutoReload
);

/**
 * @brief Configures the Timer auto-reload value
 * @details
 * Writes only `TIMx_ARR` if @p autoReload differs from the current hardware
 * image.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[in] autoReload Auto-reload value staged into `TIMx_ARR`
 * Accepted values:
 * - `0x0000U..0xFFFFU`: Any value representable by @ref `timer_auto_reload_t`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload value was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p autoReload was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 * @note This API updates only `TIMx_ARR`; it does not modify `TIMx_PSC`,
 * `TIMx_CNT`, or `TIMx_CR1`.
 */
driver_status_t TIM_SetAutoReload
(
	TIM_TypeDef* const				TIMx,
	const timer_auto_reload_t		autoReload
);

// ------------------------------------- Timer Counter Value Pair ------------------------------------- //

/**
 * @brief Returns the current Timer counter value
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[out] pCounterValue Destination for the current `TIMx_CNT` value
 * Expected values:
 * - Non-`NULL`: Current `TIMx_CNT[15:0]` value is written to @p pCounterValue
 * - `0x0000U..0xFFFFU`: Any value representable by @ref `timer_counter_value_t`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter value was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCounterValue was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetCounterValue
(
	TIM_TypeDef* const				TIMx,
	timer_counter_value_t* const	pCounterValue
);

/**
 * @brief Configures the Timer counter value
 * @details
 * Writes only `TIMx_CNT` if @p counterValue differs from the current hardware
 * image.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[in] counterValue Counter value staged into `TIMx_CNT`
 * Accepted values:
 * - `0x0000U..0xFFFFU`: Any value representable by @ref `timer_counter_value_t`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter value was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p counterValue was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 * @note This API updates only `TIMx_CNT`; it does not modify `TIMx_PSC`,
 * `TIMx_ARR`, or `TIMx_CR1`.
 */
driver_status_t TIM_SetCounterValue
(
	TIM_TypeDef* const				TIMx,
	const timer_counter_value_t		counterValue
);

// ==================================================================================================== //
//										Timer Counter Field APIs										//
// ==================================================================================================== //

// --------------------------------------- Timer Direction Pair --------------------------------------- //

/**
 * @brief Returns the current Timer counter direction selector
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[out] pDirection Destination for the current direction selector
 * Expected values:
 * - @ref `TIMx_DIR_COUNT_UP`: Counter counts up
 * - @ref `TIMx_DIR_COUNT_DOWN`: Counter counts down
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Direction selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pDirection was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid, or `TIMx_CR1` could not be decoded.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetDirection
(
	TIM_TypeDef* const				TIMx,
	timer_direction_t* const		pDirection
);

/**
 * @brief Configures the Timer counter direction selector
 * @details
 * Stages only the counter direction field in `TIMx_CR1` and writes `TIMx_CR1`
 * only when the staged image differs from the current hardware image.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[in] direction Timer counter direction selector
 * Accepted values:
 * - @ref `TIMx_DIR_COUNT_UP`: Counter counts up
 * - @ref `TIMx_DIR_COUNT_DOWN`: Counter counts down
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Direction selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p direction was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_SetDirection
(
	TIM_TypeDef* const			TIMx,
	const timer_direction_t		direction
);

// --------------------------------------- Timer Alignment Pair --------------------------------------- //

/**
 * @brief Returns the current Timer counter alignment selector
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[out] pAlignment Destination for the current edge/center-aligned selector
 * Expected values:
 * - @ref `TIMx_MODE_NORMAL`: Edge-aligned mode
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING`: Center-aligned mode 1
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING`: Center-aligned mode 2
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING`: Center-aligned mode 3
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Alignment selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pAlignment was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid, or `TIMx_CR1.CMS` could not be decoded.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetAlignment
(
	TIM_TypeDef* const				TIMx,
	timer_count_mode_t* const		pAlignment
);

/**
 * @brief Configures the Timer counter alignment selector
 * @details
 * Stages only `TIMx_CR1.CMS[1:0]` and writes `TIMx_CR1` only when the staged
 * image differs from the current hardware image.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[in] alignment Timer edge/center-aligned selector
 * Accepted values:
 * - @ref `TIMx_MODE_NORMAL`: Edge-aligned mode
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING`: Center-aligned mode 1
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING`: Center-aligned mode 2
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING`: Center-aligned mode 3
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Alignment selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p alignment was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 * @warning STM32F1 does not allow switching from edge-aligned to center-aligned
 * mode while the counter is enabled.
 */
driver_status_t TIM_SetAlignment
(
	TIM_TypeDef* const			TIMx,
	const timer_count_mode_t	alignment
);

// --------------------------------------- Timer One-Pulse Pair --------------------------------------- //

/**
 * @brief Returns the current Timer one-pulse mode selector
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[out] pOnePulse Destination for the current one-pulse selector
 * Expected values:
 * - @ref `TIMx_OPM_DISABLE`: Counter is not stopped at the next update event
 * - @ref `TIMx_OPM_ENABLE`: Counter stops at the next update event
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: One-pulse selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pOnePulse was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid, or `TIMx_CR1.OPM` could not be decoded.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetOnePulse
(
	TIM_TypeDef* const			TIMx,
	timer_opm_t* const			pOnePulse
);

/**
 * @brief Configures the Timer one-pulse mode selector
 * @details
 * Stages only `TIMx_CR1.OPM` and writes `TIMx_CR1` only when the staged image
 * differs from the current hardware image.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[in] onePulse Timer one-pulse selector
 * Accepted values:
 * - @ref `TIMx_OPM_DISABLE`: Counter is not stopped at the next update event
 * - @ref `TIMx_OPM_ENABLE`: Counter stops at the next update event
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: One-pulse selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p onePulse was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_SetOnePulse
(
	TIM_TypeDef* const			TIMx,
	const timer_opm_t			onePulse
);

// ---------------------------------- Timer Auto-Reload Preload Pair ---------------------------------- //

/**
 * @brief Returns the current Timer auto-reload preload selector
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[out] pAutoReloadPreload Destination for the current auto-reload preload selector
 * Expected values:
 * - @ref `TIMx_ARPE_DISABLE`: Auto-reload preload is disabled
 * - @ref `TIMx_ARPE_ENABLE`: Auto-reload preload is enabled
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload preload selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pAutoReloadPreload was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid, or `TIMx_CR1.ARPE` could not be decoded.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetAutoReloadPreload
(
	TIM_TypeDef* const			TIMx,
	timer_arpe_t* const			pAutoReloadPreload
);

/**
 * @brief Configures the Timer auto-reload preload selector
 * @details
 * Stages only `TIMx_CR1.ARPE` and writes `TIMx_CR1` only when the staged image
 * differs from the current hardware image.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[in] autoReloadPreload Timer auto-reload preload selector
 * Accepted values:
 * - @ref `TIMx_ARPE_DISABLE`: Auto-reload preload is disabled
 * - @ref `TIMx_ARPE_ENABLE`: Auto-reload preload is enabled
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload preload selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p autoReloadPreload was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_SetAutoReloadPreload
(
	TIM_TypeDef* const			TIMx,
	const timer_arpe_t			autoReloadPreload
);

// ------------------------------------- Timer Update Source Pair ------------------------------------- //

/**
 * @brief Returns the current Timer update request source selector
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[out] pUpdateSource Destination for the current update request source selector
 * Expected values:
 * - @ref `TIMx_UPDATE_SOURCE_ANY`: Any update source may generate an update request
 * - @ref `TIMx_UPDATE_SOURCE_OVF_DMA`: Only overflow/underflow or DMA source generates an update request
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Update request source selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pUpdateSource was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid, or `TIMx_CR1.URS` could not be decoded.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetUpdateSource
(
	TIM_TypeDef* const				TIMx,
	timer_update_source_t* const	pUpdateSource
);

/**
 * @brief Configures the Timer update request source selector
 * @details
 * Stages only `TIMx_CR1.URS` and writes `TIMx_CR1` only when the staged image
 * differs from the current hardware image.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[in] updateSource Timer update request source selector
 * Accepted values:
 * - @ref `TIMx_UPDATE_SOURCE_ANY`: Any update source may generate an update request
 * - @ref `TIMx_UPDATE_SOURCE_OVF_DMA`: Only overflow/underflow or DMA source generates an update request
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Update request source selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p updateSource was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_SetUpdateSource
(
	TIM_TypeDef* const			TIMx,
	const timer_update_source_t	updateSource
);

// ------------------------------------ Timer Clock Division Pair ------------------------------------- //

/**
 * @brief Returns the current Timer clock division selector
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[out] pClockDivision Destination for the current clock division selector
 * Expected values:
 * - @ref `TIMx_CKD_CLK_FREQ`: `t_DTS = t_CK_INT`
 * - @ref `TIMx_CKD_CLK_2_FREQ`: `t_DTS = 2 * t_CK_INT`
 * - @ref `TIMx_CKD_CLK_4_FREQ`: `t_DTS = 4 * t_CK_INT`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock division selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pClockDivision was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid, or `TIMx_CR1.CKD` could not be decoded.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetClockDivision
(
	TIM_TypeDef* const				TIMx,
	timer_clock_division_t* const	pClockDivision
);

/**
 * @brief Configures the Timer clock division selector
 * @details
 * Stages only `TIMx_CR1.CKD[1:0]` and writes `TIMx_CR1` only when the staged
 * image differs from the current hardware image.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[in] clockDivision Timer clock division selector
 * Accepted values:
 * - @ref `TIMx_CKD_CLK_FREQ`: `t_DTS = t_CK_INT`
 * - @ref `TIMx_CKD_CLK_2_FREQ`: `t_DTS = 2 * t_CK_INT`
 * - @ref `TIMx_CKD_CLK_4_FREQ`: `t_DTS = 4 * t_CK_INT`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock division selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p clockDivision was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_SetClockDivision
(
	TIM_TypeDef* const				TIMx,
	const timer_clock_division_t	clockDivision
);

/** @} */ // TIM_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIMER_H_ */
