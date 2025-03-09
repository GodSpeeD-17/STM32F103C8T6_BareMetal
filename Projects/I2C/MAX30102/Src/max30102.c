// Dependency
#include "max30102.h"

/**
 * @brief Writes a Single Byte to Register Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] reg_address MAX30102 Register Address
 * @param[in] byte Data to be written
 */
void MAX30102_writeByteAtAddress(I2C_REG_STRUCT* I2Cx, uint8_t reg_address, uint8_t byte){
	// Local Variable
	uint32_t temp = 0x00;
	
	// Start Sequence
	I2C_sendStart(I2Cx);
	// Wait for Start condition (EV5)
	while(!(I2Cx->SR1.REG & I2C_SR1_SB));

	// Send Slave Address with Write Privilege
	I2C_writeAddress(I2Cx, MAX30102_ADDRESS);
	// Wait for ADDR flag (EV6)
	while(!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2Cx->SR1.REG; // Clear ADDR flag by reading SR1
	temp = I2Cx->SR2.REG; // Clear ADDR flag by reading SR2

	// Wait for TXE flag (EV8_1)
	while(!(I2Cx->SR1.REG & I2C_SR1_TXE));
	// Write Register Address
	I2C_writeByte(I2Cx, reg_address);
	// Wait for TXE and BTF flags (EV8_2)
	while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	temp = I2Cx->SR1.REG; // Clearing BTF

	// Write Data Byte
	I2C_writeByte(I2Cx, byte);
	// Wait for TXE and BTF flags (EV8_2)
	while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));

	// Generate STOP condition
	I2C_sendStop(I2Cx);
	// Wait until STOP condition is generated
	while(I2Cx->SR2.REG & I2C_SR2_BUSY);
}

/**
 * @brief Reads a Single Byte to Register Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] reg_address MAX30102 Register Address
 * @returns The read byte
 */
uint8_t MAX30102_readByteFromAddress(I2C_REG_STRUCT* I2Cx, uint8_t reg_address){
	// Local Variable
	uint32_t temp = 0x00;
	uint8_t result = 0x00;
	
	// Start Sequence
	I2C_sendStart(I2Cx);
	// Wait for Start condition
	while(!(I2Cx->SR1.REG & I2C_SR1_SB));

	// Send Slave Address with Write Privilege
	I2C_writeAddress(I2Cx, MAX30102_ADDRESS);
	while(!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2Cx->SR1.REG; // Clearing ADDR Flag
	temp = I2Cx->SR2.REG; // Clears ADDR Flag
	while(!(I2Cx->SR1.REG & I2C_SR1_TXE));

	// Write Register Address
	I2C_writeByte(I2Cx, reg_address);
	// Wait successful transmission
	while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));

	// Repeated START Condition (Switch to Read Mode)
	I2C_sendStart(I2Cx);
	while(!(I2Cx->SR1.REG & I2C_SR1_SB));
	
	// Send Slave Address with Read Bit
	I2C_readAddress(I2Cx, MAX30102_ADDRESS);
	while(!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2Cx->SR1.REG; // Clearing ADDR Flag
	temp = I2Cx->SR2.REG; // Clears ADDR Flag
	while(!(I2Cx->SR1.REG & I2C_SR1_RXNE));

	// Read Temperature Integer Value
	result = I2C_readByte(I2Cx);

	// Generate STOP condition
	I2C_sendStop(I2Cx);
	// Wait until STOP condition is generated
	while(I2Cx->SR2.REG & I2C_SR2_BUSY);

	// Return the value
	return result;
}

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
	I2C_setByte(I2Cx, MAX30102_ADDRESS, MAX30102_TEMP_CONFIG, MAX30102_TEMP_CONFIG_TEMP_EN);
	// Wait till EOC (End of Conversion)
	while(I2C_getByte(I2Cx, MAX30102_ADDRESS, MAX30102_TEMP_CONFIG)); 
	// Read the data & store
	I2C_getMultiBytes(I2Cx, MAX30102_ADDRESS, MAX30102_TEMP_INT, rawTempC, 2);
	// Calibrate the value
	tempC = (float) rawTempC[1] * 0.0625 + (float) rawTempC[0];
	// Return the calculated value
	return tempC;
}

