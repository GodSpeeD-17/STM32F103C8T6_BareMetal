// Main Header
#include "main.h"

// USART Configuration
gpio_config_t gpio_usart_tx = {
	.GPIOx = USART_TX_GPIO,
	.PINx = USART_TX_PIN,
};
gpio_config_t gpio_usart_rx = {
	.GPIOx = USART_RX_GPIO,
	.PINx = USART_RX_PIN,
};
usart_config_t usart_config = {
	.TX_GPIO_CONFIGx = &gpio_usart_tx,
	.RX_GPIO_CONFIGx = &gpio_usart_rx,
	.USARTx = USART,
};

// Main Entry Point for User Code
int main(void){
	
	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);
	// SysTick Timer (1ms)
	config_SysTick(SYSTICK_DELAY_1_MS);

	// Load USART Configuration
	load_USART_default(&usart_config);
	// Enable RX Not Empty (RXNE) IRQ
	usart_config.RXNEIE = USARTx_RXNEIE_ENABLE;
	config_USART(&usart_config);
	enable_USART(&usart_config);

	// Infinite Loop
	while(1){

		// Deduction != Append
		if(buffer_head != buffer_tail){
			// Default Separation
			DEFAULT_SEP(&usart_config);
			// Read Data from Buffer
			USART_printf(&usart_config, "buffer[%d]: %c [%d]\r\n", buffer_tail, buffer[buffer_tail], buffer[buffer_tail++]);
			// Circular Buffer
			buffer_tail = (buffer_tail == BUFFER_SIZE)? 0 : buffer_tail + 1;
		}

		// Loop Delay
		SysTick_delay_ms(LOOP_DELAY_MS);
	}

	// Return Value
	return 0;
}

/**
 * @brief USART1 IRQ Handler
 */
void USART1_IRQHandler(void){
	// RXNE Flag
	if(USART->SR.BIT.RXNE){
		// Read & Store Data
		buffer[buffer_head] = (USART->DR.REG & 0xFF);
		// Circular Buffer
		buffer_head = (buffer_head == BUFFER_SIZE)? 0 : buffer_head + 1;
	}
}


/*
// Only RXNE IRQ

int main(void){
	
	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);
	// SysTick Timer (1ms)
	config_SysTick(SYSTICK_DELAY_1_MS);

	// Load USART Configuration
	load_USART_default(&usart_config);
	// Enable RX Not Empty IRQ
	usart_config.RXNEIE = USARTx_RXNEIE_ENABLE;
	config_USART(&usart_config);
	enable_USART(&usart_config);

	// Infinite Loop
	while(1){

		// Echo the data back to Serial Monitor
		if(curr_value){
			DEFAULT_SEP(&usart_config);
			USART_printf(&usart_config, "%c [%d]\r\n", curr_value, curr_value);
			curr_value = 0;
		}
		// Loop Delay
		SysTick_delay_ms(LOOP_DELAY_MS);
	}

	// Return Value
	return 0;
}

/**
 * @brief USART1 IRQ Handler
//
void USART1_IRQHandler(void){
	// RXNE Flag
	if(USART->SR.BIT.RXNE){
		// Read Data
		curr_value = USART->DR.REG & 0xFF;
		// Clear RXNE Flag (Not required, only read to DR will clear it)
		// USART->SR.BIT.RXNE = 0;	// Recommended only for multo-buffer communication
	}
}
*/