// Header Guards
#ifndef __DMA_REG_MAP_H__
#define __DMA_REG_MAP_H__

#include "common.h"

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
	}ISR;
	// DMA Interrupt Flag Clear Register (DMA_IFR)
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
	}IFR;
	// DMA Channel 1 Configuration Register (DMA_CCR1)
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
	}CCR1;
	// DMA Channel 2 Configuration Register (DMA_CCR2)
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
	}CCR2;
	// DMA Channel 3 Configuration Register (DMA_CCR3)
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
	}CCR3;
	// DMA Channel 4 Configuration Register (DMA_CCR4)
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
	}CCR4;
	// DMA Channel 5 Configuration Register (DMA_CCR5)
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
	}CCR5;
	// DMA Channel 6 Configuration Register (DMA_CCR6)
	union {
		// Full 32-bit Register Access// DMA Channel X Configuration Register (DMA_CCRx)
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
	}CCR1;
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
	}CCR6;
	// DMA Channel 7 Configuration Register (DMA_CCR7)
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
	}CCR7;
	// DMA Channel 1 Number of Data Register (DMA_CNDTR1)
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
	}CNDTR1;
	// DMA Channel 2 Number of Data Register (DMA_CNDTR2)
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
	}CNDTR2;
	// DMA Channel 3 Number of Data Register (DMA_CNDTR3)
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
	}CNDTR3;
	// DMA Channel 4 Number of Data Register (DMA_CNDTR4)
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
	}CNDTR4;
	// DMA Channel 5 Number of Data Register (DMA_CNDTR5)
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
	}CNDTR5;
	// DMA Channel 6 Number of Data Register (DMA_CNDTR6)
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
	}CNDTR6;
	// DMA Channel 7 Number of Data Register (DMA_CNDTR7)
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
	}CNDTR7;
	// DMA Channel 1 Peripheral Address Register (DMA_CPAR1)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Peripheral Address
			volatile uint32_t PA;
		} BIT;
	}CPAR1;
	// DMA Channel 2 Peripheral Address Register (DMA_CPAR2)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Peripheral Address
			volatile uint32_t PA;
		} BIT;
	}CPAR2;
	// DMA Channel 3 Peripheral Address Register (DMA_CPAR3)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Peripheral Address
			volatile uint32_t PA;
		} BIT;
	}CPAR3;
	// DMA Channel 4 Peripheral Address Register (DMA_CPAR4)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Peripheral Address
			volatile uint32_t PA;
		} BIT;
	}CPAR4;
	// DMA Channel 5 Peripheral Address Register (DMA_CPAR5)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Peripheral Address
			volatile uint32_t PA;
		} BIT;
	}CPAR5;
	// DMA Channel 6 Peripheral Address Register (DMA_CPAR6)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Peripheral Address
			volatile uint32_t PA;
		} BIT;
	}CPAR6;
	// DMA Channel 7 Peripheral Address Register (DMA_CPAR7)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Peripheral Address
			volatile uint32_t PA;
		} BIT;
	}CPAR7;
	// DMA Channel 1 Memory Address Register (DMA_CMAR1)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Memory Address
			volatile uint32_t MA;
		} BIT;
	}CMAR1;
	// DMA Channel 2 Memory Address Register (DMA_CMAR2)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Memory Address
			volatile uint32_t MA;
		} BIT;
	}CMAR2;
	// DMA Channel 3 Memory Address Register (DMA_CMAR3)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Memory Address
			volatile uint32_t MA;
		} BIT;
	}CMAR3;
	// DMA Channel 4 Memory Address Register (DMA_CMAR4)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Memory Address
			volatile uint32_t MA;
		} BIT;
	}CMAR4;
	// DMA Channel 5 Memory Address Register (DMA_CMAR5)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Memory Address
			volatile uint32_t MA;
		} BIT;
	}CMAR5;
	// DMA Channel 6 Memory Address Register (DMA_CMAR6)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Memory Address
			volatile uint32_t MA;
		} BIT;
	}CMAR6;
	// DMA Channel 7 Memory Address Register (DMA_CMAR7)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Memory Address
			volatile uint32_t MA;
		} BIT;
	}CMAR7;

} DMA_REG_STRUCT;


#endif /* __DMA_REG_MAP_H__ */ 