/**
 * @file stm32f1xx_rcc.h
 * @author Shrey Shah
 * @version v1.0
 * @date 08-11-2025
 * @defgroup RCC Reset & Clock Control (RCC)
 * @details
 * This module provides complete access to RCC peripheral including:
 * - @ref stm32f1xx_rcc.h "Register mapping"
 * - @ref stm32f1xx.h "Memory Address"
 * - @ref rcc_ll.h "RCC Low Level (LL) APIs"
 * - @ref rcc.h "RCC Driver APIs"
 *
 * @note    All peripheral clock operations require proper RCC configuration
 * @warning Direct register access should only be used when performance is critical
 */
// Header Guards
#ifndef STM32F1XX_RCC_H_
#define STM32F1XX_RCC_H_

// C++ Safeguards
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @include stdint */
#include <stdint.h>

/**
 * @brief RCC Peripheral Hardware Register Mapping
 * @defgroup  RCC_01_Registers RCC Registers
 * @ingroup   RCC
 * @details
 * - STM32F103C8T6 RCC peripheral controls system clocks, resets, and clock gating
 * - Manages multiple clock sources and distribution to all peripherals
 *
 * - RCC Register Map:
 *
 * | Offset | Register | Name | Description |
 * |--------|----------|------|-------------|
 * | 0x00   | RCC_CR     | Clock Control Register | Controls internal/external clock sources |
 * | 0x04   | RCC_CFGR   | Clock Configuration Register | Configures clock dividers and PLL |
 * | 0x08   | RCC_CIR    | Clock Interrupt Register | Manages clock-related interrupts |
 * | 0x0C   | RCC_APB2RSTR | APB2 Peripheral Reset Register | Resets APB2 peripherals |
 * | 0x10   | RCC_APB1RSTR | APB1 Peripheral Reset Register | Resets APB1 peripherals |
 * | 0x14   | RCC_AHBENR  | AHB Peripheral Clock Enable Register | Enables AHB peripherals |
 * | 0x18   | RCC_APB2ENR | APB2 Peripheral Clock Enable Register | Enables APB2 peripherals |
 * | 0x1C   | RCC_APB1ENR | APB1 Peripheral Clock Enable Register | Enables APB1 peripherals |
 * | 0x20   | RCC_BDCR    | Backup Domain Control Register | Controls RTC and backup domain |
 * | 0x24   | RCC_CSR     | Control/Status Register | Controls LSI and reset status |
 *
 * - Key Features:
 * <ul>
 * <li> Multiple clock sources:
 * 	<ul>
 *   <li> HSI: 8 MHz internal RC oscillator </li>
 *   <li> HSE: 4-16 MHz external crystal/oscillator </li>
 *   <li> PLL: Clock multiplier for system clock </li>
 *   <li> LSI: 40 kHz internal RC for IWDG </li>
 *   <li> LSE: 32.768 kHz external crystal for RTC </li>
 * 	</ul>
 * </li>
 * <li> Flexible clock distribution with prescalers </li>
 * <li> Individual peripheral clock gating for power management </li>
 * <li> Clock security system (CSS) for HSE failure detection </li>
 * <li> Backup domain with independent power supply </li>
 * </ul>
 *
 * @note System clock configuration must follow proper sequence
 * @warning Changing clock settings during operation may cause system instability
 *
 * @see Reference Manual RM0008 - Section 7. Reset and Clock Control (RCC)
 * @see Datasheet DS5319 - Section 5. Memory mapping
 * @{ 
 */

/**
 * @defgroup RCC_01_Registers_01_Structure RCC Registers Encapsulation
 * @ingroup  RCC_01_Registers
 * @brief    RCC Registers representation using structure
 */

/**
 * @defgroup RCC_01_Registers_02_Memory RCC Memory Address
 * @ingroup  RCC_01_Registers 
 * @brief    STM32F1xx RCC Memory Address Mapping
 */

/**
 * @defgroup RCC_01_Registers_03_API RCC Register Access APIs
 * @ingroup  RCC_01_Registers 
 * @brief    APIs to access @ref RCC_01_Registers_01_Structure "RCC Registers"
 */

/** @} */ // RCC_01_Registers

/**
 * @defgroup RCC_02_LL RCC Low Level APIs
 * @ingroup  RCC
 * @brief 	 RCC Low Level APIs
 */

