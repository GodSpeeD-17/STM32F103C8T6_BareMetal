/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// SSD 1306 Configuration Structure
i2c_config_t SSD1306_I2C_Config;
/*-------------------------------------------------------------------------------*/
// LED Configuration
gpio_config_t LED_Config = {
	.GPIOx = GPIOA,
	.PINx = GPIO_PIN_2,
	.MODEx = MODE_OUT_10MHz,
	.CNFx = CNF_OUT_GP_PP
};
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	I2C1_loadDefault(&SSD1306_I2C_Config);
	// Configure I2C
	I2C_config(&SSD1306_I2C_Config);
	// Enable I2C
	I2C_enable(SSD1306_I2Cx);
	// Enable Interrupt
	I2C_enableEvent_IRQ(SSD1306_I2Cx, 0);
	// Configure external LED
	GPIO_config(&LED_Config);

	// Initialize the SSD1306 Display
	SSD1306_IRQ_Init();

	// 
	SSD1306_IRQ_clrScreen(SSD1306_I2Cx, 0);


	
	// Infinite Loop
	while(1){
		// Toggle LED
		GPIO_toggle(&LED_Config);
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/

