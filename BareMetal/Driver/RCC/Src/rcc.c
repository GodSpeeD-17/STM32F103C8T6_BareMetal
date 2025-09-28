/**************************************************************************************
 * 	File: rcc.c
 *  Author: Shrey Shah
 *  Date: 14/09/2024
 ***************************************************************************************/

// Header File
#include "rcc.h"

/**
 * @brief System frequency Summary
 */
static rcc_clk_freq_t systemFrequency = {
	.Core = HSI_FREQ,
	.AHB = HSI_FREQ,
	.APB1 = HSI_FREQ,
	.APB2 = HSI_FREQ
};

/**
 * @brief RCC Flash Configuration
 * @param flash Flash Configuration Structure `flash_config_t` 
 * @param reg Pointer to `FLASH->ACR.REG`
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
static driver_status_t __RCC_FlashConfig__(const flash_config_t flash, uint32_t* reg){
	// Clear
	*reg &= (uint32_t)(FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY);
	// Write
	*reg |= (uint32_t)(
		((flash.prefetch & 0x01) << FLASH_ACR_PRFTBE_Pos) | 
		((flash.latency & 0x07) << FLASH_ACR_LATENCY_Pos)
	);
	// Return Success
	return DRIVER_SUCCESS;
}

/**
 * @brief RCC Clock Configuration
 * @param rccConfig RCC Clock Configuration Structure 
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_Config(const rcc_config_t* rccConfig){
	// Local Variable
	driver_status_t status = DRIVER_FAIL;
	uint32_t reg = FLASH->ACR.REG;
	// Flash Configuration
	status = __RCC_FlashConfig__(rccConfig->flash, &reg);
	reg = RCC->CFGR.REG;
	// HSE ON
	RCC->CR.REG |= RCC_CR_HSEON;
	while((RCC->CR.REG & RCC_CR_HSERDY) != 0x01);
	// PLL Configuration
	reg |= (uint32_t)(
			((rccConfig->system.pll.mul_fact & 0x0F) << RCC_CFGR_PLLMULL_Pos) | 
			((rccConfig->system.pll.src_prescaler & 0x01) << RCC_CFGR_PLLXTPRE_Pos) |
			((rccConfig->system.pll.src & 0x01) << RCC_CFGR_PLLSRC_Pos)
	);
	// Bus Prescaler Configuration
	reg |= (uint32_t)(
			((rccConfig->bus_prescaler.APB2 & 0x07) << RCC_CFGR_PPRE2_Pos) | 
			((rccConfig->bus_prescaler.APB1 & 0x07) << RCC_CFGR_PPRE1_Pos) | 
			((rccConfig->bus_prescaler.AHB & 0x0F) << RCC_CFGR_HPRE_Pos)
	);
	// Component Prescaler Configuration
	reg |= (uint32_t)(
			((rccConfig->component_prescaler.USB & 0x01) << RCC_CFGR_USBPRE_Pos) | 
			((rccConfig->component_prescaler.ADC & 0x03) << RCC_CFGR_ADCPRE_Pos)
	);
	// Update the CFGR Register
	RCC->CFGR.REG = reg;
	// PLL ON
	if(rccConfig->system.clk_src == RCC_SYS_CLK_PLL){
		RCC->CR.REG |= RCC_CR_PLLON;
		while(!(RCC->CR.REG & RCC_CR_PLLRDY));
	}
	// System Clock Source
	RCC->CFGR.REG |= (uint32_t)(((rccConfig->system.clk_src & 0x03) << RCC_CFGR_SW_Pos));
	while(((RCC->CFGR.REG & RCC_CFGR_SWS) != ((rccConfig->system.clk_src & 0x03) << RCC_CFGR_SWS_Pos)));
	// Update the Frequency (NOTE: Order of Updation is Important)
	RCC_Update_CoreClock();
	RCC_Update_AHBClock();
	RCC_Update_APB1Clock();
	RCC_Update_APB2Clock();
}

#ifdef __OLD_RCC_METHOD__

// 72MHz Configuration
static const rcc_config_t RCC_Configuration_72MHz = {
	// Flash Configuration
	.flash = {
		// 2 wait states
		.latency = FLASH_ACR_LATENCY_2,
		// Prefetch enabled
		.prefetch = FLASH_ACR_PRFTBE_Msk
	},
	// PLL Configuration
	.pll = {
		// HSE as PLL Clock Source
		.ext_src = RCC_PLL_SRC_HSE_DIV_1,
		// PLL Multiplication Factor 9
		.mul_fact = RCC_PLL_MUL_9
	},
	// Bus Configuration
	.bus_prescaler = {
		// AHB Bus Prescaler: 1 (72MHz)
		.AHB = RCC_AHB_DIV_1,
		// APB1 Bus Prescaler: 2 (36MHz)
		.APB1 = RCC_APB1_DIV_2,
		// APB2 Bus Prescaler: 1 (72MHz)
		.APB2 = RCC_APB2_DIV_1
	},
	.component_prescaler = {
		// ADC Prescaler: @14MHz
		.ADC = RCC_ADC_DIV_6,
		// USB Prescaler: @48MHz
		.USB = RCC_USB_DIV_1_5
	},
	// Select PLL as System Clock Source
	.sys_clk_src = RCC_SW_CLK_PLL
};

/**
 * @brief Configures RCC
 * @param configX RCC Configuration Structure
 */
