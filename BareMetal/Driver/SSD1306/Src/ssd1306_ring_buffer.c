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
	memset(ssd1306->display, 0, SSD1306_PIXELS);
	// Enqueue the I2C Ring Buffer
	Ring_Buffer_Enqueue_Multiple(&ssd1306->i2c_rb, SSD1306_initCmd, SSD1306_INIT_CMD_SIZE);
	// Initialize the Cursor Position
	Ring_Buffer_Enqueue(&ssd1306->i2c_rb, SSD1306_CMD_PAGE_MODE_SET_PAGE_X(ssd1306->cursor.X));
	Ring_Buffer_Enqueue(&ssd1306->i2c_rb, SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE_Y(ssd1306->cursor.Y));
	Ring_Buffer_Enqueue(&ssd1306->i2c_rb, SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE_Y(ssd1306->cursor.Y));
	
	// <<< I2C Master Write Start Sequence >>>
	I2C_Master_Write_Start(ssd1306->i2c_config.I2Cx, ssd1306->address, SSD1306_CMD_INDICATOR);

	// <<< Trigger I2C Data Transfer from Ring Buffer>>>
	I2C_Ring_Buffer_TX_Block(ssd1306->i2c_config.I2Cx, &ssd1306->i2c_rb, 
							 Ring_Buffer_Filled_Space(&ssd1306->i2c_rb));

	// <<< I2C Master Stop Sequence >>>
	I2C_Master_Stop(ssd1306->i2c_config.I2Cx);
}
