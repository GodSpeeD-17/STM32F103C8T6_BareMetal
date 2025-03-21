// Dependency
#include "i2c.h"

// I2C1 GPIO Configuration
gpio_config_t I2C1_SCL = {
	.GPIOx = GPIOB,
	.PINx = GPIO_PIN_6,
	.MODEx = MODE_OUT_50MHz,
	.CNFx = CNF_OUT_AF_OD
};
gpio_config_t I2C1_SDA = {
	.GPIOx = GPIOB,
	.PINx = GPIO_PIN_7,
	.MODEx = MODE_OUT_50MHz,
	.CNFx = CNF_OUT_AF_OD
};

// I2C2 GPIO Configuration
gpio_config_t I2C2_SCL = {
	.GPIOx = GPIOB,
	.PINx = GPIO_PIN_10,
	.MODEx = MODE_OUT_50MHz,
	.CNFx = CNF_OUT_AF_OD
};
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
	GPIO_config(I2C_CONFIGx->SCL);
	GPIO_config(I2C_CONFIGx->SDA);
	// Software Reset
	I2C_CONFIGx->I2Cx->CR1.REG |= I2C_CR1_SWRST;
	I2C_CONFIGx->I2Cx->CR1.REG &= ~I2C_CR1_SWRST;
	// I2C Buffer IRQ + I2C Event IRQ + I2C Module Frequency
	I2C_CONFIGx->I2Cx->CR2.REG |= (((I2C_CONFIGx->buffer_IRQ & 0x01) << I2C_CR2_ITBUFEN_Pos) | 
								   ((I2C_CONFIGx->event_IRQ & 0x01) << I2C_CR2_ITEVTEN_Pos) | 
								   ((I2C_CONFIGx->freq_MHz & 0x3F) << I2C_CR2_FREQ_Pos));
	// I2C Mode + I2C Duty + I2C Clock Control Register
	I2C_CONFIGx->I2Cx->CCR.REG = (((I2C_CONFIGx->mode & 0x01) << I2C_CCR_FS_Pos) |
									((I2C_CONFIGx->duty & 0x01) << I2C_CCR_DUTY_Pos) | 
									(I2C_CONFIGx->CCR & 0x0FFF) << I2C_CCR_CCR_Pos);
	// TRISE Configuration
	I2C_CONFIGx->I2Cx->TRISE.REG = (I2C_CONFIGx->TRISE & 0x3F) << I2C_TRISE_TRISE_Pos;
	// Enable Interrupt
	if(I2C_CONFIGx->buffer_IRQ || I2C_CONFIGx->event_IRQ)
		NVIC_IRQ_enable(I2C_getEV_IRQn(I2C_CONFIGx->I2Cx));
}

/**
 * @brief I2C Event Check
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @returns Status of Event
 * @note `DO NOT USE THIS`
 */
uint32_t I2C_checkEvent(I2C_REG_STRUCT* I2Cx) {
	// Local Variables
	uint16_t sr2 = 0x0000;
	uint32_t event = 0x00000000;
	// Read SR1
	event = I2Cx->SR1.REG;
	// Read SR2
	sr2 = I2Cx->SR2.REG;
	// Combine SR1 and SR2 into a single event value
	event |= ((sr2 & 0xFFFF) << 16);
	// Mask out irrelevant bits
	event &= 0x000FFFFF;
	// Return the Event Sequence
	return event;
}

/**
 * @brief Calculates the value of Clock Control Register (CCR) for I2C Module
 * @param[in] i2cMode I2C Mode: `I2Cx_MODE_FAST`, `I2Cx_MODE_STD`
 * @param[in] i2cDuty I2C Duty: `I2Cx_DUTY_NORMAL`, `I2Cx_DUTY_FAST`
 * @param[in] i2cClockFrequencyMHz I2C Module Clock Frequency (Recommended APB1Clock)
 * @returns Calculated CCR value
 */
