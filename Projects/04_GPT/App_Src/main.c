// Main Header
#include "main.h"

// Main Entry Point for User Code
int main(void){
    
    // Configure Clock (72 MHz)
    config_SYSCLK_MHz(SYSCLK_MHz);

    // SysTick Timer (1ms)
    config_SysTick(CoreClock/1000);

    // Initialize External LED
    config_GPIO(LED_PORT, LED_PIN, MODE_OUT_10MHz, CNF_OUT_GP_PP);
    reset_GPIO(LED_PORT, LED_PIN);

    // Initialise On-board LED
    config_OB_LED();
    reset_OB_LED();

    // Enable Clock for Timer
    enable_GPT_clk(GP_TIMER);

    // Configure Timer for 1ms
    config_GPT(GP_TIMER, GPT_ARR, GPT_FREQ, GPT_CNT);

    // Enable Timer
    enable_GPT(GP_TIMER);

    // Infinite Loop
    while(1){

        // Toggle external LED
        toggle_GPIO(LED_PORT, LED_PIN);

        // Delay using SysTick
        GPT_delay_ms(GP_TIMER, DELAY_MS);

        // Toggle Onboard LED
        toggle_OB_LED();

    }
    
    // Return Value
    return 0;
}
