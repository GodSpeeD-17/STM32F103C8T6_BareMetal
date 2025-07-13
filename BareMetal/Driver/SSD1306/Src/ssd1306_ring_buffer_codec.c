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

// Includes
#include "ssd1306_ring_buffer_codec.h"

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
uint8_t SSD1306_RB_Encode_Frame(ssd1306_config_t* ssd1306, uint8_t isCMD, const uint8_t* buffer, uint16_t buff_len){
	// Check space availability
	if(Ring_Buffer_Available_Space(&ssd1306->i2c_rb) < (buff_len + 2)){
		// Failure
		return 0x00;
	}
	// Step 1: Enqueue the Respective Indicator
	if(isCMD != 0x00){
		// Command Indicator
		if(Ring_Buffer_Enqueue(&ssd1306->i2c_rb, SSD1306_CMD_INDICATOR) != 0x01){
			// Failure
			return 0x00;
		}
	}
	else{
		// Data Indicator
		if(Ring_Buffer_Enqueue(&ssd1306->i2c_rb, SSD1306_DATA_INDICATOR) != 0x01){
			// Failure
			return 0x00;
		}
	}
	// Step 2: Enqueue the Command Sequence Length
	if(Ring_Buffer_Enqueue(&ssd1306->i2c_rb, buff_len) != 0x01){
		// Failure
		return 0x00;
	}
	// Step 3: Copy the Commands
	if(Ring_Buffer_Enqueue_Multiple(&ssd1306->i2c_rb, buffer, buff_len) != 0x01){
		// Failure
		return 0x00;
	}
	// Success
	return 0x01;
}

/**
 * @brief Decodes the data from Ring Buffer
 * @param ssd1306 Pointer to SSD1306 Configuration Structure 
 * @param buffer Pointer to data storage buffer
 * @param buff_len Length of the buffer
 * @return Status of Operation
 * @return - 0: Failure 
 * @return - Length of Data appended in the Buffer 
 */
uint8_t SSD1306_RB_Decode_Frame(ssd1306_config_t* ssd1306, uint8_t* buffer, uint16_t buff_len){
	// Check if the Head is in alignment with Encoding
	if((Ring_Buffer_Peek_Head(&ssd1306->i2c_rb) != SSD1306_CMD_INDICATOR) || (Ring_Buffer_Peek_Head(&ssd1306->i2c_rb) != SSD1306_DATA_INDICATOR)){
		// Failure
		return 0x00;
	}
	// Check if the Data is available in Frame or insufficient Buffer Size 
	else if((Ring_Buffer_Available_Space(&ssd1306->i2c_rb) < 0x03) || ((Ring_Buffer_Peek_Tail_Offset(&ssd1306->i2c_rb, 0x01) + 1) > buff_len)){
		// Failure
		return 0x00;
	}
	// Ininitialize the Data Length 
	uint8_t data_length = 0;
	// Step 1: Decode the Data/Command Indicator
	if(Ring_Buffer_Dequeue(&ssd1306->i2c_rb, buffer) != 0x01){
		// Failure
		return 0x00;
	}
	// Step 2: Decode the Data Sequence Length
	if(Ring_Buffer_Dequeue(&ssd1306->i2c_rb, &data_length) != 0x01){
		// Failure
		return 0x00;
	}
	// Step 3: Decode the Data/Command
	if(Ring_Buffer_Dequeue_Multiple(&ssd1306->i2c_rb, buffer, data_length) != 0x01){
		return 0x00;
	}
	// Return the data_length
	return data_length;
}



