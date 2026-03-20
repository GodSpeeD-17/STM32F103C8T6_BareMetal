/**
 * @file	rcc.h
 * @author	Shrey Shah
 * @brief	RCC Driver Public Interface
 * @version	v2.3
 * @date	20-03-2026
 *
 * @details
 * This header exposes the public RCC driver layer. The driver owns:
 * - clock-tree configuration structures,
 * - validation of requested clock configurations,
 * - orchestration of the RCC LL sequencing,
 * - bus clock gate and reset services,
 * - runtime clock-frequency queries.
 */

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
 * @{
 */

/** @brief RCC frequency unit type @typedef _rcc_freq_t */
typedef uint32_t									_rcc_freq_t;

/** @brief 1 kHz frequency constant @def _RCC_FREQ_1kHz */
#define _RCC_FREQ_1kHz							((_rcc_freq_t) 1000UL)
/** @brief 1 MHz frequency constant @def _RCC_FREQ_1MHz */
#define _RCC_FREQ_1MHz							((_rcc_freq_t) 1000000UL)
/** @brief Internal high-speed oscillator nominal frequency @def _RCC_HSI_FREQ */
#define _RCC_HSI_FREQ							((_rcc_freq_t) 8000000UL)
/** @brief External high-speed oscillator nominal frequency @def _RCC_HSE_FREQ */
#define _RCC_HSE_FREQ							((_rcc_freq_t) 8000000UL)
/** @brief Maximum SYSCLK frequency @def _RCC_SYSCLK_MAX_FREQ */
#define _RCC_SYSCLK_MAX_FREQ					((_rcc_freq_t) 72000000UL)
/** @brief Maximum HCLK frequency @def _RCC_HCLK_MAX_FREQ */
#define _RCC_HCLK_MAX_FREQ						(_RCC_SYSCLK_MAX_FREQ)
/** @brief Maximum APB1 frequency @def _RCC_PCLK1_MAX_FREQ */
#define _RCC_PCLK1_MAX_FREQ					((_rcc_freq_t) 36000000UL)
/** @brief Maximum APB2 frequency @def _RCC_PCLK2_MAX_FREQ */
#define _RCC_PCLK2_MAX_FREQ					((_rcc_freq_t) 72000000UL)
/** @brief Maximum ADC clock frequency @def _RCC_ADCCLK_MAX_FREQ */
#define _RCC_ADCCLK_MAX_FREQ					((_rcc_freq_t) 14000000UL)
/** @brief Target USB clock frequency @def _RCC_USBCLK_TARGET_FREQ */
#define _RCC_USBCLK_TARGET_FREQ				((_rcc_freq_t) 48000000UL)

/** @} */ // RCC_03_Driver_01_Frequency

/*---------------------------------------------- RCC Flash Configuration ----------------------------------------------*/
/**
 * @brief	RCC Flash Configuration Types
 * @defgroup RCC_03_Driver_02_Flash RCC Driver Flash Configuration
 * @ingroup	RCC_03_Driver
 * @{
 */

/** @brief Flash latency type @typedef rcc_flash_latency_t */
typedef uint8_t									rcc_flash_latency_t;
/** @brief Flash zero wait states @def RCC_FLASH_LATENCY_0 */
#define RCC_FLASH_LATENCY_0						((rcc_flash_latency_t) 0x00U)
/** @brief Flash one wait state @def RCC_FLASH_LATENCY_1 */
#define RCC_FLASH_LATENCY_1						((rcc_flash_latency_t) 0x01U)
/** @brief Flash two wait states @def RCC_FLASH_LATENCY_2 */
#define RCC_FLASH_LATENCY_2						((rcc_flash_latency_t) 0x02U)

/** @brief Flash prefetch selector type @typedef rcc_flash_prefetch_t */
typedef uint8_t									rcc_flash_prefetch_t;
/** @brief Flash prefetch disabled @def RCC_FLASH_PREFETCH_DISABLE */
#define RCC_FLASH_PREFETCH_DISABLE				((rcc_flash_prefetch_t) 0x00U)
/** @brief Flash prefetch enabled @def RCC_FLASH_PREFETCH_ENABLE */
#define RCC_FLASH_PREFETCH_ENABLE				((rcc_flash_prefetch_t) 0x01U)

/**
 * @brief	Flash configuration descriptor
 * @typedef	rcc_flash_config_t
 */
typedef struct
{
	rcc_flash_latency_t		latency;
	rcc_flash_prefetch_t	prefetch;
} rcc_flash_config_t;

/** @} */ // RCC_03_Driver_02_Flash

/*---------------------------------------------- RCC System Clock ----------------------------------------------*/
/**
 * @brief	RCC System Clock and PLL Types
 * @defgroup RCC_03_Driver_03_SystemClock RCC Driver System Clock Configuration
 * @ingroup	RCC_03_Driver
 * @{
 */

/** @brief System clock source selector type @typedef rcc_system_clock_t */
typedef uint8_t									rcc_system_clock_t;
/** @brief HSI selected as SYSCLK @def RCC_SYS_CLK_HSI */
#define RCC_SYS_CLK_HSI							((rcc_system_clock_t) 0x00U)
/** @brief HSE selected as SYSCLK @def RCC_SYS_CLK_HSE */
#define RCC_SYS_CLK_HSE							((rcc_system_clock_t) 0x01U)
/** @brief PLL selected as SYSCLK @def RCC_SYS_CLK_PLL */
#define RCC_SYS_CLK_PLL							((rcc_system_clock_t) 0x02U)

/** @brief PLL source selector type @typedef rcc_pll_src_t */
typedef uint8_t									rcc_pll_src_t;
/** @brief HSI divided by 2 selected as PLL input @def RCC_PLL_SRC_HSI */
#define RCC_PLL_SRC_HSI							((rcc_pll_src_t) 0x00U)
/** @brief HSE selected as PLL input @def RCC_PLL_SRC_HSE */
#define RCC_PLL_SRC_HSE							((rcc_pll_src_t) 0x01U)

/** @brief PLL input prescaler selector type @typedef rcc_pll_src_psc_t */
typedef uint8_t									rcc_pll_src_psc_t;
/** @brief Fixed HSI divide-by-2 PLL input @def RCC_PLL_SRC_HSI_DIV_2 */
#define RCC_PLL_SRC_HSI_DIV_2					((rcc_pll_src_psc_t) 0x00U)
/** @brief HSE divide-by-1 PLL input @def RCC_PLL_SRC_HSE_DIV_1 */
#define RCC_PLL_SRC_HSE_DIV_1					((rcc_pll_src_psc_t) 0x01U)
/** @brief HSE divide-by-2 PLL input @def RCC_PLL_SRC_HSE_DIV_2 */
#define RCC_PLL_SRC_HSE_DIV_2					((rcc_pll_src_psc_t) 0x02U)

/** @brief PLL multiplication factor type @typedef rcc_pll_mul_t */
typedef uint8_t									rcc_pll_mul_t;
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
typedef struct
{
	rcc_pll_src_t			source;
	rcc_pll_src_psc_t	source_prescaler;
	rcc_pll_mul_t			multiplication_factor;
} rcc_pll_config_t;

/**
 * @brief	System clock configuration descriptor
 * @typedef	rcc_sys_clk_config_t
 */
typedef struct
{
	rcc_system_clock_t	clk_src;
	rcc_pll_config_t	pll;
} rcc_sys_clk_config_t;

/** @} */ // RCC_03_Driver_03_SystemClock

/*---------------------------------------------- RCC Prescalers ----------------------------------------------*/
/**
 * @brief	RCC Bus and Component Prescaler Types
 * @defgroup RCC_03_Driver_04_Prescalers RCC Driver Prescaler Configuration
 * @ingroup	RCC_03_Driver
 * @{
 */

/** @brief RCC bus selector type @typedef rcc_bus_t */
typedef uint8_t									rcc_bus_t;
/** @brief AHB bus selector @def RCC_AHB_BUS */
#define RCC_AHB_BUS								((rcc_bus_t) 0x00U)
/** @brief APB1 bus selector @def RCC_APB1_BUS */
#define RCC_APB1_BUS							((rcc_bus_t) 0x01U)
/** @brief APB2 bus selector @def RCC_APB2_BUS */
#define RCC_APB2_BUS							((rcc_bus_t) 0x02U)

/** @brief Bus prescaler divider type @typedef rcc_bus_prescaler_t */
typedef uint16_t								rcc_bus_prescaler_t;
/** @brief Divider 1 @def RCC_AHB_DIV_1 */
#define RCC_AHB_DIV_1							((rcc_bus_prescaler_t) 1U)
/** @brief Divider 2 @def RCC_AHB_DIV_2 */
#define RCC_AHB_DIV_2							((rcc_bus_prescaler_t) 2U)
/** @brief Divider 4 @def RCC_AHB_DIV_4 */
#define RCC_AHB_DIV_4							((rcc_bus_prescaler_t) 4U)
/** @brief Divider 8 @def RCC_AHB_DIV_8 */
#define RCC_AHB_DIV_8							((rcc_bus_prescaler_t) 8U)
/** @brief Divider 16 @def RCC_AHB_DIV_16 */
#define RCC_AHB_DIV_16							((rcc_bus_prescaler_t) 16U)
/** @brief Divider 64 @def RCC_AHB_DIV_64 */
#define RCC_AHB_DIV_64							((rcc_bus_prescaler_t) 64U)
/** @brief Divider 128 @def RCC_AHB_DIV_128 */
#define RCC_AHB_DIV_128							((rcc_bus_prescaler_t) 128U)
/** @brief Divider 256 @def RCC_AHB_DIV_256 */
#define RCC_AHB_DIV_256							((rcc_bus_prescaler_t) 256U)
/** @brief Divider 512 @def RCC_AHB_DIV_512 */
#define RCC_AHB_DIV_512							((rcc_bus_prescaler_t) 512U)

/** @brief Divider 1 @def RCC_APB1_DIV_1 */
#define RCC_APB1_DIV_1							((rcc_bus_prescaler_t) 1U)
/** @brief Divider 2 @def RCC_APB1_DIV_2 */
#define RCC_APB1_DIV_2							((rcc_bus_prescaler_t) 2U)
/** @brief Divider 4 @def RCC_APB1_DIV_4 */
#define RCC_APB1_DIV_4							((rcc_bus_prescaler_t) 4U)
/** @brief Divider 8 @def RCC_APB1_DIV_8 */
#define RCC_APB1_DIV_8							((rcc_bus_prescaler_t) 8U)
/** @brief Divider 16 @def RCC_APB1_DIV_16 */
#define RCC_APB1_DIV_16							((rcc_bus_prescaler_t) 16U)

/** @brief Divider 1 @def RCC_APB2_DIV_1 */
#define RCC_APB2_DIV_1							((rcc_bus_prescaler_t) 1U)
/** @brief Divider 2 @def RCC_APB2_DIV_2 */
#define RCC_APB2_DIV_2							((rcc_bus_prescaler_t) 2U)
/** @brief Divider 4 @def RCC_APB2_DIV_4 */
#define RCC_APB2_DIV_4							((rcc_bus_prescaler_t) 4U)
/** @brief Divider 8 @def RCC_APB2_DIV_8 */
#define RCC_APB2_DIV_8							((rcc_bus_prescaler_t) 8U)
/** @brief Divider 16 @def RCC_APB2_DIV_16 */
#define RCC_APB2_DIV_16							((rcc_bus_prescaler_t) 16U)

/**
 * @brief	Bus prescaler configuration descriptor
 * @typedef	rcc_bus_config_t
 */
typedef struct
{
	rcc_bus_prescaler_t	AHB;
	rcc_bus_prescaler_t	APB1;
	rcc_bus_prescaler_t	APB2;
} rcc_bus_config_t;

/** @brief Component prescaler selector type @typedef rcc_component_prescaler_t */
typedef uint8_t									rcc_component_prescaler_t;
/** @brief ADC divider 2 @def RCC_ADC_DIV_2 */
#define RCC_ADC_DIV_2							((rcc_component_prescaler_t) 2U)
/** @brief ADC divider 4 @def RCC_ADC_DIV_4 */
#define RCC_ADC_DIV_4							((rcc_component_prescaler_t) 4U)
/** @brief ADC divider 6 @def RCC_ADC_DIV_6 */
#define RCC_ADC_DIV_6							((rcc_component_prescaler_t) 6U)
/** @brief ADC divider 8 @def RCC_ADC_DIV_8 */
#define RCC_ADC_DIV_8							((rcc_component_prescaler_t) 8U)
/** @brief USB clock equals PLL divided by 1.5 @def RCC_USB_DIV_1_5 */
#define RCC_USB_DIV_1_5							((rcc_component_prescaler_t) 0x00U)
/** @brief USB clock equals PLL directly @def RCC_USB_DIV_1 */
#define RCC_USB_DIV_1							((rcc_component_prescaler_t) 0x01U)

/**
 * @brief	Component prescaler configuration descriptor
 * @typedef	rcc_component_config_t
 */
typedef struct
{
	rcc_component_prescaler_t	ADC;
	rcc_component_prescaler_t	USB;
} rcc_component_config_t;

/** @} */ // RCC_03_Driver_04_Prescalers

/*---------------------------------------------- RCC Aggregate Configuration ----------------------------------------------*/
/**
 * @brief	RCC Aggregate Configuration Types
 * @defgroup RCC_03_Driver_05_Config RCC Driver Aggregate Configuration
 * @ingroup	RCC_03_Driver
 * @{
 */

/**
 * @brief	Clock-tree configuration descriptor
 * @typedef	rcc_clock_tree_config_t
 */
typedef struct
{
	rcc_sys_clk_config_t		system;
	rcc_bus_config_t			bus;
	rcc_component_config_t	component;
} rcc_clock_tree_config_t;

/**
 * @brief	Complete RCC configuration descriptor
 * @typedef	rcc_config_t
 */
typedef struct
{
	rcc_flash_config_t		flash;
	rcc_clock_tree_config_t	clock_tree;
} rcc_config_t;

/** @} */ // RCC_03_Driver_05_Config

/*---------------------------------------------- RCC Clock Gate and Reset APIs ----------------------------------------------*/
/**
 * @brief	RCC Clock Gate and Reset APIs
 * @defgroup RCC_03_Driver_06_ClockReset RCC Driver Clock Enable and Reset APIs
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
driver_status_t RCC_AHB_ClockEnable(const uint32_t clockMask);

/**
 * @brief	Disables AHB peripheral clock gates
 * @param[in] clockMask	AHB clock enable mask from RCC register definitions
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested AHB clock gates were disabled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid.
 */
driver_status_t RCC_AHB_ClockDisable(const uint32_t clockMask);

/**
 * @brief	Enables APB2 peripheral clock gates
 * @param[in] clockMask	APB2 clock enable mask from RCC register definitions
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested APB2 clock gates were enabled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid.
 */
driver_status_t RCC_APB2_ClockEnable(const uint32_t clockMask);

/**
 * @brief	Disables APB2 peripheral clock gates
 * @param[in] clockMask	APB2 clock enable mask from RCC register definitions
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested APB2 clock gates were disabled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid.
 */
driver_status_t RCC_APB2_ClockDisable(const uint32_t clockMask);

/**
 * @brief	Enables APB1 peripheral clock gates
 * @param[in] clockMask	APB1 clock enable mask from RCC register definitions
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested APB1 clock gates were enabled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid.
 */
driver_status_t RCC_APB1_ClockEnable(const uint32_t clockMask);

/**
 * @brief	Disables APB1 peripheral clock gates
 * @param[in] clockMask	APB1 clock enable mask from RCC register definitions
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested APB1 clock gates were disabled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockMask was zero or invalid.
 */
driver_status_t RCC_APB1_ClockDisable(const uint32_t clockMask);

/**
 * @brief	Pulses APB2 peripheral reset bits
 * @param[in] resetMask	APB2 reset mask from RCC register definitions
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested APB2 peripherals were reset-pulsed.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p resetMask was zero or invalid.
 */
driver_status_t RCC_APB2_ResetPulse(const uint32_t resetMask);

/**
 * @brief	Pulses APB1 peripheral reset bits
 * @param[in] resetMask	APB1 reset mask from RCC register definitions
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested APB1 peripherals were reset-pulsed.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p resetMask was zero or invalid.
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
 * @returns - @ref driver_status_t Validation result
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Configuration is valid and internally consistent.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p cfg was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Configuration contains an invalid source, divider, multiplier, or limit violation.
 */
driver_status_t RCC_ValidateConfig(const rcc_config_t* cfg);

/**
 * @brief	Applies Flash latency and prefetch configuration
 * @param[in] flash	Pointer to @ref rcc_flash_config_t
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Flash latency and prefetch configuration were applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p flash was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Flash configuration fields were invalid.
 */
driver_status_t RCC_ConfigFlash(const rcc_flash_config_t* flash);

/**
 * @brief	Applies AHB, APB1, and APB2 prescaler configuration
 * @param[in] busCfg	Pointer to @ref rcc_bus_config_t
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested bus prescalers were applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p busCfg was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more bus prescaler values were invalid.
 */
driver_status_t RCC_ConfigBusPrescaler(const rcc_bus_config_t* busCfg);

/**
 * @brief	Applies ADC and USB prescaler configuration
 * @param[in] componentCfg	Pointer to @ref rcc_component_config_t
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested component prescalers were applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p componentCfg was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more component prescaler values were invalid.
 */
driver_status_t RCC_ConfigComponentPrescaler(const rcc_component_config_t* componentCfg);

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
 * @brief	Applies a complete clock-tree configuration through the RCC driver orchestrator
 * @param[in] clockTree	Pointer to @ref rcc_clock_tree_config_t
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock-tree sequencing completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p clockTree was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Configuration contained invalid clock-tree values.
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A source ready-state or switch confirmation timed out.
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read during sequencing.
 */
driver_status_t RCC_ConfigClockTree(const rcc_clock_tree_config_t* clockTree);

/**
 * @brief	Applies a complete RCC configuration descriptor
 * @param[in] cfg	Pointer to @ref rcc_config_t
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Flash and clock-tree configuration completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p cfg was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Configuration contained invalid fields or violated frequency limits.
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A source ready-state or switch confirmation timed out.
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read during sequencing.
 */
driver_status_t RCC_Config(const rcc_config_t* cfg);

/**
 * @brief	Loads the default 72 MHz Blue Pill clock-tree preset
 * @param[out] cfg	Pointer to @ref rcc_config_t
 */
void RCC_72MHz_LoadDefaultConfig(rcc_config_t* cfg);

/**
 * @brief	Applies the default 72 MHz Blue Pill RCC configuration
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Default 72 MHz configuration completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Default configuration validation failed.
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A source ready-state or switch confirmation timed out.
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read during sequencing.
 */
driver_status_t RCC_Config_72MHz(void);

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

/**
 * @brief	Returns the current core clock frequency before AHB division
 * @returns	Core clock frequency in Hz
 */
_rcc_freq_t RCC_GetCoreClockFreq(void);

/**
 * @brief	Returns the configured divider for a requested bus
 * @param[in] bus	Target bus selector of @ref rcc_bus_t
 * @returns	Configured bus divider value
 */
rcc_bus_prescaler_t RCC_GetBusPrescaler(const rcc_bus_t bus);

/**
 * @brief	Returns the current frequency of a requested bus
 * @param[in] bus	Target bus selector of @ref rcc_bus_t
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
 * @{
 */

__STATIC_FORCEINLINE _rcc_freq_t RCC_Get_AHBClock(void)
{
	return RCC_GetBusFreq(RCC_AHB_BUS);
}

__STATIC_FORCEINLINE _rcc_freq_t RCC_Get_APB1Clock(void)
{
	return RCC_GetBusFreq(RCC_APB1_BUS);
}

__STATIC_FORCEINLINE _rcc_freq_t RCC_Get_APB2Clock(void)
{
	return RCC_GetBusFreq(RCC_APB2_BUS);
}

__STATIC_FORCEINLINE _rcc_freq_t RCC_CoreClockFreq_Get(void)
{
	return RCC_GetCoreClockFreq();
}

__STATIC_FORCEINLINE _rcc_freq_t RCC_AHBClockFreq_Get(void)
{
	return RCC_Get_AHBClock();
}

__STATIC_FORCEINLINE _rcc_freq_t RCC_APB1ClockFreq_Get(void)
{
	return RCC_Get_APB1Clock();
}

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
