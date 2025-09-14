/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Configure LEDs
	gpio_config_t multiLedConfig = {
		.pin = (RED_LED_PIN | YELLOW_LED_PIN),
	};
	GPIO_LED_Init(RED_LED_PORT, &multiLedConfig);
	GPIO_Set(RED_LED_PORT, RED_LED_PIN);
	GPIO_Reset(YELLOW_LED_PORT, YELLOW_LED_PIN);

	// Infinite Loop
	while(1){
		// Toggle the On-Board LED
		OB_LED_Toggle();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
		// Toggle LEDs
		GPIO_Toggle(RED_LED_PORT, RED_LED_PIN);
		GPIO_Toggle(YELLOW_LED_PORT, YELLOW_LED_PIN);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/