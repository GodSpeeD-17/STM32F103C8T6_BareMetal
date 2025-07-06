// Header Guards
#ifndef __I2C_RING_BUFFER_H__
#define __I2C_RING_BUFFER_H__

// Includes
#include "i2c.h"
#include "ring_buffer.h"

/**
 * @brief Transmit a single byte from the ring buffer over I2C 
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param ring_buffer Pointer to Ring Buffer Structure
 * @returns Status of the operation
 * @returns - 0: Failure 
 * @returns - 1: Success
 */
uint8_t I2C_Ring_Buffer_TX_Byte(I2C_REG_STRUCT* I2Cx, ring_buffer_t* ring_buffer);

/**
 * @brief Transmits a block of data from the ring buffer over I2C
 * @param i2c_config Pointer to I2C Configuration Structure
 * @param ring_buffer Pointer to Ring Buffer Structure
 * @param len Length of data to be transmitted from the ring buffer
 * @returns Status of the operation
 * @returns - 0: Failure
 * @returns - 1: Success 
 */
uint8_t I2C_Ring_Buffer_TX_Block(I2C_REG_STRUCT* I2Cx, ring_buffer_t* ring_buffer, uint8_t len);

#endif /* __I2C_RING_BUFFER_H__ */