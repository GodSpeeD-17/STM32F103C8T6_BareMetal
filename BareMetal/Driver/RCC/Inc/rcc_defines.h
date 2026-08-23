/**
 * @file	rcc_defines.h
 * @author	Shrey Shah
 * @brief	Defines public RCC constants and selector guards
 * @version	v3.0
 * @date	23-08-2026
 *
 * @details
 * @section RCC_DEFINES_H_HIERARCHY Hierarchy
 * - Position: RCC Driver symbolic-value layer
 * - Included by: RCC configuration, Codec, and public Driver interfaces
 * - Uses: RCC-owned scalar aliases from `rcc_data_types.h`
 *
 * @section RCC_DEFINES_H_RESPONSIBILITY Responsibility
 * This header owns every public RCC selector, frequency policy constant, and
 * Driver-domain selector guard. Configuration structures consume these values
 * from `rcc_config.h`; operational APIs consume them from `rcc.h`.
 *
 * @section RCC_DEFINES_H_BOUNDARY Dependency Boundary
 * This header contains no configuration structures, raw register fields,
 * Codec transformation, LL access, Driver orchestration, or hardware mutation.
 * Driver-domain guards validate semantic selectors only; LL raw-field guards
 * remain in `rcc_ll.h`.
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
 * @brief RCC Driver symbolic constants and selector guards
 * @defgroup RCC_03_Driver_02_Defines RCC Driver Defines
 * @ingroup RCC_03_Driver
 * @details
 * These values form the public vocabulary used to build RCC configurations,
 * select physical buses, and validate Driver-level selector capabilities.
 * They do not encode raw RCC register fields.
 * @{
 */

// ==================================================================================================== //
// RCC Frequency Policy
// ==================================================================================================== //

/** @brief Represents an inactive, unavailable, or not-yet-derived RCC clock @def RCC_FREQ_ZERO */
#define RCC_FREQ_ZERO				FREQ_ZERO
/** @brief Internal high-speed oscillator nominal frequency @def RCC_HSI_FREQ */
#define RCC_HSI_FREQ				((frequency_t) 8000000UL)
/** @brief Blue Pill external high-speed oscillator frequency assumption @def RCC_HSE_FREQ */
#define RCC_HSE_FREQ				((frequency_t) 8000000UL)
/** @brief Maximum supported SYSCLK frequency @def RCC_SYSCLK_MAX_FREQ */
#define RCC_SYSCLK_MAX_FREQ			((frequency_t) 72000000UL)
/** @brief Maximum supported AHB clock frequency @def RCC_HCLK_MAX_FREQ */
#define RCC_HCLK_MAX_FREQ			(RCC_SYSCLK_MAX_FREQ)
/** @brief Maximum supported APB1 clock frequency @def RCC_PCLK1_MAX_FREQ */
#define RCC_PCLK1_MAX_FREQ			((frequency_t) 36000000UL)
/** @brief Maximum supported APB2 clock frequency @def RCC_PCLK2_MAX_FREQ */
#define RCC_PCLK2_MAX_FREQ			((frequency_t) 72000000UL)
/** @brief Maximum supported ADC clock frequency @def RCC_ADCCLK_MAX_FREQ */
#define RCC_ADCCLK_MAX_FREQ			((frequency_t) 14000000UL)
/** @brief Required USB clock frequency for full-speed USB operation @def RCC_USBCLK_TARGET_FREQ */
#define RCC_USBCLK_TARGET_FREQ		((frequency_t) 48000000UL)

// ==================================================================================================== //
// RCC Physical Bus Selectors and Guards
// ==================================================================================================== //

/** @brief Selects the physical AHB register bank and derived clock @def RCC_AHB_BUS */
#define RCC_AHB_BUS					((rcc_bus_t) 0U)
/** @brief Selects the physical APB1 register bank and derived clock @def RCC_APB1_BUS */
#define RCC_APB1_BUS				((rcc_bus_t) 1U)
/** @brief Selects the physical APB2 register bank and derived clock @def RCC_APB2_BUS */
#define RCC_APB2_BUS				((rcc_bus_t) 2U)

