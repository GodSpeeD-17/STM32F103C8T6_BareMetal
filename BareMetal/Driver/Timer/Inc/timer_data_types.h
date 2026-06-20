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

/** @brief Timer channel bit-mask selector type @typedef timer_channel_t */
typedef uint8_t									timer_channel_t;
/** @brief Timer zero-based channel index type @typedef timer_channel_index_t */
typedef uint8_t									timer_channel_index_t;
/** @brief Timer counter mode selector type @typedef timer_count_mode_t */
typedef uint8_t									timer_count_mode_t;
/** @brief Timer counting direction selector type @typedef timer_direction_t */
typedef uint8_t									timer_direction_t;
/** @brief Timer auto-reload preload selector type @typedef timer_arpe_t */
typedef uint8_t									timer_arpe_t;
/** @brief Timer one-pulse mode selector type @typedef timer_opm_t */
typedef uint8_t									timer_opm_t;
/** @brief Timer update-source selector type @typedef timer_update_source_t */
typedef uint8_t									timer_update_source_t;
/** @brief Timer IRQ enable selector type @typedef timer_irq_enable_t */
typedef uint8_t									timer_irq_enable_t;
/** @brief Timer IRQ source bit-mask selector type @typedef timer_irq_t */
typedef uint8_t									timer_irq_t;
/** @brief Timer DMA source bit-mask selector type @typedef timer_dma_t */
typedef uint8_t									timer_dma_t;
/** @brief Timer channel mode selector type @typedef timer_channel_mode_t */
typedef uint8_t									timer_channel_mode_t;
/** @brief Timer channel capture/compare selection selector type @typedef timer_channel_ccs_t */
typedef uint8_t									timer_channel_ccs_t;
/** @brief Timer channel output-compare preload selector type @typedef timer_channel_oc_preload_t */
typedef uint8_t									timer_channel_oc_preload_t;
/** @brief Timer channel output-compare fast selector type @typedef timer_channel_oc_fast_t */
typedef uint8_t									timer_channel_oc_fast_t;
/** @brief Timer channel output-compare clear selector type @typedef timer_channel_oc_clear_t */
typedef uint8_t									timer_channel_oc_clear_t;
/** @brief Timer channel polarity selector type @typedef timer_channel_polarity_t */
typedef uint8_t									timer_channel_polarity_t;
/** @brief Timer clock-division selector type @typedef timer_clock_division_t */
typedef uint8_t									timer_clock_division_t;
/** @brief Timer master-mode selector type @typedef timer_master_mode_t */
typedef uint8_t									timer_master_mode_t;
/** @brief Timer slave-mode selector type @typedef timer_slave_mode_t */
typedef uint8_t									timer_slave_mode_t;
/** @brief Timer remap selector type @typedef timer_remap_t */
typedef uint8_t									timer_remap_t;
/** @brief Timer instance index type @typedef timer_instance_index_t */
typedef uint8_t									timer_instance_index_t;
/** @brief Timer prescaler value type @typedef timer_prescaler_t */
typedef uint16_t								timer_prescaler_t;
/** @brief Timer auto-reload value type @typedef timer_auto_reload_t */
typedef uint16_t								timer_auto_reload_t;
/** @brief Timer counter value type @typedef timer_counter_value_t */
typedef uint16_t								timer_counter_value_t;
/** @brief Timer frequency value type in hertz @typedef timer_frequency_t */
typedef uint32_t								timer_frequency_t;

/** @} */ // TIM_03_Driver_01_Types

/** @} */ // TIM_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIMER_DATA_TYPES_H_ */
