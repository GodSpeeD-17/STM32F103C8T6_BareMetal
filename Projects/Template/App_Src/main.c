// Main Header
#include "main.h"

// Main Entry Point for User Code
int main(void){
    
	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);

	// SysTick Timer (1ms)
	config_SysTick(CoreClock/1000);

	// Infinite Loop
	while(1){
		// User Code Start

		// User Code End
		
		// Loop Delay
		SysTick_delay_ms(DELAY_MS);
	}
		
	// Return Value
	return 0;
}
