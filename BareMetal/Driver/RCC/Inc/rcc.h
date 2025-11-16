/**
 * @file rcc.h
 * @author Shrey Shah
 * @brief Reset & Clock Control Configuration
 * @version 1.2
 * @date 08-11-2025
 * @note Logs till v1.1:
 * @note - Aborted usage of `enums` as it consumes a lot of space
 * @note - Shifted to use combination of `typedef` & macros
 */

/*---------------------------------------------- Header Guards ----------------------------------------------*/
#ifndef RCC_H_
#define RCC_H_

// C++ Safeguard
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @include @file rcc_ll.h */
#include "rcc_ll.h"

/**
 * @addtogroup RCC_03_Driver
 * @{
 */

/*---------------------------------------------- RCC Flash Configuration ----------------------------------------------*/ 
/**
 * @brief    Driver Flash Configuration Type
 * @defgroup RCC_03_Driver_01_FlashConfig Driver Flash Configuration
 * @ingroup  RCC_03_Driver
 * @details
 * - This structure defines the Flash memory configuration for RCC driver
 * - Flash wait states must be configured based on system clock frequency
 * - Prefetch buffer can be enabled for improved performance
 * - STM32F103C8T6 specific wait state requirements:
 *   - 0 < SYSCLK ≤ 24 MHz → Zero wait state
 *   - 24 MHz < SYSCLK ≤ 48 MHz → One wait state  
 *   - 48 MHz < SYSCLK ≤ 72 MHz → Two wait states
 *
 * @see Reference Manual RM0008 - Section 3.3.3 Flash access control register (FLASH_ACR)
 * @see STM32F103C8T6 Datasheet - Section 4.1 Embedded Flash memory
 * @{
 */

/**
 * \section RCC_Driver_FlashConfig_Latency RCC Driver Flash Latency Definitions
 * \brief Flash Latency Definitions
 */

/**
 * @brief Flash latency type definition @typedef rcc_flash_latency_t */
typedef uint8_t rcc_flash_latency_t;
/** @brief Zero wait state (SYSCLK ≤ 24 MHz) @def RCC_FLASH_LATENCY_0 */
#define RCC_FLASH_LATENCY_0						((rcc_flash_latency_t) 0x00)
/** @brief One wait state (24 MHz < SYSCLK ≤ 48 MHz) @def RCC_FLASH_LATENCY_1 */
#define RCC_FLASH_LATENCY_1						((rcc_flash_latency_t) 0x01)
/** @brief Two wait states (48 MHz < SYSCLK ≤ 72 MHz) @def RCC_FLASH_LATENCY_2 */
#define RCC_FLASH_LATENCY_2						((rcc_flash_latency_t) 0x02)

/**
 * \section RCC_Driver_FlashConfig_Prefetch RCC Driver Flash Pre-fetch Buffer Definitions 
 * \brief Flash Pre-fetch Buffer Definitions
 */

/**
 * @brief Flash prefetch type definition @typedef rcc_flash_prefetch_t */
typedef uint8_t									rcc_flash_prefetch_t;
/** @brief Prefetch disabled @def RCC_FLASH_PREFETCH_DISABLE */
#define RCC_FLASH_PREFETCH_DISABLE				((rcc_flash_prefetch_t) 0x00)
/** @brief Prefetch enabled @def RCC_FLASH_PREFETCH_ENABLE */
#define RCC_FLASH_PREFETCH_ENABLE				((rcc_flash_prefetch_t) 0x01)

/** @brief Flash configuration structure @typedef rcc_flash_config_t */
typedef struct 
{
	/** 
	 * @brief Flash latency (wait states)
	 * @details
	 * - Use @ref RCC_FLASH_LATENCY_0 for SYSCLK ≤ 24 MHz
	 * - Use @ref RCC_FLASH_LATENCY_1 for 24 MHz < SYSCLK ≤ 48 MHz
	 * - Use @ref RCC_FLASH_LATENCY_2 for 48 MHz < SYSCLK ≤ 72 MHz
	 */
	rcc_flash_latency_t latency: 2;
	
	/** 
	 * @brief Flash prefetch buffer control
	 * @details
	 * - Use @ref RCC_FLASH_PREFETCH_DISABLE to disable prefetch
	 * - Use @ref RCC_FLASH_PREFETCH_ENABLE to enable prefetch (recommended)
	 */
	rcc_flash_prefetch_t prefetch: 1;
} rcc_flash_config_t;

/**
 * @brief Convert driver flash latency to low-level hardware value
 * @param[in] latency Driver flash latency value (@ref RCC_FLASH_LATENCY_0, RCC_FLASH_LATENCY_1, RCC_FLASH_LATENCY_2)
 * @returns Low-level flash latency value for hardware registers
 */
__STATIC_FORCEINLINE _rcc_flash_latency_t RCC_D2L_FlashLatency(const rcc_flash_latency_t latency)
{
	switch(latency)
	{
		case RCC_FLASH_LATENCY_0: return _RCC_FLASH_LATENCY_0; break;
		case RCC_FLASH_LATENCY_1: return _RCC_FLASH_LATENCY_1; break;
		case RCC_FLASH_LATENCY_2: return _RCC_FLASH_LATENCY_2; break;
		default: return _RCC_FLASH_LATENCY_0; break; // Safe fallback
	}
}

/**
 * @brief Convert driver flash prefetch to low-level hardware value
 * @param[in] prefetch Driver flash prefetch value (@ref RCC_FLASH_PREFETCH_DISABLE, RCC_FLASH_PREFETCH_ENABLE)
 * @returns Low-level flash prefetch value for hardware registers
 */
__STATIC_FORCEINLINE _rcc_flash_prefetch_t RCC_D2L_FlashPrefetch(const rcc_flash_prefetch_t prefetch)
{
	switch(prefetch)
	{
		case RCC_FLASH_PREFETCH_DISABLE: return _RCC_FLASH_PREFETCH_DISABLE; break;
		case RCC_FLASH_PREFETCH_ENABLE: return _RCC_FLASH_PREFETCH_ENABLE; break;
		default: return _RCC_FLASH_PREFETCH_DISABLE; break; // Safe fallback
	}
}

/**
 * @brief RCC Flash Configuration
 * @param flash Flash Configuration Structure @ref rcc_flash_config_t
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_ConfigFlash(const rcc_flash_config_t* const flash);

/** @} */ // RCC_03_Driver_01_FlashConfig

/*---------------------------------------------- RCC System Clock ----------------------------------------------*/
/**
 * @brief    Driver System Clock Configuration Types and Structure
 * @defgroup RCC_03_Driver_02_SystemClockConfig Driver System Clock Configuration
 * @ingroup  RCC_03_Driver
 * @details
 * - Type definitions and structure for system clock source configuration
 * - Defines the main system clock source and PLL configuration
 * - System clock feeds into AHB prescaler for bus distribution
 *
 * @see Reference Manual RM0008 - Section 7.3.2 Clock configuration register (RCC_CFGR)
 * @{
 */

