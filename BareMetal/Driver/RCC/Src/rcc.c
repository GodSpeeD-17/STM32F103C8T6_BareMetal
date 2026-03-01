/**
 * @file rcc.c
 * @author Shrey Shah
 * @brief Reset & Clock Control Configuration
 * @version 1.2
 * @date 08-11-2025
 * @note Logs till v1.1:
 * @note - Aborted usage of `enums` as it consumes a lot of space
 * @note - Shifted to use combination of `typedef` & macros
 */

/*---------------------------------------------- Header Guards ----------------------------------------------*/
#include "rcc.h"

#ifdef __FREQ_TRACKING_ENABLED__
/*---------------------------------------------- RCC Clock Frequency Tracking ----------------------------------------------*/
/**
 * @brief    Driver RCC Clock Frequency Tracking Structure
 * @defgroup RCC_03_Driver_07_ClockFrequency Driver RCC Clock Frequency Tracking
 * @ingroup  RCC_03_Driver
 * @details
 * - Ultra-efficient frequency tracking using AHB base + prescalers
 * - Uses LUT-based right-shifting instead of division for maximum performance
 * - Perfect balance of memory efficiency and calculation speed
 *
 * @see Reference Manual RM0008 - Section 7. Clock Configuration
 * @{
 */

/**
 * @brief RCC Clock Frequency Structure
 * @typedef rcc_clk_freq_t
 */
typedef struct 
{
	/** @brief Core system clock frequency in Hz (before AHB prescaler) */
	_rcc_freq_t Core;
	
	/** @brief System Clock Configuration */
	struct 
	{
		/** @brief System clock source - HSI/HSE/PLL */
		rcc_system_clock_t source : 2;
		/** @brief Reserved for future expansion */
		uint8_t _reserved : 1;
		
		/** @brief PLL Configuration */
		struct 
		{
			/** @brief PLL multiplication factor - x2 to x16 */
			rcc_pll_mul_t multiplier : 4;
			/** @brief PLL source - HSI/HSE */
			rcc_pll_src_t source : 1;
			/** @brief PLL source prescaler */
			rcc_pll_src_psc_t source_prescaler : 1;
		} pll;
	} system;
	
	/** @brief Clock Prescalers Configuration */
	struct
	{
		/** @brief Bus Prescalers */
		struct
		{
			/** @brief AHB prescaler as shift count - /1,/2,/4,...,/512 */
			rcc_bus_prescaler_t AHB : 4;
			/** @brief APB1 prescaler as shift count - /1,/2,/4,/8,/16 */
			rcc_bus_prescaler_t APB1 : 3;
			/** @brief APB2 prescaler as shift count - /1,/2,/4,/8,/16 */
			rcc_bus_prescaler_t APB2 : 3;
		} bus;
		
		/** @brief Component Prescalers */
		struct
		{
			/** @brief ADC prescaler - /2,/4,/6,/8 */
			rcc_component_prescaler_t ADC : 2;
			/** @brief USB prescaler - /1.5,/1 */
			rcc_component_prescaler_t USB : 1;
		} component;
	} prescaler;
} rcc_clk_freq_t;

// Default System Configuration
volatile rcc_clk_freq_t _systemConfig = 
{
	.Core = _RCC_HSI_FREQ,
	.system =
	{
		.source = RCC_SYS_CLK_PLL,
		.pll =
		{
			.multiplier = RCC_PLL_MUL_9,
			.source = RCC_PLL_SRC_HSE,
			.source_prescaler = RCC_PLL_SRC_HSE_DIV_1,
		}
	},
	.prescaler =
	{
		.bus =
		{
			.AHB = RCC_AHB_DIV_1,
			.APB1 = RCC_APB1_DIV_2,
			.APB2 = RCC_APB2_DIV_1,
		},
		.component = 
		{
			.ADC = RCC_ADC_DIV_6,
			.USB = RCC_USB_DIV_1_5,
		}
	}
};

/** @} */ // RCC_03_Driver_07_ClockFrequency

#endif /* __FREQ_TRACKING_ENABLED__ */

/**
 * @brief Get current core clock frequency from hardware configuration
 * @returns Current core clock frequency in Hz
 * @note Calculates core frequency based on current system clock source and PLL configuration
 * @note Core clock is the system clock before AHB prescaler
 * @note For PLL configurations, calculates frequency based on source and multiplication factor
 */
