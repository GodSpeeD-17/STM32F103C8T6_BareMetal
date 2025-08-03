/**
 * @file ssd1306_rb_codec.h
 * @author Shrey Shah
 * @brief Encoding & Decoding the frames for SSD1306 OLED Display
 * @version 1.1
 * @date 03-08-2025
 * 
 * Frame Information:
 * 
 * - Template:
 * 		|-----------|-----------------|----------|
 * 		| INDICATOR | SEQUENCE_LENGTH | SEQUENCE |
 * 		|-----------|-----------------|----------|
 * 		    <IND>        <SEQ_LEN>       <SEQ> 
 * 
 * - Command Sequence:
 * 		|-------|-------|-------|
 * 		|CMD_IND|CMD_LEN|CMD_SEQ|
 * 		|-------|-------|-------|
 * 		   0x00   <LEN>   <CMD>
 * 
 * - Data Sequence:
 * 		|--------|--------|--------|
 * 		|DATA_IND|DATA_LEN|DATA_SEQ|
 * 		|--------|--------|--------|
 * 		   0x40     <LEN>   <DATA>
 * 
 * - Indicators: (Refer SSD1306 datasheet for Details)
 * 		- `0x00`: Command Indicator
 * 		- `0x40`: Data Indicator
 */

// Header Guards
#ifndef __SSD1306_RB_CODEC_H__
#define __SSD1306_RB_CODEC_H__

// Includes
#include "ssd1306_rb.h"

/**
 * @brief Encode multiple bytes in Ring Buffer
 * @param ssd1306 Pointer to SSD1306 Configuration Structure 
 * @param isCMD   Type of byte to encode:
 * @param | `0x00`: Data  
 * @param | `0x01`: Command
 * @param buffer Pointer to buffer
 * @param buff_len Length of the buffer
 * @return Status of operation
 * @return 	- `0x00`: Failure
 * @return 	- `0x01`: Success   
 */
uint8_t SSD1306_RB_Encode_Frame(ssd1306_config_t* ssd1306, const uint8_t isCMD, const uint8_t* buffer, uint16_t buff_len);

/**
 * @brief Decodes the data from Ring Buffer
 * @param ssd1306 Pointer to SSD1306 Configuration Structure 
 * @param buffer Pointer to data storage buffer
 * @param buff_len Length of the buffer
 * @return Status of operation
 * @return 	- `0x00`: Failure
 * @return 	- `0xXX`: Successful Length of Data appended in the Buffer
 */
uint8_t SSD1306_RB_Decode_Frame(ssd1306_config_t* ssd1306, uint8_t* buffer, uint16_t buff_len);

/**
 * @brief Encodes a Single Command on I2C Ring Buffer
 * @param ssd1306 Pointer to SSD1306 Configuration Structure 
 * @param command Command to be encoded
 * @return Status of operation
 * @return 	- `0x00`: Failure
 * @return 	- `0x01`: Success  
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
 * @return - 0x00: Failure
 * @return - 0x01: Success 
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
 * @return - 0x00: Failure
 * @return - 0x01: Success 
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
 * @return - 0x00: Failure
 * @return - 0x01: Success 
 */
__STATIC_INLINE__ uint8_t SSD1306_RB_Encode_Data_Frame(ssd1306_config_t* ssd1306, const uint8_t* data_buffer, uint16_t data_len){
	// Encode the Data Frame
	return (SSD1306_RB_Encode_Frame(ssd1306, 0x00, data_buffer, data_len));
}

/**
 * @brief Checks if Tail is aligned with Frame Start
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @return Status of operation
 * @return - 0x00: Mismatch in Frame
 * @return - 0x01: Matching Frame
 */
__STATIC_INLINE__ uint8_t SSD1306_RB_Frame_Aligned(ssd1306_config_t* ssd1306){
	return ((Ring_Buffer_Peek_Tail(&ssd1306->i2c_rb) == SSD1306_CMD_INDICATOR) || (Ring_Buffer_Peek_Tail(&ssd1306->i2c_rb) == SSD1306_DATA_INDICATOR));
}

/**
 * @brief Retrieves the length of I2C Buffer required
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @return Length of Local I2C Buffer required 
 */
__STATIC_INLINE__ uint8_t SSD1306_RB_Frame_Get_Size(ssd1306_config_t* ssd1306){
	// Returns the length of the frame
	return (Ring_Buffer_Peek_Tail_Offset(&ssd1306->i2c_rb, 1) + 1);
}

#endif /* __SSD1306_RB_CODEC_H__ */