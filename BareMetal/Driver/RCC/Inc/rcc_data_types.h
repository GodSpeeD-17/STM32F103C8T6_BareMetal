/**
 * @file	rcc_data_types.h
 * @author	Shrey Shah
 * @brief	Defines shared data types owned by the RCC Driver stack
 * @version	v1.1
 * @date	23-08-2026
 *
 * @details
 * @section RCC_DATA_TYPES_H_HIERARCHY Hierarchy
 * - Position: RCC Driver vocabulary foundation
 * - Included by: `rcc_defines.h` and the public `rcc.h` interface
 * - Uses: Foundational Core vocabulary from `stm32f1xx_data_types.h`
 *
 * @section RCC_DATA_TYPES_H_RESPONSIBILITY Responsibility
 * This header owns the scalar selector types shared by RCC Defines, Config,
 * Codec, and Driver code together with the read-only derived-frequency
 * snapshot returned by the public Driver. It gives every RCC layer one stable
 * semantic vocabulary without placing peripheral-specific types in Core.
 *
 * @section RCC_DATA_TYPES_H_BOUNDARY Dependency Boundary
 * This header defines types only. It includes no RCC register model, selector
 * value macros, writable configuration structures, LL access, Codec
 * transformation, or Driver orchestration, so every dependency continues to
 * point downward.
 */

// Header Guard
#ifndef RCC_DATA_TYPES_H_
#define RCC_DATA_TYPES_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "stm32f1xx_data_types.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief RCC Driver scalar type aliases
 * @defgroup RCC_03_Driver_01_DataTypes RCC Driver Data Types
 * @ingroup RCC_03_Driver
 * @details
 * These aliases express RCC selector domains independently from their numeric
 * values. `rcc_config.h` supplies the accepted configuration constants and
 * writable descriptors, while `rcc.h` supplies public operations.
 * @{
 */

// ==================================================================================================== //
// RCC Driver Data Types
// ==================================================================================================== //

/** @brief RCC bus selector type @typedef rcc_bus_t */
typedef uint8_t									rcc_bus_t;
/** @brief RCC bus-prescaler selector type @typedef rcc_bus_prescaler_t */
typedef uint8_t									rcc_bus_prescaler_t;
/** @brief RCC component-prescaler selector type @typedef rcc_component_prescaler_t */
typedef uint8_t									rcc_component_prescaler_t;
/** @brief RCC Flash-latency selector type @typedef rcc_flash_latency_t */
typedef uint8_t									rcc_flash_latency_t;
/** @brief RCC Flash-prefetch selector type @typedef rcc_flash_prefetch_t */
typedef uint8_t									rcc_flash_prefetch_t;
/** @brief RCC system-clock source selector type @typedef rcc_system_clock_t */
typedef uint8_t									rcc_system_clock_t;
/** @brief RCC PLL source selector type @typedef rcc_pll_src_t */
typedef uint8_t									rcc_pll_src_t;
/** @brief RCC PLL input-prescaler selector type @typedef rcc_pll_src_psc_t */
typedef uint8_t									rcc_pll_src_psc_t;
/** @brief RCC PLL multiplication-factor selector type @typedef rcc_pll_mul_t */
typedef uint8_t									rcc_pll_mul_t;

// ==================================================================================================== //
// RCC Derived Frequency Snapshot
// ==================================================================================================== //

/**
 * @brief RCC derived-frequency observation vocabulary
 * @defgroup RCC_03_Driver_02_Frequency RCC Driver Frequency Types and APIs
 * @ingroup RCC_03_Driver
 * @details Every RCC frequency is represented in hertz through @ref frequency_t.
 * @{
 */

/**
 * @brief Describes one coherent snapshot of the clocks derived by RCC
 * @struct rcc_clock_frequencies_t
 * @details
 * Every member is expressed in hertz. The Driver publishes this structure
 * only after all required hardware observations or configuration-derived
 * calculations complete successfully.
 */
typedef struct _rcc_clock_frequencies_t
{
	/**
	 * @brief System-clock frequency before AHB division
	 * Expected Values:
	 * - @ref `FREQ_ZERO` when the snapshot is cleared or unavailable
	 * - `1U..RCC_SYSCLK_MAX_FREQ` after a successful RCC observation
	 * @memberof rcc_clock_frequencies_t
	 */
	frequency_t	sysclk;
	/**
	 * @brief AHB clock frequency after the AHB prescaler
	 * Expected Values:
	 * - @ref `FREQ_ZERO` when the snapshot is cleared or unavailable
	 * - `1U..RCC_HCLK_MAX_FREQ` after a successful RCC observation
	 * @memberof rcc_clock_frequencies_t
	 */
	frequency_t	hclk;
	/**
	 * @brief APB1 clock frequency after the APB1 prescaler
	 * Expected Values:
	 * - @ref `FREQ_ZERO` when the snapshot is cleared or unavailable
	 * - `1U..RCC_PCLK1_MAX_FREQ` after a successful RCC observation
	 * @memberof rcc_clock_frequencies_t
	 */
	frequency_t	pclk1;
	/**
	 * @brief APB2 clock frequency after the APB2 prescaler
	 * Expected Values:
	 * - @ref `FREQ_ZERO` when the snapshot is cleared or unavailable
	 * - `1U..RCC_PCLK2_MAX_FREQ` after a successful RCC observation
	 * @memberof rcc_clock_frequencies_t
	 */
	frequency_t	pclk2;
	/**
	 * @brief ADC clock frequency derived from PCLK2
	 * Expected Values:
	 * - @ref `FREQ_ZERO` when the snapshot is cleared or unavailable
	 * - `1U..RCC_ADCCLK_MAX_FREQ` after a successful RCC observation
	 * @memberof rcc_clock_frequencies_t
	 */
	frequency_t	adcclk;
	/**
	 * @brief USB clock frequency derived from the PLL output
	 * Expected Values:
	 * - @ref `FREQ_ZERO` when PLL is not the active system-clock source
	 * - @ref `RCC_USBCLK_TARGET_FREQ` when the active clock tree supports USB
	 * @memberof rcc_clock_frequencies_t
	 */
	frequency_t	usbclk;
} rcc_clock_frequencies_t;

/** @} */ // RCC_03_Driver_02_Frequency

/** @} */ // RCC_03_Driver_01_DataTypes

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_DATA_TYPES_H_ */
