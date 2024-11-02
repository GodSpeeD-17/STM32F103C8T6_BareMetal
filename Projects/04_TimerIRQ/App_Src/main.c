// Main Header
#include "main.h"

// Main Entry Point for User Code
int main(void){
    
    // Configure Clock
    config_SYSCLK_MHz(SYSCLK_MHz);

    // SysTick Timer (1ms)
    config_SysTick(CoreClock/1000);

    // Configure GPIO
    config_GPIO(LED_PORT, LED_PIN, MODE_OUT_10MHz, CNF_OUT_GP_PP);
    reset_GPIO(LED_PORT, LED_PIN);

    // Error Check
    IS_TIMx_GPT(GP_TIMER);

    // Enable Timer Clock
    enable_GPT_clk(GP_TIMER);

    // Disable Timer
    disable_GPT(GP_TIMER);

    // Reset Timer
    reset_GPT(GP_TIMER);

    // Configure Timer
    config_GPT(GP_TIMER, TIMER_ARR, TIMER_FREQ, TIMER_CNT);

    // Enable Timer Interrupt
    enable_GPT_IRQ(GP_TIMER);

    // Enable Timer
    enable_GPT(GP_TIMER);

    // Enable NVIC Interrupt
    enable_NVIC_IRQ(TIMER_IRQn);

    // Infinite Loop
    while(1){

    }
    
    // Return Value
    return 0;
}

/**
 * @brief TIM2 IRQ Handler
 */
void TIM2_IRQHandler(void){
    // Clear the already Set Update Interrupt Flag
    if(TIM2->SR.BIT.UIF){
        // Clear
        TIM2->SR.BIT.UIF = BIT_RESET;
        // Toggle GPIO
        toggle_GPIO(LED_PORT, LED_PIN);
    }
}