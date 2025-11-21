// // Header Guards
// #ifndef __I2C_DMA_H__
// #define __I2C_DMA_H__

// // Address Mapping
// #include "stm32f1xx.h"

// /**
//  * @brief Enables I2C DMA Configuration
//  * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
//  */
// __STATIC_FORCEINLINE void I2C_DMA_enable(I2C_TypeDef* I2Cx){
// 	// Enable the I2C DMA
// 	I2Cx->CR2.REG |= I2C_CR2_DMAEN;
// }

// /**
//  * @brief Disables I2C DMA Configuration
//  * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
//  */
// __STATIC_FORCEINLINE void I2C_DMA_disable(I2C_TypeDef* I2Cx){
// 	// Disable the I2C DMA
// 	I2Cx->CR2.REG &= ~I2C_CR2_DMAEN;
// }

// #endif /* __I2C_DMA_H__ */ 