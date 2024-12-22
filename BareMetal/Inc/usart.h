/***************************************************************************************
 *  File: uart.h
 *  Created on: 19/12/2024
 *  Author: Shrey Shah
 ***************************************************************************************/
// Header Guards
#ifndef __UART_H__
#define __UART_H__

#include "rcc.h"    // USART Clock
#include "gpio.h"   // GPIO Struct
#include "nvic.h"   // NVIC Enable

// Local Separation Function
#define DEFAULT_SEP_LEN					((uint8_t) 50)
#define DEFAULT_SEP(X)					(sep((X), DEFAULT_SEP_LEN)) 

// UART Configuration Structure
typedef struct {
	// GPIO Configuration Structure
	gpio_config_t* TX_GPIO_CONFIGx;
	gpio_config_t* RX_GPIO_CONFIGx;
	// USART
	USART_REG_STRUCT* USARTx;
	// Baud Rate
	uint16_t baud_rate;
	// Stop Bits
	uint8_t stop_bits;
	// Word Length
	uint8_t word_length: 1;
	// Enable Parity Control
	uint8_t enable_parity: 1;
	// Parity Mode
	uint8_t parity_selection: 1;
	// Enable Transmission
	uint8_t TXE: 1;
	// Enable Reception
	uint8_t RXE: 1;
	// Enable TX Register Empty (TXE) Interrupt
	uint8_t TXEIE: 1;
	// Enable TX Complete (TC) Interrupt
	uint8_t TCIE: 1;
	// Enable RX Register Not Empty (RXNE) Interrupt
	uint8_t RXNEIE: 1; 
} usart_config_t;

/**
 * @brief Enables the Clock to USART Module
 * @param[in] USART_CONFIGx USART Configuration Structure
 */
__attribute__((always_inline)) inline void enable_USART_clk(usart_config_t* USART_CONFIGx) {
	// Enable Clock based upon USART
	if(USART_CONFIGx->USARTx == USART1)
		RCC->APB2ENR.REG |= (1 << 14);
	if(USART_CONFIGx->USARTx == USART2)
		RCC->APB1ENR.REG |= (1 << 17);
	if(USART_CONFIGx->USARTx == USART3)
		RCC->APB1ENR.REG |= (1 << 18);
}

/**
 * @brief Disables the Clock to USART Module
 * @param[in] USART_CONFIGx USART Configuration Structure
 */
__attribute__((always_inline)) inline void disable_USART_clk(usart_config_t* USART_CONFIGx) {
	// Disable Clock based upon USART
	if(USART_CONFIGx->USARTx == USART1)
		RCC->APB2ENR.REG &= ~(1 << 14);
	if(USART_CONFIGx->USARTx == USART2)
		RCC->APB1ENR.REG &= ~(1 << 17);
	if(USART_CONFIGx->USARTx == USART3)
		RCC->APB1ENR.REG &= ~(1 << 18);
}

/**
 * @brief Starts USART Module
 * @param[in] USART_CONFIGx USART Configuration Structure
 */
__attribute__((always_inline)) inline void enable_USART(usart_config_t* USART_CONFIGx) {
	// Enable USART
	USART_CONFIGx->USARTx->CR1.REG |= (1 << 13);
}

/**
 * @brief Stops USART Module
 * @param[in] USART_CONFIGx USART Configuration Structure
 */
__attribute__((always_inline)) inline void disable_USART(usart_config_t* USART_CONFIGx) {
	// Disable USART
	USART_CONFIGx->USARTx->CR1.REG &= ~(1 << 13);
}

/**
 * @brief Retrieves the IRQn of USART
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @return IRQn for the corresponding USART
 */
__attribute__((always_inline)) inline uint8_t get_USARTx_IRQn(usart_config_t* USART_CONFIGx){
	// Retrieves the IRQ Number for NVIC
	if(USART_CONFIGx->USARTx == USART1)
		return USART1_IRQn;
	else if(USART_CONFIGx->USARTx == USART2)
		return USART2_IRQn;
	else if(USART_CONFIGx->USARTx == USART3)
		return USART3_IRQn;
}

/**
 * @brief Initialises USART based upon input Configuration Structure
 * @param[in] USART_CONFIGx USART Configuration Structure
 */
void config_USART(usart_config_t* USART_CONFIGx);

/**
 * @brief Transmits a character on USART
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @param[in] c The character to be transmitted
 */
void USART_putc(usart_config_t* USART_CONFIGx, const char c);

/**
 * @brief Transmits a string on USART
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @param[in] str The character to be transmitted
 */
void USART_puts(usart_config_t* USART_CONFIGx, const char* str);

/**
 * @brief Loads the default value for USART Struct
 * @param[in] USART_CONFIGx USART Configuration Structure
 */
__attribute__((always_inline)) inline void load_USART_default(usart_config_t* USART_CONFIGx){
    // Load default GPIO Configuration
    USART_CONFIGx->TX_GPIO_CONFIGx->MODEx = MODE_OUT_50MHz;
    USART_CONFIGx->TX_GPIO_CONFIGx->CNFx = CNF_OUT_AF_PP;
    USART_CONFIGx->RX_GPIO_CONFIGx->MODEx = MODE_IN;
    USART_CONFIGx->RX_GPIO_CONFIGx->CNFx = CNF_IN_FLOAT;
    // Set Baud Rate to 9600
    USART_CONFIGx->baud_rate = USARTx_BAUD_9600;
    // Set Stop Bit to 1
	USART_CONFIGx->stop_bits = USARTx_STOP_1_BIT;
	// Word Length
	USART_CONFIGx->word_length = USARTx_WORD_8_BITS;
	// USART Parity Disable
	USART_CONFIGx->enable_parity = USARTx_PARITY_DISABLE;
	// USART Parity Selection
	USART_CONFIGx->parity_selection = USARTx_PARITY_EVEN;
	// Disable Interrupts
	USART_CONFIGx->TXEIE = USARTx_TXEIE_DISABLE;
	USART_CONFIGx->RXNEIE = USARTx_RXNEIE_DISABLE;
	USART_CONFIGx->TCIE = USARTx_TCIE_DISABLE;
	// Enable TX
	USART_CONFIGx->TXE = USARTx_TX_ENABLE;
	// Enable RX
	USART_CONFIGx->RXE = USARTx_RX_ENABLE;
}

/**
 * @brief Prints '*' on USART
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @param[in] length The length of '*'
 */
__attribute__((always_inline)) inline void sep(usart_config_t* USART_CONFIGx, uint8_t length){
	// Print '*'
	while(length--){
		// Print character
		USART_putc(USART_CONFIGx, '*');
		// Delay
		for(volatile uint16_t local_delay = 0; local_delay < USARTx_STRING_TX_DELAY; local_delay++);
	}
	// Send CR
	USART_putc(USART_CONFIGx, '\r');
	// Send NL
	USART_putc(USART_CONFIGx, '\n');
}

#endif /* __UART_H__ */