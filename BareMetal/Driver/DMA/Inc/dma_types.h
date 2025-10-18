/**
 * @file dma_types.h
 * @author Shrey Shah
 * @brief DMA API Driver
 * @version 1.1
 * @date 05-10-2025
 * Logs: Added DMA Configuration Structure
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

/*********************************************** Header Guards ***********************************************/
#ifndef DMA_TYPES_H
#define DMA_TYPES_H

// C++ Compatibility
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*********************************************** Includes ***********************************************/
#include "nvic.h"

/*********************************************** Data Type Definitions ***********************************************/
typedef uint8_t dma_channel_priority_t;
typedef uint8_t dma_transfer_dir_t;
typedef uint8_t dma_endpoint_data_size_t;
typedef uint8_t dma_endpoint_memory_increment_t;
typedef uint8_t dma_circular_mode_t;
typedef uint8_t dma_mem2mem_mode_t;
typedef uint8_t dma_channel_t;
typedef uint8_t dma_irq_t;
typedef void* dma_src_t;
typedef void* dma_dst_t;
typedef uint16_t dma_size_t;

/*********************************************** DMA Channel ***********************************************/
#define DMA_1_Channel_1								((dma_channel_t) 0x00)
#define DMA_1_Channel_2								((dma_channel_t) 0x01)
#define DMA_1_Channel_3								((dma_channel_t) 0x02)
#define DMA_1_Channel_4								((dma_channel_t) 0x03)
#define DMA_1_Channel_5								((dma_channel_t) 0x04)
#define DMA_1_Channel_6								((dma_channel_t) 0x05)
#define DMA_1_Channel_7								((dma_channel_t) 0x06)
#define DMA_2_Channel_1								((dma_channel_t) 0x07)
#define DMA_2_Channel_2								((dma_channel_t) 0x08)
#define DMA_2_Channel_3								((dma_channel_t) 0x09)
#define DMA_2_Channel_4								((dma_channel_t) 0x0A)
#define DMA_2_Channel_5								((dma_channel_t) 0x0B)

/*********************************************** STM32F103C8T6 ***********************************************/
#if defined(STM32F103C8T6__)
// --- DMA 1 Channel 1 ---- //
#define DMA_ADC1_Channel							DMA1_Channel1
#define DMA_TIM2_CH3_Channel						DMA1_Channel1
#define DMA_TIM4_CH1_Channel						DMA1_Channel1
// --- DMA 1 Channel 2 ---- //
#define DMA_SPI1_RX_Channel							DMA1_Channel2
#define DMA_USART3_TX_Channel						DMA1_Channel2
#define DMA_TIM1_CH1_Channel						DMA1_Channel2
#define DMA_TIM2_UP_Channel							DMA1_Channel2
#define DMA_TIM3_CH3_Channel						DMA1_Channel2
// --- DMA 1 Channel 3 ---- //
#define DMA_SPI1_TX_Channel							DMA1_Channel3
#define DMA_USART3_RX_Channel						DMA1_Channel3
#define DMA_TIM3_CH4_Channel						DMA1_Channel3
#define DMA_TIM3_UP_Channel							DMA1_Channel3
// --- DMA 1 Channel 4 ---- //
#define DMA_SPI2_RX_Channel							DMA1_Channel4
#define DMA_I2S2_RX_Channel							DMA1_Channel4
#define DMA_USART1_TX_Channel						DMA1_Channel4
#define DMA_I2C2_TX_Channel							DMA1_Channel4
#define DMA_TIM1_CH4_Channel						DMA1_Channel4
#define DMA_TIM1_TRIG_Channel						DMA1_Channel4
#define DMA_TIM1_COM_Channel						DMA1_Channel4
#define DMA_TIM4_CH2_Channel						DMA1_Channel4
// --- DMA 1 Channel 5 ---- //
#define DMA_SPI2_TX_Channel							DMA1_Channel5
#define DMA_I2S2_TX_Channel							DMA1_Channel5
#define DMA_USART1_RX_Channel						DMA1_Channel5
#define DMA_I2C2_RX_Channel							DMA1_Channel5
#define DMA_TIM1_UP_Channel							DMA1_Channel5
#define DMA_TIM2_CH1_Channel						DMA1_Channel5
#define DMA_TIM4_CH3_Channel						DMA1_Channel5
// --- DMA 1 Channel 6 ---- //
#define DMA_USART2_RX_Channel						DMA1_Channel6
#define DMA_I2C1_TX_Channel							DMA1_Channel6
#define DMA_TIM1_CH3_Channel						DMA1_Channel6
#define DMA_TIM3_CH1_Channel						DMA1_Channel6
#define DMA_TIM3_TRIG_Channel						DMA1_Channel6
// --- DMA 1 Channel 7 ---- //
#define DMA_USART2_TX_Channel						DMA1_Channel7
#define DMA_I2C1_RX_Channel							DMA1_Channel7
#define DMA_TIM2_CH2_Channel						DMA1_Channel7
#define DMA_TIM2_CH4_Channel						DMA1_Channel7
#define DMA_TIM4_UP_Channel							DMA1_Channel7
#endif /* STM32F103C8T6__ */
/******************************** STM32F103C8T6 ********************************/


