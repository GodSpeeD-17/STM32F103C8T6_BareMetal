/* ------------------------------------------------------------------------------------ */
// Header Guards
#ifndef __SSD1306_H__
#define __SSD1306_H__
/* ------------------------------------------------------------------------------------ */
// Includes
#include "reg_map.h"
#include "i2c.h"
#include "ssd1306_config.h"
#include "ssd1306_font.h"
/* ------------------------------------------------------------------------------------ */
/**
 * @brief Single SSD1306 Command
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] Command Command
 */
#define SSD1306_sendCMD(I2Cx, Command)							(SSD1306_writeByte((I2Cx), 1, (Command)))

/**
 * @brief SSD1306 Multiple Command
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] CMDArray Pointer to Command Array
 * @param[in] ArrayLen Length of the Command Array
 */
#define SSD1306_sendCMDArray(I2Cx, CMDArray, ArrayLen)			(SSD1306_writeBytes((I2Cx), 1, (CMDArray), (ArrayLen)))

/**
 * @brief Single SSD1306 Data
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] Data Data
 */
#define SSD1306_sendData(I2Cx, Data)							(SSD1306_writeByte((I2Cx), 0, (Data)))

/**
 * @brief SSD1306 Multiple Data
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] DataArray Pointer to Data Array
 * @param[in] ArrayLen Length of the Data Array
 */
#define SSD1306_sendDataArray(I2Cx, DataArray, ArrayLen)		(SSD1306_writeBytes((I2Cx), 0, (DataArray), (ArrayLen)))

/**
 * @brief Clears the Screen (Black)
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2` 
 */
#define SSD1306_clrScr(I2Cx)									(SSD1306_fillDisp((I2Cx), 0x00))
/* ------------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------------ */
/**
 * @brief Occupies the I2C Bus
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__STATIC_INLINE__ void SSD1306_I2C_Start(I2C_REG_STRUCT* I2Cx){
	// Local Variable
	uint32_t temp = 0x00;
	// Wait till bus is ready
	while(!(I2C_busReady(I2Cx)));
	// Start Sequence
	I2C_sendStart(I2Cx);
	// Wait for Start condition (EV5)
	while (!(I2Cx->SR1.REG & I2C_SR1_SB));
	// Send Slave Address with Write Privilege
	I2C_writeAddress(I2Cx, SSD1306_I2C_ADDRESS);
	// Wait for ADDR flag (EV6)
	while (!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2Cx->SR1.REG; // Clear ADDR flag by reading SR1
	temp = I2Cx->SR2.REG; // Clear ADDR flag by reading SR2
	// Wait for TXE flag (EV8_1)
	while (!(I2Cx->SR1.REG & I2C_SR1_TXE));
}

/**
 * @brief Common Implementation for Byte Transfer
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] isCMD 0: Data, 1: Command, else: data
 * @param[in] data Data to be sent
 */
__STATIC_INLINE__ void SSD1306_writeByte(I2C_REG_STRUCT* I2Cx, uint8_t isCMD, uint8_t data){
	
	if(isCMD == 1){
		// Command transmission
		I2C_writeByte(I2Cx, SSD1306_CMD_INDICATOR);
		// Wait for TXE and BTF flags (EV8_2)
		while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	}
	else if (isCMD == 0){
		// Data transmission
		I2C_writeByte(I2Cx, SSD1306_DATA_INDICATOR);	
		// Wait for TXE and BTF flags (EV8_2)
		while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	}

	// Data Transfer
	I2C_writeByte(I2Cx, data);	
	// Wait for TXE and BTF flags (EV8_2)
	while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
}

/**
 * @brief Common Implementation for Bytes Transfer
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] isCMD - 0: Data
 * 					- 1: Command
 * 					- else: array
 * @param[in] array Pointer to array to be sent 
 * @param[in] arrayLength Length of array to be sent 
 */
__STATIC_INLINE__ void SSD1306_writeBytes(I2C_REG_STRUCT* I2Cx, uint8_t isCMD, uint8_t* array, uint16_t arrayLength){
	
	if(isCMD == 1){
		// Command transmission
		I2C_writeByte(I2Cx, SSD1306_CMD_INDICATOR);
		// Wait for TXE and BTF flags (EV8_2)
		while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	}
	else if (isCMD == 0){
		// Data transmission
		I2C_writeByte(I2Cx, SSD1306_DATA_INDICATOR);	
		// Wait for TXE and BTF flags (EV8_2)
		while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	}

	// Transmit the whole Array
	for(uint16_t i = 0; i < arrayLength; i++){
		// Transmit the Byte
		I2C_writeByte(I2Cx, array[i]);
		// Wait for TXE and BTF flags (EV8_2)
		while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	}
}

