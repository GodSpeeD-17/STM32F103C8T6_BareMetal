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
	SSD1306_Init(SSD1306_I2Cx);

	// Command Array
	uint8_t cmd[3] = {SSD1306_CMD_PAGE_MODE_SET_PAGE_ADDR0, SSD1306_CMD_PAGE_MODE_SET_COL_LOW_NIBBLE_ADDR0, SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE_ADDR0};

	// Pixel Values
	uint8_t data[128] = {0x00};
	for(uint8_t i = 0; i < 128; i++){
		data[i] = 0x0F;
	}

	// Demo
	for(uint8_t page = 1; page <= 8; page++){
		// Send Command for Page Address
		SSD1306_I2C_CMD_Array(SSD1306_I2Cx, cmd, 3);
		cmd[0] = SSD1306_CMD_PAGE_MODE_SET_PAGE_ADDR0 + page;
		// Send Data for each column
		SSD1306_I2C_Data_Array(SSD1306_I2Cx, data, 128);
	}

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