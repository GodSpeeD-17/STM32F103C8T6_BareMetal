/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// SSD1306 Configuration Structure
ssd1306_config_t myOLED;
// SSD1306 Display Buffer
static uint8_t displayBuffer[SSD1306_PAGE][SSD1306_WIDTH];
// I2C Ring Buffer
static uint8_t i2cBuffer[I2C_BUFFER_SIZE];
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// SSD1306 Parameters Configuration
	SSD1306_RB_Load_Default(&myOLED);
	SSD1306_RB_Disp_Config(&myOLED, displayBuffer);
	SSD1306_RB_Config(&myOLED, i2cBuffer, I2C_BUFFER_SIZE);

	// SSD1306 I2C Configure
	I2C_Config(&myOLED.i2c_config);
	I2C_Enable(myOLED.i2c_config.I2Cx);

	// SSD1306 Display Initialization
	SSD1306_RB_Disp_Init(&myOLED);

	// Draw a White Strap
	if(SSD1306_RB_Torch_Screen(&myOLED) != 0x01){
		while(1);
	}

	// Wait for the Display to Settle
	delay_ms(10 * LOOP_DELAY_MS);
	
	// Clear the SSD1306 OLED Display
	if(SSD1306_RB_Clear_Screen(&myOLED) != 0x01){
		while(1);
	}

	// Infinite Loop
	while(1){
		// On-board LED Toggle
		OB_LED_Toggle();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/