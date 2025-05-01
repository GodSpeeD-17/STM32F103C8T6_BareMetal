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
	SSD1306_Clear_Screen();

	SSD1306_DMA_Goto_XY(8, 100);
	// SSD1306_DMA_Set_Pattern(0xFF);

	// Test
	// for(uint8_t page = 0; page < 8; page++){
	// 	SSD1306_DMA_Goto_XY(page, 63);
	// 	SSD1306_DMA_Set_Pattern(SSD1306_PATTERN_ALTERNATE);
	// 	delay_ms(100);
	// }

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

