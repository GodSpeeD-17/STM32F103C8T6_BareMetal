// Header File
#include "ssd1306.h"

// Co-ordinate Storing Structure
static SSD1306_pix_t SSD1306_coordinates = {
	.X = 0,
	.Y = 0,
};

/**
 * @brief Initializes the SSD1306 display
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
void SSD1306_init(I2C_REG_STRUCT* I2Cx){
	// Internal Array
	SSD1306_I2C_cmdArray(I2Cx, SSD1306_initCmd, (sizeof(SSD1306_initCmd)/sizeof(SSD1306_initCmd[0])));
	// __SSD1306_Init__(I2Cx, SSD1306_initCmd, (sizeof(SSD1306_initCmd)/sizeof(SSD1306_initCmd[0]))); // Wrong Method
}

/**
 * @brief Transmits the custom commands to SSD1306
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] cmd SSD1306 Command
 * @note Takes care of complete I2C Sequence as well 
 */
void SSD1306_I2C_CMD(I2C_REG_STRUCT* I2Cx, uint8_t cmd){
	// Occupy the I2C Bus
	SSD1306_I2C_Start(I2Cx);
	// Send the Command Array
	SSD1306_sendCMD(I2Cx, cmd);
	// Free the I2C Bus
	SSD1306_I2C_End(I2Cx);
}

/**
 * @brief Transmits the custom commands to SSD1306
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] cmdArray Pointer to array storing the SSD1306 Commands
 * @param[in] cmdArrayLen Length of the array storing the SSD1306 Commands
 * @note Takes care of complete I2C Sequence as well 
 */
void SSD1306_I2C_cmdArray(I2C_REG_STRUCT* I2Cx, uint8_t* cmdArray, uint16_t cmdArrayLen){
	// Occupy the I2C Bus
	SSD1306_I2C_Start(I2Cx);
	// Send the Command Array
	SSD1306_sendCMDArray(I2Cx, cmdArray, cmdArrayLen);
	// Free the I2C Bus
	SSD1306_I2C_End(I2Cx);
}

/**
 * @brief Transmits the custom commands to SSD1306
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] data SSD1306 Command
 * @note Takes care of complete I2C Sequence as well 
 */
void SSD1306_I2C_Data(I2C_REG_STRUCT* I2Cx, uint8_t data){
	// Occupy the I2C Bus
	SSD1306_I2C_Start(I2Cx);
	// Send the Command Array
	SSD1306_sendData(I2Cx, data);
	// Free the I2C Bus
	SSD1306_I2C_End(I2Cx);
}

/**
 * @brief Transmits the data to SSD1306
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] dataArray Pointer to array storing the Data
 * @param[in] dataArrayLen Length of the array storing the Data
 * @note Takes care of complete I2C Sequence as well 
 */
void SSD1306_I2C_dataArray(I2C_REG_STRUCT* I2Cx, uint8_t* dataArray, uint16_t dataArrayLen){
	// Occupy the I2C Bus
	SSD1306_I2C_Start(I2Cx);
	// Send the Command Array
	SSD1306_sendDataArray(I2Cx, dataArray, dataArrayLen);
	// Free the I2C Bus
	SSD1306_I2C_End(I2Cx);
}

/**
 * @brief Sets the Column Range
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] start Starting Column
 * @param[in] end Ending Column
 * @note Only valid for Horizontal & Vertical Addressing Mode
 */
void SSD1306_setColumnRange(I2C_REG_STRUCT* I2Cx, uint8_t start, uint8_t end){
	// I2C Start
	SSD1306_I2C_Start(I2Cx);
	// Command
	I2C_writeByte(I2Cx, SSD1306_CMD_SET_COL_ADDR);
	// Wait for TXE and BTF flags (EV8_2)
	while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	// Start Column
	I2C_writeByte(I2Cx, start);
	// Wait for TXE and BTF flags (EV8_2)
	while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	// End Column
	I2C_writeByte(I2Cx, end);
	// Wait for TXE and BTF flags (EV8_2)
	while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	// I2C End
	SSD1306_I2C_End(I2Cx);
}

