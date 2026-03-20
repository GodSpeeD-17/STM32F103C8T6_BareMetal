/**
 * @file	rcc.h
 * @author	Shrey Shah
 * @brief	RCC Driver Public Interface
 * @version	v2.2
 * @date	20-03-2026
 *
 * @details
 * This header exposes the public RCC driver API used by the rest of the framework.
 * The driver is responsible for:
 * - System clock tree configuration.
 * - Flash wait-state and prefetch configuration required for clock changes.
 * - AHB/APB/ADC/USB prescaler configuration.
 * - Bus clock enable and peripheral reset helpers.
 * - Runtime clock-frequency queries.
 */

// Header Guards
#ifndef RCC_H_
#define RCC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*---------------------------------------------- Includes ----------------------------------------------*/
#include "rcc_ll.h"

/**
 * @addtogroup RCC_03_Driver
 * @{
 */

/*---------------------------------------------- RCC Frequency Definitions ----------------------------------------------*/
/**
 * @brief	RCC Frequency Types and Limits
 * @defgroup RCC_03_Driver_01_Frequency RCC Driver Frequency Types and Macros
 * @ingroup	RCC_03_Driver
 * @details
 * - These constants describe the nominal frequencies and limits assumed by the framework.
 * - The base oscillator values reflect the STM32F103C8T6 Blue Pill target currently used.
 * @{
 */

/** @brief RCC frequency unit type @typedef _rcc_freq_t */
typedef uint32_t									_rcc_freq_t;

/** @brief 1 kHz frequency constant @def _RCC_FREQ_1kHz */
#define _RCC_FREQ_1kHz							((_rcc_freq_t) 1000UL)
/** @brief 1 MHz frequency constant @def _RCC_FREQ_1MHz */
#define _RCC_FREQ_1MHz							((_rcc_freq_t) 1000000UL)
/** @brief Internal high-speed oscillator frequency @def _RCC_HSI_FREQ */
#define _RCC_HSI_FREQ							((_rcc_freq_t) 8000000UL)
/** @brief External high-speed oscillator frequency @def _RCC_HSE_FREQ */
#define _RCC_HSE_FREQ							((_rcc_freq_t) 8000000UL)
/** @brief Maximum allowed system clock frequency @def _RCC_SYSCLK_MAX_FREQ */
#define _RCC_SYSCLK_MAX_FREQ						((_rcc_freq_t) 72000000UL)
/** @brief Maximum allowed APB1 clock frequency @def _RCC_PCLK1_MAX_FREQ */
#define _RCC_PCLK1_MAX_FREQ						((_rcc_freq_t) 36000000UL)
/** @brief Maximum allowed APB2 clock frequency @def _RCC_PCLK2_MAX_FREQ */
#define _RCC_PCLK2_MAX_FREQ						((_rcc_freq_t) 72000000UL)
/** @brief Maximum allowed ADC clock frequency @def _RCC_ADCCLK_MAX_FREQ */
#define _RCC_ADCCLK_MAX_FREQ						((_rcc_freq_t) 14000000UL)
/** @brief Required USB clock target @def _RCC_USBCLK_TARGET_FREQ */
#define _RCC_USBCLK_TARGET_FREQ					((_rcc_freq_t) 48000000UL)

/** @} */ // RCC_03_Driver_01_Frequency

/*---------------------------------------------- RCC Flash Configuration ----------------------------------------------*/
/**
 * @brief	RCC Flash Configuration Types
 * @defgroup RCC_03_Driver_02_Flash RCC Driver Flash Configuration
 * @ingroup	RCC_03_Driver
 * @details
 * - Flash wait-state configuration must be applied before increasing SYSCLK.
 * - Prefetch is typically enabled for higher frequency operation on STM32F1.
 * @{
 */