/**
 * @defgroup RCC_03_Driver RCC Driver APIs
 * @ingroup  RCC
 * @brief 	 RCC Driver APIs
 */

/**
 * @addtogroup RCC_01_Registers_01_Structure
 * @{
 * @details
 * - This structure represents the complete register set for RCC peripheral
 * - It is memory-mapped to the RCC base address
 * @note The structure uses unions to provide both bit-level and register-level access
 * @see Reference Manual RM0008 - Section 7.3 RCC registers (Page 113) 
 * @typedef RCC_TypeDef
 */
typedef volatile struct __RCC_TypeDef
{
	/**
	 * @brief Clock Control Register
	 * @details
	 * Controls the internal and external clock sources including HSI, HSE, and PLL.
	 * Manages oscillator enable/disable, ready status, calibration, and clock security system.
	 * This register must be configured before any clock switching operations.
	 */
	union RCC_CR
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t HSION: 1;
			volatile uint32_t HSIRDY: 1;
			volatile uint32_t reserved_1: 1;
			volatile uint32_t HSITRIM: 5;
			volatile uint32_t HSICAL: 8;
			volatile uint32_t HSEON: 1;
			volatile uint32_t HSERDY: 1;
			volatile uint32_t HSEBYP: 1;
			volatile uint32_t CSSON: 1;
			volatile uint32_t reserved_2: 4;
			volatile uint32_t PLLON: 1;
			volatile uint32_t PLLRDY: 1;
			volatile uint32_t reserved_3: 6;
		} BIT;
	} CR;
	/**
	 * @brief Clock Configuration Register  
	 * @details
	 * Configures the system clock source, prescalers for AHB, APB1, APB2 buses,
	 * PLL multiplication factor, and clock output selection. This register determines
	 * the final system clock frequency and peripheral clock speeds.
	 */
	union RCC_CFGR 
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t SW: 2;
			volatile uint32_t SWS: 2;
			volatile uint32_t HPRE: 4;
			volatile uint32_t PPRE1: 3;
			volatile uint32_t PPRE2: 3;
			volatile uint32_t ADCPRE: 2;
			volatile uint32_t PLLSRC: 1;
			volatile uint32_t PLLXTPRE: 1;
			volatile uint32_t PLLMUL: 4;
			volatile uint32_t USBPRE: 1;
			volatile uint32_t reserved_1: 1;
			volatile uint32_t MCO: 3;
			volatile uint32_t reserved_2: 5;
		} BIT;
	} CFGR;
	/**
	 * @brief Clock Interrupt Register
	 * @details
	 * Manages interrupt flags and enable bits for various clock events including
	 * oscillator ready flags, PLL lock, and clock security system interrupts.
	 * Provides clear bits to reset interrupt flags.
	 */
	union RCC_CIR 
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t LSIRDYF: 1;
			volatile uint32_t LSERDYF: 1;
			volatile uint32_t HSIRDYF: 1;
			volatile uint32_t HSERDYF: 1;
			volatile uint32_t PLLRDYF: 1;
			volatile uint32_t reserved_1: 2;
			volatile uint32_t CSFF: 1;
			volatile uint32_t LSIRDYIE: 1;
			volatile uint32_t LSERDYIE: 1;
			volatile uint32_t HSIRDYIE: 1;
			volatile uint32_t HSERDYIE: 1;
			volatile uint32_t PLLRDYIE: 1;
			volatile uint32_t reserved_2: 3;
			volatile uint32_t LSIRDYC: 1;
			volatile uint32_t LSERDYC: 1;
			volatile uint32_t HSIRDYC: 1;
			volatile uint32_t HSERDYC: 1;
			volatile uint32_t PLLRDYC: 1;
			volatile uint32_t reserved_3: 2;
			volatile uint32_t CSSC: 1;
			volatile uint32_t reserved_4: 8;
		} BIT;
	} CIR;
	/**
	 * @brief APB2 Peripheral Reset Register
	 * @details
	 * Controls the reset functionality for peripherals connected to APB2 bus.
	 * Writing 1 to any bit asserts reset for the corresponding peripheral,
	 * writing 0 releases reset. Includes GPIO ports, ADC, TIM1, SPI1, USART1.
	 */
	union RCC_APB2RSTR 
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t AFIORST: 1;
			volatile uint32_t reserved_1: 1;
			volatile uint32_t IOPARST: 1;
			volatile uint32_t IOPBRST: 1;
			volatile uint32_t IOPCRST: 1;
			volatile uint32_t IOPDRST: 1;
			volatile uint32_t IOPERST: 1;
			volatile uint32_t IOPFRST: 1;
			volatile uint32_t IOPGRST: 1;
			volatile uint32_t ADC1RST: 1;
			volatile uint32_t ADC2RST: 1;
			volatile uint32_t TIM1RST: 1;
			volatile uint32_t SPI1RST: 1;
			volatile uint32_t TIM8RST: 1;
			volatile uint32_t USART1RST: 1;
			volatile uint32_t ADC3RST: 1;
			volatile uint32_t reserved_2: 3;
			volatile uint32_t TIM9RST: 1;
			volatile uint32_t TIM10RST: 1;
			volatile uint32_t TIM11RST: 1;
			volatile uint32_t reserved_3: 10;
		} BIT;
	} APB2RSTR;
	/**
	 * @brief APB1 Peripheral Reset Register
	 * @details
	 * Controls the reset functionality for peripherals connected to APB1 bus.
	 * Writing 1 to any bit asserts reset for the corresponding peripheral,
	 * writing 0 releases reset. Includes timers, watchdogs, SPI, USART, I2C, USB, CAN.
	 */
	union RCC_APB1RSTR
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t TIM2RST: 1;
			volatile uint32_t TIM3RST: 1;
			volatile uint32_t TIM4RST: 1;
			volatile uint32_t TIM5RST: 1;
			volatile uint32_t TIM6RST: 1;
			volatile uint32_t TIM7RST: 1;
			volatile uint32_t TIM12RST: 1;
			volatile uint32_t TIM13RST: 1;
			volatile uint32_t TIM14RST: 1;
			volatile uint32_t reserved_1: 1;
			volatile uint32_t WWDGRST: 1;
			volatile uint32_t reserved_2: 2;
			volatile uint32_t SPI2RST: 1;
			volatile uint32_t SPI3RST: 1;
			volatile uint32_t reserved_3: 1;
			volatile uint32_t USART2RST: 1;
			volatile uint32_t USART3RST: 1;
			volatile uint32_t UART4RST: 1;
			volatile uint32_t UART5RST: 1;
			volatile uint32_t I2C1RST: 1;
			volatile uint32_t I2C2RST: 1;
			volatile uint32_t USBRST: 1;
			volatile uint32_t reserved_4: 1;
			volatile uint32_t CANRST: 1;
			volatile uint32_t reserved_5: 1;
			volatile uint32_t BKPRST: 1;
			volatile uint32_t PWRRST: 1;
			volatile uint32_t DACRST: 1;
			volatile uint32_t reserved_6: 2;
		} BIT;
	} APB1RSTR;
	/**
	 * @brief AHB Peripheral Clock Enable Register
	 * @details
	 * Controls clock gating for peripherals connected to AHB bus.
	 * Enables or disables clocks to DMA, SRAM, FLASH, CRC, FSMC, and SDIO peripherals.
	 * Disabling unused peripheral clocks reduces power consumption.
	 */
	union RCC_AHBENR
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t DMA1EN: 1;
			volatile uint32_t DMA2EN: 1;
			volatile uint32_t SRAMEN: 1;
			volatile uint32_t reserved_1: 1;
			volatile uint32_t FLITFEN: 1;
			volatile uint32_t reserved_2: 1;
			volatile uint32_t CRCEN: 1;
			volatile uint32_t reserved_3: 1;
			volatile uint32_t FSMCEN: 1;
			volatile uint32_t reserved_4: 1;
			volatile uint32_t SDIOEN: 1;
			volatile uint32_t reserved_5: 21;
		} BIT;
	} AHBENR;
	/**
	 * @brief APB2 Peripheral Clock Enable Register
	 * @details
	 * Controls clock gating for peripherals connected to APB2 bus.
	 * Enables or disables clocks to AFIO, GPIO ports, ADC, advanced timers,
	 * SPI1, and USART1. Essential for GPIO and communication peripheral operation.
	 */
	union RCC_APB2ENR
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t AFIOEN: 1;
			volatile uint32_t reserved_1: 1;
			volatile uint32_t IOPAEN: 1;
			volatile uint32_t IOPBEN: 1;
			volatile uint32_t IOPCEN: 1;
			volatile uint32_t IOPDEN: 1;
			volatile uint32_t IOPEEN: 1;
			volatile uint32_t IOPFEN: 1;
			volatile uint32_t IOPGEN: 1;
			volatile uint32_t ADC1EN: 1;
			volatile uint32_t ADC2EN: 1;
			volatile uint32_t TIM1EN: 1;
			volatile uint32_t SPI1EN: 1;
			volatile uint32_t TIM8EN: 1;
			volatile uint32_t USART1EN: 1;
			volatile uint32_t ADC3EN: 1;
			volatile uint32_t reserved_2: 3;
			volatile uint32_t TIM9EN: 1;
			volatile uint32_t TIM10EN: 1;
			volatile uint32_t TIM11EN: 1;
			volatile uint32_t reserved_3: 10;
		} BIT;
	} APB2ENR;
	/**
	 * @brief APB1 Peripheral Clock Enable Register
	 * @details
	 * Controls clock gating for peripherals connected to APB1 bus.
	 * Enables or disables clocks to general-purpose timers, watchdogs,
	 * SPI2/3, USART2-5, I2C, USB, CAN, backup interface, power, and DAC.
	 * Critical for timer and communication peripheral operation.
	 */
	union RCC_APB1ENR
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t TIM2EN: 1;
			volatile uint32_t TIM3EN: 1;
			volatile uint32_t TIM4EN: 1;
			volatile uint32_t TIM5EN: 1;
			volatile uint32_t TIM6EN: 1;
			volatile uint32_t TIM7EN: 1;
			volatile uint32_t TIM12EN: 1;
			volatile uint32_t TIM13EN: 1;
			volatile uint32_t TIM14EN: 1;
			volatile uint32_t reserved_1: 2;
			volatile uint32_t WWDGEN: 1;
			volatile uint32_t reserved_2: 2;
			volatile uint32_t SPI2EN: 1;
			volatile uint32_t SPI3EN: 1;
			volatile uint32_t reserved_3: 1;
			volatile uint32_t USART2EN: 1;
			volatile uint32_t USART3EN: 1;
			volatile uint32_t UART4EN: 1;
			volatile uint32_t UART5EN: 1;
			volatile uint32_t I2C1EN: 1;
			volatile uint32_t I2C2EN: 1;
			volatile uint32_t USBEN: 1;
			volatile uint32_t reserved_4: 1;
			volatile uint32_t CANEN: 1;
			volatile uint32_t reserved_5: 1;
			volatile uint32_t BKPEN: 1;
			volatile uint32_t PWREN: 1;
			volatile uint32_t DACEN: 1;
			volatile uint32_t reserved_6: 2;
		} BIT;
	} APB1ENR;
	/**
	 * @brief Backup Domain Control Register
	 * @details
	 * Controls the backup domain including LSE oscillator and RTC configuration.
	 * Manages RTC clock source selection, RTC enable, and backup domain reset.
	 * This register is not reset by system reset, only by backup domain reset.
	 */
	union RCC_BDCR
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t LSEON: 1;
			volatile uint32_t LSERDY: 1;
			volatile uint32_t LSEBYP: 1;
			volatile uint32_t reserved_1: 5;
			volatile uint32_t RTCSEL: 2;
			volatile uint32_t reserved_2: 5;
			volatile uint32_t RTCEN: 2;
			volatile uint32_t BDRST: 2;
			volatile uint32_t reserved_3: 15;
		} BIT;
	} BDCR;
	/**
	 * @brief Control/Status Register
	 * @details
	 * Controls the LSI oscillator and provides reset status flags.
	 * Indicates the source of the last reset (power-on, pin, watchdog, etc.)
	 * and allows clearing of reset flags. LSI is used for independent watchdog.
	 */
	union RCC_CSR 
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t LSION: 1;
			volatile uint32_t LSIRDY: 1;
			volatile uint32_t reserved_1: 22;
			volatile uint32_t RMVF: 1;
			volatile uint32_t reserved_2: 1;
			volatile uint32_t PINRSTF: 1;
			volatile uint32_t PORRSTF: 1;
			volatile uint32_t SFTRSTF: 1;
			volatile uint32_t IWDGRSTF: 1;
			volatile uint32_t WWDGRSTF: 1;
			volatile uint32_t LPWRRSTF: 1;
		} BIT;
	} CSR;
} RCC_TypeDef;

/** @} */ // RCC_01_Registers_01_Structure

// C++ Safeguards
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_RCC_H_ */