/**
 * @file ssd1306_disp.h
 * @author Shrey Shah
 * @brief Display related configurations for SSD1306 OLED Display
 * @version 1.0
 * @date 16-08-2025
 * 
 * THEORY:
 * ----- 128 Columns x 8 Pages ------
 * -|---|--------|-----|-------|------|
 * -| 0 |   1    |  2  | ..... | 128  |
 * -|---|--------|-----|-------|------|
 * -| 0 |  MSB   |     | ..... | <|>  |
 * -| 1 |  BIT6  |     | ..... |  |   |
 * -| 2 |  BIT5  |     | ..... |  C   |
 * -| 3 |  BIT4  |     | ..... |  E   |
 * -| 4 |  BIT3  |     | ..... |  L   |
 * -| 5 |  BIT2  |     | ..... |  L   |
 * -| 6 |  BIT1  |     | ..... |  |   |
 * -| 7 |  LSB   |     | ..... | <|>  |
 * -|---|--------|-----|-------|------|
 */
// Header Guards
#ifndef __SSD1306_DISP_H__
#define __SSD1306_DISP_H__

// ------------------------------------------------------------- INCLUDES START ------------------------------------------------------------- //
#include "ssd1306_config.h"
// ------------------------------------------------------------- INCLUDES END ------------------------------------------------------------- //

// ------------------------------------------------------------- DISPLAY HELPER FUNCTION START ------------------------------------------------------------- //
/**
 * @brief Retrieves the Page from the SSD1306 Configuration Structure
 * @param ssd1306 Pointer to the SSD1306 Configuration Structure
 * @return Current Page of the SSD1306 Display
 */
__STATIC_INLINE__ uint8_t SSD1306_Disp_Get_Page(ssd1306_config_t* ssd1306){
	return (ssd1306->display.page);
}

/**
 * @brief Retrieves the Column from the SSD1306 Configuration Structure
 * @param ssd1306 Pointer to the SSD1306 Configuration Structure
 * @return Current Column of the SSD1306 Display
 */
__STATIC_INLINE__ uint8_t SSD1306_Disp_Get_Column(ssd1306_config_t* ssd1306){
	return (ssd1306->display.col);
}

/**
 * @brief Sets the cell from the SSD1306 OLED Display Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param cell Vertical pixel byte present at the current page and column
 */
__STATIC_INLINE__ void SSD1306_Disp_Set_Cell(ssd1306_config_t* ssd1306, const uint8_t cell){
	ssd1306->display.buffer[ssd1306->display.page][ssd1306->display.col] = cell;
}

/**
 * @brief Retrieves the cell from the SSD1306 OLED Display Buffer
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 */
__STATIC_INLINE__ uint8_t SSD1306_Disp_Get_Cell(ssd1306_config_t* ssd1306){
	return (ssd1306->display.buffer[ssd1306->display.page][ssd1306->display.col]);
}
// ------------------------------------------------------------- DISPLAY HELPER FUNCTION END ------------------------------------------------------------- //


#endif /* __SSD1306_DISP_H__ */