// Main Header
#include "main.h"

// Global Variables
volatile uint8_t count = 0x00;
volatile uint8_t configured = 0x00;
volatile uint8_t sync_time = 0x00;
volatile uint64_t last_ticks = 0x00;

// Configure External LED for Falling Edge Interrupt
gpio_config_t led_falling_config = {
	.GPIOx = LED_FALLING_PORT,
	.PINx = LED_FALLING_PIN,
	.MODEx = MODE_OUT_10MHz,
	.CNFx = CNF_OUT_GP_PP,
};

// Configure External LED for Rising Edge Interrupt
gpio_config_t led_rising_config = {
	.GPIOx = LED_RISING_PORT,
	.PINx = LED_RISING_PIN,
	.MODEx = MODE_OUT_10MHz,
	.CNFx = CNF_OUT_GP_PP,
};

// Configure Push Button for Rising Edge Interrupt
gpio_config_t pb_rising_config = {
	.GPIOx = PB_RISING_PORT,
	.PINx = PB_RISING_PIN,
	.MODEx = MODE_IN,
	.CNFx = CNF_IN_PD,
};
exti_config_t exti_rising_config = {
	.GPIO_CONFIGx = &pb_rising_config,
	.TRIGx = EXTI_TRIG_RISING,
	.IRQn = PB_RISING_IRQ_NUM,
};

// Configure Push Button for Falling Edge Interrupt
gpio_config_t pb_falling_config = {
	.GPIOx = PB_FALLING_PORT,
	.PINx = PB_FALLING_PIN,
	.MODEx = MODE_IN,
	.CNFx = CNF_IN_PU,
};
exti_config_t exti_falling_config = {
	.GPIO_CONFIGx = &pb_falling_config,
	.TRIGx = EXTI_TRIG_FALLING,
	.IRQn = PB_FALLING_IRQ_NUM,
};

// Main Entry Point for User Code
int main(void){
	
	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);

	// SysTick Timer (1ms)
	config_SysTick(CoreClock/1000);

	// Configure External LED for Rising Edge Interrupt
	config_GPIO(&led_rising_config);

	// Configure External LED for Falling Edge Interrupt
	config_GPIO(&led_falling_config);
	
	// Configure On-board Active Low LED
	config_OB_LED();
	reset_OB_LED();

	// Configure Push Button for Rising Edge Interrupt
	config_EXTI(&exti_rising_config);

	// Configure Push Button for Falling Edge Interrupt
	config_EXTI(&exti_falling_config);

	// Infinite Loop
	while(1){

		// Updates the LED initial state upon Interrupt
		update_configuration();

		// Synchronize Time for Delay
		if(sync_time){
			// Get Current Number of Ticks
			last_ticks = get_curr_ticks();
			// Update Variable
			sync_time = 0x00;
		}

		// Customized Delay for LED Blinking
		if(get_curr_ticks() - last_ticks >= LED_DELAY_MS){
			// Already reference configured
			if(configured){
				// Toggle Decision
				if(count){
					// GPIO Toggle
					toggle_GPIO(&led_rising_config);
					toggle_GPIO(&led_falling_config);
				}
			}
			// Update the reference
			last_ticks = get_curr_ticks();
		}
		
		// Delay
		SysTick_delay_ms(LOOP_DELAY_MS);
	}
	
	// Return Value
	return 0;
}

/**
 * @brief IRQ Handler for Px5 - Px9
 */
void EXTI9_5_IRQHandler(void){

	// On-board LED Toggle
	toggle_OB_LED();

	// Push Button Rising Edge Interrupt bit pending
	if(get_EXTI_pend(pb_rising_config.PINx)){
		// Increment Count
		count++;
		// Boundary
		if(count > (uint8_t) 0x03)
			count = 0x00;
		// Acknowledge EXTI Flag
		clear_EXTI_pend(pb_rising_config.PINx);
	}

	// Push Button Falling Edge Interrupt bit pending
	if(get_EXTI_pend(pb_falling_config.PINx)){
		// Decrement Count
		count--;
		// Boundary
		if(count > (uint8_t) 0x03)
			count = 0x03;
		// Acknowledge EXTI Flag
		clear_EXTI_pend(pb_falling_config.PINx);
	}

	// Reset Configuration
	configured = 0x00;
	// Synchronize Time
	sync_time = 0x01;
}

/*
// Basic Individual LED Toggle
void EXTI9_5_IRQHandler(void){

	// Push Button Rising Edge Interrupt bit pending
	if(get_EXTI_pend(PB_RISING_PIN)){
		// Acknowledge EXTI Flag
		clear_EXTI_pend(PB_RISING_PIN);
		// Toggle LED
		toggle_GPIO(LED_RISING_PORT, LED_RISING_PIN);
	} 

	// Push Button Falling Edge Interrupt bit pending
	if(get_EXTI_pend(PB_FALLING_PIN)){
		// Acknowledge EXTI Flag
		clear_EXTI_pend(PB_FALLING_PIN);
		// Toggle LED
		toggle_GPIO(LED_FALLING_PORT, LED_FALLING_PIN);
	} 
}
*/