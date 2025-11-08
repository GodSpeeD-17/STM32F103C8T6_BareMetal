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
	rcc_flash_latency_t latency;
	
	/** 
	 * @brief Flash prefetch buffer control
	 * @details
	 * - Use @ref RCC_FLASH_PREFETCH_DISABLE to disable prefetch
	 * - Use @ref RCC_FLASH_PREFETCH_ENABLE to enable prefetch (recommended)
	 */
	rcc_flash_prefetch_t prefetch;
} rcc_flash_config_t;

/** @} */ // RCC_03_Driver_01_FlashConfig

/*---------------------------------------------- RCC Bus Prescaler ----------------------------------------------*/
/**
 * @brief    Driver Bus Prescaler Configuration Structure  
 * @defgroup RCC_03_Driver_02_BusPrescalerConfig Driver Bus Prescaler Configuration
 * @ingroup  RCC_03_Driver
 * @details
 * - Configuration structure for AHB, APB1, and APB2 bus prescalers
 * - Each bus has specific maximum frequency limits
 * - Used during system clock configuration
 *
 * @see Reference Manual RM0008 - Section 7.3.2 Clock configuration register (RCC_CFGR)
 * @{
 */

/** @brief AHB bus prescaler type definition @typedef rcc_ahb_prescaler_t */
typedef uint8_t rcc_ahb_prescaler_t;

/** @brief AHB division by 1 (no prescaling) @def RCC_AHB_DIV_1 */
#define RCC_AHB_DIV_1 							((rcc_ahb_prescaler_t) 0x00)
/** @brief AHB division by 2 @def RCC_AHB_DIV_2 */
#define RCC_AHB_DIV_2 							((rcc_ahb_prescaler_t) 0x01)
/** @brief AHB division by 4 @def RCC_AHB_DIV_4 */
#define RCC_AHB_DIV_4 							((rcc_ahb_prescaler_t) 0x02)
/** @brief AHB division by 8 @def RCC_AHB_DIV_8 */
#define RCC_AHB_DIV_8 							((rcc_ahb_prescaler_t) 0x03)
/** @brief AHB division by 16 @def RCC_AHB_DIV_16 */
#define RCC_AHB_DIV_16 							((rcc_ahb_prescaler_t) 0x04)
/** @brief AHB division by 64 @def RCC_AHB_DIV_64 */
#define RCC_AHB_DIV_64 							((rcc_ahb_prescaler_t) 0x05)
/** @brief AHB division by 128 @def RCC_AHB_DIV_128 */
#define RCC_AHB_DIV_128 						((rcc_ahb_prescaler_t) 0x06)
/** @brief AHB division by 256 @def RCC_AHB_DIV_256 */
#define RCC_AHB_DIV_256 						((rcc_ahb_prescaler_t) 0x07)
/** @brief AHB division by 512 @def RCC_AHB_DIV_512 */
#define RCC_AHB_DIV_512 						((rcc_ahb_prescaler_t) 0x08)

/** @brief APB1 bus prescaler type definition @typedef rcc_apb1_prescaler_t */
typedef uint8_t rcc_apb1_prescaler_t;

/** @brief APB1 division by 1 (no prescaling) @def RCC_APB1_DIV_1 */
#define RCC_APB1_DIV_1 							((rcc_apb1_prescaler_t) 0x00)
/** @brief APB1 division by 2 @def RCC_APB1_DIV_2 */
#define RCC_APB1_DIV_2 							((rcc_apb1_prescaler_t) 0x01)
/** @brief APB1 division by 4 @def RCC_APB1_DIV_4 */
#define RCC_APB1_DIV_4 							((rcc_apb1_prescaler_t) 0x02)
/** @brief APB1 division by 8 @def RCC_APB1_DIV_8 */
#define RCC_APB1_DIV_8 							((rcc_apb1_prescaler_t) 0x03)
/** @brief APB1 division by 16 @def RCC_APB1_DIV_16 */
#define RCC_APB1_DIV_16 						((rcc_apb1_prescaler_t) 0x04)

/** @brief APB2 bus prescaler type definition @typedef rcc_apb2_prescaler_t */
typedef uint8_t rcc_apb2_prescaler_t;

/** @brief APB2 division by 1 (no prescaling) @def RCC_APB2_DIV_1 */
#define RCC_APB2_DIV_1 							((rcc_apb2_prescaler_t) 0x00)
/** @brief APB2 division by 2 @def RCC_APB2_DIV_2 */
#define RCC_APB2_DIV_2 							((rcc_apb2_prescaler_t) 0x01)
/** @brief APB2 division by 4 @def RCC_APB2_DIV_4 */
#define RCC_APB2_DIV_4 							((rcc_apb2_prescaler_t) 0x02)
/** @brief APB2 division by 8 @def RCC_APB2_DIV_8 */
#define RCC_APB2_DIV_8 							((rcc_apb2_prescaler_t) 0x03)
/** @brief APB2 division by 16 @def RCC_APB2_DIV_16 */
#define RCC_APB2_DIV_16 						((rcc_apb2_prescaler_t) 0x04)

