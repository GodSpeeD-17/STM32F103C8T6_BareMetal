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

// Bus Prescaler Configuration
typedef struct {
	// APB1 Bus Prescaler 
	// - Max Freq: 36MHz
	uint16_t APB1_pre: 3;
	// APB2 Bus Prescaler 
	// - Max Freq: 72MHz
	uint16_t APB2_pre: 3;
	// AHB Bus Prescaler 
	// - Max Freq: 72MHz
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
	// - Max 48MHz
	// - Clock Source: `PLL`
	uint8_t USB_pre: 1;
	// - ADC Prescaler
	// - Max 14MHz
	// Clock Source: `APB2`
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

/***
 * @brief Retrieves the System Clock Source
 * @note Return Values: `SYS_CLK_HSI`, `SYS_CLK_HSE`, `SYS_CLK_PLL`
 */
__INLINE__ uint8_t RCC_getClkSrc(void){
	// Final Value
	uint8_t value = 0x00;
	// Read the Clock Source
	value = RCC->CFGR.REG & RCC_CFGR_SWS;
	value = (value >> 2); 
	// Return the value
	return value;
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
 * @brief Configures RCC
 * @param configX RCC Configuration Structure
 */
void RCC_Config(rcc_config_t* configX);

void RCC_Config_72MHz();

#endif /* __RCC_H__ */
