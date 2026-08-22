/**
 * @file	rcc.h
 * @author	Shrey Shah
 * @brief	RCC Driver Public Interface
 * @version	v3.0
 * @date	22-08-2026
 *
 * @details
 * This header defines the RCC driver layer built on top of @ref rcc_ll.h and
 * @ref rcc_codec.h.
 *
 * Theory:
 * - The RCC hardware exposes clock sources, prescalers, and gate/reset control.
 * - The LL layer performs direct register-near actions.
 * - The Codec layer translates driver-facing selectors into raw hardware fields.
 * - The driver layer validates requested policies, sequences safe transitions,
 *   and exposes frequency-oriented runtime queries.
 *
 * @see @ref RCC_Peripheral_Guide "STM32F103C8T6 RCC Architecture"
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
#include "rcc_defines.h"

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
 * @details Selector value macros (`RCC_SYS_CLK_*`, `RCC_PLL_SRC_*`, `RCC_PLL_MUL_*`)
 * are declared in @ref rcc_defines.h so @ref rcc_codec.h can share them without
 * depending on this Driver header.
 * @{
 */

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
 * @details Prescaler selector value macros (`RCC_AHB_DIV_*`, `RCC_APB1_DIV_*`,
 * `RCC_APB2_DIV_*`, `RCC_ADC_DIV_*`, `RCC_USB_DIV_*`) are declared in
 * @ref rcc_defines.h so @ref rcc_codec.h can share them without depending on
 * this Driver header.
 * @{
 */

/** @brief AHB bus selector @def RCC_AHB_BUS */
#define RCC_AHB_BUS								((rcc_bus_t) 0U)
/** @brief APB1 bus selector @def RCC_APB1_BUS */
#define RCC_APB1_BUS							((rcc_bus_t) 1U)
/** @brief APB2 bus selector @def RCC_APB2_BUS */
#define RCC_APB2_BUS							((rcc_bus_t) 2U)
/** @brief ADC bus selector @def RCC_ADC_BUS */
#define RCC_ADC_BUS								((rcc_bus_t) 3U)
/** @brief USB bus selector @def RCC_USB_BUS */
#define RCC_USB_BUS								((rcc_bus_t) 4U)

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
 * @brief	Gets AHB peripheral clock gate state
 * @param[in] clockMask	AHB clock enable mask from RCC register definitions
 * @returns AHB clock gate state or driver error status
 * @retval - @ref `DRIVER_STATUS_OFF`: Requested AHB clock gates are disabled
 * @retval - @ref `DRIVER_STATUS_ON`: Requested AHB clock gates are enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid
 */
__STATIC_FORCEINLINE driver_status_t RCC_GetAHBClockState(const uint32_t clockMask)
{
	reg regImage = 0x00000000UL;

	if (LL_RCC_IS_MASK_VALID(clockMask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Read the full gate register once through the named LL accessor, matching every other RCC gate query.
	regImage = LL_RCC_ReadAHBENR();
	if ((regImage & clockMask) == clockMask)
	{
		return DRIVER_STATUS_ON;
	}
	else
	{
		return DRIVER_STATUS_OFF;
	}
}

/**
 * @brief	Sets AHB peripheral clock gate state
 * @details
 * Enables or disables the requested AHB clock gates depending on @p clockState.
 * @param[in] clockMask	AHB clock enable mask from RCC register definitions
 * @param[in] clockState	Requested AHB clock gate state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disables the requested AHB clock gates
 * - @ref `DRIVER_STATUS_ON`: Enables the requested AHB clock gates
 * @returns @ref driver_status_t "Driver operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested AHB clock gates were updated
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid, or @p clockState was neither `DRIVER_STATUS_OFF` nor `DRIVER_STATUS_ON`
 */
__STATIC_FORCEINLINE driver_status_t RCC_SetAHBClockState(const uint32_t clockMask, const driver_status_t clockState)
{
	//! Dispatch to the matching LL gate primitive; every other state is rejected instead of silently defaulting.
	if (clockState == DRIVER_STATUS_ON)
	{
		return LL_RCC_EnableAHBClock(clockMask);
	}
	else if (clockState == DRIVER_STATUS_OFF)
	{
		return LL_RCC_DisableAHBClock(clockMask);
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
}

/**
 * @brief	Gets APB2 peripheral clock gate state
 * @param[in] clockMask	APB2 clock enable mask from RCC register definitions
 * @returns APB2 clock gate state or driver error status
 * @retval - @ref `DRIVER_STATUS_OFF`: Requested APB2 clock gates are disabled
 * @retval - @ref `DRIVER_STATUS_ON`: Requested APB2 clock gates are enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid
 */
__STATIC_FORCEINLINE driver_status_t RCC_GetAPB2ClockState(const uint32_t clockMask)
{
	reg regImage = 0x00000000UL;

	if (LL_RCC_IS_MASK_VALID(clockMask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Read the full gate register once through the named LL accessor, matching every other RCC gate query.
	regImage = LL_RCC_ReadAPB2ENR();
	if ((regImage & clockMask) == clockMask)
	{
		return DRIVER_STATUS_ON;
	}
	else
	{
		return DRIVER_STATUS_OFF;
	}
}

/**
 * @brief	Sets APB2 peripheral clock gate state
 * @details
 * Enables or disables the requested APB2 clock gates depending on @p clockState.
 * @param[in] clockMask	APB2 clock enable mask from RCC register definitions
 * @param[in] clockState	Requested APB2 clock gate state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disables the requested APB2 clock gates
 * - @ref `DRIVER_STATUS_ON`: Enables the requested APB2 clock gates
 * @returns @ref driver_status_t "Driver operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested APB2 clock gates were updated
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid, or @p clockState was neither `DRIVER_STATUS_OFF` nor `DRIVER_STATUS_ON`
 */
__STATIC_FORCEINLINE driver_status_t RCC_SetAPB2ClockState(const uint32_t clockMask, const driver_status_t clockState)
{
	//! Dispatch to the matching LL gate primitive; every other state is rejected instead of silently defaulting.
	if (clockState == DRIVER_STATUS_ON)
	{
		return LL_RCC_EnableAPB2Clock(clockMask);
	}
	else if (clockState == DRIVER_STATUS_OFF)
	{
		return LL_RCC_DisableAPB2Clock(clockMask);
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
}

/**
 * @brief	Gets APB1 peripheral clock gate state
 * @param[in] clockMask	APB1 clock enable mask from RCC register definitions
 * @returns APB1 clock gate state or driver error status
 * @retval - @ref `DRIVER_STATUS_OFF`: Requested APB1 clock gates are disabled
 * @retval - @ref `DRIVER_STATUS_ON`: Requested APB1 clock gates are enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid
 */
__STATIC_FORCEINLINE driver_status_t RCC_GetAPB1ClockState(const uint32_t clockMask)
{
	reg regImage = 0x00000000UL;

	if (LL_RCC_IS_MASK_VALID(clockMask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Read the full gate register once through the named LL accessor, matching every other RCC gate query.
	regImage = LL_RCC_ReadAPB1ENR();
	if ((regImage & clockMask) == clockMask)
	{
		return DRIVER_STATUS_ON;
	}
	else
	{
		return DRIVER_STATUS_OFF;
	}
}

/**
 * @brief	Sets APB1 peripheral clock gate state
 * @details
 * Enables or disables the requested APB1 clock gates depending on @p clockState.
 * @param[in] clockMask	APB1 clock enable mask from RCC register definitions
 * @param[in] clockState	Requested APB1 clock gate state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disables the requested APB1 clock gates
 * - @ref `DRIVER_STATUS_ON`: Enables the requested APB1 clock gates
 * @returns @ref driver_status_t "Driver operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested APB1 clock gates were updated
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid, or @p clockState was neither `DRIVER_STATUS_OFF` nor `DRIVER_STATUS_ON`
 */
__STATIC_FORCEINLINE driver_status_t RCC_SetAPB1ClockState(const uint32_t clockMask, const driver_status_t clockState)
{
	//! Dispatch to the matching LL gate primitive; every other state is rejected instead of silently defaulting.
	if (clockState == DRIVER_STATUS_ON)
	{
		return LL_RCC_EnableAPB1Clock(clockMask);
	}
	else if (clockState == DRIVER_STATUS_OFF)
	{
		return LL_RCC_DisableAPB1Clock(clockMask);
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
}

/**
 * @brief	Pulses APB2 peripheral reset bits
 * @param[in] resetMask	APB2 reset mask from RCC register definitions
 * @returns @ref driver_status_t "Driver operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested APB2 peripherals were reset-pulsed
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p resetMask was zero or invalid
 */
__STATIC_FORCEINLINE driver_status_t RCC_APB2_ResetPulse(const uint32_t resetMask)
{
	return LL_RCC_PulseAPB2Reset(resetMask);
}

/**
 * @brief	Pulses APB1 peripheral reset bits
 * @param[in] resetMask	APB1 reset mask from RCC register definitions
 * @returns @ref driver_status_t "Driver operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested APB1 peripherals were reset-pulsed
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p resetMask was zero or invalid
 */
__STATIC_FORCEINLINE driver_status_t RCC_APB1_ResetPulse(const uint32_t resetMask)
{
	return LL_RCC_PulseAPB1Reset(resetMask);
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
frequency_t RCC_GetCoreClockFrequency(void);

/**
 * @brief	Returns the current frequency of a requested bus
 * @param[in] bus	Target bus selector of @ref rcc_bus_t
 * Accepted values:
 * - @ref `RCC_AHB_BUS`: AHB bus
 * - @ref `RCC_APB1_BUS`: APB1 bus
 * - @ref `RCC_APB2_BUS`: APB2 bus
 * - @ref `RCC_ADC_BUS`: ADC clock
 * - @ref `RCC_USB_BUS`: USB clock
 * @returns @ref frequency_t "Bus clock frequency in hertz"
 */
frequency_t RCC_GetBusFrequency(const rcc_bus_t bus);

/**
 * @brief	Returns the cached or current derived RCC clock frequencies snapshot
 * @param[out] pClockFrequencies	Pointer to @ref rcc_clock_frequencies_t
 * @returns @ref driver_status_t "Driver operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The clock frequency snapshot was returned successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pClockFrequencies was a null pointer
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read while building the snapshot
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
 * @returns @ref driver_status_t "Driver operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Flash latency and prefetch configuration were applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pFlashConfig was a null pointer
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Flash configuration fields were invalid
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
 * @brief	Returns the active system clock source
 * @returns	Current system clock source as @ref rcc_system_clock_t
 */
rcc_system_clock_t RCC_GetSystemClockSource(void);

/**
 * @brief	Selects SYSCLK and validates the transition with a timeout
 * @details
 * Dispatches to the HSI, HSE, or PLL enable-and-switch sequence required by
 * @p source. Every path enables the requested oscillator/PLL, waits for its
 * ready flag, programs `CFGR.SW`, and waits for `CFGR.SWS` to confirm the
 * switch before refreshing the cached frequency snapshot.
 * @param[in] source	Requested system clock source
 * Accepted values:
 * - @ref `RCC_SYS_CLK_HSI`: Enables HSI and switches SYSCLK to HSI
 * - @ref `RCC_SYS_CLK_HSE`: Enables HSE and switches SYSCLK to HSE
 * - @ref `RCC_SYS_CLK_PLL`: Switches SYSCLK to the already-configured PLL
 * @returns @ref driver_status_t "System clock source selection status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The requested source became ready and SYSCLK switched successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p source is not a supported selector
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: @ref `RCC_SYS_CLK_PLL` was requested while the PLL was not ready
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: The requested source did not become ready, or SYSCLK did not switch, within the timeout window
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read during the transition
 * @note Selecting @ref `RCC_SYS_CLK_PLL` requires the PLL to already be configured and ready; this
 * function does not program PLL source, divider, or multiplier fields.
 */
driver_status_t RCC_SetSystemClockSource(const rcc_system_clock_t source);

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
 * @returns @ref driver_status_t "Driver operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested bus prescalers were applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pBusConfig was a null pointer
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more bus prescaler values were invalid
 */
driver_status_t RCC_ConfigBusPrescalers(const rcc_bus_config_t* const pBusConfig);

/**
 * @brief	Applies ADC and USB prescaler configuration
 * @param[in] pComponentConfig	Pointer to @ref rcc_component_config_t
 * @returns @ref driver_status_t "Driver operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested component prescalers were applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pComponentConfig was a null pointer
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more component prescaler values were invalid
 */
driver_status_t RCC_ConfigComponentPrescalers(const rcc_component_config_t* const pComponentConfig);

/**
 * @brief	Returns the configured prescaler selector for a requested bus
 * @param[in] bus	Target bus selector of @ref rcc_bus_t
 * Accepted values:
 * - @ref `RCC_AHB_BUS`: AHB bus
 * - @ref `RCC_APB1_BUS`: APB1 bus
 * - @ref `RCC_APB2_BUS`: APB2 bus
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
 * @returns @ref driver_status_t "Validation result"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Configuration is valid and internally consistent
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pRCCConfig was a null pointer
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Configuration contains an invalid source, divider, multiplier, or limit violation
 */
driver_status_t RCC_ValidateConfig(const rcc_config_t* const pRCCConfig);

/**
 * @brief	Applies a complete clock-tree configuration through the RCC driver orchestrator
 * @param[in] pClockTreeConfig	Pointer to @ref rcc_clock_tree_config_t
 * @returns @ref driver_status_t "Driver operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock-tree sequencing completed successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pClockTreeConfig was a null pointer
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Configuration contained invalid clock-tree values
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A source ready-state or switch confirmation timed out
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read during sequencing
 */
driver_status_t RCC_ConfigClockTree(const rcc_clock_tree_config_t* const pClockTreeConfig);

/**
 * @brief	Applies a complete RCC configuration descriptor
 * @param[in] pRCCConfig	Pointer to @ref rcc_config_t
 * @returns @ref driver_status_t "Driver operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Flash and clock-tree configuration completed successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pRCCConfig was a null pointer
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Configuration contained invalid fields or violated frequency limits
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A source ready-state or switch confirmation timed out
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read during sequencing
 */
driver_status_t RCC_Config(const rcc_config_t* const pRCCConfig);

/**
 * @brief	Loads the default 72 MHz Blue Pill clock-tree preset
 * @param[out] pRCCConfig	Pointer to @ref rcc_config_t
 */
void RCC_Load72MHzDefaultConfig(rcc_config_t* const pRCCConfig);

/**
 * @brief	Applies the default 72 MHz Blue Pill RCC configuration
 * @returns @ref driver_status_t "Driver operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Default 72 MHz configuration completed successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Default configuration validation failed
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A source ready-state or switch confirmation timed out
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read during sequencing
 */
driver_status_t RCC_Config72MHz(void);

/** @} */ // RCC_03_Driver_06_Config

/** @} */ // RCC_03_Driver

// C++ Compatibility
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_H_ */
