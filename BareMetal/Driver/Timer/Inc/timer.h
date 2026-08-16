/**
 * @file	timer.h
 * @author	Shrey Shah
 * @brief	Timer Driver Public Interface
 * @version	v1.0
 * @date	20-06-2026
 *
 * @details
 * This header exposes the public Timer driver API. Public code sees Timer configuration structures, public
 * selectors, validation macros, and driver entry points. Low-level register
 * access and codec image staging remain private to `timer.c`.
 *
 * This API pass is intentionally limited to the fields owned by
 * @ref tim_config_t "tim_config_t":
 * - `TIMx_CR1` counter behavior fields
 * - `TIMx_PSC` counter tick prescaler
 * - `TIMx_ARR` auto-reload value
 * - `TIMx_CNT` counter value
 *
 * Channel/PWM, DMA, and master/slave APIs remain outside this public header
 * scope. Timer IRQ source/event APIs, the fixed @ref TIM_ConfigForBlockingDelay
 * service bootstrap, and the blocking @ref TIM_BlockingDelayUs and @ref TIM_BlockingDelayMs
 * APIs are provided. RCC clock-gate control and NVIC delivery remain explicit
 * application responsibilities.
 */
// Header Guard
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
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @returns @ref driver_status_t "Operation State - Operation Status"
 * @retval - @ref `DRIVER_STATUS_OFF`: Timer counter operation is disabled
 * @retval - @ref `DRIVER_STATUS_ON`: Timer counter operation is enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 * @pre The application enabled the matching APB1 clock gate through the RCC driver
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
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] operationState Requested Timer counter operation state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disable Timer counter operation.
 * - @ref `DRIVER_STATUS_ON`: Enable Timer counter operation.
 * @returns @ref driver_status_t "Operation State - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer counter operation state was updated
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported or @p `operationState` was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 * @pre The application enabled the matching APB1 clock gate through the RCC driver
 */
driver_status_t TIM_SetOperationState(TIM_TypeDef* const TIMx, const driver_status_t operationState);

// ==================================================================================================== //
//										Timer Root Configuration APIs									//
// ==================================================================================================== //

// ---------------------------------- Timer Root Configuration Pair ----------------------------------- //

/**
 * @brief Restores one supported Timer register bank to its hardware reset state
 * @details
 * Requires the matching APB1 clock gate to already be enabled, then pulses the
 * matching RCC peripheral-reset bit. This restores the complete Timer register
 * bank, including channel, IRQ, DMA, and master/slave state, without changing
 * RCC clock-gate state or NVIC delivery state.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @returns @ref driver_status_t "Root-deconfiguration operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer register state was reset
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` is unsupported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 * @pre The application enabled the matching APB1 clock gate through the RCC driver
 * @note The Timer counter is disabled by hardware reset; the APB1 clock gate
 * and NVIC line retain their application-owned states
 */
driver_status_t TIM_DeConfig(TIM_TypeDef* const TIMx);

/**
 * @brief Configures the complete supported base state of one general-purpose Timer
 * @details
 * Applies every field contained in @ref tim_config_t. The driver validates
 * @p `TIMx` and the complete configuration before touching hardware, requires
 * the APB1 Timer clock gate to already be enabled, and directly orchestrates
 * every currently implemented base-configuration domain. This function never calls
 * @ref TIM_DeConfig; the application explicitly chooses whether a reset is
 * required before configuration. Deferred channel, capture, synchronization,
 * and DMA domains are not represented by @ref tim_config_t and remain
 * unchanged. Timer IRQ-source state is also preserved; interrupt sources must
 * be configured explicitly through @ref TIM_SetIRQSources.
 *
 * The configuration sequence writes `TIMx_PSC` and `TIMx_ARR`, temporarily
 * enables update events and selects overflow/underflow-only update requests,
 * then generates `TIMx_EGR.UG`. This loads buffered timebase values without
 * generating `UIF`, an interrupt, or a DMA request. The final `TIMx_CR1` state
 * and requested initial counter value are then restored. The function neither
 * reads nor modifies `TIMx_DIER` or the instance NVIC line; Timer interrupt
 * sources and NVIC delivery remain explicit application ownership.
 *
 * This API stages:
 * - `TIMx_CR1` fields represented by @ref tim_config_counter_t
 * - `TIMx_PSC` from @ref tim_config_timebase_t::prescaler
 * - `TIMx_ARR` from @ref tim_config_timebase_t::auto_reload
 * - `TIMx_CNT` from @ref tim_config_timebase_t::initial_count
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] pConfig Complete supported Timer base configuration
 * Accepted values:
 * - Non-`NULL`: Complete Timer base-configuration object
 * - @ref tim_config_t::timebase : Timer prescaler, auto-reload, and initial counter values
 * - @ref tim_config_t::counter : Timer counter behavior selectors
 * @returns @ref driver_status_t "Root-configuration operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Complete supported Timer base configuration was applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pConfig` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` is unsupported or a configuration selector is invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate could not
 * be verified, or the request changes direction while the current mode is
 * center-aligned
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: Timer counter is running
 * @pre The application enabled the matching APB1 clock gate through the RCC driver
 * @pre The application owns the complete Timer transaction
 * @note Success leaves the application-owned Timer clock gate unchanged and the counter disabled without
 * changing Timer IRQ sources or NVIC state. For IRQ operation, explicitly
 * configure sources through @ref TIM_SetIRQSources, configure NVIC delivery,
 * and only then start the counter through @ref TIM_SetOperationState
 * @note @ref TIM_DeConfig performs a complete hardware reset and therefore
 * clears Timer IRQ sources even though this configuration API preserves them
 * @note Every represented base domain is staged before the first Timer-register
 * write. Counter behavior is coalesced into the temporary update-policy
 * `TIMx_CR1` image, eliminating a separate counter-configuration write; the
 * timebase commit then applies the final requested `TIMx_CR1` image only when
 * it differs. A validation or staging failure leaves Timer register state
 * unchanged; this function never mutates the Timer clock gate
 * @note To change direction from a center-aligned mode, the application must
 * first call @ref TIM_SetAlignment with @ref `TIMx_MODE_NORMAL`, then call
 * @ref TIM_SetDirection, and finally restore the requested center-aligned mode
 * explicitly
 */
