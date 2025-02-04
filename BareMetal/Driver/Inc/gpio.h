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
static gpio_config_t OB_LED_config = {
	.GPIOx = OB_LED_PORT,
	.PINx = OB_LED_PIN,
	.MODEx = MODE_OUT_2MHz,
	.CNFx = CNF_OUT_GP_PP,
};

/**
 * @brief Enables Clock for respective GPIO
 * @param[in] GPIOx The GPIO Port
 */
__attribute__((always_inline)) inline void enable_GPIO_clk(GPIO_REG_STRUCT* GPIOx){
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
__attribute__((always_inline)) inline void disable_GPIO_clk(GPIO_REG_STRUCT* GPIOx){
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
__attribute__((always_inline)) inline void enable_AFIO_clk(void){
	// Enable AFIO Clock
	RCC->APB2ENR.REG |= RCC_APB2ENR_AFIOEN;
}

/**
 * @brief Disables Clock for Alternate Function (AFIO)
 */
__attribute__((always_inline)) inline void disable_AFIO_clk(void){
	// Disable AFIO Clock
	RCC->APB2ENR.REG &= ~RCC_APB2ENR_AFIOEN;
}

/**
 * @brief Configures the GPIO based upon gpio structure
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
void config_GPIO(gpio_config_t* GPIO_CONFIGx);

/**
 * @brief Sets the state of GPIO Pin to HIGH
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
__attribute__((always_inline)) inline void set_GPIO(gpio_config_t* GPIO_CONFIGx){
	// Bit Set (Atomicity)
	GPIO_CONFIGx->GPIOx->BSRR.REG |= (1 << GPIO_CONFIGx->PINx);
}

/**
 * @brief Sets the state of GPIO Pin to LOW
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
__attribute__((always_inline)) inline void reset_GPIO(gpio_config_t* GPIO_CONFIGx){
	// Bit Reset (Atomicity)
	GPIO_CONFIGx->GPIOx->BRR.REG |= (1 << GPIO_CONFIGx->PINx);
}

/**
 * @brief Toggles the state of GPIO Pin
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
__attribute__((always_inline)) inline void toggle_GPIO(gpio_config_t* GPIO_CONFIGx){
	// Bit Reset (Atomicity)
	GPIO_CONFIGx->GPIOx->ODR.REG ^= (1 << GPIO_CONFIGx->PINx);
}

/**
 * @brief Retrieves the state of GPIO Pin
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 * @param[out] pin_state Pin State
 */
uint8_t get_GPIO(gpio_config_t* GPIO_CONFIGx);

/**
 * @brief Configures the on-board active low LED (PC13) as GP_OUT-PP-2MHz
 * @note Configuration is done based on capability of the GPIO as mentioned in data sheet
 */
__attribute__((always_inline)) inline void config_OB_LED(void){
	// Configure the OB LED
	config_GPIO(&OB_LED_config); 
}

/**
 * @brief Turns on-board active low LED (PC13) ON
 */
__attribute__((always_inline)) inline void set_OB_LED(void){
	// Reset the on-board active low LED GPIO
	reset_GPIO(&OB_LED_config);
}

/**
 * @brief Turns on-board active low LED (PC13) OFF
 */
__attribute__((always_inline)) inline void reset_OB_LED(void){
	// Set the on-board active low LED GPIO
	set_GPIO(&OB_LED_config);
}

/**
 * @brief Toggles the on-board active low LED (PC13)
 */
__attribute__((always_inline)) inline void toggle_OB_LED(void){
	// Toggle the on-board active low LED GPIO
	toggle_GPIO(&OB_LED_config);
}


#endif /* __GPIO__H__ */