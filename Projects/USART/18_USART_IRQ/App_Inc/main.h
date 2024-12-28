// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

// Bare Metal Libraries
#include "bare_metal.h"

// MACROS
#define SYSCLK_MHz					(SYSCLK_72MHz)
#define LOOP_DELAY_MS				((uint32_t) 50)

// USART Configuration
#define USART                       (USART1)
#define USART_TX_GPIO				(GPIOA)    
#define USART_TX_PIN				((uint8_t) 9)
#define USART_RX_GPIO				(GPIOA)    
#define USART_RX_PIN				((uint8_t) 10)

// Buffer
#define BUFFER_SIZE					((uint8_t) 8)
char buffer[BUFFER_SIZE] = {0};
char curr_value = 0x00;
uint8_t buffer_head = 0;
uint8_t buffer_tail = 0;

#endif /* __MAIN_H__ */