/** @brief System clock source type definition @typedef rcc_system_clock_t */
typedef uint8_t 								rcc_system_clock_t;
/** @brief System clock source HSI (High Speed Internal) @def RCC_SYS_CLK_HSI */
#define RCC_SYS_CLK_HSI 						((rcc_system_clock_t) 0x00)
/** @brief System clock source HSE (High Speed External) @def RCC_SYS_CLK_HSE */
#define RCC_SYS_CLK_HSE 						((rcc_system_clock_t) 0x01)
/** @brief System clock source PLL (Phase Locked Loop) @def RCC_SYS_CLK_PLL */
#define RCC_SYS_CLK_PLL 						((rcc_system_clock_t) 0x02)

/**
 * @brief Convert driver system clock source to low-level hardware value
 * @param[in] src Driver system clock source value (@ref RCC_SYS_CLK_HSI "RCC_SYS_CLK_*")
 * @returns Low-level system clock source value for hardware registers
 */
__STATIC_FORCEINLINE _rcc_sys_clk_t RCC_D2L_SystemClockSource(const rcc_system_clock_t src)
{
	switch(src)
	{
		case RCC_SYS_CLK_HSI: return _RCC_SYS_CLK_HSI; break;
		case RCC_SYS_CLK_HSE: return _RCC_SYS_CLK_HSE; break;
		case RCC_SYS_CLK_PLL: return _RCC_SYS_CLK_PLL; break;
		default: return _RCC_SYS_CLK_HSI; break; // Safe fallback
	}
}

/**
 * @brief Convert low-level system clock source to driver hardware value
 * @param[in] src Low-level system clock source value (@ref _rcc_sys_clk_t "_RCC_SYS_CLK_*")
 * @returns Driver system clock source value for driver layer
 */
__STATIC_FORCEINLINE rcc_system_clock_t RCC_L2D_SystemClockSource(const _rcc_sys_clk_t src)
{
	switch(src)
	{
		case _RCC_SYS_CLK_HSI: return RCC_SYS_CLK_HSI; break;
		case _RCC_SYS_CLK_HSE: return RCC_SYS_CLK_HSE; break;
		case _RCC_SYS_CLK_PLL: return RCC_SYS_CLK_PLL; break;
		default: return RCC_SYS_CLK_HSI; break; // Safe fallback
	}
}

/**
 * @brief Controls the state of the Internal High Speed Clock (HSI)
 * @param[in] state 
 * Desired state:
 *	- DRIVER_STATE_OFF: Turn OFF HSI
 *	- DRIVER_STATE_ON: Turn ON HSI
 * @note Operates on the HSI ON/OFF bit @ref RCC_CR_HSION
 */
__STATIC_FORCEINLINE void RCC_ControlHSI(const driver_status_t state)
{
	if (state == DRIVER_STATE_ON) __RCC_SetCR(RCC, RCC_CR_HSION);
	else if(state == DRIVER_STATE_OFF) __RCC_ClearCR(RCC, RCC_CR_HSION);
}

/**
 * @brief Checks the readiness status of the HSI clock source.
 * @return DRIVER_STATE_READY if HSI is stable, otherwise DRIVER_STATE_BUSY
 * @note Relies on the RCC_CR_HSIRDY flag.
 */
__STATIC_FORCEINLINE driver_status_t RCC_HSIReady(void)
{
	return (__RCC_ReadCR(RCC) & RCC_CR_HSIRDY) ? DRIVER_STATE_READY : DRIVER_STATE_BUSY;
}

/**
 * @brief Controls the state of the External High Speed Clock (HSE)
 * @param[in] state 
 * Desired state:
 *	- DRIVER_STATE_OFF: Turn OFF HSE
 *	- DRIVER_STATE_ON: Turn ON HSE
 * @note Operates on the HSE ON/OFF bit @ref RCC_CR_HSEON
 */
__STATIC_FORCEINLINE void RCC_ControlHSE(const driver_status_t state)
{
	if (state == DRIVER_STATE_ON) __RCC_SetCR(RCC, RCC_CR_HSEON);
	else if(state == DRIVER_STATE_OFF) __RCC_ClearCR(RCC, RCC_CR_HSEON);
}

/**
 * @brief Checks the readiness status of the HSE clock source.
 * @return DRIVER_STATE_READY if HSE is stable, otherwise DRIVER_STATE_BUSY.
 * @note Relies on the RCC_CR_HSERDY flag.
 */
__STATIC_FORCEINLINE driver_status_t RCC_HSEReady(void)
{
	return (__RCC_ReadCR(RCC) & RCC_CR_HSERDY) ? DRIVER_STATE_READY : DRIVER_STATE_BUSY;
}

/**
 * @brief Controls the state of the Phase Lock Loop (PLL)
 * @param[in] state 
 * Desired state:
 *	- DRIVER_STATE_OFF: Turn OFF PLL
 *	- DRIVER_STATE_ON: Turn ON PLL
 * @note Operates on the PLL ON/OFF bit @ref RCC_CR_PLLON
 */
__STATIC_FORCEINLINE void RCC_ControlPLL(const driver_status_t state)
{
	if (state == DRIVER_STATE_ON) __RCC_SetCR(RCC, RCC_CR_PLLON);
	else if(state == DRIVER_STATE_OFF) __RCC_ClearCR(RCC, RCC_CR_PLLON);
}

/**
 * @brief Checks the readiness status of the PLL clock source.
 * @return DRIVER_STATE_READY if PLL is locked, otherwise DRIVER_STATE_BUSY.
 * @note Relies on the RCC_CR_PLLRDY flag.
 */
__STATIC_FORCEINLINE driver_status_t RCC_PLLReady(void)
{
	return (__RCC_ReadCR(RCC) & RCC_CR_PLLRDY) ? DRIVER_STATE_READY : DRIVER_STATE_BUSY;
}

/**
 * @brief Set System Clock Source
 * @param[in] sysClkSrc System Clock Source (@ref rcc_system_clock_t "RCC_SYS_CLK_*")
 */
__STATIC_FORCEINLINE void RCC_SetSysClkSrc(const rcc_system_clock_t sysClkSrc)
{
	uint32_t reg = __RCC_ReadCFGR(RCC);
	reg &= ~RCC_CFGR_SW_Msk;
	reg |= (uint32_t)(RCC_D2L_SystemClockSource(sysClkSrc) << RCC_CFGR_SW_Pos);
	__RCC_WriteCFGR(RCC, reg);
}

/**
 * @brief Retrieve System Clock Source
 * @returns @ref rcc_system_clock_t "System Clock Source"
 */
__STATIC_FORCEINLINE rcc_system_clock_t RCC_GetSysClkSrc(void)
{
	return RCC_L2D_SystemClockSource((_rcc_sys_clk_t)(__RCC_ReadCFGR(RCC) >> RCC_CFGR_SWS_Pos));
}

/** @} */ // RCC_03_Driver_02_SystemClockConfig

/*---------------------------------------------- RCC PLL ----------------------------------------------*/
/**
 * @brief    Driver PLL Configuration Types and Structure
 * @defgroup RCC_03_Driver_02_PLLConfig Driver PLL Configuration
 * @ingroup  RCC_03_Driver
 * @details
 * - Type definitions and structure for PLL (Phase Locked Loop) configuration
 * - PLL generates high-frequency system clock from lower frequency sources
 * - STM32F103C8T6 specific constraints and requirements
 *
 * @see Reference Manual RM0008 - Section 7.3.2 Clock configuration register (RCC_CFGR)
 * @{
 */