/** @brief Flash latency type @typedef rcc_flash_latency_t */
typedef uint8_t									rcc_flash_latency_t;
/** @brief Zero wait states @def RCC_FLASH_LATENCY_0 */
#define RCC_FLASH_LATENCY_0						((rcc_flash_latency_t) 0x00)
/** @brief One wait state @def RCC_FLASH_LATENCY_1 */
#define RCC_FLASH_LATENCY_1						((rcc_flash_latency_t) 0x01)
/** @brief Two wait states @def RCC_FLASH_LATENCY_2 */
#define RCC_FLASH_LATENCY_2						((rcc_flash_latency_t) 0x02)

/** @brief Flash prefetch configuration type @typedef rcc_flash_prefetch_t */
typedef uint8_t									rcc_flash_prefetch_t;
/** @brief Flash prefetch disable @def RCC_FLASH_PREFETCH_DISABLE */
#define RCC_FLASH_PREFETCH_DISABLE					((rcc_flash_prefetch_t) 0x00)
/** @brief Flash prefetch enable @def RCC_FLASH_PREFETCH_ENABLE */
#define RCC_FLASH_PREFETCH_ENABLE					((rcc_flash_prefetch_t) 0x01)

/**
 * @brief	RCC flash configuration descriptor
 * @typedef	rcc_flash_config_t
 */
typedef struct
{
	/** @brief Flash wait-state configuration */
	rcc_flash_latency_t		latency;
	/** @brief Flash prefetch buffer configuration */
	rcc_flash_prefetch_t	prefetch;
} rcc_flash_config_t;

/** @} */ // RCC_03_Driver_02_Flash

/*---------------------------------------------- RCC System Clock ----------------------------------------------*/
/**
 * @brief	RCC System Clock and PLL Types
 * @defgroup RCC_03_Driver_03_SystemClock RCC Driver System Clock Configuration
 * @ingroup	RCC_03_Driver
 * @details
 * - These types model the public clock-tree configuration used by the driver.
 * - They are intentionally driver-level abstractions rather than raw register encodings.
 * @{
 */

/** @brief System clock source selector type @typedef rcc_system_clock_t */
typedef uint8_t									rcc_system_clock_t;
/** @brief HSI selected as SYSCLK @def RCC_SYS_CLK_HSI */
#define RCC_SYS_CLK_HSI							((rcc_system_clock_t) 0x00)
/** @brief HSE selected as SYSCLK @def RCC_SYS_CLK_HSE */
#define RCC_SYS_CLK_HSE							((rcc_system_clock_t) 0x01)
/** @brief PLL selected as SYSCLK @def RCC_SYS_CLK_PLL */
#define RCC_SYS_CLK_PLL							((rcc_system_clock_t) 0x02)

/** @brief PLL source type @typedef rcc_pll_src_t */
typedef uint8_t									rcc_pll_src_t;
/** @brief HSI/2 selected as PLL input @def RCC_PLL_SRC_HSI */
#define RCC_PLL_SRC_HSI							((rcc_pll_src_t) 0x00)
/** @brief HSE selected as PLL input @def RCC_PLL_SRC_HSE */
#define RCC_PLL_SRC_HSE							((rcc_pll_src_t) 0x01)

/** @brief PLL source prescaler type @typedef rcc_pll_src_psc_t */
typedef uint8_t									rcc_pll_src_psc_t;
/** @brief Fixed HSI divide-by-2 PLL input @def RCC_PLL_SRC_HSI_DIV_2 */
#define RCC_PLL_SRC_HSI_DIV_2					((rcc_pll_src_psc_t) 0x00)
/** @brief HSE divide-by-1 PLL input @def RCC_PLL_SRC_HSE_DIV_1 */
#define RCC_PLL_SRC_HSE_DIV_1					((rcc_pll_src_psc_t) 0x01)
/** @brief HSE divide-by-2 PLL input @def RCC_PLL_SRC_HSE_DIV_2 */
#define RCC_PLL_SRC_HSE_DIV_2					((rcc_pll_src_psc_t) 0x02)

