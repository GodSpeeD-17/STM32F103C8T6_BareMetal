// Main Header
#include "main.h"

// ADC Configuration

// Main Entry Point for User Code
int main(void){
    
	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);

	// SysTick Timer (1ms)
	config_SysTick(CoreClock/1000);

	// PWM Configuration Structure
	gpio_config_t led_config = {
		.GPIOx = LED_PORT, 
		.PINx = LED_PIN, 
		.MODEx = MODE_OUT_10MHz, 
		.CNFx = CNF_OUT_AF_PP,
	};
	gpt_config_t tim_config = {
		.GPIO_CONFIGx = &led_config,
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
	pwm_config_t pwm_config = {
		.GPT_CONFIGx = &tim_config,
		.pwm_mode = TIMx_OCM_PWM_NORMAL,
		.duty_cycle = MIN_DUTY_CYCLE,
		.polarity = TIMx_POL_ACTIVE_HIGH,
		.pwm_channel_preload = PWM_CHx_PRELOAD_ENABLE,
	};
	config_PWM(&pwm_config);
	start_PWM(&pwm_config);

	// ADC Configuration Structure
	gpio_config_t pot_config = {
		.GPIOx = POT_PORT,
		.PINx = POT_PIN,
		.MODEx = MODE_IN,
		.CNFx = CNF_IN_ANALOG,
	};
	adc_config_t adc_config = {
		.GPIO_CONFIGx = &pot_config,
		.ADCx = POT_ADC,
		.channel = POT_ADC_CHANNEL,
		.num_channels = 1,
		.sample_time = POT_ADC_SAMPLE_TIME,
		.cc = ADC_CONT_CONV_ON,
		.data_alignment = ADC_DATA_ALIGN_RIGHT,
		.enable_IRQ = 
	};
	// Configure ADC
	config_ADC(&adc_config);

	// Infinite Loop
	while(1){
		// User Code Start

		// User Code End
		
		// Loop Delay
		SysTick_delay_ms(DELAY_MS);
	}
		
	// Return Value
	return 0;
}
