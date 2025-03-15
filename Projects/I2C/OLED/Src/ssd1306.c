// Header File
#include "ssd1306.h"

/**
 * @brief Initializes the SSD1306 display
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] cmdArray Command array for initialization
 * @param[in] cmdArrayLen Length of the command array
 */
static void __SSD1306_Init__(I2C_REG_STRUCT* I2Cx, uint8_t* cmdArray, uint8_t cmdArrayLen){
	// Local Variable
	uint32_t temp = 0x00;

    // Enable I2C Module
    I2C_enable(I2Cx);
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

	// Command Indicator
	I2C_writeByte(I2Cx, SSD1306_CMD_INDICATOR);
	// Wait for TXE and BTF flags (EV8_2)
	while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));

	// Send the Commands
	for(uint8_t i = 0; i < cmdArrayLen; i++){
		// Send Command
		I2C_writeByte(I2Cx, cmdArray[i]);
		// Wait for TXE and BTF flags (EV8_2)
		while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	}

    // Generate STOP condition
	I2C_sendStop(I2Cx);
	// Wait until STOP condition is generated
	while (!(I2C_busReady(I2Cx)));
}

/**
 * @brief Initializes the SSD1306 display
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
void SSD1306_Init(I2C_REG_STRUCT* I2Cx){
	// Internal Array
	SSD1306_I2C_CMD_Array(I2Cx, SSD1306_initCmd, (sizeof(SSD1306_initCmd)/sizeof(SSD1306_initCmd[0])));
}

/**
 * @brief Transmits the custom commands to SSD1306
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] cmdArray Pointer to array storing the SSD1306 Commands
 * @param[in] cmdArrayLen Length of the array storing the SSD1306 Commands
 * @note Takes care of complete I2C Sequence as well 
 */
void SSD1306_I2C_CMD_Array(I2C_REG_STRUCT* I2Cx, uint8_t* cmdArray, uint16_t cmdArrayLen){
	// Occupy the I2C Bus
	SSD1306_I2C_Init(I2Cx);
	// Send the Command Array
	SSD1306_SendCMDArray(I2Cx, cmdArray, cmdArrayLen);
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
void SSD1306_I2C_Data_Array(I2C_REG_STRUCT* I2Cx, uint8_t* dataArray, uint16_t dataArrayLen){
	// Occupy the I2C Bus
	SSD1306_I2C_Init(I2Cx);
	// Send the Command Array
	SSD1306_SendDataArray(I2Cx, dataArray, dataArrayLen);
	// Free the I2C Bus
	SSD1306_I2C_End(I2Cx);
}