/** @brief PLL source type definition @typedef rcc_pll_src_t */
typedef uint8_t									rcc_pll_src_t;
/** @brief PLL source HSI (High Speed Internal) @def RCC_PLL_SRC_HSI */
#define RCC_PLL_SRC_HSI 						((rcc_pll_src_t) 0x00)
/** @brief PLL source HSE (High Speed External) @def RCC_PLL_SRC_HSE */
#define RCC_PLL_SRC_HSE 						((rcc_pll_src_t) 0x01)

/** @brief PLL multiplication factor type definition @typedef rcc_pll_mul_t */
typedef uint8_t									rcc_pll_mul_t;
/** @brief PLL multiplication by 2 @def RCC_PLL_MUL_2 */
#define RCC_PLL_MUL_2 							((rcc_pll_mul_t) 0x00)
/** @brief PLL multiplication by 3 @def RCC_PLL_MUL_3 */
#define RCC_PLL_MUL_3 							((rcc_pll_mul_t) 0x01)
/** @brief PLL multiplication by 4 @def RCC_PLL_MUL_4 */
#define RCC_PLL_MUL_4 							((rcc_pll_mul_t) 0x02)
/** @brief PLL multiplication by 5 @def RCC_PLL_MUL_5 */
#define RCC_PLL_MUL_5 							((rcc_pll_mul_t) 0x03)
/** @brief PLL multiplication by 6 @def RCC_PLL_MUL_6 */
#define RCC_PLL_MUL_6 							((rcc_pll_mul_t) 0x04)
/** @brief PLL multiplication by 7 @def RCC_PLL_MUL_7 */
#define RCC_PLL_MUL_7 							((rcc_pll_mul_t) 0x05)
/** @brief PLL multiplication by 8 @def RCC_PLL_MUL_8 */
#define RCC_PLL_MUL_8 							((rcc_pll_mul_t) 0x06)
/** @brief PLL multiplication by 9 @def RCC_PLL_MUL_9 */
#define RCC_PLL_MUL_9 							((rcc_pll_mul_t) 0x07)
/** @brief PLL multiplication by 10 @def RCC_PLL_MUL_10 */
#define RCC_PLL_MUL_10 							((rcc_pll_mul_t) 0x08)
/** @brief PLL multiplication by 11 @def RCC_PLL_MUL_11 */
#define RCC_PLL_MUL_11 							((rcc_pll_mul_t) 0x09)
/** @brief PLL multiplication by 12 @def RCC_PLL_MUL_12 */
#define RCC_PLL_MUL_12 							((rcc_pll_mul_t) 0x0A)
/** @brief PLL multiplication by 13 @def RCC_PLL_MUL_13 */
#define RCC_PLL_MUL_13 							((rcc_pll_mul_t) 0x0B)
/** @brief PLL multiplication by 14 @def RCC_PLL_MUL_14 */
#define RCC_PLL_MUL_14 							((rcc_pll_mul_t) 0x0C)
/** @brief PLL multiplication by 15 @def RCC_PLL_MUL_15 */
#define RCC_PLL_MUL_15 							((rcc_pll_mul_t) 0x0D)
/** @brief PLL multiplication by 16 @def RCC_PLL_MUL_16 */
#define RCC_PLL_MUL_16 							((rcc_pll_mul_t) 0x0E)

/** @brief PLL source prescaler type definition @typedef rcc_pll_src_psc_t */
typedef uint8_t									rcc_pll_src_psc_t;
/** @brief HSI division by 2 for PLL input @def RCC_PLL_SRC_HSI_DIV_2 */
#define RCC_PLL_SRC_HSI_DIV_2 					((rcc_pll_src_psc_t) 0x00)
/** @brief HSE division by 1 for PLL input @def RCC_PLL_SRC_HSE_DIV_1 */
#define RCC_PLL_SRC_HSE_DIV_1 					((rcc_pll_src_psc_t) 0x00)
/** @brief HSE division by 2 for PLL input @def RCC_PLL_SRC_HSE_DIV_2 */
#define RCC_PLL_SRC_HSE_DIV_2 					((rcc_pll_src_psc_t) 0x01)

/**
 * @brief PLL Configuration Structure
 * @typedef rcc_pll_config_t
 */
typedef struct {
	/**
	 * @brief PLL Multiplication Factor Configuration
	 * @details
	 * - Determines the multiplication factor for PLL output
	 * - Determines the final Clock Frequency if PLL is System Clock Source
	 * - Max frequency: 72MHz
	 * - Do not use value 0x0F (reserved, not multiplication by 16)
	 * - Use @ref RCC_PLL_MUL_16 for multiplication by 16
	 */
	rcc_pll_mul_t multiplication_factor: 4;
	
	/**
	 * @brief PLL Source Configuration
	 * @details
	 * - Determines the input source to PLL
	 * - For STM32F1xx, HSI is always divided by 2 before PLL input
	 * - HSE can be used directly or divided by 2
	 */
	rcc_pll_src_t source: 1;
	
	/**
	 * @brief PLL Source Prescaler Configuration
	 * @details
	 * - Determines the prescaler for PLL input source
	 * - For STM32F1xx, HSI does not have prescaler configuration (always /2)
	 * - HSE can be configured with division by 1 or 2
	 * - Only applicable when source is HSE (@ref RCC_PLL_SRC_HSE)
	 */
	rcc_pll_src_psc_t source_prescaler: 1;
} rcc_pll_config_t;

/**
 * @brief System Clock Configuration Structure
 * @typedef rcc_sys_clk_config_t
 */
typedef struct
{
	/**
	 * @brief System Clock Source
	 * @details
	 * - System Clock Source Values Refer @ref RCC_SYS_CLK_HSI "RCC_SYS_CLK_*"
	 * - This defines the AHB input clock before AHB Prescaler
	 * - Determines the source for the main system clock
	 */
	rcc_system_clock_t clk_src;
	
	/**
	 * @brief Phase Lock Loop (PLL) Configuration Structure
	 * @details
	 * - Refer @ref rcc_pll_config_t for PLL configuration options
	 * - This parameter defines the PLL Configuration to be set
	 * - Only used when system clock source is @ref RCC_SYS_CLK_PLL
	 */
	rcc_pll_config_t pll;
} rcc_sys_clk_config_t;

/**
 * @brief Convert driver PLL source to low-level hardware value
 * @param[in] src Driver PLL source value (@ref RCC_PLL_SRC_HSI "RCC_PLL_SRC_*")
 * @returns Low-level PLL source value for hardware registers
 */
__STATIC_FORCEINLINE _rcc_pll_src_t RCC_D2L_PLLSource(const rcc_pll_src_t src)
{
    switch(src)
	{
        case RCC_PLL_SRC_HSI: return _RCC_PLL_SRC_HSI; break;
        case RCC_PLL_SRC_HSE: return _RCC_PLL_SRC_HSE; break;
        default: return _RCC_PLL_SRC_HSI; break; // Safe fallback
    }
}

/**
 * @brief Convert driver PLL multiplication factor to low-level hardware value
 * @param[in] mul Driver PLL multiplication value (@ref RCC_PLL_MUL_2 "RCC_PLL_MUL_*")
 * @returns Low-level PLL multiplication value for hardware registers
 */
