/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	GPIO_config(&PB_GPIO_Config);
	// Infinite Loop
	while(1){
		// Button Pressed
		if(GPIO_get(&PB_GPIO_Config)){
			// Set OB LED
			OB_LED_set();
		}
		else{
			// Reset OB LED
			OB_LED_reset();
		}
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/