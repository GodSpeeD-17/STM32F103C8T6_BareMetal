// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__
/*-------------------------------------------------------------------------------*/
// Headers
#include "bare_metal.h"
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
// MACROS
#define LOOP_DELAY_MS						((uint32_t) 1000)
#define BUFFER_SIZE							((uint8_t) 32)

/*-------------------------------------------------------------------------------*/
// Variables
#ifdef BIT_SIZE_8
	__attribute__ ((aligned(4))) uint8_t src_buffer[BUFFER_SIZE] = {[0 ... (BUFFER_SIZE - 1)] = 0xAA}; 
	__attribute__ ((aligned(4))) uint8_t dst_buffer[BUFFER_SIZE] = {[0 ... (BUFFER_SIZE - 1)] = 0x00};
#else
	__attribute__ ((aligned(4))) uint32_t src_buffer[BUFFER_SIZE] = {[0 ... (BUFFER_SIZE - 1)] = 0xDDCCBBAA}; 
	__attribute__ ((aligned(4))) uint32_t dst_buffer[BUFFER_SIZE] = {[0 ... (BUFFER_SIZE - 1)] = 0x00};
#endif /* BIT_SIZE_8 */
/*-------------------------------------------------------------------------------*/
// DMA Configuration
dma_channel_config_t DMA_Configuration = {NULL};
// GPIO Configuration Structure
gpio_config_t LED_Configuration = {
	.GPIO = GPIOA,
	.PIN = GPIOx_PIN_2,
	.MODE = GPIOx_MODE_OUT_10MHz,
	.CNF = GPIOx_CNF_OUT_GP_PP
};
/*-------------------------------------------------------------------------------*/
#endif /* __MAIN_H__ */