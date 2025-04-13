/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// SSD 1306 Configuration Structure
i2c_config_t SSD1306_I2C_Config;
/*-------------------------------------------------------------------------------*/
// LED Configuration
gpio_config_t LED_Config = {
	.GPIO = GPIOA,
	.PIN = GPIOx_PIN_2,
	.MODE = GPIOx_MODE_OUT_10MHz,
	.CNF = GPIOx_CNF_OUT_GP_PP
};
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){

	// Configure external LED
	GPIO_Config(&LED_Config);

	// I2C Initialisation
	I2C1_loadDefault(&SSD1306_I2C_Config);
	// Configure I2C
	I2C_config(&SSD1306_I2C_Config);
	// Enable Interrupt
	I2C_IRQ_enable(SSD1306_I2Cx, 1, 1);
	// Enable I2C
	I2C_enable(SSD1306_I2Cx);
	
	// Initialize the SSD1306 Display
	SSD1306_IRQ_Init(SSD1306_I2Cx);				  

	// Infinite Loop
	while(1){
		// Toggle Screen Color
		SSD1306_IRQ_clrScreen(SSD1306_I2Cx, GPIO_Get(&LED_Config)? 0xFF: 0x00);
		// Toggle LED
		GPIO_Toggle(&LED_Config);
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/

