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
} rcc_config_t;

/***
 * @brief Retrieves the System Clock Source
 * @note Return Values: `SYS_CLK_HSI`, `SYS_CLK_HSE`, `SYS_CLK_PLL`
 */
__attribute__((always_inline)) inline uint8_t get_clock_source(void){
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
uint32_t get_clock_freq(void);

/**
 * @brief Retrieves the frequency of AHB
 * @return AHB Frequency (in Hz)
 */
uint32_t get_AHB_freq(void);

/**
 * @brief Retrieves the frequency of the APB1
 * @return APB1 Frequency (in Hz)
 * @note Max Value should not exceed more than 36MHz
 */
uint32_t get_APB1_freq(void);

/**
 * @brief Retrieves the frequency of the APB2
 * @return APB2 Frequency (in Hz)
 */
uint32_t get_APB2_freq(void);

/**
 * @brief Configures PLL parameters
 * @param[in] PLL_SRC PLL Input Source
 * @param[in] PLL_MUL PLL Multiplication Factor
 */
static void config_PLL(PLL_CLK_SRC_ENUM PLL_SRC, uint8_t PLL_MUL);

/**
 * @brief Updates the Peripheral Bus Prescaler
 * @param[in] AHB_PRE  AHB Prescaler `AHB_DIV_X`
 * @param[in] APB1_PRE APB1 Prescaler `APB1_DIV_X`
 * @param[in] APB2_PRE APB2 Prescaler `APB2_DIV_X`
 */
__attribute__((always_inline)) inline void config_BUS(uint8_t AHB_PRE, uint8_t APB1_PRE, uint8_t APB2_PRE){

	// AHB Prescaler
	RCC->CFGR.BIT.HPRE = AHB_PRE;

	// APB2 Prescaler (Faster Bus)
	RCC->CFGR.BIT.PPRE2 = APB2_PRE;

	// APB1 Prescaler (Slower Bus)
	RCC->CFGR.BIT.PPRE1 = APB1_PRE;
}

/**
 * @brief Reference Working Code
 */
static void config_SYS_72MHz(void);

/**
 * @brief Wrapper Function to create abstraction for System Core Clock Updation
 * @param[in] CLK_FREQ Core Clock Frequency `SYSCLK_FREQ`
 * @note - PLL as System Clock Source 
 * @note - HSE is used for PLL Clock Source
 */
void config_SYSCLK_MHz(SYSCLK_FREQ CLK_FREQ);

#endif /* __RCC_H__ */
