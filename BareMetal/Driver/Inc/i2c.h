// Header Guards
#ifndef __I2C_H__
#define __I2C_H__

// Dependency
#include "reg_map.h"
#include "rcc.h"	// Clock Configuration
#include "gpio.h"   // For GPIO pin configuration

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
 ** TRISE:
 - For Standard Mode: 100kHz
	I2C_TRISE = (APB1 Clock/1MHz) + 1
	I2C_TRISE = (36MHz/1MHz) + 1 = 36 + 1 = 37
 - For Fast Mode: 400kHz
	I2C_TRISE = (0.3 * (APB1 Clock/1MHz)) + 1
	I2C_TRISE = (0.3 * (36MHz/1MHz)) + 1 = (0.3 * 36) + 1 = (10.8) + 1 = 11.8 ~ 12
 */

// 1/100kHz = 10,000ns
#define I2C_MODE_STD_TIME_NS						((uint16_t) (10 * 1000))
// 1/400kHz = 2500ns
#define I2C_MODE_FAST_TIME_NS						((uint16_t) (2500))

/**
 * @section[start] I2C Event
 */

/**
 * @subsection[start] MASTER TX MODE
 */
// START Transmitted (EV5): `0x00030001`
#define I2Cx_EV_MST_START							((uint32_t)(((I2C_SR2_BUSY | I2C_SR2_MSL) << 16) \
													 | \
													  (I2C_SR1_SB)))

// Master Tx ADDRESS (EV6): `0x00070082` (Ideal = Actual + I2C_SR1_ADDR)										
// Master Tx ADDRESS (EV6): `0x00070080` (Actual)												
#define I2Cx_EV_MST_TX_ADDR							((uint32_t)(((I2C_SR2_TRA | I2C_SR2_BUSY | I2C_SR2_MSL) << 16) \ 
													 | \
													  (I2C_SR1_TXE)))

// Master Rx ADDRESS (EV6): `0x00030042` (Ideal = Actual + I2C_SR1_ADDR)
// #define I2Cx_EV_MST_RX_ADDR							((uint32_t)(((I2C_SR2_TRA | I2C_SR2_BUSY | I2C_SR2_MSL) << 16) \ 
// 													 | \
// 													  (I2C_SR1_RXNE)))
// Master Rx ADDRESS (EV6): `0x00030044` (Actual)
#define I2Cx_EV_MST_RX_ADDR							((uint32_t)(((I2C_SR2_BUSY | I2C_SR2_MSL) << 16) \ 
													 | \
													  (I2C_SR1_RXNE | I2C_SR1_BTF)))

// Byte Sending (EV8): `0x00070080`											
#define I2Cx_EV_MST_BYTE_DR							((uint32_t)(((I2C_SR2_TRA | I2C_SR2_BUSY | I2C_SR2_MSL) << 16) \ 
													 | \
													  (I2C_SR1_TXE )))

// Byte Sent (EV8_1): `0x00070084` 														
#define I2Cx_EV_MST_BYTE_SENT						((uint32_t)(((I2C_SR2_TRA | I2C_SR2_BUSY | I2C_SR2_MSL) << 16) \ 
													 | \
													  (I2C_SR1_TXE | I2C_SR1_BTF)))

/**
 * @subsection[end] MASTER TX MODE
 */

#define I2C_readAddress(I2Cx, slaveAddress)			(I2C_sendAddress((I2Cx), (((slaveAddress) << 1) | I2Cx_READ)))
#define I2C_writeAddress(I2Cx, slaveAddress)		(I2C_sendAddress((I2Cx), (((slaveAddress) << 1) | I2Cx_WRITE)))

/**	
 * @section[end] I2C Event
 */ 


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
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__attribute__((always_inline)) inline void I2C_clk_enable(I2C_REG_STRUCT* I2Cx){
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
__attribute__((always_inline)) inline void I2C_clk_disable(I2C_REG_STRUCT* I2Cx){
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
__attribute__((always_inline)) inline void I2C_enable(I2C_REG_STRUCT* I2Cx){
	// Enable the I2C Module
	I2Cx->CR1.REG |= I2C_CR1_PE;
}

/**
 * @brief Disables the I2C
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__attribute__((always_inline)) inline void I2C_disable(I2C_REG_STRUCT* I2Cx){
	// Enable the I2C Module
	I2Cx->CR1.REG &= ~I2C_CR1_PE;
}

/**
 * @brief I2C Bus Ready
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @returns - 0: I2C Bus is not ready
 * @returns - 1: I2C Bus is ready
 */
__attribute__((always_inline)) inline uint8_t I2C_busReady(I2C_REG_STRUCT* I2Cx){
	// Bus Busy
	if((I2Cx->SR2.REG & I2C_SR2_BUSY))
		return (uint8_t)0x00;
	// Bus Free
	else
		return (uint8_t)0x01;
}

/**
 * @brief I2C Send START Sequence
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__attribute__((always_inline)) inline void I2C_sendStart(I2C_REG_STRUCT* I2Cx){
	// Send START condition
	I2Cx->CR1.REG |= I2C_CR1_START;
}

/**
 * @brief I2C Byte Send
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] data Data to be TX
 */
__attribute__((always_inline)) inline void I2C_writeDR(I2C_REG_STRUCT* I2Cx, uint8_t data){
	// Send data
	I2Cx->DR.REG = data;
}

/**
 * @brief I2C Send STOP Sequence
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__attribute__((always_inline)) inline void I2C_sendStop(I2C_REG_STRUCT* I2Cx){
	// Send STOP condition
	I2Cx->CR1.REG |= I2C_CR1_STOP;
}

/**
 * @brief Configures I2C as per the Configuration Structure
 * @param[in] I2C_CONFIGx I2C Configuration Structure
 */
void I2C_config(i2c_config_t* I2C_CONFIGx);

/**
 * @brief I2C Event Check
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @returns Status of Event
 */
uint32_t I2C_checkEvent(I2C_REG_STRUCT* I2Cx);

/**
 * @brief Send I2C Slave Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address
 * @returns 0: Failure
 * @returns 1: Success
 */
uint8_t I2C_sendAddress(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress);

/**
 * @brief Read from I2C Slave
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address
 * @returns 0: Failure
 * @returns 1: Success
 */
// uint8_t I2C_readAddress(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress);

/**
 * @brief Write to I2C Slave
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address
 * @returns 0: Failure
 * @returns 1: Success
 */
// uint8_t I2C_writeAddress(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress);

/**
 * @brief Calculates the value of Clock Control Register (CCR) for I2C Module
 * @param[in] i2cMode I2C Mode: `I2Cx_MODE_FAST`, `I2Cx_MODE_STD`
 * @returns Calculated CCR value
 */
uint16_t I2C_calc_CCR(uint8_t i2cMode, uint8_t i2cDuty, uint8_t i2cClockFrequency);

/**
 * @brief Calculates the value of TRISE (TRISE) for I2C Module
 * @param[in] i2cMode I2C Mode: `I2Cx_MODE_FAST`, `I2Cx_MODE_STD`
 * @returns Calculated TRISE value
 */
uint8_t I2C_calc_TRISE(uint8_t i2cMode);

#endif /* __I2C_H__ */