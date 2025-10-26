/**
 * @file    stm32f1xx.h
 * @author  Shrey Shah
 * @version v1.2
 * @date    21-10-2025
 *
 * 
 * @defgroup STM32F1xx STM32F1 Memory Address Mapping
 * 
 * @brief   STM32F1xx - Peripheral Register Mapping
 *
 * @details 
 * This file provides centralized memory mapping for all peripherals for STM32F1xx Seriess
 *
 * @code
 * 
 * // STM32F1xx Series Peripheral Address Mapping
 * #include "stm32f1xx.h"
 *
 * // Set PA13
 * GPIOA->ODR.REG |= GPIO_PIN_13;
 * // Reset GPIOA clock
 * RCC->APB2ENR.REG &= ~RCC_APB2ENR_IOPAEN;
 * // Send character via USART1
 * USART1->DR = 'A';
 * 
 * @endcode
 *  
 */

/**
 * @brief Basic Utilities for Helper
 * @defgroup 01_STM32F1xx_Utilities Utilities
 * @ingroup STM32F1xx
 * 
 * @{
 * 
 * @details
 *******************************************************************************************************************
 *	Basic Notes:-
 *	YouTube Reference Video: https://youtu.be/zvTd3Zxtiek
 *	`uint32_t` inside every BIT struct because of padding alignment
 *	`volatile` used for ensuring no further optimization by compiler
 *	`: x` indicates only x bit(s) to be used from that 32-bit
 ****************************************************************************************************************
 *                          🔧 Bit Manipulation Built-ins (GCC)
 * -------------------------------------------------------------------------------------
 * | Built-in Function        | Description                                           |
 * |--------------------------|--------------------------------------------------------|
 * | __builtin_clz(x)         | Counts leading zeros from MSB (Undefined if x == 0)   |
 * | __builtin_ctz(x)         | Counts trailing zeros from LSB (Undefined if x == 0)  |
 * | __builtin_popcount(x)    | Counts number of bits set to 1 (Hamming weight)       |
 * | __builtin_parity(x)      | Returns 1 if number of 1-bits is odd, else 0          |
 * | __builtin_ffsl(x)        | Index (1-based) of first bit set (LSB side)           |
 * | __builtin_bswap16(x)     | Swaps byte order (Endian swap) for 16-bit integer     |
 * | __builtin_bswap32(x)     | Swaps byte order for 32-bit integer                   |
 * | __builtin_bswap64(x)     | Swaps byte order for 64-bit integer                   |
 * -------------------------------------------------------------------------------------
 * 
 * @note
 * - All __builtin_* functions are evaluated at compile-time if argument is constant.
 * - __builtin_clz/ctz are undefined if input is zero; guard input accordingly.
 * - These generate single assembly instructions (CLZ, RBIT, etc.) on ARM Cortex-M.
 * - Use with uint32_t or cast explicitly to avoid type promotion issues.
 *
 * @example
 * Example Usage:
 *   uint32_t val = 0x0000000F;
 *   uint8_t zeros = __builtin_clz(val);      // → 28
 *   uint8_t set   = __builtin_popcount(val); // → 4
 *   uint8_t rev   = __builtin_bswap32(val);  // → 0xF0000000
 * 
 * @}
 */
 
// Header Guards
#ifndef STM32F1XX_H_
#define STM32F1XX_H_

// C++ Safeguard
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// STM32F103C8T6
#ifdef STM32F103C8T6__

/*----------------------------------------------- ARM Cortex-M3 -----------------------------------------------*/
#include "cmsis_gcc.h"
#include "stm32f1xx_defines.h"
#include "stm32f1xx_flash.h"
#include "stm32f1xx_scb.h"
#include "stm32f1xx_nvic.h"
#include "stm32f1xx_systick.h"
#include "stm32f1xx_watchdog.h"
/*----------------------------------------------- ARM Cortex-M3 -----------------------------------------------*/

/*----------------------------------------------- STM32F103C8T6 -----------------------------------------------*/
#include "stm32f1xx_adc.h"
#include "stm32f1xx_advtim.h"
#include "stm32f1xx_afio.h"
#include "stm32f1xx_dma.h"
#include "stm32f1xx_exti.h"
#include "stm32f1xx_gpio.h"
#include "stm32f1xx_i2c.h"
#include "stm32f1xx_timer.h"
#include "stm32f1xx_rcc.h"
#include "stm32f1xx_usart.h"
/*----------------------------------------------- STM32F103C8T6 -----------------------------------------------*/

/*----------------------------------------------- Custom Declaration -----------------------------------------------*/
#define BIT_MASK(X)								((uint32_t) (0x01 << (X)))
#define CONSECUTIVE_BIT1_MASK()					((uint32_t) (0x01))
#define CONSECUTIVE_BIT2_MASK()					((uint32_t) (0x03))
#define CONSECUTIVE_BIT3_MASK()					((uint32_t) (0x07))
#define CONSECUTIVE_BIT4_MASK()					((uint32_t) (0x0F))
#define CONSECUTIVE_BIT5_MASK()					((uint32_t) (0x1F))
#define CONSECUTIVE_BIT6_MASK()					((uint32_t) (0x3F))
#define CONSECUTIVE_BIT7_MASK()					((uint32_t) (0x7F))
#define CONSECUTIVE_BIT8_MASK()					((uint32_t) (0xFF))

/**
 * @addtogroup 01_STM32F1xx_Utilities
 * 
 * @{
 */

/** 
 * @brief Sets bit at `POS`
 * @param[in] POS Bit position
 * @note Assumed 32-bits
 */
#define BIT_SET(POS)							((uint32_t) (0x01UL << (POS)))

