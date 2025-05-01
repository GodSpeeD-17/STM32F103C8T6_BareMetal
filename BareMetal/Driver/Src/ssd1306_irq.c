// Header File
#include "ssd1306_irq.h"

/**
 * @brief Initialize the SSD1306 I2C Buffer
 * @param[in] buffer  The Buffer to be copied
 * @param[in] buff_len Length of the Buffer to be copied
 * @param[in] isCMD Buffer contains Command(1)/Data(0)
 * @note Takes care of waiting until end of previous transmission
 */
void SSD1306_IRQ_updateBuff(uint8_t *buff, uint16_t buff_len, uint8_t isCMD){
	// Only Update after the data from Buffer is transmitted
	while((SSD1306_I2C_status != I2C_STATE_READY));
	// Buffer contains Command
	if(isCMD == 0x01)
		SSD1306_I2C_buffer[SSD1306_buff_last_index] = SSD1306_CMD_INDICATOR;
	// Buffer contains Data [Pixel Values]
	else
		SSD1306_I2C_buffer[SSD1306_buff_last_index] = SSD1306_DATA_INDICATOR;
	// Update index
	SSD1306_buff_last_index = ((SSD1306_buff_last_index + 1) & (BUFFER_SIZE - 1));
	
	// Update the Buffer
	for (uint16_t i = 0; i < buff_len; i++) {
		// Copy the data
		SSD1306_I2C_buffer[SSD1306_buff_last_index] = buff[i];
		// Update index
		SSD1306_buff_last_index = ((SSD1306_buff_last_index + 1) & (BUFFER_SIZE - 1));
	}
}

/**
 * @brief Clears the Screen
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] color Screen Color: Black(0)/White(1)
 */
void SSD1306_IRQ_clrScreen(I2C_REG_STRUCT* I2Cx, uint8_t color){
	// SSD1306 Commands for setting Page & Column Address
	uint8_t SSD1306_scrCmd[3] = { SSD1306_CMD_PAGE_MODE_SET_PAGE(0),
								  SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE(0),
								  SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE(0) };
	// Screen Color
	uint8_t SSD1306_scrColor[SSD1306_WIDTH];
	memset(SSD1306_scrColor, color, SSD1306_WIDTH);
	
	// Traverse through the Page
	for(uint8_t page = 0; page <= 7; page++){
		// Update Page
		SSD1306_scrCmd[0] = SSD1306_CMD_PAGE_MODE_SET_PAGE(page);
		// Command to set position
		SSD1306_IRQ_updateBuff(SSD1306_scrCmd, 3, 1);
		// Start I2C Communication
		SSD1306_IRQ_I2C_Start(I2Cx);
		delay_us(100);
		// Pixel Data
		SSD1306_IRQ_updateBuff(SSD1306_scrColor, SSD1306_WIDTH, 0);
		// Start I2C Communication
		SSD1306_IRQ_I2C_Start(I2Cx);
		delay_us(100);
	}
}

