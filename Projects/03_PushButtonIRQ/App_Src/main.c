// Main Header
#include "main.h"

// Variables
uint8_t volatile button_pressed = 0x00;

// Main Entry Point for User Code
int main(void){
    
    // Configure Clock
    config_SYSCLK_MHz(SYSCLK_MHz);

    // SysTick Timer (1ms)
    config_SysTick(CoreClock/1000);

    // Configure LED
    config_GPIO(LED_PORT, LED_PIN, MODE_OUT_10MHz, CNF_OUT_GP_PP);
    reset_GPIO(LED_PORT, LED_PIN);

    // Configure Push Button for Interrupts
    config_GPIO(IRQ_PORT, IRQ_PIN, MODE_IN, CNF_IN_PD);
    config_EXTI(IRQ_PORT, IRQ_PIN, EXTI_TRIG_RISING, IRQ_NUM);

    // Infinite Loop
    while(1){;
        // Push Button Pressed
        if(button_pressed){
            // Toggle LED
            toggle_GPIO(LED_PORT, LED_PIN);
            // Toggle the status
            button_pressed = 0x00; 
        }
        // Delay
        SysTick_delay_ms(DELAY_MS);
    }
    
    // Return Value
    return 0;
}

/**
 * @brief IRQ Handler for GPIOx (5 - 9)
 */
void EXTI9_5_IRQHandler(void){
    // IRQ bit pending
    if(get_EXTI_pending(IRQ_PIN)){
        // Clear EXTI Flag
        clear_EXTI_pending(IRQ_PIN);
        // Toggle a Button Status
        button_pressed = 0x01;
    } 
}
