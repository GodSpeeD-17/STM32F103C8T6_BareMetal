/**
 * @file dma_config.h
 * @author Shrey Shah
 * @brief DMA API Driver
 * @version 1.0
 * @date 04-10-2025
 */

 /*
===============================================================================
							DMA THEORY REFERENCE
===============================================================================

DMA (Direct Memory Access) is a hardware engine that moves data directly
between memory and peripherals without CPU intervention. It improves
efficiency, reduces CPU load, and ensures reliable timing for data streams.

------------------------------------------------------------------------------
ARCHITECTURE (STM32F103C8T6)
------------------------------------------------------------------------------
- One DMA controller: DMA1
- 7 Channels (no Streams on F1, those exist on F2/F4+)
- Each channel is HARD-WIRED to specific peripheral request lines
  (e.g. USART1_TX → DMA1 Channel4, ADC1 → DMA1 Channel1).

Each channel has 4 main registers:
- CCR   : Control register
- CNDTR : Number of data to transfer (counter)
- CPAR  : Peripheral address register
- CMAR  : Memory address register

Global status/interrupt flags are in DMA1_ISR and DMA1_IFCR.

------------------------------------------------------------------------------
CCR BITFIELDS
------------------------------------------------------------------------------
- EN     : Enable channel. Must clear EN=0 before reconfiguring.
- TCIE   : Transfer Complete interrupt enable.
- HTIE   : Half Transfer interrupt enable.
- TEIE   : Transfer Error interrupt enable.
- DIR    : Transfer direction.
		   0 = Peripheral → Memory
		   1 = Memory → Peripheral
		   In MEM2MEM mode: selects which endpoint is source/destination.
- CIRC   : Circular mode (auto-reload NDTR when it hits zero).
- PINC   : Increment peripheral address after each transfer.
- MINC   : Increment memory address after each transfer.
- PSIZE  : Peripheral data size (8/16/32 bits).
- MSIZE  : Memory data size (8/16/32 bits).
- PL     : Priority level (low → very high).
- MEM2MEM: Enables memory-to-memory transfers.

------------------------------------------------------------------------------
HOW IT WORKS
------------------------------------------------------------------------------
- Peripheral asserts request line (e.g. USART TXE, RXNE, ADC EOC).
- DMA channel sees request and performs one transfer:
  - Reads from source (CPAR or CMAR depending on DIR).
  - Writes to destination.
  - Decrements NDTR.
- When NDTR hits zero → Transfer Complete (TC) flag.
- In Circular mode, NDTR auto-reloads, transfer continues.

------------------------------------------------------------------------------
IRQ RELATIONSHIP
------------------------------------------------------------------------------
- Peripheral flags (TXE, RXNE) normally trigger CPU interrupts.
- When DMA is enabled, those requests feed the DMA controller instead.
- CPU does NOT see per-byte interrupts anymore.
- Instead, DMA generates its own interrupts:
  - Half Transfer (HT): NDTR reached half.
  - Transfer Complete (TC): NDTR reached zero.
  - Transfer Error (TE): bus error, misaligned access, etc.
- Application should use DMA IRQs for block events, and peripheral IRQs
  only for exceptions (e.g. UART IDLE line for frame detection).

------------------------------------------------------------------------------
USAGE PATTERNS
------------------------------------------------------------------------------
- USART TX (memory → peripheral):
  DIR=1, MINC=1, PINC=0, sizes=8-bit, CIRC=0, TCIE=1.
- USART RX (peripheral → memory, circular buffer):
  DIR=0, MINC=1, PINC=0, sizes=8-bit, CIRC=1, HTIE+TCIE=1.
- ADC continuous sampling:
  DIR=0, MINC=1, PINC=0, sizes=16-bit, CIRC=1, HTIE+TCIE=1.
- Memory copy:
  MEM2MEM=1, set DIR depending on which endpoint is source.

------------------------------------------------------------------------------
DESIGN PRINCIPLES
------------------------------------------------------------------------------
- ISR should be minimal: only clear flags + set "event" variables.
- Main loop or RTOS task should handle actual data processing.
- Always enable TEIE to catch bus errors.
- Never re-enable DMA channel without clearing EN first.
- DMA guarantees data plane reliability; CPU handles control plane logic.

===============================================================================
*/

// Header Guards
#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

// C++ Compatibility
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ---- Includes ---- //
#include "nvic.h"

// --- Data Type Definitions --- //
typedef uint8_t dma_channel_priority_t;
typedef uint8_t dma_transfer_dir_t;
typedef uint8_t dma_endpoint_data_size_t;
typedef uint8_t dma_endpoint_address_increment_t;
typedef uint8_t dma_circular_mode_t;
typedef uint8_t dma_mem2mem_mode_t;

// --- DMA Transfer Direction --- //
#define DMA_DIR_PERIPHERAL_TO_MEMORY				((dma_transfer_dir_t) 0x00)
#define DMA_DIR_MEMORY_TO_PERIPHERAL				((dma_transfer_dir_t) 0x01)
#define DMA_DIR_MEMORY_TO_MEMEORY					((dma_transfer_dir_t) 0x02)

// --- DMA Priority levels --- //
#define DMA_PRIORITY_LOW							((dma_channel_priority_t) 0x00)
#define DMA_PRIORITY_MEDIUM							((dma_channel_priority_t) 0x01)
#define DMA_PRIORITY_HIGH							((dma_channel_priority_t) 0x02)
#define DMA_PRIORITY_VERY_HIGH						((dma_channel_priority_t) 0x03)

// --- DMA Circular Mode --- //
#define DMA_MODE_CIRCULAR_DISABLE					((dma_circular_mode_t) 0x00)
#define DMA_MODE_CIRCULAR_ENABLE					((dma_circular_mode_t) 0x01)

// --- DMA MEM2MEM Mode --- //
#define DMA_MODE_MEM2MEM_DISABLE					((dma_mem2mem_mode_t) 0x00)
#define DMA_MODE_MEM2MEM_ENABLE						((dma_mem2mem_mode_t) 0x01)

/**
 * @brief DMA Endpoint Configuration Structure
 * @note Provides configuration for data size & address increment
 */
typedef struct {
	// Data Size
	dma_endpoint_data_size_t size: 2;
	// Increment Address
	dma_endpoint_address_increment_t increment: 1;
} dma_endpoint_t;

/**
 * @brief DMA Mode Configuration Structure
 * @note Provides mode configuration for Circular & `MEM2MEM` Mode
 */
typedef struct {
	// Circular Mode
	dma_circular_mode_t circular: 1;
	// Memeory to Memory Transfer Mode
	dma_mem2mem_mode_t mem2mem: 1;
} dma_mode_t;

//TODO: <<<< Optimize naming ????
/**
 * @brief DMA Transfer Configuration Structure
 * @note Defines the memory and peripheral pointers and the transfer length
 */
typedef struct {
	// Peripheral address
	void* peripheral;
	// Memory address
	void* memory;
	// Number of data items to transfer (max 65535)
	uint16_t size;
} dma_transfer_config_t;

/**
 * @brief DMA Configuration Structure
 * @note Controls transfer direction, priority, and addressing
 */
typedef struct {
	// Channel priority level
	dma_channel_priority_t priority: 2;
	// Transfer direction
	dma_transfer_dir_t direction: 1;
	// Source Descriptor
	dma_endpoint_t memory;
	// Destination Descriptor
	dma_endpoint_t peripheral;
	// DMA Mode Configuration
	dma_mode_t mode;
	// Transfer Configuration
	dma_transfer_config_t transfer;
} dma_config_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DMA_CONFIG_H__ */