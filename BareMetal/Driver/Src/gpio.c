/***************************************************************************************
 *  File: gpio.c
 *  Created on: 14/09/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

#include "gpio.h"

/**
 * @brief Configures the GPIO based upon gpio structure
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
void config_GPIO(gpio_config_t* GPIO_CONFIGx){
	
	// Error Check
	if(!IS_GPIO_STRUCTURE_VALID(GPIO_CONFIGx)) 
		return;
	
	// Local Variables
	uint32_t reg = 0x00, shift = 0x00;
    // Enable GPIO Clock
    enable_GPIO_clk(GPIO_CONFIGx->GPIOx);
	// Alternate Function Clock
	if((GPIO_CONFIGx->CNFx == CNF_OUT_AF_OD) || (GPIO_CONFIGx->CNFx == CNF_OUT_AF_PP))
		enable_AFIO_clk();

    // Determine the register, shift based on the pin number
    if (GPIO_CONFIGx->PINx <= GPIO_PIN_7){
        reg = GPIO_CONFIGx->GPIOx->CRL.REG;
        shift = GPIO_CONFIGx->PINx * 4;
    } 
	else if (GPIO_CONFIGx->PINx <= GPIO_PIN_15){
        reg = GPIO_CONFIGx->GPIOx->CRH.REG;
        shift = (GPIO_CONFIGx->PINx - (uint8_t)8) * 4;
    }

	// Pull Up
    if (GPIO_CONFIGx->MODEx == MODE_IN && GPIO_CONFIGx->CNFx == CNF_IN_PU) {
		// Set the bit high to enable pull-up
		GPIO_CONFIGx->GPIOx->BSRR.REG |= (1 << GPIO_CONFIGx->PINx);
		// Update the Configuration Bits as Input Push-Pull
		GPIO_CONFIGx->CNFx = (uint8_t)0x02;
	} 
	// Pull Down
    else if (GPIO_CONFIGx->MODEx == MODE_IN && GPIO_CONFIGx->CNFx == CNF_IN_PD) {
		// Set the bit low to enable pull-down
		GPIO_CONFIGx->GPIOx->BRR.REG |= (1 << GPIO_CONFIGx->PINx);
		// Update the Configuration Bits as Input Push-Pull
		GPIO_CONFIGx->CNFx = (uint8_t)0x02;	
    }

    // Clear the current mode and configuration bits
    reg &= ~(0x0F << shift);
	// Update the configuration
	reg |= (uint32_t)((GPIO_CONFIGx->CNFx << (shift + 2) | GPIO_CONFIGx->MODEx << shift));

    // New value Updation
    if (GPIO_CONFIGx->PINx <= GPIO_PIN_7) {
        GPIO_CONFIGx->GPIOx->CRL.REG = reg;
    } 
	else if(GPIO_CONFIGx->PINx <= GPIO_PIN_15){
        GPIO_CONFIGx->GPIOx->CRH.REG = reg;
    } 
}

/**
 * @brief Retrieves the state of GPIO Pin
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 * @param[out] pin_state Pin State
 */
uint8_t get_GPIO(gpio_config_t* GPIO_CONFIGx){
	// Result
	uint32_t pin_state = 0xFFFFFFFF;
	// Get State
	pin_state = (uint32_t)(GPIO_CONFIGx->GPIOx->IDR.REG & (1 << GPIO_CONFIGx->PINx));
	// Return Result
	return (uint8_t)(pin_state >> GPIO_CONFIGx->PINx);
}
