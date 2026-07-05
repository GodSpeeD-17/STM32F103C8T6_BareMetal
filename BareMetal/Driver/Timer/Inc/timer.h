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
 * @ref `tim_config_t`:
 * - `TIMx_CR1` counter behavior fields
 * - `TIMx_PSC` counter tick prescaler
 * - `TIMx_ARR` auto-reload value
 * - `TIMx_CNT` counter value
 *
 * Channel/PWM, IRQ/NVIC, DMA, master/slave, and broad delay-service APIs are
 * outside this public header scope for this pass. The delay helpers in this
 * pass are the blocking @ref `TIM_DelayUs` and @ref `TIM_DelayMs` convenience
 * APIs for a Timer already configured with @ref `TIM_Config1MHz`.
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
 * @returns @ref driver_status_t "Clock State - Operation Status"
 * @retval - @ref `DRIVER_STATUS_OFF`: Timer APB1 clock gate is disabled.
 * @retval - @ref `DRIVER_STATUS_ON`: Timer APB1 clock gate is enabled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was invalid.
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
 * @returns @ref driver_status_t "Clock State - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer APB1 clock gate was updated.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `clockState` was invalid.
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
 * @returns @ref driver_status_t "Operation State - Operation Status"
 * @retval - @ref `DRIVER_STATUS_OFF`: Timer counter operation is disabled.
 * @retval - @ref `DRIVER_STATUS_ON`: Timer counter operation is enabled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was invalid.
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
 * @returns @ref driver_status_t "Operation State - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer counter operation state was updated.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `operationState` was invalid.
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
 * Restores the register fields represented by @ref `tim_config_t` back to
 * their reset/default raw values. The driver validates @p TIMx, enables the
 * APB1 Timer clock gate with @ref `TIM_SetClockState`, disables the counter
 * with @ref `TIM_SetOperationState`, stages the reset images locally, and then
 * commits them through the same update-event latch sequence used by
 * @ref `TIM_Config`.
 *
 * The reset sequence writes `TIMx_CR1`, `TIMx_PSC`, and `TIMx_ARR` before
 * generating one software update event with `TIMx_EGR.UG`. Because
 * @ref `tim_config_t` does not own `TIMx_CR1.UDIS`, the driver temporarily
 * clears `UDIS` only for that generated update event so the reset prescaler and
 * auto-reload values are latched into active Timer logic. The original `UDIS`
 * state is restored afterward. `TIMx_CNT` is written last because the generated
 * update event can alter the counter value.
 *
 * If `TIMx_SR.UIF` was clear before the generated update event and becomes
 * pending afterward, the driver clears that generated flag before returning. A
 * pre-existing pending `TIMx_SR.UIF` flag is preserved.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @returns @ref driver_status_t "Root De-Configuration - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer configuration fields were restored.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate could not be verified during the reset sequence.
 * @note This API is limited to the fields represented by @ref `tim_config_t`.
 * Channel/PWM, IRQ/NVIC, DMA, master/slave, and delay-helper state are not part
 * of this de-configuration scope.
 * @note This API does not issue an RCC peripheral reset. It leaves the Timer
 * counter disabled and disables the Timer APB1 clock gate before returning.
 */
driver_status_t TIM_DeConfig(TIM_TypeDef* const TIMx);

/**
 * @brief Configures one supported general-purpose Timer instance
 * @details
 * Applies every field contained in @ref `tim_config_t`. The driver validates
 * @p TIMx, enables the APB1 Timer clock gate with @ref `TIM_SetClockState`,
 * disables the counter with @ref `TIM_SetOperationState`, stages register
 * images through the codec layer, and writes only changed register images. All
 * requested images are staged before the first hardware write so codec failures
 * cannot leave a partially staged configuration.
 *
 * The configuration sequence writes `TIMx_CR1`, `TIMx_PSC`, and `TIMx_ARR`
 * before generating one software update event with `TIMx_EGR.UG`; this update
 * event latches the prescaler and any preloaded auto-reload value into active
 * Timer logic. Because @ref `tim_config_t` does not own `TIMx_CR1.UDIS`, the
 * driver temporarily clears `UDIS` only for this generated update event and
 * restores the original `UDIS` state afterward. `TIMx_CNT` is applied after
 * the update event so the requested initial counter value is preserved.
 *
 * If `TIMx_SR.UIF` was clear before the generated update event and becomes
 * pending afterward, the driver clears that generated update flag before
 * returning. A pre-existing pending `TIMx_SR.UIF` flag is preserved.
 *
 * This API stages:
 * - `TIMx_CR1` fields represented by @ref `tim_config_counter_t`
 * - `TIMx_PSC` from @ref `tim_config_timebase_t::prescaler`
 * - `TIMx_ARR` from @ref `tim_config_timebase_t::auto_reload`
 * - `TIMx_CNT` from @ref `tim_config_timebase_t::initial_count`
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
 * - @ref `tim_config_t::timebase`: Timer prescaler, auto-reload, and initial counter values
 * - @ref `tim_config_t::counter`: Timer counter behavior selectors
 * @returns @ref driver_status_t "Root Configuration - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer configuration was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` / @p `pConfig` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / one or more configuration fields were invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate could not be verified during the configuration sequence.
 * @note This API does not configure channel/PWM, IRQ/NVIC, DMA, master/slave,
 * or delay-helper state.
 * @note This API leaves the Timer counter disabled. Use
 * @ref `TIM_SetOperationState` with @ref `DRIVER_STATUS_ON` to start the
 * counter after configuration.
 */
