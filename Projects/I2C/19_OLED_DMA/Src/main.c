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
	SSD1306_DMA_I2C_Init();
	// Delay for allowing SSD1306 to Boot Up
	delay_ms(LOOP_DELAY_MS);
	// DMA Display Initialization Commands
	SSD1306_DMA_Disp_Init();

	// Clear Screen
	SSD1306_DMA_Clear_Screen();

	// Wait
	delay_ms(2 * LOOP_DELAY_MS);

	// Clear Screen
	SSD1306_DMA_Clear_Screen();


	// Fill the Screen with Pattern
	for(uint8_t col = 63; col < 70; col++){
		SSD1306_DMA_Goto_XY(48, col);
		SSD1306_DMA_Set_Col_Pattern(SSD1306_PATTERN_ALTERNATE);
		delay_ms(100);
	}
	// Delay
	delay_ms(2 * LOOP_DELAY_MS);

	// /*
	// Fill the Screen with Pattern
	for(uint8_t col = 63; col < 70; col++){
		SSD1306_DMA_Set_Pixel(48, col);
		delay_ms(100);
	}
	delay_ms(2 * LOOP_DELAY_MS);
	// */

	// Infinite Loop
	while(1){
		// LED Toggle
		GPIO_Toggle(&LED_Configuration);
		// Delay
		delay_ms(LOOP_DELAY_MS);
	}

	// Return Value
	return 0;
}

