/***************************************************************************************
 *  File: uart.h
 *  Created on: 19/12/2024
 *  Author: Shrey Shah
 ***************************************************************************************/
// Header Guards
#ifndef __USART_H__
#define __USART_H__

/*************************************** Dependency ********************************************/
#include "reg_map.h"
#include "rcc.h"    // Clocks (APB1/APB2)
#include "gpio.h"   // GPIO Struct
#include "nvic.h"   // NVIC Enable
#include <stdarg.h> // va_list
/*************************************** Dependency ********************************************/

/*************************************** MACROs ********************************************/
#define USART1_TX_GPIO					GPIOA
#define USART1_TX_PIN					GPIOx_PIN_9
#define USART1_RX_GPIO					GPIOA
#define USART1_RX_PIN					GPIOx_PIN_10
#define USART1_putc(X)					USART_putc(&USART1_Configuration, ((char)(X)))
#define USART1_puts(X)					USART_puts(&USART1_Configuration, ((const char *)(X)))
#define DEF_SEP_LEN						((uint8_t) 50)
#define DEF_SEP(X)						sep((X), '*', DEF_SEP_LEN)
#define USART1_DEF_SEP()				DEF_SEP(&USART1_Configuration)
#define USART1_Config()					USART_Config(&USART1_Configuration)
#define USART1_Enable()					USART_Enable(&USART1_Configuration)
/*************************************** MACROs ********************************************/

