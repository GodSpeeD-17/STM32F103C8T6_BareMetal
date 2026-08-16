// // Header Guards
// #ifndef __I2C_IRQ_H__
// #define __I2C_IRQ_H__

// // Address Mapping
// #include "stm32f1xx.h"
// #include "i2c_config.h"
// /**
//  * @brief Enables the I2C Interrupt
//  * @param I2Cx I2C Instance: `I2C1`, `I2C2`
//  * @param I2C_IRQ_status Any logical combination of 
//  * 		  - `I2Cx_IRQ_EVENT`
//  * 		  - `I2Cx_IRQ_BUFFER`
//  * 		  - `I2Cx_IRQ_ERROR`
//  * 		  - `I2Cx_IRQ_ALL`
//  */
// void I2C_IRQ_Enable(I2C_TypeDef* I2Cx, uint8_t I2C_IRQ_status);

// /**
//  * @brief Disables the I2C Interrupt
//  * @param I2Cx I2C Instance: `I2C1`, `I2C2`
//  * @param I2C_IRQ_status Any logical combination of 
//  * 		  - `I2Cx_IRQ_EVENT`
//  * 		  - `I2Cx_IRQ_BUFFER`
//  * 		  - `I2Cx_IRQ_ERROR`
//  * 		  - `I2Cx_IRQ_ALL`
//  */
// void I2C_IRQ_Disable(I2C_TypeDef* I2Cx, uint8_t I2C_IRQ_status);

// #endif /* __I2C_IRQ_H__ */
