// Header Guards
#ifndef __SSD1306_REG_MAP_H__
#define __SSD1306_REG_MAP_H__

/* ------------------------------------------------------------------------------------ */
// Library
#include <stdint.h>
/* ------------------------------------------------------------------------------------ */
// SSD1306 I2C Address
#ifndef SA0
	#define SSD1306_I2C_ADDRESS					((uint8_t) 0x3C)
#else
	#define SSD1306_I2C_ADDRESS					((uint8_t) 0x3D)
#endif
/* ------------------------------------------------------------------------------------ */
// SSD1306 Characteristics
#define SSD1306_HEIGHT							64
#define SSD1306_WIDTH							128
/* ------------------------------------------------------------------------------------ */
// Indicator regarding the sent bytes
#define SSD1306_CMD_INDICATOR					0x00
#define SSD1306_DATA_INDICATOR					0x40
/* ------------------------------------------------------------------------------------ */
// I2C Instance
#define SSD1306_I2Cx							I2C1
/* ------------------------------------------------------------------------------------ */
// Size of Buffer
#define SIZEOF(X)								(sizeof((X))/sizeof((X)[0]))
/* ------------------------------------------------------------------------------------ */
// SSD1306 Color Patterns
// Black
#define SSD1306_PATTERN_BLACK					0x00
// White
#define SSD1306_PATTERN_WHITE					0xFF
// Alternate
#define SSD1306_PATTERN_ALTERNATE				0xAA
// Top 2 Rows
#define SSD1306_PATTERN_TOP						0x03
// Bottom 2 Rows
#define SSD1306_PATTERN_BOTTOM					0xC0

/* ------------------------------------------------------------------------------------ */
// <! --- Command Table --- !> //
// Double byte command to select 1 out of 256 contrast steps
#define SSD1306_CMD_SET_CONTRAST                0x81
// Resume to RAM content display, Output follows RAM content
#define SSD1306_CMD_ENTIRE_DISP_ON_OUT_RAM      0xA4
// Entire display ON, Output ignores RAM content
#define SSD1306_CMD_ENTIRE_DISP_ON              0xA5
// Normal display
#define SSD1306_CMD_DISP_NORMAL                 0xA6
// Inverse display
#define SSD1306_CMD_DISP_INVERSE                0xA7
// Display OFF
#define SSD1306_CMD_DISP_OFF                    0xAE
// Display ON
#define SSD1306_CMD_DISP_ON                     0xAF
// Set display clock divide ratio/oscillator frequency
#define SSD1306_CMD_SET_DISPLAY_CLOCK_DIV       0xD5
// Set multiplex ratio (1/64 duty)
#define SSD1306_CMD_SET_MULTIPLEX               0xA8
// Set display offset
#define SSD1306_CMD_SET_DISPLAY_OFFSET          0xD3
// Set display start line
#define SSD1306_CMD_SET_START_LINE              0x40
// Enable charge pump
#define SSD1306_CMD_CHARGE_PUMP                 0x8D
// Set memory addressing mode
#define SSD1306_CMD_MEM_ADDR_MODE               0x20
// Set segment re-map (column address 127 is mapped to SEG0)
#define SSD1306_CMD_SET_SEGMENT_REMAP           0xA1
// Set COM output scan direction (remapped mode, scan from COM[N-1] to COM0)
#define SSD1306_CMD_SET_COM_SCAN_DIR            0xC8
// Set COM pins hardware configuration
#define SSD1306_CMD_SET_COM_PINS                0xDA
// Set contrast control
#define SSD1306_CMD_SET_CONTRAST                0x81
// Set pre-charge period
#define SSD1306_CMD_SET_PRECHARGE               0xD9
// Set VCOMH deselect level
#define SSD1306_CMD_SET_VCOMH_DESELECT          0xDB
// Resume to RAM content display
#define SSD1306_CMD_RESUME_TO_RAM_CONTENT       0xA4
// Set normal display (non-inverted)
#define SSD1306_CMD_SET_NORMAL_DISPLAY          0xA6
// Display ON
#define SSD1306_CMD_DISPLAY_ON                  0xAF
// Set Column Address (`Only for Horizontal or vertical Addressing Mode`)
#define SSD1306_CMD_SET_COL_ADDR				0x21
// Set Page Address (`Only for Horizontal or vertical Addressing Mode`)
#define SSD1306_CMD_SET_PAGE_ADDR				0x22
/* ------------------------------------------------------------------------------------ */
// Set Page Address (`Only for Page Addressing Mode`)
#define SSD1306_CMD_PAGE_MODE_SET_PAGE(VALUE)	(0xB0 + ((VALUE) & 0x07))
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_0		0xB0
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_1		0xB1
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_2		0xB2
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_3		0xB3
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_4		0xB4
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_5		0xB5
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_6		0xB6
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_7		0xB7
/* ------------------------------------------------------------------------------------ */
// Set Column Lower Nibble Address (`Only for Page Addressing Mode`)
#define SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE(VALUE)		(0x00 + ((VALUE) & 0x0F))
// Set Column Upper Nibble Address (`Only for Page Addressing Mode`)
#define SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE(VALUE)		(0x10 + ((VALUE) & 0x0F))
/* ------------------------------------------------------------------------------------ */
/**
 * @brief Set Page Address
 * @param[in] CURSOR_X 0 - (`SSD1306_HEIGHT` - 1)
 * @note Only for `Page Addressing` Mode
 */
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_X(CURSOR_X)				(0xB0 + ((CURSOR_X >> 3) & 0x07))

