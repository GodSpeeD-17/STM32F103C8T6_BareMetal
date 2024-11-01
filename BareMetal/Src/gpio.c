/***************************************************************************************
 *  File: gpio.c
 *  Created on: 14/09/2024
 *  Author: shrey_shah
 ***************************************************************************************/

#include "gpio.h"

/**
 * @brief Enables Clock for respective GPIO
 * @param[in] GPIOx The GPIO Port
 */
static inline void enable_GPIO_clk(GPIO_REG_STRUCT* GPIOx){

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
static inline void disable_GPIO_clk(GPIO_REG_STRUCT* GPIOx){

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
 * @brief Configures GPIO as per input
 * @param[in] GPIOx `GPIOA`, `GPIOB`, `GPIOC`
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 * @param[in] MODEx Pin Mode `MODE_..`
 * @param[in] CNFx Pin Configuration `CNF_..`
 * @note Does not configure PC13 (On-board active low LED)
 */
void config_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx, uint8_t MODEx, uint8_t CNFx){
	
	// Enable GPIO Clock
	enable_GPIO_clk(GPIOx);

	// PINx >= 8 
	if(PINx > 7 && PINx < 16){
		// Clear Reset State (0x4 i.e Floating State)
		GPIOx->CRH.REG &= ~(uint32_t)(0xF << (4 * (PINx - 8)));
		// MODE: CRH
		GPIOx->CRH.REG |= (uint32_t)(MODEx << (4 * (PINx - 8)));
		// CONFIGURATION: Set
		GPIOx->CRH.REG |= ((uint32_t)(CNFx << ((4 * (PINx - 8)) + 2)));
	}
	// PINx <= 7
	else if (PINx <= 7){
		// Clear Reset State (0x4 i.e Floating State)
		GPIOx->CRL.REG &= ~((uint32_t)(0xF << (4 * PINx)));
		// MODE: CRL
		GPIOx->CRL.REG |= (uint32_t)(MODEx << (4 * PINx));
		// CONFIGURATION: Set
		GPIOx->CRL.REG |= ((uint32_t)(CNFx << ((4 * PINx) + 2)));
	}
	// Error Condition
	else{
		return;
	}
}

/**
 * @brief Sets a GPIO Pin HIGH
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 */
void set_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx){
	// Bit Set (Atomicity)
	GPIOx->BSRR.REG = (1 << PINx);
}

/**
 * @brief Resets a GPIO Pin LOW
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 */
void reset_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx){
	// Bit Reset (Atomicity)
	GPIOx->BRR.REG = (1 << PINx);
}

/**
 * @brief Toggles GPIO Pin
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 */
void toggle_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx){
	// Toggle the GPIO Pin
	GPIOx->ODR.REG ^= (1 << PINx);
}

/**
 * @brief Configures the on-board active low LED (PC13) as GP_OUT-PP-2MHz
 * @note Configuration is done based on capability of the GPIO as mentioned in data sheet
 */
void config_OB_LED(void){
	// Set the GPIO Pin as an Output
	config_GPIO(OB_LED_PORT, OB_LED_PIN, MODE_OUT_2MHz, CNF_OUT_GP_PP);
}

/**
 * @brief Turns on-board active low LED (PC13) ON
 */
void set_OB_LED(void){
	// Reset the on-board active low LED GPIO
	reset_GPIO(OB_LED_PORT, OB_LED_PIN);
}

/**
 * @brief Turns on-board active low LED (PC13) OFF
 */
void reset_OB_LED(void){
	// Reset the on-board active low LED GPIO
	set_GPIO(OB_LED_PORT, OB_LED_PIN);
}

/**
 * @brief Toggles the on-board active low LED (PC13)
 */
void toggle_OB_LED(void){
	// Toggle the on-board active low LED GPIO
	toggle_GPIO(OB_LED_PORT, OB_LED_PIN);
}
