/***************************************************************************************
 *  File: gpio.h
 *  Created on: 14/09/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __GPIO__H__
#define __GPIO__H__

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
#define CNF_IN_PD                          ((uint8_t) 3)
#define CNF_IN_PU                          ((uint8_t) 4)
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
void enable_GPIO_clk(GPIO_REG_STRUCT* GPIOx);

/**
 * @brief Disables Clock for respective GPIO
 * @param[in] GPIOx The GPIO Port
 */
void disable_GPIO_clk(GPIO_REG_STRUCT* GPIOx);

/**
 * @brief Configures GPIO as per input
 * @param[in] GPIOx `GPIOA`, `GPIOB`, `GPIOC`
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 * @param[in] MODEx Pin Mode `MODE_..`
 * @param[in] CNFx Pin Configuration `CNF_..`
 * @note Does not configure PC13, PC14, PC15
 */
void config_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx, uint8_t MODEx, uint8_t CNFx);

/**
 * @brief Sets a GPIO Pin HIGH
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 */
__attribute__((always_inline)) inline void set_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx){
	// Bit Set (Atomicity)
	GPIOx->BSRR.REG = (BIT_SET << PINx);
}

/**
 * @brief Gets the status of GPIO Pin
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 * @returns `BIT_SET`, `BIT_RESET`
 */
uint8_t get_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx);

/**
 * @brief Resets a GPIO Pin LOW
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 */
__attribute__((always_inline)) inline void reset_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx) {
	// Bit Reset (Atomicity)
	GPIOx->BRR.REG = (BIT_SET << PINx);
}

/**
 * @brief Toggles GPIO Pin
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 */
__attribute__((always_inline)) inline void toggle_GPIO(GPIO_REG_STRUCT* GPIOx, uint8_t PINx){
	// Toggle the GPIO Pin
	GPIOx->ODR.REG ^= (BIT_SET << PINx);
}

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

/**
 * @brief Sets the GPIO to be used in Input Pull Up Mode
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 */
/*
__attribute__((always_inline)) inline void config_GPIO_IN_PU(GPIO_REG_STRUCT* GPIOx, uint8_t PINx){
    // Configure the GPIO as Input Pull Up / Pull Down
    config_GPIO(GPIOx, PINx, MODE_IN, CNF_IN_PU_PD);
    // Refer Table 20 (PDF Page 161)
    GPIOx->ODR.REG |= (BIT_SET << PINx);
}
*/


/**
 * @brief Sets the GPIO to be used in Input Pull Down Mode
 * @param[in] GPIOx GPIOA, GPIOB, GPIOC
 * @param[in] PINx GPIO Pin Number
 */
__attribute__((always_inline)) inline void config_GPIO_IN_PD(GPIO_REG_STRUCT* GPIOx, uint8_t PINx){
    // Configure the GPIO as Input Pull Up / Pull Down
    config_GPIO(GPIOx, PINx, MODE_IN, CNF_IN_PU_PD);
    // Refer Table 20 (PDF Page 161)
    GPIOx->ODR.REG &= ~(BIT_SET << PINx);
} 

/*
__attribute__((always_inline)) inline void config_GPIO_IN_PD(GPIO_REG_STRUCT* GPIOx, uint8_t PINx){
    // Enable Clock
    enable_GPIO_clk(GPIOx);
    // PINx >= 8 
    if(PINx > 7 && PINx < 16){
		// Return on PC13, PC14, PC15
		if((GPIOx == GPIOC) && (PINx > (uint8_t)12))
			return;
        // Configure for pull down mode
        GPIOx->ODR.REG &= ~(BIT_SET << PINx); 
		// Clear Reset State (0x04 i.e Floating State)
		GPIOx->CRH.REG &= ~(uint32_t)(0x0F << (4 * (PINx - 8)));
		// MODE + CONFIGURATION
		GPIOx->CRH.REG |= (uint32_t)((MODEx << (4 * (PINx - 8))) | (CNFx << ((4 * (PINx - 8)) + 2)));
	}
    // PINx <= 7
	else if (PINx <= 7){
        // Configure for pull down mode
        GPIOx->ODR.REG &= ~(BIT_SET << PINx); 
		// Clear Reset State (0x04 i.e Floating State)
		GPIOx->CRL.REG &= ~((uint32_t)(0x0F << (4 * PINx)));
		// MODE + CONFIGURATION
		GPIOx->CRL.REG |= (uint32_t)((MODEx << (4 * PINx)) | (CNFx << ((4 * PINx) + 2)));
	}
	// Error Condition
	else{
		return;
	}

    
}
*/

#endif /* __GPIO__H__ */
