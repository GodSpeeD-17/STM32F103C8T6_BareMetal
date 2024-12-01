/***************************************************************************************
 *  File: adc.c
 *  Created on: 12/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/
// Header File
#include "adc.h"

/**
 * @brief Starts the ADC
 * @param[in] ADCx `ADC1`, `ADC2`, `ADC3`
 * @param[in] channel `ADC_CHANNEL_x`
 * @param[in] cc `ADC_CONT_CONV_ON`, `ADC_CONT_CONV_OFF`
 */
void config_ADC(ADC_REG_STRUCT* ADCx, uint8_t channel, uint8_t cc){
    // Enable Clock for ADC
    enable_ADC_clk(ADCx);
    // Clear the Control Register, Sample Time Register, Regular Sequence Register
    ADCx->CR2.REG = (uint32_t) 0x00000000;
    ADCx->SMPR2.REG = (uint32_t) 0x000000;
    ADCx->SQR1.REG = (uint32_t) 0x000000;
    ADCx->SQR3.REG = (uint32_t) 0x000000;
    // Set Maximum Sampling time for ADC Channel
    ADCx->SMPR2.REG |= (0x07 << (channel * 3));
    // Set number of Channel Conversion (0x00 = 1 conversion)
    ADCx->SQR1.REG |= (0x00 << 20);
    // Setup Channel Sequence for Conversion
    ADCx->SQR3.REG |= channel;
    // Enable/Disable Continuous Conversion
    ADCx->CR2.BIT.CONT = cc;
    // When the ADON bit is set for the first time, it wakes up the ADC from Power Down mode
	enable_ADC(ADCx);
	// Wait for for time (tSTAB)
	for(volatile uint16_t demo = 0; demo <= ADC_ON_DELAY; demo++);
    // When the ADON bit is set for the first time, it wakes up the ADC from Power Down mode
	enable_ADC(ADCx);
    // Calibration of ADC
    calibrate_ADC(ADCx);
}

/**
 * @brief Retrieves the 12-bit ADC Data
 * @returns ADC Data
 * @note - Assumed that ADC data is right aligned
 * @note - Conversion starts when this bit holds a value of 1 and a 1 is written to it.
 */
uint16_t get_ADC_raw_data(ADC_REG_STRUCT* ADCx){
	// Final Result
	uint16_t result;
    // Start the conversion using Software as Trigger
    ADCx->CR2.REG |= (1 << 22);
    // Wait for End of Conversion
    while(!ADCx->SR.BIT.EOC);
    // Read the ADC Data (Generally, It is cleared by software or by reading the ADC_DR)
	result = (ADCx->DR.REG & 0x0FFF);
    // Just for backup
    ADCx->CR2.REG &= ~(1 << 22);
    ADCx->SR.BIT.EOC = BIT_RESET;
    // 12-bit ADC Data
    return (result & 0x0FFF);
}