/**
 * @brief Sets the Page Range
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] start Starting Page
 * @param[in] end Ending Page
 * @note Only valid for Horizontal & Vertical Addressing Mode
 */
void SSD1306_setPageRange(I2C_REG_STRUCT* I2Cx, uint8_t start, uint8_t end){
	// I2C Start
	SSD1306_I2C_Start(I2Cx);
	// Command
	I2C_writeByte(I2Cx, SSD1306_CMD_SET_PAGE_ADDR);
	// Wait for TXE and BTF flags (EV8_2)
	while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	// Start Column
	I2C_writeByte(I2Cx, start);
	// Wait for TXE and BTF flags (EV8_2)
	while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	// End Column
	I2C_writeByte(I2Cx, end);
	// Wait for TXE and BTF flags (EV8_2)
	while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	// I2C End
	SSD1306_I2C_End(I2Cx);
}

/**
 * @brief Retrieves the current X-Coordinate
 * @returns Current X-Coordinate
 */
uint8_t SSD1306_getX(void){
	return SSD1306_coordinates.X;
}

/**
 * @brief Retrieves the current Y-Coordinate
 * @returns Current Y-Coordinate
 */
uint8_t SSD1306_getY(void){
	return SSD1306_coordinates.Y;
}

/**
 * @brief Directs to the Pixel Pointer
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] X X-Coordinate (Along the Columns)
 * @param[in] Y Y-Coordinate (Along the Page)
 * @note Only valid for Page Addressing Mode
 */
void SSD1306_gotoXY(I2C_REG_STRUCT* I2Cx, uint8_t X, uint8_t Y){
	// Wrap X, Y
	X &= 0x7F; Y &= 0x3F; 
	// Mathematical Calculations to obtain the Commands
	uint8_t cmdArray[3] = {SSD1306_CMD_PAGE_MODE_SET_PAGE(0) + ((Y >> 3) & 0x07), 
						   SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE(0) + (X & 0x0F),
						   SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE(0) + ((X & 0xF0) >> 4)};
	// Send the Commands
	SSD1306_I2C_cmdArray(I2Cx, cmdArray, 3);
	// Update the co-ordinates
	SSD1306_coordinates.X = X;
	SSD1306_coordinates.Y = Y;
}

/**
 * @brief Fills the whole Display with input color
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] color 0x00: Black; 0xFF: White
 * @note Column Storage: TOP: LSB --> BOTTOM: MSB
 */
void SSD1306_fillDisp(I2C_REG_STRUCT* I2Cx, uint8_t color){
	// Command Array
	uint8_t cmdArray[3] = {SSD1306_CMD_PAGE_MODE_SET_PAGE(0), SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE(0), SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE(0)};
	// Data Array
	uint8_t data[SSD1306_WIDTH];
	for(uint8_t i = 0; i < SSD1306_WIDTH; i++){
		data[i] = color;
	}
	// Traverse through Pages
	for(uint8_t page = 1; page <= 8; page++){
		// Page Command
		SSD1306_I2C_cmdArray(I2Cx, cmdArray, (sizeof(cmdArray)/sizeof(cmdArray[0])));
		cmdArray[0] = (uint8_t) (SSD1306_CMD_PAGE_MODE_SET_PAGE(0) + page);
		// Traverse through Columns
		SSD1306_I2C_dataArray(I2Cx, data, (sizeof(data)/sizeof(data[0])));
	}
}

/**
 * @brief Fills the rectangle
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] X1 Top left X-coordinate
 * @param[in] Y1 Top left Y-coordinate
 * @param[in] X2 Bottom right X-coordinate
 * @param[in] Y2 Bottom right Y-coordinate
 */
