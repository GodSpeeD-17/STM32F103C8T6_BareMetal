/***************************************************************************************
 *  File: adc.h
 *  Created on: 01/12/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __ADC_H__
#define __ADC_H__

// Dependency
#include "reg_map.h"
#include "gpio.h"			// For Configuration
#include "nvic.h"			// For IRQ Handling

// Wait time for stabilize (tSTAB)
#define ADC_ON_DELAY						((uint16_t) 10)

// ADC Channel Sequence
typedef struct {
	// Channel Sequence 1
	uint8_t channel_seq_1;
	// Channel Sequence 2
	uint8_t channel_seq_2;
	// Channel Sequence 3
	uint8_t channel_seq_3;
	// Channel Sequence 4
	uint8_t channel_seq_4;
	// Channel Sequence 5
	uint8_t channel_seq_5;
	// Channel Sequence 6
	uint8_t channel_seq_6;
	// Channel Sequence 7
	uint8_t channel_seq_7;
	// Channel Sequence 8
	uint8_t channel_seq_8;
	// Channel Sequence 9
	uint8_t channel_seq_9;
	// Channel Sequence 10
	uint8_t channel_seq_10;
	// Channel Sequence 11
	uint8_t channel_seq_11;
	// Channel Sequence 12
	uint8_t channel_seq_12;
} adc_sequence_t;

// ADC Configuration Structure
typedef struct {
	// GPIO Configuration
	gpio_config_t* GPIO_CONFIGx;
	// ADC Number
	ADC_REG_STRUCT* ADCx;
	// ADC Channel
	uint8_t channel;
	// Number of Channels
	uint8_t num_channels;
	// Sample Time
	uint8_t sample_time;
	// Continuous Conversion Mode
	uint8_t cc;
	// ADC Data Alignment
	uint8_t data_alignment;
	// IRQ Enable/Disable
	uint8_t enable_IRQ;
} adc_config_t;

/**
 * @brief Enables the Clock for Analog to Digital Converter (ADC)
 * @param[in] ADCx `ADC1`, `ADC2`, `ADC3`
 * @note RCC->APB2ENR
 */
__attribute__((always_inline)) inline void enable_ADC_clk(ADC_REG_STRUCT* ADCx){
	// Enable the clock for the ADC
	if(ADCx == ADC1)
		RCC->APB2ENR.BIT.ADC1EN = BIT_SET;
	else if(ADCx == ADC2)
		RCC->APB2ENR.BIT.ADC2EN = BIT_SET;
}

/**
 * @brief Disables the Clock for Analog to Digital Converter (ADC)
 * @param[in] ADCx `ADC1`, `ADC2`, `ADC3`
 * @note RCC->APB2ENR
 */
__attribute__((always_inline)) inline void disable_ADC_clk(ADC_REG_STRUCT* ADCx){
	// Disable the clock for the ADC
	if(ADCx == ADC1)
		RCC->APB2ENR.BIT.ADC1EN = BIT_RESET;
	else if(ADCx == ADC2)
		RCC->APB2ENR.BIT.ADC2EN = BIT_RESET;
}

/**
 * @brief Enables the Analog to Digital Converter (ADC)
 * @param[in] ADCx `ADC1`, `ADC2`, `ADC3`
 */
__attribute__((always_inline)) inline void enable_ADC(ADC_REG_STRUCT* ADCx){
	// Enable ADC
	ADCx->CR2.REG |= BIT_SET;  
}

/**
 * @brief Disables the Analog to Digital Converter (ADC)
 * @param[in] ADCx `ADC1`, `ADC2`, `ADC3`
 */
__attribute__((always_inline)) inline void disable_ADC(ADC_REG_STRUCT* ADCx){
	// Disable the ADC
	ADCx->CR2.REG &= ~BIT_SET;
}

/**
 * @brief ADC Calibration 
 * @param[in] ADCx `ADC1`, `ADC2`, `ADC3` 
 * @note - It is recommended to perform a calibration after each power-up
 * @note - Before starting a calibration, the ADC must have been in power-on state for at least two ADC clock cycles
 */
__attribute__((always_inline)) inline void calibrate_ADC(ADC_REG_STRUCT* ADCx){
	// Initialise Calibration Registers
	ADCx->CR2.REG |= (1 << 3);
	// Cleared after the Calibration Registers are Initialized
	while((ADCx->CR2.REG & (1 << 3)));
	// Start the Calibration
	ADCx->CR2.REG |= (1 << 2);
	// Reset by Hardware after Calibration is Complete
	while((ADCx->CR2.REG & (1 << 2)));
}

/**
 * @brief Starts the ADC based upon the sequence
 * @param[in] ADCx `ADC1`, `ADC2`, `ADC3`
 */
__attribute__((always_inline)) inline void start_ADC(ADC_REG_STRUCT* ADCx){
	// When the ADON bit is set for the first time, it wakes up the ADC from Power Down mode
	// If this bit holds a value of 0 and a 1 is written to it then it wakes up the ADC from Power Down state
	enable_ADC(ADCx);
	// Wait for for time (tSTAB)
	for(volatile uint16_t tSTAB_delay = 0; tSTAB_delay <= ADC_ON_DELAY; tSTAB_delay++);
	// Calibrate the ADC
	calibrate_ADC(ADCx);
	// Conversion starts when ADON bit is set for a second time by software after ADC power-up time (tSTAB)
	// Conversion starts when this bit holds a value of 1 and a 1 is written to it
	enable_ADC(ADCx);
}

/**
 * @brief Enables the ADC Clock
 * @param[in] ADC_CONFIGx ADC configuration structure
 */
void config_ADC(adc_config_t* ADC_CONFIGx);

/**
 * @brief Status of ADC
 * @param[in] ADC_CONFIGx ADC configuration structure
 */
__attribute__((always_inline)) inline uint8_t ready_ADC_data(adc_config_t* ADC_CONFIGx){
	// Result
	uint8_t result = 0xFF;
	// Check if ADC is ready
	result = (uint8_t)(ADC_CONFIGx->ADCx->SR.REG & 0x02);
	// Return the value
	return result;
}

/**
 * @brief Returns the IRQn of ADCx 
 * @param[in] ADC_CONFIGx ADC configuration structure
 */
__attribute__((always_inline)) inline uint8_t get_ADC_IRQn(adc_config_t* ADC_CONFIGx){
	// Return the value based upon the ADC Number
	if((ADC_CONFIGx->ADCx == ADC1) || (ADC_CONFIGx->ADCx == ADC2))
		return ADC1_2_IRQn;
	else if(ADC_CONFIGx->ADCx == ADC3)
		return ADC3_IRQn;
}

/**
 * @brief Retrieves the 12-bit ADC Raw Data
 * @param[in] ADC_CONFIGx ADC configuration structure
 * @returns ADC Raw Data
 */
uint16_t get_ADC_data(adc_config_t* ADC_CONFIGx);

#endif /* __ADC_H__ */
