// Header Guards
#ifndef __DMA_REG_MAP_H__
#define __DMA_REG_MAP_H__

// Dependency
#include "common.h"

// DMA Register Structure
typedef struct {
	// DMA Interrupt Status Register (DMA_ISR)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Channel 1
			volatile uint32_t GIF1: 1;
			volatile uint32_t TCIF1: 1;
			volatile uint32_t HTIF1: 1;
			volatile uint32_t TEIF1: 1;
			// Channel 2
			volatile uint32_t GIF2: 1;
			volatile uint32_t TCIF2: 1;
			volatile uint32_t HTIF2: 1;
			volatile uint32_t TEIF2: 1;
			// Channel 3
			volatile uint32_t GIF3: 1;
			volatile uint32_t TCIF3: 1;
			volatile uint32_t HTIF3: 1;
			volatile uint32_t TEIF3: 1;
			// Channel 4
			volatile uint32_t GIF4: 1;
			volatile uint32_t TCIF4: 1;
			volatile uint32_t HTIF4: 1;
			volatile uint32_t TEIF4: 1;
			// Channel 5
			volatile uint32_t GIF5: 1;
			volatile uint32_t TCIF5: 1;
			volatile uint32_t HTIF5: 1;
			volatile uint32_t TEIF5: 1;
			// Channel 6
			volatile uint32_t GIF6: 1;
			volatile uint32_t TCIF6: 1;
			volatile uint32_t HTIF6: 1;
			volatile uint32_t TEIF6: 1;
			// Channel 7
			volatile uint32_t GIF7: 1;
			volatile uint32_t TCIF7: 1;
			volatile uint32_t HTIF7: 1;
			volatile uint32_t TEIF7: 1;
			// Reserved
			volatile uint32_t RESERVED: 4;
		} BIT;
	} ISR;
	// DMA Interrupt Flag Clear Register (DMA_IFCR)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Channel 1
			volatile uint32_t CGIF1: 1;
			volatile uint32_t CTCIF1: 1;
			volatile uint32_t CHTIF1: 1;
			volatile uint32_t CTEIF1: 1;
			// Channel 2
			volatile uint32_t CGIF2: 1;
			volatile uint32_t CTCIF2: 1;
			volatile uint32_t CHTIF2: 1;
			volatile uint32_t CTEIF2: 1;
			// Channel 3
			volatile uint32_t CGIF3: 1;
			volatile uint32_t CTCIF3: 1;
			volatile uint32_t CHTIF3: 1;
			volatile uint32_t CTEIF3: 1;
			// Channel 4
			volatile uint32_t CGIF4: 1;
			volatile uint32_t CTCIF4: 1;
			volatile uint32_t CHTIF4: 1;
			volatile uint32_t CTEIF4: 1;
			// Channel 5
			volatile uint32_t CGIF5: 1;
			volatile uint32_t CTCIF5: 1;
			volatile uint32_t CHTIF5: 1;
			volatile uint32_t CTEIF5: 1;
			// Channel 6
			volatile uint32_t CGIF6: 1;
			volatile uint32_t CTCIF6: 1;
			volatile uint32_t CHTIF6: 1;
			volatile uint32_t CTEIF6: 1;
			// Channel 7
			volatile uint32_t CGIF7: 1;
			volatile uint32_t CTCIF7: 1;
			volatile uint32_t CHTIF7: 1;
			volatile uint32_t CTEIF7: 1;
			// Reserved
			volatile uint32_t RESERVED: 4;
		} BIT;
	} IFCR;
} DMA_REG_STRUCT;

// DMA Channel Register Structure Configuration
typedef struct {
	// DMA Channel 1 Configuration Register (DMA_CCR)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t EN: 1;
			volatile uint32_t TCIE: 1;
			volatile uint32_t HTIE: 1;
			volatile uint32_t TEIE: 1;
			volatile uint32_t DIR: 1;
			volatile uint32_t CIRC: 1;
			volatile uint32_t PINC: 1;
			volatile uint32_t MINC: 1;
			volatile uint32_t PSIZE: 2;
			volatile uint32_t MSIZE: 2;
			volatile uint32_t PL: 2;
			volatile uint32_t MEM2MEM: 1;
			// Reserved
			volatile uint32_t RESERVED: 17;
		} BIT;
	} CCR;
	// DMA Channel  Number of Data Register (DMA_CNDTR)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Number of data to transfer
			volatile uint32_t NDT: 1;
			// Reserved
			volatile uint32_t RESERVED: 17;
		} BIT;
	} CNDTR;
	// DMA Channel  Peripheral Address Register (DMA_CPAR)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Peripheral Address
			volatile uint32_t PA;
		} BIT;
	} CPAR;
	// DMA Channel  Memory Address Register (DMA_CMAR)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Memory Address
			volatile uint32_t MA;
		} BIT;
	} CMAR;
} DMA_CHANNEL_REG_STRUCT;


#endif /* __DMA_REG_MAP_H__ */ 