/** @brief PLL multiplication factor type @typedef rcc_pll_mul_t */
typedef uint8_t									rcc_pll_mul_t;
/** @brief PLL x2 multiplication factor @def RCC_PLL_MUL_2 */
#define RCC_PLL_MUL_2							((rcc_pll_mul_t) 2U)
/** @brief PLL x3 multiplication factor @def RCC_PLL_MUL_3 */
#define RCC_PLL_MUL_3							((rcc_pll_mul_t) 3U)
/** @brief PLL x4 multiplication factor @def RCC_PLL_MUL_4 */
#define RCC_PLL_MUL_4							((rcc_pll_mul_t) 4U)
/** @brief PLL x5 multiplication factor @def RCC_PLL_MUL_5 */
#define RCC_PLL_MUL_5							((rcc_pll_mul_t) 5U)
/** @brief PLL x6 multiplication factor @def RCC_PLL_MUL_6 */
#define RCC_PLL_MUL_6							((rcc_pll_mul_t) 6U)
/** @brief PLL x7 multiplication factor @def RCC_PLL_MUL_7 */
#define RCC_PLL_MUL_7							((rcc_pll_mul_t) 7U)
/** @brief PLL x8 multiplication factor @def RCC_PLL_MUL_8 */
#define RCC_PLL_MUL_8							((rcc_pll_mul_t) 8U)
/** @brief PLL x9 multiplication factor @def RCC_PLL_MUL_9 */
#define RCC_PLL_MUL_9							((rcc_pll_mul_t) 9U)
/** @brief PLL x10 multiplication factor @def RCC_PLL_MUL_10 */
#define RCC_PLL_MUL_10							((rcc_pll_mul_t) 10U)
/** @brief PLL x11 multiplication factor @def RCC_PLL_MUL_11 */
#define RCC_PLL_MUL_11							((rcc_pll_mul_t) 11U)
/** @brief PLL x12 multiplication factor @def RCC_PLL_MUL_12 */
#define RCC_PLL_MUL_12							((rcc_pll_mul_t) 12U)
/** @brief PLL x13 multiplication factor @def RCC_PLL_MUL_13 */
#define RCC_PLL_MUL_13							((rcc_pll_mul_t) 13U)
/** @brief PLL x14 multiplication factor @def RCC_PLL_MUL_14 */
#define RCC_PLL_MUL_14							((rcc_pll_mul_t) 14U)
/** @brief PLL x15 multiplication factor @def RCC_PLL_MUL_15 */
#define RCC_PLL_MUL_15							((rcc_pll_mul_t) 15U)
/** @brief PLL x16 multiplication factor @def RCC_PLL_MUL_16 */
#define RCC_PLL_MUL_16							((rcc_pll_mul_t) 16U)

/**
 * @brief	PLL configuration descriptor
 * @typedef	rcc_pll_config_t
 */
typedef struct
{
	/** @brief PLL multiplication factor */
	rcc_pll_mul_t				multiplication_factor;
	/** @brief PLL input source */
	rcc_pll_src_t				source;
	/** @brief PLL source prescaler */
	rcc_pll_src_psc_t		source_prescaler;
} rcc_pll_config_t;

/**
 * @brief	System clock configuration descriptor
 * @typedef	rcc_sys_clk_config_t
 */
typedef struct
{
	/** @brief Requested system clock source */
	rcc_system_clock_t		clk_src;
	/** @brief PLL descriptor used when SYSCLK source is PLL */
	rcc_pll_config_t		pll;
} rcc_sys_clk_config_t;

/** @} */ // RCC_03_Driver_03_SystemClock

/*---------------------------------------------- RCC Prescalers ----------------------------------------------*/
/**
 * @brief	RCC Bus and Component Prescaler Types
 * @defgroup RCC_03_Driver_04_Prescalers RCC Driver Prescaler Configuration
 * @ingroup	RCC_03_Driver
 * @details
 * - The public API exposes divider values instead of raw register fields.
 * - The RCC driver translates these values internally to hardware encodings.
 * @{
 */

