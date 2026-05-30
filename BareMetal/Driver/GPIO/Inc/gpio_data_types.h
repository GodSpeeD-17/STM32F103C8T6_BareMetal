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
/** @brief GPIO pin mode selector type @typedef gpio_pin_mode_t */
typedef uint8_t									gpio_pin_mode_t;
/** @brief GPIO pin configuration selector type @typedef gpio_pin_config_t */
typedef uint8_t									gpio_pin_config_t;
/** @brief Raw GPIO MODE field type @typedef gpio_mode_t */
typedef uint8_t									gpio_mode_t;
/** @brief Raw GPIO output speed field type @typedef gpio_speed_t */
typedef uint8_t									gpio_speed_t;
/** @brief Raw GPIO CNF field type @typedef gpio_cnf_t */
typedef uint8_t									gpio_cnf_t;
/** @brief Raw GPIO pull direction bit type @typedef gpio_pull_t */
typedef uint8_t									gpio_pull_t;
/** @brief Raw packed GPIO pin configuration field type @typedef gpio_pin_config_bits_t */
typedef uint8_t									gpio_pin_config_bits_t;
/** @brief GPIO EXTI trigger selector type @typedef gpio_exti_trigger_t */
typedef uint8_t									gpio_exti_trigger_t;
/** @brief GPIO EXTI port source selector type @typedef gpio_exti_port_t */
typedef uint8_t									gpio_exti_port_t;

/** @} */ // GPIO_03_Driver_01_Types

/** @} */ // GPIO_03_Driver

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_DATA_TYPES_H_ */
