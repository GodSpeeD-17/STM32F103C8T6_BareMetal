/***************************************************************************************
 *  File: uart.h
 *  Created on: 19/12/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Dependency
#include "usart.h"

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
 * @brief Reads the USART DR
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @returns The value of the USART DR
 */
uint16_t USART_getc(usart_config_t* USART_CONFIGx){
	// Result
	uint16_t result = 0;
	// Read the Data Register
	result = USART_CONFIGx->USARTx->DR.REG;
	// Return Result
	return result;
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
 * @param[in] format The formatted string
 * @note 'float' is not yet supported
 */
void USART_printf(usart_config_t* USART_CONFIGx, const char* format, ...) {
	// Starts VA
	va_list args;
	va_start(args, format);

	// Data Present
	while (*format) {
		// Format Specifier Encountered
		if (*format == '%'){
			// Move to the next character
			format++;
			// Handle escape sequences
			if(*format == '%'){
				// Print a literal '%'
				USART_putc(USART_CONFIGx, '%');
			} 
			else if(*format == 'c'){
				// Handle character
				char c = (char)va_arg(args, int);
				USART_putc(USART_CONFIGx, c);
			} 
			else if(*format == 's'){
				// Handle string
				char* str = va_arg(args, char*);
				while (*str) {
					USART_putc(USART_CONFIGx, *str++);
				}
			} 
			else if(*format == 'd'){
				// Handle integer
				int num = va_arg(args, int);
				// Storing the integer value after converting it to character
				char buffer[10];
				// Buffer Index
				uint8_t i = 0;
				// Negative Number Indicator
				char isNegative = 0;
				// Negative Number
				if (num < 0) {
					isNegative = 1;
					num = -num;
				}
				// `int` to `char` (Reverse Storing)
				do {
					buffer[i++] = (num % 10) + '0';
					num /= 10;
				} while (num > 0);
				// Add negative sign if required
				if (isNegative) buffer[i++] = '-';
				// Print it in reverse order
				while (i > 0) {
					USART_putc(USART_CONFIGx, buffer[--i]);
				}
			} 
			// Unsupported format specifier
			else if (*format == 'f') {
				// Handle unsupported float
				const char* unsupported_msg = "Unsupported float\n";
				while (*unsupported_msg) {
					USART_putc(USART_CONFIGx, *unsupported_msg++);
				}
			} 
			// Handle unknown format specifier
			else {
				const char* unknown_msg = "Unknown format specifier\n";
				while (*unknown_msg) {
					USART_putc(USART_CONFIGx, *unknown_msg++);
				}
			}
		}
		// Non-format specifier character
		else {
			USART_putc(USART_CONFIGx, *format);
		}
		// Go to next character
		format++;
	}

	// Ends the VA
	va_end(args);
}

/**
 * @brief Receives data using USART
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @returns Data present in USARTx->DR
 * @note Polling Based Approach
 */
uint16_t USART_receive(usart_config_t* USART_CONFIGx){
	// Result
	uint16_t result = 0;
	// RXNE (Received data is ready to be read)
	while(!(USART_CONFIGx->USARTx->SR.REG & (1 << 5)));
	// Read received data
	result = USART_getc(USART_CONFIGx);
	// Return Result
	return result;
}
