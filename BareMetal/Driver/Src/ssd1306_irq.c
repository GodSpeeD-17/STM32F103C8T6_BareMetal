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
		delay_ms(1);
		// Pixel Data
		SSD1306_IRQ_updateBuff(SSD1306_scrColor, SSD1306_WIDTH, 0);
		// Start I2C Communication
		SSD1306_IRQ_I2C_Start(I2Cx);
		delay_ms(1);
	}
}


/**
 * @brief I2C1 Event Handler
 */
void I2C1_EV_IRQHandler(void){
	// Switch Case Based upon Scenario
	switch(SSD1306_I2C_status){
		// Ready State
		case I2C_STATE_READY:
			// Success
			if(SSD1306_I2Cx->SR1.REG & I2C_SR1_SB){
				// Send Address
				SSD1306_I2Cx->DR.REG = ((SSD1306_I2C_ADDRESS << 1) | I2Cx_WRITE);
				// SSD1306 I2C Address Written
				SSD1306_I2C_status = I2C_STATE_ADDR_SENT;
			}
		break;

		// I2C Address Sent 
		case I2C_STATE_ADDR_SENT:
			// Slave Acknowledged
			if(SSD1306_I2Cx->SR1.REG & I2C_SR1_ADDR){
				// Clear ADDR
				temp_data = SSD1306_I2Cx->SR2.REG;
				// SSD1306 I2C Address Written
				SSD1306_I2C_status = I2C_STATE_ADDR_CLEARED;
			}
		break;
		
		// Sending First Byte 
		case I2C_STATE_ADDR_CLEARED:
			// Indicator Sent 
			SSD1306_I2Cx->DR.REG = SSD1306_I2C_buffer[SSD1306_buff_curr_index];
			// Update Index
			SSD1306_buff_curr_index = ((SSD1306_buff_curr_index + 1) & (BUFFER_SIZE - 1));
			// Data Burst
			SSD1306_I2C_status = I2C_STATE_SENDING;
		break;

		// Send remaining Data
		case I2C_STATE_SENDING:
			// Transmission Buffer Empty (Data Shifted to Shift Register)
			if(SSD1306_I2Cx->SR1.REG & I2C_SR1_TXE){
				// All Bytes Sent
				if(SSD1306_buff_curr_index == SSD1306_buff_last_index){
					// Stop Indication
					SSD1306_I2Cx->CR1.REG |= I2C_CR1_STOP;
					// Ready for Next Transmission
					SSD1306_I2C_status = I2C_STATE_READY;
					// << Demo Indication >>
					// OB_LED_Toggle();
				}
				// Transfer the remaining Bytes
				else{
					// Bytes Send 
					SSD1306_I2Cx->DR.REG = SSD1306_I2C_buffer[SSD1306_buff_curr_index];
					// Update Index
					SSD1306_buff_curr_index = ((SSD1306_buff_curr_index + 1) & (BUFFER_SIZE - 1));
				}
			}
		break;
	}
}

/**
 * @brief Error Protection
 */
void I2C1_ER_IRQHandler(void){
	// Arbitration Lost Flag
	if(SSD1306_I2Cx->SR1.REG & I2C_SR1_AF) {
		// Clear NACK flag
		SSD1306_I2Cx->SR1.REG &= ~I2C_SR1_AF;
		// Force stop
		SSD1306_I2Cx->CR1.REG |= I2C_CR1_STOP;
		// Reset state machine
		SSD1306_I2C_status = I2C_STATE_READY;
	}
}

