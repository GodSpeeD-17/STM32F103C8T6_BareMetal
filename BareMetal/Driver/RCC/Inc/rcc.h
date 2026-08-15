/**
 * @file	rcc.h
 * @author	Shrey Shah
 * @brief	RCC Driver Public Interface
 * @version	v2.4
 * @date	22-03-2026
 *
 * @details
 * This header defines the RCC driver layer built on top of `rcc_ll.h`.
 *
 * Theory:
 * - The RCC hardware exposes clock sources, prescalers, and gate/reset control.
 * - The LL layer performs direct register-near actions.
 * - The driver layer validates requested policies, sequences safe transitions,
 *   and exposes frequency-oriented runtime queries.
 */

#ifndef RCC_H_
#define RCC_H_

// C++ Compatibility
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //

#include "rcc_ll.h"

/**
 * @addtogroup RCC_03_Driver
 * @{
 */

// ==================================================================================================== //
//                                         RCC Driver Data Types                                        //
// ==================================================================================================== //

/**
 * @brief	RCC Driver Shared Type Aliases
 * @defgroup RCC_03_Driver_01_DataTypes RCC Driver Data Types
 * @ingroup	RCC_03_Driver
 * @details
 * The RCC scalar typedef aliases are declared in @ref `stm32f1xx_data_types.h` so
 * they are available to the core layer, LL layer, and driver layer without
 * requiring inclusion of @ref `rcc.h`
 * @{
 */

/** @} */ // RCC_03_Driver_01_DataTypes

// ==================================================================================================== //
//                                      RCC Frequency Definitions                                       //
// ==================================================================================================== //

/**
 * @brief	RCC Frequency Types and Limits
 * @defgroup RCC_03_Driver_02_Frequency RCC Driver Frequency Types and Macros
 * @ingroup	RCC_03_Driver
 * @details All hertz-valued RCC fields and APIs use the Core-owned
 * @ref frequency_t alias.
 * @{
 */

/**
 * @brief	Derived RCC clock frequencies snapshot
 * @typedef	rcc_clock_frequencies_t
 */
typedef struct _rcc_clock_frequencies_t
{

	/**
	 * @brief System clock frequency in Hz
	 * @memberof rcc_clock_frequencies_t
	 */
	frequency_t	sysclk;

	/**
	 * @brief AHB clock frequency in Hz
	 * @memberof rcc_clock_frequencies_t
	 */
	frequency_t	hclk;

	/**
	 * @brief APB1 clock frequency in Hz
	 * @memberof rcc_clock_frequencies_t
	 */
	frequency_t	pclk1;
	
	/**
	 * @brief APB2 clock frequency in Hz
	 * @memberof rcc_clock_frequencies_t
	 */
	frequency_t	pclk2;

	/**
	 * @brief ADC clock frequency in Hz
	 * @memberof rcc_clock_frequencies_t
	 */
	frequency_t	adcclk;

	/**
	 * @brief USB clock frequency in Hz
	 * @memberof rcc_clock_frequencies_t
	 */
	frequency_t	usbclk;

} rcc_clock_frequencies_t;

/** @} */ // RCC_03_Driver_02_Frequency

// ==================================================================================================== //
//									   RCC Flash Configuration										//
// ==================================================================================================== //

/**
 * @brief	RCC Flash Configuration Types
 * @defgroup RCC_03_Driver_03_Flash RCC Driver Flash Configuration
 * @ingroup	RCC_03_Driver
 * @{
 */

/** @brief Flash zero wait states @def RCC_FLASH_LATENCY_0 */
#define RCC_FLASH_LATENCY_0						((rcc_flash_latency_t) 0U)
/** @brief Flash one wait state @def RCC_FLASH_LATENCY_1 */
#define RCC_FLASH_LATENCY_1						((rcc_flash_latency_t) 1U)
/** @brief Flash two wait states @def RCC_FLASH_LATENCY_2 */
#define RCC_FLASH_LATENCY_2						((rcc_flash_latency_t) 2U)

/** @brief Flash prefetch disabled @def RCC_FLASH_PREFETCH_DISABLE */
#define RCC_FLASH_PREFETCH_DISABLE				((rcc_flash_prefetch_t) 0U)
/** @brief Flash prefetch enabled @def RCC_FLASH_PREFETCH_ENABLE */
#define RCC_FLASH_PREFETCH_ENABLE				((rcc_flash_prefetch_t) 1U)

