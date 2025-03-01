// Dependency
#include "i2c.h"

// I2C2 SCL
gpio_config_t I2C2_SCL = {
	.GPIOx = GPIOB,
	.PINx = GPIO_PIN_10,
	.MODEx = MODE_OUT_50MHz,
	.CNFx = CNF_OUT_AF_OD
};
// I2C2 SDA
gpio_config_t I2C2_SDA = {
	.GPIOx = GPIOB,
	.PINx = GPIO_PIN_11,
	.MODEx = MODE_OUT_50MHz,
	.CNFx = CNF_OUT_AF_OD
};

/**
 * @brief Configures I2C as per the Configuration Structure
 * @param[in] I2C_CONFIGx I2C Configuration Structure
 */
void I2C_config(i2c_config_t* I2C_CONFIGx){
	// Enable Clock
	I2C_clk_enable(I2C_CONFIGx->I2Cx);
	// Configure GPIOs
	config_GPIO(I2C_CONFIGx->SCL);
	config_GPIO(I2C_CONFIGx->SDA);
	// Software Reset
	I2C_CONFIGx->I2Cx->CR1.REG |= I2C_CR1_SWRST;
	I2C_CONFIGx->I2Cx->CR1.REG &= ~I2C_CR1_SWRST;
	// I2C Module Frequency
	I2C_CONFIGx->I2Cx->CR2.REG |= (I2C_CONFIGx->freq_MHz & 0x3F) << I2C_CR2_FREQ_Pos;
	// I2C Mode + I2C Duty + I2C Clock Control Register
	I2C_CONFIGx->I2Cx->CCR.REG |= (((I2C_CONFIGx->mode & 0x01) << I2C_CCR_FS_Pos) |
									((I2C_CONFIGx->duty & 0x01) << I2C_CCR_DUTY_Pos) | 
									(I2C_CONFIGx->CCR & 0x0FFF) << I2C_CCR_CCR_Pos);
	// TRISE Configuration
	I2C_CONFIGx->I2Cx->TRISE.REG = (I2C_CONFIGx->TRISE & 0x3F) << I2C_TRISE_TRISE_Pos;
}

/**
 * @brief I2C Slave Address Send
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address to be TX
 * @returns - 0: Failure
 * @returns - 1: Success
 */
uint8_t I2C_sendAddress(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress){
	// TODO: Arbitration Logic
	// Transmit Slave Address
	I2Cx->DR.REG = slaveAddress; // SB Cleared
	// Wait till successful transmission of Address
	if((I2Cx->SR1.REG & I2C_SR1_TXE) || (I2Cx->SR1.REG & I2C_SR1_RXNE))
		// Success
		return (uint8_t) 0x01;
	else
		// Failure
		return (uint8_t) 0x00;
}

/**
 * @brief I2C Byte Send
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] data Data to be TX
 * @returns - 0: Failure
 * @returns - 1: Success
 */
uint8_t I2C_sendByte(I2C_REG_STRUCT* I2Cx, uint8_t data){
	// Send data
	I2Cx->DR.REG = data;
	// Transmission Success
	if(I2Cx->SR1.REG & I2C_SR1_TXE)
		return (uint8_t) 0x01;
	// Transmission Failure
	else
		return (uint8_t) 0x00;
}

/**
 * @brief I2C Event Check
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
uint32_t I2C_checkEvent(I2C_REG_STRUCT* I2Cx){
	// Local Variables
	uint16_t temp = 0x0000;
	uint32_t event = 0x00000000;
	// Read SR1
	event = I2Cx->SR1.REG;
	// Read SR2
	temp = I2Cx->SR2.REG;
	// Past Event Combination
	event &= 0xFFFF;
	event |= ((temp & 0xFFFF) << 16);
	// Return the Event Sequence
	return event;
}