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

	// Wait
	delay_ms(2 * LOOP_DELAY_MS);

	// Clear Screen
	SSD1306_DMA_Clear_Screen();


	uint8_t page = 0;

	// Infinite Loop
	while(1){

		// Incrementing
		for(page = 0; page < 8; page++){
			SSD1306_DMA_Goto_XY(page << 3, 63);
			SSD1306_DMA_Set_Col_Pattern(SSD1306_PATTERN_ALTERNATE);
			delay_ms(100);
		}

		// LED Toggle
		GPIO_Toggle(&LED_Configuration);
		// Delay
		delay_ms(LOOP_DELAY_MS);

		// Decrementing
		for(page = 7; page != 0xFF; page--){
			SSD1306_DMA_Goto_XY(page << 3, 63);
			SSD1306_DMA_Set_Col_Pattern(SSD1306_PATTERN_BLACK);
			delay_ms(100);
		}

		// LED Toggle
		GPIO_Toggle(&LED_Configuration);
		// Delay
		delay_ms(LOOP_DELAY_MS);
	}

	// Return Value
	return 0;
}

