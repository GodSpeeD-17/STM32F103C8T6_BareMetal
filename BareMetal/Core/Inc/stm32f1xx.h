/**
 * @file	stm32f1xx.h
 * @author  Shrey Shah
 * @version v1.2
 * @date	21-10-2025
 *
 * 
 * @defgroup STM32F1xx STM32F1 Memory Address Mapping
 * 
 * @brief   STM32F1xx - Peripheral Register Mapping
 *
 * @details 
 * This file provides centralized memory mapping for all peripherals for STM32F1xx Series
 *  
 */
 
// Header Guards
#ifndef STM32F1XX_H_
#define STM32F1XX_H_

// --- C++ Safeguards ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ------------------------------------------------------------------------------------------
// Data Types
// ------------------------------------------------------------------------------------------
#include "stm32f1xx_data_types.h"

// ------------------------------------------------------------------------------------------
// Cortex-M3 Core Peripheral Register Structures
// ------------------------------------------------------------------------------------------
#include "cmsis_gcc.h"
#include "stm32f1xx_defines.h"
#include "stm32f1xx_scb.h"
#include "stm32f1xx_systick.h"

// ------------------------------------------------------------------------------------------
// STM32F103C8T6
// ------------------------------------------------------------------------------------------
#include "stm32f1xx_utils.h"
#include "stm32f1xx_base_address.h"
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
#include "stm32f1xx_watchdog.h"
#include "stm32f1xx_flash.h"
#include "stm32f1xx_nvic.h"

// ==========================================================================================
// Address Mapping
// ==========================================================================================

// ------------------------------------------------------------------------------------------
// Cortex-M3 Core Peripherals
// ------------------------------------------------------------------------------------------
/** @brief System Control Block  (Cortex-M3 Core Peripheral) @def SCB */
#define SCB										((SCB_TypeDef*) SCB_BASE_ADDR)
/** @brief Nested Vectored Interrupt Controller  (Cortex-M3 Core Peripheral) @def NVIC */
#define NVIC									((NVIC_TypeDef*) NVIC_BASE_ADDR)
/** @brief System Timer  (Cortex-M3 Core Peripheral) @def SysTick */
#define SysTick									((SysTick_TypeDef*) SysTick_BASE_ADDR)

// ------------------------------------------------------------------------------------------
// AHB Peripherals
// ------------------------------------------------------------------------------------------
/** @brief DMA1 Controller @def DMA1 */
#define DMA1									((DMA_TypeDef*) DMA1_BASE_ADDR)
/**
 * @brief DMA1 Channel 1 @def DMA1_Channel1
 * @details Channel 1 of DMA1 controller
 * @note  - Address: DMA1 base + 0x08 (channel 1 register offset)
 * @note  - Connected peripherals: ADC1, TIM2_CH3, TIM4_CH1
 */
#define DMA1_Channel1 							((DMA_Channel_TypeDef*) (&DMA1->CHANNEL[0]))
/**
 * @brief DMA1 Channel 2 @def DMA1_Channel2
 * @details Channel 2 of DMA1 controller
 * @note  - Address: DMA1 base + 0x1C (channel 2 register offset)
 * @note  - Connected peripherals: SPI1_RX, TIM1_CH1, TIM2_UP, TIM3_CH3
 */
#define DMA1_Channel2 							((DMA_Channel_TypeDef*) (&DMA1->CHANNEL[1]))
/**
 * @brief DMA1 Channel 3 @def DMA1_Channel3
 * @details Channel 3 of DMA1 controller
 * @note  - Address: DMA1 base + 0x30 (channel 3 register offset)
 * @note  - Connected peripherals: SPI1_TX, TIM1_CH2, TIM3_CH4, TIM3_UP
 */
#define DMA1_Channel3 							((DMA_Channel_TypeDef*) (&DMA1->CHANNEL[2]))
/**
 * @brief DMA1 Channel 4 @def DMA1_Channel4
 * @details Channel 4 of DMA1 controller
 * @note  - Address: DMA1 base + 0x44 (channel 4 register offset)
 * @note  - Connected peripherals: SPI2_RX, USART1_TX, I2C2_TX, TIM1_CH4, TIM2_CH1, TIM4_CH3
 */
#define DMA1_Channel4 							((DMA_Channel_TypeDef*) (&DMA1->CHANNEL[3]))
/**
 * @brief DMA1 Channel 5 @def DMA1_Channel5
 * @details Channel 5 of DMA1 controller
 * @note  - Address: DMA1 base + 0x58 (channel 5 register offset)
 * @note  - Connected peripherals: SPI2_TX, USART1_RX, I2C2_RX, TIM1_CH1, TIM2_CH2, TIM4_CH4
 */
