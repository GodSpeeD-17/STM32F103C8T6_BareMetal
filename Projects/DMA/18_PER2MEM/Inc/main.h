// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

/*-------------------------------------------------------------------------------*/
// Headers
#include "bare_metal.h"
/*-------------------------------------------------------------------------------*/
// DMA Configuration Structure
dma_config_t I2C_DMA_Configuration;
i2c_config_t I2C_Configuration;
uint8_t i2c_buffer = 0x3C;

// GPIO Configuration Structure
gpio_config_t LED_Configuration = {
	.GPIO = GPIOA,
	.PIN = GPIOx_PIN_2,
	.MODE = GPIOx_MODE_OUT_10MHz,
	.CNF = GPIOx_CNF_OUT_GP_PP
};
/*-------------------------------------------------------------------------------*/
// MACROS
#define LOOP_DELAY_MS						((uint32_t) 1000)
/*-------------------------------------------------------------------------------*/

#endif /* __MAIN_H__ */ 