void SSD1306_fillRect(I2C_REG_STRUCT* I2Cx, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2){
	// TODO: Implement this logic
	if((X1 > X2) || (Y1 > Y2))
		return;
	// Bounds checking
	X1 &= 0x7F; X2 &= 0x7F;
	Y1 &= 0x3F; Y2 &= 0x3F;
	// Local Variables	
	const uint8_t page_end = ((Y2 >> 3) & 0x07);
	const uint8_t column_start_lower_nibble = (X1 & 0x0F);
	const uint8_t column_start_upper_nibble = ((X1 & 0xF0) >> 4);
	uint8_t current_page = ((Y1 >> 3) & 0x07), current_Y = Y1;

	// Command Array
	uint8_t cmdArray[3] = {SSD1306_CMD_PAGE_MODE_SET_PAGE(0) + current_page, SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE(0) + column_start_lower_nibble, SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE(0) + column_start_upper_nibble};
	uint8_t dataArray[(X2 - X1) + 1]; // +1: 0-indexed
	uint8_t temp = 0x00;
	// Loop
	do{
		// Same Page
		if(current_page == page_end){
			// Column Pattern
			temp = 0x00;
			// Page Start Boundary -> Cover Upper Portion
			if(current_Y & 0x07 == 0){
				temp = 0xFF >> (7 - (Y2 - current_Y));
			}
			// Random Middle Portion
			else{
				// Generate Appropriate Mask 
				for(uint8_t i = 0; i < (Y2 - current_Y); i++){
					temp |= (0x01 << ((current_Y & 0x07) + i));
				}
			}
		}
		// Different Pages
		else{
			// Column Pattern
			temp = ((current_page + 1) * 8) - current_Y;
			temp = 0xFF << ((temp > 7) ? 0 : temp);
		}

		// Update Data Array
		for(uint8_t i = 0; i < ((X2 - X1) + 1); i++){
			dataArray[i] = temp;
		}

		// Send the Commands
		SSD1306_I2C_cmdArray(I2Cx, cmdArray, (sizeof(cmdArray)/sizeof(cmdArray[0])));
		// Send the Data
		SSD1306_I2C_dataArray(I2Cx, dataArray, (sizeof(dataArray)/sizeof(dataArray[0])));
		// Update Variables
		cmdArray[0] += 1; 
		current_page++;
		current_Y = current_page * 8;
		temp = 0x00;
	}
	while(current_page <= page_end);
}

/**
 * @brief Displays a single character
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] c Character to display
 */
void SSD1306_I2C_dispChar(I2C_REG_STRUCT* I2Cx, char c){
	// Send character data
	SSD1306_I2C_dataArray(I2Cx, font8x8[font_get_index(font8x8, c)], 8);
}

/**
 * @brief Displays a string
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] str String to display
 * @param[in] strLength Length of String
 */
void SSD1306_I2C_dispString(I2C_REG_STRUCT* I2Cx, const char* str){
	// Local Variable
	char c = 0xFF; uint8_t index = 0;
	// Capture I2C Bus
	SSD1306_I2C_Start(I2Cx);
	// Data Indicator
	SSD1306_writeByte(I2Cx, 0xFF, SSD1306_DATA_INDICATOR);
	// Transmit the Data
	while(*str != '\0'){
		// Get Current Value of String
		c = *str++;
		// Send character data
		SSD1306_writeBytes(I2Cx, 0xFF, font8x8[font_get_index(font8x8, c)], 8);
	}
	// Free I2C Bus
	SSD1306_I2C_End(I2Cx);
}

/**
 * @brief Displays input image on the screen
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] dataArray The array of data
 * @note The data size should be of 1024 bytes
 */
void SSD1306_I2C_dispFullScreen(I2C_REG_STRUCT* I2Cx, const uint8_t* dataArray){
	// Command Array
	uint8_t cmdArray[3] = {SSD1306_CMD_PAGE_MODE_SET_PAGE(0), 
		SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE(0),
		SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE(0)};
	// Go to (X,Y) = (0,0)
	SSD1306_gotoXY(I2Cx, 0, 0);
	// Traverse Pages
	for(uint8_t page = 0; page < 8; page++){
		// Send Page Address
		SSD1306_I2C_cmdArray(I2Cx, cmdArray, 3);
		// Update it to next page
		cmdArray[0] = SSD1306_CMD_PAGE_MODE_SET_PAGE(0) + page + 1;
		// Send Data for all the 128 columns for a single page
		SSD1306_I2C_dataArray(I2Cx, (dataArray + (page * 128)), 128);
	}
}

