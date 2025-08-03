// Header Guards
#ifndef __I2C_CONFIG_H__
#define __I2C_CONFIG_H__

// Address Mapping
#include "reg_map.h"
// For GPIO pin configuration
#include "gpio.h"
// Clock Configuration
#include "rcc.h"

/**
 ** I2Cx->CR2.BIT.FREQ: I2C Clock Frequency 
	Generally same as APBx Clock Frequency
	APB1 Clock = 36MHz -> I2C Clock = 36MHz i.e (0x24)
 ** I2Cx->CCR.BIT.CCR: In I2C protocol, the transistors of master devices pull down the lines and the pull-up resistors pull
	the lines up. Since the internal resistance of transistors are much less than the pull-up resistors, the fall
	time is much less than the rise time. Using the I2C_TRISE, we mention the amount of time that the rise
	time might take
 * I2C Duty Cycle and Baud Rate Configuration
 * |--------------|------|-------------------|-------------|-------------|-------------------|--------------------------|
 * | 	F/S 	  | DUTY |Duty Cycle for SCL |    Tlow     |    Thigh    | TI2C (Tlow+Thigh) |  **Baud Rate (1/TI2C)**	|
 * |--------------|------|-------------------|-------------|-------------|-------------------|--------------------------|
 * | 0 (Standard) |  X   |       50%    	 | CCR × TPCLK | CCR × TPCLK | 2×CCR×TPCLK       |  (APB1 Clock)/(2×CCR)    |
 * | 1 (Fast)     |  0   |		33.3%  		 | CCR × TPCLK | 2×CCR×TPCLK | 3×CCR×TPCLK       |  (APB1 Clock)/(3×CCR)    |
 * | 1 (Fast)     |  1   |		 36%    	 | 9×CCR×TPCLK | 16×CCR×TPCLK| 25×CCR×TPCLK      |  (APB1 Clock)/(25×CCR)   |
 * ----------------------------------------------------------------------------------------------------------------------
 * 
 * Thus;
 * For Standard Mode:
 * 	DUTY = x:
 * 		CCR = (APB1 Clock)/(100kHz * 2) = (APB1 Clock)/(200kHz);
 * For Fast Mode:
 * 	DUTY = 0:
 * 		CCR = (APB1 Clock)/(400kHz * 3) = (APB1 Clock)/(1200kHz);
 * 	DUTY = 1:
 * 		CCR = (APB1 Clock)/(400kHz * 25) = (APB1 Clock)/(10MHz);
 * 
 ** TRISE:
 - For Standard Mode: 100kHz
	I2C_TRISE = (APB1 Clock/1MHz) + 1
	I2C_TRISE = (36MHz/1MHz) + 1 = 36 + 1 = 37
 - For Fast Mode: 400kHz
	I2C_TRISE = (0.3 * (APB1 Clock/1MHz)) + 1
	I2C_TRISE = (0.3 * (36MHz/1MHz)) + 1 = (0.3 * 36) + 1 = (10.8) + 1 = 11.8 ~ 12
*/

// TODO: TRISE for Fast Mode
// I2C Configuration Structure
typedef struct {
	// I2C Instance: `I2C1`, `I2C2`
	I2C_REG_STRUCT* I2Cx;
	// Serial Clock GPIO Configuration
	gpio_config_t SCL;
	// Serial Data GPIO Configuration
	gpio_config_t SDA;
	// SCL Clock Frequency (in MHz)
	// |--- `I2Cx_SCL_FREQ_4MHz`
	// |--- `I2Cx_SCL_FREQ_8MHz`
	// |--- `I2Cx_SCL_FREQ_16MHz`
	// |--- `I2Cx_SCL_FREQ_32MHz`
	// |--- `APB1Clock` (Preferred)
	// - Determines the total time duration for I2C Module
	// - T = (1/`clk_freq_MHz`), T = Time Period of I2C Module
	// - Generally kept same as that of APBx Clock Frequency
	uint8_t freq_MHz;
	// I2C Speed Mode: 
	// - `I2Cx_MODE_STD` 
	// - `I2Cx_MODE_FAST`
	uint16_t mode: 1;
	// Fast Mode (400kHz) duty cycle
	// - `I2Cx_DUTY_NORMAL`: Thigh = CCR * `freq_MHz`
	// - `I2Cx_DUTY_FAST`: Thigh = 9 * CCR * `freq_MHz`
	uint16_t duty: 1;
	// Clock Control Register (CCR) value
		// - `I2Cx_MODE_STD`:
			// |--- Thigh = Clock control register (CCR) * `freq_MHz`;
			// |--- Tlow = Clock control register (CCR) * `freq_MHz`;
			// |--- T = Thigh + Tlow; T = Total Time Period (Refer `freq_MHz`)
		// - `I2Cx_MODE_FAST`:
			// |--- DUTY = 0 (normal duty cycle):
				// |---|--- Thigh = CCR * `freq_MHz`
				// |---|--- Tlow = 2 * CCR * `freq_MHz`
			// |--- DUTY = 1 (fast duty cycle):
				// |---|--- Thigh = 9 * CCR * `freq_MHz`
				// |---|--- Tlow = 16 * CCR * `freq_MHz`
	uint16_t CCR: 12;
	// Maximum rise time in Fast/Standard Mode (Master mode)
	// - Provide the maximum duration of the SCL feedback loop in master mode
	// - `I2Cx_MODE_STD`:
	// |- TRISE = ((APB1Clock/1MHz) + 1) = ((36MHz/1MHz) + 1) = (36 + 1) = 37 
	// - `I2Cx_MODE_FAST`:
	// |- TRISE = ((0.3 * (APB1Clock/1MHz)) + 1) = ((0.3 * (36MHz/1MHz)) + 1) = ((0.3 * 36)) + 1) = (10.8 + 1) = 11.8 ~ 11 
	uint8_t TRISE;
} i2c_config_t;

