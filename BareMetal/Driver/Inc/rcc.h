/***************************************************************************************
 *  File: rcc.h
 *  Created on: 14/09/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __RCC_H__
#define __RCC_H__

// Register Address Mapping
#include "reg_map.h"

// Shortcut Macro
#define RCC_Config_72MHz()							(RCC_Config(&RCC_Configuration_72MHz))

// Bus Prescaler Configuration
typedef struct {
	// APB1 Bus Prescaler 
	// Max 36MHz
	uint16_t APB1_pre: 3;
	// APB2 Bus Prescaler 
	// Max 72MHz
	uint16_t APB2_pre: 3;
	// AHB Bus Prescaler 
	// Max 72MHz
	uint16_t AHB_pre: 4;
} bus_config_t;

// PLL Configuration
typedef struct {
	// External Source
	uint8_t ext_src;
	// External Source Prescaler
	uint8_t ext_src_pre;
	// Multiplication Factor
	uint8_t mul_fact;
} pll_config_t;

// Internal Components Clock Configuration
typedef struct {
	// USB Prescaler
	// Max 48MHz
	// Clock Source: PLL
	uint8_t USB_pre: 1;
	// ADC Prescaler
	// Max 14MHz
	// Clock Source: APB2
	uint8_t ADC_pre: 2;
} component_config_t;

// RCC Configuration Structure
typedef struct {
	// Flash Configuration
	flash_config_t flash;
	// PLL Configuration
	pll_config_t pll;
	// Bus Prescaler Configuration
	bus_config_t bus;
	// Components Prescaler
	component_config_t component;
	// System Clock Source
	uint8_t sys_clk_src;
} rcc_config_t;

// Configuration: 72MHz
static const rcc_config_t RCC_Configuration_72MHz = {
	// System Clock Source
	.sys_clk_src = SW_CLK_PLL,
	// Flash Configuration
	.flash = {
		.latency = FLASH_ACR_LATENCY_2,
		.prefetch = FLASH_ACR_PRFTBE_Msk,
	},
	// PLL Configuration
	.pll = {
		.ext_src = PLL_SRC_HSE,
		.ext_src_pre = PLL_HSE_DIV_1,
		.mul_fact = PLL_MUL_9,
	},
	// Bus Configuration
	.bus = {
		.APB1_pre = APB1_DIV_2,
		.APB2_pre = APB2_DIV_1,
		.AHB_pre = AHB_DIV_1
	},
	// Components Configuration
	.component = {
		.ADC_pre = ADC_DIV_6,
		.USB_pre = USB_DIV_1_5,
	},
};

/***
 * @brief Retrieves the System Clock Source
 * @note Return Values: `SYS_CLK_HSI`, `SYS_CLK_HSE`, `SYS_CLK_PLL`
 */
__INLINE__ uint8_t RCC_getClkSrc(void){
	// Final Value
	uint8_t value = 0xFF;
	// Read the Clock Source
	value = (uint8_t)(RCC->CFGR.REG & RCC_CFGR_SWS_Msk);
	// Return the value
	return (value >> 2);
}

/**
 * @brief Retrieves the current System Clock
 * @return SYSCLK Frequency (in Hz)
 */
uint32_t RCC_getClkFreq(void);

/**
 * @brief Retrieves the frequency of AHB
 * @return AHB Frequency (in Hz)
 */
uint32_t RCC_getAHBFreq(void);

/**
 * @brief Retrieves the frequency of the APB1
 * @return APB1 Frequency (in Hz)
 * @note Max Value should not exceed more than 36MHz
 */
uint32_t RCC_getAPB1Freq(void);

/**
 * @brief Retrieves the frequency of the APB2
 * @return APB2 Frequency (in Hz)
 */
uint32_t RCC_getAPB2Freq(void);

/**
 * @brief Configures PLL parameters
 * @param[in] PLL_SRC PLL Input Source
 * @param[in] PLL_MUL PLL Multiplication Factor
 */
static void RCC_PLL_config(PLL_CLK_SRC_ENUM PLL_SRC, uint8_t PLL_MUL);

/**
 * @brief Updates the Peripheral Bus Prescaler
 * @param[in] AHB_PRE  AHB Prescaler `AHB_DIV_X`
 * @param[in] APB1_PRE APB1 Prescaler `APB1_DIV_X`
 * @param[in] APB2_PRE APB2 Prescaler `APB2_DIV_X`
 */
__INLINE__ void RCC_busConfig(uint8_t AHB_PRE, uint8_t APB1_PRE, uint8_t APB2_PRE){

	// AHB Prescaler
	RCC->CFGR.BIT.HPRE = AHB_PRE;

	// APB2 Prescaler (Faster Bus)
	RCC->CFGR.BIT.PPRE2 = APB2_PRE;

	// APB1 Prescaler (Slower Bus)
	RCC->CFGR.BIT.PPRE1 = APB1_PRE;
}

/**
 * @brief Configures RCC
 * @param configX RCC Configuration Structure
 */
void RCC_Config(rcc_config_t* configX);

#endif /* __RCC_H__ */
