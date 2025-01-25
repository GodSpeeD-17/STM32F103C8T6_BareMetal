#include "main.h"

// #define HARD_CODED

#ifndef HARD_CODED
// Configuration: 72MHz
rcc_config_t rcc_config = {
	// System Clock Source
	.sys_clk_src = SW_CLK_PLL,
	// Flash Configuration
	.flash = {
		.latency = FLASH_ACR_LATENCY_2,
		.prefetch = FLASH_ACR_PRFTBE_Msk,
	},
	// PLL Configuration
	.pll = {
		.ext_src = PLL_SRC_HSE,
		.ext_src_pre = PLL_HSE_DIV_1,
		.mul_fact = PLL_MUL_9,
	},
	// Bus Configuration
	.bus = {
		.APB1_pre = APB1_DIV_2,
		.APB2_pre = APB2_DIV_1,
		.AHB_pre = AHB_DIV_1
	},
	// Components Configuration
	.component = {
		.ADC_pre = ADC_DIV_6,
		.USB_pre = USB_DIV_1_5,
	},
};

int main(void){
	// RCC Configuration
	config_RCC(&rcc_config);
	// 1ms
	config_SysTick(CoreClock/1000);
	
	// OB LED
	config_OB_LED();
	reset_OB_LED();

	// Infinite Loop
	while(1){
		// Set
		set_OB_LED();
		// 1s
		delay_ms(1000);
		// Reset
		reset_OB_LED();
		// 1s
		delay_ms(1000);
	}
	
	return 0;
}
#else
int main(void){
	
	// PLL
	uint32_t reg = 0x00;
	// Configure Flash for Two Wait States
	FLASH->ACR.REG = FLASH_ACR_LATENCY_2 | FLASH_ACR_PRFTBE;
	while(!(FLASH->ACR.REG & FLASH_ACR_PRFTBS_Msk));
	RCC->CR.REG |= RCC_CR_HSEON;
	while(!(RCC->CR.REG & RCC_CR_HSERDY_Msk));
	// PLL Configuration
	reg |= RCC_CFGR_PLLMULL9 | RCC_CFGR_PLLXTPRE_HSE | RCC_CFGR_PLLSRC;
	// Bus Prescaler Configuration
	reg |= RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_HPRE_DIV1;
	// USB_DIV_1.5: 48MHz
	reg &= ~RCC_CFGR_USBPRE_Msk;
	// ADC_DIV_6
	reg |= RCC_CFGR_ADCPRE_DIV6;
	RCC->CFGR.REG = reg;
	// PLL ON
	RCC->CR.REG |= RCC_CR_PLLON;
	while(!(RCC->CR.REG & RCC_CR_PLLRDY));
	// System Clock Switch
	RCC->CFGR.REG |= RCC_CFGR_SW_PLL;
	while((RCC->CFGR.REG & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_PLL);

	// 1ms
	config_SysTick(72*1000);
	
	// OB LED
	config_OB_LED();
	reset_OB_LED();


	// Infinite Loop
	while(1){
		// 
		// toggle_OB_LED();
		set_OB_LED();
		// 1s
		delay_ms(1000);
		reset_OB_LED();
		delay_ms(1000);
	}
	
	return 0;
}
#endif