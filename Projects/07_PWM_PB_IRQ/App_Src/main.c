// Main Header
#include "main.h"

// Global Variables
uint8_t irq_status = 0x00;

// Main Entry Point for User Code
int main(void){
    
    // Configure Clock
    config_SYSCLK_MHz(SYSCLK_MHz);

    // SysTick Timer (1ms)
    config_SysTick(CoreClock/1000);

    // Configure GPIO as AF
	config_GPIO(LED1_PORT, LED1_PIN, MODE_OUT_10MHz, CNF_OUT_AF_PP);
	config_GPIO(LED2_PORT, LED2_PIN, MODE_OUT_10MHz, CNF_OUT_AF_PP);

    // Configure Push Button for Rising Edge Interrupt
    config_GPIO(PB_RISING_PORT, PB_RISING_PIN, MODE_IN, CNF_IN_PD);
    config_EXTI(PB_RISING_PORT, PB_RISING_PIN, EXTI_TRIG_RISING, PB_RISING_IRQ_NUM);

    // Configure On-board LED
    config_OB_LED();
    reset_OB_LED();

    // Generic LED for status display
    config_LED(LED_PORT, LED_PIN);

    // Timer1 Configuration Structure
    gpt_config_t tim_config = {
        .GP_TIMx = GP_TIMER,
        .channel = (GPT_CHANNEL1 | GPT_CHANNEL2),
        .auto_reload_value = GPT_ARR,
        .frequency_Hz = GPT_FREQ,
        .count = GPT_CNT,
        .cms_mode = CMS_EDGE,
        .direction = TIMx_COUNT_UP,
        .auto_reload_preload = TIMx_ARPE_ENABLE,
        .one_pulse = TIMx_OPM_DISABLE,
    };

    // PWM Configuration Structure for LED1
	pwm_config_t pwm_led_combined = {
		.GPT_CONFIGx = &tim_config,
		.pwm_mode = TIMx_OCM_PWM_NORMAL,
		.duty_cycle = MIN_DUTY_CYCLE,
		.polarity = TIMx_POL_ACTIVE_HIGH,
	};

    // PWM Configuration
    config_PWM(&pwm_led_combined);

    // Start PWM
	start_PWM(&pwm_led_combined);

    // Infinite Loop
    while(1){

        // LED1
        for(pwm_led_combined.duty_cycle = MIN_DUTY_CYCLE; (pwm_led_combined.duty_cycle <= MAX_DUTY_CYCLE && irq_status); pwm_led_combined.duty_cycle += 2){
            // Duty Cycle Updated
            set_PWM_duty_cycle_multi_channel(&pwm_led_combined, GPT_CHANNEL1);
            // Delay
            SysTick_delay_ms(DELAY_MS);
        }
        // LED2
        for(pwm_led_combined.duty_cycle = MIN_DUTY_CYCLE; (pwm_led_combined.duty_cycle <= MAX_DUTY_CYCLE && !irq_status); pwm_led_combined.duty_cycle += 2){
            // Duty Cycle Updated
            set_PWM_duty_cycle_multi_channel(&pwm_led_combined, GPT_CHANNEL2);
            // Delay
            SysTick_delay_ms(DELAY_MS);
        }

        // On-board LED Toggle
        toggle_OB_LED();
        
        // LED1
        for(pwm_led_combined.duty_cycle = MAX_DUTY_CYCLE; (pwm_led_combined.duty_cycle >= MIN_DUTY_CYCLE && irq_status); pwm_led_combined.duty_cycle -= 2){
            // Duty Cycle Updated
            set_PWM_duty_cycle_multi_channel(&pwm_led_combined, GPT_CHANNEL1);
            // Delay
            SysTick_delay_ms(DELAY_MS);
        }
        // LED2
        for(pwm_led_combined.duty_cycle = MAX_DUTY_CYCLE; (pwm_led_combined.duty_cycle >= MIN_DUTY_CYCLE && !irq_status); pwm_led_combined.duty_cycle -= 2){
            // Duty Cycle Updated
            set_PWM_duty_cycle_multi_channel(&pwm_led_combined, GPT_CHANNEL2);
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
    if(get_EXTI_pend(PB_RISING_PIN)){
        // Toggle LED for indication
        toggle_GPIO(LED_PORT, LED_PIN);
        // Toggle Status
        irq_status = !irq_status;
        // Acknowledge EXTI Flag
        clear_EXTI_pend(PB_RISING_PIN);
    }
}

/*
// Code for two different TIMERS
int main(void){
    
    // Configure Clock
    config_SYSCLK_MHz(SYSCLK_MHz);

    // SysTick Timer (1ms)
    config_SysTick(CoreClock/1000);

    // Configure GPIO as AF
	config_GPIO(LED1_PORT, LED1_PIN, MODE_OUT_10MHz, CNF_OUT_AF_PP);
	config_GPIO(LED2_PORT, LED2_PIN, MODE_OUT_10MHz, CNF_OUT_AF_PP);

    // Configure Push Button for Rising Edge Interrupt
    config_GPIO(PB_RISING_PORT, PB_RISING_PIN, MODE_IN, CNF_IN_PD);
    config_EXTI(PB_RISING_PORT, PB_RISING_PIN, EXTI_TRIG_RISING, PB_RISING_IRQ_NUM);

    // Configure On-board LED
    config_OB_LED();
    reset_OB_LED();

    // Generic LED for status display
    config_LED(LED_PORT, LED_PIN);

    // Timer1 Configuration Structure
    gpt_config_t tim1_config = {
        .GP_TIMx = GP_TIMER1,
        .channel = GPT_CHANNEL1,
        .auto_reload_value = GPT_ARR1,
        .frequency_Hz = GPT_FREQ1,
        .count = GPT_CNT1,
        .cms_mode = CMS_EDGE,
        .direction = TIMx_COUNT_UP,
        .auto_reload_preload = TIMx_ARPE_ENABLE,
        .one_pulse = TIMx_OPM_DISABLE,
    };

    // Timer2 Configuration Structure
    gpt_config_t tim2_config = {
        .GP_TIMx = GP_TIMER2,
        .channel = GPT_CHANNEL2,
        .auto_reload_value = GPT_ARR2,
        .frequency_Hz = GPT_FREQ2,
        .count = GPT_CNT2,
        .cms_mode = CMS_EDGE,
        .direction = TIMx_COUNT_UP,
        .auto_reload_preload = TIMx_ARPE_ENABLE,
        .one_pulse = TIMx_OPM_DISABLE,
    };

    // PWM Configuration Structure for LED1
	pwm_config_t pwm_led_1 = {
		.GPT_CONFIGx = &tim1_config,
		.pwm_mode = TIMx_OCM_PWM_NORMAL,
		.duty_cycle = MIN_DUTY_CYCLE,
		.polarity = TIMx_POL_ACTIVE_HIGH,
	};

    // PWM Configuration Structure for LED2
	pwm_config_t pwm_led_2 = {
		.GPT_CONFIGx = &tim2_config,
		.pwm_mode = TIMx_OCM_PWM_NORMAL,
		.duty_cycle = MIN_DUTY_CYCLE,
		.polarity = TIMx_POL_ACTIVE_HIGH,
	};

    // PWM Configuration
    config_PWM(&pwm_led_1);
    config_PWM(&pwm_led_2);

    // Enable Channel
    enable_GPT_CH(pwm_led_1.GPT_CONFIGx);
    enable_GPT_CH(pwm_led_2.GPT_CONFIGx);

    // Timer Enable
	enable_GPT(pwm_led_1.GPT_CONFIGx);
	enable_GPT(pwm_led_2.GPT_CONFIGx);

    // Infinite Loop
    while(1){

        // LED1
        for(pwm_led_1.duty_cycle = MIN_DUTY_CYCLE; (pwm_led_1.duty_cycle <= MAX_DUTY_CYCLE && irq_status); pwm_led_1.duty_cycle += 2){
            // Duty Cycle Updated
            set_PWM_duty_cycle(&pwm_led_1);
            // Delay
            SysTick_delay_ms(DELAY_MS);
        }
        // LED2
        for(pwm_led_2.duty_cycle = MIN_DUTY_CYCLE; (pwm_led_2.duty_cycle <= MAX_DUTY_CYCLE && !irq_status); pwm_led_2.duty_cycle += 2){
            // Duty Cycle Updated
            set_PWM_duty_cycle(&pwm_led_2);
            // Delay
            SysTick_delay_ms(DELAY_MS);
        }

        // On-board LED Toggle
        toggle_OB_LED();

        // LED1
        for(pwm_led_1.duty_cycle; (pwm_led_1.duty_cycle >= MIN_DUTY_CYCLE && irq_status); pwm_led_1.duty_cycle -= 2){
            // Duty Cycle Updated
            set_PWM_duty_cycle(&pwm_led_1);
            // Delay
            SysTick_delay_ms(DELAY_MS);
        }
        // LED2
        for(pwm_led_2.duty_cycle; (pwm_led_2.duty_cycle >= MIN_DUTY_CYCLE && !irq_status); pwm_led_2.duty_cycle -= 2){
            // Duty Cycle Updated
            set_PWM_duty_cycle(&pwm_led_2);
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

void EXTI9_5_IRQHandler(void){

    // Push Button Rising Edge Interrupt bit pending
    if(get_EXTI_pend(PB_RISING_PIN)){
        // Toggle LED for indication
        toggle_GPIO(LED_PORT, LED_PIN);
        // Toggle Status
        irq_status = !irq_status;
        // Acknowledge EXTI Flag
        clear_EXTI_pend(PB_RISING_PIN);
    }
}
*/