/**
 * @brief Enables the Clock for I2C Module
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__STATIC_INLINE__ void I2C_Clk_Enable(I2C_REG_STRUCT* I2Cx){
	// Enable AFIO
	RCC->APB2ENR.REG |= RCC_APB2ENR_AFIOEN;
	// I2C1
	if(I2Cx == I2C1){
		// Enable I2C1 Clock
		RCC->APB1ENR.REG |= RCC_APB1ENR_I2C1EN;
	}
	// I2C2
	if(I2Cx == I2C2){
		// Enable I2C1 Clock
		RCC->APB1ENR.REG |= RCC_APB1ENR_I2C2EN;
	}
}

/**
 * @brief Disables the Clock for I2C Module
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__STATIC_INLINE__ void I2C_Clk_Disable(I2C_REG_STRUCT* I2Cx){
	// Disable AFIO
	RCC->APB2ENR.REG &= ~RCC_APB2ENR_AFIOEN;
	// I2C1
	if(I2Cx == I2C1){
		// Disable I2C1 Clock
		RCC->APB1ENR.REG &= ~RCC_APB1ENR_I2C1EN;
	}
	// I2C2
	if(I2Cx == I2C2){
		// Disable I2C1 Clock
		RCC->APB1ENR.REG &= ~RCC_APB1ENR_I2C2EN;
	}
}

/**
 * @brief Enables the I2C
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__STATIC_INLINE__ void I2C_Enable(I2C_REG_STRUCT* I2Cx){
	// Enable the I2C Module
	I2Cx->CR1.REG |= I2C_CR1_PE;
}

/**
 * @brief Disables the I2C
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__STATIC_INLINE__ void I2C_Disable(I2C_REG_STRUCT* I2Cx){
	// Enable the I2C Module
	I2Cx->CR1.REG &= ~I2C_CR1_PE;
}

/**
 * @brief Calculates the value of TRISE (TRISE) for I2C Module
 * @param[in] i2cMode I2C Mode: `I2Cx_MODE_FAST`, `I2Cx_MODE_STD`
 * @returns Calculated TRISE value
 */
uint8_t I2C_Calc_tRISE(uint8_t i2cMode);

/**
 * @brief Calculates the value of Clock Control Register (CCR) for I2C Module
 * @param[in] i2cMode I2C Mode: `I2Cx_MODE_FAST`, `I2Cx_MODE_STD`
 * @param[in] i2cDuty I2C Duty: `I2Cx_DUTY_NORMAL`, `I2Cx_DUTY_FAST`
 * @param[in] i2cClockFrequencyMHz I2C Module Clock Frequency (Recommended APB1Clock)
 * @returns Calculated CCR value
 * @note Template Formula:
 * @note CCR = (I2C_CONFIGx->freq_MHz * `FREQ_1MHz`) / (<T_ns/Thigh_ns> * I2Cx_SPEED_y);
 */
uint16_t I2C_Calc_CCR(uint8_t i2cMode, uint8_t i2cDuty, uint8_t i2cClockFrequencyMHz);

/**
 * @brief Configures I2C as per the Configuration Structure
 * @param I2C_CONFIGx I2C Configuration Structure
 */
void I2C_Config(i2c_config_t* I2C_CONFIGx);

/**
 * @brief I2C load default values
 * @param I2C_CONFIGx I2C Configuration Structure
 */
void I2C1_Load_Default(i2c_config_t* I2C_CONFIGx);

/**
 * @brief I2C load default values
 * @param I2C_CONFIGx I2C Configuration Structure
 */
void I2C2_Load_Default(i2c_config_t* I2C_CONFIGx);

#endif /* __I2C_CONFIG_H__ */