driver_status_t TIM_Config(TIM_TypeDef* const TIMx, const tim_config_t* const pConfig);

// --------------------------------- Timer 1 MHz Configuration Preset --------------------------------- //

/**
 * @brief Configures one Timer instance for a 1 MHz counter tick
 * @details
 * Builds a local @ref `tim_config_t` preset and applies it through
 * @ref `TIM_Config`. The wrapper uses the existing default 1 MHz preset
 * values:
 * - @ref `TIMx_DEFAULT_1MHz_PSC`
 * - @ref `TIMx_DEFAULT_1MHz_ARR`
 * - @ref `TIMx_DEFAULT_CNT`
 *
 * The counter behavior preset is edge-aligned up-counting, one-pulse disabled,
 * auto-reload preload enabled, update source set to any update event, and
 * clock division set to `t_DTS = t_CK_INT`.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @returns @ref driver_status_t "1 MHz Configuration - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer was configured for a 1 MHz counter tick.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate could not be verified during the configuration sequence.
 * @note - This is a header-local static inline wrapper around @ref `TIM_Config`.
 * @note - This wrapper leaves the Timer counter disabled, matching @ref `TIM_Config`.
 * @note - Assumptions and constraints:
 * @note - @p `TIMx` is one of the supported APB1 general-purpose Timers.
 * @note - @ref `TIMx_DEFAULT_1MHz_PSC` assumes the Timer kernel clock is
 *   72 MHz. If the current clock tree uses a different Timer kernel clock,
 *   this wrapper still applies the preset but the resulting counter tick will
 *   not be exactly 1 MHz.
 * @note - The counting window uses @ref `TIMx_DEFAULT_1MHz_ARR`, so this preset
 *   configures a 1 MHz counter tick with the default 1 MHz count window.
 */
__STATIC_INLINE driver_status_t TIM_Config1MHz(TIM_TypeDef* const TIMx)
{
	// Local Variables
	tim_config_t config =
	{
		.timebase =
		{
			.prescaler		= TIMx_DEFAULT_1MHz_PSC,
			.auto_reload	= TIMx_DEFAULT_1MHz_ARR,
			.initial_count	= TIMx_DEFAULT_CNT
		},
		.counter =
		{
			.direction				= TIMx_DIR_COUNT_UP,
			.alignment				= TIMx_MODE_NORMAL,
			.one_pulse				= TIMx_OPM_DISABLE,
			.auto_reload_preload	= TIMx_ARPE_ENABLE,
			.update_source			= TIMx_UPDATE_SOURCE_ANY,
			.clock_division			= TIMx_CKD_CLK_FREQ
		}
	};

	return TIM_Config(TIMx, &config);
}

// ==================================================================================================== //
//										Timer Group Configuration APIs									//
// ==================================================================================================== //

// -------------------------------- Timer TimeBase Configuration Pair --------------------------------- //

