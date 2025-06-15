// Library
#include "pwm_config.h"

// Common Timer GPIO Mapping Lookup Table
static const timer_gpio_mapping_t tim_gpio_map[3][4] = {
	// TIM2
	{
		// TIM2_CH1: PA0
		{GPIOA, GPIOx_PIN_0},
		// TIM2_CH2: PA1
		{GPIOA, GPIOx_PIN_1},
		// TIM2_CH3: PA2
		{GPIOA, GPIOx_PIN_2},
		// TIM2_CH4: PA3
		{GPIOA, GPIOx_PIN_3},
	},
	// TIM3
	{
		// TIM3_CH1: PA6
		{GPIOA, GPIOx_PIN_6},
		// TIM3_CH2: PA7
		{GPIOA, GPIOx_PIN_7},
		// TIM3_CH3: PB0
		{GPIOB, GPIOx_PIN_0},
		// TIM3_CH4: PB1
		{GPIOB, GPIOx_PIN_1}
	},
	// TIM4
	{
		// TIM4_CH1: PB6
		{GPIOB, GPIOx_PIN_6},
		// TIM4_CH2: PB7
		{GPIOB, GPIOx_PIN_7},
		// TIM4_CH3: PB8
		{GPIOB, GPIOx_PIN_8},
		// TIM4_CH4: PB9
		{GPIOB, GPIOx_PIN_9}
	}
};

/**
 * @brief Retrieve the GPIO mapping for a given General Purpose Timer
 * @param TIMx_CONFIG General Purpose Timer Configuration Structure
 * @param GPIOx_CONFIG GPIO Configuration Structure 
 */
void PWM_Get_GPIO_Mapping(const timer_config_t* TIMx_CONFIG, gpio_config_t* GPIOx_CONFIG){
	// Get the row tim_index of the timer
	uint8_t tim_index = ((((uint32_t)(TIMx_CONFIG->TIM)) - ((uint32_t)(TIM2))) >> 10);
	// Count Trailing Zeros to get the channel_index tim_index
	uint8_t channel_index = __builtin_ctz(TIMx_CONFIG->channel);
	// Load the GPIO
	GPIOx_CONFIG->GPIO = tim_gpio_map[tim_index][channel_index].GPIO;
	// Load the GPIO Pin
	GPIOx_CONFIG->PIN = tim_gpio_map[tim_index][channel_index].PIN;
}

/**
 * @brief Retrieve the Timer Mapping for a given GPIO Configuration Structure
 * @param[in] TIMx_CONFIG General Purpose Timer Configuration Structure
 * @param[in] GPIOx_CONFIG GPIO Configuration Structure 
 * @returns - 0: Failure
 * @returns - 1: Success 
 */
uint8_t PWM_Get_TIM_Mapping(timer_config_t* TIMx_CONFIG, const gpio_config_t* GPIOx_CONFIG){
	// Local Variables
	uint8_t tim_index = 0, channel_index = 0;
	//  Traverse through the Timers in Lookup Table
	for(tim_index = 0; tim_index < 3; tim_index++){
		// Traverse through the Channels in Lookup Table
		for(channel_index = 0; channel_index < 4; channel_index++){
			// Check if the GPIO & PIN matches the Timer Mapping
			if((tim_gpio_map[tim_index][channel_index].GPIO == GPIOx_CONFIG->GPIO) &&
			   (tim_gpio_map[tim_index][channel_index].PIN == GPIOx_CONFIG->PIN)){
				// Set the Timer and Channel
				TIMx_CONFIG->TIM = (TIM_REG_STRUCT*)((uint32_t)TIM2 + (tim_index << 10));
				TIMx_CONFIG->channel = (1 << channel_index);
				// Exit once found
				return 1;
			}
		}
	}
	// Not Found
	return 0;
}
