// Header Guards
#ifndef __SSD1306_IRQ_H__
#define __SSD1306_IRQ_H__

// Libraries
#include "bare_metal.h"
#include "ssd1306.h"

// MACROS
#define BUFFER_SIZE							((uint16_t) 2048)
#define SSD1306_I2Cx						(I2C1)
#define get_buff_len(X)						(sizeof((X))/sizeof((X)[0]))

/**
 * @brief Initializes the SSD1306 display using Interrupt Service Routine
 */
#define SSD1306_IRQ_Init() \
{	/* Update the Buffer */ \
	SSD1306_IRQ_updateBuff(SSD1306_initCmd, (sizeof(SSD1306_initCmd)/sizeof(SSD1306_initCmd[0])), 1); \
	/* I2C Send Address */ \
	I2C_sendStart(SSD1306_I2Cx);\
}

// Buffer (SSD1306)
static uint8_t SSD1306_buffer[BUFFER_SIZE] = {0};
// Index for Buffer (SSD1306)
static volatile uint16_t SSD1306_buff_curr_index = 0x00;
static volatile uint16_t SSD1306_buff_last_index = 0x00;

/**
 * @brief Initialize the SSD1306 Data Buffer
 * @param[in] buffer  The buffer to be copied
 * @param[in] buff_len Length of the Buffer to be copied
 * @param[in] isCMD		The data in the Buffer is (CMD = 1)/(DATA = 0)
 */
void SSD1306_IRQ_updateBuff(uint8_t *buff, uint8_t buff_len, uint8_t isCMD);

/**
 * @brief Clears the Screen
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] color Screen Color: Black(0)/White(1)
 */
void SSD1306_IRQ_clrScreen(I2C_REG_STRUCT* I2Cx, uint8_t color);

/**
 * @brief I2C1 Event Handler
 */
void I2C1_EV_IRQHandler(void);

#endif /* __SSD1306_IRQ_H__ */