// Header Guards
#ifndef __SSD1306_DMA_H__
#define __SSD1306_DMA_H__
/*-------------------------------------------------------------------------------*/
// Headers
#include "bare_metal.h"
#include "ssd1306_font.h"
/*-------------------------------------------------------------------------------*/
// MACROS
#define BUFFER_SIZE							SSD1306_WIDTH
#define DMA_STATUS_RESET					0x00
#define DMA_STATUS_CMD						0x07
#define DMA_STATUS_DATA						0x70
#define DMA_STATUS_COMPLETED				0xFF
/*-------------------------------------------------------------------------------*/
/**
 * @brief Used for Starting the transmission for I2C using DMA for SSD1306
 * @param[in] I2Cx I2C instance: `I2C1`, `I2C2`
 * @note Dependency on DMA 
 */
#define SSD1306_I2C_DMA_sendStart(I2Cx) 	\
{	/* Wait for Bus to be free */ 			\
	while(!I2C_busReady((I2Cx))); 			\
	/* Send Start Condition */				\
	I2C_sendStart((I2Cx)); 					\
}
/*-------------------------------------------------------------------------------*/
/**
 * @brief Used for Stoping the transmission for I2C using DMA for SSD1306
 * @param[in] I2Cx I2C instance: `I2C1`, `I2C2`
 * @note Dependency on DMA
 */
#define SSD1306_I2C_DMA_sendStop(I2Cx) 				\
{	/* DMA Indicator for Transfer Complete */ 		\
	while(dma_status != DMA_STATUS_COMPLETED);	\
	/* Wait for SSD1306 to synchronize */ 			\
	delay_us(SSD1306_I2C_SYNC_DELAY_TIME_US); 		\
	/* Send Stop Condition */						\
	I2C_sendStop((I2Cx)); 							\
	/* DMA Reset Status for Completion */			\
	dma_status = DMA_STATUS_RESET;				\
}
/*-------------------------------------------------------------------------------*/
/**
 * @brief Takes care of whole I2C with DMA sequence
 * @note Dependency on DMA 
 */
#define SSD1306_DMA_Trigger()	                \
{	/* Start I2C DMA Transfer */		        \
	SSD1306_I2C_DMA_sendStart(SSD1306_I2Cx);	\
	/* Stop I2C DMA Transfer */			        \
	SSD1306_I2C_DMA_sendStop(SSD1306_I2Cx);	    \
}
/*-------------------------------------------------------------------------------*/
/**
 * @brief Takes care of whole I2C with DMA sequence for transfering Command Buffer
 */
#define SSD1306_DMA_CMD_Trigger()\
{	/* Set DMA Status to Transfer Command Buffer */	\
	dma_status = DMA_STATUS_CMD;					\
	/* Trigger the DMA */							\
	SSD1306_DMA_Trigger();							\
}
/*-------------------------------------------------------------------------------*/
/**
 * @brief Takes care of whole I2C with DMA sequence for transfering Data Buffer
 */
#define SSD1306_DMA_Data_Trigger()\
{	/* Set DMA Status to Transfer Command Buffer */	\
	dma_status = DMA_STATUS_DATA;					\
	/* Trigger the DMA */							\
	SSD1306_DMA_Trigger();							\
}
/*-------------------------------------------------------------------------------*/
// MACRO Function Definition
// Time required for Display to Synchronize with data or commands
// @note - Try to keep between 100-150 us
// @note - Going below 100us is insufficient time for display to synchronize
// @note - Going beyond 150us creates I2C Bus Error
#define SSD1306_I2C_SYNC_DELAY_TIME_US			124
/*-------------------------------------------------------------------------------*/
// DMA Configuration
static dma_config_t DMA_SSD1306_Configuration;
// I2C Configuration Structure
static i2c_config_t I2C_SSD1306_Configuration;
/*-------------------------------------------------------------------------------*/
// I2C Status
static volatile uint8_t i2c_status = 0x00;
// DMA Status
static volatile uint8_t dma_status = DMA_STATUS_RESET;
/*-------------------------------------------------------------------------------*/
// I2C Command Buffer
__attribute__((aligned(4))) static uint8_t cmd_buffer[(BUFFER_SIZE >> 2)] = {[0 ... ((BUFFER_SIZE >> 2) - 1)] = SSD1306_CMD_INDICATOR};
// I2C Data Buffer
__attribute__((aligned(4))) static uint8_t data_buffer[BUFFER_SIZE] = {[0 ... (BUFFER_SIZE - 1)] = SSD1306_DATA_INDICATOR};
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
/**
 * @brief SSD1306 OLED I2C & DMA Configuration
 */
void SSD1306_I2C_DMA_Init();
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
/**
 * @brief Updates the Buffer with Display Initialization Commands 
 */
void SSD1306_DMA_Disp_Init();
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
/**
 * @brief Fills the Columns in Page with pattern
 * @param page Page Number: 0 - 7
 * @param pattern Display Pattern for each Column within the Page
 */
void SSD1306_DMA_Page_Color(uint8_t page, uint8_t pattern);
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
/**
 * @brief Colors the SSD1306 Screen based on input pattern
 * @param[in] pattern Display Pattern for each Column
 */
void SSD1306_DMA_Color_Screen(uint8_t pattern);
/*-------------------------------------------------------------------------------*/

#endif /* __SSD1306_DMA_H__  */