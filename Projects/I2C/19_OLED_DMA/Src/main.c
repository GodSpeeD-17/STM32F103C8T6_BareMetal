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

	// Clear Screen
	SSD1306_DMA_Clear_Screen();

	// Test
	SSD1306_DMA_Goto_XY(8, 49);
	SSD1306_DMA_Set_Pattern(0xFF);
	SSD1306_DMA_Goto_XY(9, 51);
	SSD1306_DMA_Set_Pattern(0xFF);
	SSD1306_DMA_Goto_XY(10, 53);
	SSD1306_DMA_Set_Pattern(0xFF);

	// Wait
	delay_ms(2 * LOOP_DELAY_MS);

	// Clear Screen
	SSD1306_DMA_Clear_Screen();
	
	uint8_t row = 0;

	// Infinite Loop
	while(1){
		/*
		// Test
		for(uint8_t page = 0; page < 8; page++){
			SSD1306_DMA_Goto_XY(page << 3, 63);
			SSD1306_DMA_Set_Pattern(SSD1306_PATTERN_ALTERNATE);
			delay_ms(100);
			}
			
			// LED Toggle
			GPIO_Toggle(&LED_Configuration);
			// Delay
			delay_ms(LOOP_DELAY_MS);
			
			// Test
			for(uint8_t page = 7; page >= 0; page--){
				SSD1306_DMA_Goto_XY(page << 3, 63);
				SSD1306_DMA_Set_Pattern(SSD1306_PATTERN_BLACK);
				delay_ms(100);
				}
				*/

		SSD1306_DMA_Set_Pixel(row, ((SSD1306_WIDTH/2) - 1));
		row = (row + 1) & (SSD1306_HEIGHT - 1); 
		// LED Toggle
		GPIO_Toggle(&LED_Configuration);
		// Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}