#define DMA1_Channel5 							((DMA_Channel_TypeDef*) (&DMA1->CHANNEL[4]))
/**
 * @brief DMA1 Channel 6 @def DMA1_Channel6
 * @details Channel 6 of DMA1 controller
 * @note  - Address: DMA1 base + 0x6C (channel 6 register offset)
 * @note  - Connected peripherals: USART2_RX, I2C1_TX, TIM1_CH3, TIM3_CH1, TIM3_TRIG
 */
#define DMA1_Channel6 							((DMA_Channel_TypeDef*) (&DMA1->CHANNEL[5]))
/**
 * @brief DMA1 Channel 7 @def DMA1_Channel7
 * @details Channel 7 of DMA1 controller
 * @note  - Address: DMA1 base + 0x80 (channel 7 register offset)
 * @note  - Connected peripherals: USART2_TX, I2C1_RX, TIM2_CH2, TIM2_CH4, TIM4_UP
 */
#define DMA1_Channel7 							((DMA_Channel_TypeDef*) (&DMA1->CHANNEL[6]))
/** @brief DMA2 Controller @def DMA2 */
#define DMA2									((DMA_TypeDef*) DMA2_BASE_ADDR)
/**
 * @brief DMA2 Channel 1 @def DMA2_Channel1
 * @details Channel 1 of DMA2 controller
 * @note  - Available only on high-density STM32F103 devices
 * @note  - Address: DMA2 base + 0x08 (channel 1 register offset)
 * @note  - Connected peripherals: ADC3, TIM1_CH1, TIM8_CH3, TIM8_UP
 */
#define DMA2_Channel1 							((DMA_Channel_TypeDef*)(&DMA2->CHANNEL[0]))
/**
 * @brief DMA2 Channel 2 @def DMA2_Channel2
 * @details Channel 2 of DMA2 controller
 * @note  - Available only on high-density STM32F103 devices
 * @note  - Address: DMA2 base + 0x1C (channel 2 register offset)
 * @note  - Connected peripherals: TIM1_CH2, TIM8_CH4, SPI1_RX, USART3_TX
 */
#define DMA2_Channel2 							((DMA_Channel_TypeDef*)(&DMA2->CHANNEL[1]))
/**
 * @brief DMA2 Channel 3 @def DMA2_Channel3
 * @details Channel 3 of DMA2 controller
 * @note  - Available only on high-density STM32F103 devices
 * @note  - Address: DMA2 base + 0x30 (channel 3 register offset)
 * @note  - Connected peripherals: TIM1_CH3, TIM8_CH1, SPI1_TX, USART3_RX
 */
#define DMA2_Channel3 							((DMA_Channel_TypeDef*)(&DMA2->CHANNEL[2]))
/**
 * @brief DMA2 Channel 4 @def DMA2_Channel4
 * @details Channel 4 of DMA2 controller
 * @note  - Available only on high-density STM32F103 devices
 * @note  - Address: DMA2 base + 0x44 (channel 4 register offset)
 * @note  - Connected peripherals: TIM1_CH4, TIM8_CH2, I2C2_TX, USART1_TX
 */
#define DMA2_Channel4 							((DMA_Channel_TypeDef*)(&DMA2->CHANNEL[3]))
/**
 * @brief DMA2 Channel 5 @def DMA2_Channel5
 * @details Channel 5 of DMA2 controller
 * @note  - Available only on high-density STM32F103 devices
 * @note  - Address: DMA2 base + 0x58 (channel 5 register offset)
 * @note  - Connected peripherals: TIM1_UP, TIM8_CH3, I2C2_RX, USART1_RX
 */
#define DMA2_Channel5 							((DMA_Channel_TypeDef *)(&DMA2->CHANNEL[4]))
/** @brief RCC Memory Address @def RCC  */
#define RCC 									((RCC_TypeDef*) RCC_BASE_ADDRESS)
/** @brief Flash Memory Interface  @def FLASH */
#define FLASH									((FLASH_TypeDef*) FLASH_BASE_ADDR)

