// Main Header
#include "main.h"

// Global Variables
volatile uint8_t count = 0x00;
volatile uint8_t configured = 0x00;
volatile uint8_t sync_time = 0x00;
volatile uint64_t last_ticks = 0x00;

// Main Entry Point for User Code
int main(void){
    
    // Configure Clock
    config_SYSCLK_MHz(SYSCLK_MHz);

    // SysTick Timer (1ms)
    config_SysTick(CoreClock/1000);

    // Configure LED
    config_LED(LED_RISING_PORT, LED_RISING_PIN);
    config_LED(LED_FALLING_PORT, LED_FALLING_PIN);
    config_OB_LED();
    reset_OB_LED();

    // Configure Push Button for Rising Edge Interrupt
    config_GPIO(PB_RISING_PORT, PB_RISING_PIN, MODE_IN, CNF_IN_PD);
    config_EXTI(PB_RISING_PORT, PB_RISING_PIN, EXTI_TRIG_RISING, PB_RISING_IRQ_NUM);
    
    // Configure Push Button for Falling Edge Interrupt
    config_GPIO(PB_FALLING_PORT, PB_FALLING_PIN, MODE_IN, CNF_IN_PU);
    config_EXTI(PB_FALLING_PORT, PB_FALLING_PIN, EXTI_TRIG_FALLING, PB_FALLING_IRQ_NUM);

    // Infinite Loop
    while(1){

        // Updates the LED initial state upon Interrupt
        update_configuration();

        // Synchronize Time for Delay
        if(sync_time){
            // Get Current Number of Ticks
            last_ticks = get_curr_ticks();
            // Update Variable
            sync_time = 0x00;
        }

        // Customized Delay for LED Blinking
        if(get_curr_ticks() - last_ticks >= LED_DELAY_MS){

            // Already reference configured
            if(configured){
                // Toggle Decision
                if(count){
                    // GPIO Toggle
                    toggle_GPIO(LED_FALLING_PORT, LED_FALLING_PIN);
                    toggle_GPIO(LED_RISING_PORT, LED_RISING_PIN);
                }
            }

            // Update the reference
            last_ticks = get_curr_ticks();
        }
        
        // Delay
        SysTick_delay_ms(LOOP_DELAY_MS);
    }
    
    // Return Value
    return 0;
}

/**
 * @brief IRQ Handler for Px5 - Px9
 */
void EXTI9_5_IRQHandler(void){

    // On-board LED Toggle
    toggle_OB_LED();

    // Push Button Rising Edge Interrupt bit pending
    if(get_EXTI_pend(PB_RISING_PIN)){
        // Increment Count
        count++;
        // Boundary
        if(count > (uint8_t) 0x03)
            count = 0x00;
        // Acknowledge EXTI Flag
        clear_EXTI_pend(PB_RISING_PIN);
    } 

    // Push Button Falling Edge Interrupt bit pending
    if(get_EXTI_pend(PB_FALLING_PIN)){
        // Decrement Count
        count--;
        // Boundary
        if(count > (uint8_t) 0x03)
            count = 0x03;
        // Acknowledge EXTI Flag
        clear_EXTI_pend(PB_FALLING_PIN);
    }

    // Reset Configuration
    configured = 0x00;
    // Synchronize Time
    sync_time = 0x01;
}

/*
// Basic Individual LED Toggle
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
*/