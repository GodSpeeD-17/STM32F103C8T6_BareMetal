// Header File
#include "led_function.h"

// Variables declared in main.c
extern volatile uint8_t count, configured;
extern gpio_config_t led_falling_config, led_rising_config;

/**
 * @brief Updates the LED Configuration based upon count value
 */
void update_configuration(void){

    // Ensuring only configuration is done
    if(!configured){

        // Interrupt based Configuration
        switch (count) {

            // Reset State: NO LED TOGGLE
            case LED_STATE_NO_TOGGLE:
                    reset_GPIO(&led_rising_config);
                    reset_GPIO(&led_falling_config);
            break;

            // First State: RISING EDGE LED SET & BOTH LED TOGGLE
            case LED_STATE_1:
                    set_GPIO(&led_rising_config);
                    reset_GPIO(&led_falling_config);
            break;

            // Second State: FALLING EDGE LED SET & BOTH LED TOGGLE
            case LED_STATE_2:
                    set_GPIO(&led_falling_config);
                    reset_GPIO(&led_rising_config);
            break;

            // Third State: BOTH LED TOGGLE
            case LED_STATE_BOTH_TOGGLE:
                    set_GPIO(&led_falling_config);
                    set_GPIO(&led_rising_config);
            break;    
        }

        // Indication of Configuration
        configured = 0xFF;
    }
}