/**
 * @brief Validates a physical RCC bus selector
 * @def RCC_IS_BUS_VALID
 * @param[in] _BUS Physical RCC bus selector
 * Accepted values:
 * - @ref `RCC_AHB_BUS`
 * - @ref `RCC_APB1_BUS`
 * - @ref `RCC_APB2_BUS`
 * @returns Physical-bus selector validity
 * @retval - `0x00U`: Selector does not identify a physical RCC bus
 * @retval - `0x01U`: Selector identifies AHB, APB1, or APB2
 * @warning Evaluate only side-effect-free arguments because @p _BUS may be evaluated more than once
 */
#define RCC_IS_BUS_VALID(_BUS)					\
(												\
	((_BUS) == RCC_AHB_BUS)		||				\
	((_BUS) == RCC_APB1_BUS)	||				\
	((_BUS) == RCC_APB2_BUS)					\
)

/**
 * @brief Validates an RCC peripheral-reset bus selector
 * @def RCC_IS_RESET_BUS_VALID
 * @param[in] _BUS Physical RCC bus selector
 * Accepted values:
 * - @ref `RCC_APB1_BUS`
 * - @ref `RCC_APB2_BUS`
 * @returns Peripheral-reset bus selector validity
 * @retval - `0x00U`: Selector has no supported RCC peripheral-reset register
 * @retval - `0x01U`: Selector identifies APB1 or APB2
 * @warning Evaluate only side-effect-free arguments because @p _BUS may be evaluated more than once
 */
#define RCC_IS_RESET_BUS_VALID(_BUS)			\
(												\
	((_BUS) == RCC_APB1_BUS)	||				\
	((_BUS) == RCC_APB2_BUS)					\
)

// ==================================================================================================== //
// RCC Flash Configuration Values
// ==================================================================================================== //

/** @brief Selects zero Flash wait states for SYSCLK through 24 MHz @def RCC_FLASH_LATENCY_0 */
#define RCC_FLASH_LATENCY_0					((rcc_flash_latency_t) 0U)
/** @brief Selects one Flash wait state for SYSCLK above 24 MHz through 48 MHz @def RCC_FLASH_LATENCY_1 */
#define RCC_FLASH_LATENCY_1					((rcc_flash_latency_t) 1U)
/** @brief Selects two Flash wait states for SYSCLK above 48 MHz through 72 MHz @def RCC_FLASH_LATENCY_2 */
#define RCC_FLASH_LATENCY_2					((rcc_flash_latency_t) 2U)

/** @brief Disables the Flash instruction prefetch buffer @def RCC_FLASH_PREFETCH_DISABLE */
#define RCC_FLASH_PREFETCH_DISABLE			((rcc_flash_prefetch_t) 0U)
/** @brief Enables the Flash instruction prefetch buffer @def RCC_FLASH_PREFETCH_ENABLE */
#define RCC_FLASH_PREFETCH_ENABLE			((rcc_flash_prefetch_t) 1U)

/** @brief Maximum SYSCLK admitted with zero Flash wait states @def RCC_FLASH_LATENCY_0_MAX_FREQ */
#define RCC_FLASH_LATENCY_0_MAX_FREQ		((frequency_t) 24000000UL)
/** @brief Maximum SYSCLK admitted with one Flash wait state @def RCC_FLASH_LATENCY_1_MAX_FREQ */
#define RCC_FLASH_LATENCY_1_MAX_FREQ		((frequency_t) 48000000UL)

// ==================================================================================================== //
// RCC System Clock and PLL Configuration Values
// ==================================================================================================== //

/** @brief Selects the internal 8 MHz HSI oscillator as SYSCLK @def RCC_SYS_CLK_HSI */
#define RCC_SYS_CLK_HSI						((rcc_system_clock_t) 0U)
/** @brief Selects the board HSE oscillator directly as SYSCLK @def RCC_SYS_CLK_HSE */
#define RCC_SYS_CLK_HSE						((rcc_system_clock_t) 1U)
/** @brief Selects the configured PLL output as SYSCLK @def RCC_SYS_CLK_PLL */
#define RCC_SYS_CLK_PLL						((rcc_system_clock_t) 2U)

