// Main Header
#include "main.h"

// Global Variables
uint16_t adc_data = 0x0000;

// Main Entry Point for User Code
int main(void){
    
    // Configure Clock
    config_SYSCLK_MHz(SYSCLK_MHz);

    // SysTick Timer (1ms)
    config_SysTick(CoreClock/1000);

    // Configure GPIO as Alternate Function
    RCC_AF_ENABLE();
    config_GPIO(POT_PORT, POT_PIN, MODE_IN, CNF_IN_ANALOG);

    // Configure GPIO as Output
    // config_GPIO(LED_PORT, LED_PIN, MODE_OUT_10MHz, CNF_OUT_GP_PP);

    // Infinite Loop
    while(1){
        // ADC Conversion Complete
        if(POT_ADC->SR.BIT.EOC){
            // Read ADC Value
            adc_data = get_ADC_data(POT_ADC);
        }
    }
    
    // Return Value
    return 0;
}