/**
 * @brief Extracts the Timer timebase configuration
 * @details
 * Reads only the Timer registers required for @ref `tim_config_timebase_t`.
 * The current `TIMx_PSC`, `TIMx_ARR`, and `TIMx_CNT` values are returned
 * through @ref `tim_config_timebase_t`. Use @ref `TIM_GetFrequency` when the
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
 * - @ref `tim_config_timebase_t::prescaler`: Current `TIMx_PSC` value
 * - @ref `tim_config_timebase_t::auto_reload`: Current `TIMx_ARR` value
 * - @ref `tim_config_timebase_t::initial_count`: Current `TIMx_CNT` value
 * @returns @ref driver_status_t "TimeBase Configuration - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: TimeBase configuration was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pTimeBase` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetTimeBaseConfig
(
	TIM_TypeDef* const					TIMx,
	tim_config_timebase_t* const		pTimeBase
);

/**
 * @brief Configures the Timer timebase fields
 * @details
 * Applies @ref `tim_config_timebase_t::prescaler` to `TIMx_PSC`,
 * @ref `tim_config_timebase_t::auto_reload` to `TIMx_ARR`, and
 * @ref `tim_config_timebase_t::initial_count` to `TIMx_CNT`. Each register is
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
 * - @ref `tim_config_timebase_t::prescaler`: Value staged into `TIMx_PSC`
 * - @ref `tim_config_timebase_t::auto_reload`: Value staged into `TIMx_ARR`
 * - @ref `tim_config_timebase_t::initial_count`: Value staged into `TIMx_CNT`
 * @returns @ref driver_status_t "TimeBase Configuration - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: TimeBase configuration was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pTimeBase` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / one or more timebase fields were invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 * @note This API does not modify `TIMx_CR1` counter behavior fields.
 */
driver_status_t TIM_SetTimeBaseConfig
(
	TIM_TypeDef* const					TIMx,
	const tim_config_timebase_t* const	pTimeBase
);

// --------------------------------- Timer Counter Configuration Pair --------------------------------- //

/**
 * @brief Extracts the Timer counter behavior configuration
 * @details
 * Reads `TIMx_CR1` and extracts only the fields represented by
 * @ref `tim_config_counter_t`.
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
 * - @ref `tim_config_counter_t::direction`: @ref `TIMx_DIR_COUNT_UP` or @ref `TIMx_DIR_COUNT_DOWN`
 * - @ref `tim_config_counter_t::alignment`: @ref `TIMx_MODE_NORMAL`,
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING`,
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING`, or
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING`
 * - @ref `tim_config_counter_t::one_pulse`: @ref `TIMx_OPM_DISABLE` or @ref `TIMx_OPM_ENABLE`
 * - @ref `tim_config_counter_t::auto_reload_preload`: @ref `TIMx_ARPE_DISABLE` or @ref `TIMx_ARPE_ENABLE`
 * - @ref `tim_config_counter_t::update_source`: @ref `TIMx_UPDATE_SOURCE_ANY` or @ref `TIMx_UPDATE_SOURCE_OVF_DMA`
 * - @ref `tim_config_counter_t::clock_division`: @ref `TIMx_CKD_CLK_FREQ`,
 *   @ref `TIMx_CKD_CLK_2_FREQ`, or @ref `TIMx_CKD_CLK_4_FREQ`
 * @returns @ref driver_status_t "Counter Configuration - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter configuration was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pCounter` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was invalid, or `TIMx_CR1` contained a field value outside the public Timer vocabulary.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 * @note Counter enable state and update-event enable state are not part of
 * @ref `tim_config_counter_t`.
 */
driver_status_t TIM_GetCounterConfig
(
	TIM_TypeDef* const				TIMx,
	tim_config_counter_t* const		pCounter
);

/**
 * @brief Configures the Timer counter behavior fields
 * @details
 * Stages @ref `tim_config_counter_t` into the `TIMx_CR1` image and writes
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
 * - @ref `tim_config_counter_t::direction`: @ref `TIMx_DIR_COUNT_UP` or @ref `TIMx_DIR_COUNT_DOWN`
 * - @ref `tim_config_counter_t::alignment`: @ref `TIMx_MODE_NORMAL`,
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING`,
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING`, or
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING`
 * - @ref `tim_config_counter_t::one_pulse`: @ref `TIMx_OPM_DISABLE` or @ref `TIMx_OPM_ENABLE`
 * - @ref `tim_config_counter_t::auto_reload_preload`: @ref `TIMx_ARPE_DISABLE` or @ref `TIMx_ARPE_ENABLE`
 * - @ref `tim_config_counter_t::update_source`: @ref `TIMx_UPDATE_SOURCE_ANY` or @ref `TIMx_UPDATE_SOURCE_OVF_DMA`
 * - @ref `tim_config_counter_t::clock_division`: @ref `TIMx_CKD_CLK_FREQ`,
 *   @ref `TIMx_CKD_CLK_2_FREQ`, or @ref `TIMx_CKD_CLK_4_FREQ`
 * @returns @ref driver_status_t "Counter Configuration - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter configuration was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pCounter` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / one or more counter fields were invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_SetCounterConfig
(
	TIM_TypeDef* const					TIMx,
	const tim_config_counter_t* const	pCounter
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
 * - `0U..0xFFFFFFFFU`: Any value representable by @ref `tim_frequency_t`
 * @returns @ref driver_status_t "Counter Frequency - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter tick frequency was derived.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pFrequency` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled, or the Timer input clock could not be derived.
 * @note This is a derived convenience getter. Frequency is not stored in
 * @ref `tim_config_t`.
 */
