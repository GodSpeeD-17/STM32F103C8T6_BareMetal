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
 * @brief Enqueues the SSD1306 Cursor Frame in I2C Ring Buffer 
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @param cursor_X X-coordinate: 0 - `SSD1306_WIDTH_MAX`
 * @param cursor_Y Y-coordinate: 0 - `SSD1306_HEIGHT_MAX`
 * @return Status of the operation 
 * @return - 0: Failure  
 * @return - 1: Success  
 */
uint8_t SSD1306_Frame_RB_Goto_XY_Enqueue(ssd1306_config_t* ssd1306, uint8_t cursor_X, uint8_t cursor_Y);

/**
 * @brief Dequeues the SSD1306 I2C Ring Buffer & transmits over I2C
 * @param ssd1306 Pointer to SSD1306 Configuration Structure
 * @return Status of the operation 
 * @return - 0: Failure  
 * @return - 1: Success 
 */
uint8_t SSD1306_Frame_RB_I2C_Dequeue(ssd1306_config_t* ssd1306);



#endif /* SSD1306_FRAME_RB_H_ */