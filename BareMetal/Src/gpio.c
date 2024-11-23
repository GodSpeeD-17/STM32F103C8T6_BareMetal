/***************************************************************************************
 *  File: gpio.c
 *  Created on: 14/09/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

#include "gpio.h"

/**
 * @brief Configures GPIO as per input
 * @param[in] GPIOx `GPIOA`, `GPIOB`, `GPIOC`
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 * @param[in] MODEx Pin Mode `MODE_..`
 * @param[in] CNFx Pin Configuration `CNF_..`
 * @note Do not use it to configure PA15, PB3, PB4, PC13, PC14, PC15
 */
void config_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx, uint8_t MODEx, uint8_t CNFx){
    
	// Error checking for input parameters & mode - configuration mapping
	if(!ARE_GPIO_PARAMETERS_VALID(GPIOx, PINx, MODEx, CNFx))
		return;
	else if(!IS_MODE_CNF_VALID(MODEx, CNFx))
		return;

	// Local Variables
	uint32_t reg, shift, mask;

    // Enable GPIO Clock
    enable_GPIO_clk(GPIOx);

    // Determine the register, shift, and mask based on the pin number
    if (PINx <= GPIO_PIN_7){
        reg = GPIOx->CRL.REG;
        shift = PINx * 4;
        mask = 0x0F << shift;
    } 
	else if (PINx <= GPIO_PIN_15){
        reg = GPIOx->CRH.REG;
        shift = (PINx - (uint8_t)8) * 4;
        mask = 0x0F << shift;
    }

	// Pull Up
    if (MODEx == MODE_IN && CNFx == CNF_IN_PU) {
		// Set the bit high to enable pull-up
		GPIOx->BSRR.REG |= (1 << PINx);
		// Update the Configuration Bits as Input Push-Pull
		CNFx = (uint8_t)0x02;
	} 
	// Pull Down
    else if (MODEx == MODE_IN && CNFx == CNF_IN_PD) {
		// Set the bit low to enable pull-down
		GPIOx->BRR.REG |= (1 << PINx);
		// Update the Configuration Bits as Input Push-Pull
		CNFx = (uint8_t)0x02;	
    }
	// Alternate Function
	else if((CNFx == CNF_OUT_AF_OD) || (CNFx == CNF_OUT_AF_PP))
		RCC->APB2ENR.BIT.AFIOEN = (uint8_t) 0x01;

    // Clear the current mode and configuration bits
    reg &= ~mask;
	// Update the configuration
	reg |= (uint32_t)((CNFx << (shift + 2) | MODEx << shift));

    // New value Updation
    if (PINx <= GPIO_PIN_7) {
        GPIOx->CRL.REG = reg;
    } 
	else if(PINx <= GPIO_PIN_15){
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
