/***************************************************************************************
 *  File: gpio.c
 *  Created on: 14/09/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Dependency
#include "gpio.h"

// On-board LED Configuration
static const gpio_config_t OB_LED_Configuration = {
	.GPIO = OB_LED_PORT,
	.PIN = OB_LED_PIN,
	.MODE = GPIOx_MODE_OUT_2MHz,	// Refer RM008
	.CNF = GPIOx_CNF_OUT_GP_PP,
};

// Determine the register, shift based on the pin number
static volatile uint32_t reg = 0x00; 
static volatile uint32_t shift = 0x00;

/**
 * @brief Configures the GPIO based upon gpio structure
 * @param[in] GPIOx_CONFIG GPIO Configuration Structure
 */
void GPIO_Config(gpio_config_t* GPIOx_CONFIG){
	// GPIO Clock
	GPIO_Clk_Enable(GPIOx_CONFIG->GPIO);
	// Alternate Function Clock
	if((GPIOx_CONFIG->CNF == GPIOx_CNF_OUT_AF_PP) || (GPIOx_CONFIG->CNF == GPIOx_CNF_OUT_AF_OD)){
		RCC_AFIO_Clk_Enable();
	}
	
	if (GPIOx_CONFIG->PIN <= GPIOx_PIN_7){
		reg = GPIOx_CONFIG->GPIO->CRL.REG;
		shift = GPIOx_CONFIG->PIN << 2;
	}
	else if (GPIOx_CONFIG->PIN <= GPIOx_PIN_15){
		reg = GPIOx_CONFIG->GPIO->CRH.REG;
		shift = (GPIOx_CONFIG->PIN & 0x07) << 2;
	}

	// Input Mode Configuration
	if(GPIOx_CONFIG->MODE == GPIOx_MODE_IN){
		// Pull-Up Configuration
		if(GPIOx_CONFIG->CNF == GPIOx_CNF_IN_PU){
			// Set the bit high to enable pull-up
			GPIOx_CONFIG->GPIO->BSRR.REG |= (1 << GPIOx_CONFIG->PIN);
		}
		// Pull-Down Configuration
		else if (GPIOx_CONFIG->CNF == GPIOx_CNF_IN_PD){
			// Reset the bit to enable pull-down
			GPIOx_CONFIG->GPIO->BRR.REG |= (1 << GPIOx_CONFIG->PIN);
		}
		// Update the Configuration Bits as Input Push-Pull
		GPIOx_CONFIG->CNF = 0x02;
	}

	// Clear the current mode and configuration bits
	reg &= ~(0x0F << shift);
	// Update the configuration
	reg |= (GPIOx_CONFIG->CNF << (shift + 2) | GPIOx_CONFIG->MODE << shift);

	// Register Updation
	if (GPIOx_CONFIG->PIN <= GPIOx_PIN_7) {
		GPIOx_CONFIG->GPIO->CRL.REG = reg;
	} 
	else if(GPIOx_CONFIG->PIN <= GPIOx_PIN_15){
		GPIOx_CONFIG->GPIO->CRH.REG = reg;
	} 
}

/**
 * @brief De-configures the GPIO based upon gpio structure
 * @param[in] GPIOx_CONFIG GPIO Configuration Structure
 */
void GPIO_DeConfig(gpio_config_t* GPIOx_CONFIG){
	// Determine the register, shift based on the pin number
	if (GPIOx_CONFIG->PIN <= GPIOx_PIN_7){
		reg = GPIOx_CONFIG->GPIO->CRL.REG;
		shift = GPIOx_CONFIG->PIN << 2;
	}
	else if (GPIOx_CONFIG->PIN <= GPIOx_PIN_15){
		reg = GPIOx_CONFIG->GPIO->CRH.REG;
		shift = (GPIOx_CONFIG->PIN & 0x07) << 2;
	}

	// Input Mode Configuration
	if(GPIOx_CONFIG->MODE == GPIOx_MODE_IN){
		// Reset the bit
		GPIOx_CONFIG->GPIO->BRR.REG |= (1 << GPIOx_CONFIG->PIN);
	}

	// Clear the current mode and configuration bits
	reg &= ~(0x0F << shift);
	// Reset the configuration
	reg |= (0x04 << shift);

	// Register Updation
	if (GPIOx_CONFIG->PIN <= GPIOx_PIN_7) {
		GPIOx_CONFIG->GPIO->CRL.REG = reg;
	} 
	else if(GPIOx_CONFIG->PIN <= GPIOx_PIN_15){
		GPIOx_CONFIG->GPIO->CRH.REG = reg;
	}
}

/**
 * @brief Retrieves the state of GPIO Pin
 * @param[in] GPIOx_CONFIG GPIO Configuration Structure
 * @returns Pin State
 */
uint8_t GPIO_Get_State(gpio_config_t* GPIOx_CONFIG){
	// Pin State
	reg = 0x00; 
	shift = GPIOx_CONFIG->PIN;
	// Get State
	reg = (GPIOx_CONFIG->GPIO->IDR.REG);
	reg >>= shift;
	// Shift the pin state to the right based on the pin number
	reg &= 0x01;
	// Return Result
	return (uint8_t) reg;
}

/**
 * @brief Configures On-board LED
 * @note This function configures the on-board LED (OB_LED) for output mode at 2MHz
 *       with general-purpose push-pull configuration.
 * @note The on-board LED is active-low, meaning it turns ON when the pin is set to LOW.
 */
void OB_LED_Config(void){
	// Configure the On-board LED
	GPIO_Config(&OB_LED_Configuration);
	// Set the On-board LED to LOW (Active-Low)
	OB_LED_Reset();
}
