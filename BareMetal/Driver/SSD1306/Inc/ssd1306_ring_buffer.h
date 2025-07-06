// Header Guards
#ifndef __SSD1306_NEW_H__
#define __SSD1306_NEW_H__

// Includes
#include "ssd1306_reg_map.h"
#include "i2c_ring_buffer.h"

// SSD1306 Structure Definition
typedef struct {
	// I2C Configuration Structure 
	i2c_config_t i2c_config;
	// SSD1306 I2C Address: 
	// - 0x3C (Default)
	// - 0x3D
	uint8_t address;
	// I2C Ring Buffer
	ring_buffer_t i2c_rb;
	// 128 * 64 = 1024-byte display buffer
	uint8_t* display;
	// Cursor position
	SSD1306_pix_t cursor;
} ssd1306_config_t;

/**
 * @brief Initializes the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 */
void SSD1306_Ring_Buffer_Init(ssd1306_config_t* ssd1306);


#endif /* __SSD1306_NEW_H__ */