/***************************************************************************************
 *  File: gpio.c
 *  Created on: 14/09/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Dependency
#include "gpio.h"

/**
 * @brief Configures the GPIO based upon gpio structure
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
void GPIO_Config(gpio_config_t* GPIO_CONFIGx){
	// Just for safety
	if(GPIO_CONFIGx == NULL)
		return;
	// Local Variables
	uint32_t reg = 0x00, shift = 0x00;
    // Enable GPIO Clock
    GPIO_clk_enable(GPIO_CONFIGx->GPIO);
	// Alternate Function Clock
	if((GPIO_CONFIGx->CNF == GPIOx_CNF_OUT_AF_OD) || (GPIO_CONFIGx->CNF == GPIOx_CNF_OUT_AF_PP))
		AFIO_clk_enable();

    // Determine the register, shift based on the pin number
    if (GPIO_CONFIGx->PIN <= GPIOx_PIN_7){
        reg = GPIO_CONFIGx->GPIO->CRL.REG;
        shift = GPIO_CONFIGx->PIN * 4;
    } 
	else if (GPIO_CONFIGx->PIN <= GPIOx_PIN_15){
        reg = GPIO_CONFIGx->GPIO->CRH.REG;
        shift = (GPIO_CONFIGx->PIN - (uint8_t)8) * 4;
    }

	// Pull Up
    if (GPIO_CONFIGx->MODE == GPIOx_MODE_IN && GPIO_CONFIGx->CNF == GPIOx_CNF_IN_PU) {
		// Set the bit high to enable pull-up
		GPIO_CONFIGx->GPIO->BSRR.REG |= (1 << GPIO_CONFIGx->PIN);
		// Update the Configuration Bits as Input Push-Pull
		GPIO_CONFIGx->CNF = (uint8_t)0x02;
	} 
	// Pull Down
    else if (GPIO_CONFIGx->MODE == GPIOx_MODE_IN && GPIO_CONFIGx->CNF == GPIOx_CNF_IN_PD) {
		// Set the bit low to enable pull-down
		GPIO_CONFIGx->GPIO->BRR.REG |= (1 << GPIO_CONFIGx->PIN);
		// Update the Configuration Bits as Input Push-Pull
		GPIO_CONFIGx->CNF = (uint8_t)0x02;	
    }

    // Clear the current mode and configuration bits
    reg &= ~(0x0F << shift);
	// Update the configuration
	reg |= (uint32_t)((GPIO_CONFIGx->CNF << (shift + 2) | GPIO_CONFIGx->MODE << shift));

    // New value Updation
    if (GPIO_CONFIGx->PIN <= GPIOx_PIN_7) {
        GPIO_CONFIGx->GPIO->CRL.REG = reg;
    } 
	else if(GPIO_CONFIGx->PIN <= GPIOx_PIN_15){
        GPIO_CONFIGx->GPIO->CRH.REG = reg;
    } 
}

/**
 * @brief Retrieves the state of GPIO Pin
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 * @param[out] pin_state Pin State
 */
uint8_t GPIO_Get(gpio_config_t* GPIO_CONFIGx){
	// Result
	uint32_t pin_state = 0xFFFFFFFF;
	// Get State
	pin_state = (uint32_t)(GPIO_CONFIGx->GPIO->IDR.REG & (1 << GPIO_CONFIGx->PIN));
	// Return Result
	return (uint8_t)(pin_state >> GPIO_CONFIGx->PIN);
}