/**
 * @brief   Compute peripheral index based on base addresses
 * @addtogroup 01_STM32F1xx_Utilities
 *
 * @details
 * This macro computes the relative index (or bit position) of a peripheral 
 * instance based on its memory-mapped base address, reference base address, 
 * and register block type.
 *
 * It is primarily used to determine clock-enable bit positions or array indices
 * for peripherals of the same type (e.g., GPIOA–GPIOG, USART1–USART3).
 *
 * @note
 * - The computation uses pointer arithmetic on `uintptr_t` to ensure 
 *   portability across 32-bit and 64-bit targets
 * - The result assumes all peripheral instances of the given `type` 
 *   are equally spaced in memory
 * - No hardware access is performed by this macro; it performs 
 *   pure compile-time address arithmetic when operands are constants
 *
 * @param[in] value   The address (or pointer) of the target peripheral instance  
 *                    (e.g., `GPIOC`, `USART2`, `TIM4`).
 * @param[in] base    The address (or pointer) of the first peripheral instance  
 *                    of the same type (e.g., `GPIOA`, `USART1`, `TIM2`).
 * @param[in] type    The peripheral structure type (e.g., `GPIO_TypeDef`, 
 *                    `USART_TypeDef`).
 *
 * @return The peripheral index (zero-based)
 *
 * @pre The base and value must both point to valid peripherals of the same type.
 *
 * @warning The result is undefined if `base` and `value` do not belong to 
 *          peripherals of the same structure layout or are not memory-aligned
 *          as expected.
 *
 * @see @ref RCC_APB2ENR for example bit positioning of GPIO ports.
 * @see @ref GPIO_TypeDef for structure size reference.
 *
 * @par Example:
 * @code
 * // Example: Compute GPIO port index
 * uint32_t index = BIT_POS(GPIOC, GPIOA, GPIO_TypeDef);
 * // index = 2 → GPIOC is the third port after GPIOA
 *
 * // Enable corresponding GPIO clock (bit = index + 2)
 * RCC->APB2ENR |= (1U << (index + 2));
 * @endcode
 */
#define BIT_POS(value, base, type) \
	((unsigned long)((((uintptr_t)(value)) - ((uintptr_t)(base))) / ((uintptr_t)(sizeof((type))))))

/**
 * @brief Driver Status
 */
typedef enum
{
	DRIVER_SUCCESS = (uint8_t) 0x00,
	DRIVER_FAIL = (uint8_t) 0x01
} driver_status_t;

/**
 * @brief Assert Driver Functionality Status
 */
#define ASSERT_DRIVER_STATUS(status)    \
	do                                  \
	{                                   \
		if ((status) != DRIVER_SUCCESS) \
		{                               \
			return (status);            \
		}                               \
	} while (0)

/** @} */ // 01_STM32F1xx_Utilities
/*----------------------------------------------- Custom Declaration -----------------------------------------------*/

/*----------------------------------------------- Memory Bus Base Addresses -----------------------------------------------*/

/**
 * @defgroup 02_STM32F1xx_BaseAddress Memory Base Addresses
 * @ingroup  STM32F1xx
 * @brief    Base addresses for different memory buses in STM32F1xx
 *
 * @details 
 * STM32F1xx Base Memory Addresses Offsets
 * @see Reference Manual RM0008 - Section 3.2 Memory Map
 * 
 * @{
 */

/** @brief System Timer Base (Cortex-M3 Core Peripheral) */
#define SysTick_BASE_ADDR                       0xE000E010UL
/** @brief Nested Vectored Interrupt Controller Base */
#define NVIC_BASE_ADDR                          0xE000E100UL
/** @brief System Control Block Base */
#define SCB_BASE_ADDR                           0xE000ED00UL
/** @brief Core Debug Registers Base */
#define CoreDebug_BASE_ADDR                     0xE000EDF0UL
/** @brief APB1 Peripheral Base (Low-speed peripherals) @def APB1_BASE_ADDR */
#define APB1_BASE_ADDR                          0x40000000UL
/** @brief APB2 Peripheral Base (High-speed peripherals) @def APB2_BASE_ADDR */
#define APB2_BASE_ADDR                          0x40010000UL
/** @brief AHB Peripheral Base (Memory, DMA, CRC) @def AHB_BASE_ADDR */
#define AHB_BASE_ADDR                           0x40018000UL
/** @brief Flash Memory Interface Base */
#define FLASH_BASE_ADDR                         0x40022000UL
/** @brief DMA1 Controller Base */
#define DMA1_BASE_ADDR                          (AHB_BASE_ADDR + 0x00008000UL)
/** @brief DMA2 Controller Base */
#define DMA2_BASE_ADDR                          (DMA1_BASE_ADDR + 0x00000400UL)
/** @brief Window Watchdog Base */
#define WWDG_BASE_ADDR                          (APB1_BASE_ADDR + 0x00002000UL)
/** @brief Independent Watchdog Base */
#define IWDG_BASE_ADDR                          (APB1_BASE_ADDR + 0x00003000UL)

/** @} */  // 02_STM32F1xx_BaseAddress


#define SCB										((SCB_TypeDef *) (SCB_BASE_ADDR))
#define NVIC 									((NVIC_TypeDef *) (NVIC_BASE_ADDR))
#define SysTick 								((SysTick_TypeDef *) (SysTick_BASE_ADDR))
#define FLASH 									((FLASH_TypeDef *) (FLASH_BASE_ADDR))
#define RCC 									((RCC_TypeDef *) (AHB_BASE_ADDR + 0x00009000UL))

/*----------------------------------------------- GPIO Peripheral -----------------------------------------------*/

