/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// __disable_irq();
	// GPIO Configuration
	GPIO_config(&gpio_LED_config);
	OB_LED_set();
	// __enable_irq();
	// Infinite Loop
	while(1){
		// Toggle LED
		GPIO_toggle(&gpio_LED_config);
		// Toggle On-board LED
		OB_LED_Toggle();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/