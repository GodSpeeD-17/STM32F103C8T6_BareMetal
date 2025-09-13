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
#define LOOP_DELAY_MS						(1000)
#define LED_PORT							(GPIO_PORT_A)
#define LED_PIN								(GPIO_PIN_2)
#define LED_MODE							(GPIO_MODE_OUTPUT_10MHz)
#define LED_CONFIG							(GPIO_CNF_OUT_GP_PP)
/*-------------------------------------------------------------------------------*/

#endif /* __MAIN_H__ */