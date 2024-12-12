/***************************************************************************************
 *  File: adc.c
 *  Created on: 01/12/2024
 *  Author: Shrey Shah
 ***************************************************************************************/
// TO DO: Use adc_sequence_t and develop a logic to read the data as per sequence using SQRx Registers

// Header File
#include "adc.h"

/**
 * @brief Configures the ADC based upon ADC Configuration Structure
 * @param[in] ADC_CONFIGx ADC Configuration Structure
 */
void config_ADC(adc_config_t* ADC_CONFIGx){
	
	// Enable Clock for ADC
	enable_ADC_clk(ADC_CONFIGx->ADCx);
	// Disable the ADC if already ON
	disable_ADC(ADC_CONFIGx->ADCx);
	// Configure GPIO
	config_GPIO(ADC_CONFIGx->GPIO_CONFIGx);

	// Reset Registers
	ADC_CONFIGx->ADCx->CR2.REG = (uint32_t) 0x00000000;
	ADC_CONFIGx->ADCx->SMPR2.REG = (uint32_t) 0x000000;
	ADC_CONFIGx->ADCx->SQR1.REG = (uint32_t) 0x000000;
	ADC_CONFIGx->ADCx->SQR2.REG = (uint32_t) 0x000000;
	ADC_CONFIGx->ADCx->SQR3.REG = (uint32_t) 0x000000;

	// Sampling Time
	ADC_CONFIGx->ADCx->SMPR2.REG |= ((ADC_SAMPLE_TIME(ADC_CONFIGx->sample_time) & 0x07) << (ADC_SAMPLE_CHANNEL(ADC_CONFIGx->sample_time) * 3));
	// Number of Channel for Conversion
	ADC_CONFIGx->ADCx->SQR1.REG |= ((ADC_CONFIGx->num_channels - 1) << 20);
	// Configure Channel Sequence
	if(ADC_CONFIGx->num_channels == 1){
		ADC_CONFIGx->ADCx->SQR3.REG |= ADC_CONFIGx->channel;
	}
	// ADC Data Alignment
	ADC_CONFIGx->ADCx->CR2.REG |= ((ADC_CONFIGx->data_alignment & 0x01) << 11);
	// Continuous Conversion
	ADC_CONFIGx->ADCx->CR2.REG |= ((ADC_CONFIGx->cc & 0x01) << 1);
	// IRQ Configuration
	if(ADC_CONFIGx->enable_IRQ == (ADCx_IRQ_ENABLE)){
		// Enable the IQR Bit
		ADC_CONFIGx->ADCx->CR1.REG |= (1 << 5);
		// Enable NVIC IRQ
		enable_NVIC_IRQ(get_ADC_IRQn(ADC_CONFIGx));
	}
	// Starts the ADC
	start_ADC(ADC_CONFIGx->ADCx);
}

/**
 * @brief Retrieves the 12-bit ADC Data
 * @param[in] ADC_CONFIGx ADC Configuration Structure
 * @returns ADC Data
 */
uint16_t get_ADC_data(adc_config_t* ADC_CONFIGx){
	// Result
	uint16_t result = 0;
	// Read the data register
	result = ADC_CONFIGx->ADCx->DR.REG;
	// Data is Right Aligned
	if(ADC_CONFIGx->data_alignment == ADC_DATA_ALIGN_RIGHT)
		result &= 0x0FFF;
	// Data is Left Aligned
	else
		result &= 0xFFF0;
	// Return the result
	return result; 
}
