/**
 * @file ssd1306_frame_rb.h
 * @author Shrey Shah
 * @brief SSD1306 OLED Display Driver using Ring Buffer & Codec
 * @version 0.1
 * @date 13-07-2025
 */

// Header Guards
#ifndef SSD1306_FRAME_RB_H_
#define SSD1306_FRAME_RB_H_

// Defined for instant triggering
#define __SSD1306_FRAME_I2C__

// Includes
#include "ssd1306_rb_codec.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Initializes the buffer with X, Y command sequence
 * @param X X-coordinate: 0 - `SSD1306_WIDTH_MAX`
 * @param Y Y-coordinate: 0 - `SSD1306_HEIGHT_MAX`
 */
#define SSD1306_BUFFER_GOTO_XY(X, Y) 				 \
{													 \
	/* Send X Lower Nibble Command */				 \
	SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE((X)), \
	/* Send X Upper Nibble Command */				 \
	SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE((X)), \
	/* Send Y Command */				 \
	SSD1306_CMD_PAGE_MODE_SET_PAGE(((Y) >> 3)) 		 \
}
// Size of SSD1306 Goto XY Buffer Size
#define SSD1306_BUFFER_GOTO_XY_SIZE					(3)

/**
 * @brief Clear the Display
 * @param ssd1306 Pointer to SSD1306 structure
 */
#define SSD1306_Frame_RB_Clear_Screen(ssd1306) 							\
{																		\
	SSD1306_Frame_RB_Set_Disp_Pattern(ssd1306, SSD1306_PATTERN_BLACK);  \
}

/**
 * @brief SSD1306 Display Initialization
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @return Status of operation
 * @return - 0: Failure  
 * @return - 1: Success 
 */
uint8_t SSD1306_Frame_RB_Disp_Init(ssd1306_config_t* ssd1306);

/**
 * @brief Enqueues the SSD1306 Cursor Frame in I2C Ring Buffer 
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @param cursor_X X-coordinate: 0 - `SSD1306_WIDTH_MAX`
 * @param cursor_Y Y-coordinate: 0 - `SSD1306_HEIGHT_MAX`
 * @return Status of the operation 
 * @return - 0: Failure  
 * @return - 1: Success  
 */
uint8_t SSD1306_Frame_RB_Goto_XY(ssd1306_config_t* ssd1306, uint8_t cursor_X, uint8_t cursor_Y);

/**
 * @brief Dequeues the SSD1306 I2C Ring Buffer & transmits over I2C
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @return Status of the operation 
 * @return - 0: Failure  
 * @return - 1: Success 
 */
uint8_t SSD1306_Frame_RB_I2C_Dequeue(ssd1306_config_t* ssd1306);

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
uint8_t SSD1306_Frame_RB_Manipulate_Pixel(ssd1306_config_t* ssd1306, uint8_t isClear, uint8_t cursor_X, uint8_t cursor_Y);

/**
 * @brief Sets the Pixel
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @param cursor_X X-coordinate: 0 - `SSD1306_WIDTH_MAX`
 * @param cursor_Y Y-coordinate: 0 - `SSD1306_HEIGHT_MAX`
 * @return Status of the operation 
 * @return - 0: Failure  
 * @return - 1: Success  
 */
__STATIC_INLINE__ uint8_t SSD1306_Frame_RB_Set_Pixel(ssd1306_config_t* ssd1306, uint8_t cursor_X, uint8_t cursor_Y){
	// Set the Pixel
	return (SSD1306_Frame_RB_Manipulate_Pixel(ssd1306, 0x00, cursor_X, cursor_Y));
}

/**
 * @brief Resets the Pixel
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @param cursor_X X-coordinate: 0 - `SSD1306_WIDTH_MAX`
 * @param cursor_Y Y-coordinate: 0 - `SSD1306_HEIGHT_MAX`
 * @return Status of the operation 
 * @return - 0: Failure  
 * @return - 1: Success  
 */
__STATIC_INLINE__ uint8_t SSD1306_Frame_RB_Reset_Pixel(ssd1306_config_t* ssd1306, uint8_t cursor_X, uint8_t cursor_Y){
	// Reset the Pixel
	return (SSD1306_Frame_RB_Manipulate_Pixel(ssd1306, 0x01, cursor_X, cursor_Y));
}

/**
 * @brief Sets the Page to a particular pattern
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @param page Page Number: 0 - `PAGE_MAX`
 * @param pattern Pattern to be followed for each column
 * @return Status of operation
 * @return - 0: Failure
 * @return - 1: Success
 */
uint8_t SSD1306_Frame_RB_Set_Page_Pattern(ssd1306_config_t* ssd1306, uint8_t page, const uint8_t pattern);

/**
 * @brief Set Display Pattern
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @param pattern Pattern to be followed for each column
 * @return Status of operation
 * @return - 0: Failure
 * @return - 1: Success
 */
__STATIC_INLINE__ uint8_t SSD1306_Frame_RB_Set_Disp_Pattern(ssd1306_config_t* ssd1306, const uint8_t pattern){
	// Iterate through loops
	for(uint8_t page = 0; page < SSD1306_PAGE; page++){
		// Set the Page Pattern
		if(SSD1306_Frame_RB_Set_Page_Pattern(ssd1306, page, pattern) == 0x00){
			// Failure
			return 0x00;
		}
	}
	// Success
	return 0x01;
}

#endif /* SSD1306_FRAME_RB_H_ */