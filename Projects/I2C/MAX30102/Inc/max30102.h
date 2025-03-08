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
#define MAX30102_REV_ID							((uint8_t) 0xFE)
// Part ID
#define MAX30102_PART_ID						((uint8_t) 0xFF)

#endif /* __MAX30102_H__ */ 