__STATIC_FORCEINLINE _rcc_pll_mul_t RCC_D2L_PLLMultiplication(const rcc_pll_mul_t mul)
{
    switch(mul)
	{
        case RCC_PLL_MUL_2:  return _RCC_PLL_MUL_2;
        case RCC_PLL_MUL_3:  return _RCC_PLL_MUL_3;
        case RCC_PLL_MUL_4:  return _RCC_PLL_MUL_4;
        case RCC_PLL_MUL_5:  return _RCC_PLL_MUL_5;
        case RCC_PLL_MUL_6:  return _RCC_PLL_MUL_6;
        case RCC_PLL_MUL_7:  return _RCC_PLL_MUL_7;
        case RCC_PLL_MUL_8:  return _RCC_PLL_MUL_8;
        case RCC_PLL_MUL_9:  return _RCC_PLL_MUL_9;
        case RCC_PLL_MUL_10: return _RCC_PLL_MUL_10;
        case RCC_PLL_MUL_11: return _RCC_PLL_MUL_11;
        case RCC_PLL_MUL_12: return _RCC_PLL_MUL_12;
        case RCC_PLL_MUL_13: return _RCC_PLL_MUL_13;
        case RCC_PLL_MUL_14: return _RCC_PLL_MUL_14;
        case RCC_PLL_MUL_15: return _RCC_PLL_MUL_15;
        case RCC_PLL_MUL_16: return _RCC_PLL_MUL_16;
        default: return _RCC_PLL_MUL_2; // Safe fallback
    }
}

/**
 * @brief Convert driver PLL source prescaler to low-level hardware value
 * @param[in] prescaler Driver PLL source prescaler value (@ref RCC_PLL_SRC_HSE_DIV_1 "RCC_PLL_SRC_*_DIV_*")
 * @returns Low-level PLL source prescaler value for hardware registers
 */
__STATIC_FORCEINLINE _rcc_pll_src_psc_t RCC_D2L_PLLSourcePrescaler(const rcc_pll_src_psc_t prescaler)
{
    switch(prescaler)
	{
        case RCC_PLL_SRC_HSE_DIV_1: return _RCC_PLL_SRC_HSE_DIV_1;
        case RCC_PLL_SRC_HSE_DIV_2: return _RCC_PLL_SRC_HSE_DIV_2;
        default: return _RCC_PLL_SRC_HSE_DIV_1; // Safe fallback
    }
}

/**
 * @brief Convert low-level PLL source to driver hardware value
 * @param[in] src Low-level PLL source value (@ref _RCC_PLL_SRC_HSI "_RCC_PLL_SRC_*")
 * @returns Driver PLL source value for driver layer
 */
__STATIC_FORCEINLINE rcc_pll_src_t RCC_L2D_PLLSource(const _rcc_pll_src_t src)
{
	switch(src)
	{
		case _RCC_PLL_SRC_HSI: return RCC_PLL_SRC_HSI; break;
		case _RCC_PLL_SRC_HSE: return RCC_PLL_SRC_HSE; break;
		default: return RCC_PLL_SRC_HSI; break; // Safe fallback
	}
}

/**
 * @brief Convert low-level PLL multiplication factor to driver hardware value
 * @param[in] mul Low-level PLL multiplication value (@ref _RCC_PLL_MUL_2 "_RCC_PLL_MUL_*")
 * @returns Driver PLL multiplication value for driver layer
 */
__STATIC_FORCEINLINE rcc_pll_mul_t RCC_L2D_PLLMultiplication(const _rcc_pll_mul_t mul)
{
	switch(mul)
	{
		case _RCC_PLL_MUL_2:  return RCC_PLL_MUL_2;
		case _RCC_PLL_MUL_3:  return RCC_PLL_MUL_3;
		case _RCC_PLL_MUL_4:  return RCC_PLL_MUL_4;
		case _RCC_PLL_MUL_5:  return RCC_PLL_MUL_5;
		case _RCC_PLL_MUL_6:  return RCC_PLL_MUL_6;
		case _RCC_PLL_MUL_7:  return RCC_PLL_MUL_7;
		case _RCC_PLL_MUL_8:  return RCC_PLL_MUL_8;
		case _RCC_PLL_MUL_9:  return RCC_PLL_MUL_9;
		case _RCC_PLL_MUL_10: return RCC_PLL_MUL_10;
		case _RCC_PLL_MUL_11: return RCC_PLL_MUL_11;
		case _RCC_PLL_MUL_12: return RCC_PLL_MUL_12;
		case _RCC_PLL_MUL_13: return RCC_PLL_MUL_13;
		case _RCC_PLL_MUL_14: return RCC_PLL_MUL_14;
		case _RCC_PLL_MUL_15: return RCC_PLL_MUL_15;
		case _RCC_PLL_MUL_16: return RCC_PLL_MUL_16;
		default: return RCC_PLL_MUL_2; // Safe fallback
	}
}

/**
 * @brief Convert low-level PLL source prescaler to driver hardware value
 * @param[in] prescaler Low-level PLL source prescaler value (@ref _RCC_PLL_SRC_HSE_DIV_1 "_RCC_PLL_SRC_*_DIV_*")
 * @returns Driver PLL source prescaler value for driver layer
 */
__STATIC_FORCEINLINE rcc_pll_src_psc_t RCC_L2D_PLLSourcePrescaler(const _rcc_pll_src_psc_t prescaler)
{
	switch(prescaler)
	{
		case _RCC_PLL_SRC_HSE_DIV_1: return RCC_PLL_SRC_HSE_DIV_1;
		case _RCC_PLL_SRC_HSE_DIV_2: return RCC_PLL_SRC_HSE_DIV_2;
		default: return RCC_PLL_SRC_HSE_DIV_1; // Safe fallback
	}
}

/**
 * @brief Get current PLL source configuration from hardware registers
 * @returns Current PLL source configuration as driver layer value
 * @note Reads PLLSRC bits from RCC_CFGR register and converts to driver type
 */
__STATIC_FORCEINLINE rcc_pll_src_t RCC_GetPLLSource(void)
{
	return RCC_L2D_PLLSource((_rcc_pll_src_t)((__RCC_ReadCFGR(RCC) & RCC_CFGR_PLLSRC_Msk) >> RCC_CFGR_PLLSRC_Pos));
}

/**
 * @brief Get current PLL HSE source prescaler configuration from hardware registers
 * @returns Current PLL HSE source prescaler configuration as driver layer value
 * @note Reads PLLXTPRE bits from RCC_CFGR register and converts to driver type
 * @note Only applicable when PLL source is HSE
 */
__STATIC_FORCEINLINE rcc_pll_src_psc_t RCC_GetPLLSourcePrescaler(void)
{
	return RCC_L2D_PLLSourcePrescaler((_rcc_pll_src_psc_t)((__RCC_ReadCFGR(RCC) & RCC_CFGR_PLLXTPRE_Msk) >> RCC_CFGR_PLLXTPRE_Pos));
}

/**
 * @brief Get current core clock frequency from hardware configuration
 * @returns Current core clock frequency in Hz
 * @note Calculates core frequency based on current system clock source and PLL configuration
 * @note Core clock is the system clock before AHB prescaler
 * @note For PLL configurations, calculates frequency based on source and multiplication factor
 */
_rcc_freq_t RCC_GetCoreClockFreq(void);

/** @} */ // RCC_03_Driver_02_PLLConfig

