// Main Header
#include "main.h"

// Status Flag
uint16_t toggle_led = EXT_LED_DELAY_MS;
uint16_t toggle_OB_led = OB_LED_DELAY_MS;

// GPIO Configuration Structure
gpio_config_t led_config = {
	.GPIOx = LED_PORT,
	.PINx = LED_PIN,
	.MODEx = MODE_OUT_10MHz,
	.CNFx = CNF_OUT_GP_PP};

// GPT Configuration Structure
gpt_config_t gpt_config = {
	.GPIO_CONFIGx = NULL,
	.GP_TIMx = GP_TIMER,
	.channel = TIMER_CHANNEL,
	.auto_reload_value = TIMER_ARR,
	.frequency_Hz = TIMER_FREQ,
	.count = TIMER_CNT,
	.cms_mode = CMS_EDGE,
	.direction = TIMx_COUNT_UP,
	.auto_reload_preload = TIMx_ARPE_ENABLE,
	.one_pulse = TIMx_OPM_DISABLE,
	.enable_IRQ = TIMx_IRQ_ENABLE,
};

// Main Entry Point for User Code
int main(void){

	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);

	// SysTick Timer (1ms)
	config_SysTick(CoreClock/1000);

	// Initialize External LED
	config_GPIO(&led_config);
	reset_GPIO(&led_config);

	// Configure OB LED
	config_OB_LED();
	set_OB_LED();

	// Enable Timer Clock
	config_GPT(&gpt_config);
	// Enable Timer
	enable_GPT(&gpt_config);

	// Infinite Loop
	while(1){
		// External LED Timer Expired
		if(!toggle_led){
			toggle_GPIO(&led_config);
			toggle_led = EXT_LED_DELAY_MS;
		}
		// On-board LED Timer Expired
		if(!toggle_OB_led){
			toggle_OB_LED();
			toggle_OB_led = OB_LED_DELAY_MS;
		}
		// Infinite Loop Short Delay
		SysTick_delay_ms(DELAY_MS);
	}
	
	// Return Value
	return 0;
}

/**
 * @brief TIM2 IRQ Handler
 * @note Will be called based upon the Timer Frequency
 */
void TIM2_IRQHandler(void){
	// GP_TIMx IRQ status
	if(get_TIMx_IRQ_status(&gpt_config)){
		// External LED Timer
		if(toggle_led)
			toggle_led--;
		// On-board LED Timer
		if(toggle_OB_led)    
			toggle_OB_led--;
		// Clear the Update Interrupt Flag
		clear_TIMx_IRQ_status(&gpt_config);
	}
}
