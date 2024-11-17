/***************************************************************************************
 *  File: gpio.c
 *  Created on: 14/09/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

#include "gpio.h"

/**
 * @brief Enables Clock for respective GPIO
 * @param[in] GPIOx The GPIO Port
 */
void enable_GPIO_clk(GPIO_REG_STRUCT* GPIOx){

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
void disable_GPIO_clk(GPIO_REG_STRUCT* GPIOx){

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
 * @note Do not use it to configure PB3, PB4, PC13, PC14, PC15
 */
void config_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx, uint8_t MODEx, uint8_t CNFx){
    uint32_t reg, shift, mask;

    // Enable GPIO Clock
    enable_GPIO_clk(GPIOx);

    // Determine the register, shift, and mask based on the pin number
    if (PINx < (uint8_t) 8){
        reg = GPIOx->CRL.REG;
        shift = PINx * 4;
        mask = 0x0F << shift;
    } 
	else if (PINx < (uint8_t) 16){
        reg = GPIOx->CRH.REG;
        shift = (PINx - 8) * 4;
        mask = 0x0F << shift;
    }
	// Error
	else
		return;

    // Handle input mode and configuration (pull-up or pull-down)
    if (MODEx == MODE_IN) {
        // Input mode with pull-up or pull-down
        if (CNFx == CNF_IN_PU) {
            // Set pin to pull-up
            GPIOx->BSRR.REG |= (1 << PINx);  // Set the pin high to enable pull-up
			// Wait
			while(!(GPIOx->ODR.REG & (1 << PINx)));
        } 
        else if (CNFx == CNF_IN_PD) {
            // Set pin to pull-down
            GPIOx->BRR.REG |= (1 << PINx);   // Set the pin low to enable pull-down
			// Wait
			while((GPIOx->ODR.REG & (1 << PINx)));
        }
		// Update the Configuration Bits
		CNFx = CNF_IN_PU_PD;
    }

    // Clear the current mode and configuration bits
    reg &= ~mask;
	// Update the configuration
	reg |= ((CNFx << (shift + 2) | MODEx << shift));

    // New value Updation
    if (PINx < (uint8_t) 8) {
        GPIOx->CRL.REG = reg;
    } 
	else {
        GPIOx->CRH.REG = reg;
    }
}

/**
 * @brief Gets the status of GPIO Pin
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 * @returns `BIT_SET`, `BIT_RESET`
 */
uint8_t get_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx){
	// Value
	uint8_t result = 0xFF;
	// Retrieve Data
	result = (uint8_t)((GPIOx->IDR.REG >> PINx) & BIT_SET);
	// Return the Value
	return result;
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
