// Header Guards
#ifndef __SSD1306_H__
#define __SSD1306_H__

#include "i2c.h"

// SSD1306 I2C Address
#ifndef SA0
	#define SSD1306_I2C_ADDRESS					((uint8_t) 0x3C)
#else
	#define SSD1306_I2C_ADDRESS					((uint8_t) 0x3D)
#endif

// SSD1306 Characteristics
#define SSD1306_HEIGHT						((uint8_t) 64)
#define SSD1306_WIDTH						((uint8_t) 128)

/*
// Double byte command to select 1 out of 256 contrast steps
#define SSD1306_CMD_SET_CONTRAST					((uint8_t) 0x81)
// Resume to RAM content display, Output follows RAM content
#define SSD1306_CMD_ENTIRE_DISP_ON_OUT_RAM			((unit8_t) 0xA4)
// Entire display ON, Output ignores RAM content
#define SSD1306_CMD_ENTIRE_DISP_ON					((unit8_t) 0xA5)
// Normal display
#define SSD1306_CMD_DISP_NORMAL						((unit8_t) 0xA6)
// Inverse display
#define SSD1306_CMD_DISP_INVERSE					((unit8_t) 0xA7)
// Display OFF
#define SSD1306_CMD_DISP_OFF						((unit8_t) 0xAE)
// Display ON
#define SSD1306_CMD_DISP_ON							((unit8_t) 0xAF)
// Horizontal Scroll (1 Column)
#define SSD1306_CMD_RIGHT_HSCROLL					((unit8_t) 0x26)
#define SSD1306_CMD_LEFT_HSCROLL					((unit8_t) 0x27)
// Memory Addressing Mode
#define SSD1306_CMD_MEM_ADDR_MODE					((unit8_t) 0x20)
// No Operation
#define SSD1306_CMD_NOP								((uint8_t) 0xE3)


*/

// Command Table
// Double byte command to select 1 out of 256 contrast steps
#define SSD1306_CMD_SET_CONTRAST                (0x81)
// Resume to RAM content display, Output follows RAM content
#define SSD1306_CMD_ENTIRE_DISP_ON_OUT_RAM      (0xA4)
// Entire display ON, Output ignores RAM content
#define SSD1306_CMD_ENTIRE_DISP_ON              (0xA5)
// Normal display
#define SSD1306_CMD_DISP_NORMAL                 (0xA6)
// Inverse display
#define SSD1306_CMD_DISP_INVERSE                (0xA7)
// Display OFF
#define SSD1306_CMD_DISP_OFF                    (0xAE)
// Display ON
#define SSD1306_CMD_DISP_ON                     (0xAF)
// Set display clock divide ratio/oscillator frequency
#define SSD1306_CMD_SET_DISPLAY_CLOCK_DIV       (0xD5)
// Set multiplex ratio (1/64 duty)
#define SSD1306_CMD_SET_MULTIPLEX               (0xA8)
// Set display offset
#define SSD1306_CMD_SET_DISPLAY_OFFSET          (0xD3)
// Set display start line
#define SSD1306_CMD_SET_START_LINE              (0x40)
// Enable charge pump
#define SSD1306_CMD_CHARGE_PUMP                 (0x8D)
// Set memory addressing mode
#define SSD1306_CMD_MEM_ADDR_MODE               (0x20)
// Set segment re-map (column address 127 is mapped to SEG0)
#define SSD1306_CMD_SET_SEGMENT_REMAP           (0xA1)
// Set COM output scan direction (remapped mode, scan from COM[N-1] to COM0)
#define SSD1306_CMD_SET_COM_SCAN_DIR            (0xC8)
// Set COM pins hardware configuration
#define SSD1306_CMD_SET_COM_PINS                (0xDA)
// Set contrast control
#define SSD1306_CMD_SET_CONTRAST                (0x81)
// Set pre-charge period
#define SSD1306_CMD_SET_PRECHARGE               (0xD9)
// Set VCOMH deselect level
#define SSD1306_CMD_SET_VCOMH_DESELECT          (0xDB)
// Resume to RAM content display
#define SSD1306_CMD_RESUME_TO_RAM_CONTENT       (0xA4)
// Set normal display (non-inverted)
#define SSD1306_CMD_SET_NORMAL_DISPLAY          (0xA6)
// Display ON
#define SSD1306_CMD_DISPLAY_ON                  (0xAF)
// Set Column Address
#define SSD1306_CMD_SET_COL_ADDR				(0x21)
// Set Page Address
#define SSD1306_CMD_SET_PAGE_ADDR				(0x22)

// Memory Addressing Mode Options
#define SSD1306_MEM_ADDR_MODE_H					(0x00)
#define SSD1306_MEM_ADDR_MODE_V					(0x01)
#define SSD1306_MEM_ADDR_MODE_PAGE				(0x02)
// Indicator regarding the sent bytes
#define SSD1306_CMD_INDICATOR					(0x00)
#define SSD1306_DATA_INDICATOR					(0x40)

/**
 * @brief Single SSD1306 Command
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] Command Command
 */
#define SSD1306_SendCMD(I2Cx, Command)							(SSD1306_writeByte((I2Cx), 1, (Command)))

/**
 * @brief SSD1306 Multiple Command
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] CMDArray Pointer to Command Array
 * @param[in] ArrayLen Length of the Command Array
 */
#define SSD1306_SendCMDArray(I2Cx, CMDArray, ArrayLen)			(SSD1306_writeBytes((I2Cx), 1, (CMDArray), (ArrayLen)))

/**
 * @brief Single SSD1306 Data
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] Data Data
 */
