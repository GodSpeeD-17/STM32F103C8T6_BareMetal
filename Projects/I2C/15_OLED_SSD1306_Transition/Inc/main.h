// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

/*-------------------------------------------------------------------------------*/
// Headers
#include "bare_metal.h"
#include "ssd1306.h"
/*-------------------------------------------------------------------------------*/
// __YAMI__
/*-------------------------------------------------------------------------------*/
// MACROS
#define LOOP_DELAY_MS						((uint32_t) 1000)
#define RECT_WIDTH							((uint8_t) 5)
#define RECT_HEIGHT							((uint8_t) 5)
/*-------------------------------------------------------------------------------*/
/**
 * @brief Demo Function for displaying loading screen animation
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
void SSD1306_loadScrAnim(I2C_REG_STRUCT* I2Cx);
/*-------------------------------------------------------------------------------*/
// Image Bitmap
static const uint8_t image_yami[1024] 
= {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 
	0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x8F, 0x83, 0xC0, 0xE0, 0xFC, 0xFA, 0xFF, 0xFF, 0xFF, 0xF7, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xF9, 0xE7, 0xDB, 0xF3, 0xE7, 0xDF, 0xFE, 0xFD, 0x80, 0x04, 0x98, 0x38, 0x30, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0x1F, 0xFF, 0xFF, 0xE7, 0x8E, 0x1E, 0x7C, 0xF1, 0xC7, 0x3F, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 
	0x8E, 0x86, 0xC6, 0xC3, 0xE3, 0xE9, 0xE1, 0xF4, 0xF6, 0xFA, 0xFF, 0x7F, 0x7F, 0x7F, 0xFF, 0xFF, 
	0xE4, 0xBF, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xBF, 
	0xFF, 0xDF, 0xEF, 0x77, 0xBB, 0xFD, 0xFB, 0xFF, 0xFF, 0xFF, 0x1F, 0x3F, 0x7F, 0xF7, 0xCF, 0xCF, 
	0x4F, 0x4F, 0xBF, 0xFF, 0xFF, 0xE7, 0x7F, 0x3F, 0x1F, 0x0F, 0x83, 0xC0, 0xE0, 0x60, 0x20, 0x20, 
	0x00, 0x00, 0x00, 0x00, 0xFF, 0xF1, 0xFF, 0xFF, 0xFE, 0xC0, 0x03, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 
	0xF7, 0xF7, 0xF7, 0xF3, 0xFB, 0xFB, 0xFB, 0xFD, 0xFF, 0x3F, 0x03, 0xC0, 0xE0, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xF8, 0xE0, 0xEF, 0xEB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xDF, 0xEF, 0x77, 0x1B, 0x0F, 0x37, 0x01, 0xFE, 0xFF, 0x00, 0x1E, 0x07, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0x01, 0x00, 0x00, 0x80, 0xF0, 0x81, 0x08, 0x40, 0x01, 0x0F, 0x0F, 0x02, 0x02, 0x00, 
	0xC0, 0x7C, 0xFC, 0xE0, 0x81, 0x3F, 0xFF, 0xFF, 0xFF, 0x81, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 
	0xFF, 0xFF, 0x7F, 0xBF, 0xBF, 0xDF, 0xCF, 0xE7, 0xF1, 0x78, 0x1E, 0xCF, 0xFF, 0xFF, 0xFF, 0x03, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCF, 0x7F, 0xFF, 0x03, 
	0x03, 0xF1, 0x00, 0x38, 0x78, 0xF0, 0xE0, 0xE0, 0xEE, 0x80, 0x00, 0x40, 0x60, 0x70, 0x60, 0x70, 
	0x70, 0x70, 0x60, 0x60, 0x60, 0x63, 0xC3, 0x01, 0x80, 0x90, 0x80, 0x60, 0x1C, 0x82, 0xE0, 0xFC, 
	0xFF, 0xFC, 0xF0, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 
	0x7F, 0x7F, 0xBF, 0x9F, 0xCF, 0xE7, 0x67, 0x33, 0xB8, 0xDC, 0xEF, 0xFF, 0xFF, 0x3F, 0x3F, 0x80, 
	0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF9, 0xF7, 0xEF, 0xDF, 0xBF, 0xFF, 0xF8, 
	0xE3, 0xC1, 0xC0, 0x00, 0x00, 0x01, 0x01, 0x1F, 0x1F, 0x01, 0x01, 0xE7, 0xE3, 0x1B, 0x73, 0xF3, 
	0xE7, 0xE7, 0xE6, 0xCC, 0x48, 0x40, 0x25, 0x11, 0x80, 0xE3, 0xF0, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 
	0x7F, 0x37, 0x37, 0x1B, 0x19, 0x1C, 0x8E, 0xE6, 0xF3, 0xFF, 0x1F, 0x07, 0x01, 0x00, 0x00, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 
	0xEF, 0xFF, 0xBF, 0x7F, 0xFE, 0xFC, 0xF8, 0xFB, 0xF3, 0xF8, 0xF4, 0xFD, 0xF9, 0x8C, 0xBC, 0xFC, 
	0xCF, 0x63, 0x91, 0x3E, 0x00, 0xC0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 
	0xF8, 0xFC, 0xFC, 0x3C, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0xC0, 0xFE, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF9, 0xF7, 0xB2, 
	0xBD, 0xFF, 0xFF, 0xFC, 0xF0, 0xED, 0xED, 0xE7, 0xE3, 0xF3, 0xF3, 0xFF, 0xFF, 0x1F, 0x0F, 0x07, 
	0x83, 0x7B, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x01, 0x00, 0xC6, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xFF, 
	0xFF, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xFF, 0x1F, 0x03, 0x00, 0x80, 0xE0, 0xFC, 
	0xF0, 0xF8, 0xF0, 0xE0, 0xC1, 0x03, 0x03, 0x07, 0x0F, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 
};

