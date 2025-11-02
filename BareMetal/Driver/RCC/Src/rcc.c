/**
 * @file rcc.c
 * @author Shrey Shah
 * @brief Reset & Clock Control Configuration
 * @version 1.1
 * @date 28-09-2025
 * @note Logs till v1.1:
 * @note - Aborted usage of `enums` as it consumes a lot of space
 * @note - Shifted to use combination of `typedef` & macros
 */

/*********************************************** Header Guards ***********************************************/
#include "rcc.h"

/*********************************************** System Frequency Tracker ***********************************************/
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

/*********************************************** Driver APIs ***********************************************/
/**
 * @brief RCC Flash Configuration
 * @param flash Flash Configuration Structure `rcc_flash_config_t`
 * @param reg Pointer to `FLASH->ACR.REG`
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_FlashConfig(const rcc_flash_config_t flash, uint32_t *reg)
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
 * @param componentPrescalerConfig Compoennt Prescaler Configuration Structure
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
	status = RCC_FlashConfig(rccConfig->flash, &reg);
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