uint16_t I2C_calc_CCR(uint8_t i2cMode, uint8_t i2cDuty, uint8_t i2cClockFrequencyMHz){
	// Local Value
	uint32_t calculated_CCR = 0;
	// I2C Module Frequency (Tfreq)
	// Tfreq_us = (1/`freq_MHz`);
	// Tfreq_ns = 1000 * Tfreq_us -> Tfreq_ns = (1000/`freq_MHz`); .... [1]
	// I2C Mode
	switch(i2cMode){
		// I2C Standard Mode: 100kHz
		case I2Cx_MODE_STD:
			// Calculation reference is ns (Simplifies Calculation as it can be completed using `uint16_t`)
			// Thigh = Tlow -> T = Thigh + Tlow -> T = 2 * Thigh -> Thigh = (T/2)
			// Thigh = CCR * Tfreq -> Thigh_ns = CCR * Tfreq_ns -> CCR = (Thigh_ns/Tfreq_ns) -> CCR = (Tns/(2*Tfreq_ns));
			// CCR = (Tns * `freq_MHz` / (2 * 1000)); ..... {Refer 1}
			// calculated_CCR = ((I2C_MODE_STD_TIME_NS * i2cClockFrequencyMHz)/(2 * 1000));
// 			calculated_CCR = (i2cClockFrequencyMHz * FREQ_1MHz);
			calculated_CCR = ((i2cClockFrequencyMHz * FREQ_1MHz)/(I2Cx_SPEED_STD << 1));
		break;
		// I2C Fast Mode: 400kHz
		case I2Cx_MODE_FAST:
			// Tlow/Thigh = 16/9 -> Tlow = (16/9*Thigh) -> T = Tlow + Thigh -> T = Thigh * (1 + 16/9) -> T = Thigh * 25/9 -> Thigh = 9/25 * T -> Thigh_ns = ((9 * Tns)/25));
			// Thigh = 9 * CCR * Tfreq -> Thigh_ns = (9 * CCR * Tfreq_ns) -> (9 * Tns)/25 = 9 * CCR * Tfreq_ns -> Tns / 25 = CCR * Tfreq_ns -> CCR = Tns / (25 * Tfreq_ns);
			// CCR = (Tns * `freq_MHz`)/(25 * 1000);
			if(i2cDuty){
				calculated_CCR = ((i2cClockFrequencyMHz * FREQ_1MHz)/(25 * I2Cx_SPEED_FAST));
			}
			// Tlow/Thigh = 2 -> Tlow = 2 * Thigh -> T = Tlow + Thigh -> T = 3 * Thigh -> Thigh = T/3 -> Thigh_ns = Tns/3;
			// Thigh = CCR * Tfreq -> Thigh_ns = CCR * Tfreq_ns -> (Tns/3) = CCR * Tfreq_ns -> CCR = (Tns/(3*Tfreq_ns));
			// CCR = ((Tns * `freq_MHz`)/(3 * 1000)); .... {Refer 1}
			else{
				calculated_CCR = ((i2cClockFrequencyMHz * FREQ_1MHz)/(3 * I2Cx_SPEED_FAST));
			}
		break;
	}
	// Template Formula:
	// CCR = (I2C_CONFIGx->freq_MHz * `FREQ_1MHz`) / (<T_ns/Thigh_ns> * I2Cx_SPEED_y);
	// Return the value
	return (uint16_t) (calculated_CCR & 0xFFFF);
}

/**
 * @brief Calculates the value of TRISE (TRISE) for I2C Module
 * @param[in] i2cMode I2C Mode: `I2Cx_MODE_FAST`, `I2Cx_MODE_STD`
 * @returns Calculated TRISE value
 */
uint8_t I2C_calc_TRISE(uint8_t i2cMode){
	// Local Value
	uint8_t calc_TRISE = 0;
	// Get APB1 Clock (in MHz)
	calc_TRISE = (APB1Clock/FREQ_1MHz);
	// Fast I2C Mode: 400kHz
	if(i2cMode == I2Cx_MODE_FAST){
		calc_TRISE *= 3;
		calc_TRISE /= 10;
	}
	// Return the value
	return (calc_TRISE + 1);
}

/**
 * @brief Writes a Single Byte to Register Address of a given Slave Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slave_address MAX30102 Slave Address
 * @param[in] register Register Address
 * @param[in] byte Data to be written
 */
void I2C_writeRegisterByte(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress, uint8_t byte){
	// Local Variable
	uint32_t temp = 0x00;
	
	// Start Sequence
	I2C_sendStart(I2Cx);
	// Wait for Start condition (EV5)
	while(!(I2Cx->SR1.REG & I2C_SR1_SB));

	// Send Slave Address with Write Privilege
	I2C_writeAddress(I2Cx, slaveAddress);
	// Wait for ADDR flag (EV6)
	while(!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2Cx->SR1.REG; // Clear ADDR flag by reading SR1
	temp = I2Cx->SR2.REG; // Clear ADDR flag by reading SR2
	// Wait for TXE flag (EV8_1)
	while(!(I2Cx->SR1.REG & I2C_SR1_TXE));

	// Write Register Address
	I2C_writeByte(I2Cx, registerAddress);
	// Wait for TXE and BTF flags (EV8_2)
	while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	temp = I2Cx->SR1.REG; // Clearing BTF

	// Write Data Byte
	I2C_writeByte(I2Cx, byte);
	// Wait for TXE and BTF flags (EV8_2)
	while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));

	// Generate STOP condition
	I2C_sendStop(I2Cx);
	// Wait until STOP condition is generated
	while(!(I2C_busReady(I2Cx)));
}