/**
 * @brief Bus Prescaler Configuration Structure
 * @typedef rcc_bus_prescaler_config_t
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
	rcc_ahb_prescaler_t AHB: 4;
	
	/**
	 * @brief APB1 Bus Prescaler
	 * @details  
	 * - APB1 Prescaler Values Refer @ref RCC_APB1_DIV_1 "RCC_APB1_DIV_*"
	 * - Max frequency = 36MHz
	 * - APB1 clock = AHB clock / APB1 prescaler
	 */
	rcc_apb1_prescaler_t APB1: 3;
	
	/**
	 * @brief APB2 Bus Prescaler
	 * @details
	 * - APB2 Prescaler Values Refer @ref RCC_APB2_DIV_1 "RCC_APB2_DIV_*"
	 * - Max frequency = 72MHz  
	 * - APB2 clock = AHB clock / APB2 prescaler
	 */
	rcc_apb2_prescaler_t APB2: 3;
} rcc_bus_prescaler_config_t;

/**
 * @brief Convert driver AHB prescaler to low-level hardware value
 * @param[in] prescaler Driver AHB prescaler value (@ref RCC_AHB_DIV_1 "RCC_AHB_DIV_*")
 * @returns Low-level AHB prescaler value for hardware registers
 */
__STATIC_FORCEINLINE _rcc_bus_prescaler_t RCC_DriverToLL_AHBPrescaler(const rcc_ahb_prescaler_t prescaler)
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
__STATIC_FORCEINLINE _rcc_bus_prescaler_t RCC_DriverToLL_APB1Prescaler(const rcc_apb1_prescaler_t prescaler)
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
__STATIC_FORCEINLINE _rcc_bus_prescaler_t RCC_DriverToLL_APB2Prescaler(const rcc_apb2_prescaler_t prescaler)
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

/** @} */ // RCC_03_Driver_02_BusPrescalerConfig


/*---------------------------------------------- RCC PLL ----------------------------------------------*/
/**
 * @brief    Driver PLL Configuration Types and Structure
 * @defgroup RCC_03_Driver_04_PLLConfig Driver PLL Configuration
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
typedef uint8_t rcc_pll_src_t;

/** @brief PLL source HSI (High Speed Internal) @def RCC_PLL_SRC_HSI */
#define RCC_PLL_SRC_HSI 						((rcc_pll_src_t) 0x00)
/** @brief PLL source HSE (High Speed External) @def RCC_PLL_SRC_HSE */
#define RCC_PLL_SRC_HSE 						((rcc_pll_src_t) 0x01)

/** @brief PLL multiplication factor type definition @typedef rcc_pll_mul_t */
typedef uint8_t rcc_pll_mul_t;

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

/** @brief PLL source prescaler type definition @typedef rcc_pll_src_prescaler_t */
typedef uint8_t rcc_pll_src_prescaler_t;

/** @brief HSE division by 1 for PLL input @def RCC_PLL_SRC_HSE_DIV_1 */
#define RCC_PLL_SRC_HSE_DIV_1 					((rcc_pll_src_prescaler_t) 0x00)
/** @brief HSE division by 2 for PLL input @def RCC_PLL_SRC_HSE_DIV_2 */
#define RCC_PLL_SRC_HSE_DIV_2 					((rcc_pll_src_prescaler_t) 0x01)

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
	rcc_pll_mul_t mul_fact: 4;
	
	/**
	 * @brief PLL Source Configuration
	 * @details
	 * - Determines the input source to PLL
	 * - For STM32F1xx, HSI is always divided by 2 before PLL input
	 * - HSE can be used directly or divided by 2
	 */
	rcc_pll_src_t src: 1;
	
	/**
	 * @brief PLL Source Prescaler Configuration
	 * @details
	 * - Determines the prescaler for PLL input source
	 * - For STM32F1xx, HSI does not have prescaler configuration (always /2)
	 * - HSE can be configured with division by 1 or 2
	 * - Only applicable when source is HSE (@ref RCC_PLL_SRC_HSE)
	 */
	rcc_pll_src_prescaler_t src_prescaler: 1;
} rcc_pll_config_t;

/**
 * @brief Convert driver PLL source to low-level hardware value
 * @param[in] src Driver PLL source value (@ref RCC_PLL_SRC_HSI "RCC_PLL_SRC_*")
 * @returns Low-level PLL source value for hardware registers
 */
