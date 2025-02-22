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
void config_I2C(i2c_config_t* I2C_CONFIGx){
	// Enable Clock
	enable_I2C_clk(I2C_CONFIGx);
	// Configure GPIOs
	config_GPIO(I2C_CONFIGx->SCL);
	config_GPIO(I2C_CONFIGx->SDA);
	// Software Reset
	I2C_CONFIGx->I2Cx->CR1.REG |= I2C_CR1_SWRST;
	I2C_CONFIGx->I2Cx->CR1.REG &= ~I2C_CR1_SWRST;
	// I2C Module Frequency
	I2C_CONFIGx->I2Cx->CR2.REG |= (I2C_CONFIGx->SCL_freq_MHz & 0x3F) << I2C_CR2_FREQ_Pos;
	// I2C Mode + I2C Duty + I2C Clock Control Register
	I2C_CONFIGx->I2Cx->CCR.REG |= (((I2C_CONFIGx->mode & 0x01) << I2C_CCR_FS_Pos) |
									((I2C_CONFIGx->duty & 0x01) << I2C_CCR_DUTY_Pos) | 
									calc_CRR(I2C_CONFIGx) << I2C_CCR_CCR_Pos);
}

/**
 * @brief START condition
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @note Operation Mode: Master
 */
void start_I2C(I2C_REG_STRUCT* I2Cx){
	// Start Sequence
	I2Cx->CR1.REG |= I2C_CR1_START;
	// Wait until Start Bit is sent
	while(!(I2Cx->SR1.REG & I2C_SR1_SB));
}

/***
 * @brief Sends I2C Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slave_address I2C Slave Address
 * @param[in] r_w `I2Cx_READ`,`I2Cx_WRITE`
 */
void send_I2C_addr(I2C_REG_STRUCT* I2Cx, uint8_t slave_address, uint8_t r_w){
	// Local Variable
	volatile uint16_t temp = 0x00;
	// Send Address
	I2Cx->DR.REG = ((slave_address << 1) | r_w);
	// Wait until I2C Slave Address is matched
	while(!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	// I2C Slave Address is matched
	while(I2Cx->SR1.REG & I2C_SR1_ADDR){
		temp = I2Cx->SR1.REG;
		temp = I2Cx->SR2.REG;
	}
}

/**
 * @brief Transmits the I2C Data
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] DATAx Data to be sent
 */
void send_I2C_data(I2C_REG_STRUCT* I2Cx, uint8_t DATAx){
	// Wait for TxE to be empty
	while(!(I2Cx->SR1.REG & I2C_SR1_TXE));
	// Store Data in Data Register
	I2Cx->DR.REG = DATAx;
	// Wait for TxE to be empty
	while(!(I2Cx->SR1.REG & I2C_SR1_TXE));
}

/**
 * @brief STOP Condition
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @note Operation Mode: Master
 */
void stop_I2C(I2C_REG_STRUCT* I2Cx){
	// Local Variable
	volatile uint16_t temp = 0x00;
	// Read Status Registers
	temp = I2Cx->SR1.REG;
	temp = I2Cx->SR2.REG;
	// Stop Sequence
	I2Cx->CR1.REG |= I2C_CR1_STOP;
}

/**
 * @brief I2C Communication Sequence
 * @param[in] I2C_DATAx I2C Data Structure
 */
void I2C_master_TX(i2c_data_t* I2C_DATAx){
	// START Condition
	start_I2C(I2C_DATAx->I2Cx);
	// Transmit Address
	send_I2C_addr(I2C_DATAx->I2Cx, I2C_DATAx->slave->address, I2C_DATAx->slave->r_w);
	// Local Variable
	uint8_t data = 0x00, index = 0x00;
	// Transmit Data
	for(index = 0x00; index < I2C_DATAx->slave->buff_len; index++){
		data = *(I2C_DATAx->slave->buffer + index);
		send_I2C_data(I2C_DATAx->I2Cx, data);
	}
	// STOP Condition
	stop_I2C(I2C_DATAx->I2Cx);
}

/**
 * @brief I2C Slave Address Send
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address to be TX
 * @returns 0: Failure; 1: Success
 */
uint8_t I2C_sendAddress(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress){
	// Transmit Slave Address
	I2Cx->DR.REG = slaveAddress;
	uint32_t status = I2Cx->SR1.REG;
	// Arbitration Lost
	if(status & I2C_SR1_ARLO)
		return (uint8_t) 0x00;
	// Address Sent
	if(status & I2C_SR1_ADDR){
		// Read SR2 to clear ADDR flag
		status = I2Cx->SR2.REG;
		return (uint8_t) 0x01;
	}
}

/**
 * @brief I2C Slave Address Send
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] data Data to be TX
 */
void I2C_sendData(I2C_REG_STRUCT* I2Cx, uint8_t data){
	// Send data
	I2Cx->DR.REG = data;
	uint32_t status = 0x00;
	// Transmission Success
	while(!(status & I2C_SR1_TXE));
}

