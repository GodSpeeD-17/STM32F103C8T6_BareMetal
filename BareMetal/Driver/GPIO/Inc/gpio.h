/***************************************************************************************
 *  File: gpio.h
 *  Created on: 14/09/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __GPIO__H__
#define __GPIO__H__

// Register Address Mapping
#include "gpio_config.h"

// On-board LED MACROs (Active-Low)
#define OB_LED_Set()				OB_LED_PORT->BRR.REG |= (1 << OB_LED_PIN)
#define OB_LED_Reset()				OB_LED_PORT->BSRR.REG |= (1 << OB_LED_PIN)
#define OB_LED_Toggle()				OB_LED_PORT->ODR.REG ^= (1 << OB_LED_PIN)

/**
 * @brief Configures the GPIO based upon gpio structure
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
void GPIO_Config(gpio_config_t* GPIO_CONFIGx);

/**
 * @brief Configures the GPIO assuming LED
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
__INLINE__ void GPIO_Config_LED(gpio_config_t* GPIO_CONFIGx){
	// Set Mode to Output at 10MHz
	GPIO_CONFIGx->MODE = GPIOx_MODE_OUT_10MHz;
	// Set Configuration to General Purpose Push-Pull
	GPIO_CONFIGx->CNF = GPIOx_CNF_OUT_GP_PP;
	// Configure GPIO
	GPIO_Config(GPIO_CONFIGx);
}

/**
 * @brief Sets the state of GPIO Pin to HIGH
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
__INLINE__ void GPIO_Set(gpio_config_t* GPIO_CONFIGx){
	// Bit Set (Atomicity)
	GPIO_CONFIGx->GPIO->BSRR.REG |= (1 << GPIO_CONFIGx->PIN);
}

/**
 * @brief Sets the state of GPIO Pin to LOW
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
__INLINE__ void GPIO_Reset(gpio_config_t* GPIO_CONFIGx){
	// Bit Reset (Atomicity)
	GPIO_CONFIGx->GPIO->BRR.REG |= (1 << GPIO_CONFIGx->PIN);
}

/**
 * @brief Toggles the state of GPIO Pin
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
__INLINE__ void GPIO_Toggle(gpio_config_t* GPIO_CONFIGx){
	// Output Data Register
	GPIO_CONFIGx->GPIO->ODR.REG ^= (1 << GPIO_CONFIGx->PIN);
}

/**
 * @brief Retrieves the state of GPIO Pin
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 * @returns Pin State
 */
uint8_t GPIO_Get(gpio_config_t* GPIO_CONFIGx);

/**
 * @brief Configures On-board LED
 * @note This function configures the on-board LED (OB_LED) for output mode at 2MHz
 *       with general-purpose push-pull configuration.
 * @note The on-board LED is active-low, meaning it turns ON when the pin is set to LOW.
 */
void OB_LED_Config(void);

#endif /* __GPIO__H__ */