driver_status_t TIM_Config(TIM_TypeDef* const TIMx, const tim_config_t* const pConfig);

// ==================================================================================================== //
//										Timer Group Configuration APIs									//
// ==================================================================================================== //

// -------------------------------- Timer TimeBase Configuration Pair --------------------------------- //

/**
 * @brief Extracts the Timer timebase configuration
 * @details
 * Reads only the Timer registers required for @ref tim_config_timebase_t.
 * The current `TIMx_PSC`, `TIMx_ARR`, and `TIMx_CNT` values are returned
 * through @ref tim_config_timebase_t. Use @ref TIM_GetProgrammedTickFrequency when the
 * derived counter tick frequency is required.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[out] pTimeBase Destination for the current Timer timebase configuration
 * Expected values:
 * - Non-`NULL`: TimeBase configuration is written to @p pTimeBase
 * - @ref tim_config_timebase_t::prescaler : Current `TIMx_PSC` value
 * - @ref tim_config_timebase_t::auto_reload : Current `TIMx_ARR` value
 * - @ref tim_config_timebase_t::initial_count : Current `TIMx_CNT` value
 * @returns @ref driver_status_t "TimeBase-configuration extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: TimeBase configuration was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pTimeBase` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` is unsupported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_GetTimeBaseConfig(TIM_TypeDef* const TIMx, tim_config_timebase_t* const	pTimeBase);

/**
 * @brief Configures the Timer timebase fields
 * @details
 * Applies @ref tim_config_timebase_t::prescaler to `TIMx_PSC`,
 * @ref tim_config_timebase_t::auto_reload to `TIMx_ARR`, and
 * @ref tim_config_timebase_t::initial_count to `TIMx_CNT`. The counter must
 * be stopped. A software update event makes buffered PSC/ARR values active;
 * temporary `UDIS=0` and `URS=1` prevent that commit from creating `UIF`, an
 * interrupt, or a DMA request. The requested CNT and original CR1 state are
 * restored after the commit.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] pTimeBase Timer timebase configuration
 * Accepted values:
 * - Non-`NULL`: TimeBase configuration to apply
 * - @ref tim_config_timebase_t::prescaler : Value staged into `TIMx_PSC`
 * - @ref tim_config_timebase_t::auto_reload : Value staged into `TIMx_ARR`
 * - @ref tim_config_timebase_t::initial_count : Value staged into `TIMx_CNT`
 * @returns @ref driver_status_t "TimeBase-configuration operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: TimeBase configuration was applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pTimeBase` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` is unsupported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: Timer counter is running
 * @note This API does not modify `TIMx_CR1` counter behavior fields.
 */
driver_status_t TIM_SetTimeBaseConfig(TIM_TypeDef* const TIMx, const tim_config_timebase_t* const pTimeBase);

// --------------------------------- Timer Counter Configuration Pair --------------------------------- //

