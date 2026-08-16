/**
 * @file	nvic_data_types.h
 * @author	Shrey Shah
 * @brief	NVIC Driver Data Types
 * @version	v2.0
 * @date	16-08-2026
 *
 * @details
 * This header owns only scalar aliases used by the NVIC driver. Logical
 * preemption and sub-priority values remain separate scalar parameters.
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
 * @brief Cortex-M3 external-interrupt controller driver
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
/** @brief Logical preemption-priority selector type @typedef nvic_preempt_priority_t */
typedef uint8_t									nvic_preempt_priority_t;
/** @brief Logical sub-priority selector type @typedef nvic_sub_priority_t */
typedef uint8_t									nvic_sub_priority_t;

/** @} */ // NVIC_01_DataTypes

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NVIC_DATA_TYPES_H_ */
