/***************************************************************************************
 *  File: uart.h
 *  Created on: 19/12/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Dependency
#include "usart.h"

/*************************************** USART1 ********************************************/
// TX GPIO Configuration Structure
static gpio_config_t USART1_TX_GPIO_Config = {
	.GPIOx = USART1_TX_GPIO,
	.PINx = USART1_TX_PIN,
	.MODEx = MODE_OUT_50MHz,
	.CNFx = CNF_OUT_AF_PP,
};
// RX GPIO Configuration Structure
static gpio_config_t USART1_RX_GPIO_Config = {
	.GPIOx = USART1_RX_GPIO,
	.PINx = USART1_RX_PIN,
	.MODEx = MODE_IN,
	.CNFx = CNF_IN_FLOAT,
};
// Configuration Structure (Interrupt Disabled)
usart_config_t USART1_Config = {
	.USARTx = USART1,
	.TX_GPIO_CONFIGx = &USART1_TX_GPIO_Config,
	.RX_GPIO_CONFIGx = &USART1_RX_GPIO_Config,
	.word_length = USARTx_WORD_8_BITS,
	.baud_rate = USARTx_BAUD_9600,
	.stop_bits = USARTx_STOP_1_BIT,
	.RXE = USARTx_RX_ENABLE,
	.TXE = USARTx_TX_ENABLE,
	.enable_parity = USARTx_PARITY_DISABLE,
	.parity_selection = USARTx_PARITY_EVEN,
	.RXNEIE = USARTx_RXNEIE_DISABLE,
	.TCIE = USARTx_TCIE_DISABLE,
};
/*************************************** USART1 ********************************************/

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
	USART_CONFIGx->USARTx->CR2.REG |= ((USART_CONFIGx->stop_bits & 0x03) << USART_CR2_STOP_Pos);
	// Configure Rest of the Parameters
	USART_CONFIGx->USARTx->CR1.REG |= (((USART_CONFIGx->word_length & 0x01) << USART_CR1_M_Pos) | ((USART_CONFIGx->enable_parity & 0x01) << USART_CR1_PCE_Pos) | ((USART_CONFIGx->parity_selection & 0x01) << USART_CR1_PS_Pos) | ((USART_CONFIGx->TXEIE & 0x01) << USART_CR1_TXEIE_Pos) | ((USART_CONFIGx->TCIE & 0x01) << USART_CR1_TXEIE_Pos) | ((USART_CONFIGx->RXNEIE & 0x01) << USART_CR1_RXNEIE_Pos) | ((USART_CONFIGx->TXE & 0x01) << USART_CR1_TE_Pos) | ((USART_CONFIGx->RXE & 0x01) << USART_CR1_RE_Pos));
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
	while (!(USART_CONFIGx->USARTx->SR.REG & USART_SR_TXE_Msk));
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
	uint16_t data = 0;
	// Read the Data Register
	data = USART_CONFIGx->USARTx->DR.REG;
	// Return Result
	return data;
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
			// Character
			if(*format == 'c'){
				// Handle character
				char c = (char)va_arg(args, int);
				USART_putc(USART_CONFIGx, c);
			}
			// String
			else if(*format == 's'){
				// Handle string
				char* str = va_arg(args, char*);
				while (*str) {
					USART_putc(USART_CONFIGx, *str++);
				}
			} 
			// Integer
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
			/*
			// Float
			else if (*format == 'f') {
				// Default precision
				uint8_t precision = 4; // Default to 4 decimal places
				format++; // Move to the next character

				// Check for a precision specifier
				if (*format == '.') {
					format++; // Move past the '.'
					// Read the precision value
					if (*format >= '0' && *format <= '9') {
						precision = 0; // Reset precision
						while (*format >= '0' && *format <= '9') {
							precision = precision * 10 + (*format - '0');
							format++;
						}
					}
				}

				// Handle float
				float f = (float)va_arg(args, double); // float is promoted to double in variadic functions
				char buffer[30]; // Buffer to hold the string representation of the float
				int intPart = (int)f; // Get the integer part
				float fracPart = f - intPart; // Get the fractional part
				uint8_t i = 0; // Buffer Index

				// Handle negative float
				if (f < 0) {
					USART_putc(USART_CONFIGx, '-');
					intPart = -intPart;
					fracPart = -fracPart;
				}

				// Convert integer part to string
				do {
					buffer[i++] = (intPart % 10) + '0';
					intPart /= 10;
				} while (intPart > 0);

				// Print integer part in reverse order
				while (i > 0) {
					USART_putc(USART_CONFIGx, buffer[--i]);
				}

				// Print decimal point
				USART_putc(USART_CONFIGx, '.');

				// Convert fractional part to string based on specified precision
				for (uint8_t j = 0; j < precision; j++) {
					fracPart *= 10; // Shift left by one decimal place
				}
				int fracInt = (int)fracPart; // Get the integer part of the fraction

				// Print the fractional part
				for (uint8_t j = 0; j < precision; j++) {
					USART_putc(USART_CONFIGx, ((fracInt / (int)(1 * (10 ^ (precision - j - 1)))) + '0')); // Print each digit
					fracInt %= (int)(1 * (10 ^ (precision - j - 1))); // Remove the printed digit
				}
			}
			*/
			// Float
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
