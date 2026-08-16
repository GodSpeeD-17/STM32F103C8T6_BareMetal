/**
 * @file	nvic_data_types.h
 * @author	Shrey Shah
 * @brief	NVIC Driver Data Types
 * @version	v1.0
 * @date	06-06-2026
 *
 * @details
 * This header owns only NVIC driver scalar aliases. It deliberately contains
 * no IRQ number macros, priority selectors, or register helper macros; those
 * belong in @ref `nvic_defines.h`.
 */

// Header Guards
#ifndef NVIC_DATA_TYPES_H_
#define NVIC_DATA_TYPES_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "stm32f1xx_data_types.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup NVIC_Driver NVIC Driver
 * @brief Cortex-M3 NVIC driver layer
 */

/**
 * @defgroup NVIC_01_DataTypes NVIC Driver Data Types
 * @ingroup NVIC_Driver
 * @brief Scalar aliases used by the NVIC driver
 * @{
 */

/** @brief External interrupt request number type @typedef irq_t */
typedef uint8_t									irq_t;
/** @brief Logical priority-group selector type @typedef nvic_priority_group_t */
typedef uint8_t									nvic_priority_group_t;
/** @brief Raw 8-bit NVIC priority field image type @typedef nvic_priority_t */
typedef uint8_t									nvic_priority_t;
/** @brief Logical sub-priority selector type @typedef nvic_sub_priority_t */
typedef uint8_t									nvic_sub_priority_t;
/** @brief SCB system-exception bit-mask type @typedef scb_exception_t */
typedef uint32_t								scb_exception_t;

/** @} */ // NVIC_01_DataTypes

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NVIC_DATA_TYPES_H_ */
