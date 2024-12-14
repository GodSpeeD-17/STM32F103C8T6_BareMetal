// Main Header
#include "main.h"

// Main Entry Point for User Code
int main(void){

	// Configure Clock (72 MHz)
	config_SYSCLK_MHz(SYSCLK_MHz);

	// SysTick Timer (1ms)
	config_SysTick(CoreClock/1000);

	// Initialize External LED
	gpio_config_t led_config = {
		.GPIOx = LED_PORT,
		.PINx = LED_PIN,
		.MODEx = MODE_OUT_10MHz,
		.CNFx = CNF_OUT_GP_PP
	};
	config_GPIO(&led_config);
	reset_GPIO(&led_config);

	// GPT Configuration Structure
	gpt_config_t gpt_config = {
		.GPIO_CONFIGx = NULL,
		.GP_TIMx = GP_TIMER,
		.channel = GPT_CHANNEL,
		.auto_reload_value = GPT_ARR,
		.frequency_Hz = GPT_FREQ,
		.count = GPT_CNT,
		.cms_mode = CMS_EDGE,
		.direction = TIMx_COUNT_UP,
		.auto_reload_preload = TIMx_ARPE_ENABLE,
		.one_pulse = TIMx_OPM_DISABLE,
		.enable_IRQ = TIMx_IRQ_DISABLE,
	};
	config_GPT(&gpt_config);
	enable_GPT(&gpt_config);

	// Initialise On-board LED
	config_OB_LED();
	reset_OB_LED();

	// Infinite Loop
	while(1){
		// Toggle external LED
		toggle_GPIO(&led_config);
		// Delay using SysTick
		GPT_delay_ms(&gpt_config, DELAY_MS);
		// Toggle Onboard LED
		toggle_OB_LED();
	}
	
	// Return Value
	return 0;

}