/**
 * @addtogroup  GPIO_01_Registers
 * @brief       STM32F1xx GPIO Memory Address Mapping
 * @details 
 * - GPIO peripheral instances based on @ref 01_GPIO_01_Registers_Structure "GPIO Registers"
 * - All GPIO ports are clocked from @ref APB2_BASE_ADDR "APB2 Bus"
 * - Each GPIO port occupies 0x400 bytes of address space
 * - Supports GPIO Port A through G on STM32F103C8T6
 * @see Reference Manual RM0008 - Section 9.2 GPIO Registers
 * @see Datasheet - Section 4 Memory Mapping
 * @{
 */

/**
 * @defgroup  GPIO_01_Registers_02_Offset GPIO Register Offset
 * @brief GPIO Register Offset from Base Memory Address
 * @ingroup GPIO_01_Registers
 * @{
 */
/** @brief GPIO Port A Offset @def GPIOA_OFFSET */
#define GPIOA_OFFSET                            0x00000800UL
/** @brief GPIO Port B Offset @def GPIOB_OFFSET */
#define GPIOB_OFFSET                            0x00000C00UL
/** @brief GPIO Port C Offset @def GPIOC_OFFSET */
#define GPIOC_OFFSET                            0x00001000UL
/** @brief GPIO Port D Offset @def GPIOD_OFFSET */
#define GPIOD_OFFSET                            0x00001400UL
/** @brief GPIO Port E Offset @def GPIOE_OFFSET */
#define GPIOE_OFFSET                            0x00001800UL
/** @brief GPIO Port F Offset @def GPIOF_OFFSET */
#define GPIOF_OFFSET                            0x00001C00UL
/** @brief GPIO Port G Offset @def GPIOG_OFFSET */
#define GPIOG_OFFSET                            0x00002000UL

/** @} */ // GPIO_01_Registers_02_Offset

/**
 * @defgroup  GPIO_03_Registers_03_Memory GPIO Register Memory Addess
 * @ingroup GPIO_01_Registers
 * @{
 */
/** @brief GPIO Port A memory-mapped register structure @def GPIOA */
#define GPIOA									((GPIO_TypeDef *) (APB2_BASE_ADDR + GPIOA_OFFSET))
/** @brief GPIO Port B memory-mapped register structure @def GPIOB */
#define GPIOB									((GPIO_TypeDef *) (APB2_BASE_ADDR + GPIOB_OFFSET))
/** @brief GPIO Port C memory-mapped register structure @def GPIOC */
#define GPIOC									((GPIO_TypeDef *) (APB2_BASE_ADDR + GPIOC_OFFSET))
/** @brief GPIO Port D memory-mapped register structure @def GPIOD */
#define GPIOD									((GPIO_TypeDef *) (APB2_BASE_ADDR + GPIOD_OFFSET))
/** @brief GPIO Port E memory-mapped register structure @def GPIOE */
#define GPIOE									((GPIO_TypeDef *) (APB2_BASE_ADDR + GPIOE_OFFSET))
/** @brief GPIO Port F memory-mapped register structure @def GPIOF */
#define GPIOF									((GPIO_TypeDef *) (APB2_BASE_ADDR + GPIOF_OFFSET))
/** @brief GPIO Port G memory-mapped register structure @def GPIOG */
#define GPIOG									((GPIO_TypeDef *) (APB2_BASE_ADDR + GPIOG_OFFSET))

/** @} */ // GPIO_03_Registers_03_Memory

/** @} */ // GPIO_01_Registers

#define AFIO 									((AFIO_TypeDef *) (APB2_BASE_ADDR))
#define TIM1 									((Adv_TIM_TypeDef *) (APB2_BASE_ADDR + 0x00002C00UL))
#define TIM2 									((TIM_TypeDef *) (APB1_BASE_ADDR + 0x00000000UL))
#define TIM3 									((TIM_TypeDef *) (APB1_BASE_ADDR + 0x00000400UL))
#define TIM4 									((TIM_TypeDef *) (APB1_BASE_ADDR + 0x00000800UL))
#define TIM5 									((TIM_TypeDef *) (APB1_BASE_ADDR + 0x00000C00UL))
#define TIM6 									((TIM_TypeDef *) (APB1_BASE_ADDR + 0x00001000UL))
#define TIM7 									((TIM_TypeDef *) (APB1_BASE_ADDR + 0x00001400UL))
#define TIM8 									((Adv_TIM_TypeDef *) (APB2_BASE_ADDR + 0x00003400UL))
#define ADC1 									((ADC_TypeDef *) (APB2_BASE_ADDR + 0x00002400UL))
#define ADC2 									((ADC_TypeDef *) (APB2_BASE_ADDR + 0x00002800UL))
#define ADC3 									((ADC_TypeDef *) (APB2_BASE_ADDR + 0x00003C00UL))
#define USART1 									((USART_TypeDef *) (APB2_BASE_ADDR + 0x00003800UL))
#define USART2 									((USART_TypeDef *) (APB1_BASE_ADDR + 0x00004400UL))
#define USART3 									((USART_TypeDef *) (APB1_BASE_ADDR + 0x00004800UL))
#define EXTI 									((EXTI_REG_STRUCT *) (APB2_BASE_ADDR + 0x00000400UL))
#define I2C1 									((I2C_TypeDef *) (APB1_BASE_ADDR + 0x00005400UL))
#define I2C2 									((I2C_TypeDef *) (APB1_BASE_ADDR + 0x00005800UL))
#define IWDG									((IWDG_TypeDef *) IWDG_BASE_ADDR)
#define WWDG									((WWDG_TypeDef *) WWDG_BASE_ADDR)
#define DMA1 									((DMA_TypeDef *) DMA1_BASE_ADDR)
#define DMA1_Channel1 							((DMA_Channel_TypeDef *) (&DMA1->CHANNEL[0]))
#define DMA1_Channel2 							((DMA_Channel_TypeDef *) (&DMA1->CHANNEL[1]))
#define DMA1_Channel3 							((DMA_Channel_TypeDef *) (&DMA1->CHANNEL[2]))
#define DMA1_Channel4 							((DMA_Channel_TypeDef *) (&DMA1->CHANNEL[3]))
#define DMA1_Channel5 							((DMA_Channel_TypeDef *) (&DMA1->CHANNEL[4]))
#define DMA1_Channel6 							((DMA_Channel_TypeDef *) (&DMA1->CHANNEL[5]))
#define DMA1_Channel7 							((DMA_Channel_TypeDef *) (&DMA1->CHANNEL[6]))
#define DMA2 									((DMA_TypeDef *) DMA2_BASE_ADDR)
#define DMA2_Channel1 							((DMA_Channel_TypeDef *)(&DMA2->CHANNEL[0]))
#define DMA2_Channel2 							((DMA_Channel_TypeDef *)(&DMA2->CHANNEL[1]))
#define DMA2_Channel3 							((DMA_Channel_TypeDef *)(&DMA2->CHANNEL[2]))
#define DMA2_Channel4 							((DMA_Channel_TypeDef *)(&DMA2->CHANNEL[3]))
#define DMA2_Channel5 							((DMA_Channel_TypeDef *)(&DMA2->CHANNEL[4]))

