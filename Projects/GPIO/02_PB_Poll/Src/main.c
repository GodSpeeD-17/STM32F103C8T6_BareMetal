/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// RED LED Configuration
static gpio_config_t LED_Red = {
	.GPIO = GPIOA,
	.PIN = GPIOx_PIN_2,
};
// Yellow LED Configuration
static gpio_config_t LED_Yellow = {
	.GPIO = GPIOA,
	.PIN = GPIOx_PIN_3,
};
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation of LEDs
	GPIO_Config_LED(&LED_Red);
	GPIO_Config_LED(&LED_Yellow);
	// Set LEDs to ON
	GPIO_Set(&LED_Red);
	// Infinite Loop
	while(1){
		// Toggle LEDs
		GPIO_Toggle(&LED_Red); 
		GPIO_Toggle(&LED_Yellow); 
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/