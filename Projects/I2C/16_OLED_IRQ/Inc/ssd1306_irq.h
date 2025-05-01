/* ------------------------------------------------------------------------------------ */
// Header Guards
#ifndef __SSD1306_IRQ_H__
#define __SSD1306_IRQ_H__
/* ------------------------------------------------------------------------------------ */
// Libraries
#include <string.h>		// memset
#include "systick.h" 	// delay
#include "i2c.h"
#include "ssd1306_font.h"
/* ------------------------------------------------------------------------------------ */
// MACROS
#define BUFFER_SIZE							((uint16_t) 512)
/* ------------------------------------------------------------------------------------ */
/**
 * @brief Initiates the I2C communication with the SSD1306 display
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
#define SSD1306_IRQ_I2C_Start(I2Cx)			\
{											\
	/* Wait until Bus is Ready*/			\
	while((I2Cx)->SR2.REG & I2C_SR2_BUSY);	\
	/* Send Start Condition */				\
	I2C_sendStart((I2Cx));					\
}
/* ------------------------------------------------------------------------------------ */
/**
 * @brief Initializes the SSD1306 display using Interrupt Service Routine
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
#define SSD1306_IRQ_Init(I2Cx)												\
{																			\
	/* Only Update after the data from Buffer is transmitted */ 			\
	while((SSD1306_I2C_status != I2C_STATE_READY));							\
	/* Update the Buffer */ 												\
	SSD1306_IRQ_updateBuff(SSD1306_initCmd, SIZEOF(SSD1306_initCmd), 1);							\
	/* I2C Start */ 														\
	SSD1306_IRQ_I2C_Start((I2Cx));											\
}
/* ------------------------------------------------------------------------------------ */
// Buffer (SSD1306)
static uint8_t SSD1306_I2C_buffer[BUFFER_SIZE] = {0};
/* ------------------------------------------------------------------------------------ */
// Index for Buffer (SSD1306)
static volatile uint16_t SSD1306_buff_curr_index = 0x00;
static volatile uint16_t SSD1306_buff_last_index = 0x00;
static volatile uint32_t temp_data = 0x00;
/* ------------------------------------------------------------------------------------ */
// I2C State
typedef enum {
    I2C_STATE_READY = 0,
    I2C_STATE_ADDR_SENT,
    I2C_STATE_ADDR_CLEARED,
    I2C_STATE_SENDING
} i2c_state_t;

// I2C Transmission Status
static volatile uint8_t SSD1306_I2C_status = I2C_STATE_READY;
/* ------------------------------------------------------------------------------------ */
/**
 * @brief Initialize the SSD1306 I2C Buffer
 * @param[in] buffer  The Buffer to be copied
 * @param[in] buff_len Length of the Buffer to be copied
 * @param[in] isCMD Buffer contains Command(1)/Data(0)
 * @note Takes care of waiting until end of previous transmission
 */
void SSD1306_IRQ_updateBuff(uint8_t *buff, uint16_t buff_len, uint8_t isCMD);
/* ------------------------------------------------------------------------------------ */
/**
 * @brief Clears the Screen
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param[in] color Screen Color: Black(0)/White(1)
 */
void SSD1306_IRQ_clrScreen(I2C_REG_STRUCT* I2Cx, uint8_t color);
/* ------------------------------------------------------------------------------------ */
/**
 * @brief I2C1 Event Handler
 */
// static void I2C1_EV_IRQHandler(void);
/* ------------------------------------------------------------------------------------ */
/**
 * @brief Error Protection
 */
// void I2C1_ER_IRQHandler(void);
/* ------------------------------------------------------------------------------------ */
#endif /* __SSD1306_IRQ_H__ */
/* ------------------------------------------------------------------------------------ */