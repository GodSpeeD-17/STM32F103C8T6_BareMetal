/***************************************************************************************
 *  File: adc.c
 *  Created on: 12/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

#include "adc.h"

/**
 * @brief Starts the ADC
 * @param[in] ADCx `ADC1`, `ADC2`, `ADC3`
 * @param[in] channel `ADC_CHx`
 * @param[in] cc `ADC_CONT_CONV_ON`, `ADC_CONT_CONV_OFF`
 */
void config_ADC(ADC_REG_STRUCT* ADCx, uint8_t channel, uint8_t cc){

    // Enable Clock for ADC
    enable_ADC_clk(ADCx);

    // Calibration of ADC
    cal_ADC(ADCx);

    // Clear the Control Register
    ADCx->CR2.REG = (uint32_t) 0x00000000;

    // Setup Channel
    ADCx->SQR3.REG = channel;

    // When the ADON bit is set for the first time, it wakes up the ADC from Power Down mode
	enable_ADC(ADCx);

	// Wait for for time (tSTAB)
	for(volatile uint16_t demo = 0; demo <= ADC_ON_DELAY; demo++);

	// Conversion starts when ADON bit is set for a second time by software after ADC power-up time (tSTAB)
	enable_ADC(ADCx);

    // Enable/Disable Continuos Conversion
    ADCx->CR2.BIT.CONT = cc;
}