void RCC_Config(rcc_config_t* configX){
	// Flash Configuration
	FLASH->ACR.REG |= (uint32_t)(configX->flash.latency << FLASH_ACR_LATENCY_Pos);
	// HSE ON
	RCC->CR.REG |= RCC_CR_HSEON;
	// Local Variable
	uint32_t reg = RCC->CFGR.REG;
	while(!(RCC->CR.REG & RCC_CR_HSERDY_Msk));
	// PLL Configuration
	reg |= (uint32_t)(((configX->pll.mul_fact & 0x0F) << RCC_CFGR_PLLMULL_Pos) | 
					  ((configX->pll.ext_src & 0x03) << RCC_CFGR_PLLSRC_Pos));
	// Bus Prescaler Configuration
	reg |= (uint32_t)(((configX->bus_prescaler.APB2 & 0x07) << RCC_CFGR_PPRE2_Pos) | 
					  ((configX->bus_prescaler.APB1 & 0x07) << RCC_CFGR_PPRE1_Pos) | 
					  ((configX->bus_prescaler.AHB & 0x0F) << RCC_CFGR_HPRE_Pos));
	// Component Prescaler Configuration
	reg |= (uint32_t)(((configX->component_prescaler.USB & 0x01) << RCC_CFGR_USBPRE_Pos) | 
					  ((configX->component_prescaler.ADC & 0x03) << RCC_CFGR_ADCPRE_Pos));
	// Update the CFGR Register
	RCC->CFGR.REG = reg;
	// PLL ON
	if(configX->sys_clk_src == RCC_SW_CLK_PLL){
		RCC->CR.REG |= RCC_CR_PLLON;
		while(!(RCC->CR.REG & RCC_CR_PLLRDY));
	}
	// System Clock Source
	RCC->CFGR.REG |= (uint32_t)(((configX->sys_clk_src & 0x03) << RCC_CFGR_SW_Pos));
	while(((RCC->CFGR.REG & RCC_CFGR_SWS) != ((RCC->CFGR.REG & RCC_CFGR_SW) << RCC_CFGR_SWS_Pos)));
	// Update the Frequency (NOTE: Order of Updation is Important)
	RCC_Update_CoreClock();
	RCC_Update_AHBClock();
	RCC_Update_APB1Clock();
	RCC_Update_APB2Clock();
}

/**
 * @brief Loads `rcc_config_t` with PLL 72MHz configuration
 * @param configX Pointer to `rcc_config_t` structure to be configured
 */
void RCC_Config_Load_72MHz(rcc_config_t* configX){
	// Configure Flash Latency to 2 wait states
	configX->flash.latency = FLASH_ACR_LATENCY_2;
	// Enable Flash Prefetch Buffer
	configX->flash.prefetch = FLASH_ACR_PRFTBE_Msk;
	// Select PLL as System Clock Source
	configX->sys_clk_src = RCC_SW_CLK_PLL;
	// Select HSE as PLL Clock Source
	configX->pll.ext_src = RCC_PLL_SRC_HSE_DIV_1;
	// Select 9 as PLL Multiplication Factor
	configX->pll.mul_fact = RCC_PLL_MUL_9;
	// Set AHB Bus @72MHz
	configX->bus_prescaler.AHB = RCC_AHB_DIV_1;
	// Set APB1 Bus @36MHz
	configX->bus_prescaler.APB1 = RCC_APB1_DIV_2;
	// Set APB2 Bus @72MHz
	configX->bus_prescaler.APB2 = RCC_APB2_DIV_1;
	// Set ADC @14MHz
	configX->component_prescaler.ADC = RCC_ADC_DIV_6;
	// Set USB @48MHz
	configX->component_prescaler.USB = RCC_USB_DIV_1_5;
}

/**
 * @brief Configures System to run at 72MHz
 */
void RCC_Config_72MHz(){
	// Configuration
	RCC_Config(&RCC_Configuration_72MHz);
}

#endif /* __OLD_RCC_METHOD__ */