static const uint8_t image_gojo[1024] 
= {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xCF, 0xE7, 
	0x63, 0xB1, 0x90, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x31, 0x73, 0xF3, 0xF7, 0xF7, 0xF7, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0xBF, 0x9F, 0x9F, 0x8F, 0x8F, 0xC7, 0xC7, 
	0x63, 0x21, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x40, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x08, 0x11, 0x33, 0x33, 0x77, 0xF7, 0xF7, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF9, 0xFC, 
	0xFE, 0xFF, 0x07, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 
	0x60, 0x18, 0x04, 0x01, 0x00, 0x40, 0x30, 0xBC, 0x3F, 0x00, 0x78, 0xFF, 0xE0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x38, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xC1, 0x87, 0x0F, 0x1E, 0x7E, 0xFE, 0xFE, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xE7, 0xF3, 
	0xF1, 0xF8, 0xFC, 0xFE, 0xFF, 0xFE, 0xFC, 0xFE, 0xE0, 0xF0, 0xF0, 0xF8, 0x3C, 0x0E, 0x07, 0x01, 
	0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x07, 0x02, 0x00, 0x06, 
	0x00, 0x00, 0x00, 0x80, 0xC0, 0x00, 0x00, 0xE0, 0xE0, 0xFF, 0xFE, 0xE0, 0x87, 0xFF, 0xFE, 0xF8, 
	0xE0, 0x0E, 0x78, 0xC0, 0x00, 0x00, 0x78, 0xE0, 0x80, 0x00, 0x00, 0x0F, 0xF8, 0x80, 0x00, 0x00, 
	0x80, 0x00, 0xC0, 0xE0, 0x02, 0xFC, 0xF8, 0xF3, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 0xFD, 0xFB, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x03, 0x3B, 0xFF, 0xFF, 0xFF, 0xFF, 0x78, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xF0, 0xFD, 0xFF, 0x7E, 0x78, 0x3F, 0x1F, 0x0F, 0x03, 0x01, 0x01, 0x00, 0x00, 0x01, 
	0x01, 0x03, 0x0E, 0x1F, 0x00, 0xFE, 0xFC, 0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xFF, 0xFF, 0xE0, 0xFF, 
	0xFF, 0xF8, 0xFF, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF9, 0xF1, 0xF8, 0xFE, 0xF8, 0xE0, 0x80, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0xC0, 0xF0, 0xFC, 0xFE, 0xFF, 0xFF, 0x7F, 0x7F, 0xBF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x82, 0xC2, 0xC2, 0xC6, 
	0xC6, 0xC6, 0xC6, 0xC4, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 
};


