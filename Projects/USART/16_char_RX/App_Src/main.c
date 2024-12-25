// Main Header
#include "main.h"

// USART Configuration Structure
gpio_config_t usart_tx_config = {
	.GPIOx = USART_PORT,
	.PINx = USART_TX_PIN,
};
gpio_config_t usart_rx_config = {
	.GPIOx = USART_PORT,
	.PINx = USART_RX_PIN,
};
usart_config_t usart_config = {
	.TX_GPIO_CONFIGx = &usart_tx_config,
	.RX_GPIO_CONFIGx = &usart_rx_config,
	.USARTx = USART,
};

// PWM Configuration Structure
gpio_config_t led_config = {
	.GPIOx = LED_PORT,
	.PINx = LED_PIN,
	.MODEx = MODE_OUT_10MHz,
	.CNFx = CNF_OUT_GP_PP,
};

// Lookup Table Index
char received_character = '\0';

// Main Entry Point for User Code
int main(void){

	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);
	// SysTick Timer (1ms)
	config_SysTick(SYSTICK_DELAY_1_MS);

	// LED Configuration
	config_GPIO(&led_config);

	// USART Configuration 
	load_USART_default(&usart_config);
	config_USART(&usart_config);
	enable_USART(&usart_config);

	// On-board LED Configuration
	config_OB_LED();
	reset_OB_LED();

	// Infinite Loop
	while(1){
		// Blocks the loop until character is received
		received_character = USART_receive(&usart_config);
		// Prints Start Sequence
		DEFAULT_SEP(&usart_config);
		// Print it back to console
		USART_printf(&usart_config, "Received char: \'%c\' [%d]\r\n", received_character, received_character);
		// Set OB LED
		toggle_OB_LED();
		// Action based upon received LED
		take_action(received_character);
		// Loop Delay
		SysTick_delay_ms(LOOP_DELAY_MS);
	}
		
	// Return Value
	return 0;
}
