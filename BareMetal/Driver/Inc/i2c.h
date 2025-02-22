// Header Guards
#ifndef __I2C_H__
#define __I2C_H__

// Dependency
#include "reg_map.h"
#include "rcc.h"	// Clock Configuration
#include "gpio.h"   // For GPIO pin configuration

/**
 * I2Cx->CR2.BIT.FREQ: I2C Clock Frequency 
	Generally same as APBx Clock Frequency
	APB1 Clock = 36MHz -> I2C Clock = 36MHz i.e (0x24)
 * I2Cx->CCR.BIT.CCR: In I2C protocol, the transistors of master devices pull down the lines and the pull-up resistors pull
	the lines up. Since the internal resistance of transistors are much less than the pull-up resistors, the fall
	time is much less than the rise time. Using the I2C_TRISE, we mention the amount of time that the rise
	time might take
 * I2C Duty Cycle and Baud Rate Configuration
 * |--------------|------|-------------------|-------------|-------------|-------------------|--------------------------|
 * | 	F/S 	  | DUTY |Duty Cycle for SCL |    Tlow     |    Thigh    | TI2C (Tlow+Thigh) |  **Baud Rate (1/TI2C)**	|
 * |--------------|------|-------------------|-------------|-------------|-------------------|--------------------------|
 * | 0 (Standard) |  X   |       50%    	 | CCR × TPCLK | CCR × TPCLK | 2×CCR×TPCLK       |  (APB1 Clock)/(2×CCR)    |
 * | 1 (Fast)     |  0   |		33.3%  		 | CCR × TPCLK | 2×CCR×TPCLK | 3×CCR×TPCLK       |  (APB1 Clock)/(3×CCR)    |
 * | 1 (Fast)X    |  1   |		 36%    	 | 9×CCR×TPCLK | 16×CCR×TPCLK| 25×CCR×TPCLK      |  (APB1 Clock)/(25×CCR)   |
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
 * TRISE:
 - For Standard Mode: 100kHz
	I2C_TRISE = (APB1 Clock/1MHz) + 1
	I2C_TRISE = (36MHz/1MHz) + 1 = 36 + 1 = 37
 - For Fast Mode: 400kHz
	I2C_TRISE = (0.3 * (APB1 Clock/1MHz)) + 1
	I2C_TRISE = (0.3 * (36MHz/1MHz)) + 1 = (0.3 * 36) + 1 = (10.8) + 1 = 11.8 ~ 12
 */

// 100kHz
#define I2C_MODE_STD_FREQ					((uint32_t) (1 * FREQ_100kHz))
// 400kHz
#define I2C_MODE_FAST_FREQ					((uint32_t) (4 * FREQ_100kHz))
// 1/100kHz = 10,000ns
#define I2C_MODE_STD_TIME_NS				((uint16_t) (10 * 1000))
// 1/400kHz = 2500ns
#define I2C_MODE_FAST_TIME_NS				((uint16_t) (2500))

// I2C Configuration Structure
typedef struct {
	// TODO: TRISE for Fast Mode
	// Serial Clock GPIO Configuration
	gpio_config_t* SCL;
	// Serial Data GPIO Configuration
	gpio_config_t* SDA;
	// I2C Instance: `I2C1`, `I2C2`
	I2C_REG_STRUCT* I2Cx;
	// SCL Clock Frequency (in MHz)
	// |--- `I2Cx_SCL_FREQ_4MHz`
	// |--- `I2Cx_SCL_FREQ_8MHz` (Preferred)
	// |--- `I2Cx_SCL_FREQ_16MHz`
	// |--- `I2Cx_SCL_FREQ_32MHz`
	// - Determines the total time duration for SCL
	// - T = (1/`clk_freq_MHz`), T = Time Period of SCL
	uint8_t SCL_freq_MHz;
	// I2C Speed Mode: 
	// - `I2Cx_MODE_STD` 
	// - `I2Cx_MODE_FAST`
	uint16_t mode: 1;
	// Fast Mode (400kHz) duty cycle
	// - `I2Cx_DUTY_NORMAL`: Thigh = CCR * `SCL_freq_MHz`
	// - `I2Cx_DUTY_FAST`: Thigh = 9 * CCR * `SCL_freq_MHz`
	uint16_t duty: 1;
	// Clock Control Register (CCR) value
		// - `I2Cx_MODE_STD`:
			// |--- Thigh = Clock control register (CCR) * `SCL_freq_MHz`;
			// |--- Tlow = Clock control register (CCR) * `SCL_freq_MHz`;
			// |--- T = Thigh + Tlow; T = Total Time Period (Refer `SCL_freq_MHz`)
		// - `I2Cx_MODE_FAST`:
			// |--- DUTY = 0 (normal duty cycle):
				// |---|--- Thigh = CCR * `SCL_freq_MHz`
				// |---|--- Tlow = 2 * CCR * `SCL_freq_MHz`
			// |--- DUTY = 1 (fast duty cycle):
				// |---|--- Thigh = 9 * CCR * `SCL_freq_MHz`
				// |---|--- Tlow = 16 * CCR * `SCL_freq_MHz`
	uint16_t CCR: 12;
	// Maximum rise time in Fast/Standard Mode (Master mode)
	// - Provide the maximum duration of the SCL feedback loop in master mode
	// - if(mode == `I2Cx_MODE_STD` && SCL_freq_MHz == `I2Cx_SCL_FREQ_8MHz`): 
	// |---|--- maximum allowed SCL rise time is 1000ns (`I2Cx_MODE_STD`)
	// |---|--- TRISE = ((Max allowed SCL rise time (ns)/Tfreq_ns) + 1) = ((1000/125) + 1) = (8 + 1) = 9 
	uint8_t TRISE;
} i2c_config_t;