/**
 * @brief	Flash configuration descriptor
 * @typedef	rcc_flash_config_t
 */
typedef struct _rcc_flash_config_t
{

	/**
	 * @brief Flash Latency
	 * @memberof rcc_flash_config_t 
	 */
	rcc_flash_latency_t		latency;
	
	/**
	 * @brief Flash Pre-fetch
	 * @memberof rcc_flash_config_t 
	 */
	rcc_flash_prefetch_t	prefetch;

} rcc_flash_config_t;

/** @} */ // RCC_03_Driver_03_Flash

// ==================================================================================================== //
//                                           RCC System Clock                                           //
// ==================================================================================================== //

/**
 * @brief	RCC System Clock and PLL Types
 * @defgroup RCC_03_Driver_04_SystemClock RCC Driver System Clock Configuration
 * @ingroup	RCC_03_Driver
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

/**
 * @brief	PLL configuration descriptor
 * @typedef	rcc_pll_config_t
 */
typedef struct _rcc_pll_config_t
{

	/**
	 * @brief PLL Source
	 * @memberof rcc_pll_config_t
	 */
	rcc_pll_src_t			source;

	/**
	 * @brief PLL Source - Prescaler
	 * @memberof rcc_pll_config_t
	 */
	rcc_pll_src_psc_t		source_prescaler;

	/**
	 * @brief PLL Multiplication Factor
	 * @memberof rcc_pll_config_t
	 */
	rcc_pll_mul_t			multiplication_factor;

} rcc_pll_config_t;

/**
 * @brief	System clock configuration descriptor
 * @typedef	rcc_sys_clk_config_t
 */
typedef struct _rcc_sys_clk_config_t
{

	/**
	 * @brief System Clock Source
	 * @memberof rcc_sys_clk_config_t
	 */
	rcc_system_clock_t	clk_src;

	/**
	 * @brief PLL Configuration (if applicable)
	 * @memberof rcc_sys_clk_config_t
	 */
	rcc_pll_config_t	pll;

} rcc_sys_clk_config_t;

/** @} */ // RCC_03_Driver_04_SystemClock

// ==================================================================================================== //
//                                            RCC Prescalers                                            //
// ==================================================================================================== //

/**
 * @brief	RCC Bus and Component Prescaler Types
 * @defgroup RCC_03_Driver_05_Prescalers RCC Driver Prescaler Configuration
 * @ingroup	RCC_03_Driver
 * @{
 */

/** @brief AHB bus selector @def RCC_AHB_BUS */
#define RCC_AHB_BUS								((rcc_bus_t) 0U)
/** @brief APB1 bus selector @def RCC_APB1_BUS */
#define RCC_APB1_BUS							((rcc_bus_t) 1U)
/** @brief APB2 bus selector @def RCC_APB2_BUS */
#define RCC_APB2_BUS							((rcc_bus_t) 2U)

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

/**
 * @brief	Bus prescaler configuration descriptor
 * @typedef	rcc_bus_config_t
 */
typedef struct _rcc_bus_config_t
{

	/**
	 * @brief AHB Prescaler
	 * @memberof rcc_bus_config_t
	 */
	rcc_bus_prescaler_t	AHB;

	/**
	 * @brief APB1 Prescaler
	 * @memberof rcc_bus_config_t
	 */
	rcc_bus_prescaler_t	APB1;
	
	/**
	 * @brief APB2 Prescaler
	 * @memberof rcc_bus_config_t
	 */
	rcc_bus_prescaler_t	APB2;

} rcc_bus_config_t;

/**
 * @brief	Component prescaler configuration descriptor
 * @typedef	rcc_component_config_t
 */
typedef struct _rcc_component_config_t
{
	/**
	 * @brief ADC - Prescaler 
	 * @memberof rcc_component_config_t
	 */
	rcc_component_prescaler_t	ADC;

	/**
	 * @brief USB - Prescaler
	 * @memberof rcc_component_config_t
	 */
	rcc_component_prescaler_t	USB;

} rcc_component_config_t;

/** @} */ // RCC_03_Driver_05_Prescalers

// ==================================================================================================== //
//                                     RCC Aggregate Configuration                                      //
// ==================================================================================================== //

