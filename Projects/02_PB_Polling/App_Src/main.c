// Main Header
#include "main.h"

// Main Entry Point for User Code
int main(void){
	
	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);

	// SysTick Timer (1ms)
	config_SysTick(CoreClock/1000);

	// Initialize External LED
	gpio_config_t GPIO_CONFIGx = {
		.GPIOx = LED_PORT,
		.PINx = LED_PIN,
		.MODEx = MODE_OUT_10MHz,
		.CNFx = CNF_OUT_GP_PP,
	};
	config_GPIO(&GPIO_CONFIGx);

	// Configure Push Button as Input Pull Up
	gpio_config_t PB_CONFIGx = {
		.GPIOx = IRQ_PORT,
		.PINx = IRQ_PIN,
		.MODEx = MODE_IN,
		.CNFx = CNF_IN_PU,
	};
	config_GPIO(&PB_CONFIGx);
	
	// Infinite Loop
	while(1){

		// Push Button Pressed
		if(!get_GPIO(&PB_CONFIGx)){
			// LED ON
			set_GPIO(&GPIO_CONFIGx);
		}
		// Push Button Released
		else{
			// LED OFF
			reset_GPIO(&GPIO_CONFIGx);
		}

		// Delay
		SysTick_delay_ms(DELAY_MS);
	}
	
	// Return Value
	return 0;
}
