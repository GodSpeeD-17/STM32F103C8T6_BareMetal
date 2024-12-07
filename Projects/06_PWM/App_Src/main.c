// Main Header
#include "main.h"

// Main Entry Point for User Code
int main(void){
	
	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);

	// SysTick Timer (1ms)
	config_SysTick(CoreClock/1000);

	// Configure On-board LED
	config_OB_LED();
	reset_OB_LED();

	// GPIO Configuration Structure
	gpio_config_t gpio_config = {
		.GPIOx = LED_PORT,
		.PINx = LED_PIN,
		.MODEx = MODE_OUT_10MHz,
		.CNFx = CNF_OUT_AF_PP,
	};

	// Timer Configuration Structure
	gpt_config_t tim_config = {
		.GPIO_CONFIGx = &gpio_config,
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

	// PWM Configuration Structure
	pwm_config_t pwm_config = {
		.GPT_CONFIGx = &tim_config,
		.pwm_mode = TIMx_OCM_PWM_NORMAL,
		.duty_cycle = MIN_DUTY_CYCLE,
		.polarity = TIMx_POL_ACTIVE_HIGH,
		.pwm_channel_preload = PWM_CHx_PRELOAD_ENABLE,
	};

	// Configure PWM
	config_PWM(&pwm_config);
	// Start PWM
	start_PWM(&pwm_config);

	while(1){

		// Increase Brightness
		for(pwm_config.duty_cycle = MIN_DUTY_CYCLE; pwm_config.duty_cycle <= MAX_DUTY_CYCLE; pwm_config.duty_cycle += 2){
			// Set Duty Cycle
			set_PWM_duty_cycle(&pwm_config);
			// Delay
			SysTick_delay_ms(DELAY_MS);
		}
		
		// Indication
		toggle_OB_LED();
		SysTick_delay_ms(2000);
		toggle_OB_LED();

		// Decrease Brightness
		for(pwm_config.duty_cycle = MAX_DUTY_CYCLE; pwm_config.duty_cycle >= MIN_DUTY_CYCLE; pwm_config.duty_cycle -= 2){
			// Set Duty Cycle
			set_PWM_duty_cycle(&pwm_config);
			// Delay
			SysTick_delay_ms(DELAY_MS);
		}

		// Indication
		toggle_OB_LED();
		SysTick_delay_ms(2000);
		toggle_OB_LED();
	}

	// Return Value
	return 0;
}
