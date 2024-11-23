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

/**
 * @brief Enables Clock for respective GPIO
 * @param[in] GPIOx The GPIO Port
 */
__attribute__((always_inline)) inline void enable_GPIO_clk(GPIO_REG_STRUCT* GPIOx){

	// Enable Clock for respective GPIO
	if(GPIOx == GPIOA){
		RCC->APB2ENR.BIT.IOPAEN = BIT_SET;
	}
	else if (GPIOx == GPIOB){
		RCC->APB2ENR.BIT.IOPBEN = BIT_SET;
	}
	else if (GPIOx == GPIOC){
		RCC->APB2ENR.BIT.IOPCEN = BIT_SET;
	}
	// Error
	else{
		return;
	}
}

/**
 * @brief Disables Clock for respective GPIO
 * @param[in] GPIOx The GPIO Port
 */
__attribute__((always_inline)) inline void disable_GPIO_clk(GPIO_REG_STRUCT* GPIOx){

	// Enable Clock for respective GPIO
	if(GPIOx == GPIOA){
		RCC->APB2ENR.BIT.IOPAEN = BIT_RESET;
	}
	else if (GPIOx == GPIOB){
		RCC->APB2ENR.BIT.IOPBEN = BIT_RESET;
	}
	else if (GPIOx == GPIOC){
		RCC->APB2ENR.BIT.IOPCEN = BIT_RESET;
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
	// Enable AFIO Clock in APB2 Enable Register (APB2ENR)
	RCC->APB2ENR.BIT.AFIOEN = (uint8_t) 0x01;
}

/**
 * @brief Disables Clock for Alternate Function (AFIO)
 */
__attribute__((always_inline)) inline void disable_AFIO_clk(void){
	// Enable AFIO Clock in APB2 Enable Register (APB2ENR)
	RCC->APB2ENR.BIT.AFIOEN = (uint8_t) 0x00;
}

/**
 * @brief Configures GPIO as per input
 * @param[in] GPIOx `GPIOA`, `GPIOB`, `GPIOC`
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 * @param[in] MODEx Pin Mode `MODE_..`
 * @param[in] CNFx Pin Configuration `CNF_..`
 * @note Do not use it to configure PB3, PB4, PC13, PC14, PC15
 */
void config_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx, uint8_t MODEx, uint8_t CNFx);

/**
 * @brief Configures a GPIO as LED
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 */
__attribute__((always_inline)) inline void config_LED(GPIO_REG_STRUCT* GPIOx, uint8_t PINx){
	// General Purpose Output @10MHz
	config_GPIO(GPIOx, PINx, MODE_OUT_10MHz, CNF_OUT_GP_PP);
}

/**
 * @brief Sets a GPIO Pin HIGH
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 */
__attribute__((always_inline)) inline void set_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx){
	// Bit Set (Atomicity)
	GPIOx->BSRR.REG = (BIT_SET << PINx);
}

/**
 * @brief Resets a GPIO Pin LOW
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 */
__attribute__((always_inline)) inline void reset_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx) {
	// Bit Reset (Atomicity)
	GPIOx->BRR.REG = (BIT_SET << PINx);
}

/**
 * @brief Toggles GPIO Pin
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 */
__attribute__((always_inline)) inline void toggle_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx){
	// Toggle the GPIO Pin
	GPIOx->ODR.REG ^= (BIT_SET << PINx);
}

/**
 * @brief Gets the status of GPIO Pin
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 * @returns `BIT_SET`, `BIT_RESET`
 */
uint8_t get_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx);

/**
 * @brief Configures the on-board active low LED (PC13) as GP_OUT-PP-2MHz
 * @note Configuration is done based on capability of the GPIO as mentioned in data sheet
 */
__attribute__((always_inline)) inline void config_OB_LED(void){
	// Set the GPIO Pin as an Output
	config_GPIO(OB_LED_PORT, OB_LED_PIN, MODE_OUT_2MHz, CNF_OUT_GP_PP);
}

/**
 * @brief Turns on-board active low LED (PC13) ON
 */
__attribute__((always_inline)) inline void set_OB_LED(void){
	// Reset the on-board active low LED GPIO
	reset_GPIO(OB_LED_PORT, OB_LED_PIN);
}

/**
 * @brief Turns on-board active low LED (PC13) OFF
 */
__attribute__((always_inline)) inline void reset_OB_LED(void){
	// Reset the on-board active low LED GPIO
	set_GPIO(OB_LED_PORT, OB_LED_PIN);
}

/**
 * @brief Toggles the on-board active low LED (PC13)
 */
__attribute__((always_inline)) inline void toggle_OB_LED(void){
	// Toggle the on-board active low LED GPIO
	toggle_GPIO(OB_LED_PORT, OB_LED_PIN);
}

#endif /* __GPIO__H__ */