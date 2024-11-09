// Main Header
#include "main.h"

// Main Entry Point for User Code
int main(void){
    
    // Configure Clock
    config_SYSCLK_MHz(SYSCLK_MHz);

    // SysTick Timer (1ms)
    config_SysTick(CoreClock/1000);

    // Configure GPIO as Alternate Function
    config_GPIO(POT_PORT, POT_PIN, MODE_IN, CNF_IN_ANALOG);


    // Infinite Loop
    while(1){

    }
    
    // Return Value
    return 0;
}
