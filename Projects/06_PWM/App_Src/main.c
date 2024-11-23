// Main Header
#include "main.h"

// Main Entry Point for User Code
int main(void){
	
	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);

	// SysTick Timer (1ms)
	config_SysTick(CoreClock/1000);

	// Configure GPIO as AF
	config_GPIO(LED_PORT, LED_PIN, MODE_OUT_10MHz, CNF_OUT_AF_PP);

	// Configure On-board LED
	config_OB_LED();
	reset_OB_LED();

	// PWM Configuration Structure
	pwm_config_t pwm_config = {
		.GPT_CONFIGx = {
			.GP_TIMx = GP_TIMER,
			.channel = GPT_CHANNEL,
			.auto_reload_value = GPT_ARR,
			.frequency_Hz = GPT_FREQ,
			.count = GPT_CNT,
			.cms_mode = CMS_EDGE,
			.direction = TIMx_COUNT_UP,
			.auto_reload_preload = TIMx_ARPE_ENABLE,
			.one_pulse = TIMx_OPM_DISABLE,
		},
		.pwm_mode = TIMx_OCM_PWM_NORMAL,
		.duty_cycle = MIN_DUTY_CYCLE,
		.polarity = TIMx_POL_ACTIVE_HIGH,
	};

	// Configure PWM
	config_PWM(&pwm_config);
	
	// Channel Enable
	enable_GPT_CH(&pwm_config.GPT_CONFIGx);

	// Timer Enable
	enable_GPT(&pwm_config.GPT_CONFIGx);

	// Local Variable
	uint8_t dutyCycle;
	
	while(1){

		// Increase Brightness
		for(dutyCycle = MIN_DUTY_CYCLE; dutyCycle <= MAX_DUTY_CYCLE; dutyCycle += 2){
			// Update PWM Duty Cycle
			pwm_config.duty_cycle = dutyCycle;
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
		for(dutyCycle = MAX_DUTY_CYCLE; dutyCycle >= MIN_DUTY_CYCLE; dutyCycle -= 2){
			// Update PWM Duty Cycle
			pwm_config.duty_cycle = dutyCycle;
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