/**
 * @brief Extracts the Timer counter behavior configuration
 * @details
 * Reads `TIMx_CR1` and extracts only the fields represented by
 * @ref tim_config_counter_t.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[out] pCounter Destination for the current Timer counter configuration
 * Expected values:
 * - Non-`NULL`: Counter configuration is written to @p pCounter
 * - @ref tim_config_counter_t::direction : @ref `TIMx_DIR_COUNT_UP` or @ref `TIMx_DIR_COUNT_DOWN`
 * - @ref tim_config_counter_t::alignment : @ref `TIMx_MODE_NORMAL`,
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING`,
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING`, or
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING`
 * - @ref tim_config_counter_t::one_pulse : @ref `TIMx_OPM_DISABLE` or @ref `TIMx_OPM_ENABLE`
 * - @ref tim_config_counter_t::auto_reload_preload : @ref `TIMx_ARPE_DISABLE` or @ref `TIMx_ARPE_ENABLE`
 * - @ref tim_config_counter_t::update_source : @ref `TIMx_UPDATE_SOURCE_ANY` or @ref `TIMx_UPDATE_SOURCE_OVERFLOW_UNDERFLOW_ONLY`
 * - @ref tim_config_counter_t::digital_filter_clock_division : @ref `TIMx_DIGITAL_FILTER_CLOCK_DIV_1`,
 *   @ref `TIMx_DIGITAL_FILTER_CLOCK_DIV_2`, or @ref `TIMx_DIGITAL_FILTER_CLOCK_DIV_4`
 * @returns @ref driver_status_t "Counter Configuration - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter configuration was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pCounter` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported or `TIMx_CR1` could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 * @note Counter enable state and update-event enable state are not part of
 * @ref tim_config_counter_t.
 */
driver_status_t TIM_GetCounterConfig(TIM_TypeDef* const TIMx, tim_config_counter_t* const pCounter);

/**
 * @brief Configures the Timer counter behavior fields
 * @details
 * Stages @ref tim_config_counter_t into one final `TIMx_CR1` image while
 * preserving counter-enable and update-event-enable state. The counter must be
 * stopped. A request that changes direction while the current mode is
 * center-aligned is rejected because hardware makes `TIMx_CR1.DIR` read-only
 * in that mode. Every admitted transaction dirty-writes `TIMx_CR1` at most once.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] pCounter Timer counter configuration
 * Accepted values:
 * - Non-`NULL`: Counter configuration to apply
 * - @ref tim_config_counter_t::direction : @ref `TIMx_DIR_COUNT_UP` or @ref `TIMx_DIR_COUNT_DOWN`
 * - @ref tim_config_counter_t::alignment : @ref `TIMx_MODE_NORMAL`,
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING`,
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING`, or
 *   @ref `TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING`
 * - @ref tim_config_counter_t::one_pulse : @ref `TIMx_OPM_DISABLE` or @ref `TIMx_OPM_ENABLE`
 * - @ref tim_config_counter_t::auto_reload_preload : @ref `TIMx_ARPE_DISABLE` or @ref `TIMx_ARPE_ENABLE`
 * - @ref tim_config_counter_t::update_source : @ref `TIMx_UPDATE_SOURCE_ANY` or @ref `TIMx_UPDATE_SOURCE_OVERFLOW_UNDERFLOW_ONLY`
 * - @ref tim_config_counter_t::digital_filter_clock_division : @ref `TIMx_DIGITAL_FILTER_CLOCK_DIV_1`,
 *   @ref `TIMx_DIGITAL_FILTER_CLOCK_DIV_2`, or @ref `TIMx_DIGITAL_FILTER_CLOCK_DIV_4`
 * @returns @ref driver_status_t "Counter Configuration - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter configuration was applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pCounter` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported or a counter selector was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is
 * disabled, or the request changes direction while the current mode is
 * center-aligned
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: Timer counter is running
 * @note To change direction from a center-aligned mode, explicitly configure
 * edge-aligned mode, change direction, and then restore the requested
 * center-aligned mode through separate application-owned calls
 */
driver_status_t TIM_SetCounterConfig(TIM_TypeDef* const TIMx, const tim_config_counter_t* const	pCounter);

// ==================================================================================================== //
//										Timer TimeBase Field APIs										//
// ==================================================================================================== //

/**
 * @brief Returns the Timer tick frequency derived from the programmed prescaler
 * @details
 * Reads `TIMx_PSC` and derives the counter tick frequency from the Timer input
 * clock and prescaler value.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[out] pFrequency Destination for the derived counter tick frequency in hertz
 * Expected values:
 * - Non-`NULL`: Derived counter tick frequency in hertz is written to @p pFrequency
 * - `0U..0xFFFFFFFFU`: Any value representable by @ref frequency_t
 * @returns @ref driver_status_t "Programmed tick-frequency operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Programmed counter tick frequency was derived
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pFrequency` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` is unsupported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled or the Timer input clock could not be derived
 * @note This reports the frequency implied by readable `TIMx_PSC`; it does not
 * prove that the active buffered prescaler has already been latched by an update event.
 */
driver_status_t TIM_GetProgrammedTickFrequency(TIM_TypeDef* const TIMx, frequency_t* const pFrequency);

// --------------------------------------- Timer Prescaler Pair --------------------------------------- //

