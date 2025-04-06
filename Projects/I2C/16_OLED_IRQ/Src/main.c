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

	// Configure external LED
	GPIO_config(&LED_Config);

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

	// SSD1306_IRQ_clrScreen(SSD1306_I2Cx, 0x00);

	// SSD1306 Commands for setting Page & Column Address
	// uint8_t SSD1306_scrCmd[3] = { SSD1306_CMD_PAGE_MODE_SET_PAGE(0),
	// 							  SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE(0),
	// 							  SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE(0) };

	// uint8_t scrColor[SSD1306_WIDTH];
	// memset(scrColor, 0x00, SSD1306_WIDTH);

	// SSD1306_IRQ_updateBuff(SSD1306_scrCmd, 3, 1);
	// SSD1306_IRQ_I2C_Start(SSD1306_I2Cx);
	// SSD1306_IRQ_updateBuff(scrColor, SSD1306_WIDTH, 0);
	// SSD1306_IRQ_I2C_Start(SSD1306_I2Cx);					  

	// Infinite Loop
	while(1){

		SSD1306_IRQ_clrScreen(SSD1306_I2Cx, GPIO_get(&LED_Config)? 0xFF: 0x00);
		// Toggle LED
		GPIO_toggle(&LED_Config);
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/

