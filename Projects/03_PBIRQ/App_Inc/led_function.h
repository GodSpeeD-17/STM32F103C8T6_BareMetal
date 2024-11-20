// Header Guards
#ifndef __LED_FUNCTION_H__
#define __LED_FUNCTION_H__

// Standard C Library 
#include "bare_metal.h"

// LED States
#define LED_STATE_NO_TOGGLE             ((uint8_t) 0)
#define LED_STATE_1                     ((uint8_t) 1)
#define LED_STATE_2                     ((uint8_t) 2)
#define LED_STATE_BOTH_TOGGLE           ((uint8_t) 3)
#define LED_RISING_PORT                 (GPIOA)
#define LED_RISING_PIN                  (GPIO_PIN_4)
#define LED_FALLING_PORT                (GPIOA)
#define LED_FALLING_PIN                 (GPIO_PIN_9)


/**
 * @brief Updates the LED Configuration based upon count value
 */
void update_configuration(void);

#endif /* __LED_FUNCTION_H__ */