/*---------------------------------------------- RCC Bus Prescaler ----------------------------------------------*/
/**
 * @brief    Driver Bus Prescaler Configuration Structure  
 * @defgroup RCC_03_Driver_03_BusPrescalerConfig Driver Bus Prescaler Configuration
 * @ingroup  RCC_03_Driver
 * @details
 * - Configuration structure for AHB, APB1, and APB2 bus prescaler
 * - Each bus has specific maximum frequency limits
 * - Used during system clock configuration
 *
 * @see Reference Manual RM0008 - Section 7.3.2 Clock configuration register (RCC_CFGR)
 * @{
 */

/** @brief RCC Bus @typedef rcc_bus_t */
typedef uint8_t									rcc_bus_t;
/** @brief AHB Bus @def RCC_AHB_BUS */
#define RCC_AHB_BUS								((rcc_bus_t) 0x00)
/** @brief APB1 Bus @def RCC_APB1_BUS */
#define RCC_APB1_BUS							((rcc_bus_t) 0x01)
/** @brief APB2 Bus @def RCC_APB2_BUS */
#define RCC_APB2_BUS							((rcc_bus_t) 0x02)

/** @brief Prescaler type definition @typedef rcc_bus_prescaler_t */
typedef uint8_t									rcc_bus_prescaler_t;
/** @brief AHB division by 1 (no prescaling) @def RCC_AHB_DIV_1 */
#define RCC_AHB_DIV_1 							((rcc_bus_prescaler_t) 0x00)
/** @brief AHB division by 2 @def RCC_AHB_DIV_2 */
#define RCC_AHB_DIV_2 							((rcc_bus_prescaler_t) 0x01)
/** @brief AHB division by 4 @def RCC_AHB_DIV_4 */
#define RCC_AHB_DIV_4 							((rcc_bus_prescaler_t) 0x02)
/** @brief AHB division by 8 @def RCC_AHB_DIV_8 */
#define RCC_AHB_DIV_8 							((rcc_bus_prescaler_t) 0x03)
/** @brief AHB division by 16 @def RCC_AHB_DIV_16 */
#define RCC_AHB_DIV_16 							((rcc_bus_prescaler_t) 0x04)
/** @brief AHB division by 64 @def RCC_AHB_DIV_64 */
#define RCC_AHB_DIV_64 							((rcc_bus_prescaler_t) 0x06)
/** @brief AHB division by 128 @def RCC_AHB_DIV_128 */
#define RCC_AHB_DIV_128 						((rcc_bus_prescaler_t) 0x07)
/** @brief AHB division by 256 @def RCC_AHB_DIV_256 */
#define RCC_AHB_DIV_256 						((rcc_bus_prescaler_t) 0x08)
/** @brief AHB division by 512 @def RCC_AHB_DIV_512 */
#define RCC_AHB_DIV_512 						((rcc_bus_prescaler_t) 0x09)
/** @brief APB1 division by 1 (no prescaling) @def RCC_APB1_DIV_1 */
#define RCC_APB1_DIV_1 							((rcc_bus_prescaler_t) 0x00)
/** @brief APB1 division by 2 @def RCC_APB1_DIV_2 */
#define RCC_APB1_DIV_2 							((rcc_bus_prescaler_t) 0x01)
/** @brief APB1 division by 4 @def RCC_APB1_DIV_4 */
#define RCC_APB1_DIV_4 							((rcc_bus_prescaler_t) 0x02)
/** @brief APB1 division by 8 @def RCC_APB1_DIV_8 */
#define RCC_APB1_DIV_8 							((rcc_bus_prescaler_t) 0x03)
/** @brief APB1 division by 16 @def RCC_APB1_DIV_16 */
#define RCC_APB1_DIV_16 						((rcc_bus_prescaler_t) 0x04)
/** @brief APB2 division by 1 (no prescaling) @def RCC_APB2_DIV_1 */
#define RCC_APB2_DIV_1 							((rcc_bus_prescaler_t) 0x00)
/** @brief APB2 division by 2 @def RCC_APB2_DIV_2 */
#define RCC_APB2_DIV_2 							((rcc_bus_prescaler_t) 0x01)
/** @brief APB2 division by 4 @def RCC_APB2_DIV_4 */
#define RCC_APB2_DIV_4 							((rcc_bus_prescaler_t) 0x02)
/** @brief APB2 division by 8 @def RCC_APB2_DIV_8 */
#define RCC_APB2_DIV_8 							((rcc_bus_prescaler_t) 0x03)
/** @brief APB2 division by 16 @def RCC_APB2_DIV_16 */
#define RCC_APB2_DIV_16 						((rcc_bus_prescaler_t) 0x04)

/**
 * @brief Bus Prescaler Configuration Structure
 * @typedef rcc_bus_config_t
 */
typedef struct 
{
	/**
	 * @brief AHB Bus Prescaler
	 * @details
	 * - AHB Prescaler Values Refer @ref RCC_AHB_DIV_1 "RCC_AHB_DIV_*"
	 * - Max frequency = 72MHz
	 * - AHB clock = SYSCLK / AHB prescaler
	 */
	rcc_bus_prescaler_t AHB: 4;
	
	/**
	 * @brief APB1 Bus Prescaler
	 * @details  
	 * - APB1 Prescaler Values Refer @ref RCC_APB1_DIV_1 "RCC_APB1_DIV_*"
	 * - Max frequency = 36MHz
	 * - APB1 clock = AHB clock / APB1 prescaler
	 */
	rcc_bus_prescaler_t APB1: 3;
	
	/**
	 * @brief APB2 Bus Prescaler
	 * @details
	 * - APB2 Prescaler Values Refer @ref RCC_APB2_DIV_1 "RCC_APB2_DIV_*"
	 * - Max frequency = 72MHz  
	 * - APB2 clock = AHB clock / APB2 prescaler
	 */
	rcc_bus_prescaler_t APB2: 3;
} rcc_bus_config_t;

/**
 * @brief Convert driver AHB prescaler to low-level hardware value
 * @param[in] prescaler Driver AHB prescaler value (@ref RCC_AHB_DIV_1 "RCC_AHB_DIV_*")
 * @returns Low-level AHB prescaler value for hardware registers
 */
__STATIC_FORCEINLINE _rcc_bus_prescaler_t RCC_D2L_AHBPrescaler(const rcc_bus_prescaler_t prescaler)
{
    switch(prescaler)
	{
        case RCC_AHB_DIV_1:   return _RCC_AHB_DIV_1; break;
        case RCC_AHB_DIV_2:   return _RCC_AHB_DIV_2; break;
        case RCC_AHB_DIV_4:   return _RCC_AHB_DIV_4; break;
        case RCC_AHB_DIV_8:   return _RCC_AHB_DIV_8; break;
        case RCC_AHB_DIV_16:  return _RCC_AHB_DIV_16; break;
        case RCC_AHB_DIV_64:  return _RCC_AHB_DIV_64; break;
        case RCC_AHB_DIV_128: return _RCC_AHB_DIV_128; break;
        case RCC_AHB_DIV_256: return _RCC_AHB_DIV_256; break;
        case RCC_AHB_DIV_512: return _RCC_AHB_DIV_512; break;
        default: return _RCC_AHB_DIV_1; break; // Safe fallback
    }
}

