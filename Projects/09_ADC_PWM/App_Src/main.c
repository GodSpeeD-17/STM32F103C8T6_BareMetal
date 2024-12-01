// Main Header
#include "main.h"

// Global Variables
uint16_t adc_data[2] = {0};

// Main Entry Point for User Code
int main(void){
    
	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);

	// SysTick Timer (1ms)
	config_SysTick(CoreClock/1000);

	// Debugging LED
	config_LED(DEBUG_LED_PORT, DEBUG_LED_PIN);

	// ADC Configuration Structure
	adc_config_t adc_config = {
        .GPIOx = POT_PORT,
        .PINx = POT_PIN,
        .ADCx = POT_ADC,
        .channel = POT_ADC_CHANNEL,
        .num_channels = 1,
        .sample_time = POT_ADC_SAMPLE_TIME,
        .cc = ADC_CONT_CONV_ON,
        .data_alignment = ADC_DATA_ALIGN_RIGHT,
    };

	// Configure ADC
	config_ADC(&adc_config);

	// Timer Configuration Structure
	gpt_config_t tim_config = {
		.GP_TIMx = GP_TIMER,
		.channel = GPT_CHANNEL,
		.auto_reload_value = GPT_ARR,
		.frequency_Hz = GPT_FREQ,
		.count = GPT_CNT,
		.cms_mode = CMS_EDGE,
		.direction = TIMx_COUNT_UP,
		.auto_reload_preload = TIMx_ARPE_ENABLE,
		.one_pulse = TIMx_OPM_DISABLE,
	};

	// PWM Configuration Structure
	pwm_config_t pwm_config = {
		.GPT_CONFIGx = &tim_config,
		.pwm_mode = TIMx_OCM_PWM_NORMAL,
		.duty_cycle = MIN_DUTY_CYCLE,
		.polarity = TIMx_POL_ACTIVE_HIGH,
	};

	// Configure PWM
	config_PWM(&pwm_config);

	// Start PWM
	start_PWM(&pwm_config);

	// Config On-board LED for ADC indication
	config_OB_LED();
	reset_OB_LED();

	// Infinite Loop
	while(1){
		// ADC Data Ready
		if (ready_ADC_data(&adc_config)){
			// Read ADC Data
			adc_data[0] = get_ADC_data(&adc_config);
			// ADC Data exceeds the Error Range
			if ((adc_data[1] > adc_data[0] + ADC_ERROR_RANGE) || (adc_data[1] < adc_data[0] - ADC_ERROR_RANGE)){
				// Shift the new data
				adc_data[1] = adc_data[0];
				// Update PWM duty cycle
				// pwm_config.duty_cycle = calc_PWM_ADC(adc_data[1]);
				// PWM Indication
				// set_PWM_duty_cycle(&pwm_config);
				// Toggle OB LED
				toggle_OB_LED();
            }

			// Increase Brightness
			for(pwm_config.duty_cycle = MIN_DUTY_CYCLE; pwm_config.duty_cycle <= MAX_DUTY_CYCLE; pwm_config.duty_cycle += 2){
				// Set Duty Cycle
				set_PWM_duty_cycle(&pwm_config);
				// Delay
				SysTick_delay_ms(DELAY_MS);
			}

            // Loop Delay
            SysTick_delay_ms(DELAY_MS);
        }
    }

    // Return Value
    return 0;
}

/**
 * @brief Calculates Duty Cycle based upon input ADC Value
 * @param[in] adc_value 12-bit ADC Value
 */
uint8_t calc_PWM_ADC(uint16_t adc_value){
	// Wrap ADC Value to ensure it is in 12-bit range
	adc_value &= 0x0FFF;
	// Calculate Duty Cycle
	uint32_t result = (((uint32_t)adc_value * MAX_DUTY_CYCLE) / MAX_ADC_VALUE);
	// Return the result
	return (uint8_t)result;
}