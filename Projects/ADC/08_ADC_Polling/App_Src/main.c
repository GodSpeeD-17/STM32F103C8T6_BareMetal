// Main Header
#include "main.h"

// Global Variables
uint16_t adc_data[2] = {0};

// Main Entry Point for User Code
int main(void){
	
	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);

	// SysTick Timer (1ms)
	config_SysTick(CoreClock/1000);

	// Configure GPIO as LED
	gpio_config_t led_config = {
		.GPIOx = LED_PORT,
		.PINx = LED_PIN,
		.MODEx = MODE_OUT_10MHz,
		.CNFx = CNF_OUT_GP_PP,
	};
	config_GPIO(&led_config);

	// ADC Configuration Structure
	gpio_config_t pot_config = {
		.GPIOx = POT_PORT,
		.PINx = POT_PIN,
		.MODEx = MODE_IN,
		.CNFx = CNF_IN_ANALOG,
	};
	adc_config_t adc_config = {
		.GPIO_CONFIGx = &pot_config,
		.ADCx = POT_ADC,
		.channel = POT_ADC_CHANNEL,
		.num_channels = 1,
		.sample_time = POT_ADC_SAMPLE_TIME,
		.cc = ADC_CONT_CONV_ON,
		.data_alignment = ADC_DATA_ALIGN_RIGHT,
	};

	// Configure ADC
	config_ADC(&adc_config);

	// Infinite Loop
	while(1){
		// Data Ready
		if(ready_ADC_data(&adc_config)){
			// Read ADC Data
			adc_data[0] = get_ADC_data(&adc_config);
			// ADC Data exceeds the Error Range
			if((adc_data[1] > adc_data[0] + ADC_ERROR_RANGE) || (adc_data[1] < adc_data[0] - ADC_ERROR_RANGE)){
				// Shift the new data
				adc_data[1] = adc_data[0];
				// Status
				toggle_GPIO(&led_config);
			}
		}
		// Loop Delay
		SysTick_delay_ms(DELAY_MS);
	}
	
	// Return Value
	return 0;
}
