// Header Guards
#ifndef __USART_REG_MAP_H__
#define __USART_REG_MAP_H__

#include <stdint.h>

// USART Structure
typedef struct {
    // Status Register (SR)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t PE: 1;
			volatile uint32_t FE: 1;
			volatile uint32_t NE: 1;
			volatile uint32_t ORE: 1;
			volatile uint32_t IDLE: 1;
			volatile uint32_t RXNE: 1;
			volatile uint32_t TC: 1;
			volatile uint32_t TXE: 1;
			volatile uint32_t LBD: 1;
			volatile uint32_t CTS: 1;
			volatile uint32_t reserved: 22;
		} BIT;
	} SR;

    // Data Register (DR)
    union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t DR: 9;
			volatile uint32_t reserved: 23;
		} BIT;
	} DR;
    
    // Baud Rate Register (BRR)
    union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t DIV_FRACTION: 4;
			volatile uint32_t DIV_MANTISSA: 12;
			volatile uint32_t reserved: 16;
		} BIT;
	} BRR;
    
    // Control Register 1 (CR1)
    union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t SBK: 1;
			volatile uint32_t RWU: 1;
			volatile uint32_t RE: 1;
			volatile uint32_t TE: 1;
			volatile uint32_t IDLEIE: 1;
			volatile uint32_t RXNIE: 1;
			volatile uint32_t TCIE: 1;
			volatile uint32_t TXEIE: 1;
			volatile uint32_t PEIE: 1;
			volatile uint32_t PS: 1;
			volatile uint32_t PCE: 1;
			volatile uint32_t WAKE: 1;
			volatile uint32_t M: 1;
			volatile uint32_t UE: 1;
			volatile uint32_t reserved: 18;
		} BIT;
	} CR1;

    // Control Register 2 (CR2)
    union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t ADD: 4;
			volatile uint32_t reserved_1: 1;
			volatile uint32_t LBDL: 1;
			volatile uint32_t LBDIE: 1;
			volatile uint32_t reserved_2: 1;
			volatile uint32_t LBCL: 1;
			volatile uint32_t CPHA: 1;
			volatile uint32_t CPOL: 1;
			volatile uint32_t CLKEN: 1;
			volatile uint32_t STOP: 2;
			volatile uint32_t LINEN: 2;
			volatile uint32_t reserved_3: 17;
		} BIT;
	} CR2;
    
    // Control Register 3 (CR3)
    union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t EIE: 1;
			volatile uint32_t IREN: 1;
			volatile uint32_t IRLP: 1;
			volatile uint32_t HDSEL: 1;
			volatile uint32_t NACK: 1;
			volatile uint32_t SCEN: 1;
			volatile uint32_t DMAR: 1;
			volatile uint32_t DMAT: 1;
			volatile uint32_t RTSE: 1;
			volatile uint32_t RTSE: 1;
			volatile uint32_t CTSE: 1;
			volatile uint32_t CTSIE: 1;
			volatile uint32_t reserved: 17;
		} BIT;
	} CR3;
    
    // Guard Time and Prescaler Register (GTPR)
    union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t PSC: 8;
			volatile uint32_t GT: 8;
			volatile uint32_t reserved: 16;
		} BIT;
	} CR3;

} USART_REG_STRUCT;

#endif /* __USART_REG_MAP_H__ */