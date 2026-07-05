/**
 * @file	timer_config.h
 * @author	Shrey Shah
 * @brief	Timer Driver Configuration Structures
 * @version	v1.0
 * @date	20-06-2026
 *
 * @details
 * This header owns Timer driver configuration structures only. These
 * structures are intentionally timer-instance independent so one
 * @ref `tim_config_t` object can be reused with any supported Timer instance
 * passed separately to the public driver API.
 *
 * This header does not own:
 * - register access helpers
 * - clock enable/reset helpers
 * - NVIC helpers
 * - public Timer API declarations
 * - selector macros or validation helpers
 *
 * Public Timer selector macros and validation helpers live in
 * @ref `timer_defines.h`. Hardware register access belongs to the Timer LL and
 * driver layers.
 */

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "timer_defines.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup TIM_03_Driver
 * @{
 */

/**
 * @brief Timer driver configuration structures
 * @defgroup TIM_03_Driver_04_Config Timer Driver Configuration Structures
 * @ingroup TIM_03_Driver
 * @details
 * These structures group driver-facing configuration parameters. They do not
 * contain a @ref `TIM_TypeDef` instance pointer because the same configuration
 * should be applicable to multiple Timer peripherals.
 * @{
 */

// ==================================================================================================== //
//										Timer Timebase Configuration									//
// ==================================================================================================== //

/**
 * @brief Timer timebase configuration
 * @typedef tim_config_timebase_t
 * @details
 * Groups the Timer register-backed values that define the counter clock
 * division and counting window. The driver stages @ref `prescaler` into `PSC`,
 * @ref `auto_reload` into `ARR`, and @ref `initial_count` into `CNT`.
 *
 * @note The counter tick frequency is derived from @ref `prescaler` as
 * `timer_input_clock / (prescaler + 1U)`.
 */
typedef struct _tim_config_timebase_t
{
	/**
	 * @brief Prescaler value staged into `TIMx_PSC`
	 * @details
	 * Divides the Timer input clock before it reaches the counter.
	 * `CK_CNT = timer_input_clock / (prescaler + 1U)`.
	 * Accepted values:
	 * - `0x0000U..0xFFFFU`: Any value representable by @ref `tim_prescaler_t`
	 * @memberof tim_config_timebase_t
	 */
	tim_prescaler_t			prescaler;

	/**
	 * @brief Auto-reload value staged into `TIMx_ARR`
	 * @details
	 * Defines the counter reload boundary. The effective update period depends
	 * on both @ref `prescaler` and @ref `auto_reload`.
	 * Accepted values:
	 * - `0x0000U..0xFFFFU`: Any value representable by @ref `tim_auto_reload_t`
	 * @memberof tim_config_timebase_t
	 */
	tim_auto_reload_t			auto_reload;

	/**
	 * @brief Initial counter value staged into `TIMx_CNT`
	 * @details
	 * Defines the counter value used after configuration staging.
	 * Accepted values:
	 * - `0x0000U..0xFFFFU`: Any value representable by @ref `tim_counter_value_t`
	 * @memberof tim_config_timebase_t
	 */
	tim_counter_value_t		initial_count;

} tim_config_timebase_t;

// ==================================================================================================== //
//										Timer Counter Configuration									//
// ==================================================================================================== //

/**
 * @brief Timer counter behavior configuration
 * @typedef tim_config_counter_t
 * @details
 * Groups the driver-facing selectors that map to `TIMx_CR1` counter behavior.
 * The Timer codec converts these selectors into the caller-owned `CR1` image;
 * the driver layer decides when to read, stage, and write that image.
 */
typedef struct _tim_config_counter_t
{
	/**
	 * @brief Counter direction selector
	 * @details
	 * Accepted values:
	 * - @ref `TIMx_DIR_COUNT_UP`: Counter counts up
	 * - @ref `TIMx_DIR_COUNT_DOWN`: Counter counts down
	 * @memberof tim_config_counter_t
	 */
	tim_direction_t			direction;

	/**
	 * @brief Counter alignment mode selector
	 * @details
	 * Selects edge-aligned counting or one of the center-aligned counting modes.
	 * Accepted values:
	 * - @ref `TIMx_MODE_NORMAL`: Edge-aligned mode
	 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING`: Center-aligned mode 1
	 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING`: Center-aligned mode 2
	 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING`: Center-aligned mode 3
	 * @memberof tim_config_counter_t
	 */
	tim_count_mode_t			alignment;

	/**
	 * @brief One-pulse mode selector
	 * @details
	 * Accepted values:
	 * - @ref `TIMx_OPM_DISABLE`: Counter is not stopped at the next update event
	 * - @ref `TIMx_OPM_ENABLE`: Counter stops at the next update event
	 * @memberof tim_config_counter_t
	 */
	tim_opm_t					one_pulse;

	/**
	 * @brief Auto-reload preload selector
	 * @details
	 * Accepted values:
	 * - @ref `TIMx_ARPE_DISABLE`: Auto-reload preload is disabled
	 * - @ref `TIMx_ARPE_ENABLE`: Auto-reload preload is enabled
	 * @memberof tim_config_counter_t
	 */
	tim_arpe_t				auto_reload_preload;

	/**
	 * @brief Update request source selector
	 * @details
	 * Accepted values:
	 * - @ref `TIMx_UPDATE_SOURCE_ANY`: Any update source may generate an update request
	 * - @ref `TIMx_UPDATE_SOURCE_OVF_DMA`: Only overflow/underflow or DMA source generates an update request
	 * @memberof tim_config_counter_t
	 */
	tim_update_source_t		update_source;

	/**
	 * @brief Digital filter and dead-time sampling clock division selector
	 * @details
	 * Accepted values:
	 * - @ref `TIMx_CKD_CLK_FREQ`: `t_DTS = t_CK_INT`
	 * - @ref `TIMx_CKD_CLK_2_FREQ`: `t_DTS = 2 * t_CK_INT`
	 * - @ref `TIMx_CKD_CLK_4_FREQ`: `t_DTS = 4 * t_CK_INT`
	 * @memberof tim_config_counter_t
	 */
	tim_clock_division_t		clock_division;

} tim_config_counter_t;

// ==================================================================================================== //
//										Timer Driver Root Configuration									//
// ==================================================================================================== //

/**
 * @brief Timer root configuration
 * @typedef tim_config_t
 * @details
 * Root configuration object consumed by the Timer driver. It deliberately does
 * not contain a Timer peripheral pointer; the public driver API should receive
 * `TIMx` separately so this structure remains reusable across Timer instances.
 */
typedef struct _tim_config_t
{
	/**
	 * @brief Timer counter tick, reload, and initial count configuration
	 * @memberof tim_config_t
	 */
	tim_config_timebase_t	timebase;

	/**
	 * @brief Timer counter behavior configuration
	 * @memberof tim_config_t
	 */
	tim_config_counter_t	counter;

} tim_config_t;

/** @} */ // TIM_03_Driver_04_Config

/** @} */ // TIM_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIMER_CONFIG_H_ */