/*----------------------------------------------- Address Mapping -----------------------------------------------*/



/*----------------------------------------------- I2C MACROS -----------------------------------------------*/
// I2C Speed
#define I2Cx_SPEED_STD (FREQ_100kHz)
#define I2Cx_SPEED_FAST (FREQ_100kHz << 2)
// I2C SCL Clock Frequency
#define I2Cx_SCL_FREQ_4MHz						(0x04)
#define I2Cx_SCL_FREQ_8MHz						(0x08)
#define I2Cx_SCL_FREQ_16MHz						(0x10)
#define I2Cx_SCL_FREQ_32MHz						(0x20)
#define I2Cx_SCL_FREQ_DEFAULT 					RCC_APB1ClockFreq_Get()
// I2C Mode
#define I2Cx_MODE_STD 							(0x00)
#define I2Cx_MODE_FAST 							(0x01)
// I2C Interrupt Mapping
#define I2Cx_IRQ_EVENT 							(0x01)
#define I2Cx_IRQ_BUFFER 						(0x02)
#define I2Cx_IRQ_ERROR 							(0x04)
#define I2Cx_IRQ_ALL 							(I2Cx_IRQ_EVENT | I2Cx_IRQ_BUFFER | I2Cx_IRQ_ERROR)
// I2C Fast Mode Duty
#define I2Cx_DUTY_NORMAL						(0x00)
#define I2Cx_DUTY_FAST							(0x01)
// I2C Slave R/W Definitions
#define I2Cx_WRITE								(0x00)
#define I2Cx_READ								(0x01)
// I2C Peripheral Definitions
#define I2C1_SCL_GPIO 							(GPIOB)
#define I2C1_SCL_PIN 							(GPIOx_PIN_6)
#define I2C1_SDA_GPIO 							(GPIOB)
#define I2C1_SDA_PIN 							(GPIOx_PIN_7)
#define I2C2_SCL_GPIO 							(GPIOB)
#define I2C2_SCL_PIN 							(GPIOx_PIN_10)
#define I2C2_SDA_GPIO 							(GPIOB)
#define I2C2_SDA_PIN 							(GPIOx_PIN_11)
/*----------------------------------------------- I2C MACROS -----------------------------------------------*/

/*----------------------------------------------- SysTick MACROS -----------------------------------------------*/
// SysTick Clock Selection
#define SYSTICK_CLK_EXT (0x00)
#define SYSTICK_CLK_CORE (0x01)

// SysTick Delay
#define SYSTICK_DELAY_1_US (RCC_Get_AHBClock())
#define SYSTICK_DELAY_2_US (SYSTICK_DELAY_1_US << 1)
#define SYSTICK_DELAY_1_MS (SYSTICK_DELAY_1_US / FREQ_1kHz)
#define SYSTICK_DELAYS_2_MS (SYSTICK_DELAY_1_MS << 1)
/*----------------------------------------------- SysTick MACROS -----------------------------------------------*/

/*----------------------------------------------- Timer MACROS -----------------------------------------------*/
// - Prescaler
// |-> Timer Frequency: 10kHz
// |-> (PSC + 1) = (7199 + 1) = (7200)
#define TIMx_DEFAULT_10kHz_PSC ((uint16_t)7199)
// - Max Count Value
// |-> Timer Frequency: 10kHz
// |-> (ARR + 1) = (9999 + 1) = (10000)
#define TIMx_DEFAULT_10kHz_ARR ((uint16_t)9999)
// - Prescaler
// |-> Timer Frequency: 1MHz
// |-> (PSC + 1) = (71 + 1) = (72)
#define TIMx_DEFAULT_1MHz_PSC ((uint16_t)71)
// - Max Count Value
// |-> Timer Frequency: 10kHz
// |-> (ARR + 1) = (999 + 1) = (1000)
#define TIMx_DEFAULT_1MHz_ARR ((uint16_t)999)
// Timer Start Value
#define TIMx_DEFAULT_CNT ((uint16_t)0)

// Clock Division
#define TIMx_CKD_CLK_FREQ (0x00)
#define TIMx_CKD_CLK_2_FREQ (0x01)
#define TIMx_CKD_CLK_4_FREQ (0x02)