/**
 * @brief Convert driver APB1 prescaler to low-level hardware value
 * @param[in] prescaler Driver APB1 prescaler value (@ref RCC_APB1_DIV_1 "RCC_APB1_DIV_*")
 * @returns Low-level APB1 prescaler value for hardware registers
 */
__STATIC_FORCEINLINE _rcc_bus_prescaler_t RCC_D2L_APB1Prescaler(const rcc_bus_prescaler_t prescaler)
{
    switch(prescaler)
	{
        case RCC_APB1_DIV_1:  return _RCC_APB1_DIV_1; break;
        case RCC_APB1_DIV_2:  return _RCC_APB1_DIV_2; break;
        case RCC_APB1_DIV_4:  return _RCC_APB1_DIV_4; break;
        case RCC_APB1_DIV_8:  return _RCC_APB1_DIV_8; break;
        case RCC_APB1_DIV_16: return _RCC_APB1_DIV_16; break;
        default: return _RCC_APB1_DIV_1; break; // Safe fallback
    }
}

/**
 * @brief Convert driver APB2 prescaler to low-level hardware value
 * @param[in] prescaler Driver APB2 prescaler value (@ref RCC_APB2_DIV_1 "RCC_APB2_DIV_*")
 * @returns Low-level APB2 prescaler value for hardware registers
 */
__STATIC_FORCEINLINE _rcc_bus_prescaler_t RCC_D2L_APB2Prescaler(const rcc_bus_prescaler_t prescaler)
{
    switch(prescaler)
	{
        case RCC_APB2_DIV_1:  return _RCC_APB2_DIV_1; break;
        case RCC_APB2_DIV_2:  return _RCC_APB2_DIV_2; break;
        case RCC_APB2_DIV_4:  return _RCC_APB2_DIV_4; break;
        case RCC_APB2_DIV_8:  return _RCC_APB2_DIV_8; break;
        case RCC_APB2_DIV_16: return _RCC_APB2_DIV_16; break;
        default: return _RCC_APB2_DIV_1; break; // Safe fallback
    }
}

/**
 * @brief Convert low-level AHB prescaler to driver hardware value
 * @param[in] prescaler Low-level AHB prescaler value (@ref _RCC_AHB_DIV_1 "_RCC_AHB_DIV_*")
 * @returns Driver AHB prescaler value for driver layer
 */
__STATIC_FORCEINLINE rcc_bus_prescaler_t RCC_L2D_AHBPrescaler(const _rcc_bus_prescaler_t prescaler)
{
	switch(prescaler)
	{
		case _RCC_AHB_DIV_1:   return RCC_AHB_DIV_1; break;
		case _RCC_AHB_DIV_2:   return RCC_AHB_DIV_2; break;
		case _RCC_AHB_DIV_4:   return RCC_AHB_DIV_4; break;
		case _RCC_AHB_DIV_8:   return RCC_AHB_DIV_8; break;
		case _RCC_AHB_DIV_16:  return RCC_AHB_DIV_16; break;
		case _RCC_AHB_DIV_64:  return RCC_AHB_DIV_64; break;
		case _RCC_AHB_DIV_128: return RCC_AHB_DIV_128; break;
		case _RCC_AHB_DIV_256: return RCC_AHB_DIV_256; break;
		case _RCC_AHB_DIV_512: return RCC_AHB_DIV_512; break;
		default: return RCC_AHB_DIV_1; break; // Safe fallback
	}
}

/**
 * @brief Convert low-level APB1 prescaler to driver hardware value
 * @param[in] prescaler Low-level APB1 prescaler value (@ref _RCC_APB1_DIV_1 "_RCC_APB1_DIV_*")
 * @returns Driver APB1 prescaler value for driver layer
 */
__STATIC_FORCEINLINE rcc_bus_prescaler_t RCC_L2D_APB1Prescaler(const _rcc_bus_prescaler_t prescaler)
{
	switch(prescaler)
	{
		case _RCC_APB1_DIV_1:  return RCC_APB1_DIV_1; break;
		case _RCC_APB1_DIV_2:  return RCC_APB1_DIV_2; break;
		case _RCC_APB1_DIV_4:  return RCC_APB1_DIV_4; break;
		case _RCC_APB1_DIV_8:  return RCC_APB1_DIV_8; break;
		case _RCC_APB1_DIV_16: return RCC_APB1_DIV_16; break;
		default: return RCC_APB1_DIV_1; break; // Safe fallback
	}
}

/**
 * @brief Convert low-level APB2 prescaler to driver hardware value
 * @param[in] prescaler Low-level APB2 prescaler value (@ref _RCC_APB2_DIV_1 "_RCC_APB2_DIV_*")
 * @returns Driver APB2 prescaler value for driver layer
 */
__STATIC_FORCEINLINE rcc_bus_prescaler_t RCC_L2D_APB2Prescaler(const _rcc_bus_prescaler_t prescaler)
{
	switch(prescaler)
	{
		case _RCC_APB2_DIV_1:  return RCC_APB2_DIV_1; break;
		case _RCC_APB2_DIV_2:  return RCC_APB2_DIV_2; break;
		case _RCC_APB2_DIV_4:  return RCC_APB2_DIV_4; break;
		case _RCC_APB2_DIV_8:  return RCC_APB2_DIV_8; break;
		case _RCC_APB2_DIV_16: return RCC_APB2_DIV_16; break;
		default: return RCC_APB2_DIV_1; break; // Safe fallback
	}
}

/**
 * @brief Configure RCC Bus Prescaler
 * @param[in] rccBusPrescaler Pointer to Bus Prescaler Configuration Structure
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_ConfigBusPrescaler(rcc_bus_config_t* const rccBusPrescaler);

/**
 * @brief Retrieves the currently configured prescaler value for a specified bus
 * @param[in] rccBus The target bus to query (e.g., RCC_AHB_BUS). Refer to @ref rcc_bus_t.
 * @return The high-level prescaler setting. Refer to @ref rcc_bus_prescaler_t.
 * @note This is an inline helper function for performance.
 */
rcc_bus_prescaler_t RCC_GetBusPrescaler(const rcc_bus_t rccBus);

/**
 * @brief Get current bus clock frequency
 * @param[in] bus Target bus identifier (@ref rcc_bus_t)
 * @returns Current bus clock frequency in Hz
 * @note Calculates bus frequency based on core clock and bus prescaler
 * @note For AHB bus: returns frequency after AHB prescaler
 * @note For APB1/APB2 buses: returns frequency after respective APB prescaler
 * @note Uses right-shift operation for efficient division by prescaler value
 */
_rcc_freq_t RCC_GetBusFreq(const rcc_bus_t bus);

/** @} */ // RCC_03_Driver_03_BusPrescalerConfig

/*---------------------------------------------- RCC Component ----------------------------------------------*/
/**
 * @brief    Driver Component Prescaler Configuration Types and Structure
 * @defgroup RCC_03_Driver_05_ComponentPrescalerConfig Driver Component Prescaler Configuration
 * @ingroup  RCC_03_Driver
 * @details
 * - Type definitions and structure for peripheral component prescaler configuration
 * - ADC and USB have specific frequency requirements and clock sources
 * - STM32F103C8T6 specific constraints and requirements
 *
 * @see Reference Manual RM0008 - Section 7.3.2 Clock configuration register (RCC_CFGR)
 * @{
 */

