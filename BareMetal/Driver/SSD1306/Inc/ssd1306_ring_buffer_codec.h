/**
 * @file ssd1306_ring_buffer_encode.h
 * @author Shrey Shah
 * @brief Encoding & Framing for SSD1306 to differentiate between Command & Data Sequence
 * @version 0.1
 * @date 13-07-2025
 * 
 * Framing:
 * 
 * - Command Sequence:
 * |-------|-------|-------|
 * |CMD_IND|CMD_LEN|CMD_SEQ|
 * |-------|-------|-------|
 *    0x00   <LEN>   <SEQ>
 * 
 * - Data Sequence:
 * |--------|--------|--------|
 * |DATA_IND|DATA_LEN|DATA_SEQ|
 * |--------|--------|--------|
 *    0x40     <LEN>    <SEQ>
 * 
 */

// Header Guards
#ifndef __SSD1306_RING_BUFFER_ENCODE_H__
#define __SSD1306_RING_BUFFER_ENCODE_H__

// Includes
#include "i2c_ring_buffer.h"
#include "ssd1306_ring_buffer.h"

/**
 * @brief Encode multiple bytes in Ring Buffer
 * @param ssd1306 Pointer to SSD1306 Configuration Structure 
 * @param isCMD   Type of byte to encode:  
 *				  - 0: Command  
 *				  - 1: Data
 * @param buffer Pointer to buffer
 * @param buff_len Length of the buffer
 * @return Status of Operation
 * @return - 0: Failure
 * @return - 1: Success   
 */
uint8_t SSD1306_RB_Encode_Frame(ssd1306_config_t* ssd1306, uint8_t isCMD, const uint8_t* buffer, uint16_t buff_len);

/**
 * @brief Decodes the data from Ring Buffer
 * @param ssd1306 Pointer to SSD1306 Configuration Structure 
 * @param buffer Pointer to data storage buffer
 * @param buff_len Length of the buffer
 * @return Status of Operation
 * @return - 0: Failure 
 * @return - Length of Data appended in the Buffer 
 */
uint8_t SSD1306_RB_Decode_Frame(ssd1306_config_t* ssd1306, uint8_t* buffer, uint16_t buff_len);

/**
 * @brief Encodes a Single Command on I2C Ring Buffer
 * @param ssd1306 Pointer to SSD1306 Configuration Structure 
 * @param command Command to be encoded
 * @return Status of operation
 * @return - 0: Failure
 * @return - 1: Success 
 */
__STATIC_INLINE__ uint8_t SSD1306_RB_Encode_CMD(ssd1306_config_t* ssd1306, uint8_t command){
	// Encode a Single Command
	return (SSD1306_RB_Encode_Frame(ssd1306, 0x01, &command, 1));
}

/**
 * @brief Encodes Command Sequence on I2C Ring Buffer
 * @param ssd1306 Pointer to SSD1306 Configuration Structure 
 * @param cmd_buffer Pointer to command buffer
 * @param cmd_len Length of command buffer
 * @return Status of operation
 * @return - 0: Failure
 * @return - 1: Success 
 */
__STATIC_INLINE__ uint8_t SSD1306_RB_Encode_CMD_Frame(ssd1306_config_t* ssd1306, const uint8_t* cmd_buffer, uint16_t cmd_len){
	// Encode the Command Frame
	return (SSD1306_RB_Encode_Frame(ssd1306, 0x01, cmd_buffer, cmd_len));
}

/**
 * @brief Encodes a Single Data on I2C Ring Buffer
 * @param ssd1306 Pointer to SSD1306 Configuration Structure 
 * @param data Data to be encoded
 * @return Status of operation
 * @return - 0: Failure
 * @return - 1: Success 
 */
__STATIC_INLINE__ uint8_t SSD1306_RB_Encode_Data(ssd1306_config_t* ssd1306, uint8_t data){
	// Encode a Single Data
	return (SSD1306_RB_Encode_Frame(ssd1306, 0x00, &data, 1));
}

/**
 * @brief Encodes Data Sequence on I2C Ring Buffer
 * @param ssd1306 Pointer to SSD1306 Configuration Structure 
 * @param data_buffer Pointer to data buffer
 * @param data_len Length of data buffer
 * @return Status of operation
 * @return - 0: Failure
 * @return - 1: Success 
 */
__STATIC_INLINE__ uint8_t SSD1306_RB_Encode_Data_Frame(ssd1306_config_t* ssd1306, const uint8_t* data_buffer, uint16_t data_len){
	// Encode the Data Frame
	return (SSD1306_RB_Encode_Frame(ssd1306, 0x00, data_buffer, data_len));
}

#endif /* __SSD1306_RING_BUFFER_ENCODE_H__ */