/**
 * @brief Returns the current Timer prescaler value
 * @details
 * Reads the register-backed `TIMx_PSC` value directly. Use
 * @ref TIM_GetProgrammedTickFrequency when the programmed counter tick frequency is required.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[out] pPrescaler Destination for the current `TIMx_PSC` value
 * Expected values:
 * - Non-`NULL`: Current `TIMx_PSC[15:0]` value is written to @p pPrescaler
 * - `0x0000U..0xFFFFU`: Any value representable by @ref tim_prescaler_t
 * @returns @ref driver_status_t "Prescaler - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Prescaler value was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pPrescaler` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_GetPrescaler(TIM_TypeDef* const TIMx, tim_prescaler_t* const pPrescaler);

/**
 * @brief Configures the Timer prescaler value
 * @details
 * Updates `TIMx_PSC` and generates a non-requesting software update event so
 * the new prescaler is active when this function returns. The counter must be
 * stopped; ARR, CNT, and the caller's CR1 state are preserved.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] prescaler Prescaler value staged into `TIMx_PSC`
 * Accepted values:
 * - `0x0000U..0xFFFFU`: Any value representable by @ref tim_prescaler_t
 * @returns @ref driver_status_t "Prescaler - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Prescaler value was applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: Timer counter is running
 * @note This API updates only `TIMx_PSC`; it does not modify `TIMx_ARR`,
 * `TIMx_CNT`, or `TIMx_CR1`.
 */
driver_status_t TIM_SetPrescaler(TIM_TypeDef* const TIMx, const tim_prescaler_t	prescaler);

// -------------------------------------- Timer Auto-Reload Pair -------------------------------------- //

/**
 * @brief Returns the current Timer auto-reload value
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[out] pAutoReload Destination for the current `TIMx_ARR` value
 * Expected values:
 * - Non-`NULL`: Current `TIMx_ARR[15:0]` value is written to @p pAutoReload
 * - `0x0000U..0xFFFFU`: Any value representable by @ref tim_auto_reload_t
 * @returns @ref driver_status_t "Auto-Reload - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload value was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pAutoReload` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_GetAutoReload(TIM_TypeDef* const TIMx, tim_auto_reload_t* const	pAutoReload);

/**
 * @brief Configures the Timer auto-reload value
 * @details
 * Updates `TIMx_ARR` and generates a non-requesting software update event so
 * a preloaded ARR is active when this function returns. The counter must be
 * stopped; PSC, CNT, and the caller's CR1 state are preserved.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] autoReload Auto-reload value staged into `TIMx_ARR`
 * Accepted values:
 * - `0x0000U..0xFFFFU`: Any value representable by @ref tim_auto_reload_t
 * @returns @ref driver_status_t "Auto-Reload - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload value was applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: Timer counter is running
 * @note This API updates only `TIMx_ARR`; it does not modify `TIMx_PSC`,
 * `TIMx_CNT`, or `TIMx_CR1`.
 */
driver_status_t TIM_SetAutoReload(TIM_TypeDef* const TIMx, const tim_auto_reload_t autoReload);

// ------------------------------------- Timer Counter Value Pair ------------------------------------- //

/**
 * @brief Returns the current Timer counter value
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[out] pCounterValue Destination for the current `TIMx_CNT` value
 * Expected values:
 * - Non-`NULL`: Current `TIMx_CNT[15:0]` value is written to @p pCounterValue
 * - `0x0000U..0xFFFFU`: Any value representable by @ref tim_counter_value_t
 * @returns @ref driver_status_t "Counter Value - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter value was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pCounterValue` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_GetCounterValue(TIM_TypeDef* const TIMx, tim_counter_value_t* const	pCounterValue);

/**
 * @brief Configures the Timer counter value
 * @details
 * Writes only `TIMx_CNT` if @p counterValue differs from the current hardware
 * image.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] counterValue Counter value staged into `TIMx_CNT`
 * Accepted values:
 * - `0x0000U..0xFFFFU`: Any value representable by @ref tim_counter_value_t
 * @returns @ref driver_status_t "Counter Value - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter value was applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: Timer counter is running
 * @note This API updates only `TIMx_CNT`; it does not modify `TIMx_PSC`,
 * `TIMx_ARR`, or `TIMx_CR1`.
 */
driver_status_t TIM_SetCounterValue(TIM_TypeDef* const TIMx, const tim_counter_value_t counterValue);

// ==================================================================================================== //
//										Timer Counter Field APIs										//
// ==================================================================================================== //

// --------------------------------------- Timer Direction Pair --------------------------------------- //

/**
 * @brief Returns the current Timer counter direction selector
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[out] pDirection Destination for the current direction selector
 * Expected values:
 * - @ref `TIMx_DIR_COUNT_UP` : Counter counts up
 * - @ref `TIMx_DIR_COUNT_DOWN` : Counter counts down
 * @returns @ref driver_status_t "Direction - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Direction selector was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pDirection` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported or `TIMx_CR1` could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_GetDirection(TIM_TypeDef* const TIMx, tim_direction_t* const pDirection);

/**
 * @brief Configures the Timer counter direction selector
 * @details
 * Preserves all unrelated `TIMx_CR1` fields and dirty-writes one final image at
 * most once. The counter must be stopped. A direction change is rejected while
 * the current mode is center-aligned because hardware makes `TIMx_CR1.DIR`
 * read-only in that mode.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] direction Timer counter direction selector
 * Accepted values:
 * - @ref `TIMx_DIR_COUNT_UP` : Counter counts up
 * - @ref `TIMx_DIR_COUNT_DOWN` : Counter counts down
 * @returns @ref driver_status_t "Direction - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Direction selector was applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported, @p `direction` was invalid, or `TIMx_CR1` could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled, or direction cannot change in the current counter mode
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: Timer counter is running
 * @note To change direction from a center-aligned mode, explicitly configure
 * edge-aligned mode first and restore the requested center-aligned mode after
 * this call
 */