/*********************************************** DMA Transfer Direction ***********************************************/
#define DMA_CHANNEL_DIR_PERIPHERAL_TO_MEMORY		((dma_transfer_dir_t) 0x00)
#define DMA_CHANNEL_DIR_MEMORY_TO_PERIPHERAL		((dma_transfer_dir_t) 0x01)

/*********************************************** DMA Priority levels ***********************************************/
#define DMA_CHANNEL_PRIORITY_LOW					((dma_channel_priority_t) 0x00)
#define DMA_CHANNEL_PRIORITY_MEDIUM					((dma_channel_priority_t) 0x01)
#define DMA_CHANNEL_PRIORITY_HIGH					((dma_channel_priority_t) 0x02)
#define DMA_CHANNEL_PRIORITY_VERY_HIGH				((dma_channel_priority_t) 0x03)

/*********************************************** DMA Circular Mode ***********************************************/
#define DMA_CHANNEL_CIRCULAR_MODE_DISABLE			((dma_circular_mode_t) 0x00)
#define DMA_CHANNEL_CIRCULAR_MODE_ENABLE			((dma_circular_mode_t) 0x01)

/*********************************************** DMA MEM2MEM Mode ***********************************************/
#define DMA_CHANNEL_MEM2MEM_MODE_DISABLE			((dma_mem2mem_mode_t) 0x00)
#define DMA_CHANNEL_MEM2MEM_MODE_ENABLE				((dma_mem2mem_mode_t) 0x01)

/*********************************************** DMA ENDPOINT DATA SIZE ***********************************************/
#define DMA_ENDPOINT_DATA_SIZE_8_BIT				((dma_endpoint_data_size_t) 0x00)
#define DMA_ENDPOINT_DATA_SIZE_16_BIT				((dma_endpoint_data_size_t) 0x01)
#define DMA_ENDPOINT_DATA_SIZE_32_BIT				((dma_endpoint_data_size_t) 0x02)

/*********************************************** DMA ENDPOINT MEMORY INCREMENT ***********************************************/
#define DMA_ENDPOINT_MEMORY_INCREMENT_DISABLE		((dma_endpoint_memory_increment_t) 0x00)
#define DMA_ENDPOINT_MEMORY_INCREMENT_ENABLE		((dma_endpoint_memory_increment_t) 0x01)

/*********************************************** DMA IRQ ***********************************************/
#define DMA_IRQ_TRANSFER_COMPLETE					((dma_irq_t) 0x01)
#define DMA_IRQ_HALF_TRANSFER_COMPLETE				((dma_irq_t) 0x02)
#define DMA_IRQ_TRANSFER_ERROR						((dma_irq_t) 0x04)

/*********************************************** Configuration Structure ***********************************************/
/**
 * @brief DMA Endpoint Configuration Structure
 * @note Provides configuration for data size & address increment
 */
typedef struct {
	// Data Size
	dma_endpoint_data_size_t size: 2;
	// Increment Address
	dma_endpoint_memory_increment_t increment: 1;
} dma_endpoint_t;

/**
 * @brief DMA Channel Mode Configuration Structure
 * @note Provides configuration for generic modes of a channel
 */
