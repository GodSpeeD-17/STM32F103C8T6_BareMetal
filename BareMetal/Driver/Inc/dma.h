// Header Guards
#ifndef __DMA_H__
#define __DMA_H__

// Dependency
#include "reg_map.h"

// DMA Configuration Structure
typedef struct {
	dma_direction_t direction;   // Direction of data transfer
	dma_data_size_t data_size;   // Data size (byte, half-word, word)
	uint8_t circular_mode;       // Enable circular mode (0: disabled, 1: enabled)
	dma_priority_t priority;     // Priority level
} dma_config_t;

// DMA Direction Enum
typedef enum {
	DMA_DIR_PERIPHERAL_TO_MEMORY = 0,
	DMA_DIR_MEMORY_TO_PERIPHERAL,
	DMA_DIR_MEMORY_TO_MEMORY
} dma_direction_t;

// 
typedef enum {
	DMA_DATA_SIZE_BYTE = 0,
	DMA_DATA_SIZE_HALFWORD,
	DMA_DATA_SIZE_WORD
} dma_data_size_t;

// 
typedef enum {
	DMA_PRIORITY_LOW = 0,
	DMA_PRIORITY_MEDIUM,
	DMA_PRIORITY_HIGH,
	DMA_PRIORITY_VERY_HIGH
} dma_priority_t;


#endif /* __DMA_H__ */ 