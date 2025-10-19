// Header Guards
#ifndef STM32F1XX_DMA_H_
#define STM32F1XX_DMA_H_

// C++ Safeguards
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// Includes
#include <stdint.h>

// DMA Channel Register Structure Configuration
typedef struct {
	// DMA Channel Configuration Register (DMA_CCR)
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
			volatile uint32_t NDT0: 1;
			volatile uint32_t NDT1: 1;
			volatile uint32_t NDT2: 1;
			volatile uint32_t NDT3: 1;
			volatile uint32_t NDT4: 1;
			volatile uint32_t NDT5: 1;
			volatile uint32_t NDT6: 1;
			volatile uint32_t NDT7: 1;
			volatile uint32_t NDT8: 1;
			volatile uint32_t NDT9: 1;
			volatile uint32_t NDT10: 1;
			volatile uint32_t NDT11: 1;
			volatile uint32_t NDT12: 1;
			volatile uint32_t NDT13: 1;
			volatile uint32_t NDT14: 1;
			volatile uint32_t NDT15: 1;
			// Reserved
			volatile uint32_t RESERVED: 16;
		} BIT;
	} CNDTR;
	// DMA Channel  Peripheral Address Register (DMA_CPAR)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Peripheral Address
			volatile uint32_t PA0: 1;
			volatile uint32_t PA1: 1;
			volatile uint32_t PA2: 1;
			volatile uint32_t PA3: 1;
			volatile uint32_t PA4: 1;
			volatile uint32_t PA5: 1;
			volatile uint32_t PA6: 1;
			volatile uint32_t PA7: 1;
			volatile uint32_t PA8: 1;
			volatile uint32_t PA9: 1;
			volatile uint32_t PA10: 1;
			volatile uint32_t PA11: 1;
			volatile uint32_t PA12: 1;
			volatile uint32_t PA13: 1;
			volatile uint32_t PA14: 1;
			volatile uint32_t PA15: 1;
			volatile uint32_t PA16: 1;
			volatile uint32_t PA17: 1;
			volatile uint32_t PA18: 1;
			volatile uint32_t PA19: 1;
			volatile uint32_t PA20: 1;
			volatile uint32_t PA21: 1;
			volatile uint32_t PA22: 1;
			volatile uint32_t PA23: 1;
			volatile uint32_t PA24: 1;
			volatile uint32_t PA25: 1;
			volatile uint32_t PA26: 1;
			volatile uint32_t PA27: 1;
			volatile uint32_t PA28: 1;
			volatile uint32_t PA29: 1;
			volatile uint32_t PA30: 1;
			volatile uint32_t PA31: 1;
		} BIT;
	} CPAR;
	// DMA Channel  Memory Address Register (DMA_CMAR)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			// Memory Address
			volatile uint32_t MA0: 1;
			volatile uint32_t MA1: 1;
			volatile uint32_t MA2: 1;
			volatile uint32_t MA3: 1;
			volatile uint32_t MA4: 1;
			volatile uint32_t MA5: 1;
			volatile uint32_t MA6: 1;
			volatile uint32_t MA7: 1;
			volatile uint32_t MA8: 1;
			volatile uint32_t MA9: 1;
			volatile uint32_t MA10: 1;
			volatile uint32_t MA11: 1;
			volatile uint32_t MA12: 1;
			volatile uint32_t MA13: 1;
			volatile uint32_t MA14: 1;
			volatile uint32_t MA15: 1;
			volatile uint32_t MA16: 1;
			volatile uint32_t MA17: 1;
			volatile uint32_t MA18: 1;
			volatile uint32_t MA19: 1;
			volatile uint32_t MA20: 1;
			volatile uint32_t MA21: 1;
			volatile uint32_t MA22: 1;
			volatile uint32_t MA23: 1;
			volatile uint32_t MA24: 1;
			volatile uint32_t MA25: 1;
			volatile uint32_t MA26: 1;
			volatile uint32_t MA27: 1;
			volatile uint32_t MA28: 1;
			volatile uint32_t MA29: 1;
			volatile uint32_t MA30: 1;
			volatile uint32_t MA31: 1;
		} BIT;
	} CMAR;
} DMA_Channel_TypeDef;

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
	// DMA channels (7 channels × 20 bytes each)
    DMA_Channel_TypeDef CHANNEL[7];
} DMA_TypeDef;

// C++ Safeguards
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_DMA_H_ */