typedef struct {
	// Channel priority level
	// - `DMA_CHANNEL_PRIORITY_LOW`: Background tasks
	// - `DMA_CHANNEL_PRIORITY_MEDIUM`: Normal communication  
	// - `DMA_CHANNEL_PRIORITY_HIGH`: Time-sensitive data
	// - `DMA_CHANNEL_PRIORITY_VERY_HIGH`: Critical system functions
	dma_channel_priority_t priority: 2;
	
	// Transfer direction
	// - DMA_CHANNEL_DIR_PERIPHERAL_TO_MEMORY: Read from peripheral, write to memory
	// - DMA_CHANNEL_DIR_MEMORY_TO_PERIPHERAL: Read from memory, write to peripheral  
	// - DMA_DIR_MEMORY_TO_MEMORY: Memory copy operation
	dma_transfer_dir_t direction: 1;
	
	// Circular Mode
	// - DMA_CHANNEL_CIRCULAR_MODE_DISABLE: One-time transfer
	// - DMA_CHANNEL_CIRCULAR_MODE_ENABLE: Continuous/loop transfer
	dma_circular_mode_t circular: 1;
	
	// Memory to Memory Transfer Mode
	// - DMA_CHANNEL_MEM2MEM_MODE_DISABLE: Peripheral involved in transfer
	// - DMA_CHANNEL_MEM2MEM_MODE_ENABLE: Pure memory copy operation
	dma_mem2mem_mode_t mem2mem: 1;
} dma_channel_mode_config_t;

/**
 * @brief DMA Data Transfer Structure
 * @note Determines transfer configuration
 */
typedef struct {
	// Source Address
	dma_src_t src;
	// Destination Address
	dma_dst_t dst;
	// Size of Data to be Transferred
	dma_size_t size;
} dma_transfer_t;

/**
 * @brief DMA Configuration Structure
 * @note Complete configuration for DMA channel operation
 * 
 * USAGE SCENARIOS:
 * 
 * - Scenario 1: UART TX (Memory → Peripheral)
 *   - direction: DMA_CHANNEL_DIR_MEMORY_TO_PERIPHERAL
 *   - memory.increment: ENABLE (move through buffer)
 *   - peripheral.increment: DISABLE (fixed UART data register)
 *   - mem2mem: DISABLE
 *   - circular: DISABLE (one-time transfer)
 * 
 * - Scenario 2: UART RX (Peripheral → Memory)  
 *   - direction: DMA_CHANNEL_DIR_PERIPHERAL_TO_MEMORY
 *   - memory.increment: ENABLE (fill buffer sequentially)
 *   - peripheral.increment: DISABLE (fixed UART data register)
 *   - mem2mem: DISABLE
 *   - circular: ENABLE (continuous reception)
 * 
 * - Scenario 3: Memory Copy (Memory → Memory)
 *   - direction: DMA_DIR_MEMORY_TO_MEMORY
 *   - memory.increment: ENABLE (read from source buffer)
 *   - peripheral.increment: ENABLE (write to destination buffer)  
 *   - mem2mem: ENABLE
 *   - circular: DISABLE
 * 
 * - Scenario 4: ADC Sampling (Peripheral → Memory)
 *   - direction: DMA_CHANNEL_DIR_PERIPHERAL_TO_MEMORY
 *   - memory.increment: ENABLE (store samples in array)
 *   - peripheral.increment: DISABLE (fixed ADC data register)
 *   - mem2mem: DISABLE
 *   - circular: ENABLE (continuous sampling)
 */
typedef struct {
	// DMA Channel Configuration
	// - Channel Priority Level
	// - Data transfer direction
	// - Circular Mode
	// - MEM2MEM Mode
	dma_channel_mode_config_t config;

	// Memory Endpoint Configuration
	// - Controls data size and address increment for memory side
	// - Used as SOURCE in Memory→Peripheral transfers
	// - Used as DESTINATION in Peripheral→Memory transfers  
	// - Used as BOTH in Memory→Memory transfers
	dma_endpoint_t memory;
	
	// Peripheral Endpoint Configuration
	// - Controls data size and address increment for peripheral side
	// - Used as DESTINATION in Memory→Peripheral transfers
	// - Used as SOURCE in Peripheral→Memory transfers
	// - Typically has increment DISABLED for fixed peripheral registers
	dma_endpoint_t peripheral;
} dma_channel_config_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DMA_TYPES_H */