// Dependency
#include "max30102.h"

/**
 * @brief Reads Temperature from MAX30102 Sensor
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @returns Temperature in Celsius (floating-point value)
 */
float MAX30102_readTempC(I2C_REG_STRUCT* I2Cx){
	// Local variables
	uint8_t rawTempC[2] = {0x00};
	float tempC = 0.0f;
	// Start Temperature Data Conversion
	I2C_Write_Reg_Byte(I2Cx, MAX30102_ADDRESS, MAX30102_TEMP_CONFIG, MAX30102_TEMP_CONFIG_TEMP_EN);
	// Wait till EOC (End of Conversion)
	while(I2C_Read_Reg_Byte(I2Cx, MAX30102_ADDRESS, MAX30102_TEMP_CONFIG)); 
	// Read the data & store
	I2C_Read_Reg_Block(I2Cx, MAX30102_ADDRESS, MAX30102_TEMP_INT, rawTempC, 2);
	// Calibrate the value
	tempC = (float) rawTempC[1] * 0.0625 + (float) rawTempC[0];
	// Return the calculated value
	return tempC;
}

