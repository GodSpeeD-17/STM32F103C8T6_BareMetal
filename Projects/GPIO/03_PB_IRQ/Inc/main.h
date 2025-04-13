// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

/*-------------------------------------------------------------------------------*/
// Headers
#include "bare_metal.h"
/*-------------------------------------------------------------------------------*/
// LED Configuration Structure
gpio_config_t LED_GPIO_Config = {
	.GPIO = GPIOA,
	.PIN = GPIOx_PIN_2,
	.MODE = GPIOx_MODE_OUT_10MHz,
	.CNF = GPIOx_CNF_OUT_GP_PP,
};
// Push-button Configuration Structure
gpio_config_t PB_GPIO_Config = {
	.GPIO = GPIOB,
	.PIN = GPIOx_PIN_5,
	.MODE = GPIOx_MODE_IN,
	.CNF = GPIOx_CNF_IN_PD,
};
// External Interrupt Configuration Structure
exti_config_t PB_EXTI_Config = {
	.GPIO_CONFIGx = &PB_GPIO_Config,
	.TRIGx = EXTI_TRIG_RISING,
	.IRQn = EXTI9_5_IRQn,
};
/*-------------------------------------------------------------------------------*/
// MACROS
#define BOTH_TRIGGER	// Trigger both rising and falling edge; Comment it out for only rising edge
#define LOOP_DELAY_MS						((uint32_t) 1000)
/*-------------------------------------------------------------------------------*/

#endif /* __MAIN_H__ */ 