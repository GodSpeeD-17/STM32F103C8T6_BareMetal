// Header
#include "ssd1306_dma.h"
/*-------------------------------------------------------------------------------*/

/**
 * @brief SSD1306 Hardware for OLED regarding I2C & DMA Configuration
 */
void SSD1306_DMA_I2C_Init() {
	// SSD1306_I2Cx Configuration
	I2C1_Load_Default(&I2C_SSD1306_Configuration);
	I2C_Config(&I2C_SSD1306_Configuration);
	I2C_IRQ_enable(SSD1306_I2Cx, (I2Cx_IRQ_EVENT | I2Cx_IRQ_ERROR));
	I2C_enable(SSD1306_I2Cx);

	// DMA Configuration
	DMA_Load_Default_MEM2PER(&DMA_SSD1306_Configuration);
	DMA_SSD1306_Configuration.DMA_Channel = DMA_I2C1_TX;
	DMA_Config(&DMA_SSD1306_Configuration);
}

/**
 * @brief Updates the Buffer with Display Initialization Commands
 */
void SSD1306_DMA_Disp_Init() {
	// Configure DMA Transfer Parameters
	DMA_Transfer_Config(DMA_I2C1_TX, SSD1306_initCmd, &SSD1306_I2Cx->DR.REG, SIZEOF(SSD1306_initCmd));
	// SSD1306 I2C DMA Sequence
	SSD1306_DMA_CMD_Trigger();
}

/**
 * @brief Goes to mentioned Co-ordinates
 * @param X X Co-ordinate: 0 - `SSD1306_HEIGHT`
 * @param Y X Co-ordinate: 0 - `SSD1306_WIDTH`
 */
void SSD1306_DMA_Goto_XY(uint8_t X, uint8_t Y) {
	// Update the Co-ordinates
	cursor.X = (X & (SSD1306_HEIGHT - 1));
	cursor.Y = (Y & (SSD1306_WIDTH - 1));
	// Page Set
	cmd_buffer[0] = SSD1306_CMD_PAGE_MODE_SET_PAGE_X(cursor.X);
	// Column Set
	cmd_buffer[1] = SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE_Y(cursor.Y);
	cmd_buffer[2] = SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE_Y(cursor.Y);
	// DMA Commands Configured
	DMA_Transfer_Config(DMA_I2C1_TX, cmd_buffer, &SSD1306_I2Cx->DR.REG, 3);
	// DMA Command Trigger
	SSD1306_DMA_CMD_Trigger();
}

/**
 * @brief Set the pattern for current Column i.e cursor.Y
 * @param pattern Display Pattern for Column
 */
void SSD1306_DMA_Set_Col_Pattern(uint8_t pattern) {
	// Get Current Page & Current Page Start Boundary Offset
	uint8_t cursor_page = cursor.X >> 3;
	uint8_t cursor_X_diff = cursor.X - (cursor_page << 3);

	// Padding of 0s based upon the Offset towards LSB to obtain towards top side of Column
	data_buffer[cursor_page][cursor.Y] = (pattern << cursor_X_diff);
	DMA_Transfer_Config(DMA_I2C1_TX, &data_buffer[cursor_page][cursor.Y], &SSD1306_I2Cx->DR.REG, 2);
	SSD1306_DMA_Data_Trigger();
	
	// Offset from Page Start Boundary
	if(cursor_X_diff != 0) {
		// Go to next Page
		cursor_page++;
		SSD1306_DMA_Goto_XY((cursor_page << 3), cursor.Y);
		// Padding of 0s based upon the Offset towards MSB to obtain towards bottom side of Column
		data_buffer[cursor_page][cursor.Y] = (pattern >> (8 - cursor_X_diff));
		DMA_Transfer_Config(DMA_I2C1_TX, &data_buffer[cursor_page][cursor.Y], &SSD1306_I2Cx->DR.REG, 2);
		SSD1306_DMA_Data_Trigger();
	}
}

/**
 * @brief Sets a Particular Pixel on the Screen
 * @param[in] X X Co-ordinate: 0 - `SSD1306_HEIGHT`
 * @param[in] Y Y Co-ordinate: 0 - `SSD1306_WIDTH`
 */
