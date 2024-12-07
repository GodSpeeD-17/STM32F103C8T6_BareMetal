// Main Header
#include "main.h"

// Global Variables
uint8_t irq_status = 0x00;

// LED Configuration
gpio_config_t led_config = {
	.GPIOx = LED_PORT,
	.PINx = LED_PIN,
	.MODEx = MODE_OUT_10MHz,
	.CNFx = CNF_OUT_GP_PP,
};

// Push Button Configuration
gpio_config_t pb_config = {
	.GPIOx = PB_RISING_PORT,
	.PINx = PB_RISING_PIN,
	.MODEx = MODE_IN,
	.CNFx = CNF_IN_PD,
};
exti_config_t exti_config = {
	.GPIO_CONFIGx = &pb_config,
	.TRIGx = EXTI_TRIG_RISING,
	.IRQn = PB_RISING_IRQ_NUM,
};

// LED1 PWM Configuration
gpio_config_t led1_config = {
	.GPIOx = LED1_PORT,
	.PINx = LED1_PIN,
	.MODEx = MODE_OUT_10MHz,
	.CNFx = CNF_OUT_AF_PP,
};
gpt_config_t tim_led1_config = {
	.GPIO_CONFIGx = &led1_config,
	.GP_TIMx = GP_TIMER,
	.channel = GPT_CHANNEL1,
	.auto_reload_value = GPT_ARR,
	.frequency_Hz = GPT_FREQ,
	.count = GPT_CNT,
	.cms_mode = CMS_EDGE,
	.direction = TIMx_COUNT_UP,
	.auto_reload_preload = TIMx_ARPE_ENABLE,
	.one_pulse = TIMx_OPM_DISABLE,
	.enable_IRQ = TIMx_IRQ_DISABLE,
};
pwm_config_t pwm_led1_config = {
	.GPT_CONFIGx = &tim_led1_config,
	.pwm_mode = TIMx_OCM_PWM_NORMAL,
	.duty_cycle = MIN_DUTY_CYCLE,
	.polarity = TIMx_POL_ACTIVE_HIGH,
	.pwm_channel_preload = PWM_CHx_PRELOAD_ENABLE,
};

// LED2 PWM Configuration
gpio_config_t led2_config = {
	.GPIOx = LED2_PORT,
	.PINx = LED2_PIN,
	.MODEx = MODE_OUT_10MHz,
	.CNFx = CNF_OUT_AF_PP,
};
gpt_config_t tim_led2_config = {
	.GPIO_CONFIGx = &tim_led1_config,
	.GP_TIMx = GP_TIMER,
	.channel = GPT_CHANNEL2,
	.auto_reload_value = GPT_ARR,
	.frequency_Hz = GPT_FREQ,
	.count = GPT_CNT,
	.cms_mode = CMS_EDGE,
	.direction = TIMx_COUNT_UP,
	.auto_reload_preload = TIMx_ARPE_ENABLE,
	.one_pulse = TIMx_OPM_DISABLE,
	.enable_IRQ = TIMx_IRQ_DISABLE,
};
pwm_config_t pwm_led2_config = {
	.GPT_CONFIGx = &tim_led2_config,
	.pwm_mode = TIMx_OCM_PWM_NORMAL,
	.duty_cycle = MIN_DUTY_CYCLE,
	.polarity = TIMx_POL_ACTIVE_HIGH,
	.pwm_channel_preload = PWM_CHx_PRELOAD_ENABLE,
};

// Main Entry Point for User Code
int main(void){
	
	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);

	// SysTick Timer (1ms)
	config_SysTick(CoreClock/1000);

	// Configure Push Button for Rising Edge Interrupt
	config_EXTI(&exti_config);

	// Configure On-board LED
	config_OB_LED();
	reset_OB_LED();

	// Generic LED for status display
	config_GPIO(&led_config);

	// PWM Configuration
	config_PWM(&pwm_led1_config);
	enable_GPT_CH(&tim_led1_config);
	config_PWM(&pwm_led2_config);
	enable_GPT_CH(&tim_led2_config);

	// Start PWM
	enable_GPT(&tim_led2_config);

	// Infinite Loop
	while(1){

		// LED1
		for(pwm_led1_config.duty_cycle = MIN_DUTY_CYCLE; (pwm_led1_config.duty_cycle <= MAX_DUTY_CYCLE && irq_status); pwm_led1_config.duty_cycle += 2){
			// Duty Cycle Updated
			set_PWM_duty_cycle_multi_channel(&pwm_led1_config, pwm_led1_config.GPT_CONFIGx->channel);
			// Delay
			SysTick_delay_ms(DELAY_MS);
		}
		// LED2
		for(pwm_led2_config.duty_cycle = MIN_DUTY_CYCLE; (pwm_led2_config.duty_cycle <= MAX_DUTY_CYCLE && !irq_status); pwm_led2_config.duty_cycle += 2){
			// Duty Cycle Updated
			set_PWM_duty_cycle_multi_channel(&pwm_led2_config, pwm_led2_config.GPT_CONFIGx->channel);
			// Delay
			SysTick_delay_ms(DELAY_MS);
		}

		// On-board LED Toggle
		toggle_OB_LED();
		
		// LED1
		for(pwm_led1_config.duty_cycle = MAX_DUTY_CYCLE; (pwm_led1_config.duty_cycle >= MIN_DUTY_CYCLE && irq_status); pwm_led1_config.duty_cycle -= 2){
			// Duty Cycle Updated
			set_PWM_duty_cycle_multi_channel(&pwm_led1_config, pwm_led1_config.GPT_CONFIGx->channel);
			// Delay
			SysTick_delay_ms(DELAY_MS);
		}
		// LED2
		for(pwm_led2_config.duty_cycle = MAX_DUTY_CYCLE; (pwm_led2_config.duty_cycle >= MIN_DUTY_CYCLE && !irq_status); pwm_led2_config.duty_cycle -= 2){
			// Duty Cycle Updated
			set_PWM_duty_cycle_multi_channel(&pwm_led2_config, pwm_led2_config.GPT_CONFIGx->channel);
			// Delay
			SysTick_delay_ms(DELAY_MS);
		}

		// On-board LED Toggle
		toggle_OB_LED();

		// Loop Delay
		SysTick_delay_ms(DELAY_MS);
	}
	
	// Return Value
	return 0;
}

/**
 * @brief IRQ Handler for Px5 - Px9
 */
void EXTI9_5_IRQHandler(void){
	// Push Button Rising Edge Interrupt bit pending
	if(get_EXTI_pend(pb_config.PINx)){
		// Toggle LED for indication
		toggle_GPIO(&led_config);
		// Toggle Status
		irq_status = !irq_status;
		// Acknowledge EXTI Flag
		clear_EXTI_pend(pb_config.PINx);
	}
}
