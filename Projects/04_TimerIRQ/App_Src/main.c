// Main Header
#include "main.h"

// Status Flag
uint8_t toggle_led = 0xFF, toggle_OB_led = 0x00;

// Main Entry Point for User Code
int main(void){

    // Configure Clock
    config_SYSCLK_MHz(SYSCLK_MHz);

    // SysTick Timer (1ms)
    config_SysTick(CoreClock/1000);

    // Configure GPIO
    config_GPIO(LED_PORT, LED_PIN, MODE_OUT_10MHz, CNF_OUT_GP_PP);
    reset_GPIO(LED_PORT, LED_PIN);

    // Configure OB LED
    config_OB_LED();
    set_OB_LED();

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

    // Enable NVIC Interrupt
    enable_NVIC_IRQ(TIMER_IRQn);

    // Enable Timer
    enable_GPT(GP_TIMER);

    // Infinite Loop
    while(1){

    	if(toggle_led){
    		toggle_GPIO(LED_PORT, LED_PIN);
    		toggle_led = 0x00;
    	}

    	if(toggle_OB_led){
    		toggle_OB_LED();
    		toggle_OB_led = 0x00;
    	}
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
        toggle_led = 0xFF;
        toggle_OB_led = 0xFF;
    }
}