driver_status_t TIM_SetDirection(TIM_TypeDef* const TIMx, const tim_direction_t	direction);

// --------------------------------------- Timer Alignment Pair --------------------------------------- //

/**
 * @brief Returns the current Timer counter alignment selector
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[out] pAlignment Destination for the current edge/center-aligned selector
 * Expected values:
 * - @ref `TIMx_MODE_NORMAL` : Edge-aligned mode
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING` : Center-aligned mode 1
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING` : Center-aligned mode 2
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING` : Center-aligned mode 3
 * @returns @ref driver_status_t "Alignment - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Alignment selector was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pAlignment` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported or `TIMx_CR1.CMS` could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_GetAlignment(TIM_TypeDef* const TIMx, tim_count_mode_t* const pAlignment);

/**
 * @brief Configures the Timer counter alignment selector
 * @details
 * Preserves all unrelated `TIMx_CR1` fields, stages the requested alignment,
 * and dirty-writes one final image at most once. The counter must be stopped.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] alignment Timer edge/center-aligned selector
 * Accepted values:
 * - @ref `TIMx_MODE_NORMAL` : Edge-aligned mode
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING` : Center-aligned mode 1
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING` : Center-aligned mode 2
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING` : Center-aligned mode 3
 * @returns @ref driver_status_t "Alignment - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Alignment selector was applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported, @p `alignment` was invalid, or `TIMx_CR1` could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: Timer counter is running
 */
driver_status_t TIM_SetAlignment(TIM_TypeDef* const TIMx, const tim_count_mode_t alignment);

// --------------------------------------- Timer One-Pulse Pair --------------------------------------- //

