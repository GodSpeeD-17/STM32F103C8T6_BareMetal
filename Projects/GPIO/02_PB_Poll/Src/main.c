/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation of LEDs
	GPIO_LED_Init(RED_LED_PORT, (RED_LED_PIN | YELLOW_LED_PIN));
	// Initialization of Push Button
	GPIO_Init(PUSH_BUTTON_PORT, PUSH_BUTTON_PIN, GPIO_PIN_MODE_INPUT, GPIO_PIN_CONFIG_INPUT_FLOATING);

	// Infinite Loop
	while(1){
		// Check if Push Button is Pressed
		if(GPIO_Get(PUSH_BUTTON_PORT, PUSH_BUTTON_PIN) == 0x01){
			// Turn ON Red LED
			GPIO_PinToggle(RED_LED_PORT, RED_LED_PIN);
			// Turn OFF Yellow LED
			GPIO_PinToggle(YELLOW_LED_PORT, YELLOW_LED_PIN);
		}
		
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/
