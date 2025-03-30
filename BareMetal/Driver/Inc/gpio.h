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
	// Port
	GPIO_REG_STRUCT* GPIOx;
	// Pin
	uint8_t PINx;
	// Mode
	uint8_t MODEx;
	// Configuration
	uint8_t CNFx;
} gpio_config_t;

// On-board LED Configuration
static gpio_config_t OB_LED_Config = {
	.GPIOx = OB_LED_PORT,
	.PINx = OB_LED_PIN,
	.MODEx = MODE_OUT_2MHz,
	.CNFx = CNF_OUT_GP_PP,
};

/**
 * @brief Enables Clock for respective GPIO
 * @param[in] GPIOx The GPIO Port
 */
__STATIC_INLINE__ void GPIO_clk_enable(GPIO_REG_STRUCT* GPIOx){
	// Enable Clock for respective GPIO
	if(GPIOx == GPIOA){
		RCC->APB2ENR.REG |= RCC_APB2ENR_IOPAEN;
	}
	else if (GPIOx == GPIOB){
		RCC->APB2ENR.REG |= RCC_APB2ENR_IOPBEN;
	}
	else if (GPIOx == GPIOC){
		RCC->APB2ENR.REG |= RCC_APB2ENR_IOPCEN;
	}
	else if (GPIOx == GPIOD){
		RCC->APB2ENR.REG |= RCC_APB2ENR_IOPDEN;
	}
	else if (GPIOx == GPIOE){
		RCC->APB2ENR.REG |= RCC_APB2ENR_IOPEEN;
	}
	// Error
	else{
		return;
	}
}

/**
 * @brief Disables Clock for respective GPIO
 * @param[in] GPIOx The GPIO Configuration Structure
 */
__STATIC_INLINE__ void GPIO_clk_disable(GPIO_REG_STRUCT* GPIOx){
	// Disable Clock for respective GPIO
	if(GPIOx == GPIOA){
		RCC->APB2ENR.REG &= ~RCC_APB2ENR_IOPAEN;
	}
	else if (GPIOx == GPIOB){
		RCC->APB2ENR.REG &= ~RCC_APB2ENR_IOPBEN;
	}
	else if (GPIOx == GPIOC){
		RCC->APB2ENR.REG &= ~RCC_APB2ENR_IOPCEN;
	}
	else if (GPIOx == GPIOD){
		RCC->APB2ENR.REG &= ~RCC_APB2ENR_IOPDEN;
	}
	else if (GPIOx == GPIOE){
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
__STATIC_INLINE__ void AFIO_clk_enable(void){
	// Enable AFIO Clock
	RCC->APB2ENR.REG |= RCC_APB2ENR_AFIOEN;
}

/**
 * @brief Disables Clock for Alternate Function (AFIO)
 */
__STATIC_INLINE__ void AFIO_clk_disable(void){
	// Disable AFIO Clock
	RCC->APB2ENR.REG &= ~RCC_APB2ENR_AFIOEN;
}

/**
 * @brief Configures the GPIO based upon gpio structure
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
void GPIO_config(gpio_config_t* GPIO_CONFIGx);

/**
 * @brief Sets the state of GPIO Pin to HIGH
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
__STATIC_INLINE__ void GPIO_set(gpio_config_t* GPIO_CONFIGx){
	// Bit Set (Atomicity)
	GPIO_CONFIGx->GPIOx->BSRR.REG |= (1 << GPIO_CONFIGx->PINx);
}

/**
 * @brief Sets the state of GPIO Pin to LOW
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
__STATIC_INLINE__ void GPIO_reset(gpio_config_t* GPIO_CONFIGx){
	// Bit Reset (Atomicity)
	GPIO_CONFIGx->GPIOx->BRR.REG |= (1 << GPIO_CONFIGx->PINx);
}

/**
 * @brief Toggles the state of GPIO Pin
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
__STATIC_INLINE__ void GPIO_toggle(gpio_config_t* GPIO_CONFIGx){
	// Output Data Register
	GPIO_CONFIGx->GPIOx->ODR.REG ^= (1 << GPIO_CONFIGx->PINx);
}

/**
 * @brief Retrieves the state of GPIO Pin
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 * @param[out] pin_state Pin State
 */
uint8_t GPIO_get(gpio_config_t* GPIO_CONFIGx);

/**
 * @brief Configures the on-board active low LED (PC13) as GP_OUT-PP-2MHz
 * @note Configuration is done based on capability of the GPIO as mentioned in data sheet
 */
__STATIC_INLINE__ void OB_LED_config(void){
	// Configure the OB LED
	GPIO_config(&OB_LED_Config); 
}

/**
 * @brief Turns on-board active low LED (PC13) ON
 */
__STATIC_INLINE__ void OB_LED_set(void){
	// Reset the on-board active low LED GPIO
	GPIO_reset(&OB_LED_Config);
}

/**
 * @brief Turns on-board active low LED (PC13) OFF
 */
__STATIC_INLINE__ void OB_LED_reset(void){
	// Set the on-board active low LED GPIO
	GPIO_set(&OB_LED_Config);
}

/**
 * @brief Toggles the on-board active low LED (PC13)
 */
__STATIC_INLINE__ void OB_LED_toggle(void){
	// Toggle the on-board active low LED GPIO
	GPIO_toggle(&OB_LED_Config);
}


#endif /* __GPIO__H__ */