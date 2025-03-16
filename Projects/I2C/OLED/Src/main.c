/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// I2C Configuration Structure
i2c_config_t SSD1306_I2C_Config = {0};
const uint8_t Font5x7_A[5] = {0x7C, 0x12, 0x12, 0x7C, 0x00};
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// I2C Initialisation
	I2C1_loadDefault(&SSD1306_I2C_Config);
	I2C_config(&SSD1306_I2C_Config);
	I2C_enable(SSD1306_I2Cx);

	// SSD1306 Initialisation
	SSD1306_init(SSD1306_I2Cx);

	// Black Screen
	SSD1306_fillFullDisp(SSD1306_I2Cx, 0x00);
	// Test
	SSD1306_gotoXY(SSD1306_I2Cx, 0, 0);
	// SSD1306_I2C_dispChar(SSD1306_I2Cx, '0'); // TESTED OK
	SSD1306_I2C_dispString(SSD1306_I2Cx, 'S');

	// Infinite Loop
	while(1){
		// Toggle OB LED
		OB_LED_toggle();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}

	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/
/**
 * @brief Demo Function for displaying loading screen animation
 */
void SSD1306_loadScreen(void){
	// Full display: Black
	SSD1306_fillFullDisp(SSD1306_I2Cx, 0x00);
	// Loading Animation
	for(uint8_t column = 0; column < (SSD1306_WIDTH - RECT_WIDTH - 1); column++){
		// Fill Rectangle
		SSD1306_fillRect(SSD1306_I2Cx, column, 10, column + RECT_WIDTH, 10 + RECT_HEIGHT);
		// Wait
		delay_ms(30);
	}
}