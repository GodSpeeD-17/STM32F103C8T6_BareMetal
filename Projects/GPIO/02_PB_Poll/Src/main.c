/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// RED LED Configuration
static gpio_config_t LED_Red = {
	.GPIO = GPIOA,
	.PIN = GPIOx_PIN_2,
};
// Push Button Configuration
static gpio_config_t Push_Button = {
	.GPIO = GPIOB,
	.PIN = GPIOx_PIN_13,
	.MODE = GPIOx_MODE_IN,
	.CNF = GPIOx_CNF_IN_PD,
};
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation of LEDs and Push Button
	GPIO_Config_LED(&LED_Red);
	GPIO_Config(&Push_Button);
	// Infinite Loop
	while(1){
		// Push Button Pressed
		if(GPIO_Get(&Push_Button) != 0x00){
			// Toggle LEDs
			GPIO_Toggle(&LED_Red);
		}
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/