/** @brief RCC bus identifier type @typedef rcc_bus_t */
typedef uint8_t									rcc_bus_t;
/** @brief AHB bus identifier @def RCC_AHB_BUS */
#define RCC_AHB_BUS								((rcc_bus_t) 0x00)
/** @brief APB1 bus identifier @def RCC_APB1_BUS */
#define RCC_APB1_BUS							((rcc_bus_t) 0x01)
/** @brief APB2 bus identifier @def RCC_APB2_BUS */
#define RCC_APB2_BUS							((rcc_bus_t) 0x02)

/** @brief Bus prescaler type @typedef rcc_bus_prescaler_t */
typedef uint16_t								rcc_bus_prescaler_t;
/** @brief AHB divider 1 @def RCC_AHB_DIV_1 */
#define RCC_AHB_DIV_1							((rcc_bus_prescaler_t) 1U)
/** @brief AHB divider 2 @def RCC_AHB_DIV_2 */
#define RCC_AHB_DIV_2							((rcc_bus_prescaler_t) 2U)
/** @brief AHB divider 4 @def RCC_AHB_DIV_4 */
#define RCC_AHB_DIV_4							((rcc_bus_prescaler_t) 4U)
/** @brief AHB divider 8 @def RCC_AHB_DIV_8 */
#define RCC_AHB_DIV_8							((rcc_bus_prescaler_t) 8U)
/** @brief AHB divider 16 @def RCC_AHB_DIV_16 */
#define RCC_AHB_DIV_16							((rcc_bus_prescaler_t) 16U)
/** @brief AHB divider 64 @def RCC_AHB_DIV_64 */
#define RCC_AHB_DIV_64							((rcc_bus_prescaler_t) 64U)
/** @brief AHB divider 128 @def RCC_AHB_DIV_128 */
#define RCC_AHB_DIV_128							((rcc_bus_prescaler_t) 128U)
/** @brief AHB divider 256 @def RCC_AHB_DIV_256 */
#define RCC_AHB_DIV_256							((rcc_bus_prescaler_t) 256U)
/** @brief AHB divider 512 @def RCC_AHB_DIV_512 */
#define RCC_AHB_DIV_512							((rcc_bus_prescaler_t) 512U)

/** @brief APB1 divider 1 @def RCC_APB1_DIV_1 */
#define RCC_APB1_DIV_1							((rcc_bus_prescaler_t) 1U)
/** @brief APB1 divider 2 @def RCC_APB1_DIV_2 */
#define RCC_APB1_DIV_2							((rcc_bus_prescaler_t) 2U)
/** @brief APB1 divider 4 @def RCC_APB1_DIV_4 */
#define RCC_APB1_DIV_4							((rcc_bus_prescaler_t) 4U)
/** @brief APB1 divider 8 @def RCC_APB1_DIV_8 */
#define RCC_APB1_DIV_8							((rcc_bus_prescaler_t) 8U)
/** @brief APB1 divider 16 @def RCC_APB1_DIV_16 */
#define RCC_APB1_DIV_16							((rcc_bus_prescaler_t) 16U)

/** @brief APB2 divider 1 @def RCC_APB2_DIV_1 */
#define RCC_APB2_DIV_1							((rcc_bus_prescaler_t) 1U)
/** @brief APB2 divider 2 @def RCC_APB2_DIV_2 */
#define RCC_APB2_DIV_2							((rcc_bus_prescaler_t) 2U)
/** @brief APB2 divider 4 @def RCC_APB2_DIV_4 */
#define RCC_APB2_DIV_4							((rcc_bus_prescaler_t) 4U)
/** @brief APB2 divider 8 @def RCC_APB2_DIV_8 */
#define RCC_APB2_DIV_8							((rcc_bus_prescaler_t) 8U)
/** @brief APB2 divider 16 @def RCC_APB2_DIV_16 */
#define RCC_APB2_DIV_16							((rcc_bus_prescaler_t) 16U)

/**
 * @brief	Bus prescaler descriptor
 * @typedef	rcc_bus_config_t
 */
typedef struct
{
	/** @brief AHB prescaler divider */
	rcc_bus_prescaler_t		AHB;
	/** @brief APB1 prescaler divider */
	rcc_bus_prescaler_t		APB1;
	/** @brief APB2 prescaler divider */
	rcc_bus_prescaler_t		APB2;
} rcc_bus_config_t;

