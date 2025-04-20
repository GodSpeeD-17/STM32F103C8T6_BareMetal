// Header Guards
#ifndef __I2C_H__
#define __I2C_H__

// Dependency
#include "reg_map.h"
#include "rcc.h"	// Clock Configuration
#include "gpio.h"   // For GPIO pin configuration
#include "nvic.h"	// For Interrupt Configuration

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

 //  MACROS
#define I2C_readAddress(I2Cx, slaveAddress)			(I2C_writeByte((I2Cx), (((slaveAddress) << 1) | I2Cx_READ)))
#define I2C_writeAddress(I2Cx, slaveAddress)		(I2C_writeByte((I2Cx), (((slaveAddress) << 1) | I2Cx_WRITE)))
#define I2C1_SCL_GPIO								GPIOB
#define I2C1_SCL_PIN								GPIOx_PIN_6
#define I2C1_SDA_GPIO								GPIOB
#define I2C1_SDA_PIN								GPIOx_PIN_7
#define I2C2_SCL_GPIO								GPIOB
#define I2C2_SCL_PIN								GPIOx_PIN_10
#define I2C2_SDA_GPIO								GPIOB
#define I2C2_SDA_PIN								GPIOx_PIN_11

/**
 * @brief I2C Direction Initialisation
 * @param[in] I2C_CONFIGx I2C Configuration Structure
 */
#define I2C_init(I2C_CONFIGx) 			\
{										\
	/* I2C Configuration */ 			\
	I2C_Config((I2C_CONFIGx));			\
	/* I2C Enable */ 					\
	I2C_enable((I2C_CONFIGx)->I2Cx); 	\
}

