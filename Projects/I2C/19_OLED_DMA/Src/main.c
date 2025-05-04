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

