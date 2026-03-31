// Header Guards
#ifndef MAIN_H_
#define MAIN_H_

/*-------------------------------------------------------------------------------*/
// Headers
#include "gpio.h"
#include "gpio_exti.h"
#include "systick.h"
/*-------------------------------------------------------------------------------*/

void delay_ms(uint32_t delayTime);
void EXTI1_IRQHandler(void);

/*-------------------------------------------------------------------------------*/
// MACROS
#define LOOP_DELAY_MS						((uint32_t) 1000)
#define DEBOUNCE_TIME_MS					((uint32_t) 50)
#define RED_LED_PORT						(GPIOA)
#define RED_LED_PIN							(GPIO_PIN_2)
#define YELLOW_LED_PORT						(GPIOA)
#define YELLOW_LED_PIN						(GPIO_PIN_3)
#define PUSH_BUTTON_PORT                    (GPIOA)
#define PUSH_BUTTON_PIN                     (GPIO_PIN_1)
/*-------------------------------------------------------------------------------*/

#endif /* MAIN_H_ */