// I2C Slave Configuration Structure
typedef struct {
	// Read-Write
	// - `I2Cx_WRITE`: Write to the Slave
	// - `I2Cx_READ`: Read from the Slave
	uint8_t r_w: 1;
	// 7-bit Slave Address
	uint8_t address: 7;
	// Pointer to the Buffer where data is read from/written to
	uint8_t* buffer;
	// Buffer length
	uint8_t buff_len;
} i2c_slave_config_t;

// I2C Communication Data Structure
typedef struct {
	// I2C Instance: `I2C1`, `I2C2`
	I2C_REG_STRUCT* I2Cx;
	// Slave configuration Structure
	i2c_slave_config_t* slave;
} i2c_data_t;

/**
 * @brief Enables the Clock for I2C Module
 * @param[in] I2C_CONFIGx I2C Configuration Structure
 */
__attribute__((always_inline)) inline void enable_I2C_clk(i2c_config_t* I2C_CONFIGx){
	// Enable AFIO
	RCC->APB2ENR.REG |= RCC_APB2ENR_AFIOEN;
	// I2C1
	if(I2C_CONFIGx->I2Cx == I2C1){
		// Enable I2C1 Clock
		RCC->APB1ENR.REG |= RCC_APB1ENR_I2C1EN;
	}
	// I2C2
	if(I2C_CONFIGx->I2Cx == I2C2){
		// Enable I2C1 Clock
		RCC->APB1ENR.REG |= RCC_APB1ENR_I2C2EN;
	}
}

/**
 * @brief Disables the Clock for I2C Module
 * @param[in] I2C_CONFIGx I2C Configuration Structure
 */
__attribute__((always_inline)) inline void disable_I2C_clk(i2c_config_t* I2C_CONFIGx){
	// Disable AFIO
	RCC->APB2ENR.REG &= ~RCC_APB2ENR_AFIOEN;
	// I2C1
	if(I2C_CONFIGx->I2Cx == I2C1){
		// Disable I2C1 Clock
		RCC->APB1ENR.REG &= ~RCC_APB1ENR_I2C1EN;
	}
	// I2C2
	if(I2C_CONFIGx->I2Cx == I2C2){
		// Disable I2C1 Clock
		RCC->APB1ENR.REG &= ~RCC_APB1ENR_I2C2EN;
	}
}

/**
 * @brief Calculates the value of Clock Control Register (CCR) for I2C Module
 * @param[in] I2C_CONFIGx I2C Configuration Structure
 * @returns CCR value
 */
