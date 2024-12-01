/***************************************************************************************
 *  File: adc.h
 *  Created on: 09/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __ADC_H__
#define __ADC_H__

// Dependency
#include "reg_map.h"
#include "gpio.h"

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
	// GPIOx
	GPIO_REG_STRUCT* GPIOx;
	// PIN
	uint8_t PINx;
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

} adc_config_t;

/**
 * @brief Enables the Clock for Analog to Digital Converter (ADC)
 * @param[in] ADCx `ADC1`, `ADC2`, `ADC3`
 * @note RCC->APB2ENR
 */
inline __attribute__((always_inline)) void enable_ADC_clk(ADC_REG_STRUCT* ADCx){
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
inline __attribute__((always_inline)) void disable_ADC_clk(ADC_REG_STRUCT* ADCx){
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
inline __attribute__((always_inline)) void enable_ADC(ADC_REG_STRUCT* ADCx){
	// Enable ADC
	ADCx->CR2.REG |= BIT_SET;  
}

/**
 * @brief Disables the Analog to Digital Converter (ADC)
 * @param[in] ADCx `ADC1`, `ADC2`, `ADC3`
 */
inline __attribute__((always_inline)) void disable_ADC(ADC_REG_STRUCT* ADCx){
	// Disable the ADC
	ADCx->CR2.REG &= ~BIT_SET;
}

/**
 * @brief ADC Calibration 
 * @param[in] ADCx `ADC1`, `ADC2`, `ADC3` 
 * @note - It is recommended to perform a calibration after each power-up
 * @note - Before starting a calibration, the ADC must have been in power-on state for at least two ADC clock cycles
 */
inline __attribute__((always_inline)) void calibrate_ADC(ADC_REG_STRUCT* ADCx){
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
 * @brief Starts the ADC
 * @param[in] ADCx `ADC1`, `ADC2`, `ADC3`
 * @param[in] channel `ADC_CHANNEL_x`
 * @param[in] cc `ADC_CONT_CONV_ON`, `ADC_CONT_CONV_OFF`
 */
void init_ADC(ADC_REG_STRUCT* ADCx, uint8_t channel, uint8_t cc);


void config_ADC(adc_config_t* ADC_CONFIGx);

/**
 * @brief Retrieves the 12-bit ADC Data
 * @returns ADC Data
 */
uint16_t get_ADC_raw_data(ADC_REG_STRUCT* ADCx);


#endif /* __ADC_H__ */
