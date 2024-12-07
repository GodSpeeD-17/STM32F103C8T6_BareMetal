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
void init_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx, uint8_t MODEx, uint8_t CNFx){
    
	// Error checking for input parameters & mode - configuration mapping
	if(!ARE_GPIO_PARAMETERS_VALID(GPIOx, PINx, MODEx, CNFx) && !IS_MODE_CNF_VALID(MODEx, CNFx))
		return;

	// Local Variables
	uint32_t reg, shift, mask;

    // Enable GPIO Clock
    enable_GPIO_clk(GPIOx);

	// Alternate Function
	if((CNFx == CNF_OUT_AF_OD) || (CNFx == CNF_OUT_AF_PP))
		enable_AFIO_clk();

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
uint8_t get_init_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx){
	// Value
	uint8_t result = 0xFF;
	// Retrieve Data
	result = (uint8_t)((GPIOx->IDR.REG >> PINx) & BIT_SET);
	// Return the Value
	return result;
}

/**
 * @brief Configures the GPIO based upon gpio structure
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
void config_GPIO(gpio_config_t* GPIO_CONFIGx){
	
	// Error Check
	if(!IS_GPIO_STRUCTURE_VALID(GPIO_CONFIGx)) 
		return;
	
	// Local Variables
	uint32_t reg, shift, mask;
    // Enable GPIO Clock
    enable_GPIO_clk(GPIO_CONFIGx->GPIOx);

	// Alternate Function
	if((GPIO_CONFIGx->CNFx == CNF_OUT_AF_OD) || (GPIO_CONFIGx->CNFx == CNF_OUT_AF_PP))
		enable_AFIO_clk();

    // Determine the register, shift, and mask based on the pin number
    if (GPIO_CONFIGx->PINx <= GPIO_PIN_7){
        reg = GPIO_CONFIGx->GPIOx->CRL.REG;
        shift = GPIO_CONFIGx->PINx * 4;
        mask = 0x0F << shift;
    } 
	else if (GPIO_CONFIGx->PINx <= GPIO_PIN_15){
        reg = GPIO_CONFIGx->GPIOx->CRH.REG;
        shift = (GPIO_CONFIGx->PINx - (uint8_t)8) * 4;
        mask = 0x0F << shift;
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
    reg &= ~mask;
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
 */
uint8_t get_GPIO(gpio_config_t* GPIO_CONFIGx){
	// Result
	uint32_t result = 0xFFFFFFFF;
	// Get State
	result = (uint32_t)(GPIO_CONFIGx->GPIOx->IDR.REG & (1 << GPIO_CONFIGx->PINx));
	// Return Result
	return (uint8_t)(result >> GPIO_CONFIGx->PINx);
}
