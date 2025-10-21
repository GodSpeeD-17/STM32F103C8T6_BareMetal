/**
 * @file    stm32f1xx_gpio.h
 * @author  Shrey Shah
 * @brief   STM32F1xx General-Purpose Input/Output (GPIO) Peripheral Address Structure
 * @version v1.2
 * @date    21-10-2025
 *
 * @defgroup GPIO GPIO
 * @brief    Hardware abstraction layer for STM32F1xx GPIO peripherals
 * 
 * @details This module provides complete access to GPIO peripherals including:
 *          - Register mapping and memory addresses
 *          - Configuration structures and enumerations  
 *          - Hardware abstraction APIs
 *          - Pin control and management functions
 * 
 * The module is organized as follows:
 * @subpage gpio_organization "GPIO Module Organization"
 * 
 * @note All GPIO operations require enabled RCC clock for the corresponding GPIO port
 * @warning Direct register access should only be used when performance is critical
 * 
 * 
 */

// Header Guards
#ifndef STM32F1XX_GPIO_H_
#define STM32F1XX_GPIO_H_

// C++ Safeguard
#ifdef __cplusplus
extern "C" {
#endif

// Includes
#include <stdint.h>

/**
 * @ingroup  GPIO
 * @defgroup GPIO_RegisterMap GPIO Register Mapping Structure
 * @brief    GPIO Peripheral Register definitions and memory mapping
 * @{
 */

/**
 * @brief General-Purpose Input/Output (GPIO) Register Mapping Structure
 * 
 * @details This structure represents the complete register set for a single GPIO port.
 * It is memory-mapped to the base address of each GPIO peripheral (GPIOA, GPIOB, etc.).
 * 
 * @note The structure uses unions to provide both bit-level and register-level access
 * @see Reference Manual RM0008 - Section 9.2 GPIO registers (Page 171)
 */
typedef struct {
	/**
	 * @brief GPIO Port Configuration Register Low (CRL)
	 * @details Configures pins 0-7 for mode and output type/speed
	 */
	union {
		volatile uint32_t REG;  ///< Full 32-bit register access
		struct {
			volatile uint32_t MODE0  : 2;  ///< Pin 0 mode (00=Input, 01=Output 10MHz, 10=Output 2MHz, 11=Output 50MHz)
			volatile uint32_t CNF0   : 2;  ///< Pin 0 configuration (depends on mode)
			volatile uint32_t MODE1  : 2;  ///< Pin 1 mode
			volatile uint32_t CNF1   : 2;  ///< Pin 1 configuration
			volatile uint32_t MODE2  : 2;  ///< Pin 2 mode
			volatile uint32_t CNF2   : 2;  ///< Pin 2 configuration
			volatile uint32_t MODE3  : 2;  ///< Pin 3 mode
			volatile uint32_t CNF3   : 2;  ///< Pin 3 configuration
			volatile uint32_t MODE4  : 2;  ///< Pin 4 mode
			volatile uint32_t CNF4   : 2;  ///< Pin 4 configuration
			volatile uint32_t MODE5  : 2;  ///< Pin 5 mode
			volatile uint32_t CNF5   : 2;  ///< Pin 5 configuration
			volatile uint32_t MODE6  : 2;  ///< Pin 6 mode
			volatile uint32_t CNF6   : 2;  ///< Pin 6 configuration
			volatile uint32_t MODE7  : 2;  ///< Pin 7 mode
			volatile uint32_t CNF7   : 2;  ///< Pin 7 configuration
		} BIT;
	} CRL;

	/**
	 * @brief GPIO Port Configuration Register High (CRH)  
	 * @details Configures pins 8-15 for mode and output type/speed
	 */
	union {
		volatile uint32_t REG;  ///< Full 32-bit register access
		struct {
			volatile uint32_t MODE8  : 2;  ///< Pin 8 mode
			volatile uint32_t CNF8   : 2;  ///< Pin 8 configuration
			volatile uint32_t MODE9  : 2;  ///< Pin 9 mode
			volatile uint32_t CNF9   : 2;  ///< Pin 9 configuration
			volatile uint32_t MODE10 : 2;  ///< Pin 10 mode
			volatile uint32_t CNF10  : 2;  ///< Pin 10 configuration
			volatile uint32_t MODE11 : 2;  ///< Pin 11 mode
			volatile uint32_t CNF11  : 2;  ///< Pin 11 configuration
			volatile uint32_t MODE12 : 2;  ///< Pin 12 mode
			volatile uint32_t CNF12  : 2;  ///< Pin 12 configuration
			volatile uint32_t MODE13 : 2;  ///< Pin 13 mode
			volatile uint32_t CNF13  : 2;  ///< Pin 13 configuration
			volatile uint32_t MODE14 : 2;  ///< Pin 14 mode
			volatile uint32_t CNF14  : 2;  ///< Pin 14 configuration
			volatile uint32_t MODE15 : 2;  ///< Pin 15 mode
			volatile uint32_t CNF15  : 2;  ///< Pin 15 configuration
		} BIT;
	} CRH;

	/**
	 * @brief GPIO Port Input Data Register (IDR)
	 * @details Read-only register containing current state of input pins
	 */
	union {
		volatile const uint32_t REG;  ///< Read-only 32-bit register access
		struct {
			volatile const uint32_t IDR0   : 1;  ///< Pin 0 input state
			volatile const uint32_t IDR1   : 1;  ///< Pin 1 input state
			volatile const uint32_t IDR2   : 1;  ///< Pin 2 input state
			volatile const uint32_t IDR3   : 1;  ///< Pin 3 input state
			volatile const uint32_t IDR4   : 1;  ///< Pin 4 input state
			volatile const uint32_t IDR5   : 1;  ///< Pin 5 input state
			volatile const uint32_t IDR6   : 1;  ///< Pin 6 input state
			volatile const uint32_t IDR7   : 1;  ///< Pin 7 input state
			volatile const uint32_t IDR8   : 1;  ///< Pin 8 input state
			volatile const uint32_t IDR9   : 1;  ///< Pin 9 input state
			volatile const uint32_t IDR10  : 1;  ///< Pin 10 input state
			volatile const uint32_t IDR11  : 1;  ///< Pin 11 input state
			volatile const uint32_t IDR12  : 1;  ///< Pin 12 input state
			volatile const uint32_t IDR13  : 1;  ///< Pin 13 input state
			volatile const uint32_t IDR14  : 1;  ///< Pin 14 input state
			volatile const uint32_t IDR15  : 1;  ///< Pin 15 input state
			volatile const uint32_t RESERVED_IDR : 16; ///< Reserved bits
		} BIT;
	} IDR;

	/**
	 * @brief GPIO Port Output Data Register (ODR)
	 * @details Sets output state for pins configured as output
	 */
	union {
		volatile uint32_t REG;  ///< Full 32-bit register access
		struct {
			volatile uint32_t ODR0   : 1;  ///< Pin 0 output state
			volatile uint32_t ODR1   : 1;  ///< Pin 1 output state
			volatile uint32_t ODR2   : 1;  ///< Pin 2 output state
			volatile uint32_t ODR3   : 1;  ///< Pin 3 output state
			volatile uint32_t ODR4   : 1;  ///< Pin 4 output state
			volatile uint32_t ODR5   : 1;  ///< Pin 5 output state
			volatile uint32_t ODR6   : 1;  ///< Pin 6 output state
			volatile uint32_t ODR7   : 1;  ///< Pin 7 output state
			volatile uint32_t ODR8   : 1;  ///< Pin 8 output state
			volatile uint32_t ODR9   : 1;  ///< Pin 9 output state
			volatile uint32_t ODR10  : 1;  ///< Pin 10 output state
			volatile uint32_t ODR11  : 1;  ///< Pin 11 output state
			volatile uint32_t ODR12  : 1;  ///< Pin 12 output state
			volatile uint32_t ODR13  : 1;  ///< Pin 13 output state
			volatile uint32_t ODR14  : 1;  ///< Pin 14 output state
			volatile uint32_t ODR15  : 1;  ///< Pin 15 output state
			volatile uint32_t RESERVED_ODR : 16; ///< Reserved bits
		} BIT;
	} ODR;

	/**
	 * @brief GPIO Port Bit Set/Reset Register (BSRR)
	 * @details Atomic set/reset operations (bits 0-15 set, bits 16-31 reset)
	 */
	union {
		volatile uint32_t REG;  ///< Full 32-bit register access
		struct {
			volatile uint32_t BS0    : 1;  ///< Set Pin 0 (write 1 to set)
			volatile uint32_t BS1    : 1;  ///< Set Pin 1
			volatile uint32_t BS2    : 1;  ///< Set Pin 2
			volatile uint32_t BS3    : 1;  ///< Set Pin 3
			volatile uint32_t BS4    : 1;  ///< Set Pin 4
			volatile uint32_t BS5    : 1;  ///< Set Pin 5
			volatile uint32_t BS6    : 1;  ///< Set Pin 6
			volatile uint32_t BS7    : 1;  ///< Set Pin 7
			volatile uint32_t BS8    : 1;  ///< Set Pin 8
			volatile uint32_t BS9    : 1;  ///< Set Pin 9
			volatile uint32_t BS10   : 1;  ///< Set Pin 10
			volatile uint32_t BS11   : 1;  ///< Set Pin 11
			volatile uint32_t BS12   : 1;  ///< Set Pin 12
			volatile uint32_t BS13   : 1;  ///< Set Pin 13
			volatile uint32_t BS14   : 1;  ///< Set Pin 14
			volatile uint32_t BS15   : 1;  ///< Set Pin 15
			volatile uint32_t BR0    : 1;  ///< Reset Pin 0 (write 1 to reset)
			volatile uint32_t BR1    : 1;  ///< Reset Pin 1
			volatile uint32_t BR2    : 1;  ///< Reset Pin 2
			volatile uint32_t BR3    : 1;  ///< Reset Pin 3
			volatile uint32_t BR4    : 1;  ///< Reset Pin 4
			volatile uint32_t BR5    : 1;  ///< Reset Pin 5
			volatile uint32_t BR6    : 1;  ///< Reset Pin 6
			volatile uint32_t BR7    : 1;  ///< Reset Pin 7
			volatile uint32_t BR8    : 1;  ///< Reset Pin 8
			volatile uint32_t BR9    : 1;  ///< Reset Pin 9
			volatile uint32_t BR10   : 1;  ///< Reset Pin 10
			volatile uint32_t BR11   : 1;  ///< Reset Pin 11
			volatile uint32_t BR12   : 1;  ///< Reset Pin 12
			volatile uint32_t BR13   : 1;  ///< Reset Pin 13
			volatile uint32_t BR14   : 1;  ///< Reset Pin 14
			volatile uint32_t BR15   : 1;  ///< Reset Pin 15
		} BIT;
	} BSRR;

	/**
	 * @brief GPIO Port Bit Reset Register (BRR)
	 * @details Reset-only register (alternative to BSRR reset bits)
	 */
	union {
		volatile uint32_t REG;  ///< Full 32-bit register access
		struct {
			volatile uint32_t BR0    : 1;  ///< Reset Pin 0
			volatile uint32_t BR1    : 1;  ///< Reset Pin 1
			volatile uint32_t BR2    : 1;  ///< Reset Pin 2
			volatile uint32_t BR3    : 1;  ///< Reset Pin 3
			volatile uint32_t BR4    : 1;  ///< Reset Pin 4
			volatile uint32_t BR5    : 1;  ///< Reset Pin 5
			volatile uint32_t BR6    : 1;  ///< Reset Pin 6
			volatile uint32_t BR7    : 1;  ///< Reset Pin 7
			volatile uint32_t BR8    : 1;  ///< Reset Pin 8
			volatile uint32_t BR9    : 1;  ///< Reset Pin 9
			volatile uint32_t BR10   : 1;  ///< Reset Pin 10
			volatile uint32_t BR11   : 1;  ///< Reset Pin 11
			volatile uint32_t BR12   : 1;  ///< Reset Pin 12
			volatile uint32_t BR13   : 1;  ///< Reset Pin 13
			volatile uint32_t BR14   : 1;  ///< Reset Pin 14
			volatile uint32_t BR15   : 1;  ///< Reset Pin 15
			volatile uint32_t RESERVED_BRR : 16; ///< Reserved bits
		} BIT;
	} BRR;

	/**
	 * @brief GPIO Port Configuration Lock Register (LCKR)
	 * @details Locks pin configuration until next reset
	 */
	union {
		volatile uint32_t REG;  ///< Full 32-bit register access
		struct {
			volatile uint32_t LCK0   : 1;  ///< Lock Pin 0 configuration
			volatile uint32_t LCK1   : 1;  ///< Lock Pin 1 configuration
			volatile uint32_t LCK2   : 1;  ///< Lock Pin 2 configuration
			volatile uint32_t LCK3   : 1;  ///< Lock Pin 3 configuration
			volatile uint32_t LCK4   : 1;  ///< Lock Pin 4 configuration
			volatile uint32_t LCK5   : 1;  ///< Lock Pin 5 configuration
			volatile uint32_t LCK6   : 1;  ///< Lock Pin 6 configuration
			volatile uint32_t LCK7   : 1;  ///< Lock Pin 7 configuration
			volatile uint32_t LCK8   : 1;  ///< Lock Pin 8 configuration
			volatile uint32_t LCK9   : 1;  ///< Lock Pin 9 configuration
			volatile uint32_t LCK10  : 1;  ///< Lock Pin 10 configuration
			volatile uint32_t LCK11  : 1;  ///< Lock Pin 11 configuration
			volatile uint32_t LCK12  : 1;  ///< Lock Pin 12 configuration
			volatile uint32_t LCK13  : 1;  ///< Lock Pin 13 configuration
			volatile uint32_t LCK14  : 1;  ///< Lock Pin 14 configuration
			volatile uint32_t LCK15  : 1;  ///< Lock Pin 15 configuration
			volatile uint32_t LCKK   : 1;  ///< Lock key (write sequence required)
			volatile uint32_t RESERVED_LCKR : 15; ///< Reserved bits
		} BIT;
	} LCKR;
} GPIO_TypeDef;

/** @} */ // End of GPIO_RegisterMap

#ifdef __cplusplus
}
#endif

#endif /* STM32F1XX_GPIO_H_ */