void SSD1306_DMA_Set_Pixel(uint8_t X, uint8_t Y) {
	// Set the Corresponding Co-ordinates						
	SSD1306_DMA_Goto_XY(X, Y);
	// Retrieve the Column Pattern
	uint8_t pattern = SSD1306_DMA_Load_Col_Pattern(cursor.X, cursor.Y);
	// Set the Pixel
	pattern |= (1 << (X - ((X >> 3) << 3)));
	// Store the Column Pattern
	SSD1306_DMA_Set_Col_Pattern(pattern);
}

/**
 * @brief Draws Vertical Line on the Screen
 * @param X1 Initial X Co-ordinate: 0 - `SSD1306_HEIGHT`
 * @param X2 Final X Co-ordinate: 0 - `SSD1306_HEIGHT`
 * @param Y Y Co-ordinate: 0 - `SSD1306_WIDTH`
 */
void SSD1306_DMA_Draw_Vertical_Line(uint8_t X1, uint8_t X2, uint8_t Y) {

	// Wrap the variables
	X1 &= (SSD1306_HEIGHT - 1);
	X2 &= (SSD1306_HEIGHT - 1);
	Y &= (SSD1306_WIDTH - 1);
	// Swap X1 & X2
	if (X1 > X2) {
		X1 ^= X2;
		X2 ^= X1;
		X1 ^= X2;
	}
	// Get Start & End Page
	uint8_t start_page = X1 >> 3;
	uint8_t end_page = X2 >> 3;
	// Get Start & End Offset
	uint8_t start_offset = X1 - (start_page << 3);
	uint8_t end_offset = X2 - (end_page << 3);
	uint8_t pattern = 0x00;
	// Iterate over the Pages
	for (uint8_t page = start_page; page <= end_page; page++) {
		// Get the Column Pattern
		pattern = SSD1306_DMA_Load_Col_Pattern((page << 3), cursor.Y);
		// Set the Pixel Sequence
		if (page == start_page && page == end_page) {
			pattern = (0xFF >> (7 - (X2 - X1))) << start_offset;
		} 
		else if (page == start_page) {
			pattern = 0xFF << start_offset;
		} 
		else if (page == end_page) {
			pattern = 0xFF >> (8 - end_offset);
		} 
		else {
			pattern = 0xFF;
		}
		// Set the Co-ordinates
		SSD1306_DMA_Goto_XY(page << 3, Y);
		// Store the Column Pattern
		SSD1306_DMA_Set_Col_Pattern(pattern);
		// Small Delay
		delay_ms(5);
	}
}

/**
 * @brief Draws Horizontal Line on the Screen
 * @param X X Co-ordinate: 0 - `SSD1306_HEIGHT`
 * @param Y1 Initial Y Co-ordinate: 0 - `SSD1306_WIDTH`
 * @param Y2 Final Y Co-ordinate: 0 - `SSD1306_WIDTH`
 */
void SSD1306_DMA_Draw_Horizontal_Line(uint8_t X, uint8_t Y1, uint8_t Y2) {
	// Wrap the variables
	X &= (SSD1306_HEIGHT - 1);
	Y1 &= (SSD1306_WIDTH - 1);
	Y2 &= (SSD1306_WIDTH - 1);
	// Swap Y1 & Y2
	if (Y1 > Y2) {
		Y1 ^= Y2;
		Y2 ^= Y1;
		Y1 ^= Y2;
	}
	// Pattern for the Column
	uint8_t pattern = (0x01 << (X - ((X >> 3) << 3)));
	// Iterate over the Columns
	for(uint8_t y = Y1; y <= Y2; y++) {
		// Update Data Buffer
		data_buffer[(X >> 3)][y] |= pattern;
	}
	// Go to the Co-ordinates
	SSD1306_DMA_Goto_XY(X, Y1);
	// Configure DMA Transfer Configuration
	DMA_Transfer_Config(DMA_I2C1_TX, &data_buffer[(X >> 3)][Y1], &SSD1306_I2Cx->DR.REG, (Y2 - Y1 + 1));
	// DMA Data Trigger
	SSD1306_DMA_Data_Trigger();
	// Small Delay
	delay_ms(5);
}

/**
 * @brief Fills the Columns in Page with pattern
 * @param page Page Number: 0 - 7
 * @param pattern Display Pattern for each Column within the Page
 */
