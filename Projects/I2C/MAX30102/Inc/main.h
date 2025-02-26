// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

/*-------------------------------------------------------------------------------*/
// Headers
#include "bare_metal.h"
#include "max30102.h"
/*-------------------------------------------------------------------------------*/
// I2C SCL GPIO Config
gpio_config_t SCL_GPIO_Config = {
	.GPIOx = GPIOB,
	.PINx = GPIO_PIN_10,
	.MODEx = MODE_OUT_50MHz,
	.CNFx = CNF_OUT_AF_OD
};
// I2C SDA GPIO Config
gpio_config_t SDA_GPIO_Config = {
	.GPIOx = GPIOB,
	.PINx = GPIO_PIN_11,
	.MODEx = MODE_OUT_50MHz,
	.CNFx = CNF_OUT_AF_OD
};
// I2C Configuration Structure
i2c_config_t I2C_Config = {
	.I2Cx = I2C2,
	.SCL = &SCL_GPIO_Config,
	.SDA = &SDA_GPIO_Config,
	.mode = I2Cx_MODE_STD,
	.duty = I2Cx_DUTY_NORMAL,
};
/*-------------------------------------------------------------------------------*/
// MACROS
#define LOOP_DELAY_MS						((uint32_t) 1000)
/*-------------------------------------------------------------------------------*/

#endif /* __MAIN_H__ */ 