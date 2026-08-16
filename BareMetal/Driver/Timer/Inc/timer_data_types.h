/**
 * @file	timer_data_types.h
 * @author	Shrey Shah
 * @brief	Timer Driver Shared Data Type Aliases
 * @version	v1.0
 * @date	07-06-2026
 *
 * @details
 * This header owns Timer driver-facing scalar typedef aliases only. Public
 * selector macros and pure validation helpers live in `timer_defines.h`.
 *
 * Timer public configuration structures intentionally remain in the Timer
 * driver API layer because Timer configuration is wider and more modular than
 * GPIO-style fixed argument lists.
 */

#ifndef TIMER_DATA_TYPES_H_
#define TIMER_DATA_TYPES_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "stm32f1xx_data_types.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup TIM_03_Driver
 * @{
 */

// ==================================================================================================== //
//										Timer Driver Data Types										//
// ==================================================================================================== //

/**
 * @brief Timer driver data type aliases
 * @defgroup TIM_03_Driver_01_Types Timer Driver Data Types
 * @ingroup TIM_03_Driver
 * @{
 */

/** @brief Timer channel bit-mask selector type @typedef tim_channel_t */
typedef uint8_t									tim_channel_t;
/** @brief Timer zero-based channel index type @typedef tim_channel_index_t */
typedef uint8_t									tim_channel_index_t;
/** @brief Timer counter mode selector type @typedef tim_count_mode_t */
typedef uint8_t									tim_count_mode_t;
/** @brief Timer counting direction selector type @typedef tim_direction_t */
typedef uint8_t									tim_direction_t;
/** @brief Timer auto-reload preload selector type @typedef tim_arpe_t */
typedef uint8_t									tim_arpe_t;
/** @brief Timer one-pulse mode selector type @typedef tim_opm_t */
typedef uint8_t									tim_opm_t;
/** @brief Timer update-source selector type @typedef tim_update_source_t */
typedef uint8_t									tim_update_source_t;
/** @brief Timer interrupt-request source bit-mask selector type @typedef tim_irq_source_t */
typedef uint8_t									tim_irq_source_t;
/** @brief Timer event-flag bit-mask selector type @typedef tim_event_flag_t */
typedef uint16_t								tim_event_flag_t;
/** @brief Timer DMA source bit-mask selector type @typedef tim_dma_t */
typedef uint8_t									tim_dma_t;
/** @brief Timer channel mode selector type @typedef tim_channel_mode_t */
typedef uint8_t									tim_channel_mode_t;
/** @brief Timer channel capture/compare selection selector type @typedef tim_channel_ccs_t */
typedef uint8_t									tim_channel_ccs_t;
/** @brief Timer channel output-compare preload selector type @typedef tim_channel_oc_preload_t */
typedef uint8_t									tim_channel_oc_preload_t;
/** @brief Timer channel output-compare fast selector type @typedef tim_channel_oc_fast_t */
typedef uint8_t									tim_channel_oc_fast_t;
/** @brief Timer channel output-compare clear selector type @typedef tim_channel_oc_clear_t */
typedef uint8_t									tim_channel_oc_clear_t;
/** @brief Timer channel polarity selector type @typedef tim_channel_polarity_t */
typedef uint8_t									tim_channel_polarity_t;
/** @brief Timer digital-filter sampling-clock division selector type @typedef tim_digital_filter_clock_division_t */
typedef uint8_t									tim_digital_filter_clock_division_t;
/** @brief Timer master-mode selector type @typedef tim_master_mode_t */
typedef uint8_t									tim_master_mode_t;
/** @brief Timer slave-mode selector type @typedef tim_slave_mode_t */
typedef uint8_t									tim_slave_mode_t;
/** @brief Timer remap selector type @typedef tim_remap_t */
typedef uint8_t									tim_remap_t;
/** @brief Timer instance index type @typedef tim_instance_index_t */
typedef uint8_t									tim_instance_index_t;
/** @brief Timer prescaler value type @typedef tim_prescaler_t */
typedef uint16_t								tim_prescaler_t;
/** @brief Timer auto-reload value type @typedef tim_auto_reload_t */
typedef uint16_t								tim_auto_reload_t;
/** @brief Timer counter value type @typedef tim_counter_value_t */
typedef uint16_t								tim_counter_value_t;
/** @brief Timer output-compare register value type @typedef tim_compare_value_t */
typedef uint16_t								tim_compare_value_t;
/** @brief Timer PWM duty-cycle value in permille units @typedef tim_pwm_duty_cycle_t */
typedef uint16_t								tim_pwm_duty_cycle_t;
/** @} */ // TIM_03_Driver_01_Types

/** @} */ // TIM_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIMER_DATA_TYPES_H_ */
