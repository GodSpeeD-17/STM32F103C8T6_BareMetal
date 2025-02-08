/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	config_USART1();
	enable_USART1();
	uint8_t index = 0x00;
	// Infinite Loop
	while(1){
		// Default Separate Function
		if(index == 0)
			USART1_DEF_SEP();
		// Transmit Data
		USART1_putc(lookup_table[index++]);
		index = index & 0x07;
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/