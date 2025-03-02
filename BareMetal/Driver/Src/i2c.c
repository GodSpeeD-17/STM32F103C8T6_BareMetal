// Dependency
#include "i2c.h"

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
	config_GPIO(I2C_CONFIGx->SCL);
	config_GPIO(I2C_CONFIGx->SDA);
	// Software Reset
	I2C_CONFIGx->I2Cx->CR1.REG |= I2C_CR1_SWRST;
	I2C_CONFIGx->I2Cx->CR1.REG &= ~I2C_CR1_SWRST;
	// I2C Module Frequency
	I2C_CONFIGx->I2Cx->CR2.REG |= (I2C_CONFIGx->freq_MHz & 0x3F) << I2C_CR2_FREQ_Pos;
	// I2C Mode + I2C Duty + I2C Clock Control Register
	I2C_CONFIGx->I2Cx->CCR.REG = (((I2C_CONFIGx->mode & 0x01) << I2C_CCR_FS_Pos) |
									((I2C_CONFIGx->duty & 0x01) << I2C_CCR_DUTY_Pos) | 
									(I2C_CONFIGx->CCR & 0x0FFF) << I2C_CCR_CCR_Pos);
	// TRISE Configuration
	I2C_CONFIGx->I2Cx->TRISE.REG = (I2C_CONFIGx->TRISE & 0x3F) << I2C_TRISE_TRISE_Pos;
}

/**
 * @brief I2C Event Check
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @returns Status of Event
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
	event &= 0x000FFFFF;
	// Return the Event Sequence
	return event;
}

/**
 * @brief Send I2C Slave Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address
 * @returns 0: Failure
 * @returns 1: Success
 */
uint8_t I2C_sendAddress(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress){
	// Format Slave Address
	I2Cx->DR.REG = (uint8_t) (slaveAddress & 0xFF);
	// Check Event
	if(I2C_checkEvent(I2Cx) == ((slaveAddress & I2Cx_READ)? (I2Cx_EV_MST_RX_ADDR) : (I2Cx_EV_MST_TX_ADDR)))
		return (uint8_t) 0x01;
	else
		return (uint8_t) 0x00;
}

/**
 * @brief Read from I2C Slave
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address
 * @returns 0: Failure
 * @returns 1: Success
 */
/*
uint8_t I2C_readAddress(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress){
	// Format the address data to be sent
	I2Cx->DR.REG = (uint8_t) (((slaveAddress << 1) | I2Cx_READ) & 0xFF);
	// Check Event
	if(I2C_checkEvent(I2Cx) == I2Cx_EV_MST_RX_ADDR)
		return (uint8_t) 0x01;
	else
		return (uint8_t) 0x00;
}
*/

/**
 * @brief Write to I2C Slave
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address
 * @returns 0: Failure
 * @returns 1: Success
 */
/*
uint8_t I2C_writeAddress(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress){
	// Format the address data to be sent
	I2Cx->DR.REG = (uint8_t) (((slaveAddress << 1) | I2Cx_WRITE) & 0xFF);
	// Check Event
	if(I2C_checkEvent(I2Cx) == I2Cx_EV_MST_TX_ADDR)
		return (uint8_t) 0x01;
	else
		return (uint8_t) 0x00;
}
*/

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

