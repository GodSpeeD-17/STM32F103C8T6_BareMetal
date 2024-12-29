// Main Header
#include "main.h"

// #define CIRCULAR_BUFFER		// Uncomment this for direct Circular Buffer Fetch
#define PERIODIC_BUFFER_FETCH	// Uncomment this for periodic Circular Buffer Fetch

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

// Circular Buffer Example
#ifdef CIRCULAR_BUFFER
	// Main Entry Point
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
			// Buffer Head and Tail are at different position
			if(buffer_head != buffer_tail){
				// Default Separation
				DEF_SEP(&usart_config);
				// Read Data from Buffer
				USART_printf(&usart_config, "buffer[%d]: %c [%d]\r\n", buffer_tail, buffer[buffer_tail], buffer[buffer_tail++]);
				// Circular Buffer
				buffer_tail = (buffer_tail == BUFFER_SIZE)? 0 : buffer_tail;
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
			buffer[buffer_head++] = (USART->DR.REG & 0xFF);
			// Circular Buffer
			buffer_head = (buffer_head == BUFFER_SIZE)? 0 : buffer_head;
		}
	}

// Periodic Buffer Fetch
#elif defined(PERIODIC_BUFFER_FETCH)

// Buffer Fetch Period (ms)
#define BUFFER_FETCH_DELAY_MS			((uint64_t) 15 * 1000)

// Reference Tick Count
uint64_t reference_ticks = 0x00;
uint32_t tick_difference = 0x00;
static int8_t time_left = (BUFFER_FETCH_DELAY_MS / 1000);

	// Main Entry Point
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

		// Configure OB LED
		config_OB_LED();
		reset_OB_LED();

		// Update Reference Ticks
		reference_ticks = get_curr_ticks();

		// Infinite Loop
		while(1){
			// Take tick difference
			tick_difference = (uint32_t)(get_curr_ticks() - reference_ticks);
			// Wait for Buffer Fetch Period
			if(tick_difference >= BUFFER_FETCH_DELAY_MS){
				// Default Separation
				DEF_SEP(&usart_config);
				// If head & Tail are at different index
				if(buffer_head != buffer_tail){
					// Read Data from Buffer
					USART_printf(&usart_config, "Received String: ");
					// Buffer Head and Tail should be at same index
					while(buffer_head != buffer_tail){
						// Print the character
						USART_putc(&usart_config, buffer[buffer_tail++]);
						// Circular Buffer
						buffer_tail = (buffer_tail == BUFFER_SIZE)? 0 : buffer_tail;
					}
					// Carriage Return + New Line
					USART_printf(&usart_config,"\r\n");
				}
				// Update Reference Ticks
				reference_ticks = get_curr_ticks();
			}
			// Countdown Time
			// else if(tick_difference & (1 << 10)){
			// 	// Toggle OB LED
			// 	toggle_OB_LED();
			// 	// Custom Separation
			// 	sep(&usart_config, '-', DEF_SEP_LEN);
			// 	// Counting
			// 	USART_printf("Time Left: %d (s)\r\n", time_left);
			// 	// Variable Updation
			// 	time_left--;
			// 	time_left = (time_left <= 0)? (BUFFER_FETCH_DELAY_MS / 1000): time_left;
			// }
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
			USART_echo(&usart_config, buffer[buffer_head++]);
			// Circular Buffer
			buffer_head = (buffer_head == BUFFER_SIZE)? 0 : buffer_head;
		}
	}
// No Buffer Example
#else
	// Main Entry Point
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
				DEF_SEP(&usart_config);
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
	*/
	void USART1_IRQHandler(void){
		// RXNE Flag
		if(USART->SR.BIT.RXNE){
			// Read Data
			curr_value = USART->DR.REG & 0xFF;
			// Clear RXNE Flag (Not required, only read to DR will clear it)
			// USART->SR.BIT.RXNE = 0;	// Recommended only for multo-buffer communication
		}
	}

#endif