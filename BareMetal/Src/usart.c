/***************************************************************************************
 *  File: uart.h
 *  Created on: 19/12/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Dependency
#include "usart.h"

static usart_config_t my_usart_config = {
	.USARTx = USART1,
};

/**
 * @brief Initialises USART based upon input Configuration Structure
 * @param[in] USART_CONFIGx USART Configuration Structure
 */
void config_USART(usart_config_t* USART_CONFIGx){
	// Configure the GPIO
	config_GPIO(USART_CONFIGx->TX_GPIO_CONFIGx);
	config_GPIO(USART_CONFIGx->RX_GPIO_CONFIGx);
	// Enable USART Clock
	enable_USART_clk(USART_CONFIGx);
	// Configure Baud Rate
	if(USART_CONFIGx->USARTx == USART1)
		USART_CONFIGx->USARTx->BRR.REG = (uint32_t)(APB2Clock/(USART_CONFIGx->baud_rate));
	if(USART_CONFIGx->USARTx == USART2)
		USART_CONFIGx->USARTx->BRR.REG = (uint32_t)(APB1Clock/(USART_CONFIGx->baud_rate));
	if(USART_CONFIGx->USARTx == USART3)
		USART_CONFIGx->USARTx->BRR.REG = (uint32_t)(APB1Clock/(USART_CONFIGx->baud_rate));
	// Configure Stop Bits
	USART_CONFIGx->USARTx->CR2.REG |= ((USART_CONFIGx->stop_bits & 0x03) << 12);
	// Configure Rest of the Parameters
	USART_CONFIGx->USARTx->CR1.REG |= (((USART_CONFIGx->word_length & 0x01) << 12) | ((USART_CONFIGx->enable_parity & 0x01) << 10) | ((USART_CONFIGx->parity_selection & 0x01) << 9) | ((USART_CONFIGx->TXEIE & 0x01) << 7) | ((USART_CONFIGx->TCIE & 0x01) << 6) | ((USART_CONFIGx->RXNEIE & 0x01) << 5) | ((USART_CONFIGx->TXE & 0x01) << 3) | ((USART_CONFIGx->RXE & 0x01) << 2));
	// IRQ Enable
	if(USART_CONFIGx->TCIE || USART_CONFIGx->TXEIE || USART_CONFIGx->RXNEIE)
		enable_NVIC_IRQ(get_USARTx_IRQn(USART_CONFIGx));
}

/**
 * @brief Transmits a character on USART
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @param[in] c The character to be transmitted
 */
void USART_putc(usart_config_t* USART_CONFIGx, const char c){
	// Wait for TX to be Empty
	while (!(USART_CONFIGx->USARTx->SR.REG & (1 << 7)));
	// Transfer the data 
	USART_CONFIGx->USARTx->DR.REG = (c & 0x000000FF);
}

/**
 * @brief Transmits a string on USART
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @param[in] str The character to be transmitted
 * @note '\0' is required for terminating sequence
 */
void USART_puts(usart_config_t* USART_CONFIGx, const char* str){
	// Termination Condition
	while(*str != '\0'){
		// Transmit the character
		USART_putc(USART_CONFIGx, *str);
		// Update the pointer to next position
		str++;
		// Delay
		for(volatile uint16_t local_delay = 0; local_delay < USARTx_STRING_TX_DELAY; local_delay++);
	}
}

/**
 * @brief Transmits formatted data on USART
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @param[in] format The format string
 */
void USART_printf(usart_config_t* USART_CONFIGx, const char* format, ...){
	// Starts VA
	va_list args;
	va_start(args, format);

	// Data Present
	while (*format) {
		// Format Specifier Encountered
		if (*format == '%') {
			// Get the exact format specifier
			format++;
			// String
			if (*format == 's') {
				// Handle string
				char* str = va_arg(args, char*);
				// Null-Character not encountered
				while(*str != '\0'){
					// Transmit the character & Update the pointer to next position
					USART_putc(USART_CONFIGx, *str++);
					// Small Delay
					for(volatile uint16_t local_delay = 0; local_delay < USARTx_STRING_TX_DELAY; local_delay++);
				}
			} 
			// Integer
			else if (*format == 'd') {
				// Handle integer
				int num = va_arg(args, int);
				// Buffer to hold the string representation of the number
				char buffer[10];
				// Buffer Index
				uint8_t i = 0;
				// Boolean to indicate if a negative number is encountered
				char isNegative = 0;

				// Handle negative numbers
				if (num < 0) {
					isNegative = 1;
					num = -1 * num;
				}

				// Convert integer to string
				do {
					// Get last digit
					buffer[i++] = (num % 10) + '0';
					// Remove last digit
					num /= 10;
				} while (num > 0);

				// Add negative sign
				if (isNegative)
					buffer[i++] = '-';

				// Send the string in reverse order
				while (i > 0) {
					USART_putc(USART_CONFIGx, buffer[--i]);
					// Small Delay
					for(volatile uint16_t local_delay = 0; local_delay < USARTx_STRING_TX_DELAY; local_delay++);
				}
			}
			// TO DO: Add more format specifiers as needed (e.g., %x for hex, %c for char)
		} 
		// Non-format specifier character
		else {
			// Send regular characters
			USART_putc(USART_CONFIGx, *format);
		}
		// Go to next character
		format++;
	}

	// Ends the VA
	va_end(args);
}