/**
 * @brief Returns the current Timer one-pulse mode selector
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[out] pOnePulse Destination for the current one-pulse selector
 * Expected values:
 * - @ref `TIMx_OPM_DISABLE`:	Counter is not stopped at the next update event
 * - @ref `TIMx_OPM_ENABLE`:	Counter stops at the next update event
 * @returns @ref driver_status_t "One-Pulse - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: One-pulse selector was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pOnePulse` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported or `TIMx_CR1.OPM` could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_GetOnePulse(TIM_TypeDef* const TIMx, tim_opm_t* const pOnePulse);

/**
 * @brief Configures the Timer one-pulse mode selector
 * @details
 * Stages only `TIMx_CR1.OPM` and writes `TIMx_CR1` only when the staged image
 * differs from the current hardware image.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] onePulse Timer one-pulse selector
 * Accepted values:
 * - @ref `TIMx_OPM_DISABLE` : Counter is not stopped at the next update event
 * - @ref `TIMx_OPM_ENABLE` : Counter stops at the next update event
 * @returns @ref driver_status_t "One-Pulse - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: One-pulse selector was applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported or @p `onePulse` was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_SetOnePulse(TIM_TypeDef* const TIMx, const tim_opm_t onePulse);

// ---------------------------------- Timer Auto-Reload Preload Pair ---------------------------------- //

/**
 * @brief Returns the current Timer auto-reload preload selector
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[out] pAutoReloadPreload Destination for the current auto-reload preload selector
 * Expected values:
 * - @ref `TIMx_ARPE_DISABLE` : Auto-reload preload is disabled
 * - @ref `TIMx_ARPE_ENABLE` : Auto-reload preload is enabled
 * @returns @ref driver_status_t "Auto-Reload Preload - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload preload selector was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pAutoReloadPreload` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported or `TIMx_CR1.ARPE` could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_GetAutoReloadPreload(TIM_TypeDef* const	TIMx, tim_arpe_t* const	pAutoReloadPreload);

/**
 * @brief Configures the Timer auto-reload preload selector
 * @details
 * Stages only `TIMx_CR1.ARPE` and writes `TIMx_CR1` only when the staged image
 * differs from the current hardware image.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] autoReloadPreload Timer auto-reload preload selector
 * Accepted values:
 * - @ref `TIMx_ARPE_DISABLE` : Auto-reload preload is disabled
 * - @ref `TIMx_ARPE_ENABLE` : Auto-reload preload is enabled
 * @returns @ref driver_status_t "Auto-Reload Preload - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload preload selector was applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported or @p `autoReloadPreload` was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_SetAutoReloadPreload(TIM_TypeDef* const	TIMx, const tim_arpe_t autoReloadPreload);

// ------------------------------------- Timer Update Source Pair ------------------------------------- //

/**
 * @brief Returns the current Timer update request source selector
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[out] pUpdateSource Destination for the current update request source selector
 * Expected values:
 * - @ref `TIMx_UPDATE_SOURCE_ANY` : Any update source may generate an update request
 * - @ref `TIMx_UPDATE_SOURCE_OVERFLOW_UNDERFLOW_ONLY` : Only counter overflow or underflow generates an update request
 * @returns @ref driver_status_t "Update Source - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Update request source selector was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pUpdateSource` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported or `TIMx_CR1.URS` could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_GetUpdateSource(TIM_TypeDef* const TIMx, tim_update_source_t* const	pUpdateSource);

/**
 * @brief Configures the Timer update request source selector
 * @details
 * Stages only `TIMx_CR1.URS` and writes `TIMx_CR1` only when the staged image
 * differs from the current hardware image.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] updateSource Timer update request source selector
 * Accepted values:
 * - @ref `TIMx_UPDATE_SOURCE_ANY` : Any update source may generate an update request
 * - @ref `TIMx_UPDATE_SOURCE_OVERFLOW_UNDERFLOW_ONLY` : Only counter overflow or underflow generates an update request
 * @returns @ref driver_status_t "Update Source - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Update request source selector was applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported or @p `updateSource` was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_SetUpdateSource(TIM_TypeDef* const TIMx, const tim_update_source_t updateSource);

// -------------------------- Timer Digital-Filter Clock Division Pair ------------------------------- //

/**
 * @brief Returns the digital-filter sampling-clock division selector
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[out] pDigitalFilterClockDivision Destination for the current digital-filter clock-division selector
 * Expected values:
 * - @ref `TIMx_DIGITAL_FILTER_CLOCK_DIV_1` : `t_DTS = t_CK_INT`
 * - @ref `TIMx_DIGITAL_FILTER_CLOCK_DIV_2` : `t_DTS = 2 * t_CK_INT`
 * - @ref `TIMx_DIGITAL_FILTER_CLOCK_DIV_4` : `t_DTS = 4 * t_CK_INT`
 * @returns @ref driver_status_t "Digital-filter clock-division extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Digital-filter clock-division selector was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pDigitalFilterClockDivision` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` is unsupported or `TIMx_CR1.CKD` could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_GetDigitalFilterClockDivision
(
	TIM_TypeDef* const							TIMx,
	tim_digital_filter_clock_division_t* const	pDigitalFilterClockDivision
);

/**
 * @brief Configures the digital-filter sampling-clock division selector
 * @details
 * Stages only `TIMx_CR1.CKD[1:0]` and writes `TIMx_CR1` only when the staged
 * image differs from the current hardware image.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] digitalFilterClockDivision Digital-filter clock-division selector
 * Accepted values:
 * - @ref `TIMx_DIGITAL_FILTER_CLOCK_DIV_1` : `t_DTS = t_CK_INT`
 * - @ref `TIMx_DIGITAL_FILTER_CLOCK_DIV_2` : `t_DTS = 2 * t_CK_INT`
 * - @ref `TIMx_DIGITAL_FILTER_CLOCK_DIV_4` : `t_DTS = 4 * t_CK_INT`
 * @returns @ref driver_status_t "Digital-filter clock-division operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Digital-filter clock-division selector was applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` is unsupported or @p `digitalFilterClockDivision` is invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_SetDigitalFilterClockDivision
(
	TIM_TypeDef* const							TIMx,
	const tim_digital_filter_clock_division_t	digitalFilterClockDivision
);

// ==================================================================================================== //
//										Timer IRQ APIs										//
// ==================================================================================================== //

// ------------------------------------- Timer IRQ Source Pair --------------------------------------- //

/**
 * @brief Returns the enabled Timer interrupt-request sources
 * @details Reads only the supported interrupt-enable bits in `TIMx_DIER`.
 * NVIC enable, pending, and active state are independent and are not reported.
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[out] pIrqSources Destination for the enabled interrupt-request source mask
 * Expected values:
 * - Non-`NULL`: Enabled sources are written to @p pIrqSources
 * - @ref `TIMx_IRQ_SOURCE_NONE` through @ref `TIMx_IRQ_SOURCE_ALL`
 * @returns @ref driver_status_t "IRQ-source operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Enabled interrupt-request sources were returned
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pIrqSources` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` is unsupported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_GetIRQSources(TIM_TypeDef* const TIMx, tim_irq_source_t* const pIrqSources);

/**
 * @brief Enables or disables selected Timer interrupt-request sources
 * @details Updates only the supported interrupt-enable bits in `TIMx_DIER`.
 * The application or NVIC integration layer separately owns NVIC line state,
 * priority, and stale-pending policy.
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] irqSources Non-empty interrupt-request source mask to modify
 * Accepted values:
 * - @ref `TIMx_IRQ_SOURCE_UPDATE`
 * - @ref `TIMx_IRQ_SOURCE_CC1`
 * - @ref `TIMx_IRQ_SOURCE_CC2`
 * - @ref `TIMx_IRQ_SOURCE_CC3`
 * - @ref `TIMx_IRQ_SOURCE_CC4`
 * - @ref `TIMx_IRQ_SOURCE_TRIGGER`
 * - Any non-empty combination contained by @ref `TIMx_IRQ_SOURCE_ALL`
 * @param[in] sourceState Requested source-enable state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF` : Disable the selected sources.
 * - @ref `DRIVER_STATUS_ON` : Enable the selected sources.
 * @returns @ref driver_status_t "IRQ-source operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Selected interrupt-request sources were updated
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx`, @p `irqSources`, or @p `sourceState` is invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_SetIRQSources
(
	TIM_TypeDef* const			TIMx,
	const tim_irq_source_t		irqSources,
	const driver_status_t		sourceState
);

// ------------------------------------- Timer IRQ Event Pair ---------------------------------------- //

/**
 * @brief Returns the currently latched Timer event flags
 * @details Reads supported `TIMx_SR` flags independently from `TIMx_DIER` and
 * NVIC delivery state. A returned event is not proof that an IRQ is enabled,
 * pending in NVIC, or active.
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[out] pIrqEvents Destination for the latched Timer event mask
 * Expected values:
 * - Non-`NULL`: Latched event flags are written to @p pIrqEvents
 * - @ref `TIMx_IRQ_EVENT_NONE` through @ref `TIMx_IRQ_EVENT_ALL`
 * @returns @ref driver_status_t "IRQ-event operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Latched Timer events were returned
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pIrqEvents` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` is unsupported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
driver_status_t TIM_GetIRQEvents(TIM_TypeDef* const TIMx, tim_event_flag_t* const pIrqEvents);

/**
 * @brief Acknowledges selected Timer event flags
 * @details Issues one `TIMx_SR` write-zero-to-clear operation. Unselected
 * writable flags receive write-one preservation values. Timer acknowledgement
 * does not clear NVIC pending state.
 *
 * Capture/compare and overcapture events are accepted only while their channel
 * is configured for output compare. A generic acknowledgement is rejected for
 * an input-capture lane because it could discard an unread capture. The
 * deferred capture-consumption API will own captured-value and overcapture
 * ordering.
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] irqEvents Non-empty Timer event mask to acknowledge
 * Accepted values:
 * - @ref `TIMx_IRQ_EVENT_UPDATE`
 * - @ref `TIMx_IRQ_EVENT_CC1`
 * - @ref `TIMx_IRQ_EVENT_CC2`
 * - @ref `TIMx_IRQ_EVENT_CC3`
 * - @ref `TIMx_IRQ_EVENT_CC4`
 * - @ref `TIMx_IRQ_EVENT_TRIGGER`
 * - @ref `TIMx_IRQ_EVENT_CC1_OVERCAPTURE`
 * - @ref `TIMx_IRQ_EVENT_CC2_OVERCAPTURE`
 * - @ref `TIMx_IRQ_EVENT_CC3_OVERCAPTURE`
 * - @ref `TIMx_IRQ_EVENT_CC4_OVERCAPTURE`
 * - Any non-empty combination contained by @ref `TIMx_IRQ_EVENT_ALL`
 * @returns @ref driver_status_t "IRQ-event acknowledgement status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Selected Timer events were acknowledged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` or @p `irqEvents` is invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The Timer clock is disabled or a selected event belongs to an input-capture lane
 * @warning An event arriving on a selected source between observation and
 * acknowledgement can be lost. Service handlers must re-sample until their
 * owned event set is quiescent.
 */
