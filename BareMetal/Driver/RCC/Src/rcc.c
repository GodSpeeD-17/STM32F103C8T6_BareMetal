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
			rcc_ahb_prescaler_t AHB : 4;
			/** @brief APB1 prescaler as shift count - /1,/2,/4,/8,/16 */
			rcc_apb1_prescaler_t APB1 : 3;
			/** @brief APB2 prescaler as shift count - /1,/2,/4,/8,/16 */
			rcc_apb2_prescaler_t APB2 : 3;
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
rcc_bus_prescaler_t RCC_GetPrescaler(const rcc_bus_t rccBus)
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
	_rcc_freq_t ahbFreqHz = RCC_GetCoreClockFreq();
	ahbFreqHz >>= RCC_GetPrescaler(bus);
	return ahbFreqHz;
}

/**
 * @brief RCC Flash Configuration
 * @param flash Flash Configuration Structure @ref rcc_flash_config_t
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_ConfigFlash(const rcc_flash_config_t* const flash)
{
	uint32_t reg = 0x00UL;
	// TODO: Replace this with __* API
	reg = FLASH->ACR.REG;
	reg = _RCC_StageFlashConfig(flash->latency, flash->prefetch, reg);
	// TODO: Replace this with __* API
	FLASH->ACR.REG = reg;
	return DRIVER_SUCCESS;
}

/**
 * @brief Configure RCC Bus Prescalers
 * @param[in] rccBusPrescaler Pointer to Bus Prescaler Configuration Structure
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
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
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
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
 * @retval DRIVER_SUCCESS          Configuration successful.
 * @retval DRIVER_ERR_INVALID_ARG  Null configuration pointer.
 * @retval DRIVER_ERR_TIMEOUT      Clock source failed to stabilize (if timeout supported).
 *
 * @note Must be called once during system startup before any peripheral initialization.
 * @note Blocks until selected clock source (HSE/PLL) is stable.
 */
driver_status_t RCC_Config(rcc_config_t* const rcc)
{
	// Early validation
	if(rcc == NULL) return DRIVER_ERR_INVALID_ARG;

	uint32_t reg = 0x00UL;
	// Configure Flash Settings First (critical for timing)
	RCC_ConfigFlash(&rcc->flash);

	// Pipeline HSE Configuration (if needed)
	if((rcc->system.clk_src == RCC_SYS_CLK_HSE) || (rcc->system.clk_src == RCC_SYS_CLK_PLL && rcc->system.pll.source == RCC_PLL_SRC_HSE))
	{
		RCC_ControlHSE(DRIVER_STATE_ON);
	}

	reg = __RCC_ReadCFGR(RCC);
	// Bus Prescaler
	reg = _RCC_StageBusPrescaler(
		RCC_D2L_AHBPrescaler(rcc->prescaler.bus.AHB),
		RCC_D2L_APB1Prescaler(rcc->prescaler.bus.APB1),
		RCC_D2L_APB2Prescaler(rcc->prescaler.bus.APB2),
		reg
	);
	// Component Prescaler
	reg = _RCC_StageComponentPrescaler(
		RCC_D2L_ADCPrescaler(rcc->prescaler.component.ADC),
		RCC_D2L_USBPrescaler(rcc->prescaler.component.USB),
		reg
	);
	// PLL Configuration
	if(rcc->system.clk_src == RCC_SYS_CLK_PLL)
	{
		reg = _RCC_StagePLLParameters(
			rcc->system.pll.source,
			rcc->system.pll.source_prescaler,
			rcc->system.pll.multiplication_factor,
			reg
		);			
	}
	// System Clock Source
	reg = _RCC_StageSystemClockSource(rcc->system.clk_src, reg);

	// Pre-requisite compatibility
	if(rcc->system.clk_src != RCC_SYS_CLK_HSI)
	{
		// HSE ready?
		while(RCC_HSEReady() != DRIVER_STATE_READY) __ASM volatile("nop"); // Prevent compiler optimization
		// PLL?
		if(rcc->system.clk_src == RCC_SYS_CLK_PLL)
		{
			// Switch PLL ON
			RCC_ControlPLL(DRIVER_STATE_ON);
			// PLL ready?
			while(RCC_PLLReady() != DRIVER_STATE_READY) __ASM volatile("nop"); // Prevent compiler optimization
		}
	}
	
	// RCC Configuration Register Write
	__RCC_WriteCFGR(RCC, reg);
	// Validate System Clock Source
	while(RCC_GetSysClkSrc() != rcc->system.clk_src) __ASM volatile("nop"); // Prevent compiler optimization
	return DRIVER_SUCCESS;
}

