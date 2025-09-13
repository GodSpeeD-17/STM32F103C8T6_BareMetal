/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	gpio_config_t ledConfig = {
		.pin = LED_PIN,
		.mode = LED_MODE,
		.config = LED_CONFIG
	};
	GPIO_Config(LED_PORT, &ledConfig);
	GPIO_Set(LED_PORT, LED_PIN);

	// Infinite Loop
	while(1){
		// Toggle the On-Board LED
		OB_LED_Toggle();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
		// Toggle external LED
		GPIO_Toggle(LED_PORT, LED_PIN);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/