// Header Guards
#ifndef MAIN
#define MAIN

/*-------------------------------------------------------------------------------*/
// Headers
#include "gpio.h"
#include "bsp.h"
#include "systick.h"
/*-------------------------------------------------------------------------------*/
void delay_ms(uint32_t delayTime);

/*-------------------------------------------------------------------------------*/
// MACROS
#define LOOP_DELAY_MS					10UL
#define BUTTON_DEBOUNCE_DELAY_MS		50UL
#define RED_LED_PORT					GPIOA
#define RED_LED_PIN						GPIO_PIN_2
#define YELLOW_LED_PORT					GPIOA
#define YELLOW_LED_PIN					GPIO_PIN_3
#define PUSH_BUTTON_PORT				GPIOA
#define PUSH_BUTTON_PIN					GPIO_PIN_1
/*-------------------------------------------------------------------------------*/

#endif /* MAIN */