/** @brief Component prescaler type definition @typedef rcc_component_prescaler_t */
typedef uint8_t									rcc_component_prescaler_t;
/** @brief ADC division by 2 @def RCC_ADC_DIV_2 */
#define RCC_ADC_DIV_2							((rcc_component_prescaler_t) 0x00)
/** @brief ADC division by 4 @def RCC_ADC_DIV_4 */
#define RCC_ADC_DIV_4							((rcc_component_prescaler_t) 0x01)
/** @brief ADC division by 6 @def RCC_ADC_DIV_6 */
#define RCC_ADC_DIV_6							((rcc_component_prescaler_t) 0x02)
/** @brief ADC division by 8 @def RCC_ADC_DIV_8 */
#define RCC_ADC_DIV_8							((rcc_component_prescaler_t) 0x03)

/** @brief USB division by 1.5 @def RCC_USB_DIV_1_5 */
#define RCC_USB_DIV_1_5 						((rcc_component_prescaler_t) 0x00)
/** @brief USB division by 1 (no prescaling) @def RCC_USB_DIV_1 */
#define RCC_USB_DIV_1 							((rcc_component_prescaler_t) 0x01)

/**
 * @brief Component Prescaler Configuration Structure
 * @typedef rcc_component_config_t
 */
typedef struct 
{
	/**
	 * @brief ADC Prescaler Configuration
	 * @details
	 * - ADC Prescaler Values Refer @ref RCC_ADC_DIV_2 "RCC_ADC_DIV_*"
	 * - Max Frequency: 14MHz
	 * - Clock Source: APB2
	 * - ADC clock = APB2 clock / ADC prescaler
	 */
	rcc_component_prescaler_t ADC: 2;
	
	/**
	 * @brief USB Prescaler Configuration
	 * @details
	 * - USB Prescaler Values Refer @ref RCC_USB_DIV_1_5 "RCC_USB_DIV_*"
	 * - Max Frequency: 48MHz (must be exactly 48MHz for USB operation)
	 * - Clock Source: PLL
	 * - USB clock = PLL clock / USB prescaler
	 */
	rcc_component_prescaler_t USB: 1;
} rcc_component_config_t;

/**
 * @brief RCC Prescaler Configuration Structure
 * @typedef rcc_prescaler_config_t
 */
typedef struct
{
	/**
	 * @brief Bus Prescaler Configuration
	 * @details
	 * - Configuration for AHB, APB1, and APB2 bus prescaler
	 * - Refer @ref rcc_bus_prescaler_config_t for details
	 */
	rcc_bus_config_t bus;

	/**
	 * @brief Components Prescaler Configuration
	 * @details
	 * - Peripheral component prescaler (ADC, USB)
	 * - Refer @ref rcc_component_config_t for details
	 */
	rcc_component_config_t component;
} rcc_prescaler_config_t;

/**
 * @brief Convert driver ADC prescaler to low-level hardware value
 * @param[in] prescaler Driver ADC prescaler value (@ref RCC_ADC_DIV_2 "RCC_ADC_DIV_*")
 * @returns Low-level ADC prescaler value for hardware registers
 */
__STATIC_FORCEINLINE _rcc_component_prescaler_t RCC_D2L_ADCPrescaler(const rcc_component_prescaler_t prescaler)
{
    switch(prescaler)
	{
        case RCC_ADC_DIV_2: return _RCC_ADC_DIV_2; break;
        case RCC_ADC_DIV_4: return _RCC_ADC_DIV_4; break;
        case RCC_ADC_DIV_6: return _RCC_ADC_DIV_6; break;
        case RCC_ADC_DIV_8: return _RCC_ADC_DIV_8; break;
        default: return _RCC_ADC_DIV_6; break; // Safe fallback
    }
}

/**
 * @brief Convert driver USB prescaler to low-level hardware value
 * @param[in] prescaler Driver USB prescaler value (@ref RCC_USB_DIV_1_5 "RCC_USB_DIV_*")
 * @returns Low-level USB prescaler value for hardware registers
 */
__STATIC_FORCEINLINE _rcc_component_prescaler_t RCC_D2L_USBPrescaler(const rcc_component_prescaler_t prescaler)
{
    switch(prescaler)
	{
        case RCC_USB_DIV_1_5: return _RCC_USB_DIV_1_5; break;
        case RCC_USB_DIV_1:   return _RCC_USB_DIV_1; break;
        default: return _RCC_USB_DIV_1_5; break; // Safe fallback
    }
}

/**
 * @brief Convert low-level ADC prescaler to driver hardware value
 * @param[in] prescaler Low-level ADC prescaler value (@ref _RCC_ADC_DIV_2 "_RCC_ADC_DIV_*")
 * @returns Driver ADC prescaler value for driver layer
 */
__STATIC_FORCEINLINE rcc_component_prescaler_t RCC_L2D_ADCPrescaler(const _rcc_component_prescaler_t prescaler)
{
	switch(prescaler)
	{
		case _RCC_ADC_DIV_2: return RCC_ADC_DIV_2; break;
		case _RCC_ADC_DIV_4: return RCC_ADC_DIV_4; break;
		case _RCC_ADC_DIV_6: return RCC_ADC_DIV_6; break;
		case _RCC_ADC_DIV_8: return RCC_ADC_DIV_8; break;
		default: return RCC_ADC_DIV_2; break; // Safe fallback
	}
}

/**
 * @brief Convert low-level USB prescaler to driver hardware value
 * @param[in] prescaler Low-level USB prescaler value (@ref _RCC_USB_DIV_1_5 "_RCC_USB_DIV_*")
 * @returns Driver USB prescaler value for driver layer
 */
__STATIC_FORCEINLINE rcc_component_prescaler_t RCC_L2D_USBPrescaler(const _rcc_component_prescaler_t prescaler)
{
	switch(prescaler)
	{
		case _RCC_USB_DIV_1_5: return RCC_USB_DIV_1_5; break;
		case _RCC_USB_DIV_1:   return RCC_USB_DIV_1; break;
		default: return RCC_USB_DIV_1_5; break; // Safe fallback
	}
}

/**
 * @brief Configure RCC Component prescaler
 * @param[in] rccComponentPrescaler Pointer to Component Prescaler Configuration Structure
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_ConfigComponentPrescaler(rcc_component_config_t* const rccComponentPrescaler);

/** @} */ // RCC_03_Driver_05_ComponentPrescalerConfig

/*---------------------------------------------- RCC Main Configuration ----------------------------------------------*/
/**
 * @brief    Driver RCC Main Configuration Structure
 * @defgroup RCC_03_Driver_06_MainConfig Driver RCC Main Configuration
 * @ingroup  RCC_03_Driver
 * @details
 * - Main configuration structure that combines all RCC subsystems
 * - Used as the primary parameter for complete clock tree configuration
 * - Contains all necessary components for system clock setup
 *
 * @see Reference Manual RM0008 - Section 7. Clock Configuration
 * @{
 */

/**
 * @brief RCC Configuration Structure
 * @typedef rcc_config_t
 */