driver_status_t TIM_GetFrequency
(
	TIM_TypeDef* const		TIMx,
	tim_frequency_t* const	pFrequency
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
 * - `0x0000U..0xFFFFU`: Any value representable by @ref `tim_prescaler_t`
 * @returns @ref driver_status_t "Prescaler - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Prescaler value was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pPrescaler` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetPrescaler
(
	TIM_TypeDef* const		TIMx,
	tim_prescaler_t* const	pPrescaler
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
 * - `0x0000U..0xFFFFU`: Any value representable by @ref `tim_prescaler_t`
 * @returns @ref driver_status_t "Prescaler - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Prescaler value was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `prescaler` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 * @note This API updates only `TIMx_PSC`; it does not modify `TIMx_ARR`,
 * `TIMx_CNT`, or `TIMx_CR1`.
 */
driver_status_t TIM_SetPrescaler
(
	TIM_TypeDef* const		TIMx,
	const tim_prescaler_t	prescaler
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
 * - `0x0000U..0xFFFFU`: Any value representable by @ref `tim_auto_reload_t`
 * @returns @ref driver_status_t "Auto-Reload - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload value was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pAutoReload` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetAutoReload
(
	TIM_TypeDef* const			TIMx,
	tim_auto_reload_t* const	pAutoReload
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
 * - `0x0000U..0xFFFFU`: Any value representable by @ref `tim_auto_reload_t`
 * @returns @ref driver_status_t "Auto-Reload - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload value was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `autoReload` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 * @note This API updates only `TIMx_ARR`; it does not modify `TIMx_PSC`,
 * `TIMx_CNT`, or `TIMx_CR1`.
 */
driver_status_t TIM_SetAutoReload
(
	TIM_TypeDef* const			TIMx,
	const tim_auto_reload_t		autoReload
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
 * - `0x0000U..0xFFFFU`: Any value representable by @ref `tim_counter_value_t`
 * @returns @ref driver_status_t "Counter Value - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter value was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pCounterValue` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetCounterValue
(
	TIM_TypeDef* const			TIMx,
	tim_counter_value_t* const	pCounterValue
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
 * - `0x0000U..0xFFFFU`: Any value representable by @ref `tim_counter_value_t`
 * @returns @ref driver_status_t "Counter Value - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter value was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `counterValue` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 * @note This API updates only `TIMx_CNT`; it does not modify `TIMx_PSC`,
 * `TIMx_ARR`, or `TIMx_CR1`.
 */
driver_status_t TIM_SetCounterValue
(
	TIM_TypeDef* const			TIMx,
	const tim_counter_value_t	counterValue
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
 * @returns @ref driver_status_t "Direction - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Direction selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pDirection` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was invalid, or `TIMx_CR1` could not be decoded.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetDirection
(
	TIM_TypeDef* const			TIMx,
	tim_direction_t* const		pDirection
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
 * @returns @ref driver_status_t "Direction - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Direction selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `direction` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_SetDirection
(
	TIM_TypeDef* const			TIMx,
	const tim_direction_t		direction
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
 * @returns @ref driver_status_t "Alignment - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Alignment selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pAlignment` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was invalid, or `TIMx_CR1.CMS` could not be decoded.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetAlignment
(
	TIM_TypeDef* const			TIMx,
	tim_count_mode_t* const		pAlignment
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
 * @returns @ref driver_status_t "Alignment - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Alignment selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `alignment` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 * @warning STM32F1 does not allow switching from edge-aligned to center-aligned
 * mode while the counter is enabled.
 */
driver_status_t TIM_SetAlignment
(
	TIM_TypeDef* const		TIMx,
	const tim_count_mode_t	alignment
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
 * @returns @ref driver_status_t "One-Pulse - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: One-pulse selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pOnePulse` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was invalid, or `TIMx_CR1.OPM` could not be decoded.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetOnePulse
(
	TIM_TypeDef* const		TIMx,
	tim_opm_t* const		pOnePulse
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
 * @returns @ref driver_status_t "One-Pulse - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: One-pulse selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `onePulse` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_SetOnePulse
(
	TIM_TypeDef* const		TIMx,
	const tim_opm_t			onePulse
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
 * @returns @ref driver_status_t "Auto-Reload Preload - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload preload selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pAutoReloadPreload` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was invalid, or `TIMx_CR1.ARPE` could not be decoded.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetAutoReloadPreload
(
	TIM_TypeDef* const		TIMx,
	tim_arpe_t* const		pAutoReloadPreload
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
 * @returns @ref driver_status_t "Auto-Reload Preload - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload preload selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `autoReloadPreload` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_SetAutoReloadPreload
(
	TIM_TypeDef* const		TIMx,
	const tim_arpe_t		autoReloadPreload
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
 * @returns @ref driver_status_t "Update Source - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Update request source selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pUpdateSource` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was invalid, or `TIMx_CR1.URS` could not be decoded.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetUpdateSource
(
	TIM_TypeDef* const			TIMx,
	tim_update_source_t* const	pUpdateSource
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
 * @returns @ref driver_status_t "Update Source - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Update request source selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `updateSource` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_SetUpdateSource
(
	TIM_TypeDef* const			TIMx,
	const tim_update_source_t	updateSource
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
 * @returns @ref driver_status_t "Clock Division - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock division selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pClockDivision` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was invalid, or `TIMx_CR1.CKD` could not be decoded.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_GetClockDivision
(
	TIM_TypeDef* const			TIMx,
	tim_clock_division_t* const	pClockDivision
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
 * @returns @ref driver_status_t "Clock Division - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock division selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `clockDivision` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 */
driver_status_t TIM_SetClockDivision
(
	TIM_TypeDef* const			TIMx,
	const tim_clock_division_t	clockDivision
);

// ==================================================================================================== //
//										Timer Blocking Delay APIs										//
// ==================================================================================================== //

// ---------------------------------- Timer Microsecond Delay Helper ---------------------------------- //

/**
 * @brief Provides a minimum blocking delay in microseconds using a 1 MHz Timer
 * @details
 * Uses a Timer previously configured by @ref `TIM_Config1MHz` as a dedicated
 * polling delay source. The helper verifies that the APB1 Timer clock gate is
 * enabled, stops the counter, disables auto-reload preload so the delay window
 * uses the new `TIMx_ARR` immediately, writes `TIMx_ARR = delayUs - 1`,
 * restarts `TIMx_CNT` from @ref `TIMx_DEFAULT_CNT`, clears `TIMx_SR.UIF`, then
 * starts the counter with one-pulse mode enabled and update events temporarily
 * enabled so `TIMx_SR.UIF` can terminate polling. It stops the counter,
 * restores the original update-event enable state, and clears the update flag
 * before returning.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[in] delayUs Delay duration in microseconds
 * Accepted values:
 * - `1U..0xFFFFU`: Blocking delay duration in microseconds.
 * @returns @ref driver_status_t "Microsecond Delay - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Delay completed.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `delayUs` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 * @note Assumptions and constraints:
 * - @p `TIMx` was configured by @ref `TIM_Config1MHz`.
 * - The Timer counter tick is exactly 1 MHz, so one counter tick equals 1 us.
 * - The requested delay is a minimum delay; software setup, polling, and
 *   cleanup can add a small positive overhead.
 * - The Timer is treated as a dedicated delay source; this helper controls
 *   `TIMx_CR1.CEN`, `TIMx_CR1.OPM`, `TIMx_CR1.ARPE`, `TIMx_ARR`, `TIMx_CNT`,
 *   `TIMx_CR1.UDIS` during the delay window, and `TIMx_SR.UIF`, and leaves the
 *   counter disabled before returning.
 * - The delay is type-bounded to 16 bits, so the maximum delay is `65535 us`.
 * - This is a polling delay and does not use Timer IRQ/NVIC state.
 */
driver_status_t TIM_DelayUs(TIM_TypeDef* const TIMx, const uint16_t delayUs);

// ---------------------------------- Timer Millisecond Delay Helper ---------------------------------- //

/**
 * @brief Provides a minimum blocking delay in milliseconds using a 1 MHz Timer
 * @details
 * Uses @ref `TIM_DelayUs` as the primitive delay operation and performs one
 * `1000 us` delay chunk for each requested millisecond. Because each
 * millisecond is composed from the microsecond helper, the final delay is a
 * minimum delay and includes the accumulated software overhead of each chunk.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @param[in] delayMs Delay duration in milliseconds
 * Accepted values:
 * - `1U..0xFFFFFFFFU`: Blocking delay duration in milliseconds.
 * @returns @ref driver_status_t "Millisecond Delay - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Delay completed.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `delayMs` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled.
 * @note Assumptions and constraints:
 * - @p `TIMx` was configured by @ref `TIM_Config1MHz`.
 * - @p `delayMs` must not be `0U`.
 * - This is a polling delay and does not use Timer IRQ/NVIC state.
 */
driver_status_t TIM_DelayMs(TIM_TypeDef* const TIMx, const uint32_t delayMs);

/** @} */ // TIM_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIMER_H_ */