__attribute__((always_inline)) uint16_t calc_CRR(i2c_config_t* I2C_CONFIGx){
	// TODO: Try using lookup Table to reduce calculation burden
	// Local Value
	uint16_t calculated_CCR = 0;
	// I2C Module Frequency (Tfreq)
	// Tfreq_us = (1/`SCL_freq_MHz`);
	// Tfreq_ns = 1000 * Tfreq_us -> Tfreq_ns = (1000/`SCL_freq_MHz`); .... [1]
	// I2C Mode
	switch(I2C_CONFIGx->mode){
		// I2C Standard Mode: 100kHz
		case I2Cx_MODE_STD:
			// Calculation reference is ns (Simplifies Calculation as it can be completed using `uint16_t`)
			// Thigh = Tlow -> T = Thigh + Tlow -> T = 2 * Thigh -> Thigh = (T/2)
			// Thigh = CCR * Tfreq -> Thigh_ns = CCR * Tfreq_ns -> CCR = (Thigh_ns/Tfreq_ns) -> CCR = (Tns/(2*Tfreq_ns));
			// CCR = (Tns * `SCL_freq_MHz` / (2 * 1000)); ..... {Refer 1}
			calculated_CCR = ((I2C_MODE_STD_TIME_NS * I2C_CONFIGx->SCL_freq_MHz)/(2 * 1000));
		break;
		// I2C Fast Mode: 400kHz
		case I2Cx_MODE_FAST:
			// Tlow/Thigh = 16/9 -> Tlow = (16/9*Thigh) -> T = Tlow + Thigh -> T = Thigh * (1 + 16/9) -> T = Thigh * 25/9 -> Thigh = 9/25 * T -> Thigh_ns = ((9 * Tns)/25));
			// Thigh = 9 * CCR * Tfreq -> Thigh_ns = (9 * CCR * Tfreq_ns) -> (9 * Tns)/25 = 9 * CCR * Tfreq_ns -> Tns / 25 = CCR * Tfreq_ns -> CCR = Tns / (25 * Tfreq_ns);
			// CCR = (Tns * `SCL_freq_MHz`)/(25 * 1000);
			if(I2C_CONFIGx->I2Cx->CCR.REG & I2C_CCR_DUTY){
				calculated_CCR = ((I2C_MODE_FAST_TIME_NS * I2C_CONFIGx->SCL_freq_MHz)/(25 * 1000));
			}
			// Tlow/Thigh = 2 -> Tlow = 2 * Thigh -> T = Tlow + Thigh -> T = 3 * Thigh -> Thigh = T/3 -> Thigh_ns = Tns/3;
			// Thigh = CCR * Tfreq -> Thigh_ns = CCR * Tfreq_ns -> (Tns/3) = CCR * Tfreq_ns -> CCR = (Tns/(3*Tfreq_ns));
			// CCR = ((Tns * `SCL_freq_MHz`)/(3 * 1000)); .... {Refer 1}
			else{
				calculated_CCR = ((I2C_MODE_FAST_TIME_NS * I2C_CONFIGx->SCL_freq_MHz)/(3 * 1000));
			}
		break;
	}
	// Template Formula:
		// CCR = ((I2C_MODE_..._TIME_NS) * (I2C_CONFIGx->SCL_freq_MHz)) / (<T_ns/Thigh_ns> * 1000);
	// Return the value
	return calculated_CCR;
}

/**
 * @brief Enables the I2C
 * @param[in] I2C_CONFIGx I2C Configuration Structure
 */
__attribute__((always_inline)) inline void enable_I2C(i2c_config_t* I2C_CONFIGx){
	// Enable the I2C Module
	I2C_CONFIGx->I2Cx->CR1.REG |= I2C_CR1_PE;
}

/**
 * @brief Disables the I2C
 * @param[in] I2C_CONFIGx I2C Configuration Structure
 */
__attribute__((always_inline)) inline void disable_I2C(i2c_config_t* I2C_CONFIGx){
	// Enable the I2C Module
	I2C_CONFIGx->I2Cx->CR1.REG &= ~I2C_CR1_PE;
}

/**
 * @brief Configures I2C as per the Configuration Structure
 * @param[in] I2C_CONFIGx I2C Configuration Structure
 */
void config_I2C(i2c_config_t* I2C_CONFIGx);

/**
 * @brief START condition
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @note Operation Mode: Master
 */
void start_I2C(I2C_REG_STRUCT* I2Cx);

/***
 * @brief Sends I2C Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slave_address I2C Slave Address
 * @param[in] r_w `I2Cx_READ`,`I2Cx_WRITE`
 */
void send_I2C_addr(I2C_REG_STRUCT* I2Cx, uint8_t slave_address, uint8_t r_w);

/**
 * @brief STOP Condition
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @note Operation Mode: Master
 */
void stop_I2C(I2C_REG_STRUCT* I2Cx);

/**
 * @brief I2C Communication Sequence
 * @param[in] I2C_DATAx I2C Data Structure
 */
void I2C_master_TX(i2c_data_t* I2C_DATAx);

/**
 * @brief I2C Bus Ready
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__attribute__((always_inline)) inline void I2C_busReady(I2C_REG_STRUCT* I2Cx){
	// Check Bus is free
	while((I2Cx->SR2.REG & I2C_SR2_BUSY));
}

/**
 * @brief I2C Send START Sequence
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__attribute__((always_inline)) inline void I2C_sendStart(I2C_REG_STRUCT* I2Cx){
	// Send START condition
	I2Cx->CR1.REG |= I2C_CR1_START;
	// Check START bit successful
	while(!(I2Cx->SR1.REG & I2C_SR1_SB));
	// Read status
	uint8_t status = I2Cx->SR2.REG;
}

/**
 * @brief I2C Send STOP Sequence
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__attribute__((always_inline)) inline void I2C_sendStop(I2C_REG_STRUCT* I2Cx){
	// Send START condition
	I2Cx->CR1.REG |= I2C_CR1_STOP;
	// Check STOP bit successful
	while(!(I2Cx->SR2.REG & I2C_SR2_MSL));
}

/**
 * @brief I2C Slave Address Send
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address to be TX
 * @returns 0: Failure; 1: Success
 */
uint8_t I2C_sendAddress(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress);

/**
 * @brief I2C Slave Address Send
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] data Data to be TX
 */
void I2C_sendData(I2C_REG_STRUCT* I2Cx, uint8_t data);



#endif /* __I2C_H__ */ 