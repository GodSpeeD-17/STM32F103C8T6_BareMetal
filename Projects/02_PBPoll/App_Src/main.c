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

    // Configure Push Button as Input
    config_GPIO(IRQ_PORT, IRQ_PIN, MODE_IN, CNF_IN_PD);
    
    // Infinite Loop
    while(1){

        // Push Button Pressed
        if(get_GPIO(IRQ_PORT, IRQ_PIN)){
            // LED ON
            set_GPIO(LED_PORT, LED_PIN);
        }
        // Push Button Released
        else{
            // LED OFF
            reset_GPIO(LED_PORT, LED_PIN);
        }

        // Delay
        SysTick_delay_ms(DELAY_MS);
    }
    
    // Return Value
    return 0;
}


void IRQHandler(){

}