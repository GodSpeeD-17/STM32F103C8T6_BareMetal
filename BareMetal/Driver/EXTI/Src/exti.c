/***************************************************************************************
 *  File: exti.c
 *  Created on: 17/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// EXTI Configuration
#include "exti.h"

// Lookup Table for IRQn
static const uint8_t EXTI_IRQn[16] = {
	EXTI0_IRQn,
	EXTI1_IRQn,
	EXTI2_IRQn,
	EXTI3_IRQn,
	EXTI4_IRQn,
	EXTI9_5_IRQn,
	EXTI9_5_IRQn,
	EXTI9_5_IRQn,
	EXTI9_5_IRQn,
	EXTI9_5_IRQn,
	EXTI15_10_IRQn,
	EXTI15_10_IRQn,
	EXTI15_10_IRQn,
	EXTI15_10_IRQn,
	EXTI15_10_IRQn,
	EXTI15_10_IRQn,
};

// Lookup Table for EXTI Source
static const exti_port_t EXTI_Source_Port[7] = {
	AF_EXTI_PORT_A, 
	AF_EXTI_PORT_B, 
	AF_EXTI_PORT_C,
	AF_EXTI_PORT_D,
	AF_EXTI_PORT_E,
	AF_EXTI_PORT_F,
	AF_EXTI_PORT_G
};

#ifdef  __OLD_GPIO_METHOD__

/**
 * @brief Configures the NVIC EXTI Source
 * @param[in] GPIOx `GPIOA`, `GPIOB`, `GPIOC`
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
void EXTI_Source_Set(GPIO_TypeDef* GPIOx, uint8_t PINx){
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
#else

/**
 * @brief Retrieves the EXTI Configuration Register based upon the Pin Number
 * @param pin Refer to `gpio_pin_t` enum
 * @return Pointer to the relevant EXTI Configuration Register
 * @note Pass only one pin at a time
 */
uint32_t* __EXTI_getPointerToAFIO_EXTICRx__(const gpio_pin_t pin){
	// Return the Register Address
	return (uint32_t *) (&AFIO->EXTICR1.REG + (__GPIO_getPin__(pin) >> 2));
}

/**
 * @brief Sets the EXTI Source Port
 * @param gpio Refer to `gpio_port_t` enum
 * @param pin Refer to `gpio_pin_t` enum
 * @param extiConfigReg Pointer to the relevant EXTI Configuration Register
 * @note Pass only one pin at a time
 */
void EXTI_Set_Source_Port(const gpio_port_t gpio, gpio_pin_t pin, uint32_t* extiConfigReg){
	// Get the Pin Number
	pin = __GPIO_getPin__(pin);
	// Wrap the pin to 0-3
	pin &= 0x03;
	// Shift to the relevant position
	pin <<= 2;
	// Set the relevant port
	*extiConfigReg &= ~(0x0F << pin);
	*extiConfigReg |= (EXTI_Source_Port[gpio] << pin);
}

/**
 * @brief Sets the EXTI Trigger Selection
 * @param pin Refer to `gpio_pin_t` enum
 * @param trigger Refer to `exti_trigger_t` enum
 */
void EXTI_Set_Trigger(const gpio_pin_t pin, const exti_trigger_t trigger){
	// Falling Edge Trigger Selection
	if(trigger & EXTI_TRIGGER_FALLING){
		EXTI->FTSR.REG |= pin;
	}
	// Rising Edge Trigger Selection
	if(trigger & EXTI_TRIGGER_RISING){
		EXTI->RTSR.REG |= pin;
	}
}

/**
 * @brief Configures the External Interrupt
 * @param gpio GPIO Port (Refer to `gpio_port_t` enum)
 * @param pin GPIO Pin (Refer to `gpio_pin_t` enum)
 * @param trigger GPIO Trigger (Refer to `exti_trigger_t` enum)
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t EXTI_Config(const gpio_port_t gpio, const gpio_pin_t pin, const exti_trigger_t trigger){
	// Check hardware compatibility
	GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpio);
	if(GPIOx == NULL){
		return DRIVER_FAIL;
	}
	// Enable AFIO Clock
	RCC_AFIO_Clk_Enable();
	// Local Variables
	gpio_pin_t pinNumber = pin;
	// EXTI Configuration Register - Instantaneous Value
	uint32_t extiConfigReg[] = {
		AFIO->EXTICR1.REG, 
		AFIO->EXTICR2.REG, 
		AFIO->EXTICR3.REG, 
		AFIO->EXTICR4.REG
	};
	uint8_t AFIOExtiCRStatus = 0x00;
	// Iterate through all the pins
	while(pinNumber){
		// Extract only one pin set from LSB
		gpio_pin_t currentPinMask = (gpio_pin_t) (pinNumber & (-pinNumber));
		uint8_t currentPin = __GPIO_getPin__(currentPinMask);
		// Update the relevant EXTI Configuration Register
		EXTI_Set_Source_Port(gpio, currentPinMask, &extiConfigReg[(currentPin >> 2)]);
		AFIOExtiCRStatus |= (0x01 << (currentPin >> 2));
		// Enable NVIC (Global) Interrupt
		NVIC_IRQ_Enable(EXTI_IRQn[currentPin]);
		// Clear the current pin from the pin number
		pinNumber &= ~currentPinMask;
	}
	// Set the Trigger Selection
	EXTI_Set_Trigger(pin, trigger);

	// Write back the modified EXTI Configuration Registers
	for(uint8_t i = 0; i < 4; i++){
		if(AFIOExtiCRStatus & (0x01 << i)){
			*(&AFIO->EXTICR1.REG + i) = extiConfigReg[i];
		}
	}
	// Enable the EXTI Interrupt
	EXTI_IRQ_Enable(pin);
	return DRIVER_SUCCESS;
}

#endif /* __OLD_GPIO_METHOD__ */