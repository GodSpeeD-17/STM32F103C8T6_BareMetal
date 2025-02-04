// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

/*-------------------------------------------------------------------------------*/
// Headers
#include "bare_metal.h"
/*-------------------------------------------------------------------------------*/
// Struct
gpio_config_t PB_GPIO_Config = {
    .GPIOx = GPIOB,
    .PINx = GPIO_PIN_5,
    .MODEx = MODE_IN,
    .CNFx = CNF_IN_PD,
};
/*-------------------------------------------------------------------------------*/
// MACROS
#define LOOP_DELAY_MS						((uint32_t) 50)
#define OLD_STATUS                          ((uint8_t) 0)
#define NEW_STATUS                          ((uint8_t) 1)
/*-------------------------------------------------------------------------------*/

#endif /* __MAIN_H__ */ 