// Master Mode Selection
#define TIMx_MMS_RESET (0x00)
#define TIMx_MMS_ENABLE (0x01)
#define TIMx_MMS_UPDATE (0x02)
#define TIMx_MMS_CMP_PULSE (0x03)
#define TIMx_MMS_CMP_OC1REF (0x04)
#define TIMx_MMS_CMP_OC2REF (0x05)
#define TIMx_MMS_CMP_OC3REF (0x06)
#define TIMx_MMS_CMP_OC4REF (0x07)

// Slave Mode Selection
#define TIMx_SMS_DISABLE (0x00)
#define TIMx_SMS_ENC_MODE1 (0x01)
#define TIMx_SMS_ENC_MODE2 (0x02)
#define TIMx_SMS_ENC_MODE3 (0x03)

// TIM1 REMAP
#define TIM1_NO_REMAP (0x00)	   // (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PB12, CH1N/PB13, CH2N/PB14, CH3N/PB15)
#define TIM1_PARTIAL_REMAP (0x01)  // (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PA6, CH1N/PA7, CH2N/PB0, CH3N/PB1)
#define TIM1_NOT_USED_REMAP (0x02) // Not Used
#define TIM1_FULL_REMAP (0x03)	   // (ETR/PE7, CH1/PE9, CH2/PE11, CH3/PE13, CH4/PE14, BKIN/PE15, CH1N/PE8, CH2N/PE10, CH3N/PE12)

// TIM2 REMAP
#define TIM2_NO_REMAP (0x00)	   // (CH1/ETR/PA0, CH2/PA1, CH3/PA2, CH4/PA3)
#define TIM2_PARTIAL1_REMAP (0x01) // (CH1/ETR/PA15, CH2/PB3, CH3/PA2, CH4/PA3)
#define TIM2_PARTIAL2_REMAP (0x02) // (CH1/ETR/PA0, CH2/PA1, CH3/PB10, CH4/PB11)
#define TIM2_FULL_REMAP (0x03)	   // (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11)

// TIM3 REMAP
#define TIM3_NO_REMAP (0x00)	   // (CH1/PA6, CH2/PA7, CH3/PB0, CH4/PB1)
#define TIM3_NOT_USED_REMAP (0x01) // Not Used
#define TIM3_PARTIAL_REMAP (0x02)  // (CH1/PB4, CH2/PB5, CH3/PB0, CH4/PB1)
#define TIM3_FULL_REMAP (0x03)	   // (CH1/PC6, CH2/PC7, CH3/PC8, CH4/PC9)

// TIM4 REMAP
#define TIM4_NO_REMAP (0x00)   // (TIM4_CH1/PB6, TIM4_CH2/PB7, TIM4_CH3/PB8, TIM4_CH4/PB9)
#define TIM4_FULL_REMAP (0x01) // (TIM4_CH1/PD12, TIM4_CH2/PD13, TIM4_CH3/PD14, TIM4_CH4/PD15)

/**
 * @enum tim_channel_t
 * @brief Timer Channel Enumeration
 * @note  This enumeration defines the available timer channels
 */
typedef enum
{
	// Timer Channel None
	TIMx_CHANNEL_NONE = 0x00,
	// Timer Channel 1
	TIMx_CHANNEL_1 = 0x01,
	// Timer Channel 2
	TIMx_CHANNEL_2 = 0x02,
	// Timer Channel 3
	TIMx_CHANNEL_3 = 0x04,
	// Timer Channel 4
	TIMx_CHANNEL_4 = 0x08,
	// All Timer Channels
	TIMx_CHANNEL_ALL = 0x0F
} tim_channel_t;

/**
 * @brief Timer Counting Mode Enumeration
 * @note  This enumeration defines the available timer modes
 */
typedef enum
{
	/**
		@brief Normal Mode
		@note The counter counts up or down depending on direction
	 */
	TIMx_MODE_NORMAL = 0x00,
	/**
		@brief Alternate Mode Counting
		@note  The counter counts up and down alternatively but
				interrupt flags are set only during counting down
	 */
	TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING = 0x01,
	/**
		@brief Alternate Mode Counting
		@note  The counter counts up and down alternatively but
				interrupt flags are set only during counting up
	 */
	TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING = 0x02,
	/**
		@brief Alternate Mode Counting
		@note  The counter counts up and down alternatively but
				interrupt flags are set during both counting up and down
	 */
	TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING = 0x03
} tim_count_mode_t;

/**
 * @brief Timer Direction Enumeration
 * @note  This enumeration defines the counting direction of the timer
 */
typedef enum
{
	/**
		@brief Count Up
		@note  The timer counts up
	 */
	TIMx_DIR_COUNT_UP = 0x00,
	/**
		@brief Count Down
		@note  The timer counts down
	 */
	TIMx_DIR_COUNT_DOWN = 0x01
} tim_direction_t;

/**
 * @brief Auto-Reload Preload Enable
 * @note  This enumeration defines the Auto-Reload Preload Enable state of the timer
 */
typedef enum
{
	/**
		@brief Auto-Reload Preload Disable
		@note  The timer's auto-reload preload is disabled
	 */
	TIMx_ARPE_DISABLE = 0x00,
	/**
		@brief Auto-Reload Preload Enable
		@note  The timer's auto-reload preload is enabled
	 */
	TIMx_ARPE_ENABLE = 0x01
} tim_arpe_t;

/**
 * @brief One Pulse Mode
 * @note  This enumeration defines the One Pulse Mode state of the timer
 */
typedef enum
{
	/**
		@brief One Pulse Mode Disable
		@note  The timer's one pulse mode is disabled
	 */
	TIMx_OPM_DISABLE = 0x00,
	/**
		@brief One Pulse Mode Enable
		@note  The timer's one pulse mode is enabled
	 */
	TIMx_OPM_ENABLE = 0x01
} tim_opm_t;

