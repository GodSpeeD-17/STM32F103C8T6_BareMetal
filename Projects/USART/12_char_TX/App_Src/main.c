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

// Lookup Table Index
uint8_t lookup_table_index = 0;
uint8_t star_index = STAR_LENGTH;

// Main Entry Point for User Code
int main(void){

	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);
	// SysTick Timer (1ms)
	config_SysTick(SYSTICK_DELAY_1_MS);

	// USART Configuration 
	load_USART_default(&usart_config);
	config_USART(&usart_config);
	enable_USART(&usart_config);

	// Configure OB LED
	config_OB_LED();

	// Infinite Loop
	while(1){

		// Reset OB LED
		reset_OB_LED();
		// Prints Start Sequence
		while(star_index--){
			// Print '*'
			USART_putc(&usart_config, '*');
			// Character Delay
			SysTick_delay_ms(STAR_DELAY_MS);
		}
		
		// Reset '*' index
		star_index = STAR_LENGTH;
		// Print Carriage Return Character (For starting on the first index on Command Prompt)
		USART_putc(&usart_config, '\r');
		// Print New Line Character (For starting on the new line)
		USART_putc(&usart_config, '\n');

		// Set OB LED
		set_OB_LED();
		// Prints characters stored in Lookup Table
		while(lookup_table_index < 26){
			// Prints the character
			USART_putc(&usart_config, lookup_table[lookup_table_index++]);
			// Character Delay
			SysTick_delay_ms(LOOKUP_TABLE_DELAY_MS);
		}

		// Reset lookup table index
		lookup_table_index = 0;
		// Print Carriage Return Character (For starting on the first index on Command Prompt)
		USART_putc(&usart_config, '\r');
		// Print New Line Character (For starting on the new line)
		USART_putc(&usart_config, '\n');

		// Loop Delay
		SysTick_delay_ms(LOOP_DELAY_MS);
	}
		
	// Return Value
	return 0;
}
