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
 * @note Does not configure PC13, PC14, PC15
 */
void config_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx, uint8_t MODEx, uint8_t CNFx){
	
	// Enable GPIO Clock
	enable_GPIO_clk(GPIOx);

	// PINx >= 8 
	if(PINx > 7 && PINx < 16){
		// Return on PC13, PC14, PC15
		if((GPIOx == GPIOC) && (PINx > (uint8_t)12))
			return;
		// Input Mode
		if(MODEx == MODE_IN){
			// Pull Up
			if(CNFx == CNF_IN_PU){
				// Output Data Register Corresponding Bit Set
				GPIOx->BSRR.REG |= (BIT_SET << PINx);
			}
			// Pull Down
			else if(CNFx == CNF_IN_PD){
				// Output Data Register Corresponding Bit Reset
				GPIOx->BRR.REG |= (BIT_SET << PINx);
			}
			// Clear Reset State (0x04 i.e Floating State)
			GPIOx->CRH.REG &= ~(uint32_t)(0x0F << (4 * (PINx - 8)));
			// MODE + CONFIGURATION
			GPIOx->CRH.REG |= (uint32_t)((MODEx << (4 * (PINx - 8))) | (CNF_IN_PU_PD << ((4 * (PINx - 8)) + 2)));
		}
		else{
			// Clear Reset State (0x04 i.e Floating State)
			GPIOx->CRH.REG &= ~(uint32_t)(0x0F << (4 * (PINx - 8)));
			// MODE + CONFIGURATION
			GPIOx->CRH.REG |= (uint32_t)((MODEx << (4 * (PINx - 8))) | (CNFx << ((4 * (PINx - 8)) + 2)));
		}
	}
	// PINx <= 7
	else if (PINx <= 7){
		// Input Mode
		if(MODEx == MODE_IN){
			// Pull Up
			if(CNFx == CNF_IN_PU){
				// Output Data Register Corresponding Bit Set
				GPIOx->BSRR.REG |= (BIT_SET << PINx);
			}
			// Pull Down
			else if(CNFx == CNF_IN_PD){
				// Output Data Register Corresponding Bit Reset
				GPIOx->BRR.REG |= (BIT_SET << PINx);
			}
			// Clear Reset State (0x04 i.e Floating State)
			GPIOx->CRH.REG &= ~(uint32_t)(0x0F << (4 * (PINx - 8)));
			// MODE + CONFIGURATION
			GPIOx->CRH.REG |= (uint32_t)((MODE_IN << (4 * (PINx - 8))) | (CNF_IN_PU_PD << ((4 * (PINx - 8)) + 2)));
		}
		else{
			// Clear Reset State (0x04 i.e Floating State)
			GPIOx->CRL.REG &= ~((uint32_t)(0x0F << (4 * PINx)));
			// MODE + CONFIGURATION
			GPIOx->CRL.REG |= (uint32_t)((MODEx << (4 * PINx)) | (CNFx << ((4 * PINx) + 2)));
		}
	}
	// Error Condition
	else{
		return;
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
