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
