/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// I2C Configuration Structure
i2c_config_t SSD1306_I2C_Config = {0};
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// I2C Initialisation
	I2C1_Load_Default(&SSD1306_I2C_Config);
	I2C_Config(&SSD1306_I2C_Config);
	I2C_enable(SSD1306_I2Cx);

	// SSD1306 Initialisation
	SSD1306_Init(SSD1306_I2Cx);
	
	// Pointer Array
	const static uint8_t* img_ptr[3] = {image_yami, image_gojo, image_family};

	// Infinite Loop
	while(1){
		// 3 Images Display
		for(uint8_t i = 0; i < 3; i++){
			// Clear Screen
			SSD1306_clrScr(SSD1306_I2Cx);
			// Delay
			delay_ms(LOOP_DELAY_MS/10);
			// Load Screen Animation
			SSD1306_loadScrAnim(SSD1306_I2Cx);
			// Delay
			delay_ms(LOOP_DELAY_MS/10);
			// Display the whole Image
			SSD1306_I2C_dispFullScreen(SSD1306_I2Cx, img_ptr[i]);
			// Delay
			delay_ms(LOOP_DELAY_MS * 2);
		}
	}

	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/
/**
 * @brief Demo Function for displaying loading screen animation
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
void SSD1306_loadScrAnim(I2C_REG_STRUCT* I2Cx){
	// Go to X, Y co-ordinates
	SSD1306_gotoXY(I2Cx, 22, 50);
	// Display this
	SSD1306_I2C_dispString(I2Cx, "Loading ...");
	// Go to previous line
	SSD1306_gotoXY(I2Cx, 0, (SSD1306_HEIGHT/2));
	// Get Current Row
	const uint8_t row = SSD1306_getY();
	// Loading Animation
	for(uint8_t column = 0; column < (SSD1306_WIDTH - RECT_WIDTH - 1); column ++){
		// Fill Rectangle
		SSD1306_fillRect(I2Cx, column, row, column + RECT_WIDTH, row + RECT_HEIGHT);
		// Wait (Smoother Animation)
		delay_ms(20);
	}
}

