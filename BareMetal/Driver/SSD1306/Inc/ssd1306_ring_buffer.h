// Header Guards
#ifndef __SSD1306_RING_BUFFER_H__
#define __SSD1306_RING_BUFFER_H__

// Includes
#include "ssd1306_reg_map.h"
#include "i2c_ring_buffer.h"

// SSD1306 Structure Definition
typedef struct {
	// I2C Configuration Structure
	i2c_config_t i2c_config;
	// SSD1306 I2C Address: 
	// - `0x3C` (Default)
	// - `0x3D`
	uint8_t address;
	// I2C Ring Buffer
	ring_buffer_t i2c_rb;
	// 2D Array of 128x64 pixels for display
	// - Each pixel is represented by 1 byte
	// - Total 1024 bytes for the entire display
	// - Each byte represents 8 vertical pixels
	uint8_t* display;
	// Cursor position
	SSD1306_pix_t cursor;
} ssd1306_config_t;

/**
 * @brief Configures the address for Display Buffer used to track SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param buffer Pointer to the display buffer
 * @note - The display buffer must be 2D array
 * @note - The buffer will have `SSD1306_PAGE` rows
 * @note - The buffer will have `SSD1306_WIDTH` columns
 */
__STATIC_INLINE__ void SSD1306_RB_Config_Disp_Buff(ssd1306_config_t* ssd1306, uint8_t* buffer){
	// Set the Display Buffer
	ssd1306->display = buffer;
}

/**
 * @brief Configures the I2C Ring Buffer for the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param i2c_buffer Pointer to the I2C buffer
 * @param i2c_buff_size Pointer to I2C buffer size 
 * @note - The I2C buffer size must be a power of 2
 * @note - If not, it will be rounded up to the next power of 2
 * @note - The updated Buffer Size will be used for the ring buffer
 */
__STATIC_INLINE__ void SSD1306_RB_Config(ssd1306_config_t* ssd1306, uint8_t* i2c_buffer, uint16_t i2c_buff_size){
	// Configure the I2C Ring Buffer
	Ring_Buffer_Config(&ssd1306->i2c_rb, i2c_buffer, i2c_buff_size);
}

/**
 * @brief Configures the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @note This function assumes the following:
 * @note - `I2C1` is used for communication
 * @note - `0x3C` is the I2C address of the display
 */
void SSD1306_RB_Load_Default(ssd1306_config_t* ssd1306);

/**
 * @brief Initializes the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 */
void SSD1306_RB_Disp_Init(ssd1306_config_t* ssd1306);


#endif /* __SSD1306_RING_BUFFER_H__ */