/**
 * @brief Frees the I2C Bus
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__STATIC_INLINE__ void SSD1306_I2C_End(I2C_REG_STRUCT* I2Cx){
	// Generate STOP condition
	I2C_sendStop(I2Cx);
	// Wait until STOP condition is generated
	while (!(I2C_busReady(I2Cx)));
}

/**
 * @brief Initializes the SSD1306 display
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__STATIC_INLINE__ void SSD1306_Init(I2C_REG_STRUCT* I2Cx){
	// Internal Array
	SSD1306_I2C_cmdArray(I2Cx, SSD1306_initCmd, (sizeof(SSD1306_initCmd)/sizeof(SSD1306_initCmd[0])));
}

/**
 * @brief Transmits the custom commands to SSD1306
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] cmd SSD1306 Command
 * @note Takes care of complete I2C Sequence as well 
 */
void SSD1306_I2C_CMD(I2C_REG_STRUCT* I2Cx, uint8_t cmd);

/**
 * @brief Transmits the custom commands to SSD1306
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] cmdArray Pointer to array storing the SSD1306 Commands
 * @param[in] cmdArrayLen Length of the array storing the SSD1306 Commands
 * @note Takes care of complete I2C Sequence as well 
 */
void SSD1306_I2C_cmdArray(I2C_REG_STRUCT* I2Cx, uint8_t* cmdArray, uint16_t cmdArrayLen);

/**
 * @brief Transmits the custom commands to SSD1306
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] data SSD1306 Command
 * @note Takes care of complete I2C Sequence as well 
 */
void SSD1306_I2C_Data(I2C_REG_STRUCT* I2Cx, uint8_t data);

/**
 * @brief Transmits the data to SSD1306
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] dataArray Pointer to array storing the Data
 * @param[in] dataArrayLen Length of the array storing the Data
 * @note Takes care of complete I2C Sequence as well 
 */
void SSD1306_I2C_dataArray(I2C_REG_STRUCT* I2Cx, uint8_t* dataArray, uint16_t dataArrayLen);

/**
 * @brief Sets the Column Range
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] start Starting Column
 * @param[in] end Ending Column
 * @note Only valid for Horizontal & Vertical Addressing Mode
 */
void SSD1306_setColumnRange(I2C_REG_STRUCT* I2Cx, uint8_t start, uint8_t end);

/**
 * @brief Sets the Page Range
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] start Starting Page
 * @param[in] end Ending Page
 * @note Only valid for Horizontal & Vertical Addressing Mode
 */
void SSD1306_setPageRange(I2C_REG_STRUCT* I2Cx, uint8_t start, uint8_t end);

/**
 * @brief Retrieves the current X-Coordinate
 * @returns Current X-Coordinate
 */
uint8_t SSD1306_DMA_Get_Cursor_X(void);

/**
 * @brief Retrieves the current Y-Coordinate
 * @returns Current Y-Coordinate
 */
uint8_t SSD1306_DMA_Get_Cursor_Y(void);

/**
 * @brief Directs to the Pixel Pointer
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] X X-Coordinate (Along the Columns)
 * @param[in] Y Y-Coordinate (Along the Page)
 * @note Only valid for Page Addressing Mode
 */
void SSD1306_gotoXY(I2C_REG_STRUCT* I2Cx, uint8_t X, uint8_t Y);

/**
 * @brief Fills the whole Display with input color
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] color 0x00: Black; 0xFF: White
 */
void SSD1306_fillDisp(I2C_REG_STRUCT* I2Cx, uint8_t color);

/**
 * @brief Fills the rectangle
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] X1 Top left X-coordinate
 * @param[in] Y1 Top left Y-coordinate
 * @param[in] X2 Bottom right X-coordinate
 * @param[in] Y2 Bottom right Y-coordinate
 */
void SSD1306_fillRect(I2C_REG_STRUCT* I2Cx, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2);

/**
 * @brief Displays a single character
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] c Character to display
 */
void SSD1306_I2C_dispChar(I2C_REG_STRUCT* I2Cx, char c);

/**
 * @brief Displays a string
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] str String to display
 * @param[in] strLength Length of String
 */
void SSD1306_I2C_dispString(I2C_REG_STRUCT* I2Cx, const char* str);

/**
 * @brief Displays input image on the screen
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] dataArray The array of data
 * @note The data size should be of 1024 bytes
 */
void SSD1306_I2C_dispFullScreen(I2C_REG_STRUCT* I2Cx, const uint8_t* dataArray);

/**
 * @brief Write the data to the SSD1306 display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param data Pointer to the data buffer
 * @param size Size of the data buffer
 */
void SSD1306_I2C_Write(ssd1306_config_t* ssd1306, uint8_t* data, uint16_t size);

#endif /* __SSD1306_H__ */ 