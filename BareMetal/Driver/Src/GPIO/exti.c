/***************************************************************************************
 *  File: exti.c
 *  Created on: 17/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/
// Dependency
#include "exti.h"

/**
 * @brief Configures the NVIC EXTI Source
 * @param[in] GPIO `GPIOA`, `GPIOB`, `GPIOC`
 * @param[in] PIN Pin Number `GPIO_PIN_x`
 */
void EXTI_srcConfig(GPIO_REG_STRUCT* GPIO, uint8_t PIN){

	// Local Variables
	uint32_t reg = 0, pin = 0;
	uint8_t temp = 0xFF;

	// Port based selection
	if(GPIO == GPIOA){
		temp = AF_EXTI_PA;
	}
	else if(GPIO == GPIOB){
		temp = AF_EXTI_PB;
	}
	else if(GPIO == GPIOC){
		temp = AF_EXTI_PC;
	}
	
	// Parameter Determination
	if(PIN < GPIOx_PIN_4){
		reg = AFIO->EXTICR1.REG;
		pin = PIN * 4;
	}
	else if(PIN < GPIOx_PIN_8){
		reg = AFIO->EXTICR2.REG;
		pin = (PIN - 4) * 4;
	}
	else if(PIN < GPIOx_PIN_12){
		reg = AFIO->EXTICR3.REG;
		pin = (PIN - 8) * 4;
	}
	else if(PIN <= GPIOx_PIN_15){
		reg = AFIO->EXTICR4.REG;
		pin = (PIN - 12) * 4;
	}

	// Clear Register
	reg &= ~(0x0F << pin);
	// Set Register
	reg |= (temp << pin);

	// Enable Alternate Function
	RCC_AFIO_Clk_Enable();

	// Write to Appropriate Register 
	if(PIN < GPIOx_PIN_4){
		AFIO->EXTICR1.REG = reg;
	}
	else if(PIN < GPIOx_PIN_8){
		AFIO->EXTICR2.REG = reg;
	}
	else if(PIN < GPIOx_PIN_12){
		AFIO->EXTICR3.REG = reg;
	}
	else if(PIN <= GPIOx_PIN_15){
		AFIO->EXTICR4.REG = reg;
	}
}

/**
 * @brief Configures the External Interrupt Trigger Selection
 * @param[in] PIN Pin Number `GPIO_PIN_x`
 * @param[in] TRIGx `EXTI_TRIG_FALLING`, `EXTI_TRIG_FALLING`, `EXTI_TRIG_BOTH`
 * @note The external wakeup lines are edge triggered, no glitches must be generated on these lines
 */
void EXTI_trigConfig(uint8_t PIN, uint8_t TRIGx){
	// Trigger Selection
	switch (TRIGx){
		// Falling Edge 
		case EXTI_TRIG_FALLING:
			EXTI->FTSR.REG |= (1 << PIN);
		break;
		// Rising Edge 
		case EXTI_TRIG_RISING:
			EXTI->RTSR.REG |= (1 << PIN);
		break;
		// Both Edge 
		case EXTI_TRIG_BOTH:
			EXTI->RTSR.REG |= (1 << PIN);
			EXTI->FTSR.REG |= (1 << PIN);
		break;
		// Error
		default:
			return;
		break;
	}
}

/**
 * @brief Configures the EXTI Parameters Based Upon EXTI Configuration Structure
 * @param[in] EXTI_CONFIGx External Interrupt Configuration Structure 
 */
void EXTI_config(exti_config_t* EXTI_CONFIGx){
	// Error Check
	if(!IS_EXTI_STRUCTURE_VALID(EXTI_CONFIGx))
		return;

	// Configure the GPIO
	GPIO_Config(EXTI_CONFIGx->GPIO_CONFIGx);
	// Configure the Source of Interrupt (Port Selection)
	EXTI_srcConfig(EXTI_CONFIGx->GPIO_CONFIGx->GPIO, EXTI_CONFIGx->GPIO_CONFIGx->PIN);
	// Configure the External Trigger
	EXTI_trigConfig(EXTI_CONFIGx->GPIO_CONFIGx->PIN, EXTI_CONFIGx->TRIGx);
	// Enable the IRQ (Remove the Mask)
	EXTI_IRQ_enable(EXTI_CONFIGx->GPIO_CONFIGx->PIN);
	// Enable the NVIC Global Interrupt
	NVIC_IRQ_Enable(EXTI_CONFIGx->IRQn);
}
