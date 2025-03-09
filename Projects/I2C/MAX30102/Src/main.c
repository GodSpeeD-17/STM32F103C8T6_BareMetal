/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// I2C SCL GPIO Config
extern gpio_config_t I2C1_SCL;
extern gpio_config_t I2C1_SDA;
// I2C Configuration Structure
i2c_config_t I2C_Config = {
	.I2Cx = I2C1,
	.SCL = &I2C1_SCL,
	.SDA = &I2C1_SDA,
	.mode = I2Cx_MODE_STD,
	.duty = I2Cx_DUTY_NORMAL,
};
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// I2C Initialisation
	I2C_Config.freq_MHz = (APB1Clock/FREQ_1MHz);
	I2C_Config.TRISE = I2C_calc_TRISE(I2C_Config.mode);
	I2C_Config.CCR = I2C_calc_CCR(I2C_Config.mode, I2C_Config.duty, I2C_Config.freq_MHz);
	I2C_config(&I2C_Config);
	I2C_enable(I2C_Config.I2Cx);
	
	// Wait for Bus to be Ready
	while(!(I2C_busReady(I2C_Config.I2Cx)));

	// LED Intensity
	uint8_t writeConfig[2+1+2+3+2] = {0x02, 0x21, 0x00, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x11, 0x11};
	uint8_t readConfig[2+1+2+3+2] = {0x00};
	float tempC = 0.0f;

	// Turn ON the LEDs
	I2C_setMultiBytes(I2C_Config.I2Cx, MAX30102_ADDRESS, MAX30102_MODE_CNF, writeConfig, (uint8_t)(sizeof(writeConfig)/sizeof(writeConfig[0])));
	// I2C_getMultiBytes(I2C_Config.I2Cx, MAX30102_ADDRESS, MAX30102_MODE_CNF, readConfig, (uint8_t)(sizeof(readConfig)/sizeof(readConfig[0])));
	
	// // Temperature Data
	// I2C_setByte(I2C_Config.I2Cx, MAX30102_ADDRESS, MAX30102_TEMP_CONFIG, MAX30102_TEMP_CONFIG_TEMP_EN);
	// // Read the data & store
	// while(I2C_getByte(I2C_Config.I2Cx, MAX30102_ADDRESS, MAX30102_TEMP_CONFIG)); 
	// I2C_getMultiBytes(I2C_Config.I2Cx, MAX30102_ADDRESS, MAX30102_TEMP_INT, tempData, (uint8_t)(sizeof(tempData)/sizeof(tempData[0])));
	// Final Temperature Value
	tempC = MAX30102_readTempC(I2C_Config.I2Cx);
	
	// Infinite Loop
	while(1){
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/