driver_status_t TIM_AckIRQEvents(TIM_TypeDef* const TIMx, const tim_event_flag_t irqEvents);

// ==================================================================================================== //
//										Timer Blocking Delay APIs										//
// ==================================================================================================== //

// ---------------------------- Timer Blocking Delay Configuration Helper --------------------------- //

/**
 * @brief Allocates and configures a dedicated blocking polling-delay Timer for a 1 MHz counter tick
 * @details
 * Requires the matching APB1 clock gate to already be enabled, validates that
 * @p TIMx receives a 72 MHz Timer kernel clock, builds the canonical
 * blocking polling-delay @ref tim_config_t, and delegates the complete admitted
 * configuration to @ref TIM_Config. The fixed prescaler value is `71`,
 * producing a 1 MHz counter tick from the validated 72 MHz input clock.
 *
 * This helper never invokes @ref TIM_DeConfig. The application owns any
 * required reset before configuration. Like @ref TIM_Config, this helper
 * neither reads nor modifies the instance NVIC line.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @returns @ref driver_status_t "Blocking-delay Timer configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The Timer was configured with a 1 MHz counter tick
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is unsupported, the canonical configuration is invalid, or the update-flag state could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The Timer APB1 clock gate is disabled, or the Timer kernel clock is unavailable or is not 72 MHz
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: The Timer counter is running
 * @pre The application enabled the matching APB1 clock gate through the RCC driver
 * @pre The RCC clock tree provides a 72 MHz kernel clock to @p TIMx
 * @note A successful call allocates @p TIMx to the application as a dedicated
 * blocking-delay Timer until the application explicitly reconfigures or
 * deconfigures it
 * @note This helper leaves the application-owned Timer clock gate unchanged,
 * enables one-pulse mode and update events, disables auto-reload preload,
 * clears `TIMx_SR.UIF`, and leaves the counter disabled without changing Timer
 * IRQ-source or NVIC state
 */
