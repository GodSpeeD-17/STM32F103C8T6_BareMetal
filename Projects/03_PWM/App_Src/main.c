// Main Header
#include "main.h"

// Main Entry Point for User Code
int main(void){
	
	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);

	// SysTick Timer (1ms)
	config_SysTick(CoreClock/1000);

	// Configure GPIO as AF
	RCC_AF_ENABLE();
	config_GPIO(LED_PORT, LED_PIN, LED_MODE, CNF_OUT_AF_PP);

	// Enable Clock for GP Timer
	enable_GPT_clk(GP_TIMER);

	// Configure GP Timer (Frequency)
	config_GPT(GP_TIMER, GPT_ARR, GPT_FREQ, GPT_CNT);

	// Configure PWM Mode (Normal)
	config_PWM_mode(GP_TIMER, GPT_CHANNEL, TIMx_OCM_PWM_NORMAL, PRELOAD_ENABLE);

	// Configure PWM Characteristics
	set_PWM_polarity(GP_TIMER, GPT_CHANNEL, TIMx_POL_ACTIVE_HIGH);
	
	// Channel Enable
	enable_GPT_CH(GP_TIMER, GPT_CHANNEL);

	// Timer Enable
	enable_GPT(GP_TIMER);

	// Local Variable
	uint8_t dutyCycle = 0xFF;
	
	while(1){

		// Increase Brightness
		for(dutyCycle = MIN_DUTY_CYCLE; dutyCycle <= MAX_DUTY_CYCLE; dutyCycle += 5){
			// Set Duty Cycle
			set_PWM_duty_cycle(GP_TIMER, GPT_CHANNEL, dutyCycle);
			// Delay
			SysTick_delay_ms(DELAY_MS);
		}
		
		// Loop Delay
		SysTick_delay_ms(100 * DELAY_MS);

		// Decrease Brightness
		for(dutyCycle = MAX_DUTY_CYCLE; dutyCycle >= MIN_DUTY_CYCLE; dutyCycle -= 5){
			// Set Duty Cycle
			set_PWM_duty_cycle(GP_TIMER, GPT_CHANNEL, dutyCycle);
			// Delay
			SysTick_delay_ms(DELAY_MS);
		}

		// Loop Delay
		SysTick_delay_ms(100 * DELAY_MS);
	}

	// Return Value
	return 0;
}