/** @brief Component prescaler type @typedef rcc_component_prescaler_t */
typedef uint8_t									rcc_component_prescaler_t;
/** @brief ADC divider 2 @def RCC_ADC_DIV_2 */
#define RCC_ADC_DIV_2							((rcc_component_prescaler_t) 2U)
/** @brief ADC divider 4 @def RCC_ADC_DIV_4 */
#define RCC_ADC_DIV_4							((rcc_component_prescaler_t) 4U)
/** @brief ADC divider 6 @def RCC_ADC_DIV_6 */
#define RCC_ADC_DIV_6							((rcc_component_prescaler_t) 6U)
/** @brief ADC divider 8 @def RCC_ADC_DIV_8 */
#define RCC_ADC_DIV_8							((rcc_component_prescaler_t) 8U)

/** @brief USB clock = PLL/1.5 selector @def RCC_USB_DIV_1_5 */
#define RCC_USB_DIV_1_5							((rcc_component_prescaler_t) 0x00)
/** @brief USB clock = PLL/1 selector @def RCC_USB_DIV_1 */
#define RCC_USB_DIV_1							((rcc_component_prescaler_t) 0x01)

/**
 * @brief	Component prescaler descriptor
 * @typedef	rcc_component_config_t
 */
typedef struct
{
	/** @brief ADC prescaler divider */
	rcc_component_prescaler_t	ADC;
	/** @brief USB prescaler selector */
	rcc_component_prescaler_t	USB;
} rcc_component_config_t;

/**
 * @brief	Aggregate prescaler descriptor
 * @typedef	rcc_prescaler_config_t
 */
typedef struct
{
	/** @brief Bus prescaler configuration */
	rcc_bus_config_t			bus;
	/** @brief Component prescaler configuration */
	rcc_component_config_t	component;
} rcc_prescaler_config_t;

/** @} */ // RCC_03_Driver_04_Prescalers

/*---------------------------------------------- RCC Aggregate Configuration ----------------------------------------------*/
/**
 * @brief	RCC Aggregate Configuration Type
 * @defgroup RCC_03_Driver_05_Config RCC Driver Aggregate Configuration
 * @ingroup	RCC_03_Driver
 * @{
 */

/**
 * @brief	Complete RCC configuration descriptor
 * @typedef	rcc_config_t
 */
typedef struct
{
	/** @brief Flash configuration */
	rcc_flash_config_t		flash;
	/** @brief System clock configuration */
	rcc_sys_clk_config_t		system;
	/** @brief Prescaler configuration */
	rcc_prescaler_config_t	prescaler;
} rcc_config_t;

/** @} */ // RCC_03_Driver_05_Config

/*---------------------------------------------- RCC Clock Gate and Reset APIs ----------------------------------------------*/
/**
 * @brief	RCC Clock Gate and Reset APIs
 * @defgroup RCC_03_Driver_06_ClockReset RCC Driver Clock Enable and Reset APIs
 * @ingroup	RCC_03_Driver
 * @details
 * - These APIs intentionally accept raw bus masks rather than a framework-owned peripheral ID enum.
 * - The caller chooses the bit-mask directly from the MCU register definitions.
 * - This keeps the RCC driver generic and avoids maintaining another peripheral mapping layer.
 * @{
 */

/**
 * @brief	Enables AHB peripheral clock gates
 * @param[in] clockMask	AHB enable mask from RCC register definitions
 * @returns	Driver operation status
 */
driver_status_t RCC_AHB_ClockEnable(const uint32_t clockMask);

/**
 * @brief	Disables AHB peripheral clock gates
 * @param[in] clockMask	AHB enable mask from RCC register definitions
 * @returns	Driver operation status
 */
driver_status_t RCC_AHB_ClockDisable(const uint32_t clockMask);

/**
 * @brief	Enables APB2 peripheral clock gates
 * @param[in] clockMask	APB2 enable mask from RCC register definitions
 * @returns	Driver operation status
 */