typedef struct
{
	/**
	 * @brief Prescaler Configuration
	 * @details
	 * - Combined configuration for all clock prescaler
	 * - Includes bus prescaler (AHB, APB1, APB2) and component prescaler (ADC, USB)
	 * - Controls clock distribution throughout the system
	 * - Refer @ref rcc_prescaler_config_t for detailed structure
	 */
	volatile rcc_prescaler_config_t prescaler;
	
	/**
	 * @brief System Clock Configuration
	 * @details
	 * - Main system clock source and PLL configuration
	 * - Refer @ref rcc_sys_clk_config_t for details
	 */
	volatile rcc_sys_clk_config_t system;
	
	/**
	 * @brief Flash Configuration
	 * @details
	 * - Flash memory wait states and prefetch buffer configuration
	 * - Refer @ref rcc_flash_config_t for details
	 */
	volatile rcc_flash_config_t flash;
} rcc_config_t;

/**
 * @brief Configures the system clock and bus prescaler.
 *
 * Initializes the RCC to the configuration specified in @p rcc,
 * setting up Flash latency, enabling required clock sources (HSI/HSE/PLL),
 * and switching the system clock source in a single atomic CFGR update.
 *
 * All prerequisite clocks are verified to be ready before the switch,
 * ensuring a stable and deterministic clock tree setup.
 *
 * @param[in] rcc Pointer to @ref rcc_config_t "RCC Configuration Structure"
 *
 * @retval DRIVER_SUCCESS          Configuration successful.
 * @retval DRIVER_ERR_INVALID_ARG  Null configuration pointer.
 * @retval DRIVER_ERR_TIMEOUT      Clock source failed to stabilize (if timeout supported).
 *
 * @note Must be called once during system startup before any peripheral initialization.
 * @note Blocks until selected clock source (HSE/PLL) is stable.
 */
driver_status_t RCC_Config(rcc_config_t* const rcc);

/**
 * @brief Sets default flash configuration for 72MHz
 * @param flashConfig Pointer to @ref rcc_flash_config_t "Flash Configuration Structure"
 */
extern void RCC_72MHz_FlashDefaultConfig(rcc_flash_config_t* const flashConfig);

/**
 * @brief PLL Default Configuration for 72MHz
 * @param pllConfig Pointer to @ref rcc_pll_config_t "PLL Configuration Structure"
 */
void RCC_72MHz_PLLDefaultConfig(rcc_pll_config_t* const pllConfig);

/**
 * @brief Sets System Configuration for 72MHz Clock
 * @param sysClkConfig Pointer to @ref rcc_sys_clk_config_t "System Clock Configuration Structure"
 */
void RCC_72MHz_SystemDefaultConfig(rcc_sys_clk_config_t* const sysClkConfig);

/**
 * @brief Sets Bus Prescaler for 72MHz
 * @param busPrescalerConfig Pointer to @ref rcc_bus_config_t "Bus Prescaler Configuration Structure"
 */
void RCC_72MHz_BusPrescalerDefaultConfig(rcc_bus_config_t* const busPrescalerConfig);

/**
 * @brief Sets Component Prescaler for 72MHz
 * @param componentPrescalerConfig Pointer to @ref rcc_component_config_t "Component Prescaler Configuration Structure"
 */
void RCC_72MHz_ComponentPrescalerDefaultConfig(rcc_component_config_t* const componentPrescalerConfig);

/**
 * @brief Sets prescaler for 72MHz
 * @param prescalerConfig Pointer to @ref rcc_prescaler_config_t "Component Prescaler Configuration Structure"
 */
void RCC_72MHz_PrescalerDefaultConfig(rcc_prescaler_config_t* const prescalerConfig);

/**
 * @brief Sets RCC Configuration 72MHz
 * @param rccConfig Pointer to @ref rcc_config_t "RCC Configuration Structure"
 */
void RCC_72MHz_LoadDefaultConfig(rcc_config_t* const rccConfig);

/*---------------------------------------------- Helper APIs ----------------------------------------------*/
/**
 * @brief Shortcut Function to set Clock Frequency to 72MHz
 */
__STATIC_FORCEINLINE driver_status_t RCC_Config_72MHz(void)
{
	rcc_config_t rcc72MHzConfig = {0};
	RCC_72MHz_LoadDefaultConfig(&rcc72MHzConfig);
	driver_status_t status = RCC_Config(&rcc72MHzConfig);
	ASSERT_DRIVER_STATUS(status);
	return status;
}

/** @} */ // RCC_03_Driver_06_MainConfig

/** @} */ // RCC_03_Driver

#ifdef _OLD_RCC__
/*---------------------------------------------- Header File ----------------------------------------------*/
#include "rcc_config.h"

/*---------------------------------------------- System Frequency Tracker ----------------------------------------------*/
extern rcc_clk_freq_t __systemFrequency__;

/*---------------------------------------------- Driver APIs ----------------------------------------------*/
/**
 * @brief RCC Flash Configuration
 * @param flash Flash Configuration Structure `rcc_flash_config_t` 
 * @param reg Pointer to `FLASH->ACR.REG`
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_ConfigFlash(const rcc_flash_config_t flash, uint32_t* reg);

/**
 * @brief RCC PLL Configuration
 * @param pllConfig  PLL Configuration Structure
 * @param reg Pointer to `RCC->CFGR.REG`
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_PLLConfig(const rcc_pll_config_t pllConfig, uint32_t* reg);

/**
 * @brief RCC Bus Prescaler Configuration
 * @param busConfig Bus Configuration Structure 
 * @param reg Pointer to `RCC->CFGR.REG`
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success 
 */
driver_status_t RCC_BusConfig(const rcc_bus_config_t busPrescalerConfig, uint32_t* reg);

/**
 * @brief RCC Component Configuration - ADC, USB
 * @param componentPrescalerConfig Component Prescaler Configuration Structure  
 * @param reg Pointer to `RCC->CFGR.REG`
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success 
 */
driver_status_t RCC_ComponentConfig(const rcc_component_config_t componentPrescalerConfig, uint32_t* reg);

/**
 * @brief RCC Clock Configuration
 * @param rccConfig RCC Clock Configuration Structure 
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_Config(const rcc_config_t* rccConfig);



/**
 * @brief Retrieves RCC Core Clock Frequency in Hz
 * @note This is the clock which is being fed to AHB Prescaler 
 */
__STATIC_FORCEINLINE _rcc_freq_t RCC_CoreClockFreq_Get(void)
{
	return (__systemFrequency__.Core); 
}

/**
 * @brief Retrieves RCC AHB Clock Frequency in Hz
 * @note This is the clock which is being fed to APB1/APB2 Prescaler 
 */
__STATIC_FORCEINLINE _rcc_freq_t RCC_AHBClockFreq_Get(void)
{
	return (__systemFrequency__.AHB);
}

/**
 * @brief Retrieves RCC APB1 Clock Frequency in Hz
 * @note This is the clock which is being fed to APB1 Peripherals 
 */
__STATIC_FORCEINLINE _rcc_freq_t RCC_APB1ClockFreq_Get(void)
{
	return (__systemFrequency__.APB1);
}

/**
 * @brief Retrieves RCC APB2 Clock Frequency in Hz
 * @note This is the clock which is being fed to APB2 Peripherals 
 */
__STATIC_FORCEINLINE _rcc_freq_t RCC_APB2ClockFreq_Get(void)
{
	return (__systemFrequency__.APB2);
}

#endif /* _OLD_RCC__ */

// C++ Safeguard
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_H_ */