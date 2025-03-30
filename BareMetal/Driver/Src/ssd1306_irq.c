// Header File
#include "ssd1306_irq.h"

/**
 * @brief Initialize the SSD1306 I2C Buffer
 * @param[in] buffer  The Buffer to be copied
 * @param[in] buff_len Length of the Buffer to be copied
 * @param[in] isCMD		The data in the Buffer is CMD/DATA
 */
void SSD1306_IRQ_updateBuff(uint8_t *buff, uint16_t buff_len, uint8_t isCMD){
	// Only Update after the data from Buffer is transmitted
	while(SSD1306_data_sent);
	// Buffer data is Command
	if(isCMD)
		// Add Command Indicator
		SSD1306_I2C_buffer[SSD1306_buff_last_index++] = SSD1306_CMD_INDICATOR;
	// Buffer data is Data
	else
		// Add Data Indicator
		SSD1306_I2C_buffer[SSD1306_buff_last_index++] = SSD1306_DATA_INDICATOR;
	// Wrap the index
	SSD1306_buff_last_index &= (BUFFER_SIZE - 1);
	
	// Update the Buffer
	for (uint16_t i = 0; i < buff_len; i++) {
		// Copy the data
		SSD1306_I2C_buffer[SSD1306_buff_last_index++] = buff[i];
		// Wrap the index
		SSD1306_buff_last_index &= (BUFFER_SIZE - 1);
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
	for (uint8_t i = 0; i < SSD1306_WIDTH; i++) {
		SSD1306_scrColor[i] = color;
	}
	
	// Traverse through the Page
	for(uint8_t page = 1; page <= 8; page++){
		// Copy Command Array
		SSD1306_IRQ_updateBuff(SSD1306_scrCmd, 3, 1);
		// Start I2C Communication
		SSD1306_IRQ_I2C_Start(I2Cx);
		// Update Page
		SSD1306_scrCmd[0] = SSD1306_CMD_PAGE_MODE_SET_PAGE(0) + page;
		// Copy Data Array
		SSD1306_IRQ_updateBuff(SSD1306_scrColor, SSD1306_WIDTH, 0);
		// Start I2C Communication
		SSD1306_IRQ_I2C_Start(I2Cx);
	}
}


/**
 * @brief I2C1 Event Handler
 */
void I2C1_EV_IRQHandler(void){
	// External Control for Synchronization
	if(!SSD1306_data_sent){
		// Start Sent
		if(SSD1306_I2Cx->SR1.REG & I2C_SR1_SB){
			// SSD1306 I2C Address with Write Privilege
			I2C_writeAddress(SSD1306_I2Cx, SSD1306_I2C_ADDRESS);
		}
		// Address Sent
		else if(SSD1306_I2Cx->SR1.REG & I2C_SR1_ADDR){
			// Clear ADDR Bit
			uint32_t temp = SSD1306_I2Cx->SR1.REG;
			temp = SSD1306_I2Cx->SR2.REG;
			// Send Data
			I2C_writeByte(SSD1306_I2Cx, SSD1306_I2C_buffer[SSD1306_buff_curr_index++]);
		}
		// Byte Transfer Completed
		else if(SSD1306_I2Cx->SR1.REG & I2C_SR1_BTF){
			// Data Transfer left
			if(SSD1306_buff_curr_index != SSD1306_buff_last_index){
				// Send Data
				I2C_writeByte(SSD1306_I2Cx, SSD1306_I2C_buffer[SSD1306_buff_curr_index++]);
			}
			// Data Transfer Complete
			else{
				// Send Stop Condition
				I2C_sendStop(SSD1306_I2Cx);
				// < ! --- LED ON --- !>
				OB_LED_toggle();
				// Data Transfer Complete
				SSD1306_data_sent = 0x01;
			}
		}
		// Wrap Buffer Index
		SSD1306_buff_curr_index &= (BUFFER_SIZE - 1);
	}
}