/**
 * @brief Trigger Source Enumeration
 * @note  This enumeration defines the available trigger sources for the timer
 */
typedef enum
{
	/**
		@brief Trigger Source - All
		@note  Only following sources for Updated Event (UEV) enabled:
				@note 1. Counter overflow (OVF)
				@note 2. Counter underflow (UVF)
				@note 3. DMA request
				@note 4. Setting the `UG` bit (Refer `TIMx->EGR`)
				@note 5. Update generation through the slave mode controller
	 */
	TIMx_UPDATE_SOURCE_ANY = 0x00,
	/**
		@brief Trigger Source - UVF/OVF/DMA
		@note  Only following sources for Updated Event (UEV) enabled:
				@note 1. Counter overflow (OVF)
				@note 2. Counter underflow (UVF)
				@note 3. DMA request
	 */
	TIMx_UPDATE_SOURCE_OVF_DMA = 0x01
} tim_update_source_t;

// IRQ Enable
typedef enum
{
	TIMx_IRQ_DISABLE = 0x00,
	TIMx_IRQ_ENABLE = 0x01
} tim_irq_enable_t;

/**
 * @brief Timer Interrupt Request (IRQ) Enumeration
 * @note  This enumeration defines the available timer IRQ sources
 */
typedef enum
{
	/* Timer Interrupt for Overflow (OVF) /Underflow (UVF) Event */
	TIMx_IRQ_OVF_UVF = 0x01,
	/* Timer Interrupt for Output Compare (CMP) Event on Channel 1 */
	TIMx_IRQ_OUT_CMP_CH1 = 0x02,
	/* Timer Interrupt for Output Compare (CMP) Event on Channel 2 */
	TIMx_IRQ_OUT_CMP_CH2 = 0x04,
	/* Timer Interrupt for Output Compare (CMP) Event on Channel 3 */
	TIMx_IRQ_OUT_CMP_CH3 = 0x08,
	/* Timer Interrupt for Output Compare (CMP) Event on Channel 4 */
	TIMx_IRQ_OUT_CMP_CH4 = 0x10,
	/* Timer Interrupt for Input Capture (CAP) Event on Channel 1 */
	TIMx_IRQ_IN_CAP_CH1 = 0x02,
	/* Timer Interrupt for Input Capture (CAP) Event on Channel 2 */
	TIMx_IRQ_IN_CAP_CH2 = 0x04,
	/* Timer Interrupt for Input Capture (CAP) Event on Channel 3 */
	TIMx_IRQ_IN_CAP_CH3 = 0x08,
	/* Timer Interrupt for Input Capture (CAP) Event on Channel 4 */
	TIMx_IRQ_IN_CAP_CH4 = 0x10,
	/* Timer Interrupt for All Events */
	TIMx_IRQ_ALL = 0x1F
} tim_irq_t;

// Timer DMA Definitions
#define TIMx_DMA_UPDATE (0x01)
#define TIMx_DMA_CC1DE (0x02)
#define TIMx_DMA_CC2DE (0x04)
#define TIMx_DMA_CC3DE (0x08)
#define TIMx_DMA_CC4DE (0x10)

/*----------------------------------------------- Timer MACROS -----------------------------------------------*/

/*----------------------------------------------- PWM MACROS -----------------------------------------------*/
// PWM Min Duty Cycle: 1%
#define PWM_MIN_DUTY_CYCLE (1)
// PWM Max Duty Cycle: 100%
#define PWM_MAX_DUTY_CYCLE (999)

// Timer Remapping
#define TIM1_NO_REMAP (0x00)
#define TIM1_PARTIAL_REMAP (0x01)
#define TIM2_NO_REMAP (0x00)
#define TIM2_PARTIAL_REMAP_1 (0x01)
#define TIM2_PARTIAL_REMAP_2 (0x02)
#define TIM2_FULL_REMAP (0x03)
#define TIM3_NO_REMAP (0x00)
#define TIM3_PARTIAL_REMAP (0x02)
#define TIM4_NO_REMAP (0x00)

/**
 * @enum `tim_channel_mode_t`
 * @brief Channel Output Compare operating modes for TIMx channels
 * @note These modes define how the Output Compare (OC) signal behaves based on
 * @note the relationship between the counter (`TIMx_CNT`) and the capture/compare
 * @note register (`TIMx_CCRy`)
 */
typedef enum
{
	/**
	 * @brief Freeze Mode
	 * @details `TIMx_CNT == TIMx_CCRy` has no effect on the outputs
	 */
	TIMx_CHANNEL_MODE_FREEZE = 0x00,

	/**
	 * @brief Set Channel Mode
	 * @details `OCyREF` signal is forced high when `TIMx_CNT == TIMx_CCRy`
	 */
	TIMx_CHANNEL_MODE_SET_CH = 0x01,

	/**
	 * @brief Reset Channel Mode
	 * @details `OCyREF` signal is forced low when `TIMx_CNT == TIMx_CCRy`
	 */
	TIMx_CHANNEL_MODE_RESET_CH = 0x02,

	/**
	 * @brief Toggle Mode
	 * @details `OCyREF` toggles whenever `TIMx_CNT == TIMx_CCRy`
	 */
	TIMx_CHANNEL_MODE_TOGGLE = 0x03,

	/**
	 * @brief Force Reset Mode
	 * @details `OCyREF` is permanently forced low
	 */
	TIMx_CHANNEL_MODE_FORCE_RESET = 0x04,

	/**
	 * @brief Force Set Mode
	 * @details `OCyREF` is permanently forced high
	 */
	TIMx_CHANNEL_MODE_FORCE_SET = 0x05,

	/**
	 * @brief PWM Normal Mode
	 * @details Channel `CHy` is active as long as `TIMx_CNT < TIMx_CCRy`
	 */
	TIMx_CHANNEL_MODE_PWM1 = 0x06,

	/**
	 * @brief PWM Inverted Mode
	 * @details Channel `CHy` is active as long as `TIMx_CNT > TIMx_CCRy`
	 */
	TIMx_CHANNEL_MODE_PWM2 = 0x07
} tim_channel_mode_t;

