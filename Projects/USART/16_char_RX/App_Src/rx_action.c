#include "rx_action.h"

/**
 * @brief Does some Action based upon the character
 * @param[in] rx_char The character to act upon
 */
void take_action(const char rx_char){
	// Switch based upon Character
	switch(rx_char){
		// Set LED
		case 's':
			set_GPIO(&led_config);
		break;

		// Reset LED
		case 'r':
			reset_GPIO(&led_config);
		break;
	}
}
