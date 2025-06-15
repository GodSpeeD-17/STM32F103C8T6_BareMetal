/***************************************************************************************
 *  File: exti.c
 *  Created on: 17/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/
// Global Interrupt
#include "nvic.h"
// Alternate Function I/O
#include "rcc.h"
// EXTI Configuration
#include "exti.h"

// Lookup Table for IRQn
static const uint8_t EXTI_IRQn[7] = {EXTI0_IRQn, EXTI1_IRQn, EXTI2_IRQn, 
									 EXTI3_IRQn, EXTI4_IRQn, 
									 EXTI9_5_IRQn, EXTI15_10_IRQn};

/**
 * @brief Configures the NVIC EXTI Source
 * @param[in] GPIOx `GPIOA`, `GPIOB`, `GPIOC`
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
void EXTI_Source_Set(GPIO_REG_STRUCT* GPIOx, uint8_t PINx){
	// Local Variables
	uint32_t* reg = NULL;
	uint8_t temp = 0xFF, pin = ((PINx & 0x03) << 2);
	// Port based selection
	if(GPIOx == GPIOA){
		temp = AF_EXTI_PA;
	}
	else if(GPIOx == GPIOB){
		temp = AF_EXTI_PB;
	}
	else if(GPIOx == GPIOC){
		temp = AF_EXTI_PC;
	}
	// Enable Alternate Function
	RCC_AFIO_Clk_Enable();
	// Parameter Determination
	reg = AFIO_EXTI_CR_Register(PINx);
	*reg = ((*reg & ~(0x0F << pin)) | (temp << pin));
}

/**
 * @brief Configures the External Interrupt Trigger Selection
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 * @param[in] TRIGx `EXTI_TRIG_FALLING`, `EXTI_TRIG_FALLING`, `EXTI_TRIG_BOTH`
 * @note The external wakeup lines are edge triggered, no glitches must be generated on these lines
 */
void EXTI_Trigger_Set(uint8_t PINx, uint8_t TRIGx){
	// Trigger Selection
	switch (TRIGx){
		// Falling Edge 
		case EXTI_TRIG_FALLING:
			EXTI->FTSR.REG |= (1 << PINx);
		break;
		// Rising Edge 
		case EXTI_TRIG_RISING:
			EXTI->RTSR.REG |= (1 << PINx);
		break;
		// Both Edge 
		case EXTI_TRIG_BOTH:
			EXTI->RTSR.REG |= (1 << PINx);
			EXTI->FTSR.REG |= (1 << PINx);
		break;
	}
}

/**
 * @brief Configures the External Interrupt
 * @param[in] GPIOx_CONFIG GPIO Configuration Structure
 * @param[in] TRIGx `EXTI_TRIG_FALLING`, `EXTI_TRIG_RISING`, `EXTI_TRIG_BOTH`
 */
void EXTI_Config(gpio_config_t* GPIOx_CONFIG, uint8_t TRIGx){
	// Configure the GPIO
	GPIO_Config(GPIOx_CONFIG);
	// Configure the Source of Interrupt (Port Selection)
	EXTI_Source_Set(GPIOx_CONFIG->GPIO, GPIOx_CONFIG->PIN);
	// Configure the External Trigger
	EXTI_Trigger_Set(GPIOx_CONFIG->PIN, TRIGx);
	// Enable the IRQ (Remove the Mask)
	EXTI_IRQ_Enable(GPIOx_CONFIG->PIN);
	// Enable the NVIC Global Interrupt
	if(GPIOx_CONFIG->PIN <= GPIOx_PIN_4){
		NVIC_IRQ_Enable(EXTI_IRQn[GPIOx_CONFIG->PIN]);
	}
	else if(GPIOx_CONFIG->PIN <= GPIOx_PIN_9){
		NVIC_IRQ_Enable(EXTI_IRQn[5]);
	}
	else if(GPIOx_CONFIG->PIN <= GPIOx_PIN_15){
		NVIC_IRQ_Enable(EXTI_IRQn[6]);
	}
}
