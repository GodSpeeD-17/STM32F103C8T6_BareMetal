#include "systick.h"

int main(void){
	config_SysTick(SystemCoreClock/1000);
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
		GPIOC->ODR ^= GPIO_ODR_ODR13;
		delay_ms(1000);
	}
	
	return 0;
}
