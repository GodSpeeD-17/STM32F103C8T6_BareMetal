/**
 * @file	gpio_data_types.h
 * @author	Shrey Shah
 * @brief	GPIO Driver Shared Data Type Aliases
 * @version	v1.0
 * @date	24-05-2026
 *
 * @details
 * This header owns GPIO driver-facing scalar typedef aliases only. Public
 * selector macros and pure validation helpers live in `gpio_defines.h`.
 */

#ifndef GPIO_DATA_TYPES_H_
#define GPIO_DATA_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //
#include "stm32f1xx_data_types.h"

/**
 * @addtogroup GPIO_03_Driver
 * @{
 */

// ==================================================================================================== //
//                                         GPIO Driver Data Types                                       //
// ==================================================================================================== //

/**
 * @brief GPIO driver data type aliases
 * @defgroup GPIO_03_Driver_01_Types GPIO Driver Data Types
 * @ingroup GPIO_03_Driver
 * @{
 */

/** @brief GPIO pin bit-mask type @typedef gpio_pin_t */
typedef uint16_t								gpio_pin_t;
/** @brief GPIO zero-based pin index type @typedef gpio_pin_index_t */
typedef uint8_t									gpio_pin_index_t;
/** @brief GPIO pin mode selector type @typedef gpio_pin_mode_t */
typedef uint8_t									gpio_pin_mode_t;
/** @brief GPIO pin configuration selector type @typedef gpio_pin_config_t */
typedef uint8_t									gpio_pin_config_t;
/** @brief GPIO IRQ trigger selector type @typedef gpio_irq_trigger_t */
typedef uint8_t									gpio_irq_trigger_t;

/** @} */ // GPIO_03_Driver_01_Types

/** @} */ // GPIO_03_Driver

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_DATA_TYPES_H_ */
