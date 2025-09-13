/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation of LEDs
	gpio_config_t ledConfig = {
		.pin = (RED_LED_GPIO_PIN | YELLOW_LED_GPIO_PIN),
	};
	GPIO_LED_Config(RED_LED_GPIO_PORT, &ledConfig);
	// Initialization of Push Button
	gpio_config_t pbConfig = {
		.pin = PUSH_BUTTON_PIN,
		.mode = GPIO_MODE_INPUT,
		.config = GPIO_CNF_IN_FLOAT
	};
	GPIO_Config(PUSH_BUTTON_PORT, &pbConfig);

	// Infinite Loop
	while(1){
		// Check if Push Button is Pressed
		if(GPIO_Get(PUSH_BUTTON_PORT, PUSH_BUTTON_PIN) == 0x01){
			// Turn ON Red LED
			GPIO_Toggle(RED_LED_GPIO_PORT, RED_LED_GPIO_PIN);
			// Turn OFF Yellow LED
			GPIO_Toggle(YELLOW_LED_GPIO_PORT, YELLOW_LED_GPIO_PIN);
		}
		
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/