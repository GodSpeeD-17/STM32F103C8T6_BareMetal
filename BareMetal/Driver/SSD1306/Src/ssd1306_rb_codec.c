/**
 * @file ssd1306_rb_codec.c
 * @author Shrey Shah
 * @brief Encoding & Decoding the frames for SSD1306 OLED Display
 * @version 1.1
 * @date 03-08-2025
 */

// Includes
#include "ssd1306_rb_codec.h"

/**
 * @brief Encode multiple bytes in Ring Buffer
 * @param ssd1306 Pointer to SSD1306 Configuration Structure 
 * @param isCMD   Type of byte to encode:  
 *				  - `0x00`: Data  
 *				  - `0x01`: Command
 * @param buffer Pointer to buffer
 * @param buff_len Length of the buffer
 * @return Status of Operation
 * @return - `0x00`: Failure
 * @return - `0x01`: Success   
 */
uint8_t SSD1306_RB_Encode_Frame(ssd1306_config_t* ssd1306, const uint8_t isCMD, const uint8_t* buffer, uint16_t buff_len){
	// Check space availability
	if(Ring_Buffer_Available_Space(&ssd1306->i2c_rb) < (buff_len + 2)){
		// Failure
		return 0x00;
	}
	// Step 1: Enqueue the Respective Indicator
	if(Ring_Buffer_Enqueue(&ssd1306->i2c_rb, ((isCMD != 0x00)? (SSD1306_CMD_INDICATOR) : (SSD1306_DATA_INDICATOR))) != 0x01){
		// Failure
		return 0x00;
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
 * @return - `0x00`: Failure 
 * @return - Length of Data appended in the Buffer 
 */
uint8_t SSD1306_RB_Decode_Frame(ssd1306_config_t* ssd1306, uint8_t* buffer, uint16_t buff_len){
	// Check if the Tail is aligned with Frame
	if(SSD1306_RB_Frame_Aligned(ssd1306) != 0x01){
		// Failure
		return 0x00;
	}
	// Ininitialize the Data Length 
	uint8_t data_length = SSD1306_RB_Frame_Get_Size(ssd1306);
	// Check if the Data is available in Frame or insufficient Buffer Size
	if(data_length > buff_len){
		// Failure
		return 0x00;
	}

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
	if(Ring_Buffer_Dequeue_Multiple(&ssd1306->i2c_rb, buffer + 1, data_length) != 0x01){
		// Failure
		return 0x00;
	}
	// Return the data_length
	return data_length;
}

