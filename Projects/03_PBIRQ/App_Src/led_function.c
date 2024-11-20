// Header File
#include "led_function.h"

// Variables declared in main.c
extern volatile uint8_t count, configured;

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
                    reset_GPIO(LED_RISING_PORT, LED_RISING_PIN);
                    reset_GPIO(LED_FALLING_PORT, LED_FALLING_PIN);
                    configured = 0xFF;
            break;

            // First State: RISING EDGE LED SET & BOTH LED TOGGLE
            case LED_STATE_1:
                    set_GPIO(LED_RISING_PORT, LED_RISING_PIN);
                    reset_GPIO(LED_FALLING_PORT, LED_FALLING_PIN);
                    configured = 0xFF;
            break;

            // Second State: FALLING EDGE LED SET & BOTH LED TOGGLE
            case LED_STATE_2:
                    set_GPIO(LED_FALLING_PORT, LED_FALLING_PIN);
                    reset_GPIO(LED_RISING_PORT, LED_RISING_PIN);
                    configured = 0xFF;
            break;

            // Third State: BOTH LED TOGGLE
            case LED_STATE_BOTH_TOGGLE:
                    set_GPIO(LED_FALLING_PORT, LED_FALLING_PIN);
                    set_GPIO(LED_RISING_PORT, LED_RISING_PIN);
                    configured = 0xFF;
            break;
        }
    }
}
