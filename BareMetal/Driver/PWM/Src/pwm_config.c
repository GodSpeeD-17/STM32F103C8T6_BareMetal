// Library
#include "pwm_config.h"

// Test Case
#ifdef REVERSE_TIMER_MAPPING

// Timer based GPIO Mapping Configuration Structure
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

// TIMx Channel 1 lookup table -> GPIO Mapping
static const timer_gpio_mapping_t tim_ch1_lookup[3] = {
	// TIM2_CH1: PA0
	{GPIOA, GPIOx_PIN_0},
	// TIM3_CH1: PA6
	{GPIOA, GPIOx_PIN_6},
	// TIM4_CH1: PB6
	{GPIOB, GPIOx_PIN_6}
};

// TIMx Channel 2 lookup table -> GPIO Mapping
static const timer_gpio_mapping_t tim_ch2_lookup[3] = {
	// TIM2_CH2: PA1
	{GPIOA, GPIOx_PIN_1},
	// TIM3_CH2: PA7
	{GPIOA, GPIOx_PIN_7},
	// TIM4_CH2: PB7
	{GPIOB, GPIOx_PIN_7}
};

// TIMx Channel 3 lookup table -> GPIO Mapping
static const timer_gpio_mapping_t tim_ch3_lookup[3] = {
	// TIM2_CH3: PA2
	{GPIOA, GPIOx_PIN_2},
	// TIM3_CH3: PB0
	{GPIOB, GPIOx_PIN_0},
	// TIM4_CH3: PB8
	{GPIOB, GPIOx_PIN_8}
};

// TIMx Channel 4 lookup table -> GPIO Mapping
static const timer_gpio_mapping_t tim_ch4_lookup[3] = {
	// TIM2_CH4: PA3
	{GPIOA, GPIOx_PIN_3},
	// TIM3_CH4: PB1
	{GPIOB, GPIOx_PIN_1},
	// TIM4_CH4: PB9
	{GPIOB, GPIOx_PIN_9}
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

#endif /* REVERSE_TIMER_MAPPING */

// GPIO based Timer Mapping Configuration Structure
typedef struct {
	// Timer
	// - `TIM2`
	// - `TIM3`
	// - `TIM4`
	TIM_REG_STRUCT* TIM;
	// Timer Channel
	// - `TIMx_CHANNEL_1`
	// - `TIMx_CHANNEL_2`
	// - `TIMx_CHANNEL_3`
	// - `TIMx_CHANNEL_4`
	uint8_t channel;
} gpio_timer_mapping_t;

// GPIOA based Timer Mapping Lookup Table
static const gpio_timer_mapping_t gpioa_pin_map[] = {
	[0]  = {TIM2, TIMx_CHANNEL_1},  // PA0
	[1]  = {TIM2, TIMx_CHANNEL_2},  // PA1
	[2]  = {TIM2, TIMx_CHANNEL_3},  // PA2
	[3]  = {TIM2, TIMx_CHANNEL_4},  // PA3
	[6]  = {TIM3, TIMx_CHANNEL_1},  // PA6
	[7]  = {TIM3, TIMx_CHANNEL_2},  // PA7
	[8]  = {TIM1, TIMx_CHANNEL_1},  // PA8
	[9]  = {TIM1, TIMx_CHANNEL_2},  // PA9
	[10] = {TIM1, TIMx_CHANNEL_3},  // PA10
	[11] = {TIM1, TIMx_CHANNEL_4}   // PA11
};

// GPIOB based Timer Mapping Lookup Table
static const gpio_timer_mapping_t gpiob_pin_map[] = {
	[0] = {TIM3, TIMx_CHANNEL_3},   // PB0
	[1] = {TIM3, TIMx_CHANNEL_4},   // PB1
	[6] = {TIM4, TIMx_CHANNEL_1},   // PB6
	[7] = {TIM4, TIMx_CHANNEL_2},   // PB7
	[8] = {TIM4, TIMx_CHANNEL_3},   // PB8
	[9] = {TIM4, TIMx_CHANNEL_4}    // PB9
};

/**
 * @brief Timer Mapping based on GPIO Configuration
 * @param gpio GPIO Configuration Structure
 * @param timer_cfg Timer Configuration Structure
 * @return - 0: Failure
 * @return - 1: Success
 * @note This function retrieves the Timer Mapping for a given GPIO configuration 
 */
uint8_t PWM_Get_TIM_From_GPIO(const gpio_config_t* gpio, timer_config_t* timer_cfg){
	// Local Variables
	const gpio_timer_mapping_t* map = NULL;
	uint8_t map_size = 0;
	// GPIO Port
	if(gpio->GPIO == GPIOA){
		map = gpioa_pin_map;
		map_size = (sizeof(gpioa_pin_map)/sizeof(map[0]));
	}
	else if (gpio->GPIO == GPIOB){
		map = gpiob_pin_map;
		map_size = (sizeof(gpiob_pin_map)/sizeof(map[0]));
	}
	// Unsupported GPIO Port
	else
		return 0;
	
	// Provide Timer Details against GPIO
	if(gpio->PIN < map_size && map[gpio->PIN].TIM != NULL) {
		timer_cfg->TIM = map[gpio->PIN].TIM;
		timer_cfg->channel = map[gpio->PIN].channel;
		return 1;
	}
	return 0;
}

/**
 * @brief Default PWM Configuration
 * @param PWM_CONFIG Pointer to PWM Configuration Structure
 */
void PWM_Default_Configuration(pwm_config_t* PWM_CONFIG){
	// Frequency: 10kHz 
	PWM_CONFIG->freq_Hz = FREQ_10kHz;
	// Normal PWM Mode
	PWM_CONFIG->mode = PWM_MODE_NORMAL;
	// Defines "Active" as Logic High
	PWM_CONFIG->polarity = PWM_CHx_POL_ACTIVE_HIGH;
	// Enable PWM Channel Preload (Buffered Value for avoiding glitch)
	PWM_CONFIG->preload = PWM_CHx_PRELOAD_ENABLE;
	// Minimum Duty Cycle
	PWM_CONFIG->duty_cycle = PWM_MIN_DUTY_CYCLE;
	// Set the GPIO Mode to Output
	PWM_CONFIG->GPIOx_CONFIG.MODE = GPIOx_MODE_OUT_10MHz;
	// Set the GPIO Configuration to Alternate Function Push-Pull
	PWM_CONFIG->GPIOx_CONFIG.CNF = GPIOx_CNF_OUT_AF_PP;
}
