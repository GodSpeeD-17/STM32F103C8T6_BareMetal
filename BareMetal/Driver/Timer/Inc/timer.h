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
//										Timer Root Configuration APIs									//
// ==================================================================================================== //

/**
 * @brief Configures one supported general-purpose Timer instance
 * @details
 * Applies every field contained in @ref `timer_config_t`. The driver layer
 * owns validation, Timer clock enable, register-image reads, codec staging,
 * and dirty writes. Registers are written only when the staged image differs
 * from the current hardware image.
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
 * Expected values:
 * - Non-`NULL`: Complete Timer configuration object
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer configuration was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pConfig was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or one or more configuration fields were invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staging failed unexpectedly.
 * @note This API does not configure channel/PWM, IRQ/NVIC, DMA, master/slave,
 * or delay-helper state.
 */
driver_status_t TIM_Config(TIM_TypeDef* const TIMx, const timer_config_t* const pConfig);

/**
 * @brief Restores the Timer configuration fields owned by this API pass
 * @details
 * Restores the register fields represented by @ref `timer_config_t` back to
 * their reset/default raw values. The driver layer validates @p TIMx, enables
 * the Timer clock when required, stages reset images, and writes only changed
 * register images.
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
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staging failed unexpectedly.
 * @note This API is limited to the fields represented by @ref `timer_config_t`.
 * Channel/PWM, IRQ/NVIC, DMA, master/slave, and delay-helper state are not part
 * of this deconfiguration scope.
 */
driver_status_t TIM_DeConfig(TIM_TypeDef* const TIMx);

