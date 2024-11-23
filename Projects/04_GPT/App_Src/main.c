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

    // GPT Configuration Structure
    gpt_config_t gpt_config = {
        .GP_TIMx = GP_TIMER,
        .channel = GPT_CHANNEL,
        .auto_reload_value = GPT_ARR,
        .frequency_Hz = GPT_FREQ,
        .count = GPT_CNT,
        .cms_mode = CMS_EDGE,
        .direction = TIMx_COUNT_UP,
        .auto_reload_preload = TIMx_ARPE_ENABLE,
        .one_pulse = TIMx_OPM_DISABLE,
    };

    // Configures the GPT as per the input parameters
    config_GPT(&gpt_config);

    // Enable the GPT
    enable_GPT(&gpt_config);

    // Initialise On-board LED
    config_OB_LED();
    reset_OB_LED();

    // Infinite Loop
    while(1){
        // Toggle external LED
        toggle_GPIO(LED_PORT, LED_PIN);
        // Delay using SysTick
        GPT_delay_ms(&gpt_config, DELAY_MS);
        // Toggle Onboard LED
        toggle_OB_LED();
    }
    
    // Return Value
    return 0;

}
