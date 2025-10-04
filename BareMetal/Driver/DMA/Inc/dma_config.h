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
#include "reg_map.h"

// --- Configuration Structure --- //
typedef struct {

} dma_config_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DMA_CONFIG_H__ */