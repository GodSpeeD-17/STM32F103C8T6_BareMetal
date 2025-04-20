// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

/*-------------------------------------------------------------------------------*/
// Headers
#include "bare_metal.h"
#include "ssd1306.h"
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
// MACROS
#define LOOP_DELAY_MS						((uint32_t) 1000)
#define BUFFER_SIZE							128
/*-------------------------------------------------------------------------------*/
// Variables
uint8_t src_buffer[BUFFER_SIZE + 1] = {[0 ... BUFFER_SIZE] = 0xFF};

// DMA Configuration
dma_config_t DMA_SSD1306_Configuration;
// I2C Configuration Structure
i2c_config_t I2C_SSD1306_Configuration;

// LED Configuration
gpio_config_t LED_Configuration = {
	.GPIO = GPIOA,
	.PIN = GPIOx_PIN_2,
	.MODE = GPIOx_MODE_OUT_10MHz,
	.CNF = GPIOx_CNF_OUT_GP_PP
};
/*-------------------------------------------------------------------------------*/
void I2C1_EV_IRQHandler(void);

#endif /* __MAIN_H__ */ 