#define SSD1306_SendData(I2Cx, Data)							(SSD1306_writeByte((I2Cx), 0, (Data)))

/**
 * @brief SSD1306 Multiple Data
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] DataArray Pointer to Data Array
 * @param[in] ArrayLen Length of the Data Array
 */
#define SSD1306_SendDataArray(I2Cx, DataArray, ArrayLen)		(SSD1306_writeBytes((I2Cx), 0, (DataArray), (ArrayLen)))

// Initialization sequence for SSD1306
static const uint8_t SSD1306_initCmd[] = {
    SSD1306_CMD_DISP_OFF,									// Display OFF
    SSD1306_CMD_SET_DISPLAY_CLOCK_DIV, 0x80,				// Set display clock divide ratio/oscillator frequency
    SSD1306_CMD_SET_MULTIPLEX, 0x3F,						// Set multiplex ratio (1/64 duty)
    SSD1306_CMD_SET_DISPLAY_OFFSET, 0x00,					// Set display offset
    SSD1306_CMD_SET_START_LINE,								// Set display start line
    SSD1306_CMD_CHARGE_PUMP, 0x14,							// Enable charge pump
    SSD1306_CMD_MEM_ADDR_MODE, SSD1306_MEM_ADDR_MODE_PAGE,	// Set memory addressing mode to Page Addressing Mode (0x02)
    SSD1306_CMD_SET_SEGMENT_REMAP,							// Set segment re-map (column address 127 is mapped to SEG0)
    SSD1306_CMD_SET_COM_SCAN_DIR,							// Set COM output scan direction (remapped mode, scan from COM[N-1] to COM0)
    SSD1306_CMD_SET_COM_PINS, 0x12,							// Set COM pins hardware configuration
    SSD1306_CMD_SET_CONTRAST, 0xCF,							// Set contrast control
    SSD1306_CMD_SET_PRECHARGE, 0x22,						// Set pre-charge period
    SSD1306_CMD_SET_VCOMH_DESELECT, 0x20,					// Set VCOMH deselect level
    SSD1306_CMD_RESUME_TO_RAM_CONTENT,						// Resume to RAM content display
    SSD1306_CMD_SET_NORMAL_DISPLAY,							// Set normal display (non-inverted)
    SSD1306_CMD_DISPLAY_ON									// Display ON
};

/**
 * @brief Occupies the I2C Bus
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__attribute__((always_inline)) inline void SSD1306_I2C_Init(I2C_REG_STRUCT* I2Cx){
	// Local Variable
	uint32_t temp = 0x00;
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
 * @param[in] isCMD 0: Data, 1: Command
 * @param[in] data Data to be sent
 */
__attribute__((always_inline)) inline void SSD1306_writeByte(I2C_REG_STRUCT* I2Cx, uint8_t isCMD, uint8_t data){
	// Command transmission
	if(isCMD)
		I2C_writeByte(I2Cx, SSD1306_CMD_INDICATOR);
	// Data transmission
	else
		I2C_writeByte(I2Cx, SSD1306_DATA_INDICATOR);	
	// Wait for TXE and BTF flags (EV8_2)
	while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));

	// Data Transfer
	I2C_writeByte(I2Cx, data);	
	// Wait for TXE and BTF flags (EV8_2)
	while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
}

/**
 * @brief Common Implementation for Bytes Transfer
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] isCMD 0: Data, 1: Command
 * @param[in] array Pointer to array to be sent 
 * @param[in] arrayLength Length of array to be sent 
 */
__attribute__((always_inline)) inline void SSD1306_writeBytes(I2C_REG_STRUCT* I2Cx, uint8_t isCMD, uint8_t* array, uint16_t arrayLength){
	// Command transmission
	if(isCMD)
		I2C_writeByte(I2Cx, SSD1306_CMD_INDICATOR);
	// Data transmission
	else
		I2C_writeByte(I2Cx, SSD1306_DATA_INDICATOR);
	// Wait for TXE and BTF flags (EV8_2)
	while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));

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
__attribute__((always_inline)) inline void SSD1306_I2C_End(I2C_REG_STRUCT* I2Cx){
	// Generate STOP condition
	I2C_sendStop(I2Cx);
	// Wait until STOP condition is generated
	while (!(I2C_busReady(I2Cx)));
}

/**
 * @brief Initializes the SSD1306 display
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] cmdArray Command array for initialization
 * @param[in] cmdArrayLen Length of the command array
 */
static void __SSD1306_Init__(I2C_REG_STRUCT* I2Cx, uint8_t* cmdArray, uint8_t cmdArrayLen);

/**
 * @brief Initializes the SSD1306 display
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
void SSD1306_Init(I2C_REG_STRUCT* I2Cx);

/**
 * @brief Transmits the custom commands to SSD1306
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] cmdArray Pointer to array storing the SSD1306 Commands
 * @param[in] cmdArrayLen Length of the array storing the SSD1306 Commands
 * @note Takes care of complete I2C Sequence as well 
 */
void SSD1306_I2C_CMD_Array(I2C_REG_STRUCT* I2Cx, uint8_t* cmdArray, uint16_t cmdArrayLen);

/**
 * @brief Transmits the data to SSD1306
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] dataArray Pointer to array storing the Data
 * @param[in] dataArrayLen Length of the array storing the Data
 * @note Takes care of complete I2C Sequence as well 
 */
void SSD1306_I2C_Data_Array(I2C_REG_STRUCT* I2Cx, uint8_t* dataArray, uint16_t dataArrayLen);

#endif /* __SSD1306_H__ */ 