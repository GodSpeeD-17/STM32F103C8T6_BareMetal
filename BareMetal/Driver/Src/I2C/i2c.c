// Dependency
#include "i2c.h"

/**
 * @brief Writes a Single Byte to Register Address of a given Slave Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slave_address MAX30102 Slave Address
 * @param[in] register Register Address
 * @param[in] byte Data to be written
 */
void I2C_Write_Reg_Byte(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress, uint8_t byte){
	// Local Variable
	uint32_t temp = 0x00;
	
	// Start Sequence
	I2C_sendStart(I2Cx);
	// Wait for Start condition (EV5)
	while(!(I2Cx->SR1.REG & I2C_SR1_SB));

	// Send Slave Address with Write Privilege
	I2C_writeAddress(I2Cx, slaveAddress);
	// Wait for ADDR flag (EV6)
	while(!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2Cx->SR1.REG; // Clear ADDR flag by reading SR1
	temp = I2Cx->SR2.REG; // Clear ADDR flag by reading SR2
	// Wait for TXE flag (EV8_1)
	while(!(I2Cx->SR1.REG & I2C_SR1_TXE));

	// Write Register Address
	I2C_writeByte(I2Cx, registerAddress);
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
	while(!(I2C_busReady(I2Cx)));
}

/**
 * @brief Writes Multiple Consecutive Bytes to Register Address of a given Slave Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address
 * @param[in] registerAddress Starting Register Address
 * @param[in] data Pointer to the data buffer
 * @param[in] len Number of bytes to write
 */
void I2C_Write_Reg_Block(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, uint8_t len){
	// Local Variable
	uint32_t temp = 0x00;

	// Start Sequence
	I2C_sendStart(I2Cx);
	// Wait for Start condition (EV5)
	while (!(I2Cx->SR1.REG & I2C_SR1_SB));

	// Send Slave Address with Write Privilege
	I2C_writeAddress(I2Cx, slaveAddress);
	// Wait for ADDR flag (EV6)
	while (!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2Cx->SR1.REG; // Clear ADDR flag by reading SR1
	temp = I2Cx->SR2.REG; // Clear ADDR flag by reading SR2

	// Wait for TXE flag (EV8_1)
	while (!(I2Cx->SR1.REG & I2C_SR1_TXE));
	// Write Starting Register Address
	I2C_writeByte(I2Cx, registerAddress);
	// Wait for TXE and BTF flags (EV8_2)
	while (!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));

	// Write Multiple Bytes
	for (uint8_t i = 0; i < len; i++) {
		// Write Data Byte
		I2C_writeByte(I2Cx, data[i]);
		// Wait for TXE and BTF flags (EV8_2)
		while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	}

	// Generate STOP condition
	I2C_sendStop(I2Cx);
	// Wait until STOP condition is generated
	while (!(I2C_busReady(I2Cx)));
}

/**
 * @brief Reads a Single Byte from a Register Address of a given Slave Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address
 * @param[in] registerAddress Register Address to read from
 * @returns The read byte
 */
uint8_t I2C_Read_Reg_Byte(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress){
	// Local Variable
	uint32_t temp = 0x00;
	uint8_t data = 0x00;

	// Start Sequence (Write Mode)
	I2C_sendStart(I2Cx);
	// Wait for Start condition (EV5)
	while (!(I2Cx->SR1.REG & I2C_SR1_SB));

	// Send Slave Address with Write Privilege
	I2C_writeAddress(I2Cx, slaveAddress);
	// Wait for ADDR flag (EV6)
	while (!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2Cx->SR1.REG; // Clear ADDR flag by reading SR1
	temp = I2Cx->SR2.REG; // Clear ADDR flag by reading SR2

	// Wait for TXE flag (EV8_1)
	while (!(I2Cx->SR1.REG & I2C_SR1_TXE));
	// Write Register Address
	I2C_writeByte(I2Cx, registerAddress);
	// Wait for TXE and BTF flags (EV8_2)
	while (!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));

	// Repeated START Condition (Switch to Read Mode)
	I2C_sendStart(I2Cx);
	// Wait for Start condition (EV5)
	while (!(I2Cx->SR1.REG & I2C_SR1_SB));

	// Send Slave Address with Read Privilege
	I2C_readAddress(I2Cx, slaveAddress);
	// Wait for ADDR flag (EV6)
	while (!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2Cx->SR1.REG; // Clear ADDR flag by reading SR1
	temp = I2Cx->SR2.REG; // Clear ADDR flag by reading SR2

	// Wait for RXNE flag (EV7)
	while (!(I2Cx->SR1.REG & I2C_SR1_RXNE));
	// Read Data Byte
	data = I2Cx->DR.REG;

	// Generate STOP condition
	I2C_sendStop(I2Cx);
	// Wait until STOP condition is generated
	while (!(I2C_busReady(I2Cx)));

	// Return the read byte
	return data;
}

/**
 * @brief Reads Multiple Consecutive Bytes from a Register Address of a given Slave Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address
 * @param[in] registerAddress Starting Register Address
 * @param[out] data Pointer to the buffer to store the read data
 * @param[in] len Number of bytes to read
 */
void I2C_Read_Reg_Block(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, uint8_t len){
	// Local Variable
	uint32_t temp = 0x00;

	// Start Sequence (Write Mode)
	I2C_sendStart(I2Cx);
	// Wait for Start condition (EV5)
	while(!(I2Cx->SR1.REG & I2C_SR1_SB));

	// Send Slave Address with Write Privilege
	I2C_writeAddress(I2Cx, slaveAddress);
	// Wait for ADDR flag (EV6)
	while (!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2Cx->SR1.REG; // Clear ADDR flag by reading SR1
	temp = I2Cx->SR2.REG; // Clear ADDR flag by reading SR2

	// Wait for TXE flag (EV8_1)
	while (!(I2Cx->SR1.REG & I2C_SR1_TXE));
	// Write Starting Register Address
	I2C_writeByte(I2Cx, registerAddress);
	// Wait for TXE and BTF flags (EV8_2)
	while (!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));

	// Repeated START Condition (Switch to Read Mode)
	I2C_sendStart(I2Cx);
	// Wait for Start condition (EV5)
	while (!(I2Cx->SR1.REG & I2C_SR1_SB));

	// Send Slave Address with Read Privilege
	I2C_readAddress(I2Cx, slaveAddress);
	// Wait for ADDR flag (EV6)
	while (!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2Cx->SR1.REG; // Clear ADDR flag by reading SR1
	temp = I2Cx->SR2.REG; // Clear ADDR flag by reading SR2

	// For other bytes, generate ACK
	I2Cx->CR1.REG |= I2C_CR1_ACK;

	// Read Multiple Bytes
	for (uint8_t i = 0; i < len; i++) {
		// For the last byte, generate NACK
		if (i == len - 1)
			I2Cx->CR1.REG &= ~I2C_CR1_ACK;
		// Wait for RXNE flag (EV7)
		while (!(I2Cx->SR1.REG & I2C_SR1_RXNE));
		// Read Data Byte
		data[i] = I2Cx->DR.REG;
	}

	// Generate STOP condition
	I2C_sendStop(I2Cx);
	// Wait until STOP condition is generated
	while (!(I2C_busReady(I2Cx)));
}

