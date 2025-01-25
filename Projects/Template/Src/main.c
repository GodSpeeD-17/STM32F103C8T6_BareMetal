#include "main.h"

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