__STATIC_FORCEINLINE _rcc_pll_src_t RCC_DriverToLL_PLLSource(const rcc_pll_src_t src)
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
__STATIC_FORCEINLINE _rcc_pll_mul_t __RCC_DriverToLL_PLLMultiplication(const rcc_pll_mul_t mul)
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
__STATIC_FORCEINLINE _rcc_pll_src_prescaler_t __RCC_DriverToLL_PLLSourcePrescaler(const rcc_pll_src_prescaler_t prescaler)
{
    switch(prescaler)
	{
        case RCC_PLL_SRC_HSE_DIV_1: return _RCC_PLL_SRC_HSE_DIV_1;
        case RCC_PLL_SRC_HSE_DIV_2: return _RCC_PLL_SRC_HSE_DIV_2;
        default: return _RCC_PLL_SRC_HSE_DIV_1; // Safe fallback
    }
}

/** @} */ // RCC_03_Driver_04_PLLConfig

/** @} */ // RCC_03_Driver

#ifdef _OLD_
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
driver_status_t RCC_FlashConfig(const rcc_flash_config_t flash, uint32_t* reg);

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
driver_status_t RCC_BusConfig(const rcc_bus_prescaler_config_t busPrescalerConfig, uint32_t* reg);

/**
 * @brief RCC Component Configuration - ADC, USB
 * @param componentPrescalerConfig Component Prescaler Configuration Structure  
 * @param reg Pointer to `RCC->CFGR.REG`
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success 
 */
driver_status_t RCC_ComponentConfig(const rcc_component_prescaler_config_t componentPrescalerConfig, uint32_t* reg);

/**
 * @brief RCC Clock Configuration
 * @param rccConfig RCC Clock Configuration Structure 
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_Config(const rcc_config_t* rccConfig);

/**
 * @brief Sets default flash configuration for 72MHz
 * @param flashConfig Pointer to Flash Configuration Structure 
 */
void RCC_72MHz_FlashDefaultConfig(rcc_flash_config_t* flashConfig);

/**
 * @brief PLL Default Configuration for 72MHz
 * @param pllConfig Pointer to PLL Configuration Structure
 */
void RCC_72MHz_PLLDefaultConfig(rcc_pll_config_t* pllConfig);

/**
 * @brief Sets System Configuration for 72MHz Clock
 * @param sysClkConfig Pointer to System Clock
 */
void RCC_72MHz_SystemDefaultConfig(rcc_sys_clk_config_t* sysClkConfig);

/**
 * @brief Sets Bus Prescaler for 72MHz
 * @param busPrescalerConfig Pointer to Bus Prescaler Configuration Structure
 */
void RCC_72MHz_BusPrescalerDefaultConfig(rcc_bus_prescaler_config_t* busPrescalerConfig);

/**
 * @brief Sets Component Prescaler for 72MHz
 * @param componentPrescalerConfig Pointer to Component Prescaler Configuration Structure
 */
void RCC_72MHz_ComponentPrescalerDefaultConfig(rcc_component_prescaler_config_t* componentPrescalerConfig);

/**
 * @brief Sets RCC Configuration 72MHz
 * @param rccConfig RCC Configuration Structure 
 */
void RCC_72MHz_LoadDefaultConfig(rcc_config_t* rccConfig);

/*---------------------------------------------- Helper APIs ----------------------------------------------*/
/**
 * @brief Shortcut Function to set Clock Frequency to 72MHz
 */
__STATIC_FORCEINLINE driver_status_t RCC_Config_72MHz(void)
{
	static rcc_config_t rcc72MHzConfig = {0};
	RCC_72MHz_LoadDefaultConfig(&rcc72MHzConfig);
	driver_status_t status = RCC_Config(&rcc72MHzConfig);
	ASSERT_DRIVER_STATUS(status);
	return status;
}

/**
 * @brief Retrieves RCC Core Clock Frequency in Hz
 * @note This is the clock which is being fed to AHB Prescaler 
 */
__STATIC_FORCEINLINE freq_t RCC_CoreClockFreq_Get(void)
{
	return (__systemFrequency__.Core); 
}

/**
 * @brief Retrieves RCC AHB Clock Frequency in Hz
 * @note This is the clock which is being fed to APB1/APB2 Prescaler 
 */
__STATIC_FORCEINLINE freq_t RCC_AHBClockFreq_Get(void)
{
	return (__systemFrequency__.AHB);
}

/**
 * @brief Retrieves RCC APB1 Clock Frequency in Hz
 * @note This is the clock which is being fed to APB1 Peripherals 
 */
__STATIC_FORCEINLINE freq_t RCC_APB1ClockFreq_Get(void)
{
	return (__systemFrequency__.APB1);
}

/**
 * @brief Retrieves RCC APB2 Clock Frequency in Hz
 * @note This is the clock which is being fed to APB2 Peripherals 
 */
__STATIC_FORCEINLINE freq_t RCC_APB2ClockFreq_Get(void)
{
	return (__systemFrequency__.APB2);
}

#endif /* _OLD_ */

// C++ Safeguard
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_H_ */