// ==================================================================================================== //
//										Timer Group Configuration APIs									//
// ==================================================================================================== //

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
 * @param[out] pTimebase Destination for the current Timer timebase configuration
 * Expected values:
 * - Non-`NULL`: Timebase configuration is written to @p pTimebase
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timebase configuration was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pTimebase was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 */
driver_status_t TIM_GetTimebaseConfig
(
	TIM_TypeDef* const					TIMx,
	timer_config_timebase_t* const		pTimebase
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
 * @param[in] pTimebase Timer timebase configuration
 * Expected values:
 * - Non-`NULL`: Timebase configuration to apply
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timebase configuration was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pTimebase was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or one or more timebase fields were invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staging failed unexpectedly.
 * @note This API does not modify `TIMx_CR1` counter behavior fields.
 */
driver_status_t TIM_SetTimebaseConfig
(
	TIM_TypeDef* const						TIMx,
	const timer_config_timebase_t* const	pTimebase
);

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
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter configuration was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCounter was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: `TIMx_CR1` contained a field value outside the public Timer vocabulary.
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
 * Expected values:
 * - Non-`NULL`: Counter configuration to apply
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter configuration was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCounter was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or one or more counter fields were invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staged-image update failed unexpectedly.
 */
driver_status_t TIM_SetCounterConfig
(
	TIM_TypeDef* const						TIMx,
	const timer_config_counter_t* const		pCounter
);

// ==================================================================================================== //
//										Timer Timebase Field APIs										//
// ==================================================================================================== //

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
 * - Non-`NULL`: Prescaler value is written to @p pPrescaler
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Prescaler value was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPrescaler was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 */
driver_status_t TIM_GetPrescaler
(
	TIM_TypeDef* const				TIMx,
	timer_prescaler_t* const		pPrescaler
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
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Prescaler value was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p prescaler was invalid.
 * @note This API updates only `TIMx_PSC`; it does not modify `TIMx_ARR`,
 * `TIMx_CNT`, or `TIMx_CR1`.
 */
driver_status_t TIM_SetPrescaler
(
	TIM_TypeDef* const					TIMx,
	const timer_prescaler_t				prescaler
);

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
 * - Non-`NULL`: Counter tick frequency is written to @p pFrequency
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter tick frequency was derived.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pFrequency was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The Timer input clock could not be derived.
 * @note This is a derived convenience getter. Frequency is not stored in
 * @ref `timer_config_t`.
 */
driver_status_t TIM_GetFrequency
(
	TIM_TypeDef* const				TIMx,
	timer_frequency_t* const		pFrequency
);

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
 * - Non-`NULL`: Auto-reload value is written to @p pAutoReload
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload value was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pAutoReload was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 */
driver_status_t TIM_GetAutoReload
(
	TIM_TypeDef* const					TIMx,
	timer_auto_reload_t* const			pAutoReload
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
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload value was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p autoReload was invalid.
 * @note This API updates only `TIMx_ARR`; it does not modify `TIMx_PSC`,
 * `TIMx_CNT`, or `TIMx_CR1`.
 */
driver_status_t TIM_SetAutoReload
(
	TIM_TypeDef* const						TIMx,
	const timer_auto_reload_t				autoReload
);

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
 * - Non-`NULL`: Counter value is written to @p pCounterValue
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter value was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCounterValue was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 */
driver_status_t TIM_GetCounterValue
(
	TIM_TypeDef* const					TIMx,
	timer_counter_value_t* const			pCounterValue
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
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter value was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p counterValue was invalid.
 * @note This API updates only `TIMx_CNT`; it does not modify `TIMx_PSC`,
 * `TIMx_ARR`, or `TIMx_CR1`.
 */
driver_status_t TIM_SetCounterValue
(
	TIM_TypeDef* const						TIMx,
	const timer_counter_value_t				counterValue
);

// ==================================================================================================== //
//										Timer Counter Field APIs										//
// ==================================================================================================== //

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
 * - Non-`NULL`: Direction selector is written to @p pDirection
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Direction selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pDirection was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: `TIMx_CR1` could not be decoded.
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
 * - @ref `TIMx_DIR_COUNT_UP`
 * - @ref `TIMx_DIR_COUNT_DOWN`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Direction selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p direction was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Existing counter configuration could not be decoded or staged.
 */
driver_status_t TIM_SetDirection
(
	TIM_TypeDef* const				TIMx,
	const timer_direction_t			direction
);

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
 * - Non-`NULL`: Alignment selector is written to @p pAlignment
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Alignment selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pAlignment was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: `TIMx_CR1.CMS` could not be decoded.
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
 * - @ref `TIMx_MODE_NORMAL`
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING`
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING`
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Alignment selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p alignment was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Existing counter configuration could not be decoded or staged.
 * @warning STM32F1 does not allow switching from edge-aligned to center-aligned
 * mode while the counter is enabled.
 */
driver_status_t TIM_SetAlignment
(
	TIM_TypeDef* const					TIMx,
	const timer_count_mode_t				alignment
);

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
 * - Non-`NULL`: One-pulse selector is written to @p pOnePulse
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: One-pulse selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pOnePulse was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: `TIMx_CR1.OPM` could not be decoded.
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
 * - @ref `TIMx_OPM_DISABLE`
 * - @ref `TIMx_OPM_ENABLE`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: One-pulse selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p onePulse was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Existing counter configuration could not be decoded or staged.
 */
driver_status_t TIM_SetOnePulse
(
	TIM_TypeDef* const			TIMx,
	const timer_opm_t			onePulse
);

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
 * - Non-`NULL`: Auto-reload preload selector is written to @p pAutoReloadPreload
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload preload selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pAutoReloadPreload was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: `TIMx_CR1.ARPE` could not be decoded.
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
 * - @ref `TIMx_ARPE_DISABLE`
 * - @ref `TIMx_ARPE_ENABLE`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload preload selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p autoReloadPreload was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Existing counter configuration could not be decoded or staged.
 */
driver_status_t TIM_SetAutoReloadPreload
(
	TIM_TypeDef* const			TIMx,
	const timer_arpe_t			autoReloadPreload
);

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
 * - Non-`NULL`: Update request source selector is written to @p pUpdateSource
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Update request source selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pUpdateSource was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: `TIMx_CR1.URS` could not be decoded.
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
 * - @ref `TIMx_UPDATE_SOURCE_ANY`
 * - @ref `TIMx_UPDATE_SOURCE_OVF_DMA`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Update request source selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p updateSource was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Existing counter configuration could not be decoded or staged.
 */
driver_status_t TIM_SetUpdateSource
(
	TIM_TypeDef* const					TIMx,
	const timer_update_source_t			updateSource
);

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
 * - Non-`NULL`: Clock division selector is written to @p pClockDivision
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock division selector was extracted.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pClockDivision was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: `TIMx_CR1.CKD` could not be decoded.
 */
driver_status_t TIM_GetClockDivision
(
	TIM_TypeDef* const					TIMx,
	timer_clock_division_t* const		pClockDivision
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
 * - @ref `TIMx_CKD_CLK_FREQ`
 * - @ref `TIMx_CKD_CLK_2_FREQ`
 * - @ref `TIMx_CKD_CLK_4_FREQ`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock division selector was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p clockDivision was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Existing counter configuration could not be decoded or staged.
 */
driver_status_t TIM_SetClockDivision
(
	TIM_TypeDef* const						TIMx,
	const timer_clock_division_t				clockDivision
);

/** @} */ // TIM_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIMER_H_ */
