// Main Header
#include "main.h"

// Character Lookup Table
extern const char lookup_table[26];

// GPIO Configuration Structure
gpio_config_t usart_tx_config = {
	.GPIOx = USART_PORT,
	.PINx = USART_TX_PIN,
};
gpio_config_t usart_rx_config = {
	.GPIOx = USART_PORT,
	.PINx = USART_RX_PIN,
};
// USART Configuration Structure
usart_config_t usart_config = {
	.TX_GPIO_CONFIGx = &usart_tx_config,
	.RX_GPIO_CONFIGx = &usart_rx_config,
	.USARTx = USART,
};

// Main Entry Point for User Code
int main(void){

    // Local Variable
	uint8_t i = 0;

	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);
	// SysTick Timer (1ms)
	config_SysTick(SYSTICK_DELAY_1_MS);

	// USART Configuration 
	load_USART_default(&usart_config);
	config_USART(&usart_config);

	// Infinite Loop
	while(1){

		// Prints 'A'/'Z'
		while((i % 26) < 26){
			// Prints the character
			USART_putc(&usart_config, lookup_table[i++]);
			// Character Delay
			SysTick_delay_ms(DELAY_MS);
		}

		// Print New Line Character
		USART_putc(&usart_config, '\n');

		// Loop Delay
		SysTick_delay_ms(LOOP_DELAY_MS);
	}
		
	// Return Value
	return 0;
}
