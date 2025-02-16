// Header Guards
#ifndef __I2C_REG_MAP_H__
#define __I2C_REG_MAP_H__

// Dependency
#include "common.h"

// I2C Main Structure
typedef struct {
	// Control Register 1 (CR1)
	union {
		uint32_t REG;
		struct {
			// Peripheral enable
			volatile uint32_t PE: 1;
			// SMBus mode
			volatile uint32_t SMBUS: 1;
			volatile uint32_t RESERVED_1: 1;
			volatile uint32_t SMBTYPE: 1;
			// ARP enable
			volatile uint32_t ENARP: 1;
			// PEC enable
			volatile uint32_t ENPEC: 1;
			// General call enable
			volatile uint32_t ENGC: 1;
			// Clock stretching disable (Slave mode)
			volatile uint32_t NOSTRETCH: 1;
			// Start generation
			volatile uint32_t START: 1;
			// Stop generation
			volatile uint32_t STOP: 1;
			// Acknowledge enable
			volatile uint32_t ACK: 1;
			// Acknowledge/PEC Position (for data reception)
			volatile uint32_t POS: 1;
			volatile uint32_t PEC: 1;
			volatile uint32_t ALERT: 1;
			volatile uint32_t RESERVED_2: 1;
			// Software reset
			volatile uint32_t SWRST: 1;
			volatile uint32_t RESERVED_3: 16;
		} BIT;
	} CR1;
	// Control Register 2 (CR2)
	union {
		uint32_t REG;
		struct {
			// Peripheral clock frequency
			volatile uint32_t FREQ: 6;
			volatile uint32_t RESERVED_1: 2;
			// Error interrupt enable
			volatile uint32_t ITERREN: 1;
			// Event interrupt enable
			volatile uint32_t ITEVTEN: 1;
			// Buffer interrupt enable
			volatile uint32_t ITBUFEN: 1;
			// DMA requests enable
			volatile uint32_t DMAEN: 1;
			// DMA last transfer
			volatile uint32_t LAST: 1;
			volatile uint32_t RESERVED_2: 19;
		} BIT;
	} CR2;
	// Own Address Register 1 (OAR1)
	union {
		uint32_t REG;
		struct {
			volatile uint32_t ADD0: 1;
			volatile uint32_t ADD1_7: 7;
			volatile uint32_t ADD8_9: 2;
			volatile uint32_t RESERVED_1: 5;
			volatile uint32_t ADDMODE: 1;
			volatile uint32_t RESERVED_2: 16;
		} BIT;
	} OAR1;
	// Own Address Register 2 (OAR2)
	union {
		uint32_t REG;
		struct {
			volatile uint32_t ENDUAL: 1;
			volatile uint32_t ADD2_1_7: 7;
			volatile uint32_t RESERVED: 24;
		} BIT;
	} OAR2;
	// Data Register (DR)
	union {
		uint32_t REG;
		struct {
			volatile uint32_t DR: 8;
			volatile uint32_t RESERVED: 24;
		} BIT;
	} DR;
	// Status Register 1 (SR1)
	union {
		uint32_t REG;
		struct {
			// Start bit (Master mode)
			volatile uint32_t SB: 1;
			// Address sent (master mode)/matched (slave mode)
			volatile uint32_t ADDR: 1;
			// Byte transfer finished
			volatile uint32_t BTF: 1;
			// 10-bit header sent (Master mode)
			volatile uint32_t ADD10: 1;
			// Stop detection (slave mode)
			volatile uint32_t STOPF: 1;
			volatile uint32_t RESERVED_1: 1;
			// Data register not empty (receivers)
			volatile uint32_t RxNE: 1;
			// Data register empty (transmitters)
			volatile uint32_t TxE: 1;
			// Bus error
			volatile uint32_t BERR: 1;
			// Arbitration lost (master mode)
			volatile uint32_t ARLO: 1;
			// Acknowledge failure
			volatile uint32_t AF: 1;
			// Overrun/Underrun
			volatile uint32_t OVR: 1;
			volatile uint32_t PECERR: 1;
			volatile uint32_t RESERVED_2: 1;
			// Timeout or Tlow error
			volatile uint32_t TIMEOUT: 1;
			volatile uint32_t SMBALERT: 1;
			volatile uint32_t RESERVED_3: 16;
		} BIT;
	} SR1;
	// Status Register 2 (SR2)
	union {
		uint32_t REG;
		struct {
			volatile uint32_t MSL: 1;
			volatile uint32_t BUSY: 1;
			// Transmitter/receiver
			volatile uint32_t TRA: 1;
			volatile uint32_t RESERVED_1: 1;
			volatile uint32_t GENCALL: 1;
			volatile uint32_t SMBDEFAULT: 1;
			volatile uint32_t SMBHOST: 1;
			volatile uint32_t DUALF: 1;
			volatile uint32_t PEC: 8;
			volatile uint32_t RESERVED_2: 16;
		} BIT;
	} SR2;
	// Clock Control Register (CCR)
	union {
		uint32_t REG;
		struct {
			volatile uint32_t CCR: 12;
			volatile uint32_t RESERVED_1: 2;
			// Fm mode duty cycle
			volatile uint32_t DUTY: 1;
			// I2C master mode selection
			volatile uint32_t F_S: 1;
			volatile uint32_t RESERVED_2: 16;
		} BIT;
	} CCR;
	// TRISE Register (TRISE)
	union {
		uint32_t REG;
		struct {
			// Maximum rise time in Fm/Sm mode (Master mode)
			volatile uint32_t TRISE: 6;
			volatile uint32_t RESERVED_1: 26;
		} BIT;
	} TRISE;
} I2C_REG_STRUCT;

#endif /* __I2C_REG_MAP_H__ */ 