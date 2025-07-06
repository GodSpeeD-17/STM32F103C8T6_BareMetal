// Header Guards
#ifndef __GPIO_CONFIG_H__
#define __GPIO_CONFIG_H__

// Register Address Mapping
#include "reg_map.h"
// Include RCC for clock enabling
#include "rcc.h"

// GPIO Configuration Structure
typedef struct {
	// GPIO Port
	// - `GPIOA`
	// - `GPIOB`
	// - `GPIOC`
	// - `GPIOD`
	GPIO_REG_STRUCT* GPIO;
	// GPIO Pin
	// - `GPIOx_PIN_XY`
	uint8_t PIN: 4;
	// GPIO Pin Mode
	// - `GPIOx_MODE_INPUT`
	// - `GPIOx_MODE_OUT_10MHz`
	// - `GPIOx_MODE_OUT_2MHz`
	// - `GPIOx_MODE_OUT_50MHz`
	uint8_t MODE: 2;
	// GPIO Pin Configuration
	// - Input Configuration:
	// `GPIOx_CNF_IN_ANALOG`, `GPIOx_CNF_IN_FLOAT`
	// `GPIOx_CNF_IN_PD`, `GPIOx_CNF_IN_PU`
	// - Output Configuration:
	// `GPIOx_CNF_OUT_GP_PP`, `GPIOx_CNF_OUT_GP_OD`
	// `GPIOx_CNF_OUT_AF_PP`, `GPIOx_CNF_OUT_AF_OD`
	uint8_t CNF: 2;
} gpio_config_t;

/**
 * @brief Enables Clock for respective GPIO
 * @param[in] GPIO The GPIO Port
 */
__STATIC_INLINE__ void GPIO_Clk_Enable(GPIO_REG_STRUCT* GPIO){
	// Enable Clock for respective GPIO
	if(GPIO == GPIOA){
		RCC->APB2ENR.REG |= RCC_APB2ENR_IOPAEN;
	}
	else if (GPIO == GPIOB){
		RCC->APB2ENR.REG |= RCC_APB2ENR_IOPBEN;
	}
	else if (GPIO == GPIOC){
		RCC->APB2ENR.REG |= RCC_APB2ENR_IOPCEN;
	}
	else if (GPIO == GPIOD){
		RCC->APB2ENR.REG |= RCC_APB2ENR_IOPDEN;
	}
	else if (GPIO == GPIOE){
		RCC->APB2ENR.REG |= RCC_APB2ENR_IOPEEN;
	}
	// Error
	else{
		return;
	}
}

/**
 * @brief Disables Clock for respective GPIO
 * @param[in] GPIO The GPIO Configuration Structure
 */
__STATIC_INLINE__ void GPIO_Clk_Disable(GPIO_REG_STRUCT* GPIO){
	// Disable Clock for respective GPIO
	if(GPIO == GPIOA){
		RCC->APB2ENR.REG &= ~RCC_APB2ENR_IOPAEN;
	}
	else if (GPIO == GPIOB){
		RCC->APB2ENR.REG &= ~RCC_APB2ENR_IOPBEN;
	}
	else if (GPIO == GPIOC){
		RCC->APB2ENR.REG &= ~RCC_APB2ENR_IOPCEN;
	}
	else if (GPIO == GPIOD){
		RCC->APB2ENR.REG &= ~RCC_APB2ENR_IOPDEN;
	}
	else if (GPIO == GPIOE){
		RCC->APB2ENR.REG &= ~RCC_APB2ENR_IOPEEN;
	}
	// Error
	else{
		return;
	}
} 

#endif /* __GPIO_CONFIG_H__ */ 