/*************************************** USART Configuration Structure ********************************************/
// USART Configuration Structure
typedef struct {
	// USART
	USART_REG_STRUCT* USARTx;
	// TX Configuration
	gpio_config_t TX;
	// RX Configuration
	gpio_config_t RX;
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
/*************************************** USART Configuration Structure ********************************************/

/*************************************** USART1 ********************************************/
// Configuration Structure (Interrupt Disabled)
static usart_config_t USART1_Configuration = {
	.USARTx = USART1,
	.TX = {
		.GPIO = USART1_TX_GPIO,
		.PIN = USART1_TX_PIN,
		.MODE = GPIOx_MODE_OUT_50MHz,
		.CNF = GPIOx_CNF_OUT_AF_PP,
	},
	.RX = {
		.GPIO = USART1_RX_GPIO,
		.PIN = USART1_RX_PIN,
		.MODE = GPIOx_MODE_IN,
		.CNF = GPIOx_CNF_IN_FLOAT,
	},
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
 * @brief Enables the Clock to USART Module
 * @param[in] USART_CONFIGx USART Configuration Structure
 */
__INLINE__ void USART_clk_enable(usart_config_t* USART_CONFIGx) {
	// Enable Clock based upon USART
	if(USART_CONFIGx->USARTx == USART1)
		RCC->APB2ENR.REG |= RCC_APB2ENR_USART1EN;
	if(USART_CONFIGx->USARTx == USART2)
		RCC->APB1ENR.REG |= RCC_APB1ENR_USART2EN;
	if(USART_CONFIGx->USARTx == USART3)
		RCC->APB1ENR.REG |= RCC_APB1ENR_USART3EN;
}

/**
 * @brief Disables the Clock to USART Module
 * @param[in] USART_CONFIGx USART Configuration Structure
 */
__INLINE__ void USART_clk_disable(usart_config_t* USART_CONFIGx) {
	// Disable Clock based upon USART
	if(USART_CONFIGx->USARTx == USART1)
		RCC->APB2ENR.REG &= ~RCC_APB2ENR_USART1EN;
	if(USART_CONFIGx->USARTx == USART2)
		RCC->APB1ENR.REG &= ~RCC_APB1ENR_USART2EN;
	if(USART_CONFIGx->USARTx == USART3)
		RCC->APB1ENR.REG &= ~RCC_APB1ENR_USART3EN;
}

/**
 * @brief Starts USART Module
 * @param[in] USART_CONFIGx USART Configuration Structure
 */
__INLINE__ void USART_Enable(usart_config_t* USART_CONFIGx) {
	// Enable USART
	USART_CONFIGx->USARTx->CR1.REG |= USART_CR1_UE;
}

/**
 * @brief Stops USART Module
 * @param[in] USART_CONFIGx USART Configuration Structure
 */
__INLINE__ void USART_Disable(usart_config_t* USART_CONFIGx) {
	// Disable USART
	USART_CONFIGx->USARTx->CR1.REG &= ~USART_CR1_UE;
}

/**
 * @brief Retrieves the IRQn of USART
 * @param[in] USARTx USART Instance: `USART1`, `USART2`, `USART3`
 * @return IRQn for the corresponding USART
 */
__INLINE__ uint8_t USART_get_IRQn(USART_REG_STRUCT* USARTx){
	// Retrieves the IRQ Number for NVIC
	if(USARTx == USART1)
		return USART1_IRQn;
	else if(USARTx == USART2)
		return USART2_IRQn;
	else if(USARTx == USART3)
		return USART3_IRQn;
}

/**
 * @brief Initialises USART based upon input Configuration Structure
 * @param[in] USART_CONFIGx USART Configuration Structure
 */
void USART_Config(usart_config_t* USART_CONFIGx);

/**
 * @brief Transmits a character on USART
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @param[in] c The character to be transmitted
 */
void USART_putc(usart_config_t* USART_CONFIGx, const char c);

/**
 * @brief Reads the USARTx->DR
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @returns The value of the USARTx->DR
 */
uint16_t USART_getc(usart_config_t* USART_CONFIGx);

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
void USART_load_default(usart_config_t* USART_CONFIGx);

/**
 * @brief Prints '*' on USART
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @param[in] c Character to be printed
 * @param[in] length The length of character to be printed
 */
__INLINE__ void sep(usart_config_t* USART_CONFIGx, char c, uint8_t length){
	// Print character
	while(length--){
		// Print character
		USART_putc(USART_CONFIGx, c);
		// Delay
		for(volatile uint16_t local_delay = 0; local_delay < USARTx_STRING_TX_DELAY; local_delay++);
	}
	// Send CR
	USART_putc(USART_CONFIGx, '\r');
	// Send NL
	USART_putc(USART_CONFIGx, '\n');
}

/**
 * @brief Transmits formatted data on USART
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @param[in] format The formatted string
 * @note `float` decimal restricted max to 6 places
 */
void USART_printf(usart_config_t* USART_CONFIGx, const char* format, ...);

/**
 * @brief Receives data using USART
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @returns Data present in USARTx->DR
 * @note Polling Based Approach
 */
uint16_t USART_receive(usart_config_t* USART_CONFIGx);

/**
 * @brief Echos the character on Serial Console
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @param[in] rx_char Character to be displayed on Screen
 */
__INLINE__ void USART_echo(usart_config_t* USART_CONFIGx, const char rx_char){
	// Print on Serial Console
	USART_printf(USART_CONFIGx, "%c", rx_char);
}

/**
 * @brief Enables the TX using DMA
 * @param[in] USARTx USART Instance: `USART1`, `USART2`, `USART3`
 */
__INLINE__ void USART_DMA_TX_Enable(USART_REG_STRUCT* USARTx){
	// Enable the DMA TX
	USARTx->CR3.REG |= USART_CR3_DMAT;
}

/**
 * @brief Disables the TX using DMA
 * @param[in] USARTx USART Instance: `USART1`, `USART2`, `USART3`
 */
__INLINE__ void USART_DMA_TX_Disable(USART_REG_STRUCT* USARTx){
	// Enable the DMA TX
	USARTx->CR3.REG &= ~USART_CR3_DMAT;
}

/**
 * @brief Enables the RX using DMA
 * @param[in] USARTx USART Instance: `USART1`, `USART2`, `USART3`
 */
__INLINE__ void USART_DMA_RX_Enable(USART_REG_STRUCT* USARTx){
	// Enable the DMA TX
	USARTx->CR3.REG |= USART_CR3_DMAR;
}

/**
 * @brief Disables the RX using DMA
 * @param[in] USARTx USART Instance: `USART1`, `USART2`, `USART3`
 */
__INLINE__ void USART_DMA_RX_Disable(USART_REG_STRUCT* USARTx){
	// Enable the DMA TX
	USARTx->CR3.REG &= ~USART_CR3_DMAR;
}

/**
 * @brief Appends the data to the USART TX buffer
 * @param str The sequence of characters (string) to be appended
 * @param length Length of the string
 * @note The buffer is circular, so it wraps around when it reaches the end
 */
void USART_TX_Buffer_Append(const char* str, uint8_t length);

/**
 * @brief Appends the data to the USART RX buffer
 * @param str The sequence of characters (string) to be appended
 * @param length Length of the string
 * @note The buffer is circular, so it wraps around when it reaches the end
 */
void USART_RX_Buffer_Append(const char* str, uint8_t length);





#endif /* __USART_H__ */