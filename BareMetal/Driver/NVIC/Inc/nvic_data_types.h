/**
 * @file	nvic_data_types.h
 * @author	Shrey Shah
 * @brief	NVIC Driver Shared Data Type Aliases
 * @version	v2.1
 * @date	16-08-2026
 *
 * @details
 * This header owns only the scalar aliases shared by the NVIC Driver and
 * Codec layers. Public selector constants live in `nvic_defines.h`, raw
 * register representations remain Core-owned, and the public API keeps
 * preemption priority and sub-priority as separate scalar parameters.
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
 * @defgroup NVIC_03_Driver NVIC Driver
 * @ingroup NVIC
 * @brief Application-facing STM32F103C8T6 external-interrupt controller driver
 * @details
 * See @ref NVIC_Peripheral_Guide "STM32F103C8T6 NVIC Architecture" for the
 * complete interrupt theory, register model, layer ownership, and C
 * implementation mapping behind this API.
 */

/**
 * @addtogroup NVIC_03_Driver
 * @{
 */

// ==================================================================================================== //
//									NVIC Driver Data Types									//
// ==================================================================================================== //

/**
 * @brief NVIC Driver scalar aliases
 * @defgroup NVIC_03_Driver_01_Types NVIC Driver Data Types
 * @ingroup NVIC_03_Driver
 * @details
 * These aliases distinguish external IRQ identifiers, global grouping
 * selectors, preemption priorities, and sub-priorities without introducing
 * a structure for the two independent priority values.
 * @{
 */

// ------------------------------------- External IRQ Identifier Type -------------------------------- //

/** @brief STM32F103C8T6 external interrupt request number type @typedef irq_t */
typedef uint8_t									irq_t;

// --------------------------------------- NVIC Priority Types --------------------------------------- //

/** @brief Logical NVIC priority-group selector type @typedef nvic_priority_group_t */
typedef uint8_t									nvic_priority_group_t;
/** @brief Logical NVIC preemption-priority selector type @typedef nvic_preempt_priority_t */
typedef uint8_t									nvic_preempt_priority_t;
/** @brief Logical NVIC sub-priority selector type @typedef nvic_sub_priority_t */
typedef uint8_t									nvic_sub_priority_t;

/** @} */ // NVIC_03_Driver_01_Types

/** @} */ // NVIC_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NVIC_DATA_TYPES_H_ */