/** @brief Selects the fixed HSI-divided-by-two signal as PLL input @def RCC_PLL_SRC_HSI */
#define RCC_PLL_SRC_HSI						((rcc_pll_src_t) 0U)
/** @brief Selects the HSE oscillator path as PLL input @def RCC_PLL_SRC_HSE */
#define RCC_PLL_SRC_HSE						((rcc_pll_src_t) 1U)

/** @brief Selects the mandatory divide-by-two stage for the HSI PLL path @def RCC_PLL_SRC_HSI_DIV_2 */
#define RCC_PLL_SRC_HSI_DIV_2				((rcc_pll_src_psc_t) 0U)
/** @brief Selects the undivided HSE signal as PLL input @def RCC_PLL_SRC_HSE_DIV_1 */
#define RCC_PLL_SRC_HSE_DIV_1				((rcc_pll_src_psc_t) 1U)
/** @brief Selects HSE divided by two as PLL input @def RCC_PLL_SRC_HSE_DIV_2 */
#define RCC_PLL_SRC_HSE_DIV_2				((rcc_pll_src_psc_t) 2U)

/** @brief Selects PLL input multiplication by 2 @def RCC_PLL_MUL_2 */
#define RCC_PLL_MUL_2						((rcc_pll_mul_t) 2U)
/** @brief Selects PLL input multiplication by 3 @def RCC_PLL_MUL_3 */
#define RCC_PLL_MUL_3						((rcc_pll_mul_t) 3U)
/** @brief Selects PLL input multiplication by 4 @def RCC_PLL_MUL_4 */
#define RCC_PLL_MUL_4						((rcc_pll_mul_t) 4U)
/** @brief Selects PLL input multiplication by 5 @def RCC_PLL_MUL_5 */
#define RCC_PLL_MUL_5						((rcc_pll_mul_t) 5U)
/** @brief Selects PLL input multiplication by 6 @def RCC_PLL_MUL_6 */
#define RCC_PLL_MUL_6						((rcc_pll_mul_t) 6U)
/** @brief Selects PLL input multiplication by 7 @def RCC_PLL_MUL_7 */
#define RCC_PLL_MUL_7						((rcc_pll_mul_t) 7U)
/** @brief Selects PLL input multiplication by 8 @def RCC_PLL_MUL_8 */
#define RCC_PLL_MUL_8						((rcc_pll_mul_t) 8U)
/** @brief Selects PLL input multiplication by 9 @def RCC_PLL_MUL_9 */
#define RCC_PLL_MUL_9						((rcc_pll_mul_t) 9U)
/** @brief Selects PLL input multiplication by 10 @def RCC_PLL_MUL_10 */
#define RCC_PLL_MUL_10						((rcc_pll_mul_t) 10U)
/** @brief Selects PLL input multiplication by 11 @def RCC_PLL_MUL_11 */
#define RCC_PLL_MUL_11						((rcc_pll_mul_t) 11U)
/** @brief Selects PLL input multiplication by 12 @def RCC_PLL_MUL_12 */
#define RCC_PLL_MUL_12						((rcc_pll_mul_t) 12U)
/** @brief Selects PLL input multiplication by 13 @def RCC_PLL_MUL_13 */
#define RCC_PLL_MUL_13						((rcc_pll_mul_t) 13U)
/** @brief Selects PLL input multiplication by 14 @def RCC_PLL_MUL_14 */
#define RCC_PLL_MUL_14						((rcc_pll_mul_t) 14U)
/** @brief Selects PLL input multiplication by 15 @def RCC_PLL_MUL_15 */
#define RCC_PLL_MUL_15						((rcc_pll_mul_t) 15U)
/** @brief Selects PLL input multiplication by 16 @def RCC_PLL_MUL_16 */
#define RCC_PLL_MUL_16						((rcc_pll_mul_t) 16U)

// ==================================================================================================== //
// RCC Prescaler Configuration Values
// ==================================================================================================== //

