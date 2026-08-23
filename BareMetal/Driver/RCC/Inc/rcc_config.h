/**
 * @file	rcc_config.h
 * @author	Shrey Shah
 * @brief	Defines the RCC configuration vocabulary and descriptors
 * @version	v1.0
 * @date	23-08-2026
 *
 * @details
 * @section RCC_CONFIG_H_HIERARCHY Hierarchy
 * - Position: RCC Driver configuration vocabulary
 * - Included by: Public Driver interface and pure RCC Codec interface
 * - Uses: RCC-owned scalar aliases from `rcc_data_types.h`
 *
 * @section RCC_CONFIG_H_RESPONSIBILITY Responsibility
 * This header owns every accepted-value macro used to construct an RCC
 * configuration and every nested or root configuration structure. Keeping
 * these declarations together lets an application understand and build a
 * complete clock-tree request without searching through the operational API.
 *
 * @section RCC_CONFIG_H_BOUNDARY Dependency Boundary
 * This header defines immutable configuration vocabulary only. It performs no
 * validation, frequency calculation, register access, hardware sequencing, or
 * cache management and includes no Driver, Codec, LL, or Core register header.
 */

// Header Guard
#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_

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
// RCC Flash Configuration
// ==================================================================================================== //

/**
 * @brief RCC Flash configuration vocabulary
 * @defgroup RCC_03_Driver_03_Flash RCC Driver Flash Configuration
 * @ingroup RCC_03_Driver
 * @details
 * Flash latency must cover the requested SYSCLK before the clock is raised.
 * When SYSCLK is reduced, the Driver lowers latency only after the clock-tree
 * transition. Prefetch is configured independently through the same domain.
 * @{
 */

/** @brief Selects zero Flash wait states for SYSCLK through 24 MHz @def RCC_FLASH_LATENCY_0 */
#define RCC_FLASH_LATENCY_0			((rcc_flash_latency_t) 0U)
/** @brief Selects one Flash wait state for SYSCLK above 24 MHz through 48 MHz @def RCC_FLASH_LATENCY_1 */
#define RCC_FLASH_LATENCY_1			((rcc_flash_latency_t) 1U)
/** @brief Selects two Flash wait states for SYSCLK above 48 MHz through 72 MHz @def RCC_FLASH_LATENCY_2 */
#define RCC_FLASH_LATENCY_2			((rcc_flash_latency_t) 2U)

/** @brief Disables the Flash instruction prefetch buffer @def RCC_FLASH_PREFETCH_DISABLE */
#define RCC_FLASH_PREFETCH_DISABLE		((rcc_flash_prefetch_t) 0U)
/** @brief Enables the Flash instruction prefetch buffer @def RCC_FLASH_PREFETCH_ENABLE */
#define RCC_FLASH_PREFETCH_ENABLE		((rcc_flash_prefetch_t) 1U)

