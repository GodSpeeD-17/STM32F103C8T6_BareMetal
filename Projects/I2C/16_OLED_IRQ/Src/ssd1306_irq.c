// Header File
#include "ssd1306_irq.h"

/**
 * @brief Initialize the SSD1306 Data Buffer
 * @param[in] buffer  The buffer to be copied
 * @param[in] buff_len Length of the Buffer to be copied
 * @param[in] isCMD	The data in the Buffer is CMD/DATA
 */
void SSD1306_updateBuff(uint8_t *buff, uint8_t buff_len, uint8_t isCMD){
	// Is the buffer a command or data?
	if(isCMD)
		SSD1306_buffer[SSD1306_buff_last_index++] = SSD1306_CMD_INDICATOR;
	else
		SSD1306_buffer[SSD1306_buff_last_index++] = SSD1306_DATA_INDICATOR;
	// Wrap the index
	SSD1306_buff_last_index &= (BUFFER_SIZE - 1);
	
	// Update the Buffer
	for (uint8_t i = 0; i < buff_len; i++) {
		// Copy the data
		SSD1306_buffer[SSD1306_buff_last_index++] = buff[i];
		// Wrap the index
		SSD1306_buff_last_index &= (BUFFER_SIZE - 1);
	}
}

/**
 * @brief I2C1 Event Handler
 */
void I2C1_EV_IRQHandler(void){
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
		I2C_writeByte(SSD1306_I2Cx, SSD1306_buffer[SSD1306_buff_curr_index++]);
	}
	// Byte Transfer Completed
	else if(SSD1306_I2Cx->SR1.REG & I2C_SR1_BTF){
		// Data Transfer left
		if(SSD1306_buff_curr_index != SSD1306_buff_last_index){
			// Send Data
			I2C_writeByte(SSD1306_I2Cx, SSD1306_buffer[SSD1306_buff_curr_index++]);
		}
		// Data Transfer Complete
		else{
			// Send Stop Condition
			I2C_sendStop(SSD1306_I2Cx);
			// Disable the Interrupt
			I2C_disableEvent_IRQ(SSD1306_I2Cx);
			// LED ON
			OB_LED_toggle();
		}
	}

	// Wrap Buffer Index
	SSD1306_buff_curr_index &= (BUFFER_SIZE - 1);

}