/**
 * @brief Timer Channel Capture/Compare Selection
 * @note This enum defines the selection mode for the Timer Channel Capture/Compare (CC) feature
 */
typedef enum
{
	/**
		@brief Channel configured as Output
		@note This mode allows the channel to output a PWM signal based on the compare value
	 */
	TIMx_CHANNEL_CCS_OUTPUT = 0x00,
	/**
		@brief Channel configured as Input
		@note This mode allows ICx to be mapped on TIx
	 */
	TIMx_CHANNEL_CCS_INPUT_TIx = 0x01,
	/**
		@brief - Channel configured as Input
		@brief - If x is odd, This mode allows ICx to be mapped on TIx+1
		@brief - If x is even, This mode allows ICx to be mapped on TIx-1
		@note - For CC1S, IC1 is mapped on TI2
		@note - For CC2S, IC2 is mapped on TI1
		@note - For CC3S, IC3 is mapped on TI4
		@note - For CC4S, IC4 is mapped on TI3
	 */
	TIMx_CHANNEL_CCS_INPUT_TIx_1 = 0x02,
	/**
		@brief - Channel configured as Input
		@brief - This mode allows ICx to be mapped on TRC
		@note This mode is working only if an internal trigger input is selected through the TS bit (TIMx_SMCR register)
	 */
	TIMx_CHANNEL_CCS_INPUT_TRC = 0x03
} tim_channel_ccs_t;

/**
 * @enum `tim_channel_oc_preload_t`
 * @brief Timer Channel Output Compare Preload Configuration
 * @note This enum defines the preload configuration for the Output Compare (OC) feature
 */
typedef enum
{
	/**
	 * @brief Channel Output Compare Preload Disable
	 * @note The PWM channel does not use preload
	 */
	TIMx_CHANNEL_OC_PRELOAD_DISABLE = 0x00,
	/**
	 * @brief Channel Output Compare Preload Enable
	 * @note The PWM channel uses preload
	 */
	TIMx_CHANNEL_OC_PRELOAD_ENABLE = 0x01
} tim_channel_oc_preload_t;

/**
 * @enum `tim_channel_oc_fast_t`
 * @brief Timer Channel Output Compare Fast Configuration.
 * @brief Used to accelerate the effect of an event on the trigger in input on the CC output
 * @note This enum defines the fast configuration for the Output Compare (OC) feature
 */
typedef enum
{
	/**
	 * @brief - Channel Output Compare Fast Disable
	 * @brief - CCx behaves normally depending on counter and CCRx values even when the trigger is ON
	 * @note The minimum delay to activate CC1 output when an edge occurs on the trigger input is 5 clock cycles
	 */
	TIMx_CHANNEL_OC_FAST_DISABLE = 0x00,
	/**
	 * @brief - Channel Output Compare Fast Enable
	 * @brief - An active edge on the trigger input acts like a compare match on CCx output
	 * @brief - OC is set to the compare level independently from the result of the comparison
	 * @brief - Delay to sample the trigger input and to activate CC1 output is reduced to 3 clock cycles
	 * @note Acts only if the channel is configured in PWM1 or PWM2 mode
	 */
	TIMx_CHANNEL_OC_FAST_ENABLE = 0x01
} tim_channel_oc_fast_t;

/**
 * @enum `tim_channel_oc_clear_t`
 * @brief Timer Channel Output Compare Clear Configuration.
 * @brief Used to clear the effect of an event on the trigger in input on the CC output
 * @note This enum defines the clear configuration for the Output Compare (OC) feature
 */
typedef enum
{
	/**
	 * @brief - Channel Output Compare Clear Disable
	 * @brief - OCxRef is not affected by the ETRF input
	 */
	TIMx_CHANNEL_OC_CLEAR_DISABLE = 0x00,
	/**
	 * @brief - Channel Output Compare Clear Enable
	 * @brief - OCxRef is cleared as soon as a High level is detected on ETRF input
	 */
	TIMx_CHANNEL_OC_CLEAR_ENABLE = 0x01
} tim_channel_oc_clear_t;

/**
 * @enum `tim_channel_polarity_t`
 * @brief Channel Polarity Configuration
 * @note This enum defines the polarity of the PWM signal for each channel
 */
typedef enum
{
	/**
	 * @brief Channel Active High
	 * @note The PWM signal is active high
	 */
	TIMx_CHANNEL_POLARITY_HIGH = 0x00,
	/**
	 * @brief Channel Active Low
	 * @note The PWM signal is active low
	 */
	TIMx_CHANNEL_POLARITY_LOW = 0x01
} tim_channel_polarity_t;

// Max Counter Value for PWM
#define PWM_DEFAULT_ARR ((uint16_t)999)

/*----------------------------------------------- PWM MACROS -----------------------------------------------*/

/*----------------------------------------------- ADC MACROS -----------------------------------------------*/
// ADC Max Value
#define MAX_ADC_VALUE ((uint16_t)0x0FFF)