#ifdef _OLD_
/*---------------------------------------------- System Frequency Tracker ----------------------------------------------*/
/**
 * @brief System frequency Summary
 */
rcc_clk_freq_t __systemFrequency__ = 
{
	.Core = HSI_FREQ,
	.AHB = HSI_FREQ,
	.APB1 = HSI_FREQ,
	.APB2 = HSI_FREQ
};

/*---------------------------------------------- Driver APIs ----------------------------------------------*/
/**
 * @brief RCC Flash Configuration
 * @param flash Flash Configuration Structure `rcc_flash_config_t`
 * @param reg Pointer to `FLASH->ACR.REG`
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_ConfigFlash(const rcc_flash_config_t flash, uint32_t *reg)
{
	// Clear
	*reg &= ~(uint32_t)(FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY);
	// Update
	*reg |= (uint32_t)(((flash.prefetch & 0x01) << FLASH_ACR_PRFTBE_Pos) |
					   ((flash.latency & 0x07) << FLASH_ACR_LATENCY_Pos));
	// Return Success
	return DRIVER_SUCCESS;
}

/**
 * @brief RCC PLL Configuration
 * @param pllConfig  PLL Configuration Structure
 * @param reg Pointer to `RCC->CFGR.REG`
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_PLLConfig(const rcc_pll_config_t pllConfig, uint32_t *reg)
{
	// Clear
	*reg &= ~(uint32_t)(RCC_CFGR_PLLMULL_Msk | RCC_CFGR_PLLXTPRE_Msk | RCC_CFGR_PLLSRC_Msk);
	// Update
	*reg |= (uint32_t)(((pllConfig.mul_fact & 0x0F) << RCC_CFGR_PLLMULL_Pos) |
					   ((pllConfig.src & 0x01) << RCC_CFGR_PLLSRC_Pos) |
					   ((pllConfig.src_prescaler & 0x01) << RCC_CFGR_PLLXTPRE_Pos));
	// Return Success
	return DRIVER_SUCCESS;
}

/**
 * @brief RCC Bus Prescaler Configuration
 * @param busConfig Bus Configuration Structure
 * @param reg Pointer to `RCC->CFGR.REG`
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_BusConfig(const rcc_bus_prescaler_config_t busPrescalerConfig, uint32_t *reg)
{
	// Clear
	*reg &= ~(uint32_t)(RCC_CFGR_PPRE2 | RCC_CFGR_PPRE1 | RCC_CFGR_HPRE);
	// Update
	*reg |= (uint32_t)(((busPrescalerConfig.APB2 & 0x07) << RCC_CFGR_PPRE2_Pos) |
					   ((busPrescalerConfig.APB1 & 0x07) << RCC_CFGR_PPRE1_Pos) |
					   ((busPrescalerConfig.AHB & 0x0F) << RCC_CFGR_HPRE_Pos));
	// Return
	return DRIVER_SUCCESS;
}

/**
 * @brief RCC Component Configuration - ADC, USB
 * @param componentPrescalerConfig Component Prescaler Configuration Structure
 * @param reg Pointer to `RCC->CFGR.REG`
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_ComponentConfig(const rcc_component_prescaler_config_t componentPrescalerConfig, uint32_t *reg)
{
	// Clear
	*reg &= ~(uint32_t)(RCC_CFGR_ADCPRE | RCC_CFGR_USBPRE);
	// Update
	*reg |= (uint32_t)(((componentPrescalerConfig.USB & 0x01) << RCC_CFGR_USBPRE_Pos) |
					   ((componentPrescalerConfig.ADC & 0x03) << RCC_CFGR_ADCPRE_Pos));
	// Return Status
	return DRIVER_SUCCESS;
}

/**
 * @brief RCC Clock Configuration
 * @param rccConfig RCC Clock Configuration Structure
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_Config(const rcc_config_t *rccConfig)
{
	// Local Variable
	driver_status_t status = DRIVER_FAIL;
	// Flash Access Control Register Read
	uint32_t reg = FLASH->ACR.REG;
	status = RCC_ConfigFlash(rccConfig->flash, &reg);
	ASSERT_DRIVER_STATUS(status);
	// Flash Access Control Register Write
	FLASH->ACR.REG = reg;
	// RCC Configuration Register Read
	reg = RCC->CFGR.REG;
	// Turn ON HSE if required
	if (rccConfig->system.clk_src != RCC_SYS_CLK_HSI)
	{
		// Check for PLL Source Clock
		if ((rccConfig->system.clk_src == RCC_SYS_CLK_PLL) && (rccConfig->system.pll.src == RCC_SYS_CLK_HSI))
		{
			status = DRIVER_FAIL;
			return status;
		}
		// HSE ON
		RCC_HSE_ON();
	}
	// PLL Configuration
	status = RCC_PLLConfig(rccConfig->system.pll, &reg);
	ASSERT_DRIVER_STATUS(status);
	// Bus Prescaler Configuration
	status = RCC_BusConfig(rccConfig->bus_prescaler, &reg);
	ASSERT_DRIVER_STATUS(status);
	// Component Prescaler Configuration
	status = RCC_ComponentConfig(rccConfig->component_prescaler, &reg);
	ASSERT_DRIVER_STATUS(status);
	// RCC Configuration Register Write
	RCC->CFGR.REG = reg;
	// PLL ON
	if (rccConfig->system.clk_src == RCC_SYS_CLK_PLL)
	{
		// PLL Clock ON
		RCC_PLL_ON();
	}
	// System Clock Source
	RCC_SysClkSrc_Set(rccConfig->system.clk_src);
	// Update the Frequency
	status = RCC_ClockFreq_Update(&__systemFrequency__);
	ASSERT_DRIVER_STATUS(status);
	// Return Status
	return status;
}

/**
 * @brief Sets default flash configuration for 72MHz
 * @param flashConfig Pointer to Flash Configuration Structure
 */