void SSD1306_DMA_Page_Color(uint8_t page, uint8_t pattern) {
	// Data for the Page: Fill the Page with Pattern
	memset(&data_buffer[page], pattern, BUFFER_SIZE);
	// Go to (page*8, 0)
	SSD1306_DMA_Goto_XY((page << 3), 0);
	// Delay
	delay_us(SSD1306_I2C_SYNC_DELAY_TIME_US);
	// DMA Data Configuration
	DMA_Transfer_Config(DMA_I2C1_TX, &data_buffer[page], &SSD1306_I2Cx->DR.REG, BUFFER_SIZE);
	// DMA Data Trigger
	SSD1306_DMA_Data_Trigger();
}

/**
 * @brief Colors the SSD1306 Screen based on input pattern
 * @param[in] pattern Display Pattern for each Column
 */
void SSD1306_DMA_Color_Screen(uint8_t pattern) {
	// Traverse through all Pages
	for (uint8_t page = 0; page < 8; page++) {
		// Individual Page Pattern
		SSD1306_DMA_Page_Color(page, pattern);
		// Small Delay
		delay_ms(1);
	}
}

/*-------------------------------------------------------------------------------*/
/**
 * @brief I2C1 Event IRQ Handler
 */
void I2C1_EV_IRQHandler(void) {
	// I2C Status
	switch (i2c_status)
	{
	// Start Bit Sent
	case 0x00:
		if (SSD1306_I2Cx->SR1.REG & I2C_SR1_SB)
		{
			SSD1306_I2Cx->DR.REG = ((SSD1306_I2C_ADDRESS << 1) | I2Cx_WRITE);
			i2c_status = 0x01;
		}
		break;

	// Address Sent
	case 0x01:
		if (SSD1306_I2Cx->SR1.REG & I2C_SR1_ADDR)
		{
			volatile uint32_t temp = SSD1306_I2Cx->SR1.REG;
			temp = SSD1306_I2Cx->SR2.REG;
			// Now TxE is ready
			if (SSD1306_I2Cx->SR1.REG & I2C_SR1_TXE)
			{
				// Command Buffer Transfer
				if (dma_status == DMA_STATUS_CMD)
					SSD1306_I2Cx->DR.REG = SSD1306_CMD_INDICATOR;
				// Data Buffer Transfer
				else if (dma_status == DMA_STATUS_DATA)
					SSD1306_I2Cx->DR.REG = SSD1306_DATA_INDICATOR;
				// Update I2C Status
				i2c_status = 0x02;
			}
		}
		break;

	// Enable DMA
	case 0x02:
		if (SSD1306_I2Cx->SR1.REG & I2C_SR1_BTF)
		{
			SSD1306_I2Cx->CR2.REG |= I2C_CR2_DMAEN;
			DMA_I2C1_TX->CCR.REG |= DMA_CCR_EN;
			i2c_status = 0x03;
		}
		break;
	}
}
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
/**
 * @brief DMA1 Channel6 IRQ Handler
 */
void DMA1_Channel6_IRQHandler(void) {
	// DMA Transfer Complete
	if (DMA1->ISR.REG & DMA_ISR_TCIF6) {
		// Disable DMA for I2C
		SSD1306_I2Cx->CR2.REG &= ~I2C_CR2_DMAEN;
		// Disable DMA Channel
		DMA_I2C1_TX->CCR.REG &= ~DMA_CCR_EN;
		// Update Status
		i2c_status = 0x00;
		dma_status = DMA_STATUS_COMPLETED;
		// Acknowledge the Interrupt
		DMA1->IFCR.REG |= DMA_IFCR_CTCIF6;
	}
}
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
/**
 * @brief I2C1 Error IRQ Handler
 */
void I2C1_ER_IRQHandler(void) {
	// Arbitration Lost Flag
	if (SSD1306_I2Cx->SR1.REG & I2C_SR1_AF)
	{
		// Clear NACK flag
		SSD1306_I2Cx->SR1.REG &= ~I2C_SR1_AF;
		// Force stop
		SSD1306_I2Cx->CR1.REG |= I2C_CR1_STOP;
		// Reset state machine
		i2c_status = 0x00;
	}
}
/*-------------------------------------------------------------------------------*/