// ADC Channel
#define ADC_CHANNEL_0 (0)
#define ADC_CHANNEL_1 (1)
#define ADC_CHANNEL_2 (2)
#define ADC_CHANNEL_3 (3)
#define ADC_CHANNEL_4 (4)
#define ADC_CHANNEL_5 (5)
#define ADC_CHANNEL_6 (6)
#define ADC_CHANNEL_7 (7)
#define ADC_CHANNEL_8 (8)
#define ADC_CHANNEL_9 (9)

// ADC Sample Time
#define ADC_SAMPLE_1_5 (0)
#define ADC_SAMPLE_7_5 (1)
#define ADC_SAMPLE_13_5 (2)
#define ADC_SAMPLE_28_5 (3)
#define ADC_SAMPLE_41_5 (4)
#define ADC_SAMPLE_55_5 (5)
#define ADC_SAMPLE_71_5 (6)
#define ADC_SAMPLE_239_5 (7)

// ADC Continuous Conversion
#define ADC_CONT_CONV_OFF (0)
#define ADC_CONT_CONV_ON (1)

// ADC Data Alignment
#define ADC_DATA_ALIGN_RIGHT (0)
#define ADC_DATA_ALIGN_LEFT (1)

// ADC IRQ
#define ADCx_IRQ_DISABLE (0)
#define ADCx_IRQ_ENABLE (1)

// ADC Sample Time Channel Decoding
#define ADC_SAMPLE_CHANNEL(ADC_SAMPLEx) ((uint8_t)(((ADC_SAMPLEx) & 0xF0) >> 4))
// ADC Sample Time Decoding
#define ADC_SAMPLE_TIME(ADC_SAMPLEx) ((uint8_t)((ADC_SAMPLEx) & 0x0F))

/*----------------------------------------------- ADC MACROS -----------------------------------------------*/

/*----------------------------------------------- USART MACROS -----------------------------------------------*/
// TX
#define USARTx_TX_DISABLE (0x00)
#define USARTx_TX_ENABLE (0x01)

// RX
#define USARTx_RX_DISABLE (0x00)
#define USARTx_RX_ENABLE (0x01)

// TX Empty IRQ
#define USARTx_TXEIE_DISABLE (0x00)
#define USARTx_TXEIE_ENABLE (0x01)

// RX Not Empty IRQ
#define USARTx_RXNEIE_DISABLE (0x00)
#define USARTx_RXNEIE_ENABLE (0x01)

// TX Complete IRQ
#define USARTx_TCIE_DISABLE (0x00)
#define USARTx_TCIE_ENABLE (0x01)

// Parity Control
#define USARTx_PARITY_DISABLE (0x00)
#define USARTx_PARITY_ENABLE (0x01)

// Word Length
#define USARTx_WORD_8_BITS (0x00)
#define USARTx_WORD_9_BITS (0x01)

// Stop Bits
#define USARTx_STOP_1_BIT (0x00)
#define USARTx_STOP_0_5_BITS (0x01)
#define USARTx_STOP_2_BITS (0x02)
#define USARTx_STOP_1_5_BITS (0x03)

// Parity Mode
#define USARTx_PARITY_EVEN (0x00)
#define USARTx_PARITY_ODD (0x01)

// Baud Rate
#define USARTx_BAUD_4800 ((uint16_t)4800)
#define USARTx_BAUD_9600 ((uint16_t)9600)
#define USARTx_BAUD_115200 ((uint16_t)115200)

// Local Delay
#define USARTx_STRING_TX_DELAY ((uint16_t)3000)
/*----------------------------------------------- USART MACROS -----------------------------------------------*/

/*----------------------------------------------- DMA MACROS -----------------------------------------------*/
// DMA Direction
#define DMAx_DIR_READ_PER (0x00)
#define DMAx_DIR_READ_MEM (0x01)

// Memory to Memory Transfer
#define DMAx_MEM2MEM_DISABLE (0x00)
#define DMAx_MEM2MEM_ENABLE (0x01)

// Circular Mode
#define DMAx_CIRC_DISABLE (0x00)
#define DMAx_CIRC_ENABLE (0x01)

// Priority Level
#define DMAx_PRIORITY_LOW (0x00)
#define DMAx_PRIORITY_MEDIUM (0x01)
#define DMAx_PRIORITY_HIGH (0x02)
#define DMAx_PRIORITY_VERY_HIGH (0x03)

// Address Increment
#define DMAx_INC_DISABLE (0x00)
#define DMAx_INC_ENABLE (0x01)

// DMA Data Size for Transfer
#define DMAx_DATA_SIZE_BIT_8 (0x00)
#define DMAx_DATA_SIZE_BIT_16 (0x01)
#define DMAx_DATA_SIZE_BIT_32 (0x02)

// Interrupts
#define DMAx_IRQ_DISABLE (0x00)
#define DMAx_IRQ_ENABLE (0x01)

// DMA Channel 6
#define DMA_USART2_RX (DMA1_Channel6)
#define DMA_I2C1_TX (DMA1_Channel6)
#define DMA_TIM1_CH3 (DMA1_Channel6)
#define DMA_TIM3_CH1 (DMA1_Channel6)
#define DMA_TIM3_TRIG (DMA1_Channel6)

// DMA Channel 7
#define DMA_USART2_TX (DMA1_Channel7)
#define DMA_I2C1_RX (DMA1_Channel7)
#define DMA_TIM2_CH2 (DMA1_Channel7)
#define DMA_TIM2_CH4 (DMA1_Channel7)
#define DMA_TIM4_UP (DMA1_Channel7)

/*----------------------------------------------- DMA MACROS -----------------------------------------------*/



/*----------------------------------------------- Helper Functions -----------------------------------------------*/

#endif /* STM32F103C8T6__ */

// C++ Safeguard
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_H_ */