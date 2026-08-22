/**
 * @file	rcc_defines.h
 * @author	Shrey Shah
 * @brief	RCC Selector Vocabulary Definitions
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * This header defines the RCC driver-facing selector vocabulary shared by the
 * Driver and Codec layers. It exists so @ref rcc_codec.h can translate these
 * selectors without including the public Driver header, keeping the Codec
 * layer strictly below the Driver in the dependency direction.
 *
 * This header owns only scalar selector value macros built on the Core-owned
 * `rcc_*_t` typedefs. Root and nested RCC configuration structures remain in
 * @ref rcc.h because Codec transformations never consume them directly.
 */

#ifndef RCC_DEFINES_H_
#define RCC_DEFINES_H_

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //
#include "stm32f1xx.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup RCC_03_Driver
 * @{
 */

// ==================================================================================================== //
//                                       RCC System Clock Selectors                                     //
// ==================================================================================================== //

/**
 * @addtogroup RCC_03_Driver_04_SystemClock
 * @{
 */

/** @brief HSI selected as SYSCLK @def RCC_SYS_CLK_HSI */
#define RCC_SYS_CLK_HSI							((rcc_system_clock_t) 0U)
/** @brief HSE selected as SYSCLK @def RCC_SYS_CLK_HSE */
#define RCC_SYS_CLK_HSE							((rcc_system_clock_t) 1U)
/** @brief PLL selected as SYSCLK @def RCC_SYS_CLK_PLL */
#define RCC_SYS_CLK_PLL							((rcc_system_clock_t) 2U)

/** @brief HSI divided by 2 selected as PLL input @def RCC_PLL_SRC_HSI */
#define RCC_PLL_SRC_HSI							((rcc_pll_src_t) 0U)
/** @brief HSE selected as PLL input @def RCC_PLL_SRC_HSE */
#define RCC_PLL_SRC_HSE							((rcc_pll_src_t) 1U)

/** @brief Fixed HSI divide-by-2 PLL input @def RCC_PLL_SRC_HSI_DIV_2 */
#define RCC_PLL_SRC_HSI_DIV_2					((rcc_pll_src_psc_t) 0U)
/** @brief HSE divide-by-1 PLL input @def RCC_PLL_SRC_HSE_DIV_1 */
#define RCC_PLL_SRC_HSE_DIV_1					((rcc_pll_src_psc_t) 1U)
/** @brief HSE divide-by-2 PLL input @def RCC_PLL_SRC_HSE_DIV_2 */
#define RCC_PLL_SRC_HSE_DIV_2					((rcc_pll_src_psc_t) 2U)

/** @brief PLL multiplication factor x2 @def RCC_PLL_MUL_2 */
#define RCC_PLL_MUL_2							((rcc_pll_mul_t) 2U)
/** @brief PLL multiplication factor x3 @def RCC_PLL_MUL_3 */
#define RCC_PLL_MUL_3							((rcc_pll_mul_t) 3U)
/** @brief PLL multiplication factor x4 @def RCC_PLL_MUL_4 */
#define RCC_PLL_MUL_4							((rcc_pll_mul_t) 4U)
/** @brief PLL multiplication factor x5 @def RCC_PLL_MUL_5 */
#define RCC_PLL_MUL_5							((rcc_pll_mul_t) 5U)
/** @brief PLL multiplication factor x6 @def RCC_PLL_MUL_6 */
#define RCC_PLL_MUL_6							((rcc_pll_mul_t) 6U)
/** @brief PLL multiplication factor x7 @def RCC_PLL_MUL_7 */
#define RCC_PLL_MUL_7							((rcc_pll_mul_t) 7U)
/** @brief PLL multiplication factor x8 @def RCC_PLL_MUL_8 */
#define RCC_PLL_MUL_8							((rcc_pll_mul_t) 8U)
/** @brief PLL multiplication factor x9 @def RCC_PLL_MUL_9 */
#define RCC_PLL_MUL_9							((rcc_pll_mul_t) 9U)
/** @brief PLL multiplication factor x10 @def RCC_PLL_MUL_10 */
#define RCC_PLL_MUL_10							((rcc_pll_mul_t) 10U)
/** @brief PLL multiplication factor x11 @def RCC_PLL_MUL_11 */
#define RCC_PLL_MUL_11							((rcc_pll_mul_t) 11U)
/** @brief PLL multiplication factor x12 @def RCC_PLL_MUL_12 */
#define RCC_PLL_MUL_12							((rcc_pll_mul_t) 12U)
/** @brief PLL multiplication factor x13 @def RCC_PLL_MUL_13 */
#define RCC_PLL_MUL_13							((rcc_pll_mul_t) 13U)
/** @brief PLL multiplication factor x14 @def RCC_PLL_MUL_14 */
#define RCC_PLL_MUL_14							((rcc_pll_mul_t) 14U)
/** @brief PLL multiplication factor x15 @def RCC_PLL_MUL_15 */
#define RCC_PLL_MUL_15							((rcc_pll_mul_t) 15U)
/** @brief PLL multiplication factor x16 @def RCC_PLL_MUL_16 */
#define RCC_PLL_MUL_16							((rcc_pll_mul_t) 16U)

/** @} */ // RCC_03_Driver_04_SystemClock

// ==================================================================================================== //
//                                     RCC Prescaler Selectors                                          //
// ==================================================================================================== //

/**
 * @addtogroup RCC_03_Driver_05_Prescalers
 * @{
 */

/** @brief Divider 1 selection @def RCC_AHB_DIV_1 */
#define RCC_AHB_DIV_1							((rcc_bus_prescaler_t) 0U)
/** @brief Divider 2 selection @def RCC_AHB_DIV_2 */
#define RCC_AHB_DIV_2							((rcc_bus_prescaler_t) 1U)
/** @brief Divider 4 selection @def RCC_AHB_DIV_4 */
#define RCC_AHB_DIV_4							((rcc_bus_prescaler_t) 2U)
/** @brief Divider 8 selection @def RCC_AHB_DIV_8 */
#define RCC_AHB_DIV_8							((rcc_bus_prescaler_t) 3U)
/** @brief Divider 16 selection @def RCC_AHB_DIV_16 */
#define RCC_AHB_DIV_16							((rcc_bus_prescaler_t) 4U)
/** @brief Divider 64 selection @def RCC_AHB_DIV_64 */
#define RCC_AHB_DIV_64							((rcc_bus_prescaler_t) 5U)
/** @brief Divider 128 selection @def RCC_AHB_DIV_128 */
#define RCC_AHB_DIV_128							((rcc_bus_prescaler_t) 6U)
/** @brief Divider 256 selection @def RCC_AHB_DIV_256 */
#define RCC_AHB_DIV_256							((rcc_bus_prescaler_t) 7U)
/** @brief Divider 512 selection @def RCC_AHB_DIV_512 */
#define RCC_AHB_DIV_512							((rcc_bus_prescaler_t) 8U)

/** @brief Divider 1 selection @def RCC_APB1_DIV_1 */
#define RCC_APB1_DIV_1							((rcc_bus_prescaler_t) 0U)
/** @brief Divider 2 selection @def RCC_APB1_DIV_2 */
#define RCC_APB1_DIV_2							((rcc_bus_prescaler_t) 1U)
/** @brief Divider 4 selection @def RCC_APB1_DIV_4 */
#define RCC_APB1_DIV_4							((rcc_bus_prescaler_t) 2U)
/** @brief Divider 8 selection @def RCC_APB1_DIV_8 */
#define RCC_APB1_DIV_8							((rcc_bus_prescaler_t) 3U)
/** @brief Divider 16 selection @def RCC_APB1_DIV_16 */
#define RCC_APB1_DIV_16							((rcc_bus_prescaler_t) 4U)

/** @brief Divider 1 selection @def RCC_APB2_DIV_1 */
#define RCC_APB2_DIV_1							((rcc_bus_prescaler_t) 0U)
/** @brief Divider 2 selection @def RCC_APB2_DIV_2 */
#define RCC_APB2_DIV_2							((rcc_bus_prescaler_t) 1U)
/** @brief Divider 4 selection @def RCC_APB2_DIV_4 */
#define RCC_APB2_DIV_4							((rcc_bus_prescaler_t) 2U)
/** @brief Divider 8 selection @def RCC_APB2_DIV_8 */
#define RCC_APB2_DIV_8							((rcc_bus_prescaler_t) 3U)
/** @brief Divider 16 selection @def RCC_APB2_DIV_16 */
#define RCC_APB2_DIV_16							((rcc_bus_prescaler_t) 4U)

/** @brief ADC divider 2 selection @def RCC_ADC_DIV_2 */
#define RCC_ADC_DIV_2							((rcc_component_prescaler_t) 0U)
/** @brief ADC divider 4 selection @def RCC_ADC_DIV_4 */
#define RCC_ADC_DIV_4							((rcc_component_prescaler_t) 1U)
/** @brief ADC divider 6 selection @def RCC_ADC_DIV_6 */
#define RCC_ADC_DIV_6							((rcc_component_prescaler_t) 2U)
/** @brief ADC divider 8 selection @def RCC_ADC_DIV_8 */
#define RCC_ADC_DIV_8							((rcc_component_prescaler_t) 3U)

/** @brief USB clock equals PLL divided by 1.5 @def RCC_USB_DIV_1_5 */
#define RCC_USB_DIV_1_5							((rcc_component_prescaler_t) 0U)
/** @brief USB clock equals PLL directly @def RCC_USB_DIV_1 */
#define RCC_USB_DIV_1							((rcc_component_prescaler_t) 1U)

/** @} */ // RCC_03_Driver_05_Prescalers

/** @} */ // RCC_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_DEFINES_H_ */
