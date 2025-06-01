/***************************************************************************************
 *  File: gpio.c
 *  Created on: 14/09/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Dependency
#include "gpio.h"
// Include RCC for clock enabling
#include "rcc.h"

/**
 * @brief Configures the GPIO based upon gpio structure
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 */
void GPIO_Config(gpio_config_t* GPIO_CONFIGx){
	
    // GPIO Clock
    GPIO_Clk_Enable(GPIO_CONFIGx->GPIO);
	// Alternate Function Clock
	if((GPIO_CONFIGx->CNF == GPIOx_CNF_OUT_AF_PP) || (GPIO_CONFIGx->CNF == GPIOx_CNF_OUT_AF_OD))
		RCC_AFIO_Clk_Enable();
    
	// Determine the register, shift based on the pin number
	uint32_t reg = 0x00, shift = 0x00;
    if (GPIO_CONFIGx->PIN <= GPIOx_PIN_7){
        reg = GPIO_CONFIGx->GPIO->CRL.REG;
        shift = GPIO_CONFIGx->PIN << 2;
    }
	else if (GPIO_CONFIGx->PIN <= GPIOx_PIN_15){
        reg = GPIO_CONFIGx->GPIO->CRH.REG;
        shift = (GPIO_CONFIGx->PIN & 0x07) << 2;
    }

	// Input Mode Configuration
	if(GPIO_CONFIGx->MODE == GPIOx_MODE_IN){
		// Pull-Up Configuration
		if(GPIO_CONFIGx->CNF == GPIOx_CNF_IN_PU){
			// Set the bit high to enable pull-up
			GPIO_CONFIGx->GPIO->BSRR.REG |= (1 << GPIO_CONFIGx->PIN);
		}
		// Pull-Down Configuration
		else if (GPIO_CONFIGx->CNF == GPIOx_CNF_IN_PD){
			// Reset the bit to enable pull-down
			GPIO_CONFIGx->GPIO->BRR.REG |= (1 << GPIO_CONFIGx->PIN);
		}
		// Update the Configuration Bits as Input Push-Pull
		GPIO_CONFIGx->CNF = 0x02;
	}

    // Clear the current mode and configuration bits
    reg &= ~(0x0F << shift);
	// Update the configuration
	reg |= (uint32_t)((GPIO_CONFIGx->CNF << (shift + 2) | GPIO_CONFIGx->MODE << shift));

    // Register Updation
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
 * @returns Pin State
 */
uint8_t GPIO_Get(gpio_config_t* GPIO_CONFIGx){
	// Pin State
	uint32_t pin_state = 0xFFFFFFFF;
	uint8_t result = 0x00; // Safety
	// Get State
	pin_state = (GPIO_CONFIGx->GPIO->IDR.REG & (0x01 << GPIO_CONFIGx->PIN));
	// Shift the pin state to the right based on the pin number
	pin_state >>= GPIO_CONFIGx->PIN;
	// Convert to uint8_t
	result = (uint8_t)pin_state;
	// Return Result
	return result;
}

/**
 * @brief Configures On-board LED
 * @note This function configures the on-board LED (OB_LED) for output mode at 2MHz
 *       with general-purpose push-pull configuration.
 * @note The on-board LED is active-low, meaning it turns ON when the pin is set to LOW.
 */
void OB_LED_Config(void){
	// On-board LED Configuration
	gpio_config_t OB_LED_Configuration = {
		.GPIO = OB_LED_PORT,
		.PIN = OB_LED_PIN,
		.MODE = GPIOx_MODE_OUT_2MHz,	// Refer RM008
		.CNF = GPIOx_CNF_OUT_GP_PP,
	};
	// Configure the On-board LED
	GPIO_Config(&OB_LED_Configuration);
	// Set the On-board LED to LOW (Active-Low)
	OB_LED_Reset();
}
