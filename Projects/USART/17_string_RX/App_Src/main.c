// Main Header
#include "main.h"

// Echo Mode
#define ECHO_MODE

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

// Character & String Information
char received_character = '\0';
char received_string[RECEIVED_STRING_LENGTH] = {'\0'};
uint8_t string_index = 0;

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

	// Infinite Loop
	while(1){
		
		// Reset OB LED
		reset_OB_LED();
		// Separate Function 
		DEFAULT_SEP(&usart_config);
		// Display on Serial Console 
		USART_printf(&usart_config, "Entered String: ");

		// Blocks the loop until Enter is Pressed
		while((received_character != '\r') && (received_character != '\n')){
			// Receive New Character
			received_character = USART_receive(&usart_config);
			// Echo Mode
			#ifdef ECHO_MODE
				USART_echo(&usart_config, received_character);
			#endif
			// Add Character to String if within bounds
			*(received_string + (string_index++ & (RECEIVED_STRING_LENGTH - 1))) = received_character;
		}
		// Set OB LED
		set_OB_LED();

		// To remove appended '\r' and '\n'
		received_string[--string_index] = '\0';
		// For better display
		USART_putc(&usart_config, '\n');

		// Print it back to console
		if(string_index){
			// Print Data
			USART_printf(&usart_config, "Received String [%d]: \"%s\"\r\n", string_index + 1, received_string);
			// Flush Buffer & Character
			while(--string_index)
				*(received_string + string_index) = '\0';
			// Reset Index
			*received_string = received_character = '\0';
		}

		// Loop Delay
		SysTick_delay_ms(LOOP_DELAY_MS);
	}
		
	// Return Value
	return 0;
}