/**
 * @brief	RCC Aggregate Configuration Types
 * @defgroup RCC_03_Driver_06_Config RCC Driver Aggregate Configuration
 * @ingroup	RCC_03_Driver
 * @{
 */

/**
 * @brief	Clock-tree configuration descriptor
 * @typedef	rcc_clock_tree_config_t
 */
typedef struct _rcc_clock_tree_config_t
{

	/**
	 * @brief System Configurations
	 * @memberof rcc_clock_tree_config_t
	 */
	rcc_sys_clk_config_t		system;

	/**
	 * @brief Bus Prescaler Configurations
	 * @memberof rcc_clock_tree_config_t
	 */
	rcc_bus_config_t			bus;

	/**
	 * @brief Components Configurations
	 * @memberof rcc_clock_tree_config_t
	 */
	rcc_component_config_t		component;

} rcc_clock_tree_config_t;

/**
 * @brief	Complete RCC configuration descriptor
 * @typedef	rcc_config_t
 */
typedef struct _rcc_config_t
{

	/**
	 * @brief Flash - Configurations
	 * @memberof rcc_config_t
	 */
	rcc_flash_config_t		flash;

	/**
	 * @brief Clock Tree - Configurations
	 * @memberof rcc_config_t
	 */
	rcc_clock_tree_config_t	clock_tree;

} rcc_config_t;

/** @} */ // RCC_03_Driver_06_Config

// ==================================================================================================== //
//                                    RCC Clock Gate and Reset APIs                                     //
// ==================================================================================================== //

/**
 * @brief	RCC Clock Gate and Reset APIs
 * @defgroup RCC_03_Driver_07_ClockReset RCC Driver Clock Enable and Reset APIs
 * @ingroup	RCC_03_Driver
 * @{
 */

/**
 * @brief	Enables AHB peripheral clock gates
 * @param[in] clockMask	AHB clock enable mask from RCC register definitions
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested AHB clock gates were enabled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid.
 */
__STATIC_FORCEINLINE driver_status_t RCC_AHB_ClockEnable(const uint32_t clockMask)
{
	return RCC_LL_EnableAHBClock(clockMask);
}

/**
 * @brief	Disables AHB peripheral clock gates
 * @param[in] clockMask	AHB clock enable mask from RCC register definitions
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested AHB clock gates were disabled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid.
 */
__STATIC_FORCEINLINE driver_status_t RCC_AHB_ClockDisable(const uint32_t clockMask)
{
	return RCC_LL_DisableAHBClock(clockMask);
}

/**
 * @brief	Enables APB2 peripheral clock gates
 * @param[in] clockMask	APB2 clock enable mask from RCC register definitions
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested APB2 clock gates were enabled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid.
 */
__STATIC_FORCEINLINE driver_status_t RCC_APB2_ClockEnable(const uint32_t clockMask)
{
	return RCC_LL_EnableAPB2Clock(clockMask);
}

/**
 * @brief	Disables APB2 peripheral clock gates
 * @param[in] clockMask	APB2 clock enable mask from RCC register definitions
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested APB2 clock gates were disabled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid.
 */
__STATIC_FORCEINLINE driver_status_t RCC_APB2_ClockDisable(const uint32_t clockMask)
{
	return RCC_LL_DisableAPB2Clock(clockMask);
}

/**
 * @brief	Enables APB1 peripheral clock gates
 * @param[in] clockMask	APB1 clock enable mask from RCC register definitions
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested APB1 clock gates were enabled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid.
 */
__STATIC_FORCEINLINE driver_status_t RCC_APB1_ClockEnable(const uint32_t clockMask)
{
	return RCC_LL_EnableAPB1Clock(clockMask);
}

/**
 * @brief	Disables APB1 peripheral clock gates
 * @param[in] clockMask	APB1 clock enable mask from RCC register definitions
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested APB1 clock gates were disabled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid.
 */
__STATIC_FORCEINLINE driver_status_t RCC_APB1_ClockDisable(const uint32_t clockMask)
{
	return RCC_LL_DisableAPB1Clock(clockMask);
}

