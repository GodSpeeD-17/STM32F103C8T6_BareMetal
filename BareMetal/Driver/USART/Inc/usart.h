/***************************************************************************************
 *  File: usart.h
 *  Author: Shrey Shah
 *  Created on: 21/09/2025
 ***************************************************************************************/
// Header Guards
#ifndef __USART_H__
#define __USART_H__

/*********************************************** Includes ***********************************************/
// USART Configuration
#include "usart_config.h"
// Clocks (APB1/APB2)
#include "rcc.h"
// va_list
#include <stdarg.h>

/*********************************************** USART Interrupt ***********************************************/
typedef enum {
	USART_IRQ_NONE = 0x00,
	// IDLE Interrupt
	USART_IRQ_IDLE = 0x01,
	// RX Data Interrupt
	USART_IRQ_RX = 0x02,
	// TX Complete Interrupt
	USART_IRQ_TC = 0x04,
	// TX Data Register Empty Interrupt
	USART_IRQ_TX = 0x08,
	// Parity Error Interrupt
	USART_IRQ_PE = 0x10,
	// Common combinations
	USART_IRQ_RX_TX = (USART_IRQ_RX | USART_IRQ_TX),
	// Typical UART configurations
	USART_IRQ_STANDARD = (USART_IRQ_RX | USART_IRQ_TX | USART_IRQ_PE),
	USART_IRQ_FULL = (USART_IRQ_IDLE | USART_IRQ_RX | USART_IRQ_TC | USART_IRQ_TX | USART_IRQ_PE),
	// Error interrupts
	USART_IRQ_ERRORS = USART_IRQ_PE,
} usart_irq_t;

/*********************************************** Helper APIs ***********************************************/
/**
 * @brief Checks if USART TX Buffer is Empty
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3`
 * @returns Status of USART TX Buffer
 * @return - 0: TX Buffer Full
 * @return - 1: TX Buffer Empty
 * @note Check status using this function before using `USART_Send_Char()`
 */
__STATIC_FORCEINLINE uint8_t USART_TX_Ready(const usart_t usart){
	USART_TypeDef* thisUsart = USART_Get_Mapping(usart); 
	uint32_t usartTXReady = 0x00;
	usartTXReady = (thisUsart->SR.REG & USART_SR_TXE);
	return (uint8_t)(usartTXReady >> USART_SR_TXE_Pos);
}

/**
 * @brief Transmits a character on USART
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3`
 * @param character Character to be transmitted
 * @note Check status using `USART_TX_Ready()` before using this function
 */
__STATIC_FORCEINLINE void USART_TX_Byte(const usart_t usart, const uint8_t character){
	// Transfer the data
	USART_TypeDef* thisUsart = USART_Get_Mapping(usart);
	thisUsart->DR.REG = character;
}

/**
 * @brief Checks if USART RX Buffer is Full
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3`
 * @returns Status of USART RX Buffer
 * @return - 0: RX Buffer Empty
 * @return - 1: RX Buffer Full
 * @note Check status using this function before using `USART_Recv_Char()`
 */
__STATIC_FORCEINLINE uint8_t USART_RX_Ready(const usart_t usart){
	USART_TypeDef* thisUsart = USART_Get_Mapping(usart);
	uint32_t usartRXReady = 0x00;
	usartRXReady = (thisUsart->SR.REG & USART_SR_RXNE);
	return (uint8_t)(usartRXReady >> USART_SR_RXNE_Pos);
}

/**
 * @brief Receives a character on USART
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3`
 * @return 8-bits data read in the `USARTx->DR`
 * @note Check status using `USART_RX_Ready()` before using this function
 */
__STATIC_FORCEINLINE uint8_t USART_RX_Byte(const usart_t usart){
	// Receive the data
	USART_TypeDef* thisUsart = USART_Get_Mapping(usart);
	uint8_t recvData = thisUsart->DR.REG;
	return (recvData & 0xFF);
}

/**
 * @brief Blocking USART transmit byte
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3`
 * @param character Character to be transmitted
 * @note Blocking Function which takes care of USART TX
 */
__STATIC_FORCEINLINE void USART_sendByte(const usart_t usart, const uint8_t character){
	// Wait till TX Buffer is Empty
	while(USART_TX_Ready(usart) != 0x01);
	// Transmit the data
	USART_TX_Byte(usart, character);
}

/**
 * @brief Configures the following by default:
 * @brief - Data Bits: 8
 * @brief - Parity Bits: None
 * @brief - Stop Bits: 1
 * @brief - Baud Rate: 9600
 * @brief - Hardware Pins: TX+RX Enable
 * @param usartConfig pointer to USART Configuration Structure. Refer `usart_config_t`
 */
__STATIC_FORCEINLINE void USART_Default_Config(usart_config_t* usartConfig){
	// USART Communication Configuration
	usartConfig->config = USART_CONFIG_8N1;
	// USART Baud Rate Configuration
	usartConfig->baud_rate = USART_BAUD_9600;
	// USART Hardware Pins
	usartConfig->hardware = USART_TX_RX_ENABLE;
}

/*********************************************** USART APIs ***********************************************/
/**
 * @brief USART Hardware Pins Configure
 * @details
 * Explicitly enables the GPIO port clock gate (and the AFIO clock gate, for
 * alternate-function pins) for every selected pin through the RCC driver before
 * calling GPIO configuration, so GPIO never has to enable a foreign clock gate.
 * @param hardware Refer `usart_hardware_enable_t`
 * @param usartGpioConfig Refer `usart_gpio_t`
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success
 */
driver_status_t USART_GPIO_Config(const usart_hardware_enable_t hardware, usart_gpio_t* const usartGpioConfig);

/**
 * @brief Set USART Baud Rate
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3`
 * @param baudRate Refer `usart_baud_t`
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success 
 */
driver_status_t USART_BaudRate_Set(const usart_t usart, const usart_baud_t baudRate);

/**
 * @brief Sets the USART Communication Configuration
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3`
 * @param hardware Defines Hardware Feature Usage. Refer `usart_hardware_enable_t`
 * @param dataConfig Communication Standards for USART. Refer `usart_data_config_t`
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success 
 */
driver_status_t USART_DataConfig_Set(const usart_t usart, const usart_hardware_enable_t hardware, const usart_data_config_t dataConfig);

/**
 * @brief Configures the USART Module
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3`
 * @param usartConfig Pointer to USART Configuration Structure
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success
 */
driver_status_t USART_Config(const usart_t usart, usart_config_t* const usartConfig);

/**
 * @brief Enables USART-local interrupt sources
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3` 
 * @param irq USART IRQ Combinations. Refer `usart_irq_t`
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success
 * @note This API does not enable the corresponding NVIC vector. The
 * application or integration layer owns global IRQ delivery.
 */
driver_status_t USART_IRQ_Enable(const usart_t usart, const usart_irq_t irq);

/**
 * @brief Disables USART-local interrupt sources
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3` 
 * @param irq USART IRQ Combinations. Refer `usart_irq_t`
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success
 * @note This API does not disable the corresponding NVIC vector.
 */
driver_status_t USART_IRQ_Disable(const usart_t usart, const usart_irq_t irq);

/**
 * @brief Transmits formatted data on USART
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3`
 * @param format Formatted string
 * @note `float` decimal restricted max to 6 places
 */
void USART_printf(const usart_t usart, const char* format, ...);


#endif /* __USART_H__ */
