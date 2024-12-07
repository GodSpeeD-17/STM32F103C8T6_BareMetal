// Header Guards
#ifndef __LED_FUNCTION_H__
#define __LED_FUNCTION_H__

// Standard C Library 
#include "bare_metal.h"

// LED States
#define LED_STATE_NO_TOGGLE             ((uint8_t) 0x00)
#define LED_STATE_1                     ((uint8_t) 0x01)
#define LED_STATE_2                     ((uint8_t) 0x02)
#define LED_STATE_BOTH_TOGGLE           ((uint8_t) 0x03)
#define LED_DEFAULT_STATE               ((uint8_t) 0xFF)

/**
 * @brief Updates the LED Configuration based upon count value
 */
void update_configuration(void);

#endif /* __LED_FUNCTION_H__ */