// Header Guards
#ifndef __SSD1306_IRQ_H__
#define __SSD1306_IRQ_H__

// Libraries
#include "bare_metal.h"
#include "ssd1306.h"

// MACROS
#define BUFFER_SIZE							((uint8_t) 64)
#define SSD1306_I2Cx						(I2C1)

// Buffer (SSD1306)
static uint8_t SSD1306_buffer[BUFFER_SIZE] = {0};
// Index for Buffer (SSD1306)
static uint8_t SSD1306_buff_curr_index = 0x00;
static uint8_t SSD1306_buff_last_index = 0x00;

/**
 * @brief Initialize the SSD1306 Data Buffer
 * @param[in] buffer  The buffer to be copied
 * @param[in] buff_len Length of the Buffer to be copied
 * @param[in] isCMD	The data in the Buffer is CMD/DATA
 */
void SSD1306_updateBuff(uint8_t *buff, uint8_t buff_len, uint8_t isCMD);

/**
 * @brief I2C1 Event Handler
 */
void I2C1_EV_IRQHandler(void);

#endif /* __SSD1306_IRQ_H__ */