// I2C Configuration Structure
typedef struct {
	// TODO: TRISE for Fast Mode
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
__INLINE__ void I2C_clk_enable(I2C_REG_STRUCT* I2Cx){
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
__INLINE__ void I2C_clk_disable(I2C_REG_STRUCT* I2Cx){
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
__INLINE__ void I2C_enable(I2C_REG_STRUCT* I2Cx){
	// Enable the I2C Module
	I2Cx->CR1.REG |= I2C_CR1_PE;
}

/**
 * @brief Disables the I2C
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__INLINE__ void I2C_disable(I2C_REG_STRUCT* I2Cx){
	// Enable the I2C Module
	I2Cx->CR1.REG &= ~I2C_CR1_PE;
}

/**
 * @brief I2C Bus Ready
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @returns - 0: I2C Bus is not ready
 * @returns - 1: I2C Bus is ready
 */
__INLINE__ uint8_t I2C_busReady(I2C_REG_STRUCT* I2Cx){
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
__INLINE__ void I2C_sendStart(I2C_REG_STRUCT* I2Cx){
	// Send START condition
	I2Cx->CR1.REG |= I2C_CR1_START;
}

/**
 * @brief I2C Byte Send
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] data Data to be TX
 */
__INLINE__ void I2C_writeByte(I2C_REG_STRUCT* I2Cx, uint8_t data){
	// Send data
	I2Cx->DR.REG = data;
}

/**
 * @brief I2C Byte Read
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @returns Data received from I2C Bus
 */
__INLINE__ uint8_t I2C_readByte(I2C_REG_STRUCT* I2Cx){
	// Receive data
	return (uint8_t) (I2Cx->DR.REG & 0xFF);
}

/**
 * @brief I2C Send STOP Sequence
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__INLINE__ void I2C_sendStop(I2C_REG_STRUCT* I2Cx){
	// Send STOP condition
	I2Cx->CR1.REG |= I2C_CR1_STOP;
}

/**
 * @brief Retrieves I2C Event IRQn
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @returns I2C IRQn
 */
__INLINE__ uint8_t I2C_getEV_IRQn(I2C_REG_STRUCT* I2Cx){
	// I2C1
	if(I2Cx == I2C1)
	return I2C1_EV_IRQn;
	// I2C2
	else if (I2Cx == I2C2)
		return I2C2_EV_IRQn;
}

/**
 * @brief Retrieves I2C Event IRQn
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @returns I2C IRQn
 */
__INLINE__ uint8_t I2C_getER_IRQn(I2C_REG_STRUCT* I2Cx){
	// I2C1
	if(I2Cx == I2C1)
		return I2C1_ER_IRQn;
	// I2C2
	else if (I2Cx == I2C2)
		return I2C2_ER_IRQn;
}

/**
 * @brief Enables the I2C Event Interrupt
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] buff_IRQ Buffer Interrupt Enable
 * @param[in] er_IRQ Error Interrupt Enable
 */
__INLINE__ void I2C_IRQ_enable(I2C_REG_STRUCT* I2Cx, uint8_t buff_IRQ, uint8_t er_IRQ){
	// Temporary Register
	uint32_t reg = I2Cx->CR2.REG;
	// Enables the I2C Event Interrupt
	reg |= I2C_CR2_ITEVTEN;
	// Buffer Interrupt Enable
	if(buff_IRQ)
		reg |= I2C_CR2_ITBUFEN;
	// Error Interrupt Enable
	if(er_IRQ){
		reg |= I2C_CR2_ITERREN;
		// NVIC Error Interrupt Enable
		NVIC_IRQ_Enable(I2C_getER_IRQn(I2Cx));
	}
	// NVIC Event Interrupt Enable
	NVIC_IRQ_Enable(I2C_getEV_IRQn(I2Cx));
	// Write to CR2
	I2Cx->CR2.REG = reg;
}

/**
 * @brief Disables the I2C Event Interrupt
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__INLINE__ void I2C_IRQ_disable(I2C_REG_STRUCT* I2Cx){
	// Clear Interrupts
	I2Cx->CR2.REG &= ~(I2C_CR2_ITBUFEN | I2C_CR2_ITEVTEN | I2C_CR2_ITERREN);
}

/**
 * @brief Enables I2C DMA Configuration
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__INLINE__ void I2C_DMA_enable(I2C_REG_STRUCT* I2Cx){
	// Enable the I2C DMA
	I2Cx->CR2.REG |= I2C_CR2_DMAEN;
}

/**
 * @brief Disables I2C DMA Configuration
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__INLINE__ void I2C_DMA_disable(I2C_REG_STRUCT* I2Cx){
	// Disable the I2C DMA
	I2Cx->CR2.REG &= ~I2C_CR2_DMAEN;
}

/**
 * @brief Configures I2C as per the Configuration Structure
 * @param[in] I2C_CONFIGx I2C Configuration Structure
 */
void I2C_Config(i2c_config_t* I2C_CONFIGx);

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

/**
 * @brief Writes a Single Byte to Register Address of a given Slave Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slave_address MAX30102 Slave Address
 * @param[in] register Register Address
 * @param[in] byte Data to be written
 */
void I2C_Write_Reg_Byte(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress, uint8_t byte);

/**
 * @brief Writes Multiple Consecutive Bytes to Register Address of a given Slave Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address
 * @param[in] registerAddress Starting Register Address
 * @param[in] data Pointer to the data buffer
 * @param[in] len Number of bytes to write
 */
void I2C_Write_Reg_Block(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, uint8_t len);

/**
 * @brief Reads a Single Byte from a Register Address of a given Slave Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address
 * @param[in] registerAddress Register Address to read from
 * @returns The read byte
 */
uint8_t I2C_Read_Reg_Byte(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress);

/**
 * @brief Reads Multiple Consecutive Bytes from a Register Address of a given Slave Address
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] slaveAddress Slave Address
 * @param[in] registerAddress Starting Register Address
 * @param[out] data Pointer to the buffer to store the read data
 * @param[in] len Number of bytes to read
 */
void I2C_Read_Reg_Block(I2C_REG_STRUCT* I2Cx, uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, uint8_t len);

/**
 * @brief I2C load default values
 * @param[in] I2C_CONFIGx I2C Configuration Structure
 */
void I2C1_Load_Default(i2c_config_t* I2C_CONFIGx);

/**
 * @brief I2C load default values
 * @param[in] I2C_CONFIGx I2C Configuration Structure
 */
void I2C2_Load_Default(i2c_config_t* I2C_CONFIGx);

#endif /* __I2C_H__ */