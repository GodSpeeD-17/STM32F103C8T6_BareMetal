/**
 * @file ssd1306_frame_rb.h
 * @author Shrey Shah
 * @brief SSD1306 OLED Display Driver using Ring Buffer & Codec
 * @version 1.0
 * @date 13-07-2025
 */

// Includes
#include "ssd1306_frame_rb.h"

// ------------------------------------------------------------- SSD1306 FRAME HELPER FUNCTIONS START ------------------------------------------------------------- //
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
	ssd1306->display.col = SSD1306_WRAP_COLUMN(cursor_X);
	ssd1306->display.page = SSD1306_WRAP_PAGE((cursor_Y >> 3));
}
// ------------------------------------------------------------- SSD1306 FRAME HELPER FUNCTIONS END ------------------------------------------------------------- //

// ------------------------------------------------------------- SSD1306 FRAME DISPLAY INIT FUNCTIONS START ------------------------------------------------------------- //
/**
 * @brief Initializes the Display post power up
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @return Status of operation
 * @return - 0x00: Failure  
 * @return - 0x01: Success 
 */
uint8_t SSD1306_Frame_RB_Disp_Init(ssd1306_config_t* ssd1306){
	// Initialize the display
	if(SSD1306_RB_Encode_Frame(ssd1306, 0x01, SSD1306_initCmd, SSD1306_INIT_CMD_SIZE) != 0x01){
		// Failure
		return 0x00;
	}
	// if(SSD1306_RB_Encode_CMD_Frame(ssd1306, SSD1306_initCmd, SSD1306_INIT_CMD_SIZE) != 0x01){
	// 	// Failure
	// 	return 0x00;
	// }
	// Instant Triggering
	#ifdef __SSD1306_FRAME_I2C_INSTANT_TRIGGER__
		// I2C Handling
		if(SSD1306_Frame_RB_I2C_Dequeue(ssd1306) == 0x00){
			// Failure
			return 0x00;
		}
	#endif
	// Success
	return 0x01;
}

/**
 * @brief SSD1306 Display Initialization
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @return Status of operation
 * @return - 0x00: Failure
 * @return - 0x01: Success 
 */
uint8_t SSD1306_Frame_RB_Disp_Reset(ssd1306_config_t* ssd1306){
	// Display reset sequence
	if(SSD1306_Frame_RB_Disp_Init(ssd1306) != 0x01){
		// Failure
		return 0x00;
	}
	// Reset the display Buffer
	if(SSD1306_Frame_RB_Clear_Screen(ssd1306) != 0x01){
		// Failure
		return 0x00;
	}
	// Success
	return 0x01;
}
// ------------------------------------------------------------- SSD1306 FRAME DISPLAY INIT FUNCTIONS END ------------------------------------------------------------- //

// ------------------------------------------------------------- SSD1306 FRAME PIXEL FUNCTIONS START ------------------------------------------------------------- //
/**
 * @brief Enqueues the SSD1306 Cursor Frame in I2C Ring Buffer 
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @param cursor_X X-coordinate:
 * @param | `SSD1306_WIDTH_MIN` - `SSD1306_WIDTH_MAX`
 * @param cursor_Y Y-coordinate:
 * @param | `SSD1306_HEIGHT_MIN` - `SSD1306_HEIGHT_MAX`
 * @return Status of the operation:
 * @return - `0x00`: Failure
 * @return - `0x01`: Success
 */
uint8_t SSD1306_Frame_RB_Goto_XY(ssd1306_config_t* ssd1306, uint8_t cursor_X, uint8_t cursor_Y){
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
	// Instant Triggering
	#ifdef __SSD1306_FRAME_I2C_INSTANT_TRIGGER__
		if(SSD1306_Frame_RB_I2C_Dequeue(ssd1306) == 0x00){
			// Failure
			return 0x00;
		}
	#endif
	// Success
	return 0x01;
}

/**
 * @brief Manipulates a pixel mentioned at given co-ordinates
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @param isClear 0: Set the pixel, 1: Clear the pixel
 * @param cursor_X X-coordinate: 0 - `SSD1306_WIDTH_MAX`
 * @param cursor_Y Y-coordinate: 0 - `SSD1306_HEIGHT_MAX`
 * @return Status of the operation 
 * @return - 0: Failure  
 * @return - 1: Success
 */
