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
void USART_config(usart_config_t* USART_CONFIGx){
	// Configure the GPIO
	GPIO_config(USART_CONFIGx->TX_GPIO_CONFIGx);
	GPIO_config(USART_CONFIGx->RX_GPIO_CONFIGx);
	// Enable USART Clock
	USART_clk_enable(USART_CONFIGx);
	// Configure Baud Rate
	if(USART_CONFIGx->USARTx == USART1)
		USART_CONFIGx->USARTx->BRR.REG = (uint32_t)(APB2Clock/(USART_CONFIGx->baud_rate));
	else
		USART_CONFIGx->USARTx->BRR.REG = (uint32_t)(APB1Clock/(USART_CONFIGx->baud_rate));
	// Configure Stop Bits
	USART_CONFIGx->USARTx->CR2.REG |= ((USART_CONFIGx->stop_bits & 0x03) << USART_CR2_STOP_Pos);
	// Configure Rest of the Parameters
	USART_CONFIGx->USARTx->CR1.REG |= (((USART_CONFIGx->word_length & 0x01) << USART_CR1_M_Pos) | ((USART_CONFIGx->enable_parity & 0x01) << USART_CR1_PCE_Pos) | ((USART_CONFIGx->parity_selection & 0x01) << USART_CR1_PS_Pos) | ((USART_CONFIGx->TXEIE & 0x01) << USART_CR1_TXEIE_Pos) | ((USART_CONFIGx->TCIE & 0x01) << USART_CR1_TXEIE_Pos) | ((USART_CONFIGx->RXNEIE & 0x01) << USART_CR1_RXNEIE_Pos) | ((USART_CONFIGx->TXE & 0x01) << USART_CR1_TE_Pos) | ((USART_CONFIGx->RXE & 0x01) << USART_CR1_RE_Pos));
	// IRQ Enable
	if(USART_CONFIGx->TCIE || USART_CONFIGx->TXEIE || USART_CONFIGx->RXNEIE)
		enable_NVIC_IRQ(USART_get_IRQn(USART_CONFIGx));
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
 * @brief Reads the USARTx->DR
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @returns The value of the USARTx->DR
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
 * @note `float` decimal restricted max to 6 places
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
				int32_t num = va_arg(args, int);
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
			// Float Handling
			else if(*format == '.' || *format == 'f'){
				// Default precision
				uint8_t precision = 4;
				// Update Precision
				if(*format == '.'){
					// Go to next position
					format++;
					precision = (*format - '0');
					// Wrap precision if greater than 6 
					precision = (precision > 6)? 6 : precision;
					// Go to next position
					format++;
				}
				// Confirmation for float
				if(*format == 'f'){
					// Get float value
					float f = (float)va_arg(args, double);
					// Handle negative numbers
					uint8_t is_negative = 0;
					if(f < 0) {
						is_negative = 1;
						f = -f;
					}
					// Split into integer and fractional parts
					int32_t int_part = (int32_t)f;
					float frac_part = f - int_part;
					// Convert fractional part to fixed-point integer
					uint32_t frac_fixed = 0;
					for(uint8_t i = 0; i < precision; i++) {
						frac_part *= 10.0f;
						frac_fixed = frac_fixed * 10 + (uint32_t)frac_part;
						frac_part -= (uint32_t)frac_part;
					}
					// Print sign
					if(is_negative) 
						USART_putc(USART_CONFIGx, '-');
					// Print integer part
					char int_buf[12] = {'\0'};
					uint8_t idx = 0;
					do {
						int_buf[idx++] = (int_part % 10) + '0';
						int_part /= 10;
					} while(int_part > 0);
					// Print on the console
					while(idx > 0) {
						USART_putc(USART_CONFIGx, int_buf[--idx]);
					}
					// Print decimal point
					USART_putc(USART_CONFIGx, '.');
					// Print fractional part using fixed-point math
					char frac_buf[6] = {'\0'};
					for(uint8_t i = 0; i < precision; i++) {
						frac_buf[i] = (frac_fixed % 10) + '0';
						frac_fixed /= 10;
					}
					for(int8_t i = precision - 1; i >= 0; i--) {
						USART_putc(USART_CONFIGx, frac_buf[i]);
					}
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