/**
 * @brief Set Column Lower Nibble Address
 * @param[in] CURSOR_Y 0 - (`SSD1306_WIDTH` - 1)
 * @note Only for `Page Addressing` Mode
 */
#define SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE_Y(CURSOR_Y)	(0x00 + ((CURSOR_Y) & 0x0F))

/**
 * @brief Set Column Upper Nibble Address
 * @param[in] CURSOR_Y 0 - (`SSD1306_WIDTH` - 1)
 * @note Only for `Page Addressing` Mode
 */
#define SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE_Y(CURSOR_Y)	(0x10 + (((CURSOR_Y) & 0xF0) >> 4))
/* ------------------------------------------------------------------------------------ */
// Memory Addressing Mode Options
#define SSD1306_MEM_ADDR_MODE_H					0x00
#define SSD1306_MEM_ADDR_MODE_V					0x01
#define SSD1306_MEM_ADDR_MODE_PAGE				0x02
/* ------------------------------------------------------------------------------------ */
// Pixel Co-ordinates Structure
typedef struct {
	// X co-ordinate
	uint8_t X;
	// Y co-ordinate
	uint8_t Y;
} SSD1306_pix_t;
/* ------------------------------------------------------------------------------------ */
// Initialization sequence for SSD1306
static const uint8_t SSD1306_initCmd[] = {
	SSD1306_CMD_DISP_OFF,									// Display OFF
	SSD1306_CMD_SET_DISPLAY_CLOCK_DIV, 0x80,				// Set display clock divide ratio/oscillator frequency
	SSD1306_CMD_SET_MULTIPLEX, 0x3F,						// Set multiplex ratio (1/64 duty)
	SSD1306_CMD_SET_DISPLAY_OFFSET, 0x00,					// Set display offset
	SSD1306_CMD_SET_START_LINE,								// Set display start line
	SSD1306_CMD_CHARGE_PUMP, 0x14,							// Enable charge pump
	SSD1306_CMD_MEM_ADDR_MODE, SSD1306_MEM_ADDR_MODE_PAGE,	// Set memory addressing mode to Page Addressing Mode (0x02)
	SSD1306_CMD_SET_SEGMENT_REMAP,							// Set segment re-map (column address 127 is mapped to SEG0)
	SSD1306_CMD_SET_COM_SCAN_DIR,							// Set COM output scan direction (remapped mode, scan from COM[N-1] to COM0)
	SSD1306_CMD_SET_COM_PINS, 0x12,							// Set COM pins hardware configuration
	SSD1306_CMD_SET_CONTRAST, 0xCF,							// Set contrast control
	SSD1306_CMD_SET_PRECHARGE, 0x22,						// Set pre-charge period
	SSD1306_CMD_SET_VCOMH_DESELECT, 0x20,					// Set VCOMH deselect level
	SSD1306_CMD_RESUME_TO_RAM_CONTENT,						// Resume to RAM content display
	SSD1306_CMD_SET_NORMAL_DISPLAY,							// Set normal display (non-inverted)
	SSD1306_CMD_DISPLAY_ON									// Display ON
};
/* ------------------------------------------------------------------------------------ */


#endif  /* __SSD1306_REG_MAP_H__ */