/***************************************************************************************
 *  File: adc.c
 *  Created on: 12/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

#include "adc.h"

/**
 * @brief Starts the ADC
 */
void start_ADC(ADC_REG_STRUCT* ADCx){

    // SysTick OFF
    if(!(SYSTICK->CSR.BIT.EN)){
        // Configure SysTick as 1ms
        config_SysTick(CoreClock/1000);
    }

    // When the ADON bit is set for the first time, it wakes up the ADC from Power Down mode
	enable_ADC(ADCx);

	// Wait for 100ms
	SysTick_delay_ms(ADC_ON_DELAY_MS);

	// Conversion starts when ADON bit is set for a second time by software after ADC power-up time (tSTAB)
	enable_ADC(ADCx);

}