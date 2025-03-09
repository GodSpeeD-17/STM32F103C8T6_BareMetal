/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	USART1_config();
	USART1_enable();
	// Infinite Loop
	while(1){
		// Default Separate Function
		USART1_DEF_SEP();
		// Transmit Data
		USART1_puts(msg);
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/