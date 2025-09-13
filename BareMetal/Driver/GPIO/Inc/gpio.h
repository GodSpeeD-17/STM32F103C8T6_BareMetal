// Header Guards
#ifndef __GPIO_H__
#define __GPIO_H__

// Includes
#include "gpio_config.h"

/**
 * @brief Sets the GPIO 
 * @param gpioPort GPIO Port 
 * @param gpioPin GPIO Pin
 * @note Atomicity
 */
__STATIC_INLINE__ void GPIO_Set(gpio_port_t gpioPort, gpio_pin_t gpioPin){
	GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpioPort);
	if(GPIOx != NULL)
		GPIOx->BSRR.REG |= gpioPin;
}

/**
 * @brief Resets the GPIO 
 * @param gpioPort GPIO Port 
 * @param gpioPin GPIO Pin
 * @note Atomicity
 */
__STATIC_INLINE__ void GPIO_Reset(gpio_port_t gpioPort, gpio_pin_t gpioPin){
	GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpioPort);
	if(GPIOx != NULL)
		GPIOx->BRR.REG |= gpioPin;
}

/**
 * @brief Toggles the GPIO 
 * @param gpioPort GPIO Port 
 * @param gpioPin GPIO Pin
 */
__STATIC_INLINE__ void GPIO_Toggle(gpio_port_t gpioPort, gpio_pin_t gpioPin){
	GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpioPort);
	if(GPIOx != NULL)
		GPIOx->ODR.REG ^= gpioPin;
}

/**
 * @brief Retrieves the GPIO Status 
 * @param gpioPort GPIO Port 
 * @param gpioPin GPIO Pin
 */
__STATIC_INLINE__ uint8_t GPIO_Get(gpio_port_t gpioPort, gpio_pin_t gpioPin){
	GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpioPort);
	if(GPIOx != NULL){
		return ((uint8_t) ((GPIOx->IDR.REG & gpioPin) ? (0x01) : (0x00)));
	}
}

/**
 * @brief Sets the On-board (OB) LED
 * @note OB LED is active LOW
 */
__STATIC_INLINE__ void OB_LED_Set(void){
	GPIO_Reset(GPIO_PORT_OB_LED, GPIO_PIN_OB_LED);
}

/**
 * @brief Resets the On-board (OB) LED
 * @note OB LED is active LOW
 */
__STATIC_INLINE__ void OB_LED_Reset(void){
	GPIO_Set(GPIO_PORT_OB_LED, GPIO_PIN_OB_LED);
}

/**
 * @brief Toggles the On-board (OB) LED
 * @note OB LED is active LOW
 */
__STATIC_INLINE__ void OB_LED_Toggle(void){
	GPIO_Toggle(GPIO_PORT_OB_LED, GPIO_PIN_OB_LED);
}

/**
 * @brief Configures GPIO Port based on GPIO Configuration Structure
 * @param gpio GPIO Port (Refer `gpio_port_t`)
 * @param gpioConfig GPIO Configuration Structure (Refer `gpio_config_t`)
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t GPIO_Config(gpio_port_t gpio, gpio_config_t* const gpioConfig);

/**
 * @brief Configures the LED connected to the specified GPIO Port and Pin
 * @param gpio GPIO Port (Refer `gpio_port_t`)
 * @param gpioConfig GPIO Configuration Structure (Refer `gpio_config_t`)
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t GPIO_LED_Config(gpio_port_t gpio, gpio_config_t* gpioConfig);

/**
 * @brief Configures GPIO Port based on GPIO Configuration Structure
 * @param gpio GPIO Port (Refer `gpio_port_t`)
 * @param gpioConfig GPIO Configuration Structure (Refer `gpio_config_t`)
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t GPIO_Deconfig(gpio_port_t gpio, gpio_config_t* const gpioConfig);

/**
 * @brief Configures the On-board LED
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t OB_LED_Config(void);

/**
 * @brief Deconfigures the On-board LED
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t OB_LED_Deconfig(void);

#endif /* __GPIO_H__ */