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

    // Configure GPIO as Input Analog
    config_GPIO(POT_PORT, POT_PIN, MODE_IN, CNF_IN_ANALOG);
    config_ADC(POT_ADC, POT_ADC_CHANNEL, ADC_CONT_CONV_ON);

    // Configure GPIO as LED
    config_LED(LED_PORT, LED_PIN);

    // Infinite Loop
    while(1){
        // ADC Conversion Complete
        adc_data[0] = get_ADC_raw_data(POT_ADC);
        // New data
        if(adc_data[1] != adc_data[0]){
            // Store Value
            adc_data[1] = adc_data[0];
            // Toggle LED
            toggle_GPIO(LED_PORT, LED_PIN);
        }
        // Loop Delay
        SysTick_delay_ms(DELAY_MS);
    }
    
    // Return Value
    return 0;
}
