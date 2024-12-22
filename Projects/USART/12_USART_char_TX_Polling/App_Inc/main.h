// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

// Bare Metal Libraries
#include "bare_metal.h"

// MACROS
#define SYSCLK_MHz					(SYSCLK_72MHz)
#define LOOP_DELAY_MS				((uint32_t) 1000)
#define LOOKUP_TABLE_DELAY_MS		((uint32_t) 300)
#define STAR_DELAY_MS				((uint32_t) 100)

// USART MACROS
#define USART						(USART1)
#define USART_PORT					(GPIOA)
#define USART_TX_PIN				(GPIO_PIN_9)
#define USART_RX_PIN				(GPIO_PIN_10)

// Length MACROS
#define LOOKUP_TABLE_LENGTH			((uint8_t) 26)
#define STAR_LENGTH					((uint8_t) 40)

// Lookup Table
const char lookup_table[LOOKUP_TABLE_LENGTH] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',\
								'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', \
								'W', 'X', 'Y', 'Z'};

#endif /* __MAIN_H__ */