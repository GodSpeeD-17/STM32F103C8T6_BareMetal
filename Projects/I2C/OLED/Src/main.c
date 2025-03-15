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
	OB_LED_set();

	// Set Column & Page Address
	uint8_t tempArray[6] = {SSD1306_CMD_SET_COL_ADDR, 0, 127, SSD1306_CMD_SET_PAGE_ADDR, 0, 7};
	SSD1306_I2C_CMD_Array(SSD1306_I2Cx, tempArray, 6);
	
	// uint8_t tempArray1[3] = {SSD1306_CMD_SET_COL_ADDR, 0, 127};
	// SSD1306_I2C_CMD_Array(SSD1306_I2Cx, tempArray1, 3);
	// uint8_t tempArray2[3] = {SSD1306_CMD_SET_PAGE_ADDR, 0, 7};
	// SSD1306_I2C_CMD_Array(SSD1306_I2Cx, tempArray2, 3);

	//
	uint8_t tempArray3[128 * 64] = {0x00};
	SSD1306_I2C_Data_Array(SSD1306_I2Cx, tempArray3, 128 * 64);

	// // I2C Start
	// SSD1306_I2C_Init(SSD1306_I2Cx);

	// // Data Indicator
	// I2C_writeByte(SSD1306_I2Cx, SSD1306_DATA_INDICATOR);
	// // Wait for TXE and BTF flags (EV8_2)
	// while(!(SSD1306_I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	
	// // Demo Test
	// for (uint16_t page = 0; page < 128 * 64; page++) {
	// 	// Alternate between 0xAA (10101010) and 0x55 (01010101)
	// 	I2C_writeByte(SSD1306_I2Cx, 0xFF);
	// 	// Wait for TXE and BTF flags (EV8_2)
	// 	while(!(SSD1306_I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));

	// }

	// // I2C End
	// SSD1306_I2C_End(SSD1306_I2Cx);

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