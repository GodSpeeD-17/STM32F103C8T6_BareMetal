// Header Guards
#ifndef MAIN_H_
#define MAIN_H_

/*-------------------------------------------------------------------------------*/
// Headers
#include "gpio.h"
#include "bsp.h"
#include "systick.h"
#include "startup.h"
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
// MACROS
/**
 * @brief GPIO 01_OB_LED project-local LED configuration
 * @details These macros define the demo timing and external LED GPIO mappings
 * used by the 01_OB_LED project. Board on-board LED ownership remains in BSP.
 * @{
 */
/** @brief Lamp-test blink delay in milliseconds @def LED_LAMP_TEST_DELAY_MS */
#define LED_LAMP_TEST_DELAY_MS				(250UL)
/** @brief Normal LED sequence step delay in milliseconds @def LED_STEP_DELAY_MS */
#define LED_STEP_DELAY_MS					(700UL)
/** @brief Red LED GPIO port instance @def RED_LED_PORT */
#define RED_LED_PORT						GPIOA
/** @brief Red LED GPIO pin mask @def RED_LED_PIN */
#define RED_LED_PIN							GPIO_PIN_2
/** @brief Yellow LED GPIO port instance @def YELLOW_LED_PORT */
#define YELLOW_LED_PORT						GPIOA
/** @brief Yellow LED GPIO pin mask @def YELLOW_LED_PIN */
#define YELLOW_LED_PIN						GPIO_PIN_3
/** @} */
/*-------------------------------------------------------------------------------*/

#endif /* MAIN_H_ */
