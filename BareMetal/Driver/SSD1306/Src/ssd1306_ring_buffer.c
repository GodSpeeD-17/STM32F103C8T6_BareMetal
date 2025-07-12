/**
 * @file ssd1306_ring_buffer.c
 * @author Shrey Shah
 * @brief SSD1306 OLED Display Driver using Ring Buffer
 * @version 0.1
 * @date 06-07-2025
 */

// Includes
#include "ssd1306_ring_buffer.h"

/**
 * @brief Updates the Cursor Position in the SSD1306 OLED Display Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param X X-coordinate (0-`SSD1306_WIDTH_MAX`)
 * @param Y Y-coordinate (0-`SSD1306_HEIGHT_MAX`)
 */
__STATIC_INLINE__ void __SSD1306_RB_Cursor_Update__(ssd1306_config_t* ssd1306, uint8_t X, uint8_t Y){
	// Update the Cursor Position after Wrapping Around
	ssd1306->cursor.X = SSD1306_WRAP_X(X);
	ssd1306->cursor.Y = SSD1306_WRAP_Y(Y);
}

/**
 * @brief Updates the Page & Column Position in the SSD1306 OLED Display Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param X X-coordinate (0-`SSD1306_WIDTH_MAX`)
 * @param Y Y-coordinate (0-`SSD1306_HEIGHT_MAX`)
 * @note - This function is used to update the page and column position in the display buffer
 * @note - It is called after the cursor position is updated
 * @note - It calculates the page and column based on the Y-coordinate and X-coordinate respectively
 */
__STATIC_INLINE__ void __SSD1306_RB_Page_Column_Update__(ssd1306_config_t* ssd1306, uint8_t X, uint8_t Y){
	// Wrap X & Y coordinates
	X = SSD1306_WRAP_X(X);
	Y = SSD1306_WRAP_Y(Y);
	// Update the Cursor Position
	ssd1306->display.page = SSD1306_WRAP_PAGE((Y >> 3));
	ssd1306->display.col = SSD1306_WRAP_COLUMN(X);
}

/**
 * @brief Enqueues the Cursor Position Commands in the SSD1306 OLED Display I2C Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param X X-coordinate (0-`SSD1306_WIDTH_MAX`)
 * @param Y Y-coordinate (0-`SSD1306_HEIGHT_MAX`)
 */
__STATIC_INLINE__ void __SSD1306_RB_Enqueue_Cursor_Position__(ssd1306_config_t* ssd1306, uint8_t X, uint8_t Y){
	// Wrap the X and Y coordinates
	X = SSD1306_WRAP_X(X);
	Y = SSD1306_WRAP_Y(Y);
	// Enqueue the Cursor Position Commands
	Ring_Buffer_Enqueue(&ssd1306->i2c_rb, SSD1306_CMD_PAGE_MODE_SET_X_LOWER_NIBBLE(X));
	Ring_Buffer_Enqueue(&ssd1306->i2c_rb, SSD1306_CMD_PAGE_MODE_SET_X_UPPER_NIBBLE(X));
	Ring_Buffer_Enqueue(&ssd1306->i2c_rb, SSD1306_CMD_PAGE_MODE_SET_Y(Y));
}

/**
 * @brief Configures the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @note This function assumes the following:
 * @note - `I2C1` is used for communication
 * @note - `0x3C` is the I2C address of the display
 */
void SSD1306_RB_Load_Default(ssd1306_config_t* ssd1306){
	// Set the SSD1306 I2C Address
	ssd1306->address = SSD1306_I2C_ADDRESS;
	// Load default I2C1 Configuration
	I2C1_Load_Default(&ssd1306->i2c_config);
	// Initialize the Cursor Position
	ssd1306->cursor.X = 0;
	ssd1306->cursor.Y = 0;
}

/**
 * @brief Initializes the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 */
void SSD1306_RB_Disp_Init(ssd1306_config_t* ssd1306){
	// Initialize the Display Buffer 
	memset(ssd1306->display.buffer, 0, SSD1306_PIXELS);
	// Enqueue the I2C Ring Buffer
	Ring_Buffer_Enqueue_Multiple(&ssd1306->i2c_rb, SSD1306_initCmd, SSD1306_INIT_CMD_SIZE);
	// <<< I2C Master Write Start Sequence >>>
	I2C_Master_Write_Start(ssd1306->i2c_config.I2Cx, ssd1306->address, SSD1306_CMD_INDICATOR);
	// <<< Trigger I2C Data Transfer from Ring Buffer>>>
	I2C_Ring_Buffer_TX_Block(ssd1306->i2c_config.I2Cx, &ssd1306->i2c_rb, SSD1306_INIT_CMD_SIZE);
	// <<< I2C Master Stop Sequence >>>
	I2C_Master_Stop(ssd1306->i2c_config.I2Cx);
	// Update the Cursor Position 
	SSD1306_RB_Goto_XY(ssd1306, 0, 0);
}

