// Header Guards
#ifndef __I2C_H__
#define __I2C_H__

// Includes
#include "i2c_config.h"

//  MACROS
#define I2C_readAddress(I2Cx, slaveAddress)			(I2C_writeByte((I2Cx), (((slaveAddress) << 1) | I2Cx_READ)))
#define I2C_writeAddress(I2Cx, slaveAddress)		(I2C_writeByte((I2Cx), (((slaveAddress) << 1) | I2Cx_WRITE)))

/**
 * @brief I2C Direction Initialisation
 * @param[in] I2C_CONFIGx I2C Configuration Structure
 */
#define I2C_Init(I2C_CONFIGx) 			\
{										\
	/* I2C Configuration */ 			\
	I2C_Config((I2C_CONFIGx));			\
	/* I2C Enable */ 					\
	I2C_Enable((I2C_CONFIGx)->I2Cx); 	\
}

/**
 * @brief I2C Bus Ready
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @returns - `0x00`: I2C Bus is not ready
 * @returns - `0x01`: I2C Bus is ready
 */
__STATIC_INLINE__ uint8_t I2C_busReady(I2C_REG_STRUCT* I2Cx){
	// Bus Busy
	if((I2Cx->SR2.REG & I2C_SR2_BUSY))
		return 0x00;
	// Bus Free
	else
		return 0x01;
}

/**
 * @brief I2C Send START Sequence
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__STATIC_INLINE__ void I2C_sendStart(I2C_REG_STRUCT* I2Cx){
	// Send START condition
	I2Cx->CR1.REG |= I2C_CR1_START;
}

/**
 * @brief I2C Byte Send
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param data Data to be TX
 */
__STATIC_INLINE__ void I2C_writeByte(I2C_REG_STRUCT* I2Cx, uint8_t data){
	// Send data
	I2Cx->DR.REG = data;
}

/**
 * @brief I2C Byte Read
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @returns Data received from I2C Bus
 */
__STATIC_INLINE__ uint8_t I2C_readByte(I2C_REG_STRUCT* I2Cx){
	// Read data
	uint8_t byte = I2Cx->DR.REG;
	// Wrap
	byte &= 0xFF;
	// Return data
	return byte;
}

/**
 * @brief I2C Send STOP Sequence
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__STATIC_INLINE__ void I2C_sendStop(I2C_REG_STRUCT* I2Cx){
	// Send STOP condition
	I2Cx->CR1.REG |= I2C_CR1_STOP;
}

/**
 * @brief I2C Master Write Start Sequence
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param slaveAddress Target I2C Slave Address
 * @param registerAddress Target Register Address
 * @note Does not generate STOP condition, use `I2C_sendStop()` after writing data
 */
void I2C_Master_Write_Start(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress);

/**
 * @brief I2C Master Read Start Sequence
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param slaveAddress Target I2C Slave Address
 * @param registerAddress Target Register Address
 * @note Does not generate STOP condition, use `I2C_sendStop()` after reading data
 */
void I2C_Master_Read_Start(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress);

/**
 * @brief I2C Master Stop Sequence
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 */
void I2C_Master_Stop(I2C_REG_STRUCT* I2Cx);

/**
 * @brief Writes a Single Byte to Register Address of a given Slave Address
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param slave_address MAX30102 Slave Address
 * @param register Register Address
 * @param byte Data to be written
 */
void I2C_Write_Reg_Byte(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress, uint8_t byte);

/**
 * @brief Writes Multiple Consecutive Bytes to Register Address of a given Slave Address
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param slaveAddress Slave Address
 * @param registerAddress Starting Register Address
 * @param data Pointer to the data buffer
 * @param len Number of bytes to write
 */
void I2C_Write_Reg_Block(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, uint8_t len);

/**
 * @brief Reads a Single Byte from a Register Address of a given Slave Address
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param slaveAddress Slave Address
 * @param registerAddress Register Address to read from
 * @returns The read byte
 */
uint8_t I2C_Read_Reg_Byte(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress);

/**
 * @brief Reads Multiple Consecutive Bytes from a Register Address of a given Slave Address
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param slaveAddress Slave Address
 * @param registerAddress Starting Register Address
 * @param data Pointer to the buffer to store the read data
 * @param len Number of bytes to read
 */
void I2C_Read_Reg_Block(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, uint8_t len);

#endif /* __I2C_H__ */