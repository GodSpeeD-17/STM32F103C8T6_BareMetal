// Header
#include "i2c_irq.h"

// Temporary Variable for Memory Efficiency
static uint32_t reg = 0x00;

/**
 * @brief Enables the I2C Interrupt
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param I2C_IRQ_status Any logical combination of 
 * 		  - `I2Cx_IRQ_EVENT`
 * 		  - `I2Cx_IRQ_BUFFER`
 * 		  - `I2Cx_IRQ_ERROR`
 * 		  - `I2Cx_IRQ_ALL`
 */
void I2C_IRQ_Enable(I2C_REG_STRUCT* I2Cx, uint8_t I2C_IRQ_status){
	// Temporary Register
	reg = I2Cx->CR2.REG;
	// Enables the I2C Event Interrupt
	if(I2C_IRQ_status & I2Cx_IRQ_EVENT)
		reg |= I2C_CR2_ITEVTEN;
	// Buffer Interrupt Enable
	if(I2C_IRQ_status & I2Cx_IRQ_BUFFER)
		reg |= I2C_CR2_ITBUFEN;
	// Error Interrupt Enable
	if(I2C_IRQ_status & I2Cx_IRQ_ERROR){
		reg |= I2C_CR2_ITERREN;
		NVIC_IRQ_Enable(I2C_Get_ER_IRQn(I2Cx));
	}
	// NVIC Event Interrupt Enable
	NVIC_IRQ_Enable(I2C_Get_EV_IRQn(I2Cx));
	// Write to CR2
	I2Cx->CR2.REG = reg;
}

/**
 * @brief Disables the I2C Interrupt
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param I2C_IRQ_status Any logical combination of 
 * 		  - `I2Cx_IRQ_EVENT`
 * 		  - `I2Cx_IRQ_BUFFER`
 * 		  - `I2Cx_IRQ_ERROR`
 * 		  - `I2Cx_IRQ_ALL`
 */
void I2C_IRQ_Disable(I2C_REG_STRUCT* I2Cx, uint8_t I2C_IRQ_status){
	// Temporary Register
	reg = I2Cx->CR2.REG;
	// Enables the I2C Event Interrupt
	if(I2C_IRQ_status & I2Cx_IRQ_EVENT)
		reg &= ~I2C_CR2_ITEVTEN;
	// Buffer Interrupt Enable
	if(I2C_IRQ_status & I2Cx_IRQ_BUFFER)
		reg &= ~I2C_CR2_ITBUFEN;
	// Error Interrupt Enable
	if(I2C_IRQ_status & I2Cx_IRQ_ERROR){
		reg &= ~I2C_CR2_ITERREN;
		NVIC_IRQ_Disable(I2C_Get_ER_IRQn(I2Cx));
	}
	// NVIC Event Interrupt Enable
	NVIC_IRQ_Disable(I2C_Get_EV_IRQn(I2Cx));
	// Write to CR2
	I2Cx->CR2.REG = reg;
}

