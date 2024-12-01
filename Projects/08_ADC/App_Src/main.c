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

    // Infinite Loop
    while(1){
        // Loop Delay
        SysTick_delay_ms(DELAY_MS);
    }
    
    // Return Value
    return 0;
}
