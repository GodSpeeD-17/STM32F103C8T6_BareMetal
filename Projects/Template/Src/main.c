#include "stm32f103x6.h"

volatile uint64_t systick_value = 0x00;
void SysTick_Handler(void);
void delay_ms(uint32_t delay);

int main(void){ 
	SysTick_Config(SystemCoreClock/1000);
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPAEN;
	GPIOC->CRH &= ~(GPIO_CRH_CNF13_0);
	GPIOC->CRH |= (GPIO_CRH_MODE13_0); 
	GPIOA->CRL &= ~(GPIO_CRL_CNF2_0);
	GPIOA->CRL |= (GPIO_CRL_MODE2_0); 
	GPIOC->ODR |= GPIO_ODR_ODR13;
	delay_ms(1000);
	GPIOC->ODR &= ~GPIO_ODR_ODR13;
	delay_ms(1000);
	GPIOA->ODR |= GPIO_ODR_ODR2;
	
	while(1){
		// GPIOC->BRR |= GPIO_BSRR_BR13;
		// GPIOC->BSRR |= GPIO_BRR_BR13;
		GPIOC->ODR ^= GPIO_ODR_ODR13;
		delay_ms(1000);
	}
	
	return 0;
}

void SysTick_Handler(void){
	systick_value++;
}

void delay_ms(uint32_t delay){
	volatile uint64_t start = systick_value;
	while(systick_value - start <= delay){
		__asm("nop");
	}
}