_rcc_freq_t RCC_GetCoreClockFreq(void)
{
	_rcc_freq_t coreFreq = _RCC_HSI_FREQ;
	switch(RCC_GetSysClkSrc())
	{
		case RCC_SYS_CLK_HSE:
			coreFreq = _RCC_HSE_FREQ;
		break;

		case RCC_SYS_CLK_PLL:
			switch(RCC_GetPLLSource())
			{
				case RCC_PLL_SRC_HSI:
					coreFreq = _RCC_HSI_FREQ >> 1; // HSI divided by 2
				break;

				case RCC_PLL_SRC_HSE:
					coreFreq = _RCC_HSE_FREQ;
					if(RCC_GetPLLSourcePrescaler() == RCC_PLL_SRC_HSE_DIV_2) coreFreq >>= 1; // HSE divided by 2
				break;
			}
		break;
	}
	return coreFreq;
}

/**
 * @brief Retrieves the currently configured prescaler value for a specified bus
 * @param[in] rccBus The target bus to query (e.g., RCC_AHB_BUS). Refer to @ref rcc_bus_t.
 * @return The high-level prescaler setting. Refer to @ref rcc_bus_prescaler_t.
 * @note This is an inline helper function for performance.
 */
rcc_bus_prescaler_t RCC_GetBusPrescaler(const rcc_bus_t rccBus)
{
	uint32_t reg = __RCC_ReadCFGR(RCC);
	switch(rccBus)
	{
		case RCC_AHB_BUS:
			return (rcc_bus_prescaler_t)RCC_L2D_AHBPrescaler((_rcc_bus_prescaler_t)((reg & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos));
		break;
			
		case RCC_APB1_BUS:
			return (rcc_bus_prescaler_t)RCC_L2D_APB1Prescaler((_rcc_bus_prescaler_t)((reg & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos));
		break;

		case RCC_APB2_BUS:
			return (rcc_bus_prescaler_t)RCC_L2D_APB2Prescaler((_rcc_bus_prescaler_t)((reg & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos));
		break;
	}
}

/**
 * @brief Get current bus clock frequency
 * @param[in] bus Target bus identifier (@ref rcc_bus_t)
 * @returns Current bus clock frequency in Hz
 * @note Calculates bus frequency based on core clock and bus prescaler
 * @note For AHB bus: returns frequency after AHB prescaler
 * @note For APB1/APB2 buses: returns frequency after respective APB prescalers
 * @note Uses right-shift operation for efficient division by prescaler value
 */
_rcc_freq_t RCC_GetBusFreq(const rcc_bus_t bus)
{
	_rcc_freq_t busFreqHz = RCC_GetCoreClockFreq();
	busFreqHz >>= RCC_GetBusPrescaler(bus);
	return busFreqHz;
}

/**
 * @brief RCC Flash Configuration
 * @param flash Flash Configuration Structure @ref rcc_flash_config_t
 * @return Status of operation
 * @return - `DRIVER_STATUS_ERROR_FAIL`: Failure
 * @return - `DRIVER_STATUS_SUCCESS`: Success
 */
driver_status_t RCC_ConfigFlash(const rcc_flash_config_t* const flash)
{
	uint32_t reg = 0x00UL;
	// TODO: Replace this with __* API
	reg = FLASH->ACR.REG;
	reg = _RCC_StageFlashConfig(flash->latency, flash->prefetch, reg);
	// TODO: Replace this with __* API
	FLASH->ACR.REG = reg;
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Configure RCC Bus Prescalers
 * @param[in] rccBusPrescaler Pointer to Bus Prescaler Configuration Structure
 * @return Status of operation
 * @return - `DRIVER_STATUS_ERROR_FAIL`: Failure
 * @return - `DRIVER_STATUS_SUCCESS`: Success
 */
driver_status_t RCC_ConfigBusPrescaler(rcc_bus_config_t* const rccBusPrescaler)
{
	uint32_t reg = __RCC_ReadCFGR(RCC);
	reg = _RCC_StageBusPrescaler(
		RCC_D2L_AHBPrescaler(rccBusPrescaler->AHB),
		RCC_D2L_APB1Prescaler(rccBusPrescaler->APB1),
		RCC_D2L_APB2Prescaler(rccBusPrescaler->APB2),
		reg
	);
	__RCC_WriteCFGR(RCC, reg);
}

/**
 * @brief Configure RCC Component Prescalers
 * @param[in] rccComponentPrescaler Pointer to Component Prescaler Configuration Structure
 * @return Status of operation
 * @return - `DRIVER_STATUS_ERROR_FAIL`: Failure
 * @return - `DRIVER_STATUS_SUCCESS`: Success
 */
driver_status_t RCC_ConfigComponentPrescaler(rcc_component_config_t* const rccComponentPrescaler)
{
	uint32_t reg = __RCC_ReadCFGR(RCC);
	reg = _RCC_StageComponentPrescaler(
		RCC_D2L_ADCPrescaler(rccComponentPrescaler->ADC),
		RCC_D2L_USBPrescaler(rccComponentPrescaler->USB),
		reg
	);
	__RCC_WriteCFGR(RCC, reg);
}

/**
 * @brief Configures the system clock and bus prescalers.
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
 * @retval DRIVER_STATUS_SUCCESS          Configuration successful.
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG  Null configuration pointer.
 * @retval DRIVER_STATUS_ERROR_TIMEOUT      Clock source failed to stabilize (if timeout supported).
 *
 * @note Must be called once during system startup before any peripheral initialization.
 * @note Blocks until selected clock source (HSE/PLL) is stable.
 */
driver_status_t RCC_Config(rcc_config_t* const rcc)
{
	// Early validation
	if(rcc == NULL) return DRIVER_STATUS_ERROR_INVALID_ARG;

	uint32_t reg = 0x00UL;
	// Configure Flash Settings First (critical for timing)
	RCC_ConfigFlash(&rcc->flash);

	reg = __RCC_ReadCFGR(RCC);
	// Bus Prescaler
	_rcc_bus_prescaler_t ahb  = RCC_D2L_AHBPrescaler(rcc->prescaler.bus.AHB);
	_rcc_bus_prescaler_t apb1 = RCC_D2L_APB1Prescaler(rcc->prescaler.bus.APB1);
	_rcc_bus_prescaler_t apb2 = RCC_D2L_APB2Prescaler(rcc->prescaler.bus.APB2);
	reg = _RCC_StageBusPrescaler(ahb, apb1, apb2, reg);
	// Component Prescaler
	_rcc_component_prescaler_t adcPrescaler = RCC_D2L_ADCPrescaler(rcc->prescaler.component.ADC);
	_rcc_component_prescaler_t usbPrescaler = RCC_D2L_USBPrescaler(rcc->prescaler.component.USB);
	reg = _RCC_StageComponentPrescaler(adcPrescaler, usbPrescaler, reg);
	// PLL Configuration
	if(rcc->system.clk_src == RCC_SYS_CLK_PLL)
	{
		_rcc_pll_src_t pllSrc = RCC_D2L_PLLSource(rcc->system.pll.source);
		_rcc_pll_src_psc_t pllSrcPsc = RCC_D2L_PLLSourcePrescaler(rcc->system.pll.source_prescaler);
		_rcc_pll_mul_t pllMulFac = RCC_D2L_PLLMultiplication(rcc->system.pll.multiplication_factor);
		reg = _RCC_StagePLLParameters(pllSrc, pllSrcPsc, pllMulFac, reg);
	}
	
	// RCC Configuration Register Write
	__RCC_WriteCFGR(RCC, reg);

	// Ensuring reliability of clock source switch
	if((rcc->system.clk_src == RCC_SYS_CLK_HSE) || ((rcc->system.clk_src == RCC_SYS_CLK_PLL) && (rcc->system.pll.source == RCC_PLL_SRC_HSE)))
	{
		// HSE ready?
		RCC_ControlHSE(DRIVER_STATUS_ON);
		while(RCC_HSEReady() != DRIVER_STATUS_READY) __ASM volatile("nop"); // Prevent compiler optimization
	}

	// PLL?
	if(rcc->system.clk_src == RCC_SYS_CLK_PLL)
	{
		// Switch PLL ON
		RCC_ControlPLL(DRIVER_STATUS_ON);
		// PLL ready?
		while(RCC_PLLReady() != DRIVER_STATUS_READY) __ASM volatile("nop"); // Prevent compiler optimization
	}

	// System Clock Source
	reg = __RCC_ReadCFGR(RCC);
	_rcc_sys_clk_t sysClk = RCC_D2L_SystemClockSource(rcc->system.clk_src);
	reg = _RCC_StageSystemClockSource(sysClk, reg);
	__RCC_WriteCFGR(RCC, reg);
	while(RCC_GetSysClkSrc() != rcc->system.clk_src) __ASM volatile("nop"); // Prevent compiler optimization

	// HSI Required?
	if((rcc->system.clk_src != RCC_SYS_CLK_HSI) || (rcc->system.clk_src == RCC_SYS_CLK_PLL && rcc->system.pll.source != RCC_PLL_SRC_HSI))
	{
		RCC_ControlHSI(DRIVER_STATUS_OFF);
		while(RCC_HSIReady() != DRIVER_STATUS_ERROR_BUSY) __ASM volatile("nop"); // Prevent compiler optimization
	}

	// Return Success
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Sets default flash configuration for 72MHz
 * @param flashConfig Pointer to @ref rcc_flash_config_t "Flash Configuration Structure"
 */
void RCC_72MHz_FlashDefaultConfig(rcc_flash_config_t* const flashConfig)
{
	// Wait state for 2 states
	flashConfig->latency = RCC_FLASH_LATENCY_2;
	// Enable Prefetch Buffer (Enhanced Performance)
	flashConfig->prefetch = RCC_FLASH_PREFETCH_ENABLE;
}

/**
 * @brief PLL Default Configuration for 72MHz
 * @param pllConfig Pointer to @ref rcc_pll_config_t "PLL Configuration Structure"
 */
void RCC_72MHz_PLLDefaultConfig(rcc_pll_config_t* const pllConfig)
{
	// PLL Clock Source
	pllConfig->source = RCC_PLL_SRC_HSE;
	// PLL Clock Source Prescaler
	pllConfig->source_prescaler = RCC_PLL_SRC_HSE_DIV_1;
	// PLL Multiplication Factor
	pllConfig->multiplication_factor = RCC_PLL_MUL_9;
}

/**
 * @brief Sets System Configuration for 72MHz Clock
 * @param sysClkConfig Pointer to @ref rcc_sys_clk_config_t "System Clock Configuration Structure"
 */
void RCC_72MHz_SystemDefaultConfig(rcc_sys_clk_config_t* const sysClkConfig)
{
	// Set PLL as System Clock Source
	sysClkConfig->clk_src = RCC_SYS_CLK_PLL;
	// Set PLL Configuration
	RCC_72MHz_PLLDefaultConfig(&sysClkConfig->pll);
}

/**
 * @brief Sets Bus Prescaler for 72MHz
 * @param busPrescalerConfig Pointer to @ref rcc_bus_config_t "Bus Prescaler Configuration Structure"
 */
void RCC_72MHz_BusPrescalerDefaultConfig(rcc_bus_config_t* const busPrescalerConfig)
{
	// Set AHB Prescaler (Max 72MHz)
	busPrescalerConfig->AHB = RCC_AHB_DIV_1;
	// Set APB1 Prescaler (Max 36MHz)
	busPrescalerConfig->APB1 = RCC_APB1_DIV_2;
	// Set APB2 Prescaler (Max 72MHz)
	busPrescalerConfig->APB2 = RCC_APB2_DIV_1;
}

/**
 * @brief Sets Component Prescaler for 72MHz
 * @param componentPrescalerConfig Pointer to @ref rcc_component_config_t "Component Prescaler Configuration Structure"
 */
void RCC_72MHz_ComponentPrescalerDefaultConfig(rcc_component_config_t* const componentPrescalerConfig)
{
	// Set ADC Prescaler (Max 14MHz)
	componentPrescalerConfig->ADC = RCC_ADC_DIV_6;
	// Set USB Prescaler (Max 48MHz)
	componentPrescalerConfig->USB = RCC_USB_DIV_1_5;
}

/**
 * @brief Set Prescaler for 72MHz
 * @param prescalerConfig Pointer to @ref rcc_prescaler_config_t "Component Prescaler Configuration Structure"
 */
void RCC_72MHz_PrescalerDefaultConfig(rcc_prescaler_config_t* const prescalerConfig)
{
	// Set Bus Prescaler
	RCC_72MHz_BusPrescalerDefaultConfig(&prescalerConfig->bus);
	// Set Component Prescaler
	RCC_72MHz_ComponentPrescalerDefaultConfig(&prescalerConfig->component);
}

/**
 * @brief Sets RCC Configuration 72MHz
 * @param rccConfig Pointer to @ref rcc_config_t "RCC Configuration Structure"
 */
void RCC_72MHz_LoadDefaultConfig(rcc_config_t* const rccConfig)
{
	// Default Configuration for Flash
	RCC_72MHz_FlashDefaultConfig(&rccConfig->flash);
	// Default System Configuration
	RCC_72MHz_SystemDefaultConfig(&rccConfig->system);
	// Default Component Prescaler Configuration
	RCC_72MHz_PrescalerDefaultConfig(&rccConfig->prescaler);
}
