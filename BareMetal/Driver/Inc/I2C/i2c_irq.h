// Header Guards
#ifndef __I2C_IRQ_H__
#define __I2C_IRQ_H__

// Address Mapping
#include "reg_map.h"
#include "i2c_config.h"
// Interrupt Configuration
#include "nvic.h"

/**
 * @brief Retrieves I2C Event IRQn
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @returns I2C IRQn
 */
__INLINE__ uint8_t I2C_Get_EV_IRQn(I2C_REG_STRUCT* I2Cx){
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
__INLINE__ uint8_t I2C_Get_ER_IRQn(I2C_REG_STRUCT* I2Cx){
	// I2C1
	if(I2Cx == I2C1)
		return I2C1_ER_IRQn;
	// I2C2
	else if (I2Cx == I2C2)
		return I2C2_ER_IRQn;
}

/**
 * @brief Enables the I2C Interrupt
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] I2C_IRQ_status Any logical combination of 
 * @param `I2Cx_IRQ_EVENT`
 * @param `I2Cx_IRQ_BUFFER`
 * @param `I2Cx_IRQ_ERROR`
 * @param `I2Cx_IRQ_ALL`
 */
void I2C_IRQ_Enable(I2C_REG_STRUCT* I2Cx, uint8_t I2C_IRQ_status);

/**
 * @brief Disables the I2C Interrupt
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] I2C_IRQ_status Any logical combination of 
 * @param `I2Cx_IRQ_EVENT`
 * @param `I2Cx_IRQ_BUFFER`
 * @param `I2Cx_IRQ_ERROR`
 * @param `I2Cx_IRQ_ALL`
 */
void I2C_IRQ_Disable(I2C_REG_STRUCT* I2Cx, uint8_t I2C_IRQ_status);

#endif /* __I2C_IRQ_H__ */ 