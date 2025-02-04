// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

/*-------------------------------------------------------------------------------*/
// Headers
#include "bare_metal.h"
/*-------------------------------------------------------------------------------*/
// LED Configuration Structure
gpio_config_t LED_GPIO_Config = {
	.GPIOx = GPIOA,
	.PINx = GPIO_PIN_2,
	.MODEx = MODE_OUT_10MHz,
	.CNFx = CNF_OUT_GP_PP,
};
// Push-button Configuration Structure
gpio_config_t PB_GPIO_Config = {
	.GPIOx = GPIOB,
	.PINx = GPIO_PIN_5,
	.MODEx = MODE_IN,
	.CNFx = CNF_IN_PD,
};
// External Interrupt Configuration Structure
exti_config_t PB_EXTI_Config = {
	.GPIO_CONFIGx = &PB_GPIO_Config,
	.TRIGx = EXTI_TRIG_RISING,
	.IRQn = EXTI9_5_IRQn,
};
/*-------------------------------------------------------------------------------*/
// MACROS
#define LOOP_DELAY_MS						((uint32_t) 1000)
/*-------------------------------------------------------------------------------*/

#endif /* __MAIN_H__ */ 