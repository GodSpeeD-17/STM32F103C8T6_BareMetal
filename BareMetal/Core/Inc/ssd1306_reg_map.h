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
#define SSD1306_HEIGHT							(64)
#define SSD1306_WIDTH							(128)
#define SSD1306_PAGE							(SSD1306_HEIGHT >> 3)
#define SSD1306_PIXELS							(SSD1306_PAGE * SSD1306_WIDTH)
/* ------------------------------------------------------------------------------------ */
// Indicator regarding the sent bytes
#define SSD1306_CMD_INDICATOR					(0x00)
#define SSD1306_DATA_INDICATOR					(0x40)
/* ------------------------------------------------------------------------------------ */
// I2C Instance
#define SSD1306_I2Cx							(I2C1)
/* ------------------------------------------------------------------------------------ */
// Size of Buffer
#define SIZEOF(X)								(sizeof((X))/sizeof((X)[0]))
/* ------------------------------------------------------------------------------------ */
// SSD1306 Color Patterns
// Black
#define SSD1306_PATTERN_BLACK					(0x00)
// White
#define SSD1306_PATTERN_WHITE					(0xFF)
// Alternate
#define SSD1306_PATTERN_ALTERNATE				(0xAA)
// Top 2 Rows
#define SSD1306_PATTERN_TOP						(0x03)
// Bottom 2 Rows
#define SSD1306_PATTERN_BOTTOM					(0xC0)

/* ------------------------------------------------------------------------------------ */
// <! --- Command Table --- !> //
// Double byte command to select 1 out of 256 contrast steps
#define SSD1306_CMD_SET_CONTRAST                (0x81)
// Resume to RAM content display, Output follows RAM content
#define SSD1306_CMD_ENTIRE_DISP_ON_OUT_RAM      (0xA4)
// Entire display ON, Output ignores RAM content
#define SSD1306_CMD_ENTIRE_DISP_ON              (0xA5)
// Normal display
#define SSD1306_CMD_DISP_NORMAL                 (0xA6)
// Inverse display
#define SSD1306_CMD_DISP_INVERSE                (0xA7)
// Display OFF
#define SSD1306_CMD_DISP_OFF                    (0xAE)
// Display ON
#define SSD1306_CMD_DISP_ON                     (0xAF)
// Set display clock divide ratio/oscillator frequency
#define SSD1306_CMD_SET_DISPLAY_CLOCK_DIV       (0xD5)
// Set multiplex ratio (1/64 duty)
#define SSD1306_CMD_SET_MULTIPLEX               (0xA8)
// Set display offset
#define SSD1306_CMD_SET_DISPLAY_OFFSET          (0xD3)
// Set display start line
#define SSD1306_CMD_SET_START_LINE              (0x40)
// Enable charge pump
#define SSD1306_CMD_CHARGE_PUMP                 (0x8D)
// Set memory addressing mode
#define SSD1306_CMD_MEM_ADDR_MODE               (0x20)
// Set segment re-map (column address 127 is mapped to SEG0)
#define SSD1306_CMD_SET_SEGMENT_REMAP           (0xA1)
// Set COM output scan direction (remapped mode, scan from COM[N-1] to COM0)
#define SSD1306_CMD_SET_COM_SCAN_DIR            (0xC8)
// Set COM pins hardware configuration
#define SSD1306_CMD_SET_COM_PINS                (0xDA)
// Set contrast control
#define SSD1306_CMD_SET_CONTRAST                (0x81)
// Set pre-charge period
#define SSD1306_CMD_SET_PRECHARGE               (0xD9)
// Set VCOMH deselect level
#define SSD1306_CMD_SET_VCOMH_DESELECT          (0xDB)
// Resume to RAM content display
#define SSD1306_CMD_RESUME_TO_RAM_CONTENT       (0xA4)
// Set normal display (non-inverted)
#define SSD1306_CMD_SET_NORMAL_DISPLAY          (0xA6)
// Display ON
#define SSD1306_CMD_DISPLAY_ON                  (0xAF)
// Set Column Address (`Only for Horizontal or vertical Addressing Mode`)
#define SSD1306_CMD_SET_COL_ADDR				(0x21)
// Set Page Address (`Only for Horizontal or vertical Addressing Mode`)
#define SSD1306_CMD_SET_PAGE_ADDR				(0x22)
/* ------------------------------------------------------------------------------------ */
// Set Page Address (`Only for Page Addressing Mode`)
#define SSD1306_CMD_PAGE_MODE_SET_PAGE(VALUE)	(0xB0 + ((VALUE) & 0x07))
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_0		(0xB0)
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_1		(0xB1)
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_2		(0xB2)
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_3		(0xB3)
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_4		(0xB4)
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_5		(0xB5)
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_6		(0xB6)
#define SSD1306_CMD_PAGE_MODE_SET_PAGE_7		(0xB7)
/* ------------------------------------------------------------------------------------ */
// Set Column Lower Nibble Address (`Only for Page Addressing Mode`)
#define SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE(VALUE)		(0x00 + ((VALUE) & 0x0F))
// Set Column Upper Nibble Address (`Only for Page Addressing Mode`)
#define SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE(VALUE)		(0x10 + ((VALUE) & 0x0F))
/* ------------------------------------------------------------------------------------ */
#define SSD1306_INIT_CMD_SIZE					(SIZEOF(SSD1306_initCmd))
/* ------------------------------------------------------------------------------------ */
/**
 * @brief Set Page Address
 * @param CURSOR_Y 0 - (`SSD1306_HEIGHT` - 1)
 * @note Only for `Page Addressing` Mode
 */
