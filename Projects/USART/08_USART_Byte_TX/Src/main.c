/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
#include "usart.h"
/*-------------------------------------------------------------------------------*/
#define USART							USART_1
// Comment out to use 115200 Baud Rate
#define __BAUD_15200__
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	usart_config_t usart1_Config;
	USART_Default_Config(&usart1_Config);
	// Update Baud Rate to 115200
	#ifdef __BAUD_15200__
	usart1_Config.baud_rate = USART_BAUD_115200;
	#endif /* __BAUD_15200__ */
	USART_Config(USART, &usart1_Config);
	USART_Enable(USART);
	static uint8_t counter = 'A';
	// Infinite Loop
	while(1){
		// Check if TX Buffer Empty
		if(USART_TX_Ready(USART) != 0x00){
			USART_TX_Byte(USART, counter++);
			if(counter > 'Z'){
				counter = 'A';
			}
		}
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/