/**
 * @brief Writes Multiple Consecutive Bytes to Register Address of a given Slave Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address
 * @param[in] registerAddress Starting Register Address
 * @param[in] data Pointer to the data buffer
 * @param[in] len Number of bytes to write
 */
void I2C_writeRegisterBlock(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, uint8_t len){
	// Local Variable
	uint32_t temp = 0x00;

	// Start Sequence
	I2C_sendStart(I2Cx);
	// Wait for Start condition (EV5)
	while (!(I2Cx->SR1.REG & I2C_SR1_SB));

	// Send Slave Address with Write Privilege
	I2C_writeAddress(I2Cx, slaveAddress);
	// Wait for ADDR flag (EV6)
	while (!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2Cx->SR1.REG; // Clear ADDR flag by reading SR1
	temp = I2Cx->SR2.REG; // Clear ADDR flag by reading SR2

	// Wait for TXE flag (EV8_1)
	while (!(I2Cx->SR1.REG & I2C_SR1_TXE));
	// Write Starting Register Address
	I2C_writeByte(I2Cx, registerAddress);
	// Wait for TXE and BTF flags (EV8_2)
	while (!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));

	// Write Multiple Bytes
	for (uint8_t i = 0; i < len; i++) {
		// Write Data Byte
		I2C_writeByte(I2Cx, data[i]);
		// Wait for TXE and BTF flags (EV8_2)
		while(!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));
	}

	// Generate STOP condition
	I2C_sendStop(I2Cx);
	// Wait until STOP condition is generated
	while (!(I2C_busReady(I2Cx)));
}

/**
 * @brief Reads a Single Byte from a Register Address of a given Slave Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address
 * @param[in] registerAddress Register Address to read from
 * @returns The read byte
 */
