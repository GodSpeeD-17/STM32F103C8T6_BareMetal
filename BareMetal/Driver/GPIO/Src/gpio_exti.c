/***************************************************************************************
 *  File: gpio_exti.c
 *  Version: v1.2
 *  Created on: 14/09/2025
 *  Author: Shrey Shah
 ***************************************************************************************/

/*********************************************** Includes ***********************************************/
#include "gpio_exti.h"

/*********************************************** MACROs ***********************************************/
#define AFIO_EXTI_REGISTER_COUNT 					((uint8_t) 4)
#define EXTI_IRQn_COUNT								((uint8_t) 16)
#define EXTI_SOURCE_PORT_COUNT						((uint8_t) 7)

/*********************************************** Lookup Tables ***********************************************/
// Lookup Table for IRQn
static const uint8_t EXTI_IRQn[EXTI_IRQn_COUNT] = {
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
static const gpio_exti_port_t EXTI_Source_Port[EXTI_SOURCE_PORT_COUNT] = {
	GPIO_EXTI_PORT_A, 
	GPIO_EXTI_PORT_B, 
	GPIO_EXTI_PORT_C,
	GPIO_EXTI_PORT_D,
	GPIO_EXTI_PORT_E,
	GPIO_EXTI_PORT_F,
	GPIO_EXTI_PORT_G
};

/*********************************************** Driver APIs ***********************************************/
/**
 * @brief Maps the EXTI Source Port to Interrupt
 * @param gpio Refer to `gpio_port_t` enum
 * @param pin Refer to `gpio_pin_t` enum
 * @param extiConfigReg Pointer to the relevant EXTI Configuration Register
 * @note Pass only one pin at a time
 */
void GPIO_EXTI_MapPort(const gpio_port_t gpio, const gpio_pin_t pin, uint32_t* extiConfigReg){
	// Get the Pin Number
	uint8_t pinMask = __GPIO_getPin__(pin);
	// Wrap the pin to 0-3
	pinMask &= 0x03;
	// Shift to the relevant position
	pinMask <<= 2;
	// Set the relevant port
	*extiConfigReg &= ~(0x0F << pinMask);
	*extiConfigReg |= (EXTI_Source_Port[gpio] << pinMask);
}

/**
 * @brief Unmaps the EXTI Source Port from Interrupt
 * @param gpio Refer to `gpio_port_t` enum
 * @param pin Refer to `gpio_pin_t` enum
 * @param extiConfigReg Pointer to the relevant EXTI Configuration Register
 * @note Pass only one pin at a time
 */
void GPIO_EXTI_UnmapPort(const gpio_port_t gpio, gpio_pin_t pin, uint32_t* extiConfigReg){
	// Get the Pin Number
	uint8_t pinMask = __GPIO_getPin__(pin);
	// Wrap the pin to 0-3
	pinMask &= 0x03;
	// Shift to the relevant position
	pinMask <<= 2;
	// Reset the relevant port
	*extiConfigReg &= ~(0x0F << pinMask);
	*extiConfigReg |= (EXTI_Source_Port[0] << pinMask);
}

/**
 * @brief Sets the EXTI Trigger Selection
 * @param pin Refer to `gpio_pin_t` enum
 * @param trigger Refer to `gpio_exti_trigger_t` enum
 */
void GPIO_EXTI_SetTrigger(const gpio_pin_t pin, const gpio_exti_trigger_t trigger){
	// Falling Edge Trigger Selection
	if(trigger & GPIO_EXTI_TRIGGER_FALLING){
		EXTI->FTSR.REG |= pin;
	}
	// Rising Edge Trigger Selection
	if(trigger & GPIO_EXTI_TRIGGER_RISING){
		EXTI->RTSR.REG |= pin;
	}
}

/**
 * @brief Resets the EXTI Trigger Selection
 * @param pin Refer to `gpio_pin_t` enum
 * @param trigger Refer to `gpio_exti_trigger_t` enum
 */
void GPIO_EXTI_ResetTrigger(const gpio_pin_t pin, const gpio_exti_trigger_t trigger){
	// Falling Edge Trigger Selection
	if(trigger & GPIO_EXTI_TRIGGER_FALLING){
		EXTI->FTSR.REG &= ~(pin);
	}
	// Rising Edge Trigger Selection
	if(trigger & GPIO_EXTI_TRIGGER_RISING){
		EXTI->RTSR.REG &= ~(pin);
	}
}

/**
 * @brief Initialize the External Interrupt
 * @param gpio GPIO Port (Refer to `gpio_port_t` enum)
 * @param pin GPIO Pin (Refer to `gpio_pin_t` enum)
 * @param trigger GPIO Trigger (Refer to `gpio_exti_trigger_t` enum)
 * @note - GPIO should be configured as Input: Floating or Pull-Up/Pull-Down
 * @note - Failing to do so may cause driver to misbehave
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t GPIO_EXTI_Init(const gpio_port_t gpio, const gpio_pin_t pin, const gpio_exti_trigger_t trigger){
	// Check hardware compatibility
	GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpio);
	if(GPIOx == NULL){
		return DRIVER_FAIL;
	}
	// TODO: Validate the pin as input pin
	// Enable AFIO Clock
	RCC_AFIO_Clk_Enable();
	// Local Variables
	gpio_pin_t pinMask = pin;
	// EXTI Configuration Register - Instantaneous Value
	uint32_t extiConfigReg[AFIO_EXTI_REGISTER_COUNT] = {
		AFIO->EXTICR1.REG,
		AFIO->EXTICR2.REG,
		AFIO->EXTICR3.REG,
		AFIO->EXTICR4.REG
	};
	uint8_t AFIOExtiCRStatus = 0x00;
	// Iterate through all the pins
	while(pinMask){
		// Extract only one pin set from LSB
		gpio_pin_t currentPinMask = (gpio_pin_t) (pinMask & (-pinMask));
		uint8_t currentPin = __GPIO_getPin__(currentPinMask);
		// Update the relevant EXTI Configuration Register
		GPIO_EXTI_MapPort(gpio, currentPinMask, &extiConfigReg[(currentPin >> 2)]);
		AFIOExtiCRStatus |= (0x01 << (currentPin >> 2));
		// Enable NVIC (Global) Interrupt
		NVIC_IRQEnable(EXTI_IRQn[currentPin]);
		// Clear the current pin from the pin number
		pinMask &= ~currentPinMask;
	}
	// Set the Trigger Selection
	GPIO_EXTI_SetTrigger(pin, trigger);
	// Write back the modified EXTI Configuration Registers
	for(uint8_t i = 0; i < AFIO_EXTI_REGISTER_COUNT; i++){
		// Write back only if modified
		if(AFIOExtiCRStatus & (0x01 << i)){
			*(&AFIO->EXTICR1.REG + i) = extiConfigReg[i];
		}
	}
	// Enable the EXTI Interrupt
	GPIO_EXTI_Enable(pin);
	// Return Success
	return DRIVER_SUCCESS;
}

/**
 * @brief Deinitialize the External Interrupt
 * @param gpio GPIO Port (Refer to `gpio_port_t` enum)
 * @param pin GPIO Pin (Refer to `gpio_pin_t` enum)
 * @param trigger GPIO Trigger (Refer to `gpio_exti_trigger_t` enum)
 * @note - GPIO should be configured as Input: Floating or Pull-Up/Pull-Down
 * @note - Failing to do so may cause driver to misbehave
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t GPIO_EXTI_Deinit(const gpio_port_t gpio, const gpio_pin_t pin, const gpio_exti_trigger_t trigger){
	// Check hardware compatibility
	GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpio);
	if(GPIOx == NULL){
		return DRIVER_FAIL;
	}
	// TODO: Validate the pin as input pin
	// Enable AFIO Clock
	RCC_AFIO_Clk_Enable();
	// Local Variables
	gpio_pin_t pinMask = pin;
	// EXTI Configuration Register - Instantaneous Value
	uint32_t extiConfigReg[AFIO_EXTI_REGISTER_COUNT] = {
		AFIO->EXTICR1.REG,
		AFIO->EXTICR2.REG,
		AFIO->EXTICR3.REG,
		AFIO->EXTICR4.REG
	};
	uint8_t AFIOExtiCRStatus = 0x00;
	// Iterate through all the pins
	while(pinMask){
		// Extract only one pin set from LSB
		gpio_pin_t currentPinMask = (gpio_pin_t) (pinMask & (-pinMask));
		uint8_t currentPin = __GPIO_getPin__(currentPinMask);
		// Update the relevant EXTI Configuration Register
		GPIO_EXTI_UnmapPort(gpio, currentPinMask, &extiConfigReg[(currentPin >> 2)]);
		AFIOExtiCRStatus |= (0x01 << (currentPin >> 2));
		// Disable NVIC (Global) Interrupt
		NVIC_IRQDisable(EXTI_IRQn[currentPin]);
		// Clear the current pin from the pin number
		pinMask &= ~currentPinMask;
	}
	// Reset the Trigger Selection
	GPIO_EXTI_ResetTrigger(pin, trigger);
	// Write back the modified EXTI Configuration Registers
	for(uint8_t i = 0; i < AFIO_EXTI_REGISTER_COUNT; i++){
		// Write back only if modified
		if(AFIOExtiCRStatus & (0x01 << i)){
			*(&AFIO->EXTICR1.REG + i) = extiConfigReg[i];
		}
	}
	// Disable the EXTI Interrupt
	GPIO_EXTI_Disable(pin);
	// Return Success
	return DRIVER_SUCCESS;
}