/** @brief Maximum SYSCLK admitted with zero Flash wait states @def RCC_FLASH_LATENCY_0_MAX_FREQ */
#define RCC_FLASH_LATENCY_0_MAX_FREQ		((frequency_t) 24000000UL)
/** @brief Maximum SYSCLK admitted with one Flash wait state @def RCC_FLASH_LATENCY_1_MAX_FREQ */
#define RCC_FLASH_LATENCY_1_MAX_FREQ		((frequency_t) 48000000UL)

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
 * @brief RCC system-clock and PLL configuration vocabulary
 * @defgroup RCC_03_Driver_04_SystemClock RCC Driver System Clock Configuration
 * @ingroup RCC_03_Driver
 * @details
 * The system source selects HSI, HSE, or PLL. PLL configuration becomes
 * operational only when PLL is selected as SYSCLK, while its source,
 * prescaler, and multiplier jointly define the PLL output frequency.
 * @{
 */

/** @brief Selects the internal 8 MHz HSI oscillator as SYSCLK @def RCC_SYS_CLK_HSI */
#define RCC_SYS_CLK_HSI			((rcc_system_clock_t) 0U)
/** @brief Selects the board HSE oscillator directly as SYSCLK @def RCC_SYS_CLK_HSE */
#define RCC_SYS_CLK_HSE			((rcc_system_clock_t) 1U)
/** @brief Selects the configured PLL output as SYSCLK @def RCC_SYS_CLK_PLL */
#define RCC_SYS_CLK_PLL			((rcc_system_clock_t) 2U)

/** @brief Selects the fixed HSI-divided-by-two signal as PLL input @def RCC_PLL_SRC_HSI */
#define RCC_PLL_SRC_HSI			((rcc_pll_src_t) 0U)
/** @brief Selects the HSE oscillator path as PLL input @def RCC_PLL_SRC_HSE */
#define RCC_PLL_SRC_HSE			((rcc_pll_src_t) 1U)

/** @brief Selects the mandatory divide-by-two stage for the HSI PLL path @def RCC_PLL_SRC_HSI_DIV_2 */
#define RCC_PLL_SRC_HSI_DIV_2		((rcc_pll_src_psc_t) 0U)
/** @brief Selects the undivided HSE signal as PLL input @def RCC_PLL_SRC_HSE_DIV_1 */
#define RCC_PLL_SRC_HSE_DIV_1		((rcc_pll_src_psc_t) 1U)
/** @brief Selects HSE divided by two as PLL input @def RCC_PLL_SRC_HSE_DIV_2 */
#define RCC_PLL_SRC_HSE_DIV_2		((rcc_pll_src_psc_t) 2U)

/** @brief Selects PLL input multiplication by 2 @def RCC_PLL_MUL_2 */
#define RCC_PLL_MUL_2			((rcc_pll_mul_t) 2U)
/** @brief Selects PLL input multiplication by 3 @def RCC_PLL_MUL_3 */
#define RCC_PLL_MUL_3			((rcc_pll_mul_t) 3U)
/** @brief Selects PLL input multiplication by 4 @def RCC_PLL_MUL_4 */
#define RCC_PLL_MUL_4			((rcc_pll_mul_t) 4U)
/** @brief Selects PLL input multiplication by 5 @def RCC_PLL_MUL_5 */
#define RCC_PLL_MUL_5			((rcc_pll_mul_t) 5U)
/** @brief Selects PLL input multiplication by 6 @def RCC_PLL_MUL_6 */
#define RCC_PLL_MUL_6			((rcc_pll_mul_t) 6U)
/** @brief Selects PLL input multiplication by 7 @def RCC_PLL_MUL_7 */
#define RCC_PLL_MUL_7			((rcc_pll_mul_t) 7U)
/** @brief Selects PLL input multiplication by 8 @def RCC_PLL_MUL_8 */
#define RCC_PLL_MUL_8			((rcc_pll_mul_t) 8U)
/** @brief Selects PLL input multiplication by 9 @def RCC_PLL_MUL_9 */
#define RCC_PLL_MUL_9			((rcc_pll_mul_t) 9U)
/** @brief Selects PLL input multiplication by 10 @def RCC_PLL_MUL_10 */
#define RCC_PLL_MUL_10			((rcc_pll_mul_t) 10U)
/** @brief Selects PLL input multiplication by 11 @def RCC_PLL_MUL_11 */
#define RCC_PLL_MUL_11			((rcc_pll_mul_t) 11U)
/** @brief Selects PLL input multiplication by 12 @def RCC_PLL_MUL_12 */
#define RCC_PLL_MUL_12			((rcc_pll_mul_t) 12U)
/** @brief Selects PLL input multiplication by 13 @def RCC_PLL_MUL_13 */
#define RCC_PLL_MUL_13			((rcc_pll_mul_t) 13U)
/** @brief Selects PLL input multiplication by 14 @def RCC_PLL_MUL_14 */
#define RCC_PLL_MUL_14			((rcc_pll_mul_t) 14U)
/** @brief Selects PLL input multiplication by 15 @def RCC_PLL_MUL_15 */
#define RCC_PLL_MUL_15			((rcc_pll_mul_t) 15U)
/** @brief Selects PLL input multiplication by 16 @def RCC_PLL_MUL_16 */
#define RCC_PLL_MUL_16			((rcc_pll_mul_t) 16U)

/** @brief Internal high-speed oscillator nominal frequency @def RCC_HSI_FREQ */
#define RCC_HSI_FREQ			((frequency_t) 8000000UL)
/** @brief Blue Pill external high-speed oscillator frequency assumption @def RCC_HSE_FREQ */
#define RCC_HSE_FREQ			((frequency_t) 8000000UL)
/** @brief Maximum supported SYSCLK frequency @def RCC_SYSCLK_MAX_FREQ */
#define RCC_SYSCLK_MAX_FREQ		((frequency_t) 72000000UL)
/** @brief Maximum supported AHB clock frequency @def RCC_HCLK_MAX_FREQ */
#define RCC_HCLK_MAX_FREQ		(RCC_SYSCLK_MAX_FREQ)
/** @brief Maximum supported APB1 clock frequency @def RCC_PCLK1_MAX_FREQ */
#define RCC_PCLK1_MAX_FREQ		((frequency_t) 36000000UL)
/** @brief Maximum supported APB2 clock frequency @def RCC_PCLK2_MAX_FREQ */
#define RCC_PCLK2_MAX_FREQ		((frequency_t) 72000000UL)

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
 * @brief RCC bus and component prescaler configuration vocabulary
 * @defgroup RCC_03_Driver_05_Prescalers RCC Driver Prescaler Configuration
 * @ingroup RCC_03_Driver
 * @details
 * AHB divides SYSCLK, APB1 and APB2 independently divide HCLK, ADC divides
 * PCLK2, and USB selects either the PLL output or its divide-by-1.5 path.
 * @{
 */

/** @brief Selects AHB clock division by 1 @def RCC_AHB_DIV_1 */
#define RCC_AHB_DIV_1			((rcc_bus_prescaler_t) 0U)
/** @brief Selects AHB clock division by 2 @def RCC_AHB_DIV_2 */
#define RCC_AHB_DIV_2			((rcc_bus_prescaler_t) 1U)
/** @brief Selects AHB clock division by 4 @def RCC_AHB_DIV_4 */
#define RCC_AHB_DIV_4			((rcc_bus_prescaler_t) 2U)
/** @brief Selects AHB clock division by 8 @def RCC_AHB_DIV_8 */
#define RCC_AHB_DIV_8			((rcc_bus_prescaler_t) 3U)
/** @brief Selects AHB clock division by 16 @def RCC_AHB_DIV_16 */
#define RCC_AHB_DIV_16			((rcc_bus_prescaler_t) 4U)
/** @brief Selects AHB clock division by 64 @def RCC_AHB_DIV_64 */
#define RCC_AHB_DIV_64			((rcc_bus_prescaler_t) 5U)
/** @brief Selects AHB clock division by 128 @def RCC_AHB_DIV_128 */
#define RCC_AHB_DIV_128			((rcc_bus_prescaler_t) 6U)
/** @brief Selects AHB clock division by 256 @def RCC_AHB_DIV_256 */
#define RCC_AHB_DIV_256			((rcc_bus_prescaler_t) 7U)
/** @brief Selects AHB clock division by 512 @def RCC_AHB_DIV_512 */
#define RCC_AHB_DIV_512			((rcc_bus_prescaler_t) 8U)

/** @brief Selects APB1 clock division by 1 @def RCC_APB1_DIV_1 */
#define RCC_APB1_DIV_1			((rcc_bus_prescaler_t) 0U)
/** @brief Selects APB1 clock division by 2 @def RCC_APB1_DIV_2 */
#define RCC_APB1_DIV_2			((rcc_bus_prescaler_t) 1U)
/** @brief Selects APB1 clock division by 4 @def RCC_APB1_DIV_4 */
#define RCC_APB1_DIV_4			((rcc_bus_prescaler_t) 2U)
/** @brief Selects APB1 clock division by 8 @def RCC_APB1_DIV_8 */
#define RCC_APB1_DIV_8			((rcc_bus_prescaler_t) 3U)
/** @brief Selects APB1 clock division by 16 @def RCC_APB1_DIV_16 */
#define RCC_APB1_DIV_16			((rcc_bus_prescaler_t) 4U)

/** @brief Selects APB2 clock division by 1 @def RCC_APB2_DIV_1 */
#define RCC_APB2_DIV_1			((rcc_bus_prescaler_t) 0U)
/** @brief Selects APB2 clock division by 2 @def RCC_APB2_DIV_2 */
#define RCC_APB2_DIV_2			((rcc_bus_prescaler_t) 1U)
/** @brief Selects APB2 clock division by 4 @def RCC_APB2_DIV_4 */
#define RCC_APB2_DIV_4			((rcc_bus_prescaler_t) 2U)
/** @brief Selects APB2 clock division by 8 @def RCC_APB2_DIV_8 */
#define RCC_APB2_DIV_8			((rcc_bus_prescaler_t) 3U)
/** @brief Selects APB2 clock division by 16 @def RCC_APB2_DIV_16 */
#define RCC_APB2_DIV_16			((rcc_bus_prescaler_t) 4U)

/** @brief Selects ADC clock division by 2 @def RCC_ADC_DIV_2 */
#define RCC_ADC_DIV_2			((rcc_component_prescaler_t) 0U)
/** @brief Selects ADC clock division by 4 @def RCC_ADC_DIV_4 */
#define RCC_ADC_DIV_4			((rcc_component_prescaler_t) 1U)
/** @brief Selects ADC clock division by 6 @def RCC_ADC_DIV_6 */
#define RCC_ADC_DIV_6			((rcc_component_prescaler_t) 2U)
/** @brief Selects ADC clock division by 8 @def RCC_ADC_DIV_8 */
#define RCC_ADC_DIV_8			((rcc_component_prescaler_t) 3U)

/** @brief Selects the PLL-output divide-by-1.5 USB clock path @def RCC_USB_DIV_1_5 */
#define RCC_USB_DIV_1_5			((rcc_component_prescaler_t) 0U)
/** @brief Selects the undivided PLL output as USB clock @def RCC_USB_DIV_1 */
#define RCC_USB_DIV_1			((rcc_component_prescaler_t) 1U)

/** @brief Maximum supported ADC clock frequency @def RCC_ADCCLK_MAX_FREQ */
#define RCC_ADCCLK_MAX_FREQ		((frequency_t) 14000000UL)
/** @brief Required USB clock frequency for full-speed USB operation @def RCC_USBCLK_TARGET_FREQ */
#define RCC_USBCLK_TARGET_FREQ		((frequency_t) 48000000UL)

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
