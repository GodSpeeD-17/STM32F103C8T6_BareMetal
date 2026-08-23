/**
 * @file	rcc_defines.h
 * @author	Shrey Shah
 * @brief	Defines RCC query and non-configuration constants
 * @version	v2.0
 * @date	23-08-2026
 *
 * @details
 * @section RCC_DEFINES_H_HIERARCHY Hierarchy
 * - Position: RCC Driver non-configuration vocabulary
 * - Included by: Public `rcc.h` interface
 * - Uses: RCC-owned scalar aliases from `rcc_data_types.h`
 *
 * @section RCC_DEFINES_H_RESPONSIBILITY Responsibility
 * This header owns RCC constants used to select observational API targets.
 * Configuration selectors and structures belong to `rcc_config.h` so an
 * application has one complete configuration vocabulary.
 *
 * @section RCC_DEFINES_H_BOUNDARY Dependency Boundary
 * This header contains no configuration structures, raw register fields,
 * validation, Codec transformation, LL access, or Driver orchestration.
 */

// Header Guard
#ifndef RCC_DEFINES_H_
#define RCC_DEFINES_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //

#include "rcc_data_types.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup RCC_03_Driver
 * @{
 */

// ==================================================================================================== //
// RCC Bus Query Selectors
// ==================================================================================================== //

/**
 * @brief RCC bus and component query selectors
 * @defgroup RCC_03_Driver_02_Defines RCC Driver Query Defines
 * @ingroup RCC_03_Driver
 * @details
 * These selectors identify one derived clock domain for observational APIs.
 * They do not encode hardware fields and cannot configure a clock divider.
 * @{
 */

/** @brief Represents an inactive, unavailable, or not-yet-derived RCC clock @def RCC_FREQ_ZERO */
#define RCC_FREQ_ZERO		FREQ_ZERO

/** @brief Selects the AHB-derived clock domain for a frequency query @def RCC_AHB_BUS */
#define RCC_AHB_BUS		((rcc_bus_t) 0U)
/** @brief Selects the APB1-derived clock domain for a frequency query @def RCC_APB1_BUS */
#define RCC_APB1_BUS		((rcc_bus_t) 1U)
/** @brief Selects the APB2-derived clock domain for a frequency query @def RCC_APB2_BUS */
#define RCC_APB2_BUS		((rcc_bus_t) 2U)
/** @brief Selects the ADC-derived clock domain for a frequency query @def RCC_ADC_BUS */
#define RCC_ADC_BUS		((rcc_bus_t) 3U)
/** @brief Selects the USB-derived clock domain for a frequency query @def RCC_USB_BUS */
#define RCC_USB_BUS		((rcc_bus_t) 4U)

/** @} */ // RCC_03_Driver_02_Defines

/** @} */ // RCC_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_DEFINES_H_ */
