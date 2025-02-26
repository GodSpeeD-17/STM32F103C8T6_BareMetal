// Sensor Library
#ifndef __MAX30102_H__
#define __MAX30102_H__

// Libraries
#include <stdint.h>

// Register Definitions
#define MAX30102_ADDRESS						((uint8_t) 0x57)

// Interrupt Status Register 1
#define MAX30102_SR_1							((uint8_t) 0x00)  
// Interrupt Status Register 2
#define MAX30102_SR_2							((uint8_t) 0x01)  
// Interrupt Enable Register 1
#define MAX30102_ER_1							((uint8_t) 0x02)  
// Interrupt Enable Register 2
#define MAX30102_ER_2							((uint8_t) 0x03)

// FIFO Write Pointer
#define MAX30102_FIFO_WR_PTR					((uint8_t) 0x04)  
// FIFO Overflow Counter
#define MAX30102_FIFO_OVF_CNT					((uint8_t) 0x05)  
// FIFO Read Pointer
#define MAX30102_FIFO_RD_PTR					((uint8_t) 0x06)  
// FIFO Data
#define MAX30102_FIFO_DATA						((uint8_t) 0x07)

// FIFO Configuration Register
#define MAX30102_FIFO_CNF						((uint8_t) 0x08)  
// Mode Configuration Register
#define MAX30102_MODE_CNF						((uint8_t) 0x09)  
// SpO2 Configuration Register
#define MAX30102_SpO2_CNF						((uint8_t) 0x0A)  

// LED1 Pulse Amplitude
#define MAX30102_LED1_PA						((uint8_t) 0x0B)  
// LED2 Pulse Amplitude
#define MAX30102_LED2_PA						((uint8_t) 0x0C)  

// Multi-LED Mode Control Slot 1 and 2
#define MAX30102_LED_CTRL_SLOT1_2				((uint8_t) 0x11)  
// Multi-LED Mode Control Slot 3 and 4
#define MAX30102_LED_CTRL_SLOT3_4				((uint8_t) 0x12) 

// Temperature Integer Section
#define MAX30102_TEMP_INT						((uint8_t) 0x1F)  
// Temperature Fractional Section
#define MAX30102_TEMP_FRACT						((uint8_t) 0x20)
// Temperature Configuration
#define MAX30102_TEMP_CONFIG					((uint8_t) 0x21) 

// Revision ID
#define REV_ID									((uint8_t) 0xFE)
// Part ID
#define PART_ID									((uint8_t) 0xFF)

/*
// MAX30102 Register Mapping Structure
typedef struct {
	// Interrupt Section
	struct {
		// Interrupt Status Register 1
		uint8_t SR_1;
		// Interrupt Status Register 2
		uint8_t SR_2;
		// Interrupt Enable Register 1
		uint8_t ER_1;
		// Interrupt Enable Register 2
		uint8_t ER_2;
	} IRQ;
	// FIFO Section
	struct {
		// FIFO Write Pointer 
		uint8_t W_PTR;
		// FIFO Overflow Counter
		uint8_t OVF_CNT;
		// FIFO Read Pointer 
		uint8_t R_PTR;
		// FIFO Data
		uint8_t DATA;
	} FIFO;
	// Configuration Section
	struct {
		// FIFO Configuration Register
		uint8_t FIFO;
		// Mode Configuration Register
		uint8_t MODE;
		// SpO2 Configuration Register
		uint8_t SpO2;
	} CONFIG;
	// Pulse Amplitude Section
	struct {
		// LED1 Pulse Amplitude
		uint8_t LED1;
		// LED2 Pulse Amplitude
		uint8_t LED2;
	} PULSE_AMP;
	// Reserved Section
	uint8_t RESERVED1[2];
	// Multi-LED Mode Control Section
	struct {
		// Multi-LED Mode Control Registers
		uint8_t SLOT1_2;
		uint8_t SLOT3_4;
	} MODE_CTRL;
	// Reserved
	uint8_t RESERVED2[12];
	// Temperature Section
	struct {
		// Temperature Integer Section
		uint8_t INT;
		// Temperature Fractional Section
		uint8_t FRACT;
		// Temperature Configuration
		uint8_t CONFIG;
	} TEMP;
} MAX30102_REG;
*/

#endif /* __MAX30102_H__ */ 