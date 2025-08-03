// Includes
#include "i2c_rb.h"

/**
 * @brief Transmit a single byte from the ring buffer over I2C 
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param ring_buffer i2c_ring_bufferPointer to Ring Buffer Structure
 * @returns Status of the operation
 * @returns - 0: Failure 
 * @returns - 1: Success
 */
uint8_t I2C_RB_TX_Byte(I2C_REG_STRUCT* I2Cx, ring_buffer_t* ring_buffer){
	// Dequeue data from the ring buffer & store it in I2Cx->DR
	if(Ring_Buffer_Dequeue(ring_buffer, &I2Cx->DR.REG)){
		// Wait until the data is transmitted
		while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
		// Success
		return 0x01;
	}
	// Failure
	return 0x00;
}

/**
 * @brief Transmits a block of data from the ring buffer over I2C
 * @param i2c_config Pointer to I2C Configuration Structure
 * @param ring_buffer Pointer to Ring Buffer Structure
 * @param len Length of data to be transmitted from the ring buffer
 * @returns Status of the operation
 * @returns - 0: Failure
 * @returns - 1: Success
 */
uint8_t I2C_RB_TX_Block(I2C_REG_STRUCT* I2Cx, ring_buffer_t* ring_buffer, uint8_t len){
	// Check if the ring buffer has enough data to send
	if(Ring_Buffer_Filled_Space(ring_buffer) < len){
		// Not enough data in the ring buffer
		return 0x00;
	}
	// Iterate through the number of bytes to be sent
	while(len--){
		// Transmit a single byte from the ring buffer over I2C
		if(I2C_RB_TX_Byte(I2Cx, ring_buffer) != 0x01){
			// If transmission fails, return failure
			return 0x00;
		}
	}
	// Return Success
	return 0x01;
}

