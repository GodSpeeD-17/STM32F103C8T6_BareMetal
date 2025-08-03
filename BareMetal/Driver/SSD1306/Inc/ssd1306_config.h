/**
 * @file ssd1306_config.h
 * @author Shrey Shah
 * @brief Configuration Structure & Functions for SSD1306 OLED Display
 * @version 1.0
 * @date 03-08-2025
 */

// Header Guards
#ifndef __SSD1306_CONFIG_H__
#define __SSD1306_CONFIG_H__

// ------------------------------------------------------------- INCLUDES START ------------------------------------------------------------- //
#include "ssd1306_reg_map.h"
#include "i2c_config.h"
#include "i2c_rb.h"
#include "i2c_irq.h"
// ------------------------------------------------------------- INCLUDES END ------------------------------------------------------------- //

// ------------------------------------------------------------- MACROS START ------------------------------------------------------------- //
// Size of SSD1306 Goto XY Buffer Size
#define SSD1306_BUFFER_GOTO_XY_SIZE					(3)

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
	/* Send Y Command */							 \
	SSD1306_CMD_PAGE_MODE_SET_PAGE(((Y) >> 3)) 		 \
}
// ------------------------------------------------------------- MACROS END ------------------------------------------------------------- //


// ------------------------------------------------------------- STRUCT START ------------------------------------------------------------- //
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
// ------------------------------------------------------------- STRUCT END ------------------------------------------------------------- //

// ------------------------------------------------------------- DISPLAY HELPER FUNCTION START ------------------------------------------------------------- //
/**
 * @brief Retrieves the Page from the SSD1306 Configuration Structure
 * @param ssd1306 Pointer to the SSD1306 Configuration Structure
 * @return Current Page of the SSD1306 Display
 */
__STATIC_INLINE__ uint8_t SSD1306_Disp_Get_Page(ssd1306_config_t* ssd1306){
	return (ssd1306->display.page);
}

/**
 * @brief Retrieves the Column from the SSD1306 Configuration Structure
 * @param ssd1306 Pointer to the SSD1306 Configuration Structure
 * @return Current Column of the SSD1306 Display
 */
__STATIC_INLINE__ uint8_t SSD1306_Disp_Get_Column(ssd1306_config_t* ssd1306){
	return (ssd1306->display.col);
}

/**
 * @brief Sets the cell from the SSD1306 OLED Display Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param cell Vertical pixel byte present at the current page and column
 */
__STATIC_INLINE__ void SSD1306_Disp_Set_Cell(ssd1306_config_t* ssd1306, const uint8_t cell){
	ssd1306->display.buffer[ssd1306->display.page][ssd1306->display.col] = cell;
}

/**
 * @brief Retrieves the cell from the SSD1306 OLED Display Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 */
__STATIC_INLINE__ uint8_t SSD1306_Disp_Get_Cell(ssd1306_config_t* ssd1306){
	return (ssd1306->display.buffer[ssd1306->display.page][ssd1306->display.col]);
}
// ------------------------------------------------------------- DISPLAY HELPER FUNCTION END ------------------------------------------------------------- //

// ------------------------------------------------------------- CONFIGURATION FUNCTION START ------------------------------------------------------------- //
/**
 * @brief Configures the I2C Ring Buffer for the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param i2c_buffer Pointer to the I2C buffer
 * @param i2c_buff_size Pointer to I2C buffer size 
 * @note - The I2C buffer size must be a power of 2
 * @note - If not, it will be rounded up to the next power of 2
 * @note - The updated Buffer Size will be used for the ring buffer
 */
__STATIC_INLINE__ void SSD1306_Config_RB(ssd1306_config_t* ssd1306, uint8_t* i2c_buffer, uint16_t i2c_buff_size){
	// Configure the I2C Ring Buffer
	Ring_Buffer_Config(&ssd1306->i2c_rb, i2c_buffer, i2c_buff_size);
}

