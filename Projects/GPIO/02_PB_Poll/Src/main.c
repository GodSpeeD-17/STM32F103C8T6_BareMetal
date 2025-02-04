/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	config_GPIO(&PB_GPIO_Config);
	// Infinite Loop
	while(NEW_STATUS){
		// Button Pressed
		if(get_GPIO(&PB_GPIO_Config)){
			// Set OB LED
			set_OB_LED();
		}
		else{
			// Reset OB LED
			reset_OB_LED();
		}
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return OLD_STATUS;
}
/*-------------------------------------------------------------------------------*/