uint8_t I2C_readRegisterByte(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress){
	// Local Variable
	uint32_t temp = 0x00;
	uint8_t data = 0x00;

	// Start Sequence (Write Mode)
	I2C_sendStart(I2Cx);
	// Wait for Start condition (EV5)
	while (!(I2Cx->SR1.REG & I2C_SR1_SB));

	// Send Slave Address with Write Privilege
	I2C_writeAddress(I2Cx, slaveAddress);
	// Wait for ADDR flag (EV6)
	while (!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2Cx->SR1.REG; // Clear ADDR flag by reading SR1
	temp = I2Cx->SR2.REG; // Clear ADDR flag by reading SR2

	// Wait for TXE flag (EV8_1)
	while (!(I2Cx->SR1.REG & I2C_SR1_TXE));
	// Write Register Address
	I2C_writeByte(I2Cx, registerAddress);
	// Wait for TXE and BTF flags (EV8_2)
	while (!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));

	// Repeated START Condition (Switch to Read Mode)
	I2C_sendStart(I2Cx);
	// Wait for Start condition (EV5)
	while (!(I2Cx->SR1.REG & I2C_SR1_SB));

	// Send Slave Address with Read Privilege
	I2C_readAddress(I2Cx, slaveAddress);
	// Wait for ADDR flag (EV6)
	while (!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2Cx->SR1.REG; // Clear ADDR flag by reading SR1
	temp = I2Cx->SR2.REG; // Clear ADDR flag by reading SR2

	// Wait for RXNE flag (EV7)
	while (!(I2Cx->SR1.REG & I2C_SR1_RXNE));
	// Read Data Byte
	data = I2Cx->DR.REG;

	// Generate STOP condition
	I2C_sendStop(I2Cx);
	// Wait until STOP condition is generated
	while (!(I2C_busReady(I2Cx)));

	// Return the read byte
	return data;
}

/**
 * @brief Reads Multiple Consecutive Bytes from a Register Address of a given Slave Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address
 * @param[in] registerAddress Starting Register Address
 * @param[out] data Pointer to the buffer to store the read data
 * @param[in] len Number of bytes to read
 */
void I2C_readRegisterBlock(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, uint8_t len){
	// Local Variable
	uint32_t temp = 0x00;

	// Start Sequence (Write Mode)
	I2C_sendStart(I2Cx);
	// Wait for Start condition (EV5)
	while(!(I2Cx->SR1.REG & I2C_SR1_SB));

	// Send Slave Address with Write Privilege
	I2C_writeAddress(I2Cx, slaveAddress);
	// Wait for ADDR flag (EV6)
	while (!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2Cx->SR1.REG; // Clear ADDR flag by reading SR1
	temp = I2Cx->SR2.REG; // Clear ADDR flag by reading SR2

	// Wait for TXE flag (EV8_1)
	while (!(I2Cx->SR1.REG & I2C_SR1_TXE));
	// Write Starting Register Address
	I2C_writeByte(I2Cx, registerAddress);
	// Wait for TXE and BTF flags (EV8_2)
	while (!(I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF)));

	// Repeated START Condition (Switch to Read Mode)
	I2C_sendStart(I2Cx);
	// Wait for Start condition (EV5)
	while (!(I2Cx->SR1.REG & I2C_SR1_SB));

	// Send Slave Address with Read Privilege
	I2C_readAddress(I2Cx, slaveAddress);
	// Wait for ADDR flag (EV6)
	while (!(I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2Cx->SR1.REG; // Clear ADDR flag by reading SR1
	temp = I2Cx->SR2.REG; // Clear ADDR flag by reading SR2

	// For other bytes, generate ACK
	I2Cx->CR1.REG |= I2C_CR1_ACK;

	// Read Multiple Bytes
	for (uint8_t i = 0; i < len; i++) {
		// For the last byte, generate NACK
		if (i == len - 1)
			I2Cx->CR1.REG &= ~I2C_CR1_ACK;
		// Wait for RXNE flag (EV7)
		while (!(I2Cx->SR1.REG & I2C_SR1_RXNE));
		// Read Data Byte
		data[i] = I2Cx->DR.REG;
	}

	// Generate STOP condition
	I2C_sendStop(I2Cx);
	// Wait until STOP condition is generated
	while (!(I2C_busReady(I2Cx)));
}

/**
 * @brief I2C load default values
 * @param[in] I2C_CONFIGx I2C Configuration Structure
 */
void I2C1_loadDefault(i2c_config_t* I2C_CONFIGx){
	// I2C SCL GPIO Configuration
	I2C_CONFIGx->SCL = &I2C1_SCL;
	// I2C SDA GPIO Configuration
	I2C_CONFIGx->SDA = &I2C1_SDA;
	// I2C Instance
	I2C_CONFIGx->I2Cx = I2C1;
	// I2C Standard Mode (100kHz)
	I2C_CONFIGx->mode = I2Cx_MODE_STD;
	// I2C Fast Mode Duty
	I2C_CONFIGx->duty = I2Cx_DUTY_NORMAL;
	// I2C Frequency
	I2C_CONFIGx->freq_MHz = (APB1Clock/FREQ_1MHz);
	// I2C Rise Time Configuration
	I2C_CONFIGx->TRISE = I2C_calc_TRISE(I2C_CONFIGx->mode);
	// I2C Clock Control Register
	I2C_CONFIGx->CCR = I2C_calc_CCR(I2C_CONFIGx->mode, I2C_CONFIGx->duty, I2C_CONFIGx->freq_MHz);
	// Disable Interrupts
	I2C_CONFIGx->event_IRQ = I2Cx_EVENT_IRQ_DISABLE;
	I2C_CONFIGx->buffer_IRQ = I2Cx_BUFFER_IRQ_DISABLE;
}

/**
 * @brief I2C load default values
 * @param[in] I2C_CONFIGx I2C Configuration Structure
 */
void I2C2_loadDefault(i2c_config_t* I2C_CONFIGx){
	// I2C SCL Configuration
	I2C_CONFIGx->SCL = &I2C2_SCL;
	// I2C SDA Configuration
	I2C_CONFIGx->SDA = &I2C2_SDA;
	// I2C Instance
	I2C_CONFIGx->I2Cx = I2C2;
	// I2C Standard Mode (100kHz)
	I2C_CONFIGx->mode = I2Cx_MODE_STD;
	// I2C Fast Mode Duty
	I2C_CONFIGx->duty = I2Cx_DUTY_NORMAL;
	// I2C Frequency
	I2C_CONFIGx->freq_MHz = (APB1Clock/FREQ_1MHz);
	// I2C Rise Time Configuration
	I2C_CONFIGx->TRISE = I2C_calc_TRISE(I2C_CONFIGx->mode);
	// I2C Clock Control Register
	I2C_CONFIGx->CCR = I2C_calc_CCR(I2C_CONFIGx->mode, I2C_CONFIGx->duty, I2C_CONFIGx->freq_MHz);
	// Disable Interrupts
	I2C_CONFIGx->event_IRQ = I2Cx_EVENT_IRQ_DISABLE;
	I2C_CONFIGx->buffer_IRQ = I2Cx_BUFFER_IRQ_DISABLE;
}

