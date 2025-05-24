// Header Guards
#ifndef __I2C_DMA_H__
#define __I2C_DMA_H__

// Address Mapping
#include "reg_map.h"

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

#endif /* __I2C_DMA_H__ */ 