// Includes
#include "ssd1306_ring_buffer.h"

/**
 * @brief Initializes the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 */
void SSD1306_Ring_Buffer_Init(ssd1306_config_t* ssd1306){
	// Temporary Variable to clear the ADDR flag
	volatile uint32_t temp = 0x00;
	// Initialize the Display Buffer 
	memset(ssd1306->display, 0, SSD1306_PIXELS);
	// Initialize the Cursor Position
	ssd1306->cursor.X = 0;
	ssd1306->cursor.Y = 0;

	// Enqueue the I2C Ring Buffer
	Ring_Buffer_Enqueue_Multiple(&ssd1306->i2c_rb, SSD1306_initCmd, SSD1306_INIT_CMD_SIZE);
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
	