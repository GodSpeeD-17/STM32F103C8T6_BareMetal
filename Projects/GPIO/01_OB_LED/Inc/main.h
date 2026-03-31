// Header Guards
#ifndef MAIN_H_
#define MAIN_H_

/*-------------------------------------------------------------------------------*/
// Headers
#include "gpio.h"
#include "systick.h"
#include "startup.h"
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
// MACROS
#define LED_LAMP_TEST_DELAY_MS				(250UL)
#define LED_STEP_DELAY_MS					(400UL)
#define RED_LED_PORT						GPIOA
#define RED_LED_PIN							GPIO_PIN_2
#define YELLOW_LED_PORT						GPIOA
#define YELLOW_LED_PIN						GPIO_PIN_3
/*-------------------------------------------------------------------------------*/

#endif /* MAIN_H_ */
