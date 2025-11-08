/**
 * @file    stm32f1xx_gpio.h
 * @author  Shrey Shah
 * @version v1.2
 * @date    21-10-2025
 *
 * @defgroup GPIO General Purpose Input/Output (GPIO)
 *
 * @brief STM32F1xx General-Purpose Input/Output (GPIO)
 *
 * @details
 * This module provides complete access to GPIO peripherals including:
 * - @ref stm32f1xx_gpio.h "Register mapping"
 * - @ref stm32f1xx.h "Memory Address"
 * - @ref gpio_ll.h "GPIO Low Level (LL) APIs"
 * - @ref gpio.h "GPIO Driver APIs"
 *
 * @note    All GPIO operations require enabled RCC clock for the corresponding GPIO port
 * @warning Direct register access should only be used when performance is critical
 */

#ifndef STM32F1XX_GPIO_H_
#define STM32F1XX_GPIO_H_

// C++ Header Guards
#ifdef __cplusplus
extern "C"
{
#endif

/** @include stdint.h */
#include <stdint.h>

/**
 * @brief Structure encapsulation of GPIO Registers 
 * @defgroup GPIO_01_Registers GPIO Registers
 * @ingroup GPIO
 * @{
 */

/**
 * @defgroup GPIO_01_Registers_01_Structure GPIO Registers Encapsulation
 * @ingroup  GPIO_01_Registers
 * @brief    GPIO Registers representation using structure
 */

/**
 * @defgroup	GPIO_01_Registers_02_Memory GPIO Ports Memory Address
 * @ingroup		GPIO_01_Registers
 * @brief       STM32F1xx GPIO Memory Address Mapping
 */

/**
 * @defgroup GPIO_01_Registers_03_API GPIO Register Access APIs
 * @ingroup GPIO_01_Registers
 * @brief APIs to access @ref GPIO_01_Registers_01_Structure "GPIO Registers"
 */ 

/** @} */ // GPIO_01_Registers

/**
 * @brief GPIO Low Level APIs
 * @defgroup GPIO_02_LL GPIO Low Level APIs
 * @ingroup GPIO
 */

/**
 * @brief GPIO Driver Layer
 * @defgroup GPIO_03_Driver GPIO Driver APIs
 * @ingroup GPIO
 */ 

/**
 * @addtogroup  GPIO_01_Registers
 * @{
 * @details
 * - STM32F103C8T6 GPIO peripherals provide 16 digital I/O pins per port (GPIOA-GPIOG)
 * - Each GPIO port has 7 registers that control configuration, data, and locking functions
 *
 * - GPIO Register Map:
 *
 * | Offset | Register | Name | Description |
 * |--------|----------|------|-------------|
 * | 0x00   | GPIOx_CRL  | Port Configuration Low | Controls mode/speed for pins 0-7 |
 * | 0x04   | GPIOx_CRH  | Port Configuration High | Controls mode/speed for pins 8-15 |
 * | 0x08   | GPIOx_IDR  | Input Data Register | Read input states of all pins |
 * | 0x0C   | GPIOx_ODR  | Output Data Register | Set output states of all pins |
 * | 0x10   | GPIOx_BSRR | Port Bit Set/Reset Register | Atomic set/reset operations |
 * | 0x14   | GPIOx_BRR  | Port Bit Reset Register | Atomic reset operations (legacy) |
 * | 0x18   | GPIOx_LCKR | Port Configuration Lock Register | Lock pin configurations |
 *
 * - Key Features:
 * <ul>
 * <li> Each I/O pin individually configurable as:
 * 	<ul>
 *   <li> Digital input (floating, pull-up, pull-down) </li>
 *   <li> Digital output (push-pull, open-drain) </li>
 *   <li> Analog input (ADC) or alternate function </li>
 * 	</ul
 * </li>
 * <li> Output speeds: 2 MHz, 10 MHz, 50 MHz </li>
 * <li> Atomic set/reset operations for bit-banging </li>
 * <li> Pin configuration locking for safety </li>
 * <li> 3.3V tolerant I/Os </li>
 * </ul>
 *
 * @note GPIOA, GPIOB, GPIOC fully available on STM32F103C8T6
 * @note GPIOD, GPIOE partially available (check pinout)
 * @note GPIOF, GPIOG not available on LQFP48 package
 *
 * @see Reference Manual RM0008 - Section 9. GPIOs
 * @see Datasheet DS5319 - Section 5. Memory mapping
 *
 * @}
 */

/**
 * @addtogroup 03_01_GPIO_PinModes
 *
 * @{
 *
 * @details
 * @section GPIO_Pins_Mode Pin Mode Description
 * - Defines the GPIO Pin Mode: Input / Output
 * - Pattern: Input or Output@slewrate [MHz]
 * - `MODEx` settings:
 *
 *   | MODEx | Mode | Description |
 *   |-------|------|-------------|
 *   | 00    | Input | Input mode (reset state) |
 *   | 01    | Output 10MHz | Output mode, max speed 10 MHz |
 *   | 02    | Output 2MHz  | Output mode, max speed 2 MHz  |
 *   | 03    | Output 50MHz | Output mode, max speed 50 MHz |
 *
 * @}
 */

/**
 * @addtogroup 03_02_GPIO_PinConfig
 *
 * @{
 * @details
 * @section GPIO_Pins_Config Pin Configuration Description
 * - Defines the GPIO Pin Configuration: Analog, Alternate Function, ...
 * - Defines exact functionality of GPIO
 * - `CNFx`:
 *
 * Input Mode: ( @ref GPIO_Pins_Mode "MODEx" == `0x00`)
 * | CNFx  | Configuration | Description |
 * |-------|---------------|-------------|
 * | 00    | Analog        | Analog mode |
 * | 01    | Floating      | Floating input (reset state) |
 * | 10    | Pull-up/down  | Input with pull-up or pull-down |
 *
 * Output Mode: (@ref GPIO_Pins_Mode "MODEx" != `0x00`)
 * | CNFx  | Configuration | Description |
 * |-------|---------------|-------------|
 * | 00    | Push-pull     | General purpose output push-pull |
 * | 01    | Open-drain    | General purpose output Open-drain |
 * | 10    | AF Push-pull  | Alternate function push-pull |
 * | 11    | AF Open-drain | Alternate function open-drain |
 *
 * @}
 */

/**
 * @addtogroup 03_GPIO_Pins 03_01_GPIO_PinModes 03_02_GPIO_PinConfig
 *
 * @{
 *
 * @details
 * @section GPIO_Pins_Summary Summary of Configuration
 *
 * | @ref GPIO_Pins_Mode "MODEx" | @ref GPIO_Pins_Config "CNFx" | Configuration | Description |
 * |-----------|----------|---------------|-------------|
 * | 00 | 00 | Input Analog | Analog input mode |
 * | 00 | 01 | Input Floating | Floating input (reset state) |
 * | 00 | 10 | Input Pull | Input with pull-up/pull-down |
 * | 00 | 11 | Reserved | Not used |
 * | 01 | 00 | Output 10MHz Push-pull | 10MHz output, push-pull |
 * | 01 | 01 | Output 10MHz Open-drain | 10MHz output, open-drain |
 * | 01 | 10 | Output 10MHz AF Push-pull | 10MHz alternate function, push-pull |
 * | 01 | 11 | Output 10MHz AF Open-drain | 10MHz alternate function, open-drain |
 * | 10 | 00 | Output 2MHz Push-pull | 2MHz output, push-pull |
 * | 10 | 01 | Output 2MHz Open-drain | 2MHz output, open-drain |
 * | 10 | 10 | Output 2MHz AF Push-pull | 2MHz alternate function, push-pull |
 * | 10 | 11 | Output 2MHz AF Open-drain | 2MHz alternate function, open-drain |
 * | 11 | 00 | Output 50MHz Push-pull | 50MHz output, push-pull |
 * | 11 | 01 | Output 50MHz Open-drain | 50MHz output, open-drain |
 * | 11 | 10 | Output 50MHz AF Push-pull | 50MHz alternate function, push-pull |
 * | 11 | 11 | Output 50MHz AF Open-drain | 50MHz alternate function, open-drain |
 *
 * @}
 *
 */

/**
 * @addtogroup GPIO_01_Registers_01_Structure
 * @{
 * @details
 * - This structure represents the complete register set for a single GPIO port
 * - It is memory-mapped to the base address of each GPIO peripheral (`GPIOA`, `GPIOB`, etc.)
 * @note The structure uses unions to provide both bit-level and register-level access
 * @see Reference Manual RM0008 - Section 9.2 GPIO registers (Page 171)
 * @typedef GPIO_TypeDef
 */
typedef volatile struct __GPIO_TypeDef
{
	/**
	 * @section GPIO_TypeDef_CRL GPIO Port Configuration Register Low (CRL)
	 * @brief [R/W] Configures pins 0-7 for mode and output type/speed
	 * @details
	 * - Each pin uses 4 bits: 2 for MODE, 2 for CNF
	 * - Pins are configured sequentially from bit 0 to bit 31
	 * - Reset value: 0x4444 4444 (All pins in input floating mode)
	 * - @see @ref GPIO_Pins_Mode "GPIO Pin Mode" | @ref GPIO_Pins_Config "GPIO Pin Configuration" | @ref GPIO_Pins_Summary "GPIO Pin Summary"
	 */
	union GPIO_CRL
	{
		volatile uint32_t REG;
		struct
		{
			volatile uint32_t MODE0 : 2;
			volatile uint32_t CNF0 : 2;
			volatile uint32_t MODE1 : 2;
			volatile uint32_t CNF1 : 2;
			volatile uint32_t MODE2 : 2;
			volatile uint32_t CNF2 : 2;
			volatile uint32_t MODE3 : 2;
			volatile uint32_t CNF3 : 2;
			volatile uint32_t MODE4 : 2;
			volatile uint32_t CNF4 : 2;
			volatile uint32_t MODE5 : 2;
			volatile uint32_t CNF5 : 2;
			volatile uint32_t MODE6 : 2;
			volatile uint32_t CNF6 : 2;
			volatile uint32_t MODE7 : 2;
			volatile uint32_t CNF7 : 2;
		} BIT;
	} CRL;

	/**
	 * @section GPIO_TypeDef_CRH GPIO Port Configuration Register High (CRH)
	 * @brief [R/W] Configures pins 8-15 for mode and output type/speed
	 * @details Configures pins 8-15 for mode and output type/speed
	 * - Same bit structure as CRL but for higher pins
	 * - Each pin uses 4 bits: 2 for MODE, 2 for CNF
	 * - Pins are configured sequentially from bit 0 to bit 31
	 * - Reset value: 0x4444 4444 (All pins in input floating mode)
	 * - @see @ref GPIO_Pins_Mode "GPIO Pin Mode" | @ref GPIO_Pins_Config "GPIO Pin Configuration" | @ref GPIO_Pins_Summary "GPIO Pin Summary"
	 */
	union GPIO_CRH
	{
		volatile uint32_t REG;
		struct
		{
			volatile uint32_t MODE8 : 2;
			volatile uint32_t CNF8 : 2;
			volatile uint32_t MODE9 : 2;
			volatile uint32_t CNF9 : 2;
			volatile uint32_t MODE10 : 2;
			volatile uint32_t CNF10 : 2;
			volatile uint32_t MODE11 : 2;
			volatile uint32_t CNF11 : 2;
			volatile uint32_t MODE12 : 2;
			volatile uint32_t CNF12 : 2;
			volatile uint32_t MODE13 : 2;
			volatile uint32_t CNF13 : 2;
			volatile uint32_t MODE14 : 2;
			volatile uint32_t CNF14 : 2;
			volatile uint32_t MODE15 : 2;
			volatile uint32_t CNF15 : 2;
		} BIT;
	} CRH;

	/**
	 * @section GPIO_TypeDef_IDR GPIO Port Input Data Register (IDR)
	 * @brief [R] Current State of GPIO Pins
	 * @details Read-only register containing current state of input pins
	 * - Each bit represents the logic level on the corresponding GPIO pin
	 * - Only valid for pins configured as input
	 * - Reading this register returns the actual pin state
	 * - Bits 16-31 are reserved and read as 0
	 * - Reset value: 0x0000 XXXX (depends on external circuitry)
	 */
	union GPIO_IDR
	{
		const volatile uint32_t REG;
		struct
		{
			volatile const uint32_t IDR0 : 1;
			volatile const uint32_t IDR1 : 1;
			volatile const uint32_t IDR2 : 1;
			volatile const uint32_t IDR3 : 1;
			volatile const uint32_t IDR4 : 1;
			volatile const uint32_t IDR5 : 1;
			volatile const uint32_t IDR6 : 1;
			volatile const uint32_t IDR7 : 1;
			volatile const uint32_t IDR8 : 1;
			volatile const uint32_t IDR9 : 1;
			volatile const uint32_t IDR10 : 1;
			volatile const uint32_t IDR11 : 1;
			volatile const uint32_t IDR12 : 1;
			volatile const uint32_t IDR13 : 1;
			volatile const uint32_t IDR14 : 1;
			volatile const uint32_t IDR15 : 1;
			volatile const uint32_t RESERVED_IDR : 16;
		} BIT;
	} IDR;

	/**
	 * @section GPIO_TypeDef_ODR GPIO Port Output Data Register (ODR)
	 * @brief [W] Output State of GPIO Pins
	 * @details Sets output state for pins configured as output
	 * - Each bit sets the logic level for the corresponding GPIO pin
	 * - Only effective for pins configured as output
	 * - Writing 1 sets pin high, writing 0 sets pin low
	 * - Reading returns the last written value
	 * - Bits 16-31 are reserved and should be written as 0
	 * - Reset value: 0x0000 0000
	 */
	union GPIO_ODR
	{
		volatile uint32_t REG;
		struct
		{
			volatile uint32_t ODR0 : 1;
			volatile uint32_t ODR1 : 1;
			volatile uint32_t ODR2 : 1;
			volatile uint32_t ODR3 : 1;
			volatile uint32_t ODR4 : 1;
			volatile uint32_t ODR5 : 1;
			volatile uint32_t ODR6 : 1;
			volatile uint32_t ODR7 : 1;
			volatile uint32_t ODR8 : 1;
			volatile uint32_t ODR9 : 1;
			volatile uint32_t ODR10 : 1;
			volatile uint32_t ODR11 : 1;
			volatile uint32_t ODR12 : 1;
			volatile uint32_t ODR13 : 1;
			volatile uint32_t ODR14 : 1;
			volatile uint32_t ODR15 : 1;
			volatile uint32_t RESERVED_ODR : 16;
		} BIT;
	} ODR;

	/**
	 * @section GPIO_TypeDef_BSRR GPIO Port Bit Set/Reset Register (BSRR)
	 * @brief [W] Atomic Set (0-15) + Atomic Reset (16-31) GPIO Pins
	 * @details
	 * - Write-only register for atomic pin control
	 * - Bits 0-15: Set corresponding pin (write 1 to set high)
	 * - Bits 16-31: Reset corresponding pin (write 1 to set low)
	 * - Setting both set and reset bits has undefined behavior
	 * - Reading returns 0x0000
	 * - No read-modify-write required for atomic operations
	 * - Reset value: 0x0000 0000
	 */
	union GPIO_BSRR
	{
		volatile uint32_t REG;
		struct
		{
			volatile uint32_t BS0 : 1;
			volatile uint32_t BS1 : 1;
			volatile uint32_t BS2 : 1;
			volatile uint32_t BS3 : 1;
			volatile uint32_t BS4 : 1;
			volatile uint32_t BS5 : 1;
			volatile uint32_t BS6 : 1;
			volatile uint32_t BS7 : 1;
			volatile uint32_t BS8 : 1;
			volatile uint32_t BS9 : 1;
			volatile uint32_t BS10 : 1;
			volatile uint32_t BS11 : 1;
			volatile uint32_t BS12 : 1;
			volatile uint32_t BS13 : 1;
			volatile uint32_t BS14 : 1;
			volatile uint32_t BS15 : 1;
			volatile uint32_t BR0 : 1;
			volatile uint32_t BR1 : 1;
			volatile uint32_t BR2 : 1;
			volatile uint32_t BR3 : 1;
			volatile uint32_t BR4 : 1;
			volatile uint32_t BR5 : 1;
			volatile uint32_t BR6 : 1;
			volatile uint32_t BR7 : 1;
			volatile uint32_t BR8 : 1;
			volatile uint32_t BR9 : 1;
			volatile uint32_t BR10 : 1;
			volatile uint32_t BR11 : 1;
			volatile uint32_t BR12 : 1;
			volatile uint32_t BR13 : 1;
			volatile uint32_t BR14 : 1;
			volatile uint32_t BR15 : 1;
		} BIT;
	} BSRR;

	/**
	 * @section GPIO_TypeDef_BRR GPIO Port Bit Reset Register (BRR)
	 * @brief [W] Atomic Reset for GPIO Pins
	 * @details
	 * - Write-only register for resetting pins
	 * - Each bit resets the corresponding GPIO pin (write 1 to set low)
	 * - Bits 16-31 are reserved and should be written as 0
	 * - Reading returns 0x0000
	 * - Provides backward compatibility with older STM32 families
	 * - Reset value: 0x0000 0000
	 */
	union GPIO_BRR
	{
		volatile uint32_t REG;
		struct
		{
			volatile uint32_t BR0 : 1;
			volatile uint32_t BR1 : 1;
			volatile uint32_t BR2 : 1;
			volatile uint32_t BR3 : 1;
			volatile uint32_t BR4 : 1;
			volatile uint32_t BR5 : 1;
			volatile uint32_t BR6 : 1;
			volatile uint32_t BR7 : 1;
			volatile uint32_t BR8 : 1;
			volatile uint32_t BR9 : 1;
			volatile uint32_t BR10 : 1;
			volatile uint32_t BR11 : 1;
			volatile uint32_t BR12 : 1;
			volatile uint32_t BR13 : 1;
			volatile uint32_t BR14 : 1;
			volatile uint32_t BR15 : 1;
			volatile uint32_t RESERVED_BRR : 16;
		} BIT;
	} BRR;

	/**
	 * @section GPIO_TypeDef_LCKR GPIO Port Configuration Lock Register (LCKR)
	 * @brief [W] Prevents accidental modification of GPIO until next reset
	 * @details
	 * The **GPIO Lock Mechanism** provides hardware-level protection against
	 * accidental or malicious modification of GPIO configuration registers.
	 *
	 * ##### Locking Principle:
	 * - Once a pin is locked, its configuration in **CRL/CRH registers becomes read-only**
	 * - Locked configuration persists until the **next system reset**
	 * - Lock status is indicated by the **LCKK (Lock Key) bit** (bit 16)
	 * - Lock affects **entire port** but only the specified pins are protected
	 *
	 * ##### Hardware Lock Sequence:
	 * The STM32F1 requires a specific write sequence to activate locking:
	 * 1. **Write 1**: `LCKR[15:0] = pins_to_lock + LCKK = 1`
	 * 2. **Write 2**: `LCKR[15:0] = pins_to_lock + LCKK = 0`
	 * 3. **Write 3**: `LCKR[15:0] = pins_to_lock + LCKK = 1`
	 * 4. **Read Verify**: Check `LCKR[16] == 1` to confirm lock
	 *
	 * ##### Use Cases:
	 * - **Safety-critical** applications (emergency stop, watchdog)
	 * - **Production firmware** to prevent field modifications
	 * - **Secure boot** configurations
	 * - **Regulatory compliance** requiring hardware protection
	 *
	 * ##### Important Limitations:
	 * - 🔒 **Lock applies to entire GPIO port** (cannot lock individual pins separately)
	 * - 🔒 **Locked pins cannot be reconfigured** until system reset
	 * - 🔒 **Lock cannot be selectively removed** - only reset clears it
	 * - ⚠️  **Use with extreme caution** in development
	 */
	union GPIO_LCKR
	{
		volatile uint32_t REG;
		struct
		{
			volatile uint32_t LCK0 : 1;
			volatile uint32_t LCK1 : 1;
			volatile uint32_t LCK2 : 1;
			volatile uint32_t LCK3 : 1;
			volatile uint32_t LCK4 : 1;
			volatile uint32_t LCK5 : 1;
			volatile uint32_t LCK6 : 1;
			volatile uint32_t LCK7 : 1;
			volatile uint32_t LCK8 : 1;
			volatile uint32_t LCK9 : 1;
			volatile uint32_t LCK10 : 1;
			volatile uint32_t LCK11 : 1;
			volatile uint32_t LCK12 : 1;
			volatile uint32_t LCK13 : 1;
			volatile uint32_t LCK14 : 1;
			volatile uint32_t LCK15 : 1;
			volatile uint32_t LCKK : 1;
			volatile uint32_t RESERVED_LCKR : 15;
		} BIT;
	} LCKR;
} GPIO_TypeDef;

/** @} */ // GPIO_01_Registers_01_Structure

// C++ Header Guards
#ifdef __cplusplus
}
#endif

#endif /* STM32F1XX_GPIO_H_ */