/** @brief Selects AHB clock division by 1 @def RCC_AHB_DIV_1 */
#define RCC_AHB_DIV_1						((rcc_bus_prescaler_t) 0U)
/** @brief Selects AHB clock division by 2 @def RCC_AHB_DIV_2 */
#define RCC_AHB_DIV_2						((rcc_bus_prescaler_t) 1U)
/** @brief Selects AHB clock division by 4 @def RCC_AHB_DIV_4 */
#define RCC_AHB_DIV_4						((rcc_bus_prescaler_t) 2U)
/** @brief Selects AHB clock division by 8 @def RCC_AHB_DIV_8 */
#define RCC_AHB_DIV_8						((rcc_bus_prescaler_t) 3U)
/** @brief Selects AHB clock division by 16 @def RCC_AHB_DIV_16 */
#define RCC_AHB_DIV_16						((rcc_bus_prescaler_t) 4U)
/** @brief Selects AHB clock division by 64 @def RCC_AHB_DIV_64 */
#define RCC_AHB_DIV_64						((rcc_bus_prescaler_t) 5U)
/** @brief Selects AHB clock division by 128 @def RCC_AHB_DIV_128 */
#define RCC_AHB_DIV_128						((rcc_bus_prescaler_t) 6U)
/** @brief Selects AHB clock division by 256 @def RCC_AHB_DIV_256 */
#define RCC_AHB_DIV_256						((rcc_bus_prescaler_t) 7U)
/** @brief Selects AHB clock division by 512 @def RCC_AHB_DIV_512 */
#define RCC_AHB_DIV_512						((rcc_bus_prescaler_t) 8U)

/** @brief Selects APB1 clock division by 1 @def RCC_APB1_DIV_1 */
#define RCC_APB1_DIV_1						((rcc_bus_prescaler_t) 0U)
/** @brief Selects APB1 clock division by 2 @def RCC_APB1_DIV_2 */
#define RCC_APB1_DIV_2						((rcc_bus_prescaler_t) 1U)
/** @brief Selects APB1 clock division by 4 @def RCC_APB1_DIV_4 */
#define RCC_APB1_DIV_4						((rcc_bus_prescaler_t) 2U)
/** @brief Selects APB1 clock division by 8 @def RCC_APB1_DIV_8 */
#define RCC_APB1_DIV_8						((rcc_bus_prescaler_t) 3U)
/** @brief Selects APB1 clock division by 16 @def RCC_APB1_DIV_16 */
#define RCC_APB1_DIV_16						((rcc_bus_prescaler_t) 4U)

/** @brief Selects APB2 clock division by 1 @def RCC_APB2_DIV_1 */
#define RCC_APB2_DIV_1						((rcc_bus_prescaler_t) 0U)
/** @brief Selects APB2 clock division by 2 @def RCC_APB2_DIV_2 */
#define RCC_APB2_DIV_2						((rcc_bus_prescaler_t) 1U)
/** @brief Selects APB2 clock division by 4 @def RCC_APB2_DIV_4 */
#define RCC_APB2_DIV_4						((rcc_bus_prescaler_t) 2U)
/** @brief Selects APB2 clock division by 8 @def RCC_APB2_DIV_8 */
#define RCC_APB2_DIV_8						((rcc_bus_prescaler_t) 3U)
/** @brief Selects APB2 clock division by 16 @def RCC_APB2_DIV_16 */
#define RCC_APB2_DIV_16						((rcc_bus_prescaler_t) 4U)

/** @brief Selects ADC clock division by 2 @def RCC_ADC_DIV_2 */
#define RCC_ADC_DIV_2						((rcc_component_prescaler_t) 0U)
/** @brief Selects ADC clock division by 4 @def RCC_ADC_DIV_4 */
#define RCC_ADC_DIV_4						((rcc_component_prescaler_t) 1U)
/** @brief Selects ADC clock division by 6 @def RCC_ADC_DIV_6 */
#define RCC_ADC_DIV_6						((rcc_component_prescaler_t) 2U)
/** @brief Selects ADC clock division by 8 @def RCC_ADC_DIV_8 */
#define RCC_ADC_DIV_8						((rcc_component_prescaler_t) 3U)

/** @brief Selects the PLL-output divide-by-1.5 USB clock path @def RCC_USB_DIV_1_5 */
#define RCC_USB_DIV_1_5						((rcc_component_prescaler_t) 0U)
/** @brief Selects the undivided PLL output as USB clock @def RCC_USB_DIV_1 */
#define RCC_USB_DIV_1						((rcc_component_prescaler_t) 1U)

/** @} */ // RCC_03_Driver_02_Defines

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_DEFINES_H_ */
