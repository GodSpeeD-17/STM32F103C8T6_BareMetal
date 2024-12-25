// Main Header
#include "main.h"

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

// Variable
int8_t count = -10;
float fcount = 10.1234f;
// String
const char* string = "This message is populated using printf()!\r";

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

		// Sep
		reset_OB_LED();
		DEFAULT_SEP(&usart_config);
		
		// Send String
		set_OB_LED();
		// fcount += 0.1f;	// TO DO: Fix this
		USART_printf(&usart_config, "%d: %s\r\n", count++, string);
		// USART_printf(&usart_config, "%d: %s -> %.5f\n", count++, string, fcount+= 0.1);

		// Loop Delay
		SysTick_delay_ms(LOOP_DELAY_MS);
	}
		
	// Return Value
	return 0;
}