driver_status_t RCC_APB2_ClockEnable(const uint32_t clockMask);

/**
 * @brief	Disables APB2 peripheral clock gates
 * @param[in] clockMask	APB2 enable mask from RCC register definitions
 * @returns	Driver operation status
 */
driver_status_t RCC_APB2_ClockDisable(const uint32_t clockMask);

/**
 * @brief	Enables APB1 peripheral clock gates
 * @param[in] clockMask	APB1 enable mask from RCC register definitions
 * @returns	Driver operation status
 */
driver_status_t RCC_APB1_ClockEnable(const uint32_t clockMask);

/**
 * @brief	Disables APB1 peripheral clock gates
 * @param[in] clockMask	APB1 enable mask from RCC register definitions
 * @returns	Driver operation status
 */
driver_status_t RCC_APB1_ClockDisable(const uint32_t clockMask);

/**
 * @brief	Pulses APB2 peripheral reset bits
 * @param[in] resetMask	APB2 reset mask from RCC register definitions
 * @returns	Driver operation status
 */
driver_status_t RCC_APB2_ResetPulse(const uint32_t resetMask);

/**
 * @brief	Pulses APB1 peripheral reset bits
 * @param[in] resetMask	APB1 reset mask from RCC register definitions
 * @returns	Driver operation status
 */
driver_status_t RCC_APB1_ResetPulse(const uint32_t resetMask);

/** @} */ // RCC_03_Driver_06_ClockReset

/*---------------------------------------------- RCC Driver APIs ----------------------------------------------*/
/**
 * @brief	RCC Driver Functional APIs
 * @defgroup RCC_03_Driver_07_API RCC Driver Functional APIs
 * @ingroup	RCC_03_Driver
 * @{
 */

/**
 * @brief	Validates a complete RCC configuration descriptor
 * @param[in] cfg	Pointer to @ref rcc_config_t
 * @returns	Driver validation status
 */
driver_status_t RCC_ValidateConfig(const rcc_config_t* cfg);

/**
 * @brief	Applies flash latency and prefetch configuration
 * @param[in] flash	Pointer to @ref rcc_flash_config_t
 * @returns	Driver operation status
 */
driver_status_t RCC_ConfigFlash(const rcc_flash_config_t* flash);

/**
 * @brief	Applies AHB/APB bus prescaler configuration
 * @param[in] busCfg	Pointer to @ref rcc_bus_config_t
 * @returns	Driver operation status
 */
driver_status_t RCC_ConfigBusPrescaler(const rcc_bus_config_t* busCfg);

/**
 * @brief	Applies ADC and USB prescaler configuration
 * @param[in] componentCfg	Pointer to @ref rcc_component_config_t
 * @returns	Driver operation status
 */
driver_status_t RCC_ConfigComponentPrescaler(const rcc_component_config_t* componentCfg);

/**
 * @brief	Applies a complete RCC configuration sequence
 * @param[in] cfg	Pointer to @ref rcc_config_t
 * @returns	Driver operation status
 */
driver_status_t RCC_Config(const rcc_config_t* cfg);

/**
 * @brief	Loads the framework default 72 MHz clock configuration into a descriptor
 * @param[out] cfg	Pointer to @ref rcc_config_t
 */
void RCC_72MHz_LoadDefaultConfig(rcc_config_t* cfg);

/**
 * @brief	Applies the framework default 72 MHz clock configuration
 * @returns	Driver operation status
 */
driver_status_t RCC_Config_72MHz(void);

/**
 * @brief	Returns the active system clock source from hardware
 * @returns	Current system clock source
 */
rcc_system_clock_t RCC_GetSysClkSrc(void);

/**
 * @brief	Returns the active PLL source from hardware
 * @returns	Current PLL source selection
 */
rcc_pll_src_t RCC_GetPLLSource(void);

/**
 * @brief	Returns the active PLL source prescaler from hardware
 * @returns	Current PLL source prescaler
 */
rcc_pll_src_psc_t RCC_GetPLLSourcePrescaler(void);

