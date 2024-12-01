// Main Header
#include "main.h"

// Main Entry Point for User Code
int main(void){
	// Global Variables
	uint16_t adc_data[2] = {0};

    // Configure Clock
    config_SYSCLK_MHz(SYSCLK_MHz);

    // SysTick Timer (1ms)
    config_SysTick(CoreClock/1000);

    // Configure GPIO as LED
    config_LED(LED_PORT, LED_PIN);

    // ADC Configuration Structure
    adc_config_t adc_config = {
        .GPIOx = POT_PORT,
        .PINx = POT_PIN,
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
            adc_data[0] = get_ADC_raw_data(&adc_config);
            // Range +- 10
            if((adc_data[1] > adc_data[0] + ADC_ERROR_RANGE) || (adc_data[1] < adc_data[0] - ADC_ERROR_RANGE)){
                // Shift the new data
                adc_data[1] = adc_data[0];
                // Status
                toggle_GPIO(LED_PORT, LED_PIN);
            }
        }
        // Loop Delay
        SysTick_delay_ms(DELAY_MS);
    }
    
    // Return Value
    return 0;
}