/**
 * @brief Goto a specific position in the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param X X-coordinate (0-`SSD1306_WIDTH_MAX`)
 * @param Y Y-coordinate (0 - `SSD1306_HEIGHT_MAX`)
 * @return Operation Status
 * @return - 0x00: Failure
 * @return - 0x01: Success
 */
uint8_t SSD1306_RB_Goto_XY(ssd1306_config_t* ssd1306, uint8_t X, uint8_t Y){
	// Wrap the X and Y coordinates
	X = SSD1306_WRAP_X(X);
	Y = SSD1306_WRAP_Y(Y);
	// Update the Cursor Position after Wrapping Around
	__SSD1306_RB_Cursor_Update__(ssd1306, X, Y);
	// Update the Cursor Position in the Display Buffer
	__SSD1306_RB_Page_Column_Update__(ssd1306, X, Y);
	// Enqueue the Cursor Position Commands
	__SSD1306_RB_Enqueue_Cursor_Position__(ssd1306, X, Y);
	// <<< I2C Master Write Start Sequence >>>
	I2C_Master_Write_Start(ssd1306->i2c_config.I2Cx, ssd1306->address, SSD1306_CMD_INDICATOR);
	// <<< Trigger I2C Data Transfer from Ring Buffer >>>
	if(I2C_Ring_Buffer_TX_Block(ssd1306->i2c_config.I2Cx, &ssd1306->i2c_rb, 3) != 0x01){
		// <<< I2C Master Stop Sequence >>>
		I2C_Master_Stop(ssd1306->i2c_config.I2Cx);
		// Failure to transfer data
		return 0x00;
	}
	// <<< I2C Master Stop Sequence >>>
	I2C_Master_Stop(ssd1306->i2c_config.I2Cx);
	// Success
	return 0x01;
}

/**
 * @brief Set a pixel in the SSD1306 OLED Display using Ring Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @return Operation Status
 * @return - 0x00: Failure
 * @return - 0x01: Success
 */
uint8_t SSD1306_RB_Set_Pixel(ssd1306_config_t* ssd1306){
	// Retrieve the current pixel value from the display buffer  
	uint8_t pixel = ssd1306->display.buffer[ssd1306->display.page][ssd1306->display.col];
	// Set the pixel offset from Page Reference in the display buffer
	pixel |= (1 << (ssd1306->cursor.Y - (ssd1306->display.page << 3)));
	// Enqueue the pixel on Ring Buffer
	if(Ring_Buffer_Enqueue(&ssd1306->i2c_rb, pixel)){
		// <<< I2C Master Write Start Sequence >>>
		I2C_Master_Write_Start(ssd1306->i2c_config.I2Cx, ssd1306->address, SSD1306_DATA_INDICATOR);
		// <<< Trigger I2C Data Transfer from Ring Buffer >>>
		if(I2C_Ring_Buffer_TX_Byte(ssd1306->i2c_config.I2Cx, &ssd1306->i2c_rb) != 0x01){
			// <<< I2C Master Stop Sequence >>>
			I2C_Master_Stop(ssd1306->i2c_config.I2Cx);
			// Failure to transfer data
			return 0x00;
		}
		// <<< I2C Master Stop Sequence >>>
		I2C_Master_Stop(ssd1306->i2c_config.I2Cx);
		// Update the Display Buffer
		ssd1306->display.buffer[ssd1306->display.page][ssd1306->display.col] = pixel;
		// Return Success
		return 0x01;
	}
	// Return Failure
	return 0x00;
}

/**
 * @brief Clear a pixel in the SSD1306 OLED Display using Ring Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @return Operation Status
 * @return - 0x00: Failure
 * @return - 0x01: Success
 */