#define SSD1306_CMD_PAGE_MODE_SET_Y(CURSOR_Y)					(SSD1306_CMD_PAGE_MODE_SET_PAGE(0) + (((CURSOR_Y) >> 3) & 0x07))

/**
 * @brief Set Column Lower Nibble Address
 * @param CURSOR_X 0 - (`SSD1306_WIDTH` - 1)
 * @note Only for `Page Addressing` Mode
 */
#define SSD1306_CMD_PAGE_MODE_SET_X_LOWER_NIBBLE(CURSOR_X)		(SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE(0) + ((CURSOR_X) & 0x0F))

/**
 * @brief Set Column Upper Nibble Address
 * @param CURSOR_X 0 - (`SSD1306_WIDTH` - 1)
 * @note Only for `Page Addressing` Mode
 */
#define SSD1306_CMD_PAGE_MODE_SET_X_UPPER_NIBBLE(CURSOR_X)		(SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE(0) + (((CURSOR_X) >> 4) & 0x0F))
/* ------------------------------------------------------------------------------------ */
// Memory Addressing Mode Options
#define SSD1306_MEM_ADDR_MODE_H					(0x00)
#define SSD1306_MEM_ADDR_MODE_V					(0x01)
#define SSD1306_MEM_ADDR_MODE_PAGE				(0x02)
/* ------------------------------------------------------------------------------------ */
// Pixel Co-ordinates Structure
typedef struct {
	// X co-ordinate
	uint8_t X;
	// Y co-ordinate
	uint8_t Y;
} SSD1306_pix_t;
/* ------------------------------------------------------------------------------------ */
// Initialization sequence for SSD1306 OLED Display
static const uint8_t SSD1306_initCmd[] = {
	
	/******************************************************************
	 * Turn Display OFF
	 * ---------------------------------------------------------------
	 * Disables display output while we configure internal registers.
	 ******************************************************************/
	SSD1306_CMD_DISP_OFF,

	/******************************************************************
	 * Set Display Clock Divide Ratio / Oscillator Frequency
	 * ---------------------------------------------------------------
	 * - First byte (0xD5): Command for setting the display clock.
	 * - Second byte (0x80): Suggested default; 
	 *     - [7:4] = Oscillator Frequency
	 *     - [3:0] = Clock Divide Ratio
	 ******************************************************************/
	SSD1306_CMD_SET_DISPLAY_CLOCK_DIV, 0x80,

	/******************************************************************
	 * Set Multiplex Ratio
	 * ---------------------------------------------------------------
	 * - First byte (0xA8): Command for setting MUX.
	 * - Second byte (0x3F): 1/64 duty cycle (MUX = 63)
	 *   => 64 COM lines used (for 64-pixel height)
	 ******************************************************************/
	SSD1306_CMD_SET_MULTIPLEX, 0x3F,

	/******************************************************************
	 * Set Display Offset
	 * ---------------------------------------------------------------
	 * - First byte (0xD3): Command for vertical shift
	 * - Second byte (0x00): No shift → Start at COM0
	 ******************************************************************/
	SSD1306_CMD_SET_DISPLAY_OFFSET, 0x00,

	/******************************************************************
	 * Set Display Start Line
	 * ---------------------------------------------------------------
	 * - 0x40 sets the RAM row that maps to COM0.
	 * - 0x40 means display starts from line 0 (default)
	 ******************************************************************/
	SSD1306_CMD_SET_START_LINE,

	/******************************************************************
	 * Enable Charge Pump Regulator
	 * ---------------------------------------------------------------
	 * - First byte (0x8D): Charge Pump Command
	 * - Second byte (0x14): Enable internal voltage booster
	 *   Required for 3.3V operation to generate ~7.5V Vpp
	 ******************************************************************/
	SSD1306_CMD_CHARGE_PUMP, 0x14,

	/******************************************************************
	 * Set Memory Addressing Mode
	 * ---------------------------------------------------------------
	 * - First byte (0x20): Command for memory mode
	 * - Second byte (0x02): Page Addressing Mode
	 *   Allows writing by page (rows of 8-pixel high strips)
	 ******************************************************************/
	SSD1306_CMD_MEM_ADDR_MODE, SSD1306_MEM_ADDR_MODE_PAGE,

	/******************************************************************
	 * Set Segment Re-map
	 * ---------------------------------------------------------------
	 * - 0xA1 flips the horizontal orientation (mirror X)
	 * - Column address 127 → SEG0
	 ******************************************************************/
	SSD1306_CMD_SET_SEGMENT_REMAP,

	/******************************************************************
	 * Set COM Output Scan Direction
	 * ---------------------------------------------------------------
	 * - 0xC8 flips vertical scan order (mirror Y)
	 * - Scan COM[N-1] to COM0
	 ******************************************************************/
	SSD1306_CMD_SET_COM_SCAN_DIR,

	/******************************************************************
	 * Set COM Pins Hardware Configuration
	 * ---------------------------------------------------------------
	 * - First byte (0xDA): Command
	 * - Second byte (0x12): Typical value for 128x64 OLED
	 *   Bit4 = Alternative COM pin config
	 *   Bit5 = Disable COM left/right remap
	 ******************************************************************/
	SSD1306_CMD_SET_COM_PINS, 0x12,

	/******************************************************************
	 * Set Contrast Control
	 * ---------------------------------------------------------------
	 * - First byte (0x81): Contrast command
	 * - Second byte (0xCF): Contrast level (0x00 to 0xFF)
	 *   0xCF = ~80% brightness
	 ******************************************************************/
	SSD1306_CMD_SET_CONTRAST, 0xCF,

	/******************************************************************
	 * Set Pre-charge Period
	 * ---------------------------------------------------------------
	 * - First byte (0xD9): Pre-charge command
	 * - Second byte (0x22): Phase1 = 2 DCLKs, Phase2 = 2 DCLKs
	 *   Helps with OLED pixel driving efficiency
	 ******************************************************************/
	SSD1306_CMD_SET_PRECHARGE, 0x22,

	/******************************************************************
	 * Set VCOMH Deselect Level
	 * ---------------------------------------------------------------
	 * - First byte (0xDB): Command
	 * - Second byte (0x20): ~0.77 x Vcc
	 *   Sets voltage when pixel is "off"
	 ******************************************************************/
	SSD1306_CMD_SET_VCOMH_DESELECT, 0x20,

	/******************************************************************
	 * Resume to RAM Content Display
	 * ---------------------------------------------------------------
	 * - 0xA4 tells SSD1306 to use GDDRAM content for output
	 * - Opposite of "Entire Display ON" (0xA5)
	 ******************************************************************/
	SSD1306_CMD_RESUME_TO_RAM_CONTENT,

	/******************************************************************
	 * Set Normal Display
	 * ---------------------------------------------------------------
	 * - 0xA6: Non-inverted display
	 *   (0 = Black, 1 = White)
	 ******************************************************************/
	SSD1306_CMD_SET_NORMAL_DISPLAY,

	/******************************************************************
	 * Display ON
	 * ---------------------------------------------------------------
	 * - 0xAF: Enables internal display circuitry to output to screen
	 ******************************************************************/
	SSD1306_CMD_DISPLAY_ON
};
/* ------------------------------------------------------------------------------------ */
#endif  /* __SSD1306_REG_MAP_H__ */