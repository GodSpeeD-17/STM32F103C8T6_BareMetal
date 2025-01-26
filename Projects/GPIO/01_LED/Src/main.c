/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// GPIO Configuration
	config_GPIO(&gpio_LED_config);
	set_OB_LED();
	// Infinite Loop
	while(1){
		// Toggle LED
		toggle_GPIO(&gpio_LED_config);
		// Toggle On-board LED
		toggle_OB_LED();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/