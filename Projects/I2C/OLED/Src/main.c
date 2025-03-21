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
	// Clear Screen
	SSD1306_clrScreen(SSD1306_I2Cx);

	SSD1306_gotoXY(SSD1306_I2Cx, 0,0);

	// Command Array
	uint8_t cmdArray[3] = {SSD1306_CMD_PAGE_MODE_SET_PAGE(0), 
							SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE(0),
							SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE(0)};

	// Traverse Pages
	for(uint8_t page = 0; page < 8; page++){
		// Send Page Address
		SSD1306_I2C_cmdArray(SSD1306_I2Cx, cmdArray, 3);
		cmdArray[0] += 1;
		// Send Column Address
		SSD1306_I2C_dataArray(SSD1306_I2Cx, (yami_bitmap + (page * 128)), 128);
	}	
	// SSD1306_I2C_End(SSD1306_I2Cx);

	// SSD1306_I2C_dataArray(SSD1306_I2Cx, yami_image, (sizeof(yami_image)/sizeof(yami_image[0])));

	
	// Load Screen Animation
	// SSD1306_loadScreenAnimation();

	

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
void SSD1306_loadScreenAnimation(void){
	// Go to X, Y co-ordinates
	SSD1306_gotoXY(SSD1306_I2Cx, 22, 50);
	// Display this
	SSD1306_I2C_dispString(SSD1306_I2Cx, "Loading ...");
	// Go to previous line
	SSD1306_gotoXY(SSD1306_I2Cx, 0, (SSD1306_HEIGHT/2));
	// Get Current Row
	uint8_t column = 0x00;
	const uint8_t row = SSD1306_getY();
	// Loading Animation
	for(column; column < (SSD1306_WIDTH - RECT_WIDTH - 1); column += RECT_WIDTH){
		// Fill Rectangle
		SSD1306_fillRect(SSD1306_I2Cx, column, row, column + RECT_WIDTH, row + RECT_HEIGHT);
		// Wait (Smoother Animation)
		delay_ms(100);
	}
}

