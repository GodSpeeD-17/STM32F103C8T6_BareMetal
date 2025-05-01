/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"



/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){

	// Configure GPIO
	GPIO_Config(&LED_Configuration);
	GPIO_Reset(&LED_Configuration);

	// Hardware Configuration
	SSD1306_I2C_DMA_Init();

	// Delay for allowing SSD1306 to Boot Up
	delay_ms(LOOP_DELAY_MS);

	// DMA Display Initialization Commands
	SSD1306_DMA_Disp_Init();
	
	// Pattern
	SSD1306_DMA_Color_Screen(0xFF);
	// Toggle On-board LED
	OB_LED_Toggle();

	#ifdef OLD
	src_buffer[0] = SSD1306_CMD_INDICATOR;
	src_buffer[1] = SSD1306_CMD_PAGE_MODE_SET_PAGE(0);
	src_buffer[2] = SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE(0);
	src_buffer[3] = SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE(0);
	DMA_Transfer_Config(DMA_I2C1_TX, src_buffer + 1, &SSD1306_I2Cx->DR.REG, 3);
	
	// -----------------------------------------------------------------
	// SSD1306 I2C Range Selection Start
	// -----------------------------------------------------------------
		// SSD1306 I2C DMA Sequence
		SSD1306_I2C_DMA_trigger(SSD1306_I2Cx);
		// Toggle On-board LED
		OB_LED_Toggle();
	// -----------------------------------------------------------------
	// SSD1306 I2C Range Selection End
	// -----------------------------------------------------------------

	src_buffer[0] = SSD1306_DATA_INDICATOR;
	memset(src_buffer + 1, 0xFF, BUFFER_SIZE);
	DMA_Transfer_Config(DMA_I2C1_TX, src_buffer + 1, &SSD1306_I2Cx->DR.REG, BUFFER_SIZE);
	
	// -----------------------------------------------------------------
	// SSD1306 I2C Column Data Start
	// -----------------------------------------------------------------
		// SSD1306 I2C DMA Sequence
		SSD1306_I2C_DMA_trigger(SSD1306_I2Cx);
		// Toggle On-board LED
		OB_LED_Toggle();
	// -----------------------------------------------------------------
	// SSD1306 I2C Column Data End
	// -----------------------------------------------------------------	
	#endif

	// Infinite Loop
	while(1){
		// Toggle GPIO
		GPIO_Toggle(&LED_Configuration);
		// Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}

