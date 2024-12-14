// Main Header
#include "main.h"

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
	.enable_IRQ = ADCx_IRQ_ENABLE,
};

// Global Variables
volatile uint8_t adc_conversion_complete = 0x00;
volatile uint16_t adc_data[2] = {0};

// Main Entry Point for User Code
int main(void){
	
	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);

	// SysTick Timer (1ms)
	config_SysTick(CoreClock/1000);

	
	// Configure ADC
	config_ADC(&adc_config);

	// On-board LED Configuration
	config_OB_LED();
	reset_OB_LED();

	// Infinite Loop
	while(1){

		// ADC Conversion Completed
		if(adc_conversion_complete){
			// Read ADC data
			adc_data[0] = get_ADC_data(&adc_config);
			// ADC Data exceeds the Error Range
			if ((adc_data[0] > (adc_data[1] + ADC_ERROR_RANGE)) || (adc_data[0] < (adc_data[1] - ADC_ERROR_RANGE))){
				// Shift the new data
				adc_data[1] = adc_data[0];
				// Toggle OB LED
				toggle_OB_LED();
			}
		}
		
		// Loop Delay
		SysTick_delay_ms(DELAY_MS);
	}
		
	// Return Value
	return 0;
}

/**
 * @brief ADC1/ADC2 IRQ Handler
 */
void ADC1_2_IRQHandler(void){
	if(get_ADC_EOC_flag(adc_config.ADCx)){
		// Flag
		adc_conversion_complete = 0x01;
		// Clear the EOC Flag
		clear_ADC_EOC_flag(adc_config.ADCx);
	}
}