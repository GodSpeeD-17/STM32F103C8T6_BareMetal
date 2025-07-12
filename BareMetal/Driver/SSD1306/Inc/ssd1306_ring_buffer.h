// Header Guards
#ifndef __SSD1306_RING_BUFFER_H__
#define __SSD1306_RING_BUFFER_H__

// Includes
#include "ssd1306_reg_map.h"
#include "i2c_ring_buffer.h"
#include "systick.h"

// Display Pattern Delay between Page Updates 
#define SSD1306_DISP_PATTERN_DELAY_MS				(0xFFF)

// SSD1306 Display Pixel Structure
typedef struct {
	// 2D Array of 128x64 pixels for display
	// - Each pixel is represented by 1 byte
	// - Total 1024 bytes for the entire display
	// - Each byte represents 8 vertical pixels
	uint8_t (*buffer)[SSD1306_WIDTH];
	// Page Tracker
	uint16_t page: 3;
	// Column Tracker
	uint16_t col: 7;
} ssd1306_buff_t;

// SSD1306 Structure Definition
typedef struct {
	// I2C Configuration Structure
	i2c_config_t i2c_config;
	// SSD1306 I2C Address: 
	// - `0x3C` (Default)
	// - `0x3D`
	uint8_t address;
	// I2C Ring Buffer
	ring_buffer_t i2c_rb;
	// Display Buffer
	ssd1306_buff_t display;
	// Cursor position
	SSD1306_pix_t cursor;
} ssd1306_config_t;

/**
 * @brief Configures the address for Display Buffer used to track SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param buffer Pointer to the display buffer
 * @note - The display buffer must be 2D array
 * @note - The buffer will have `SSD1306_PAGE` rows
 * @note - The buffer will have `SSD1306_WIDTH` columns
 */
__STATIC_INLINE__ void SSD1306_RB_Disp_Config(ssd1306_config_t* ssd1306, uint8_t (*buffer)[SSD1306_WIDTH]){
	// Set the Display Buffer
	ssd1306->display.buffer = buffer;
	// Initialize the Page and Column Tracker
	ssd1306->display.page = 0;
	ssd1306->display.col = 0;
}

/**
 * @brief Configures the I2C Ring Buffer for the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param i2c_buffer Pointer to the I2C buffer
 * @param i2c_buff_size Pointer to I2C buffer size 
 * @note - The I2C buffer size must be a power of 2
 * @note - If not, it will be rounded up to the next power of 2
 * @note - The updated Buffer Size will be used for the ring buffer
 */
__STATIC_INLINE__ void SSD1306_RB_Config(ssd1306_config_t* ssd1306, uint8_t* i2c_buffer, uint16_t i2c_buff_size){
	// Configure the I2C Ring Buffer
	Ring_Buffer_Config(&ssd1306->i2c_rb, i2c_buffer, i2c_buff_size);
}

/**
 * @brief Configures the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @note This function assumes the following:
 * @note - `I2C1` is used for communication
 * @note - `0x3C` is the I2C address of the display
 */
void SSD1306_RB_Load_Default(ssd1306_config_t* ssd1306);

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
 * @return - `index`: Failure (Provides the number of pixels that were enqueued)
 * @return - 0x01: Success (if all pixels were enqueued successfully) 
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