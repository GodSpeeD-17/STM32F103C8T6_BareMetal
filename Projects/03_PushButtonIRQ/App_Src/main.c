// Main Header
#include "main.h"

// Main Entry Point for User Code
int main(void){
    
    // Configure Clock
    config_SYSCLK_MHz(SYSCLK_MHz);

    // SysTick Timer (1ms)
    config_SysTick(CoreClock/1000);

    // Configure LED
    config_GPIO(LED_PORT, LED_PIN, MODE_OUT_10MHz, CNF_OUT_GP_PP);
    reset_GPIO(LED_PORT, LED_PIN);

    // Infinite Loop
    while(1){

    }
    
    // Return Value
    return 0;
}