/**
 * @brief	Gets APB1 peripheral clock gate state
 * @param[in] clockMask	APB1 clock enable mask from RCC register definitions
 * @returns APB1 clock gate state or driver error status
 * @retval - @ref `DRIVER_STATUS_OFF`: Requested APB1 clock gates are disabled.
 * @retval - @ref `DRIVER_STATUS_ON`: Requested APB1 clock gates are enabled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid.
 */
__STATIC_FORCEINLINE driver_status_t RCC_APB1_ClockGetState(const uint32_t clockMask)
{
	reg regImage = 0x00000000UL;

	if (RCC_LL_IS_MASK_VALID(clockMask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	RCC_LL_READ_REG(APB1ENR, regImage);
	return ((regImage & clockMask) == clockMask) ? DRIVER_STATUS_ON : DRIVER_STATUS_OFF;
}

/**
 * @brief	Pulses APB2 peripheral reset bits
 * @param[in] resetMask	APB2 reset mask from RCC register definitions
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested APB2 peripherals were reset-pulsed.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p resetMask was zero or invalid.
 */
__STATIC_FORCEINLINE driver_status_t RCC_APB2_ResetPulse(const uint32_t resetMask)
{
	return RCC_LL_PulseAPB2Reset(resetMask);
}

/**
 * @brief	Pulses APB1 peripheral reset bits
 * @param[in] resetMask	APB1 reset mask from RCC register definitions
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested APB1 peripherals were reset-pulsed.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p resetMask was zero or invalid.
 */
__STATIC_FORCEINLINE driver_status_t RCC_APB1_ResetPulse(const uint32_t resetMask)
{
	return RCC_LL_PulseAPB1Reset(resetMask);
}

/** @} */ // RCC_03_Driver_07_ClockReset

// ==================================================================================================== //
//                                        RCC Frequency APIs                                            //
// ==================================================================================================== //

/**
 * @addtogroup RCC_03_Driver_02_Frequency
 * @{
 */

/**
 * @brief	Returns the current core clock frequency before AHB division
 * @returns @ref frequency_t "Core clock frequency in hertz"
 */
frequency_t RCC_GetCoreClockFreq(void);

/**
 * @brief	Returns the current frequency of a requested bus
 * @param[in] bus	Target bus selector of @ref rcc_bus_t
 * @returns @ref frequency_t "Bus clock frequency in hertz"
 */
frequency_t RCC_GetBusFreq(const rcc_bus_t bus);

/**
 * @brief	Returns the current ADC clock frequency
 * @returns @ref frequency_t "ADC clock frequency in hertz"
 */
frequency_t RCC_GetADCFreq(void);

/**
 * @brief	Returns the current USB clock frequency
 * @returns @ref frequency_t "USB clock frequency in hertz"
 */
frequency_t RCC_GetUSBFreq(void);

/**
 * @brief	Returns the cached or current derived RCC clock frequencies snapshot
 * @param[out] pClockFrequencies	Pointer to @ref rcc_clock_frequencies_t
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The clock frequency snapshot was returned successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pClockFrequencies was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read while building the snapshot.
 */
driver_status_t RCC_GetClockFrequencies(rcc_clock_frequencies_t* const pClockFrequencies);

/** @} */ // RCC_03_Driver_02_Frequency

// ==================================================================================================== //
//                                          RCC Flash APIs                                              //
// ==================================================================================================== //

/**
 * @addtogroup RCC_03_Driver_03_Flash
 * @{
 */

/**
 * @brief	Applies Flash latency and prefetch configuration
 * @param[in] pFlashConfig	Pointer to @ref rcc_flash_config_t
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Flash latency and prefetch configuration were applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pFlashConfig was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Flash configuration fields were invalid.
 */
driver_status_t RCC_ConfigFlash(const rcc_flash_config_t* const pFlashConfig);

/** @} */ // RCC_03_Driver_03_Flash

// ==================================================================================================== //
//                                       RCC System Clock APIs                                          //
// ==================================================================================================== //

/**
 * @addtogroup RCC_03_Driver_04_SystemClock
 * @{
 */

/**
 * @brief	Switches SYSCLK to HSI and validates the transition with a timeout
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: HSI became ready and SYSCLK switched to HSI successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: HSI did not become ready or SYSCLK did not switch within the timeout window.
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read during the transition.
 */
driver_status_t RCC_SwitchClockSourceToHSI(void);

/**
 * @brief	Switches SYSCLK to HSE and validates the transition with a timeout
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: HSE became ready and SYSCLK switched to HSE successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: HSE did not become ready or SYSCLK did not switch within the timeout window.
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read during the transition.
 */
driver_status_t RCC_SwitchClockSourceToHSE(void);

/**
 * @brief	Switches SYSCLK to PLL and validates the transition with a timeout
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: PLL was ready and SYSCLK switched to PLL successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: PLL was not ready when the switch was requested.
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: SYSCLK did not switch to PLL within the timeout window.
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read during the transition.
 */
driver_status_t RCC_SwitchClockSourceToPLL(void);

/**
 * @brief	Returns the active system clock source
 * @returns	Current system clock source as @ref rcc_system_clock_t
 */
rcc_system_clock_t RCC_GetSysClkSrc(void);

/**
 * @brief	Returns the active PLL source selection
 * @returns	Current PLL source as @ref rcc_pll_src_t
 */
rcc_pll_src_t RCC_GetPLLSource(void);

/**
 * @brief	Returns the active PLL input prescaler selection
 * @returns	Current PLL source prescaler as @ref rcc_pll_src_psc_t
 */
rcc_pll_src_psc_t RCC_GetPLLSourcePrescaler(void);

/**
 * @brief	Returns the active PLL multiplication factor
 * @returns	Current PLL multiplication factor as @ref rcc_pll_mul_t
 */
rcc_pll_mul_t RCC_GetPLLMultiplier(void);

/** @} */ // RCC_03_Driver_04_SystemClock

// ==================================================================================================== //
//                                        RCC Prescaler APIs                                            //
// ==================================================================================================== //

/**
 * @addtogroup RCC_03_Driver_05_Prescalers
 * @{
 */

/**
 * @brief	Applies AHB, APB1, and APB2 prescaler configuration
 * @param[in] pBusConfig	Pointer to @ref rcc_bus_config_t
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested bus prescalers were applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pBusConfig was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more bus prescaler values were invalid.
 */
driver_status_t RCC_ConfigBusPrescalers(const rcc_bus_config_t* const pBusConfig);

/**
 * @brief	Applies ADC and USB prescaler configuration
 * @param[in] pComponentConfig	Pointer to @ref rcc_component_config_t
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested component prescalers were applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pComponentConfig was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more component prescaler values were invalid.
 */
driver_status_t RCC_ConfigComponentPrescalers(const rcc_component_config_t* const pComponentConfig);

/**
 * @brief	Returns the configured prescaler selector for a requested bus
 * @param[in] bus	Target bus selector of @ref rcc_bus_t
 * @returns	Configured bus prescaler selector value
 */
rcc_bus_prescaler_t RCC_GetBusPrescaler(const rcc_bus_t bus);

/** @} */ // RCC_03_Driver_05_Prescalers

// ==================================================================================================== //
//                                         RCC Config APIs                                              //
// ==================================================================================================== //

/**
 * @addtogroup RCC_03_Driver_06_Config
 * @{
 */

/**
 * @brief	Validates a complete RCC configuration descriptor
 * @param[in] pRCCConfig	Pointer to @ref rcc_config_t
 * @returns - @ref driver_status_t Validation result
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Configuration is valid and internally consistent.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pRCCConfig was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Configuration contains an invalid source, divider, multiplier, or limit violation.
 */
driver_status_t RCC_ValidateConfig(const rcc_config_t* const pRCCConfig);

/**
 * @brief	Applies a complete clock-tree configuration through the RCC driver orchestrator
 * @param[in] pClockTreeConfig	Pointer to @ref rcc_clock_tree_config_t
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock-tree sequencing completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pClockTreeConfig was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Configuration contained invalid clock-tree values.
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A source ready-state or switch confirmation timed out.
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read during sequencing.
 */
driver_status_t RCC_ConfigClockTree(const rcc_clock_tree_config_t* const pClockTreeConfig);

/**
 * @brief	Applies a complete RCC configuration descriptor
 * @param[in] pRCCConfig	Pointer to @ref rcc_config_t
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Flash and clock-tree configuration completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pRCCConfig was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Configuration contained invalid fields or violated frequency limits.
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A source ready-state or switch confirmation timed out.
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read during sequencing.
 */
driver_status_t RCC_Config(const rcc_config_t* const pRCCConfig);

/**
 * @brief	Loads the default 72 MHz Blue Pill clock-tree preset
 * @param[out] pRCCConfig	Pointer to @ref rcc_config_t
 */
void RCC_Load72MHzDefaultConfig(rcc_config_t* const pRCCConfig);

/**
 * @brief	Applies the default 72 MHz Blue Pill RCC configuration
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Default 72 MHz configuration completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Default configuration validation failed.
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A source ready-state or switch confirmation timed out.
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read during sequencing.
 */
driver_status_t RCC_Config72MHz(void);

/** @} */ // RCC_03_Driver_06_Config

// ==================================================================================================== //
//                                  RCC Legacy Compatibility Wrappers                                   //
// ==================================================================================================== //

/**
 * @brief	Legacy inline compatibility wrappers
 * @defgroup RCC_03_Driver_08_Legacy RCC Driver Legacy Compatibility Wrappers
 * @ingroup	RCC_03_Driver
 * @{
 */

/**
 * @brief	Legacy wrapper that returns the current AHB clock frequency
 * @returns @ref frequency_t "AHB clock frequency in hertz"
 */
__STATIC_FORCEINLINE frequency_t RCC_GetAHBClock(void)
{
	return RCC_GetBusFreq(RCC_AHB_BUS);
}

/**
 * @brief	Legacy wrapper that returns the current APB1 clock frequency
 * @returns @ref frequency_t "APB1 clock frequency in hertz"
 */
__STATIC_FORCEINLINE frequency_t RCC_GetAPB1Clock(void)
{
	return RCC_GetBusFreq(RCC_APB1_BUS);
}

/**
 * @brief	Legacy wrapper that returns the current APB2 clock frequency
 * @returns @ref frequency_t "APB2 clock frequency in hertz"
 */
__STATIC_FORCEINLINE frequency_t RCC_GetAPB2Clock(void)
{
	return RCC_GetBusFreq(RCC_APB2_BUS);
}

/**
 * @brief	Legacy wrapper for @ref RCC_GetClockFrequencies
 * @param[out] pClockFrequencies	Pointer to @ref rcc_clock_frequencies_t
 * @returns	@ref driver_status_t Driver operation status
 */
__STATIC_FORCEINLINE driver_status_t RCC_ClockFrequenciesGet(rcc_clock_frequencies_t* const pClockFrequencies)
{
	return RCC_GetClockFrequencies(pClockFrequencies);
}

/**
 * @brief	Legacy wrapper for @ref RCC_ConfigBusPrescalers
 * @param[in] pBusConfig	Pointer to @ref rcc_bus_config_t
 * @returns	@ref driver_status_t Driver operation status
 */
__STATIC_FORCEINLINE driver_status_t RCC_ConfigBusPrescaler(const rcc_bus_config_t* const pBusConfig)
{
	return RCC_ConfigBusPrescalers(pBusConfig);
}

/**
 * @brief	Legacy wrapper for @ref RCC_ConfigComponentPrescalers
 * @param[in] pComponentConfig	Pointer to @ref rcc_component_config_t
 * @returns	@ref driver_status_t Driver operation status
 */
__STATIC_FORCEINLINE driver_status_t RCC_ConfigComponentPrescaler(const rcc_component_config_t* const pComponentConfig)
{
	return RCC_ConfigComponentPrescalers(pComponentConfig);
}

/**
 * @brief	Legacy wrapper for @ref RCC_Load72MHzDefaultConfig
 * @param[out] pRCCConfig	Pointer to @ref rcc_config_t
 * @returns	Void
 */
__STATIC_FORCEINLINE void RCC_72MHz_LoadDefaultConfig(rcc_config_t* const pRCCConfig)
{
	RCC_Load72MHzDefaultConfig(pRCCConfig);
}

/**
 * @brief	Legacy wrapper for @ref RCC_Config72MHz
 * @returns	@ref driver_status_t Driver operation status
 */
__STATIC_FORCEINLINE driver_status_t RCC_Config_72MHz(void)
{
	return RCC_Config72MHz();
}

/** @} */ // RCC_03_Driver_08_Legacy

/** @} */ // RCC_03_Driver

// C++ Compatibility
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_H_ */
