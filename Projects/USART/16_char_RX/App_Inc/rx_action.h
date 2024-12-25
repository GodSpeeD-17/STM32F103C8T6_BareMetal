// Header Guards
#ifndef __RX_ACTION_H__
#define __RX_ACTION_H__

// Bare Metal Library
#include "bare_metal.h"

// LED Configuration
extern gpio_config_t led_config;

/**
 * @brief Does some Action based upon the character
 * @param[in] rx_char The character to act upon
 */
void take_action(const char rx_char);

#endif /* __RX_ACTION_H__ */ 