uint8_t SSD1306_Frame_RB_Manipulate_Pixel(ssd1306_config_t* ssd1306, uint8_t isClear, uint8_t cursor_X, uint8_t cursor_Y){
	// Traverse to the co-ordinates
	if(SSD1306_Frame_RB_Goto_XY(ssd1306, cursor_X, cursor_Y) == 0x00){
		// Failure
		return 0x00;
	}
	// Instant Triggering
	#ifdef __SSD1306_FRAME_I2C_INSTANT_TRIGGER__
		if(SSD1306_Frame_RB_I2C_Dequeue(ssd1306) == 0x00){
			// Failure
			return 0x00;
		}
	#endif
	// Retrieve the page & column value
	uint8_t pcValue = SSD1306_Disp_Get_Cell(ssd1306);
	// Set the Pixel
	if(isClear == 0x00){
		pcValue |= (1 << (cursor_Y - (SSD1306_Disp_Get_Page(ssd1306) << 3)));
	}
	// Clear the pixel
	else{
		pcValue &= ~(1 << (cursor_Y - (SSD1306_Disp_Get_Page(ssd1306) << 3)));
	}
	// Enqueue the Data
	if(SSD1306_RB_Encode_Data(ssd1306, pcValue) == 0x00){
		// Failure
		return 0x00;
	}
	// Instant Triggering
	#ifdef __SSD1306_FRAME_I2C_INSTANT_TRIGGER__
		if(SSD1306_Frame_RB_I2C_Dequeue(ssd1306) == 0x00){
			// Failure
			return 0x00;
		}
	#endif
	// Update the Value in Display Buffer
	SSD1306_Disp_Set_Cell(ssd1306, pcValue);
	// Success
	return 0x01;
}
// ------------------------------------------------------------- SSD1306 FRAME PIXEL FUNCTIONS END ------------------------------------------------------------- //

// ------------------------------------------------------------- SSD1306 FRAME PAGE FUNCTIONS START ------------------------------------------------------------- //
/**
 * @brief Sets the Page to a particular pattern
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @param page Page Number: 0 - `PAGE_MAX`
 * @param pattern Pattern to be followed for each column
 * @return Status of operation
 * @return - 0: Failure
 * @return - 1: Success
 */
uint8_t SSD1306_Frame_RB_Set_Page_Pattern(ssd1306_config_t* ssd1306, uint8_t page, const uint8_t pattern){
	// Wrap the page
	page = SSD1306_WRAP_PAGE(page);
	// Go to (X,Y) co-ordinates
	if(SSD1306_Frame_RB_Goto_XY(ssd1306, SSD1306_WIDTH_MIN, (page << 3)) == 0x00){
		// Failure
		return 0x00;
	}
	// I2C Buffer Data
	uint8_t i2cBuffData[SSD1306_WIDTH];
	memset(i2cBuffData, pattern, SSD1306_WIDTH);
	// Enqueue the data
	if(SSD1306_RB_Encode_Data_Frame(ssd1306, i2cBuffData, SSD1306_WIDTH) == 0x00){
		// Failure
		return 0x00;
	}
	// Instant Trigger
	#ifdef __SSD1306_FRAME_I2C_INSTANT_TRIGGER__
		SSD1306_Frame_RB_I2C_Dequeue(ssd1306);
	#endif
	// Update the Display Buffer
	memset(&ssd1306->display.buffer[page][0], pattern, SSD1306_WIDTH);
	// Success
	return 0x01;
}
// ------------------------------------------------------------- SSD1306 FRAME PAGE FUNCTIONS END ------------------------------------------------------------- //


// ------------------------------------------------------------- SSD1306 FRAME DEQUEUE FUNCTIONS START ------------------------------------------------------------- //
/**
 * @brief Dequeues the SSD1306 I2C Ring Buffer & transmits over I2C
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @param i2cBuffer Pointer to I2C Storage Buffer
 * @param i2cBuffSize Size of I2C Storage Buffer
 * @return Status of the operation
 * @return - `0x00`: Failure  
 * @return - `0x01`: Success
 */
// TODO: NEED TO UPDATE THIS FUNCTION TO HANDLE THE I2C BUFFER SIZE
uint8_t SSD1306_Frame_RB_I2C_Dequeue(ssd1306_config_t* ssd1306){
	// Confirmation of tail aligned with Frame
	if(SSD1306_RB_Frame_Aligned(ssd1306) == 0x00){
		// Failure
		return 0x00;
	}
	// Get the size of frame
	uint8_t i2cBuffSize = SSD1306_RB_Frame_Get_Size(ssd1306);
	// Allocate Dynamic Local Buffer for I2C Buffer
	uint8_t* i2cBuffer = (uint8_t*) calloc(i2cBuffSize, sizeof(uint8_t));
	// Dequeue the data & store it in the local buffer
	if(SSD1306_RB_Decode_Frame(ssd1306, i2cBuffer, i2cBuffSize) == 0x00){
		// Free Dynamic Memory Allocated
		free(i2cBuffer);
		// Error
		return 0x00;
	}
	// Instant triggering
	#ifdef __SSD1306_FRAME_I2C_INSTANT_TRIGGER__
		// Occupy the I2C Bus
		I2C_Master_Write_Start(ssd1306->i2c_config.I2Cx, ssd1306->address);
		// Transmit the data over Bus
		I2C_Master_Write_Data(ssd1306->i2c_config.I2Cx, i2cBuffer, i2cBuffSize);
		// Free the I2C Bus
		I2C_Master_Stop(ssd1306->i2c_config.I2Cx);
	#endif
	// Free Dynamic Memory Allocated
	free(i2cBuffer);
	// Success
	return 0x01;
}
// ------------------------------------------------------------- SSD1306 FRAME DEQUEUE FUNCTIONS END ------------------------------------------------------------- //