/**
 * @brief	Returns the active PLL multiplication factor from hardware
 * @returns	Current PLL multiplication factor
 */
rcc_pll_mul_t RCC_GetPLLMultiplier(void);

/**
 * @brief	Returns the current core clock frequency before the AHB prescaler
 * @returns	Core clock frequency in Hz
 */
_rcc_freq_t RCC_GetCoreClockFreq(void);

/**
 * @brief	Returns the current divider configured for a bus
 * @param[in] bus	Target bus identifier
 * @returns	Configured bus prescaler divider
 */
rcc_bus_prescaler_t RCC_GetBusPrescaler(const rcc_bus_t bus);

/**
 * @brief	Returns the current clock frequency for a bus
 * @param[in] bus	Target bus identifier
 * @returns	Bus clock frequency in Hz
 */
_rcc_freq_t RCC_GetBusFreq(const rcc_bus_t bus);

/**
 * @brief	Returns the current ADC clock frequency
 * @returns	ADC clock frequency in Hz
 */
_rcc_freq_t RCC_GetADCFreq(void);

/**
 * @brief	Returns the current USB clock frequency
 * @returns	USB clock frequency in Hz
 */
_rcc_freq_t RCC_GetUSBFreq(void);

/** @} */ // RCC_03_Driver_07_API

/*---------------------------------------------- RCC Legacy Compatibility Wrappers ----------------------------------------------*/
/**
 * @brief	Legacy inline compatibility wrappers
 * @defgroup RCC_03_Driver_08_Legacy RCC Driver Legacy Compatibility Wrappers
 * @ingroup	RCC_03_Driver
 * @details
 * - These wrappers preserve older call sites while routing everything through the newer API.
 * - New code should prefer @ref RCC_GetBusFreq or @ref RCC_GetCoreClockFreq directly.
 * @{
 */

/**
 * @brief	Legacy wrapper for AHB bus frequency retrieval
 * @returns	AHB bus frequency in Hz
 */
__STATIC_FORCEINLINE _rcc_freq_t RCC_Get_AHBClock(void)
{
	return RCC_GetBusFreq(RCC_AHB_BUS);
}

/**
 * @brief	Legacy wrapper for APB1 bus frequency retrieval
 * @returns	APB1 bus frequency in Hz
 */
__STATIC_FORCEINLINE _rcc_freq_t RCC_Get_APB1Clock(void)
{
	return RCC_GetBusFreq(RCC_APB1_BUS);
}

/**
 * @brief	Legacy wrapper for APB2 bus frequency retrieval
 * @returns	APB2 bus frequency in Hz
 */
__STATIC_FORCEINLINE _rcc_freq_t RCC_Get_APB2Clock(void)
{
	return RCC_GetBusFreq(RCC_APB2_BUS);
}

/**
 * @brief	Legacy wrapper for core clock frequency retrieval
 * @returns	Core clock frequency in Hz
 */
__STATIC_FORCEINLINE _rcc_freq_t RCC_CoreClockFreq_Get(void)
{
	return RCC_GetCoreClockFreq();
}

/**
 * @brief	Legacy wrapper for AHB clock frequency retrieval
 * @returns	AHB bus frequency in Hz
 */
__STATIC_FORCEINLINE _rcc_freq_t RCC_AHBClockFreq_Get(void)
{
	return RCC_Get_AHBClock();
}

/**
 * @brief	Legacy wrapper for APB1 clock frequency retrieval
 * @returns	APB1 bus frequency in Hz
 */
__STATIC_FORCEINLINE _rcc_freq_t RCC_APB1ClockFreq_Get(void)
{
	return RCC_Get_APB1Clock();
}

/**
 * @brief	Legacy wrapper for APB2 clock frequency retrieval
 * @returns	APB2 bus frequency in Hz
 */
__STATIC_FORCEINLINE _rcc_freq_t RCC_APB2ClockFreq_Get(void)
{
	return RCC_Get_APB2Clock();
}

/** @} */ // RCC_03_Driver_08_Legacy

/** @} */ // RCC_03_Driver

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_H_ */
