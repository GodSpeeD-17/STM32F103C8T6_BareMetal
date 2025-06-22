// Header Guards
#ifndef __RCC_CONFIG_H__
#define __RCC_CONFIG_H__

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
	uint8_t ext_src: 2;
	// Multiplication Factor
	uint8_t mul_fact: 4;
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

// RCC Clock Source
typedef struct {
	// System Clock Frequency
	uint32_t CoreClock;
	// AHB Clock Frequency
	uint32_t AHBClock;
	// APB1 Clock Frequency
	uint32_t APB1Clock;
	// APB2 Clock Frequency
	uint32_t APB2Clock;
} rcc_clk_t;

/**
 * @brief Enables Clock for Alternate Function (AFIO)
 */
__INLINE__ void RCC_AFIO_Clk_Enable(void){
	// Enable AFIO Clock
	RCC->APB2ENR.REG |= RCC_APB2ENR_AFIOEN;
}

/**
 * @brief Disables Clock for Alternate Function (AFIO)
 */
__INLINE__ void RCC_AFIO_Clk_Disable(void){
	// Disable AFIO Clock
	RCC->APB2ENR.REG &= ~RCC_APB2ENR_AFIOEN;
}

/**
 * @brief AHB Prescaler
 */
uint8_t RCC_Get_AHB_Prescaler(void);

/**
 * @brief APB1 Prescaler
 */
uint8_t RCC_Get_APB1_Prescaler(void);

/**
 * @brief APB2 Prescaler
 */
uint8_t RCC_Get_APB2_Prescaler(void);

/**
 * @brief Updates the Core Clock
 * @note This function should be called after any change in the RCC configuration
 * @note Max Frequency: 72MHz 
 */
void RCC_Update_CoreClock();

/**
 * @brief Updates the AHB Clock based upon AHB prescaler (`HPRE`)
 * @note This function should be called after any change in the RCC configuration
 * @note Max Frequency: 72MHz
 */
void RCC_Update_AHBClock();

/**
 * @brief Updates the APB1 Clock based upon APB1 prescaler (`PPRE1`)
 * @note This function should be called after any change in the RCC configuration
 * @note Max Frequency: 36MHz 
 */
void RCC_Update_APB1Clock();

/**
 * @brief Updates the APB2 Clock based upon APB2 prescaler (`PPRE2`)
 * @note This function should be called after any change in the RCC configuration
 * @note Max Frequency: 72MHz 
 */
void RCC_Update_APB2Clock();

/**
 * @brief Retrieves the Core Clock Frequency
 * @return Core Clock Frequency 
 * @note Max Frequency: 72MHz 
 */
uint32_t RCC_Get_CoreClock();

/**
 * @brief Retrieves the AHB Clock Frequency
 * @return AHB Frequency 
 * @note Max Frequency: 72MHz 
 */
uint32_t RCC_Get_AHBClock();

/**
 * @brief Retrieves the APB1 Clock Frequency
 * @return APB1 Frequency 
 * @note Max Frequency: 36MHz
 */
uint32_t RCC_Get_APB1Clock();

/**
 * @brief Retrieves the APB2 Clock Frequency
 * @return APB2 Frequency 
 * @note Max Frequency: 72MHz 
 */
uint32_t RCC_Get_APB2Clock();

#endif /* __RCC_CONFIG_H__ */ 