uint8_t SSD1306_RB_Clear_Pixel(ssd1306_config_t* ssd1306){
	// Retrieve the current pixel value from the display buffer  
	uint8_t pixel = ssd1306->display.buffer[ssd1306->display.page][ssd1306->display.col];
	// Set the pixel offset from Page Reference in the display buffer
	pixel &= ~(1 << (ssd1306->cursor.Y - (ssd1306->display.page << 3)));
	// Enqueue the pixel on Ring Buffer
	if(Ring_Buffer_Enqueue(&ssd1306->i2c_rb, pixel)){
		// <<< I2C Master Write Start Sequence >>>
		I2C_Master_Write_Start(ssd1306->i2c_config.I2Cx, ssd1306->address, SSD1306_DATA_INDICATOR);
		// <<< Trigger I2C Data Transfer from Ring Buffer >>>
		if(I2C_Ring_Buffer_TX_Byte(ssd1306->i2c_config.I2Cx, &ssd1306->i2c_rb) != 0x01){
			// <<< I2C Master Stop Sequence >>>
			I2C_Master_Stop(ssd1306->i2c_config.I2Cx);
			// Failure to transfer data
			return 0x00;
		}
		// <<< I2C Master Stop Sequence >>>
		I2C_Master_Stop(ssd1306->i2c_config.I2Cx);
		// Update the Display Buffer
		ssd1306->display.buffer[ssd1306->display.page][ssd1306->display.col] = pixel;
		// Return Success
		return 0x01;
	}
	// Return Failure
	return 0x00;
}

/**
 * @brief Set a specific page pattern in the SSD1306 OLED Display using Ring Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param page Page Number (0-`SSD1306_PAGE`-1)
 * @param pattern Pattern to set in the page
 * @return Operation Status
 * @return - `index`: Failure (Provides the number of pixels that were enqueued)
 * @return - 0x01: Success (if all pixels were enqueued successfully) 
 */
uint8_t SSD1306_RB_Set_Page_Pattern(ssd1306_config_t* ssd1306, uint8_t page, const uint8_t pattern){
	// Check for space availability in the Ring Buffer
	if(Ring_Buffer_Available_Space(&ssd1306->i2c_rb) < SSD1306_WIDTH){
		// Not enough space in the Ring Buffer
		return 0x00;
	}
	// Wrap the Page Number
	page = SSD1306_WRAP_PAGE(page);
	// Update the Cursor Pixel Position
	SSD1306_RB_Goto_XY(ssd1306, 0, (page << 3));
	// Enqueue the Clear Page Command on Ring Buffer
	for(uint8_t index = 0; index < SSD1306_WIDTH; index++){
		// Enqueue the Pixel Pattern Command
		if(Ring_Buffer_Enqueue(&ssd1306->i2c_rb, pattern) != 0x01){
			// Failure to enqueue: Returns how many pixels were enqueued
			return (index + 1);
		}
	}
	// <<< I2C Master Write Start Sequence >>>
	I2C_Master_Write_Start(ssd1306->i2c_config.I2Cx, ssd1306->address, SSD1306_DATA_INDICATOR);
	// <<< Trigger I2C Data Transfer from Ring Buffer>>>
	if(I2C_Ring_Buffer_TX_Block(ssd1306->i2c_config.I2Cx, &ssd1306->i2c_rb, SSD1306_WIDTH)){
		// Update the Display Buffer
		memset(&ssd1306->display.buffer[page], pattern, SSD1306_WIDTH);
		// <<< I2C Master Stop Sequence >>>
		I2C_Master_Stop(ssd1306->i2c_config.I2Cx);
		// Update the Cursor Position
		SSD1306_RB_Goto_XY(ssd1306, 0, ((page+1) << 3));
		// Success
		return 0x01;
	}
	// <<< I2C Master Stop Sequence >>>
	I2C_Master_Stop(ssd1306->i2c_config.I2Cx);
	// Failure
	return 0x00;
}

/**
 * @brief Set a specific display pattern in the SSD1306 OLED Display using Ring Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param pattern Pattern to set in the display
 * @return Operation Status
 * @return - 0x00: Failure (if any page setting fails)
 * @return - 0x01: Success (if all pages are set successfully)
 */
uint8_t SSD1306_RB_Set_Disp_Pattern(ssd1306_config_t* ssd1306, const uint8_t pattern){
	// Set the Display Pattern
	volatile uint32_t delay = SSD1306_DISP_PATTERN_DELAY_MS;
	for(uint8_t page = 0; page < SSD1306_PAGE; page++){
		// Update Delay Time
		delay = SSD1306_DISP_PATTERN_DELAY_MS;
		// Set Page Pattern
		if(SSD1306_RB_Set_Page_Pattern(ssd1306, page, pattern) != 0x01){
			// If the pattern setting fails, break the loop
			return 0x00;
		}
		// Wait
		while(delay--);
	}
	// Update the Cursor Position
	SSD1306_RB_Goto_XY(ssd1306, 0, 0);
	// Success
	return 0x01;
}

