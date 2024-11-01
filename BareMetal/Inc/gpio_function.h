/***************************************************************************************
 *  File: gpio_function.h
 *  Created on: 14/09/2024
 *  Author: shrey_shah
 ***************************************************************************************/

// Header Guards
#ifndef _GPIO_FUNCTION_H_
#define _GPIO_FUNCTION_H_

// Register Address Mapping
#include "reg_map.h"

// GPIO PIN
#define GPIO_PIN_0                         ((uint8_t) 0)
#define GPIO_PIN_1                         ((uint8_t) 1)
#define GPIO_PIN_2                         ((uint8_t) 2)
#define GPIO_PIN_3                         ((uint8_t) 3)
#define GPIO_PIN_4                         ((uint8_t) 4)
#define GPIO_PIN_5                         ((uint8_t) 5)
#define GPIO_PIN_6                         ((uint8_t) 6)
#define GPIO_PIN_7                         ((uint8_t) 7)
#define GPIO_PIN_8                         ((uint8_t) 8)
#define GPIO_PIN_9                         ((uint8_t) 9)
#define GPIO_PIN_10                        ((uint8_t) 10)
#define GPIO_PIN_11                        ((uint8_t) 11)
#define GPIO_PIN_12                        ((uint8_t) 12)
#define GPIO_PIN_13                        ((uint8_t) 13)
#define GPIO_PIN_14                        ((uint8_t) 14)
#define GPIO_PIN_15                        ((uint8_t) 15)
#define OB_LED_PORT                        (GPIOC)
#define OB_LED_PIN                         (GPIO_PIN_13)

// MODE
#define MODE_IN                            ((uint8_t) 0)
#define MODE_OUT_10MHz                     ((uint8_t) 1)
#define MODE_OUT_2MHz                      ((uint8_t) 2)
#define MODE_OUT_50MHz                     ((uint8_t) 3)

// CNF
#define CNF_IN_ANALOG                      ((uint8_t) 0)
#define CNF_IN_FLOAT                       ((uint8_t) 1)
#define CNF_IN_PU_PD                       ((uint8_t) 2)
#define CNF_OUT_GP_PP                      ((uint8_t) 0)
#define CNF_OUT_GP_OD                      ((uint8_t) 1)
#define CNF_OUT_AF_PP                      ((uint8_t) 2)
#define CNF_OUT_AF_OD                      ((uint8_t) 3)

// AF EXTI
#define AF_EXTI_PA                         ((uint8_t) 0x00)
#define AF_EXTI_PB                         ((uint8_t) 0x01)
#define AF_EXTI_PC                         ((uint8_t) 0x02)
#define AF_EXTI_PD                         ((uint8_t) 0x03)
#define AF_EXTI_PE                         ((uint8_t) 0x04)
#define AF_EXTI_PF                         ((uint8_t) 0x05)
#define AF_EXTI_PG                         ((uint8_t) 0x06)

/**
 * @brief Enables Clock for respective GPIO
 * @param[in] GPIOx The GPIO Port
 */
static inline void enable_GPIO_clk(GPIO_REG_STRUCT* GPIOx);

/**
 * @brief Disables Clock for respective GPIO
 * @param[in] GPIOx The GPIO Port
 */
static inline void disable_GPIO_clk(GPIO_REG_STRUCT* GPIOx);

/**
 * @brief Configures GPIO as per input
 * @param[in] GPIOx `GPIOA`, `GPIOB`, `GPIOC`
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 * @param[in] MODEx Pin Mode `MODE_..`
 * @param[in] CNFx Pin Configuration `CNF_..`
 */
void config_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx, uint8_t MODEx, uint8_t CNFx);

/**
 * @brief Sets a GPIO Pin HIGH
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 */
void set_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx);

/**
 * @brief Resets a GPIO Pin LOW
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 */
void reset_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx);

/**
 * @brief Toggles GPIO Pin
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 */
void toggle_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx);

/**
 * @brief Configures the on-board active low LED (PC13) as GP_OUT-PP-2MHz
 * @note Configuration is done based on capability of the GPIO as mentioned in data sheet
 */
void config_OB_LED(void);

/**
 * @brief Turns on-board active low LED (PC13) ON
 */
void set_OB_LED(void);

/**
 * @brief Turns on-board active low LED (PC13) OFF
 */
void reset_OB_LED(void);

/**
 * @brief Toggles the on-board active low LED (PC13)
 */
void toggle_OB_LED(void);

#endif /* _GPIO_FUNCTION_H_ */