/**
 * @brief Configures the address for Display Buffer used to track SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param buffer Pointer to the display buffer
 * @note - The display buffer must be 2D array
 * @note - The buffer will have `SSD1306_PAGE` rows
 * @note - The buffer will have `SSD1306_WIDTH` columns
 */
__STATIC_INLINE__ void SSD1306_Config_Disp(ssd1306_config_t* ssd1306, uint8_t (*buffer)[SSD1306_WIDTH]){
	// Set the Display Buffer
	ssd1306->display.buffer = buffer;
	// Initialize the Cursor Position
	ssd1306->cursor.X = 0;
	ssd1306->cursor.Y = 0;
	// Initialize the Page and Column Tracker
	ssd1306->display.page = 0;
	ssd1306->display.col = 0;
}

/**
 * @brief Configures the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @note This function assumes the following:
 * @note - `I2C1` is used for communication
 * @note - `0x3C` is the I2C address of the display
 */
__STATIC_INLINE__ void SSD1306_Config_I2C1_Load_Default(ssd1306_config_t* ssd1306){
	// Set the SSD1306 I2C Address
	ssd1306->address = SSD1306_I2C_ADDRESS;
	// Load default I2C1 Configuration
	I2C1_Load_Default(&ssd1306->i2c_config);
}

/**
 * @brief Configures the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @note This function assumes the following:
 * @note - `I2C2` is used for communication
 * @note - `0x3C` is the I2C address of the display
 */
__STATIC_INLINE__ void SSD1306_Config_I2C2_Load_Default(ssd1306_config_t* ssd1306){
	// Set the SSD1306 I2C Address
	ssd1306->address = SSD1306_I2C_ADDRESS;
	// Load default I2C1 Configuration
	I2C2_Load_Default(&ssd1306->i2c_config);
}

/**
 * @brief Updates the I2C Configuration for SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param i2c_config Pointer to I2C Configuration Structure
 * @note - Pointer to the I2C configuration structure can be freed after this call
 * @note - This function only copies the contents of the I2C Configuration Structure
 */
__STATIC_INLINE__ void SSD1306_Config_I2C_Update(ssd1306_config_t* ssd1306, i2c_config_t* i2c_config){
	// Update the I2C Configuration
	memcpy(&ssd1306->i2c_config, i2c_config, sizeof(i2c_config_t));
}

/**
 * @brief Configures the I2C Peripheral for SSD1306 OLED Display based on the configuration
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 */
__STATIC_INLINE__ void SSD1306_Config_I2C(ssd1306_config_t* ssd1306){
	// Configure the I2C Peripheral as per the configuration
	I2C_Config(&ssd1306->i2c_config);
}

/**
 * @brief Enables the I2C Peripheral for SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 */
__STATIC_INLINE__ void SSD1306_Config_I2C_Enable(ssd1306_config_t* ssd1306){
	// Enable the I2C Peripheral
	I2C_Enable(ssd1306->i2c_config.I2Cx);
}

/**
 * @brief Disables the I2C Peripheral for SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 */
__STATIC_INLINE__ void SSD1306_Config_I2C_Disable(ssd1306_config_t* ssd1306){
	// Disable the I2C Peripheral
	I2C_Disable(ssd1306->i2c_config.I2Cx);
}

/**
 * @brief Initializes the I2C Peripheral for SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @note This function performs the following:
 * @note - Configures the I2C Peripheral
 * @note - Enables the I2C Peripheral
 */
__STATIC_INLINE__ void SSD1306_Config_I2C_Init(ssd1306_config_t* ssd1306){
	// Configure the I2C Peripheral
	SSD1306_Config_I2C(ssd1306);
	// Enable the I2C Peripheral
	SSD1306_Config_I2C_Enable(ssd1306);
}
// ------------------------------------------------------------- CONFIGURATION FUNCTION END ------------------------------------------------------------- //

#endif /* __SSD1306_CONFIG_H__ */