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
	// Full display: Black
	SSD1306_fillFullDisp(SSD1306_I2Cx, 0x00);
	// Fill Rectangle
	// SSD1306_fillRect(SSD1306_I2Cx, 20, 3, 107, 5); // Pass
	SSD1306_fillRect(SSD1306_I2Cx, 50, 3, 87, 6); // Pass
	// SSD1306_fillRect(SSD1306_I2Cx, 20, 3, 107, 30); // Fail

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