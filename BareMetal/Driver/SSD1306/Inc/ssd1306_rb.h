/**
 * @file ssd1306_ring_buffer.h
 * @author Shrey Shah
 * @brief SSD1306 OLED Display Driver using Ring Buffer
 * @version 0.1
 * @date 06-07-2025
 */

// Header Guards
#ifndef __SSD1306_RING_BUFFER_H__
#define __SSD1306_RING_BUFFER_H__

// Includes
#include "ssd1306_config.h"

// Display Pattern Delay between Page Updates 
#define SSD1306_DISP_PATTERN_DELAY_MS				(0xFFF)

/**
 * @brief Initializes the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 */
void SSD1306_RB_Disp_Init(ssd1306_config_t* ssd1306);

/**
 * @brief Goto a specific position in the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param X X-coordinate (0-`SSD1306_WIDTH_MAX`)
 * @param Y Y-coordinate (0 - `SSD1306_HEIGHT_MAX`)
 * @return Operation Status
 * @return - 0x00: Failure
 * @return - 0x01: Success
 */
uint8_t SSD1306_RB_Goto_XY(ssd1306_config_t* ssd1306, uint8_t X, uint8_t Y);

/**
 * @brief Set a pixel in the SSD1306 OLED Display using Ring Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @return Operation Status
 * @return - 0x00: Failure
 * @return - 0x01: Success
 */
uint8_t SSD1306_RB_Set_Current_Pixel(ssd1306_config_t* ssd1306);

/**
 * @brief Clear a pixel in the SSD1306 OLED Display using Ring Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @return Operation Status
 * @return - 0x00: Failure
 * @return - 0x01: Success
 */
uint8_t SSD1306_RB_Clear_Current_Pixel(ssd1306_config_t* ssd1306);

/**
 * @brief Set a specific page pattern in the SSD1306 OLED Display using Ring Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param page Page Number (0-`SSD1306_PAGE`-1)
 * @param pattern Pattern to set in the page
 * @return Operation Status
 * 			- `index`: Failure (Provides the number of pixels that were enqueued)
 * 			- `0x01`: Success (if all pixels were enqueued successfully) 
 */
uint8_t SSD1306_RB_Set_Page_Pattern(ssd1306_config_t* ssd1306, uint8_t page, const uint8_t pattern);

/**
 * @brief Set a specific display pattern in the SSD1306 OLED Display using Ring Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param pattern Pattern to set in the display
 * @return Operation Status
 * @return - 0x00: Failure (if any page setting fails)
 * @return - 0x01: Success (if all pages are set successfully)
 */
uint8_t SSD1306_RB_Set_Disp_Pattern(ssd1306_config_t* ssd1306, const uint8_t pattern);

/**
 * @brief Clears the entire SSD1306 OLED Display using Ring Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @note This function sets the entire display to black (clears the screen)
 * @note It uses the `SSD1306_RB_Set_Disp_Pattern` function
 * @return Operation Status
 * @return - 0x00: Failure
 * @return - 0x01: Success
 */
__STATIC_INLINE__ uint8_t SSD1306_RB_Clear_Screen(ssd1306_config_t* ssd1306){
	// Set the Display Pattern to Black
	return SSD1306_RB_Set_Disp_Pattern(ssd1306, SSD1306_PATTERN_BLACK);
}

/**
 * @brief Lightens the entire SSD1306 OLED Display using Ring Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @note This function sets the entire display to white
 * @note It uses the `SSD1306_RB_Set_Disp_Pattern` function
 * @return Operation Status
 * @return - 0x00: Failure
 * @return - 0x01: Success
 */
__STATIC_INLINE__ uint8_t SSD1306_RB_Torch_Screen(ssd1306_config_t* ssd1306){
	// Set the Display Pattern to White
	return SSD1306_RB_Set_Disp_Pattern(ssd1306, SSD1306_PATTERN_WHITE);
}

/**
 * @brief Sets the pixel at the specified coordinates in the SSD1306 OLED Display using Ring Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param X X-coordinate (0-`SSD1306_WIDTH_MAX`)
 * @param Y Y-coordinate (0 - `SSD1306_HEIGHT_MAX`)
 * @return Operation Status
 * @return - 0x00: Failure
 * @return - 0x01: Success
 */
__STATIC_INLINE__ uint8_t SSD1306_RB_Set_Pixel(ssd1306_config_t* ssd1306, uint8_t X, uint8_t Y){
	// Go to mentioned pixel 
	if(SSD1306_RB_Goto_XY(ssd1306, X, Y) != 0x01){
		return 0x00;
	}
	// Set the pixel
	if(SSD1306_RB_Set_Current_Pixel(ssd1306) != 0x01){
		// Could not set the pixel
		return 0x00;
	}
	// Success
	return 0x01;
}

/**
 * @brief Clears the pixel at the specified coordinates in the SSD1306 OLED Display using Ring Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param X X-coordinate (0-`SSD1306_WIDTH_MAX`)
 * @param Y Y-coordinate (0 - `SSD1306_HEIGHT_MAX`)
 * @return Operation Status
 * @return - 0x00: Failure
 * @return - 0x01: Success
 */
__STATIC_INLINE__ uint8_t SSD1306_RB_Clear_Pixel(ssd1306_config_t* ssd1306, uint8_t X, uint8_t Y){
	// Go to mentioned pixel 
	if(SSD1306_RB_Goto_XY(ssd1306, X, Y) != 0x01){
		return 0x00;
	}
	// Clear the pixel
	if(SSD1306_RB_Clear_Current_Pixel(ssd1306) != 0x01){
		// Could not set the pixel
		return 0x00;
	}
	// Success
	return 0x01;
}

#endif /* __SSD1306_RING_BUFFER_H__ */