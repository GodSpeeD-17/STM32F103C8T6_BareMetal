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
#define BUFFER_SIZE							((uint8_t) 128)
/*-------------------------------------------------------------------------------*/
// Variables
__attribute__ ((aligned(4))) uint8_t src_buffer[BUFFER_SIZE] = {[0 ... 127] = 0xAA}; 
__attribute__ ((aligned(4))) uint8_t dst_buffer[BUFFER_SIZE];
/*-------------------------------------------------------------------------------*/
// Channel Configuration Structure
dma_channel_config_t mem2mem_config = {
	.direction = DMAx_DIR_READ_FROM_PER, // Direction doesn't matter for MEM2MEM
	.mem2mem = DMAx_MEM2MEM_ENABLE,      // Enable memory-to-memory mode
	.circular_mode = DMAx_CIRC_DISABLE,
	.priority = DMAx_PRIORITY_HIGH
};
// Channel Data Configuration Structure
dma_channel_data_t mem2mem_data_config = {
	.srcDataSize = DMAx_DATA_SIZE_BIT_8,  // 8-bit transfers
	.dstDataSize = DMAx_DATA_SIZE_BIT_8,  // Must match source size
	.srcInc = DMAx_INC_ENABLE,
	.dstInc = DMAx_INC_ENABLE
};
// Channel Interrupt Configuration Structure
dma_channel_intr_t mem2mem_irq_config = {
	.TCIE = DMAx_IRQ_ENABLE,  // Transfer complete interrupt
	.HTIE = DMAx_IRQ_DISABLE,
	.TEIE = DMAx_IRQ_ENABLE   // Error interrupt
};
// GPIO Configuration Structure
gpio_config_t LED_Configuration = {
	.GPIO = GPIOA,
	.PIN = GPIOx_PIN_2,
	.MODE = GPIOx_MODE_OUT_10MHz,
	.CNF = GPIOx_CNF_OUT_GP_PP
};
/*-------------------------------------------------------------------------------*/
#endif /* __MAIN_H__ */