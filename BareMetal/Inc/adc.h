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
#include "systick.h"

// System Clock Frequency (Core)
extern volatile uint32_t CoreClock;

#define ADC_ON_DELAY_MS			((uint32_t) 100)

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
	if(ADCx == ADC1)
		ADC1->CR2.BIT.ADON = BIT_SET;
	else if(ADCx == ADC2)
		ADC2->CR2.BIT.ADON = BIT_SET;  
}

/**
 * @brief Disables the Analog to Digital Converter (ADC)
 * @param[in] ADCx `ADC1`, `ADC2`, `ADC3`
 */
inline __attribute__((always_inline)) void disable_ADC(ADC_REG_STRUCT* ADCx){
	// Disable the ADC
	if(ADCx == ADC1)
		ADC1->CR2.BIT.ADON = BIT_RESET;
	else if(ADCx == ADC2)
		ADC2->CR2.BIT.ADON = BIT_RESET;
}

/**
 * @brief ADC Calibration 
 * @param[in] ADCx `ADC1`, `ADC2`, `ADC3` 
 * @note - It is recommended to perform a calibration after each power-up
 * @note - Before starting a calibration, the ADC must have been in power-on state for at least two ADC clock cycles
 */
inline __attribute__((always_inline)) void cal_ADC(ADC_REG_STRUCT* ADCx){
    // Start the Calibration
    ADCx->CR2.BIT.CAL = BIT_SET;
    // Reset by Hardware after Calibration is Complete
    while(!(ADCx->CR2.BIT.CAL));
}




#endif /* __ADC_H__ */