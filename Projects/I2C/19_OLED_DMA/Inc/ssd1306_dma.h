// Header Guards
#ifndef __SSD1306_DMA_H__
#define __SSD1306_DMA_H__
/*-------------------------------------------------------------------------------*/
// Headers
#include "bare_metal.h"
#include "ssd1306_font.h"
/*-------------------------------------------------------------------------------*/
// Basic MACROS
#define BUFFER_SIZE							SSD1306_WIDTH
#define DMA_STATUS_RESET					0x00
#define DMA_STATUS_CMD						0x07
#define DMA_STATUS_DATA						0x70
#define DMA_STATUS_COMPLETED				0xFF
/*-------------------------------------------------------------------------------*/
// MACRO Function Definition
// Time required for Display to Synchronize with data or commands
// @note - Try to keep between 100-150 us
// @note - Going below 100us is insufficient time for display to synchronize
// @note - Going beyond 150us creates I2C Bus Error
#define SSD1306_I2C_SYNC_DELAY_TIME_US		124
/*-------------------------------------------------------------------------------*/
/**
 * @brief Used for Starting the transmission for I2C using DMA for SSD1306
 * @param[in] I2Cx I2C instance: `I2C1`, `I2C2`
 * @note Dependency on DMA 
 */
#define SSD1306_DMA_I2C_sendStart(I2Cx) 	\
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
#define SSD1306_DMA_I2C_sendStop(I2Cx) 				\
{	/* DMA Indicator for Transfer Complete */ 		\
	while(dma_status != DMA_STATUS_COMPLETED);		\
	/* Wait for SSD1306 to synchronize */ 			\
	delay_us(SSD1306_I2C_SYNC_DELAY_TIME_US); 		\
	/* Send Stop Condition */						\
	I2C_sendStop((I2Cx)); 							\
	/* DMA Reset Status for Completion */			\
	dma_status = DMA_STATUS_RESET;					\
}
/*-------------------------------------------------------------------------------*/
/**
 * @brief Takes care of whole I2C with DMA sequence
 * @note Dependency on DMA 
 */
#define SSD1306_DMA_Trigger()	                \
{	/* Start I2C DMA Transfer */		        \
	SSD1306_DMA_I2C_sendStart(SSD1306_I2Cx);	\
	/* Stop I2C DMA Transfer */			        \
	SSD1306_DMA_I2C_sendStop(SSD1306_I2Cx);	    \
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
/**
 * @brief Clear the Screen with Black Pattern
 */
#define SSD1306_DMA_Clear_Screen()				SSD1306_DMA_Color_Screen(SSD1306_PATTERN_BLACK)
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
__attribute__((aligned(4))) static uint8_t cmd_buffer[(BUFFER_SIZE >> 4)] = {
	[0 ... ((BUFFER_SIZE >> 4) - 1)] = 0x00
};
/*-------------------------------------------------------------------------------*/
// I2C Data Buffer
__attribute__((aligned(4))) static uint8_t data_buffer[(BUFFER_SIZE >> 4)][BUFFER_SIZE] = {
	[0 ... ((BUFFER_SIZE >> 4) - 1)][0 ... (BUFFER_SIZE - 1)] = 0x00
};
/*-------------------------------------------------------------------------------*/
// Postion Co-ordinates
static SSD1306_pix_t cursor = {
	.X = 0,
	.Y = 0
};
/*-------------------------------------------------------------------------------*/
/**
 * @brief SSD1306 Hardware for OLED regarding I2C & DMA Configuration
 */
void SSD1306_DMA_I2C_Init();

/**
 * @brief Updates the Buffer with Display Initialization Commands 
 */
void SSD1306_DMA_Disp_Init();

/**
 * @brief Get current X Co-ordinate 
 * @return Current X Co-ordinate 
 */
__INLINE__ uint8_t SSD1306_DMA_Get_Cursor_X(){
	return cursor.X;
}

/**
 * @brief Get current Y Co-ordinate 
 * @return Current Y Co-ordinate 
 */
__INLINE__ uint8_t SSD1306_DMA_Get_Cursor_Y(){
	return cursor.Y;
}

/**
 * @brief Loads the whole pattern for current Column
 * @param X X Co-ordinate: 0 - `SSD1306_HEIGHT`
 * @param Y Y Co-ordinate: 0 - `SSD1306_WIDTH`
 * @return Copy of Column Pattern
 * @note It will retrieve the pattern with respect to Page Start Boundary Address from the data buffer
 */
__INLINE__ uint8_t SSD1306_DMA_Load_Col_Pattern(uint8_t X, uint8_t Y) {
	//  Retrieve the Pattern
	return data_buffer[((X & (SSD1306_HEIGHT - 1)) >> 3)][(Y & (SSD1306_WIDTH - 1))];
}

/**
 * @brief Stores the whole pattern for current Column
 * @param X X Co-ordinate: 0 - `SSD1306_HEIGHT`
 * @param Y Y Co-ordinate: 0 - `SSD1306_WIDTH`
 * @note It will set the pattern with respect to Page Start Boundary Address in the data buffer
 */
__INLINE__ void SSD1306_DMA_Store_Col_Pattern(uint8_t X, uint8_t Y, uint8_t pattern) {
	// Sets the Pattern
	data_buffer[(X & (SSD1306_HEIGHT - 1)) >> 3][Y & (SSD1306_WIDTH - 1)] = pattern;
}
/*-------------------------------------------------------------------------------*/

/**
 * @brief Goes to mentioned Co-ordinates
 * @param X X Co-ordinate: 0 - `SSD1306_HEIGHT`
 * @param Y X Co-ordinate: 0 - `SSD1306_WIDTH`
 */
void SSD1306_DMA_Goto_XY(uint8_t X, uint8_t Y);

/**
 * @brief Set the pattern for current Column i.e cursor.Y
 * @param pattern Display Pattern for Column
 */
void SSD1306_DMA_Set_Col_Pattern(uint8_t pattern);

/**
 * @brief Sets a Particular Pixel on the Screen
 * @param[in] X X Co-ordinate: 0 - `SSD1306_HEIGHT`
 * @param[in] Y Y Co-ordinate: 0 - `SSD1306_WIDTH`
 */
void SSD1306_DMA_Set_Pixel(uint8_t X, uint8_t Y);

/**
 * @brief Fills the Columns in Page with pattern
 * @param page Page Number: 0 - 7
 * @param pattern Display Pattern for each Column within the Page
 */
void SSD1306_DMA_Page_Color(uint8_t page, uint8_t pattern);

/**
 * @brief Colors the SSD1306 Screen based on input pattern
 * @param[in] pattern Display Pattern for each Column
 */
void SSD1306_DMA_Color_Screen(uint8_t pattern);
/*-------------------------------------------------------------------------------*/

#endif /* __SSD1306_DMA_H__  */