driver_status_t TIM_ConfigForBlockingDelay(TIM_TypeDef* const TIMx);

// ---------------------------------- Timer Microsecond Delay Helper ---------------------------------- //

/**
 * @brief Provides a minimum blocking delay in microseconds using a 1 MHz Timer
 * @details
 * Uses a Timer allocated and configured through @ref TIM_ConfigForBlockingDelay as a
 * dedicated blocking polling-delay source. The helper verifies that the APB1 Timer
 * clock gate is enabled, but deliberately does not revalidate the programmed
 * prescaler or other base configuration. It updates
 * `TIMx_ARR = delayUs - 1`, restarts `TIMx_CNT` from
 * @ref `TIMx_DEFAULT_CNT`, clears `TIMx_SR.UIF`, starts the preconfigured
 * one-pulse counter, and blocks while polling until `TIMx_SR.UIF` is asserted
 * or the bounded budget expires. It then stops the counter when necessary and
 * clears the update flag before returning.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] delayUs Delay duration in microseconds
 * Accepted values:
 * - `1U..0xFFFFU`: Blocking delay duration in microseconds.
 * @returns @ref driver_status_t "Microsecond Delay - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Delay completed
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported, @p `delayUs` was `0U`, or a Timer state could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: The update flag did not arrive within the bounded polling budget
 * @pre The application successfully called @ref TIM_ConfigForBlockingDelay for @p TIMx
 * and retained exclusive dedicated blocking-delay ownership without
 * reconfiguring it
 * @note Assumptions and constraints:
 * - The Timer counter tick is exactly 1 MHz, so one counter tick equals 1 us.
 * - The requested delay is a minimum delay; software setup, polling, and
 *   cleanup can add a small positive overhead.
 * - The Timer is treated as a dedicated blocking-delay source; this helper
 *   controls `TIMx_CR1.CEN`, `TIMx_ARR`, `TIMx_CNT`, and `TIMx_SR.UIF`, and
 *   leaves the counter disabled before returning.
 * - The delay is type-bounded to 16 bits, so the maximum delay is `65535 us`.
 * - This is a polling delay and does not use Timer IRQ/NVIC state.
 * @warning Passing a Timer that was not successfully allocated through
 * @ref TIM_ConfigForBlockingDelay, or that was subsequently reconfigured, violates the
 * application-owned blocking-delay contract. This function does not validate
 * the Timer base configuration, and the resulting blocking duration is
 * unspecified
 */
driver_status_t TIM_BlockingDelayUs(TIM_TypeDef* const TIMx, const uint16_t delayUs);

// ---------------------------------- Timer Millisecond Delay Helper ---------------------------------- //

/**
 * @brief Provides a minimum blocking delay in milliseconds using a 1 MHz Timer
 * @details
 * Uses @ref TIM_BlockingDelayUs as the primitive delay operation and performs one
 * `1000 us` delay chunk for each requested millisecond. Because each
 * millisecond is composed from the microsecond helper, the final delay is a
 * minimum delay and includes the accumulated software overhead of each chunk.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] delayMs Delay duration in milliseconds
 * Accepted values:
 * - `1U..0xFFFFFFFFU`: Blocking delay duration in milliseconds.
 * @returns @ref driver_status_t "Millisecond Delay - Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Delay completed
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` was unsupported, @p `delayMs` was `0U`, or a Timer state could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A microsecond delay chunk timed out
 * @pre The application successfully called @ref TIM_ConfigForBlockingDelay for @p TIMx
 * and retained exclusive dedicated blocking-delay ownership without
 * reconfiguring it
 * @note Assumptions and constraints:
 * - @p delayMs must not be `0U`.
 * - This is a polling delay and does not use Timer IRQ/NVIC state.
 * @warning Passing a Timer that was not successfully allocated through
 * @ref TIM_ConfigForBlockingDelay, or that was subsequently reconfigured, violates the
 * application-owned blocking-delay contract. This function does not validate
 * the Timer base configuration, and the resulting blocking duration is
 * unspecified
 */
driver_status_t TIM_BlockingDelayMs(TIM_TypeDef* const TIMx, const uint32_t delayMs);

/** @} */ // TIM_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIMER_H_ */
