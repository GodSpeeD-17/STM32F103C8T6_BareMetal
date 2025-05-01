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

