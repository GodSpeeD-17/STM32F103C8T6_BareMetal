// Dependency
#include "i2c_config.h"

/**
 * @brief Calculates the value of TRISE (TRISE) for I2C Module
 * @param i2cMode I2C Mode: `I2Cx_MODE_FAST`, `I2Cx_MODE_STD`
 * @returns Calculated TRISE value
 */
uint8_t I2C_Calc_tRISE(uint8_t i2cMode){
	// Local Value
	uint8_t calc_TRISE = 0;
	// Get APB1 Clock (in MHz)
	calc_TRISE = (RCC_Get_APB1Clock()/FREQ_1MHz);
	// Fast I2C Mode: 400kHz
	if(i2cMode == I2Cx_MODE_FAST){
		calc_TRISE *= 3;
		calc_TRISE /= 10;
	}
	// Return the value
	return (calc_TRISE + 1);
}

/**
 * @brief Calculates the value of Clock Control Register (CCR) for I2C Module
 * @param[in] i2cMode I2C Mode: `I2Cx_MODE_FAST`, `I2Cx_MODE_STD`
 * @param[in] i2cDuty I2C Duty: `I2Cx_DUTY_NORMAL`, `I2Cx_DUTY_FAST`
 * @param[in] i2cClockFrequencyMHz I2C Module Clock Frequency (Recommended `APB1Clock`)
 * @returns Calculated CCR value
 * @note Template Formula:
 * @note CCR = (I2C_CONFIGx->freq_MHz * `FREQ_1MHz`) / (<T_ns/Thigh_ns> * I2Cx_SPEED_y);
 */
uint16_t I2C_Calc_CCR(uint8_t i2cMode, uint8_t i2cDuty, uint8_t i2cClockFrequencyMHz){
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

	// Return the value
	return (uint16_t) (calculated_CCR & 0xFFFF);
}

/**
 * @brief Configures I2C as per the Configuration Structure
 * @param I2C_CONFIGx I2C Configuration Structure
 */
void I2C_Config(i2c_config_t* I2C_CONFIGx){
	// Enable Clock
	I2C_Clk_Enable(I2C_CONFIGx->I2Cx);
	// Configure GPIOs
	GPIO_Config(&I2C_CONFIGx->SCL);
	GPIO_Config(&I2C_CONFIGx->SDA);
	// Software Reset
	I2C_CONFIGx->I2Cx->CR1.REG |= I2C_CR1_SWRST;
	I2C_CONFIGx->I2Cx->CR1.REG &= ~I2C_CR1_SWRST;
	// I2C Buffer IRQ + I2C Event IRQ + I2C Module Frequency
	I2C_CONFIGx->I2Cx->CR2.REG |= (uint32_t)((I2C_CONFIGx->freq_MHz & 0x3F) << I2C_CR2_FREQ_Pos);
	// I2C Mode + I2C Duty + I2C Clock Control Register
	I2C_CONFIGx->I2Cx->CCR.REG = (((I2C_CONFIGx->mode & 0x01) << I2C_CCR_FS_Pos) |
									((I2C_CONFIGx->duty & 0x01) << I2C_CCR_DUTY_Pos) | 
									(I2C_CONFIGx->CCR & 0x0FFF) << I2C_CCR_CCR_Pos);
	// TRISE Configuration
	I2C_CONFIGx->I2Cx->TRISE.REG = (I2C_CONFIGx->TRISE & 0x3F) << I2C_TRISE_TRISE_Pos;
}

/**
 * @brief I2C load default values
 * @param I2C_CONFIGx I2C Configuration Structure
 */
void I2C1_Load_Default(i2c_config_t* I2C_CONFIGx){
	// I2C1 SCL GPIO Configuration
	I2C_CONFIGx->SCL.GPIO = I2C1_SCL_GPIO;
	I2C_CONFIGx->SCL.PIN = I2C1_SCL_PIN;
	I2C_CONFIGx->SCL.MODE = GPIOx_MODE_OUT_50MHz,
	I2C_CONFIGx->SCL.CNF = GPIOx_CNF_OUT_AF_OD;
	// I2C1 SDA GPIO Configuration
	I2C_CONFIGx->SDA.GPIO = I2C1_SDA_GPIO;
	I2C_CONFIGx->SDA.PIN = I2C1_SDA_PIN;
	I2C_CONFIGx->SDA.MODE = GPIOx_MODE_OUT_50MHz,
	I2C_CONFIGx->SDA.CNF = GPIOx_CNF_OUT_AF_OD;
	// I2C1 Instance
	I2C_CONFIGx->I2Cx = I2C1;
	// I2C Standard Mode (100kHz)
	I2C_CONFIGx->mode = I2Cx_MODE_STD;
	// I2C Fast Mode Duty
	I2C_CONFIGx->duty = I2Cx_DUTY_NORMAL;
	// I2C Frequency
	I2C_CONFIGx->freq_MHz = (RCC_Get_APB1Clock()/FREQ_1MHz);
	// I2C Rise Time Configuration
	I2C_CONFIGx->TRISE = I2C_Calc_tRISE(I2C_CONFIGx->mode);
	// I2C Clock Control Register
	I2C_CONFIGx->CCR = I2C_Calc_CCR(I2C_CONFIGx->mode, I2C_CONFIGx->duty, I2C_CONFIGx->freq_MHz);
}

/**
 * @brief I2C load default values
 * @param I2C_CONFIGx I2C Configuration Structure
 */
void I2C2_Load_Default(i2c_config_t* I2C_CONFIGx){
	// I2C2 SCL GPIO Configuration
	I2C_CONFIGx->SCL.GPIO = I2C2_SCL_GPIO;
	I2C_CONFIGx->SCL.PIN = I2C2_SCL_PIN;
	I2C_CONFIGx->SCL.MODE = GPIOx_MODE_OUT_50MHz,
	I2C_CONFIGx->SCL.CNF = GPIOx_CNF_OUT_AF_OD;
	// I2C2 SDA GPIO Configuration
	I2C_CONFIGx->SDA.GPIO = I2C2_SDA_GPIO;
	I2C_CONFIGx->SDA.PIN = I2C2_SDA_PIN;
	I2C_CONFIGx->SDA.MODE = GPIOx_MODE_OUT_50MHz,
	I2C_CONFIGx->SDA.CNF = GPIOx_CNF_OUT_AF_OD;
	// I2C2 Instance
	I2C_CONFIGx->I2Cx = I2C2;
	// I2C Standard Mode (100kHz)
	I2C_CONFIGx->mode = I2Cx_MODE_STD;
	// I2C Fast Mode Duty
	I2C_CONFIGx->duty = I2Cx_DUTY_NORMAL;
	// I2C Frequency
	I2C_CONFIGx->freq_MHz = (RCC_Get_APB1Clock()/FREQ_1MHz);
	// I2C Rise Time Configuration
	I2C_CONFIGx->TRISE = I2C_Calc_tRISE(I2C_CONFIGx->mode);
	// I2C Clock Control Register
	I2C_CONFIGx->CCR = I2C_Calc_CCR(I2C_CONFIGx->mode, I2C_CONFIGx->duty, I2C_CONFIGx->freq_MHz);
}
