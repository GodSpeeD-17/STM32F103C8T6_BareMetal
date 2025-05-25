/**************************************************************************************
 * 	File: rcc.c
 *  Author: Shrey Shah
 *  Date: 14/09/2024
 ***************************************************************************************/

// Header File
#include "rcc.h"

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
	reg |= (uint32_t)(((configX->bus.APB2_pre & 0x07) << RCC_CFGR_PPRE2_Pos) | 
					  ((configX->bus.APB1_pre & 0x07) << RCC_CFGR_PPRE1_Pos) | 
					  ((configX->bus.AHB_pre & 0x0F) << RCC_CFGR_HPRE_Pos));
	// Component Prescaler Configuration
	reg |= (uint32_t)(((configX->component.USB_pre & 0x01) << RCC_CFGR_USBPRE_Pos) | 
					  ((configX->component.ADC_pre & 0x03) << RCC_CFGR_ADCPRE_Pos));
	// Update the CFGR Register
	RCC->CFGR.REG = reg;
	// PLL ON
	if(configX->sys_clk_src == RCCx_SW_CLK_PLL){
		RCC->CR.REG |= RCC_CR_PLLON;
		while(!(RCC->CR.REG & RCC_CR_PLLRDY));
	}
	// System Clock Source
	RCC->CFGR.REG |= (uint32_t)(((configX->sys_clk_src & 0x03) << RCC_CFGR_SW_Pos));
	while(((RCC->CFGR.REG & RCC_CFGR_SWS) != (RCC->CFGR.REG & RCC_CFGR_SW)));
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
	configX->sys_clk_src = RCCx_SW_CLK_PLL;
	// Select HSE as PLL Clock Source
	configX->pll.ext_src = RCCx_PLL_SRC_HSE_DIV_1;
	// Select 9 as PLL Multiplication Factor
	configX->pll.mul_fact = RCCx_PLL_MUL_9;
	// Set AHB Bus @72MHz
	configX->bus.AHB_pre = RCCx_AHB_DIV_1;
	// Set APB1 Bus @36MHz
	configX->bus.APB1_pre = RCCx_APB1_DIV_2;
	// Set APB2 Bus @72MHz
	configX->bus.APB2_pre = RCCx_APB2_DIV_1;
	// Set ADC @14MHz
	configX->component.ADC_pre = RCCx_ADC_DIV_6;
	// Set USB @48MHz
	configX->component.USB_pre = RCCx_USB_DIV_1_5;
}

/**
 * @brief Configures System to run at 72MHz
 */
void RCC_Config_72MHz(){
	// Configuration: 72MHz
	rcc_config_t RCC_Configuration_72MHz;
	// Load 72MHz Configuration
	RCC_Config_Load_72MHz(&RCC_Configuration_72MHz);
	// Configuration
	RCC_Config(&RCC_Configuration_72MHz);
}

