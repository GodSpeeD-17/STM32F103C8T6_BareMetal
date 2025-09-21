/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
#include "usart.h"
/*-------------------------------------------------------------------------------*/
#define MY_USART							USART_1

/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	usart_config_t myUSARTConfig = {0};
	USART_Default_Config(&myUSARTConfig);
	USART_Config(MY_USART, &myUSARTConfig);
	USART_Enable(MY_USART);
	static uint16_t count = 0;
	char* const pStr = "Hello World";
	// Infinite Loop
	while(1){
		// Print on console
		USART_printf(MY_USART, "%s: %d\t0x%.4X\n", pStr, count, count);
		count++;
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/