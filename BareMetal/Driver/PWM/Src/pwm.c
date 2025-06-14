// Main Header
#include "pwm.h"

// Common Timer GPIO Mapping Lookup Table
static timer_gpio_mapping_t tim_gpio_map[3][4] = {
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
 * @brief Retrieve the GPIO mapping for a given timer
 * @param TIMx General Purpose Timer
 * @param GPIO_CONFIGx GPIO Configuration Structure 
 */
void PWM_Get_GPIO_Mapping(const timer_config_t* TIM_CONFIGx, gpio_config_t* GPIO_CONFIGx){
	// Get the row index of the timer
	uint8_t tim_index = PWM_Get_TIM_Index(TIM_CONFIGx->TIM);
	// Count Trailing Zeros in the channel to get the column index
	uint8_t channel_index = __builtin_ctz(TIM_CONFIGx->channel);
	// Load the GPIO
	GPIO_CONFIGx->GPIO = tim_gpio_map[tim_index][channel_index].GPIO;
	// Load the GPIO Pin
	GPIO_CONFIGx->PIN = tim_gpio_map[tim_index][channel_index].PIN;
}

/**
 * @brief Configures the GPIO based on Timer for PWM output
 * @param TIM_CONFIGx General Purpose Timer Configuration Structure
 * @param GPIO_CONFIGx GPIO Configuration Structure
 */
void PWM_GPIO_Config(const timer_config_t* TIM_CONFIGx, gpio_config_t* GPIO_CONFIGx){
	// Get the GPIO Mapping
	PWM_Get_GPIO_Mapping(TIM_CONFIGx, GPIO_CONFIGx);
	// Set the GPIO Mode to Output
	GPIO_CONFIGx->MODE = GPIOx_MODE_OUT_10MHz;
	// Set the GPIO Configuration to Alternate Function Push-Pull
	GPIO_CONFIGx->CNF = GPIOx_CNF_OUT_AF_PP;
	// Configure the GPIO
	GPIO_Config(GPIO_CONFIGx);
}

