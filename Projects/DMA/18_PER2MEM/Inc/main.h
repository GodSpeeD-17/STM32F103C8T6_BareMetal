// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

/*-------------------------------------------------------------------------------*/
// Headers
#include "bare_metal.h"
/*-------------------------------------------------------------------------------*/
// DMA Configuration Structure
dma_config_t USART_DMA_Configuration;
uint8_t usart_buffer = 0xAA;

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