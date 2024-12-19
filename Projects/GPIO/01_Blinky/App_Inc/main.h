// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

// Bare Metal Libraries
#include "bare_metal.h"

// MACROS
#define SYSCLK_MHz                      (SYSCLK_72MHz)
#define DELAY_MS                        ((uint32_t) 1000)         
#define LED_PORT                        (GPIOB)
#define LED_PIN                         (GPIO_PIN_12)

#endif /* __MAIN_H__ */