static const uint8_t image_family[1024]
= {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0x7F, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x1F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x1F, 0x1F, 0x1F, 0x3F, 0x3F, 
	0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x3F, 
	0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0xFF, 0xBF, 0x7F, 0x7F, 0x0F, 0x03, 0x83, 0x83, 0x83, 0x03, 0xC3, 
	0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x41, 
	0x20, 0xE0, 0xE0, 0xE0, 0xC0, 0x00, 0x20, 0xF0, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 
	0x20, 0x20, 0x20, 0x21, 0x20, 0x20, 0x00, 0x10, 0x30, 0x30, 0x30, 0x10, 0x10, 0x30, 0x30, 0x10, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x19, 0x19, 0x19, 0x18, 0x00, 0x01, 0x03, 0x03, 0x00, 0x11, 
	0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCF, 0xC7, 0xC5, 0x0B, 0x07, 0x07, 0x03, 0x73, 0x73, 0x00, 
	0x00, 0x00, 0x01, 0xC1, 0x00, 0x00, 0x20, 0x7F, 0x7F, 0x7F, 0xFF, 0xFC, 0xF8, 0xF8, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xC4, 0xF4, 0xF8, 
	0xF8, 0x7C, 0x7C, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x86, 0x06, 0x06, 
	0xC6, 0xC6, 0x06, 0x07, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10, 0xF0, 0xFC, 0xBC, 0xF0, 
	0xE3, 0xC7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFF, 0xFE, 0xFE, 
	0xFE, 0xFF, 0xFE, 0xFC, 0xFC, 0xF8, 0xF0, 0xD0, 0x1B, 0x7B, 0x7F, 0x7F, 0x3F, 0x3F, 0x1F, 0x3F, 
	0x3F, 0x7F, 0x7F, 0x79, 0xF9, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x1D, 0x0C, 0x00, 0x1D, 0xCC, 0xF3, 0x0F, 0x07, 
	0x00, 0x3C, 0xFC, 0xFF, 0x1F, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x5F, 0x03, 0x01, 0x0C, 
	0x01, 0x89, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xFC, 0xFE, 0xFE, 0xFE, 0x86, 
	0xEE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x3F, 0x1F, 0x0F, 0x07, 0x07, 0x03, 0x1F, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x0C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xFB, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 
	0xF8, 0xF8, 0xFF, 0xF7, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 
	0xF2, 0xF6, 0xE2, 0xF8, 0xFF, 0xFF, 0xFF, 0xF8, 0xFF, 0x7F, 0xFF, 0x3F, 0x3B, 0xBF, 0x3F, 0x3B, 
	0x9F, 0xFF, 0xBF, 0x9F, 0xFD, 0xFD, 0xDF, 0x87, 0x07, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x80, 0xC0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7D, 0x74, 0x50, 0x73, 0x13, 0xF2, 
	0xFF, 0x3F, 0x03, 0x78, 0x7F, 0x7F, 0xFB, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x07, 0x07, 0x1F, 0x1F, 0x1F, 0x9F, 0xFF, 0xFF, 0x3F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 
};
/*-------------------------------------------------------------------------------*/

#endif /* __MAIN_H__ */ 