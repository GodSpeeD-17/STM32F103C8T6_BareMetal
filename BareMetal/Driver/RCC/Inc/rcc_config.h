/**
 * @file	rcc_config.h
 * @author	Shrey Shah
 * @brief	Defines the RCC configuration descriptors
 * @version	v1.1
 * @date	23-08-2026
 *
 * @details
 * @section RCC_CONFIG_H_HIERARCHY Hierarchy
 * - Position: RCC Driver configuration-description layer
 * - Included by: Public Driver interface
 * - Uses: RCC selector vocabulary from `rcc_defines.h`
 *
 * @section RCC_CONFIG_H_RESPONSIBILITY Responsibility
 * This header owns every nested and root structure used to describe an RCC
 * configuration. `rcc_defines.h` supplies the accepted symbolic values used
 * to initialize these structures.
 *
 * @section RCC_CONFIG_H_BOUNDARY Dependency Boundary
 * This header defines immutable configuration structures only. It performs
 * no validation, frequency calculation, register access, hardware sequencing,
 * or cache management and includes no Driver, Codec, LL, or Core register
 * header.
 */

// Header Guard
#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "rcc_defines.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup RCC_03_Driver
 * @{
 */

// ==================================================================================================== //
// RCC Flash Configuration
// ==================================================================================================== //

/**
 * @brief RCC Flash configuration structure
 * @defgroup RCC_03_Driver_03_Flash RCC Driver Flash Configuration
 * @ingroup RCC_03_Driver
 * @details
 * Flash latency must cover the requested SYSCLK before the clock is raised.
 * When SYSCLK is reduced, the Driver lowers latency only after the clock-tree
 * transition. Prefetch is configured independently through the same domain.
 * @{
 */

/**
 * @brief Describes the Flash access policy coupled to an RCC clock transition
 * @struct rcc_flash_config_t
 */
typedef struct _rcc_flash_config_t
{
	/**
	 * @brief Flash wait-state selector
	 * Accepted Values:
	 * - @ref `RCC_FLASH_LATENCY_0`
	 * - @ref `RCC_FLASH_LATENCY_1`
	 * - @ref `RCC_FLASH_LATENCY_2`
	 * @memberof rcc_flash_config_t
	 */
	rcc_flash_latency_t		latency;
	/**
	 * @brief Flash pre-fetch selector
	 * Accepted Values:
	 * - @ref `RCC_FLASH_PREFETCH_DISABLE`
	 * - @ref `RCC_FLASH_PREFETCH_ENABLE`
	 * @memberof rcc_flash_config_t
	 */
	rcc_flash_prefetch_t	prefetch;
} rcc_flash_config_t;

/** @} */ // RCC_03_Driver_03_Flash

// ==================================================================================================== //
// RCC System Clock and PLL Configuration
// ==================================================================================================== //

/**
 * @brief RCC system-clock and PLL configuration structures
 * @defgroup RCC_03_Driver_04_SystemClock RCC Driver System Clock Configuration
 * @ingroup RCC_03_Driver
 * @details
 * The system source selects HSI, HSE, or PLL. PLL configuration becomes
 * operational only when PLL is selected as SYSCLK, while its source,
 * prescaler, and multiplier jointly define the PLL output frequency.
 * @{
 */

/**
 * @brief Describes the PLL source path and multiplication policy
 * @struct rcc_pll_config_t
 */
typedef struct _rcc_pll_config_t
{
	/**
	 * @brief PLL input-source selector
	 * Accepted Values:
	 * - @ref `RCC_PLL_SRC_HSI`
	 * - @ref `RCC_PLL_SRC_HSE`
	 * @memberof rcc_pll_config_t
	 */
	rcc_pll_src_t		source;
	/**
	 * @brief PLL input-source prescaler selector
	 * Accepted Values:
	 * - @ref `RCC_PLL_SRC_HSI_DIV_2` when @ref `RCC_PLL_SRC_HSI` is selected
	 * - @ref `RCC_PLL_SRC_HSE_DIV_1` when an undivided @ref `RCC_PLL_SRC_HSE` is required
	 * - @ref `RCC_PLL_SRC_HSE_DIV_2` when a divided @ref `RCC_PLL_SRC_HSE` is required
	 * @memberof rcc_pll_config_t
	 */
	rcc_pll_src_psc_t	source_prescaler;
	/**
	 * @brief PLL input multiplication-factor selector
	 * Accepted Values:
	 * - @ref `RCC_PLL_MUL_2`
	 * - @ref `RCC_PLL_MUL_3`
	 * - @ref `RCC_PLL_MUL_4`
	 * - @ref `RCC_PLL_MUL_5`
	 * - @ref `RCC_PLL_MUL_6`
	 * - @ref `RCC_PLL_MUL_7`
	 * - @ref `RCC_PLL_MUL_8`
	 * - @ref `RCC_PLL_MUL_9`
	 * - @ref `RCC_PLL_MUL_10`
	 * - @ref `RCC_PLL_MUL_11`
	 * - @ref `RCC_PLL_MUL_12`
	 * - @ref `RCC_PLL_MUL_13`
	 * - @ref `RCC_PLL_MUL_14`
	 * - @ref `RCC_PLL_MUL_15`
	 * - @ref `RCC_PLL_MUL_16`
	 * @memberof rcc_pll_config_t
	 */
	rcc_pll_mul_t		multiplication_factor;
} rcc_pll_config_t;

/**
 * @brief Describes the requested SYSCLK source and its optional PLL domain
 * @struct rcc_sys_clk_config_t
 */
typedef struct _rcc_sys_clk_config_t
{
	/**
	 * @brief System-clock source selector
	 * Accepted Values:
	 * - @ref `RCC_SYS_CLK_HSI`
	 * - @ref `RCC_SYS_CLK_HSE`
	 * - @ref `RCC_SYS_CLK_PLL`
	 * @memberof rcc_sys_clk_config_t
	 */
	rcc_system_clock_t	clk_src;
	/**
	 * @brief PLL policy used when the PLL output supplies SYSCLK
	 * Accepted Values:
	 * - A completely initialized @ref rcc_pll_config_t compatible with the requested PLL input path
	 * @memberof rcc_sys_clk_config_t
	 */
	rcc_pll_config_t	pll;
} rcc_sys_clk_config_t;

/** @} */ // RCC_03_Driver_04_SystemClock

// ==================================================================================================== //
// RCC Prescaler Configuration
// ==================================================================================================== //

/**
 * @brief RCC bus and component prescaler configuration structures
 * @defgroup RCC_03_Driver_05_Prescalers RCC Driver Prescaler Configuration
 * @ingroup RCC_03_Driver
 * @details
 * AHB divides SYSCLK, APB1 and APB2 independently divide HCLK, ADC divides
 * PCLK2, and USB selects either the PLL output or its divide-by-1.5 path.
 * @{
 */

/**
 * @brief Describes the AHB, APB1, and APB2 prescaler domains
 * @struct rcc_bus_config_t
 */
typedef struct _rcc_bus_config_t
{
	/**
	 * @brief AHB clock-prescaler selector
	 * Accepted Values:
	 * - @ref `RCC_AHB_DIV_1`
	 * - @ref `RCC_AHB_DIV_2`
	 * - @ref `RCC_AHB_DIV_4`
	 * - @ref `RCC_AHB_DIV_8`
	 * - @ref `RCC_AHB_DIV_16`
	 * - @ref `RCC_AHB_DIV_64`
	 * - @ref `RCC_AHB_DIV_128`
	 * - @ref `RCC_AHB_DIV_256`
	 * - @ref `RCC_AHB_DIV_512`
	 * @memberof rcc_bus_config_t
	 */
	rcc_bus_prescaler_t	AHB;
	/**
	 * @brief APB1 clock-prescaler selector
	 * Accepted Values:
	 * - @ref `RCC_APB1_DIV_1`
	 * - @ref `RCC_APB1_DIV_2`
	 * - @ref `RCC_APB1_DIV_4`
	 * - @ref `RCC_APB1_DIV_8`
	 * - @ref `RCC_APB1_DIV_16`
	 * @memberof rcc_bus_config_t
	 */
	rcc_bus_prescaler_t	APB1;
	/**
	 * @brief APB2 clock-prescaler selector
	 * Accepted Values:
	 * - @ref `RCC_APB2_DIV_1`
	 * - @ref `RCC_APB2_DIV_2`
	 * - @ref `RCC_APB2_DIV_4`
	 * - @ref `RCC_APB2_DIV_8`
	 * - @ref `RCC_APB2_DIV_16`
	 * @memberof rcc_bus_config_t
	 */
	rcc_bus_prescaler_t	APB2;
} rcc_bus_config_t;

/**
 * @brief Describes the ADC and USB component prescaler domains
 * @struct rcc_component_config_t
 */
typedef struct _rcc_component_config_t
{
	/**
	 * @brief ADC clock-prescaler selector
	 * Accepted Values:
	 * - @ref `RCC_ADC_DIV_2`
	 * - @ref `RCC_ADC_DIV_4`
	 * - @ref `RCC_ADC_DIV_6`
	 * - @ref `RCC_ADC_DIV_8`
	 * @memberof rcc_component_config_t
	 */
	rcc_component_prescaler_t	ADC;
	/**
	 * @brief USB clock-prescaler selector
	 * Accepted Values:
	 * - @ref `RCC_USB_DIV_1_5`
	 * - @ref `RCC_USB_DIV_1`
	 * @memberof rcc_component_config_t
	 */
	rcc_component_prescaler_t	USB;
} rcc_component_config_t;

/** @} */ // RCC_03_Driver_05_Prescalers

// ==================================================================================================== //
// RCC Aggregate Configuration
// ==================================================================================================== //

/**
 * @brief RCC aggregate configuration descriptors
 * @defgroup RCC_03_Driver_06_Config RCC Driver Aggregate Configuration
 * @ingroup RCC_03_Driver
 * @details
 * The clock-tree descriptor groups the independently coherent system, bus,
 * and component domains. The root descriptor couples that clock tree to the
 * Flash policy required for a safe frequency transition.
 * @{
 */

/**
 * @brief Describes every configurable RCC clock-tree domain
 * @struct rcc_clock_tree_config_t
 */
typedef struct _rcc_clock_tree_config_t
{
	/**
	 * @brief System-clock source and optional PLL policy
	 * Accepted Values:
	 * - A completely initialized @ref `rcc_sys_clk_config_t`
	 * @memberof rcc_clock_tree_config_t
	 */
	rcc_sys_clk_config_t		system;
	/**
	 * @brief AHB, APB1, and APB2 prescaler policy
	 * Accepted Values:
	 * - A completely initialized @ref `rcc_bus_config_t`
	 * @memberof rcc_clock_tree_config_t
	 */
	rcc_bus_config_t			bus;
	/**
	 * @brief ADC and USB prescaler policy
	 * Accepted Values:
	 * - A completely initialized @ref `rcc_component_config_t`
	 * @memberof rcc_clock_tree_config_t
	 */
	rcc_component_config_t		component;
} rcc_clock_tree_config_t;

/**
 * @brief Describes one complete, validated RCC and Flash transition request
 * @struct rcc_config_t
 */
typedef struct _rcc_config_t
{
	/**
	 * @brief Flash-access policy ordered around the clock transition
	 * Accepted Values:
	 * - A completely initialized @ref `rcc_flash_config_t`
	 * @memberof rcc_config_t
	 */
	rcc_flash_config_t		flash;
	/**
	 * @brief Complete target clock-tree policy
	 * Accepted Values:
	 * - A completely initialized @ref `rcc_clock_tree_config_t`
	 * @memberof rcc_config_t
	 */
	rcc_clock_tree_config_t	clock_tree;
} rcc_config_t;

/** @} */ // RCC_03_Driver_06_Config

/** @} */ // RCC_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_CONFIG_H_ */