void RCC_72MHz_FlashDefaultConfig(rcc_flash_config_t *flashConfig)
{
	// Wait state for 2 states
	flashConfig->latency = FLASH_ACR_LATENCY_2;
	// Enable Prefetch Buffer (Enhanced Performance)
	flashConfig->prefetch = (uint8_t) (FLASH_ACR_PRFTBE >> FLASH_ACR_PRFTBE_Pos);
}

/**
 * @brief PLL Default Configuration for 72MHz
 * @param pllConfig Pointer to PLL Configuration Structure
 */
void RCC_72MHz_PLLDefaultConfig(rcc_pll_config_t *pllConfig)
{
	// PLL Clock Source
	pllConfig->src = RCC_PLL_SRC_HSE;
	// PLL Clock Source Prescaler
	pllConfig->src_prescaler = RCC_PLL_SRC_HSE_DIV_1;
	// PLL Multiplication Factor
	pllConfig->mul_fact = RCC_PLL_MUL_9;
}

/**
 * @brief Sets System Configuration for 72MHz Clock
 * @param sysClkConfig Pointer to System Clock
 */
void RCC_72MHz_SystemDefaultConfig(rcc_sys_clk_config_t *sysClkConfig)
{
	// Set PLL as System Clock Source
	sysClkConfig->clk_src = RCC_SYS_CLK_PLL;
	// Set PLL Configuration
	RCC_72MHz_PLLDefaultConfig(&sysClkConfig->pll);
}

/**
 * @brief Sets Bus Prescaler for 72MHz
 * @param busPrescalerConfig Pointer to Bus Prescaler Configuration Structure
 */
void RCC_72MHz_BusPrescalerDefaultConfig(rcc_bus_prescaler_config_t *busPrescalerConfig)
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
 * @param componentPrescalerConfig Pointer to Component Prescaler Configuration Structure
 */
void RCC_72MHz_ComponentPrescalerDefaultConfig(rcc_component_prescaler_config_t *componentPrescalerConfig)
{
	// Set ADC Prescaler (Max 14MHz)
	componentPrescalerConfig->ADC = RCC_ADC_DIV_6;
	// Set USB Prescaler (Max 48MHz)
	componentPrescalerConfig->USB = RCC_USB_DIV_1_5;
}

/**
 * @brief Sets RCC Configuration 72MHz
 * @param rccConfig RCC Configuration Structure
 */
void RCC_72MHz_LoadDefaultConfig(rcc_config_t *rccConfig)
{
	// Default Configuration for Flash
	RCC_72MHz_FlashDefaultConfig(&rccConfig->flash);
	// Default System Configuration
	RCC_72MHz_SystemDefaultConfig(&rccConfig->system);
	// Default Bus Prescaler Configuration
	RCC_72MHz_BusPrescalerDefaultConfig(&rccConfig->bus_prescaler);
	// Default Component Prescaler Configuration
	RCC_72MHz_ComponentPrescalerDefaultConfig(&rccConfig->component_prescaler);
}

#endif