// ------------------------------------------------------------------------------------------
// APB1 Peripherals
// ------------------------------------------------------------------------------------------
/** @brief General-purpose Timer 2  @def TIM2 */
#define TIM2									((TIM_TypeDef*) TIM2_BASE_ADDRESS)
/** @brief General-purpose Timer 3  @def TIM3 */
#define TIM3									((TIM_TypeDef*) TIM3_BASE_ADDRESS)
/** @brief General-purpose Timer 4  @def TIM4 */
#define TIM4									((TIM_TypeDef*) TIM4_BASE_ADDRESS)
/** @brief General-purpose Timer 5  @def TIM5 */
#define TIM5									((TIM_TypeDef*) TIM5_BASE_ADDRESS)
/** @brief Basic Timer 6  @def TIM6 */
#define TIM6									((TIM_TypeDef*) TIM6_BASE_ADDRESS)
/** @brief Basic Timer 7  @def TIM7 */
#define TIM7									((TIM_TypeDef*) TIM7_BASE_ADDRESS)
/** @brief Window Watchdog @def WWDG */
#define WWDG									((WWDG_TypeDef*) WWDG_BASE_ADDR)
/** @brief Independent Watchdog @def IWDG */
#define IWDG									((IWDG_TypeDef*) IWDG_BASE_ADDR)
/** @brief USART2 Peripheral @def USART2 */
#define USART2									((USART_TypeDef*) USART2_BASE_ADDRESS)
/** @brief USART3 Peripheral @def USART3 */
#define USART3									((USART_TypeDef*) USART3_BASE_ADDRESS)
/** @brief I2C1 Peripheral  @def I2C1 */ 
#define I2C1 									((I2C_TypeDef*) I2C1_BASE_ADDRESS)
/** @brief I2C2 Peripheral  @def I2C2 */ 
#define I2C2 									((I2C_TypeDef*) I2C2_BASE_ADDRESS)

// ------------------------------------------------------------------------------------------
// APB2 Peripherals
// ------------------------------------------------------------------------------------------
/** @brief Alternate Function I/O @def AFIO */
#define AFIO									((AFIO_TypeDef*) AFIO_BASE_ADDRESS)
/** @brief External Interrupt/Event Controller @def EXTI */
#define EXTI									((EXTI_REG_STRUCT*) EXTI_BASE_ADDRESS)
/** @brief General Purpose I/O Port A @def GPIOA */
#define GPIOA									((GPIO_TypeDef*) GPIOA_BASE_ADDRESS)
/** @brief General Purpose I/O Port B @def GPIOB */
#define GPIOB									((GPIO_TypeDef*) GPIOB_BASE_ADDRESS)
/** @brief General Purpose I/O Port C @def GPIOC */
#define GPIOC									((GPIO_TypeDef*) GPIOC_BASE_ADDRESS)
/** @brief General Purpose I/O Port D @def GPIOD */
#define GPIOD									((GPIO_TypeDef*) GPIOD_BASE_ADDRESS)
/** @brief General Purpose I/O Port E @def GPIOE */
#define GPIOE									((GPIO_TypeDef*) GPIOE_BASE_ADDRESS)
/** @brief General Purpose I/O Port F @def GPIOF */
#define GPIOF									((GPIO_TypeDef*) GPIOF_BASE_ADDRESS)
/** @brief General Purpose I/O Port G @def GPIOG */
#define GPIOG									((GPIO_TypeDef*) GPIOG_BASE_ADDRESS)
/** @brief ADC1  @def ADC1 */
#define ADC1									((ADC_TypeDef*) ADC1_BASE_ADDRESS)
/** @brief ADC2  @def ADC2 */
#define ADC2									((ADC_TypeDef*) ADC2_BASE_ADDRESS)
/** @brief Advanced-control Timer 1 @def TIM1 */
#define TIM1									((Adv_TIM_TypeDef*) TIM1_BASE_ADDRESS)
/** @brief Advanced-control Timer 8 @def TIM8 */
#define TIM8									((Adv_TIM_TypeDef*) TIM8_BASE_ADDRESS)
/** @brief USART1  @def USART1 */
#define USART1									((USART_TypeDef*) USART1_BASE_ADDRESS)
/** @brief ADC3  @def ADC3 */
#define ADC3									((ADC_TypeDef*) ADC3_BASE_ADDRESS)

/*----------------------------------------------- I2C MACROS -----------------------------------------------*/
// I2C Speed
#define I2Cx_SPEED_STD							(FREQ_100kHz)
#define I2Cx_SPEED_FAST							(FREQ_100kHz << 2)
// I2C SCL Clock Frequency
#define I2Cx_SCL_FREQ_4MHz						(0x04)
#define I2Cx_SCL_FREQ_8MHz						(0x08)
#define I2Cx_SCL_FREQ_16MHz						(0x10)
#define I2Cx_SCL_FREQ_32MHz						(0x20)
#define I2Cx_SCL_FREQ_DEFAULT 					RCC_GetBusPrescaler(RCC_APB1_BUS)
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

/*----------------------------------------------- SysTick MACROS -----------------------------------------------*/
// SysTick Clock Selection
#define SYSTICK_CLK_EXT (0x00)
#define SYSTICK_CLK_CORE (0x01)

// SysTick Delay
#define SYSTICK_DELAY_1_US (RCC_Get_AHBClock())
#define SYSTICK_DELAY_2_US (SYSTICK_DELAY_1_US << 1)
#define SYSTICK_DELAY_1_MS (SYSTICK_DELAY_1_US / _RCC_FREQ_1kHz)
#define SYSTICK_DELAYS_2_MS (SYSTICK_DELAY_1_MS << 1)

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

// --- C++ Safeguards ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_H_ */