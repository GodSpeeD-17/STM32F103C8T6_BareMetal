// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

/*-------------------------------------------------------------------------------*/
// Headers
#include "gpio.h"
#include "systick.h"
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
// MACROS
#define LOOP_DELAY_MS						((uint32_t) 1000)
#define DEBOUNCE_TIME_MS					((uint32_t) 50)
#define RED_LED_PORT						(GPIO_PORT_A)
#define RED_LED_PIN							(GPIO_PIN_2)
#define YELLOW_LED_PORT						(GPIO_PORT_A)
#define YELLOW_LED_PIN						(GPIO_PIN_3)
#define PUSH_BUTTON_PORT                    (GPIO_PORT_A)
#define PUSH_BUTTON_PIN                     (GPIO_PIN_1)
/*-------------------------------------------------------------------------------*/

#endif /* __MAIN_H__ */