/**
 * @file ssd1306_frame_rb.h
 * @author Shrey Shah
 * @brief SSD1306 OLED Display Driver using Ring Buffer & Codec
 * @version 0.1
 * @date 13-07-2025
 */

// Includes
#include "ssd1306_frame_rb.h"

/**
 * @brief Updates the SSD1306 Structure based on the X, Y co-ordinates 
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @param cursor_X X-coordinate: 0 - `SSD1306_WIDTH_MAX`
 * @param cursor_Y Y-coordinate: 0 - `SSD1306_HEIGHT_MAX`
 */
__STATIC_INLINE__ void __ssd1306_structure_update_cursor__(ssd1306_config_t* ssd1306, uint8_t cursor_X, uint8_t cursor_Y){
	// Wrap the cursor around the display if it's out of bounds
	cursor_X = SSD1306_WRAP_X(cursor_X);
	cursor_Y = SSD1306_WRAP_Y(cursor_Y);
	// Update the configuration structure
	ssd1306->cursor.X = cursor_X;
	ssd1306->cursor.Y = cursor_Y;
	// Update the page & column accordingly
	ssd1306->display.col = cursor_X;
	ssd1306->display.page = (cursor_Y >> 3);
}

/**
 * @brief Enqueues the SSD1306 Cursor Frame in I2C Ring Buffer 
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @param cursor_X X-coordinate: 0 - `SSD1306_WIDTH_MAX`
 * @param cursor_Y Y-coordinate: 0 - `SSD1306_HEIGHT_MAX`
 * @return Status of the operation 
 * @return - 0: Failure  
 * @return - 1: Success  
 */
uint8_t SSD1306_Frame_RB_Goto_XY_Enqueue(ssd1306_config_t* ssd1306, uint8_t cursor_X, uint8_t cursor_Y){
	// Check space availability
	if(Ring_Buffer_Available_Space(&ssd1306->i2c_rb) < (SSD1306_BUFFER_GOTO_XY_SIZE + 2)){
		// Not enough space in the Ring Buffer
		return 0x00;
	}
	// Wrap the cursor around the display if it's out of bounds
	cursor_X = SSD1306_WRAP_X(cursor_X);
	cursor_Y = SSD1306_WRAP_Y(cursor_Y);
	// Command Buffer
	uint8_t cmd_buff[SSD1306_BUFFER_GOTO_XY_SIZE] = SSD1306_BUFFER_GOTO_XY(cursor_X, cursor_Y);
	// Enqueue the Frame in I2C Buffer
	if(SSD1306_RB_Encode_CMD_Frame(ssd1306, cmd_buff, SSD1306_BUFFER_GOTO_XY_SIZE) != 0x01){
		// Failure
		return 0x00;
	}
	// Update the internal structure parameters
	__ssd1306_structure_update_cursor__(ssd1306, cursor_X, cursor_Y);
	// Success
	return 0x01;
}

/**
 * @brief Dequeues the SSD1306 I2C Ring Buffer & transmits over I2C
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @return Status of the operation 
 * @return - 0: Failure  
 * @return - 1: Success 
 */
uint8_t SSD1306_Frame_RB_I2C_Dequeue(ssd1306_config_t* ssd1306){
	// Confirmation of tail aligned with Frame
	if(SSD1306_RB_Frame_Aligned(ssd1306) != 0x01){
		// Failure
		return 0x00;
	}
	// Get the size of frame
	uint8_t i2cBuffSize = SSD1306_RB_Frame_Get_Size(ssd1306);
	uint8_t* i2cBuffer = (uint8_t*) calloc(i2cBuffSize, sizeof(uint8_t));
	// Dequeue the data & store it in the local buffer
	if(SSD1306_RB_Decode_Frame(ssd1306, i2cBuffer, i2cBuffSize) == 0x00){
		// Free Dynamic Memory Allocated
		free(i2cBuffer);
		// Error
		return 0x00;
	}
	// Occupy the I2C Bus
	I2C_Master_Write_Start(ssd1306->i2c_config.I2Cx, ssd1306->address);
	// Transmit the data over Bus
	I2C_Master_Write_Data(ssd1306->i2c_config.I2Cx, i2cBuffer, i2cBuffSize);
	// Free the I2C Bus
	I2C_Master_Stop(ssd1306->i2c_config.I2Cx);
	// Free Dynamic Memory Allocated
	free(i2cBuffer);
	// Success
	return 0x01;
}

