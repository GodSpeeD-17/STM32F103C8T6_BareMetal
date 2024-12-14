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
	reset_GPIO(&GPIO_CONFIGx);

	// Initialise On-board LED
	config_OB_LED();
	reset_OB_LED();

	// Infinite Loop
	while(1){
		// Toggle external LED
		toggle_GPIO(&GPIO_CONFIGx);
		// Delay using SysTick
		SysTick_delay_ms(DELAY_MS);
		// Toggle Onboard LED
		toggle_OB_LED();
	}
	
	// Return Value
	return 0;
}
