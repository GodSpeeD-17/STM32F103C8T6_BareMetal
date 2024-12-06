// Header Guards
#ifndef __ADC_PWM_H__
#define __ADC_PWM_H__

#include "bare_metal.h"

/**
 * @brief Calculates Duty Cycle based upon input ADC Value
 * @param[in] adc_value 12-bit ADC Value
 */
__attribute__((always_inline)) inline uint8_t calc_PWM_ADC(uint16_t adc_value){
	// Wrap ADC Value to ensure it is in 12-bit range
	adc_value &= 0x0FFF;
	// Calculate Duty Cycle
	uint32_t result = (((uint32_t)adc_value * MAX_DUTY_CYCLE) / MAX_ADC_VALUE);
	// Return the result except when it is 0 (0 causes the LED to be always ON)
	return (uint8_t)((result < MIN_DUTY_CYCLE)? MIN_DUTY_CYCLE : result);
}

#endif /* __ADC_PWM_H__ */