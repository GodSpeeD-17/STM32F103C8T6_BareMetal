/***************************************************************************************
 *  File: gpio.h
 *  Created on: 14/09/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __GPIO__H__
#define __GPIO__H__

// Register Address Mapping
#include "reg_map.h"

// GPIO Configuration Structure
typedef struct {
	// GPIO Port
	// - `GPIOA`
	// - `GPIOB`
	// - `GPIOC`
	// - `GPIOD`
	GPIO_REG_STRUCT* GPIO;
	// GPIO Pin
	// - `GPIOx_PIN_XY`
	uint8_t PIN: 4;
	// GPIO Pin Mode
	// - `GPIOx_MODE_INPUT`
	// - `GPIOx_MODE_OUT_10MHz`
	// - `GPIOx_MODE_OUT_2MHz`
	// - `GPIOx_MODE_OUT_50MHz`
	uint8_t MODE: 2;
	// GPIO Pin Configuration
	// - `GPIOx_CNF_IN_ANALOG`
	// - `GPIOx_CNF_IN_FLOAT`
	// - `GPIOx_CNF_IN_PD`
	// - `GPIOx_CNF_IN_PU`
	// - `GPIOx_CNF_OUT_GP_PP`
	// - `GPIOx_CNF_OUT_GP_OD`
	// - `GPIOx_CNF_OUT_AF_PP`
	// - `GPIOx_CNF_OUT_AF_OD`
	uint8_t CNF: 2;
} gpio_config_t;

// On-board LED Configuration
static gpio_config_t OB_LED_Configuration = {
	.GPIO = OB_LED_PORT,
	.PIN = OB_LED_PIN,
	.MODE = GPIOx_MODE_OUT_2MHz,
	.CNF = GPIOx_CNF_OUT_GP_PP,
};

/**
 * @brief Enables Clock for respective GPIO
 * @param[in] GPIO The GPIO Port
 */
__INLINE__ void GPIO_clk_enable(GPIO_REG_STRUCT* GPIO){
	// Enable Clock for respective GPIO
	if(GPIO == GPIOA){
		RCC->APB2ENR.REG |= RCC_APB2ENR_IOPAEN;
	}
	else if (GPIO == GPIOB){
		RCC->APB2ENR.REG |= RCC_APB2ENR_IOPBEN;
	}
	else if (GPIO == GPIOC){
		RCC->APB2ENR.REG |= RCC_APB2ENR_IOPCEN;
	}
	else if (GPIO == GPIOD){
		RCC->APB2ENR.REG |= RCC_APB2ENR_IOPDEN;
	}
	else if (GPIO == GPIOE){
		RCC->APB2ENR.REG |= RCC_APB2ENR_IOPEEN;
	}
	// Error
	else{
		return;
	}
}

/**
 * @brief Disables Clock for respective GPIO
 * @param[in] GPIO The GPIO Configuration Structure
 */
__INLINE__ void GPIO_clk_disable(GPIO_REG_STRUCT* GPIO){
	// Disable Clock for respective GPIO
	if(GPIO == GPIOA){
		RCC->APB2ENR.REG &= ~RCC_APB2ENR_IOPAEN;
	}
	else if (GPIO == GPIOB){
		RCC->APB2ENR.REG &= ~RCC_APB2ENR_IOPBEN;
	}
	else if (GPIO == GPIOC){
		RCC->APB2ENR.REG &= ~RCC_APB2ENR_IOPCEN;
	}
	else if (GPIO == GPIOD){
		RCC->APB2ENR.REG &= ~RCC_APB2ENR_IOPDEN;
	}
	else if (GPIO == GPIOE){
		RCC->APB2ENR.REG &= ~RCC_APB2ENR_IOPEEN;
	}
	// Error
	else{
		return;
	}
} 

/**
 * @brief Enables Clock for Alternate Function (AFIO)
 */
__INLINE__ void AFIO_clk_enable(void){
	// Enable AFIO Clock
	RCC->APB2ENR.REG |= RCC_APB2ENR_AFIOEN;
}

/**
 * @brief Disables Clock for Alternate Function (AFIO)
 */
__INLINE__ void AFIO_clk_disable(void){
	// Disable AFIO Clock
	RCC->APB2ENR.REG &= ~RCC_APB2ENR_AFIOEN;
}

/**
 * @brief Configures the GPIO based upon gpio structure
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
void GPIO_Config(gpio_config_t* GPIO_CONFIGx);

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
 * @param[out] pin_state Pin State
 */
uint8_t GPIO_Get(gpio_config_t* GPIO_CONFIGx);

/**
 * @brief Configures the on-board active low LED (PC13) as GP_OUT-PP-2MHz
 * @note Configuration is done based on capability of the GPIO as mentioned in data sheet
 */
__INLINE__ void OB_LED_Config(void){
	// Configure the OB LED
	GPIO_Config(&OB_LED_Configuration); 
}

/**
 * @brief Turns on-board active low LED (PC13) ON
 */
__INLINE__ void OB_LED_Set(void){
	// Reset the on-board active low LED GPIO
	GPIO_Reset(&OB_LED_Configuration);
}

/**
 * @brief Turns on-board active low LED (PC13) OFF
 */
__INLINE__ void OB_LED_Reset(void){
	// Set the on-board active low LED GPIO
	GPIO_Set(&OB_LED_Configuration);
}

/**
 * @brief Toggles the on-board active low LED (PC13)
 */
__INLINE__ void OB_LED_Toggle(void){
	// Toggle the on-board active low LED GPIO
	GPIO_Toggle(&OB_LED_Configuration);
}


#endif /* __GPIO__H__ */