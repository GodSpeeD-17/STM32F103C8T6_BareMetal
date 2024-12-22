// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

// Bare Metal Libraries
#include "bare_metal.h"

// MACROS
#define SYSCLK_MHz					(SYSCLK_72MHz)
#define LOOP_DELAY_MS				((uint32_t) 1000)

// USART MACROS
#define USART						(USART1)
#define USART_PORT					(GPIOA)
#define USART_TX_PIN				(GPIO_PIN_9)
#define USART_RX_PIN				(GPIO_PIN_10)

#endif /* __MAIN_H__ */