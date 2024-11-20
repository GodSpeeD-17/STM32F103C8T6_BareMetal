// Main Header
#include "main.h"

// Main Entry Point for User Code
int main(void){
    
    // Configure Clock
    config_SYSCLK_MHz(SYSCLK_MHz);

    // SysTick Timer (1ms)
    config_SysTick(CoreClock/1000);

    // Configure Rising Interrupt LED
    config_GPIO(LED_RISING_PORT, LED_RISING_PIN, MODE_OUT_10MHz, CNF_OUT_GP_PP);
    reset_GPIO(LED_RISING_PORT, LED_RISING_PIN);
    
    // Configure Falling Interrupt LED
    config_GPIO(LED_FALLING_PORT, LED_FALLING_PIN, MODE_OUT_10MHz, CNF_OUT_GP_PP);
    reset_GPIO(LED_FALLING_PORT, LED_FALLING_PIN);

    // On-board LED Configuration
    config_OB_LED();
    reset_OB_LED();

    // Configure Push Button for Rising Edge Interrupt
    config_GPIO(PB_RISING_PORT, PB_RISING_PIN, MODE_IN, CNF_IN_PD);
    config_EXTI(PB_RISING_PORT, PB_RISING_PIN, EXTI_TRIG_RISING, PB_RISING_IRQ_NUM);
    
    // Configure Push Button for Falling Edge Interrupt
    config_GPIO(PB_FALLING_PORT, PB_FALLING_PIN, MODE_IN, CNF_IN_PU);
    config_EXTI(PB_FALLING_PORT, PB_FALLING_PIN, EXTI_TRIG_FALLING, PB_FALLING_IRQ_NUM);

    // Infinite Loop
    while(1){;

        // Toggle On Board LED
        toggle_OB_LED();
        
        // Delay
        SysTick_delay_ms(DELAY_MS);
    }
    
    // Return Value
    return 0;
}

/**
 * @brief IRQ Handler for Px5 - Px9
 */
void EXTI9_5_IRQHandler(void){

    // Push Button Rising Edge Interrupt bit pending
    if(get_EXTI_pend(PB_RISING_PIN)){
        // Acknowledge EXTI Flag
        clear_EXTI_pend(PB_RISING_PIN);
        // Toggle LED
        toggle_GPIO(LED_RISING_PORT, LED_RISING_PIN);
    } 

    // Push Button Falling Edge Interrupt bit pending
    if(get_EXTI_pend(PB_FALLING_PIN)){
        // Acknowledge EXTI Flag
        clear_EXTI_pend(PB_FALLING_PIN);
        // Toggle LED
        toggle_GPIO(LED_FALLING_PORT, LED_FALLING_PIN);
    } 
}
