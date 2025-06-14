// Header Guards
#ifndef __PWM_CONFIG_H__
#define __PWM_CONFIG_H__

// Register Mapping
#include "reg_map.h"

// Timer GPIO Mapping Configuration Structure
typedef struct {
	// GPIO
	// - `GPIOA`
	// - `GPIOB`
	// - `GPIOC`
	// - `GPIOD`
	GPIO_REG_STRUCT* GPIO;
	// GPIO Pin
	// - `GPIO_PIN_0`
	// ....
	// - `GPIO_PIN_15`
	uint8_t PIN;
} timer_gpio_mapping_t;

/**
 * @brief Index for Lookup Table for GPIO Mapping against Timer & Channel
 * @param TIMx General Purpose Timer
 * @return Index for Lookup Table for GPIO Mapping against Timer & Channel
 */
__INLINE__ uint8_t PWM_Get_TIM_Index(TIM_REG_STRUCT* TIMx){
	// Row Index for Lookup Table for GPIO Mapping against Timer & Channel 
	return ((TIMx - TIM2) >> 10);
}

#endif /* __PWM_CONFIG_H__ */