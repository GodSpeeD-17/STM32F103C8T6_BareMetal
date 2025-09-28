/**
 * @file rcc_config.h
 * @author Shrey Shah
 * @brief Reset & Clock Control Configuration
 * @version 1.1
 * @date 27-09-2025
 * @note Logs till v1.1:
 * @note - Aborted usage of `enums` as it consumes a lot of space
 * @note - Shifted to use combination of `typedef` & macros
 */

// Header Guards
#ifndef __RCC_CONFIG_H__
#define __RCC_CONFIG_H__

/*********************************************** Includes ***********************************************/
#include "reg_map.h"

/*********************************************** Frequency ***********************************************/
typedef uint32_t freq_t;
#define FREQ_12Hz 								((freq_t) 12)
#define FREQ_25Hz 								((freq_t) 25)
#define FREQ_50Hz 								((freq_t) 50)
#define FREQ_100Hz 								((freq_t) 100)
#define FREQ_500Hz 								((freq_t) 500)
#define FREQ_1kHz 								((freq_t) 1000)
#define FREQ_2kHz 								((freq_t) 2000)
#define FREQ_5kHz 								((freq_t) 5000)
#define FREQ_10kHz 								((freq_t) 10000)
#define FREQ_50kHz 								((freq_t) 50000)
#define FREQ_72kHz 								((freq_t) 72000)
#define FREQ_100kHz 							((freq_t) 100000)
#define FREQ_200kHz 							((freq_t) 200000)
#define FREQ_1MHz 								((freq_t) 1000000)
#define FREQ_10MHz 								((freq_t) 10000000)

// Clock Speed
#define HSI_FREQ 								((freq_t) 8000000)
#define HSE_FREQ 								((freq_t) 8000000)
#define PLL_MIN_FREQ 							((freq_t) 16000000)
#define PLL_MAX_FREQ 							((freq_t) 72000000)

/*********************************************** Clock Source ***********************************************/
#define RCC_SYS_CLK_HSI 						((system_clock_t) 0x00)
#define RCC_SYS_CLK_HSE 						((system_clock_t) 0x01)
#define RCC_SYS_CLK_PLL 						((system_clock_t) 0x02)

/*********************************************** AHB Prescaler ***********************************************/
#define RCC_AHB_DIV_1 							((bus_prescaler_t) 0x00)
#define RCC_AHB_DIV_2 							((bus_prescaler_t) 0x08)
#define RCC_AHB_DIV_4 							((bus_prescaler_t) 0x09)
#define RCC_AHB_DIV_8 							((bus_prescaler_t) 0x0A)
#define RCC_AHB_DIV_16 							((bus_prescaler_t) 0x0B)
#define RCC_AHB_DIV_64 							((bus_prescaler_t) 0x0C)
#define RCC_AHB_DIV_128 						((bus_prescaler_t) 0x0D)
#define RCC_AHB_DIV_256 						((bus_prescaler_t) 0x0E)
#define RCC_AHB_DIV_512 						((bus_prescaler_t) 0x0F)

/*********************************************** APB1 Prescaler ***********************************************/
#define RCC_APB1_DIV_1 							((bus_prescaler_t) 0x00)
#define RCC_APB1_DIV_2 							((bus_prescaler_t) 0x04)
#define RCC_APB1_DIV_4 							((bus_prescaler_t) 0x05)
#define RCC_APB1_DIV_8 							((bus_prescaler_t) 0x06)
#define RCC_APB1_DIV_16 						((bus_prescaler_t) 0x07)

/*********************************************** APB2 Prescaler ***********************************************/
#define RCC_APB2_DIV_1 							((bus_prescaler_t) 0x00)
#define RCC_APB2_DIV_2 							((bus_prescaler_t) 0x04)
#define RCC_APB2_DIV_4 							((bus_prescaler_t) 0x05)
#define RCC_APB2_DIV_8 							((bus_prescaler_t) 0x06)
#define RCC_APB2_DIV_16 						((bus_prescaler_t) 0x07)

/*********************************************** PLL Clock Source ***********************************************/
#define RCC_PLL_SRC_HSI_DIV_2 					((pll_src_t) 0x00)
#define RCC_PLL_SRC_HSE 						((pll_src_t) 0x01)
#define RCC_PLL_SRC_NOT_USED					((pll_src_t) 0x00) // Reset State

/*********************************************** PLL Clock Source ***********************************************/
#define RCC_PLL_SRC_HSE_DIV_1 					((pll_src_prescaler_t) 0x00)
#define RCC_PLL_SRC_HSE_DIV_2 					((pll_src_prescaler_t) 0x01)
#define RCC_PLL_SRC_HSI_DIV_2 					((pll_src_prescaler_t) 0x00)
#define RCC_PLL_SRC_NOT_USED					((pll_src_prescaler_t) 0x00) // Reset State

/*********************************************** PLL Multiplication Factor ***********************************************/
#define RCC_PLL_MUL_2 							((pll_mul_t) 0x00)
#define RCC_PLL_MUL_3 							((pll_mul_t) 0x01)
#define RCC_PLL_MUL_4 							((pll_mul_t) 0x02)
#define RCC_PLL_MUL_5 							((pll_mul_t) 0x03)
#define RCC_PLL_MUL_6 							((pll_mul_t) 0x04)
#define RCC_PLL_MUL_7 							((pll_mul_t) 0x05)
#define RCC_PLL_MUL_8 							((pll_mul_t) 0x06)
#define RCC_PLL_MUL_9 							((pll_mul_t) 0x07)
#define RCC_PLL_MUL_10 							((pll_mul_t) 0x08)
#define RCC_PLL_MUL_11 							((pll_mul_t) 0x09)
#define RCC_PLL_MUL_12 							((pll_mul_t) 0x0A)
#define RCC_PLL_MUL_13 							((pll_mul_t) 0x0B)
#define RCC_PLL_MUL_14 							((pll_mul_t) 0x0C)
#define RCC_PLL_MUL_15 							((pll_mul_t) 0x0D)
#define RCC_PLL_MUL_16 							((pll_mul_t) 0x0E)
#define RCC_PLL_MUL_NOT_USED					((pll_mul_t) 0x00) // Reset State

/*********************************************** ADC Prescaler ***********************************************/
#define RCC_ADC_DIV_2 							((component_prescaler_t) 0x00)
#define RCC_ADC_DIV_4 							((component_prescaler_t) 0x01)
#define RCC_ADC_DIV_6 							((component_prescaler_t) 0x02)
#define RCC_ADC_DIV_8 							((component_prescaler_t) 0x03)

/*********************************************** USB Prescaler ***********************************************/
#define RCC_USB_DIV_1_5 						((component_prescaler_t) 0x00)
#define RCC_USB_DIV_1 							((component_prescaler_t) 0x01)

/*********************************************** Flash Configuration Structure ***********************************************/
// TODO: Optimize this
typedef struct {
	// 0 < SYSCLK <= 24MHz -> Zero wait state
	// 24MHz < SYSCLK <= 48MHz -> One wait state
	// 48MHz < SYSCLK <= 72MHz -> Two wait states
	uint8_t latency: 3;
	// 0: Prefetch is disabled
	// 1: Prefetch is enabled
	uint8_t prefetch: 5;
} flash_config_t;

/*********************************************** Bus Configuration Structure ***********************************************/
typedef uint8_t bus_prescaler_t;
/**
 * @brief Bus Prescaler Configuration Structure
 */
typedef struct {
	/**
	 * @brief AHB Bus Prescaler
	 * @param AHB AHB Prescalar Values Refer `RCC_AHB_DIV_*`
	 * @note Max frequency = 72MHz
	 */
	bus_prescaler_t AHB: 4;
	/**
	 * @brief APB1 Bus Prescaler
	 * @param APB1 APB1 Prescalar Values Refer `RCC_APB1_DIV_*`
	 * @note Max frequency = 36MHz
	 */
	bus_prescaler_t APB1: 3;
	/**
	 * @brief APB2 Bus Prescaler
	 * @param APB2 APB2 Prescalar Values Refer `RCC_APB2_DIV_*`
	 * @note Max frequency = 72MHz
	 */
	bus_prescaler_t APB2: 3;
} bus_prescaler_config_t;

/*********************************************** PLL Configuration ***********************************************/
typedef uint8_t pll_src_t;
typedef uint8_t pll_mul_t;
typedef uint8_t pll_src_prescaler_t;
/**
 * @brief PLL Configuration Structure
 */
typedef struct {
	/**
	 * @brief PLL Multiplication Factor Configuration
	 * @note - Determines the multiplication factor
	 * @note - Determines the final Clock Frequency if PLL is Clock Source
	 * @note - Max frequency: 72MHz
	 * @note - Do not use `0x0F` for setting the multiplication factor to 16
	 */
	pll_mul_t mul_fact: 4;
	/**
	 * @brief PLL Source Configuration
	 * @note - Determines the input to PLL
	 * @note - For STM32F1xx, the HSI is always divided by 2 
	 */
	pll_src_t src: 1;
	/**
	 * @brief PLL Source Prescaler Configuration
	 * @note - Determines the prescaler to PLL Source
	 * @note - For STM32F1xx, the HSI does not have prescaler configuration
	 */
	pll_src_prescaler_t src_prescaler: 1;
} pll_config_t;

/*********************************************** Internal Components Clock Configuration ***********************************************/
typedef uint8_t component_prescaler_t;
/**
 * @brief Component Prescaler Configuration Structure
 */
typedef struct {
	/**
	 * @brief ADC Prescaler Configuration
	 * @note - Max Frequency: 14MHz
	 * @note - Clock Source: `APB2`
	 */
	component_prescaler_t ADC: 2;
	/**
	 * @brief USB Prescaler Configuration
	 * @note - Max Frequency: 48MHz
	 * @note - Clock Source: `PLL`
	 */
	component_prescaler_t USB: 1;
} component_prescaler_config_t;

/*********************************************** System Clock Structure ***********************************************/
typedef uint8_t system_clock_t;
/**
 * @brief System Clock Configuration Structure
 */
typedef struct {
	/**
	 * @brief System Clock Source
	 * @param clk_src `RCC_SYS_CLK_HSI`, `RCC_SYS_CLK_HSE`, `RCC_SYS_CLK_PLL`
	 * @note This defines the AHB input clock before AHB Prescaler
	 */
	system_clock_t clk_src;
	/**
	 * @brief Phase Lock Loop (PLL) Configuration Structure
	 * @param pll Refer `pll_config_t`
	 * @note This parameter defines the PLL Configuration to be set.
	 */
	pll_config_t pll;
} sys_clk_t;

/*********************************************** RCC Configuration Structure ***********************************************/
/**
 * @brief RCC Confifuration Structure
 */
typedef struct {
	// Bus Prescaler Configuration
	bus_prescaler_config_t bus_prescaler;
	// System Clock
	sys_clk_t system;
	// Flash Configuration
	flash_config_t flash;
	// Components Prescaler
	component_prescaler_config_t component_prescaler;
} rcc_config_t;

/*********************************************** RCC Clock Frequency ***********************************************/
/**
 * @brief RCC Clock Frequency Structure
 */
typedef struct {
	// System Clock Frequency
	freq_t Core;
	// AHB Clock Frequency
	freq_t AHB;
	// APB1 Clock Frequency
	freq_t APB1;
	// APB2 Clock Frequency
	freq_t APB2;
} rcc_clk_freq_t;

/*********************************************** Prescaler Lookup Table ***********************************************/
extern const bus_prescaler_t __ahbPrescalerDriverMapping__[8];
extern const bus_prescaler_t __apbPrescalerDriverMapping__[4];

/**
 * @brief Enables Clock for Alternate Function (AFIO)
 */
__STATIC_INLINE__ void RCC_AFIO_Clk_Enable(void){
	// Enable AFIO Clock
	RCC->APB2ENR.REG |= RCC_APB2ENR_AFIOEN;
}

/**
 * @brief Disables Clock for Alternate Function (AFIO)
 */
__STATIC_INLINE__ void RCC_AFIO_Clk_Disable(void){
	// Disable AFIO Clock
	RCC->APB2ENR.REG &= ~RCC_APB2ENR_AFIOEN;
}

/**
 * @brief Computes the APB1 Clock Divisor from prescaler
 * @param prescaler Refer `RCC_APB1_DIV_*`
 * @return Computed Divisor Value
 */
__STATIC_INLINE__ uint8_t RCC_APB1ComputePrescaler(const bus_prescaler_t prescaler){
	return ((uint8_t)((prescaler == RCC_APB1_DIV_1)? (0x01) : (0x01 << (__apbPrescalerDriverMapping__[prescaler]))));
}

/**
 * @brief Computes the APB2 Clock Divisor from prescaler
 * @param prescaler Refer `RCC_APB2_DIV_*`
 * @return Computed Divisor Value
 */
__STATIC_INLINE__ uint8_t RCC_APB2ComputePrescaler(const bus_prescaler_t prescaler){
	return ((uint8_t)((prescaler == RCC_APB2_DIV_1)? (0x01) : (0x01 << (__apbPrescalerDriverMapping__[prescaler]))));
}

__STATIC_INLINE__ uint16_t RCC_AHBComputePrescaler(const bus_prescaler_t prescaler){
	return ((uint16_t)((prescaler == RCC_AHB_DIV_1)? (0x01) : (0x01 << __ahbPrescalerDriverMapping__[prescaler])));
}

#ifdef __OLD_RCC_METHOD__
/**
 * @brief AHB Prescaler
 */
uint8_t RCC_Get_AHB_Prescaler(void);

/**
 * @brief APB1 Prescaler
 */
uint8_t RCC_Get_APB1_Prescaler(void);

/**
 * @brief APB2 Prescaler
 */
uint8_t RCC_Get_APB2_Prescaler(void);

/**
 * @brief Updates the Core Clock
 * @note This function should be called after any change in the RCC configuration
 * @note Max Frequency: 72MHz 
 */
void RCC_Update_CoreClock();

/**
 * @brief Updates the AHB Clock based upon AHB prescaler (`HPRE`)
 * @note This function should be called after any change in the RCC configuration
 * @note Max Frequency: 72MHz
 */
void RCC_Update_AHBClock();

/**
 * @brief Updates the APB1 Clock based upon APB1 prescaler (`PPRE1`)
 * @note This function should be called after any change in the RCC configuration
 * @note Max Frequency: 36MHz 
 */
void RCC_Update_APB1Clock();

/**
 * @brief Updates the APB2 Clock based upon APB2 prescaler (`PPRE2`)
 * @note This function should be called after any change in the RCC configuration
 * @note Max Frequency: 72MHz 
 */
void RCC_Update_APB2Clock();

/**
 * @brief Retrieves the Core Clock Frequency
 * @return Core Clock Frequency 
 * @note Max Frequency: 72MHz 
 */
uint32_t RCC_Get_CoreClock();

/**
 * @brief Retrieves the AHB Clock Frequency
 * @return AHB Frequency 
 * @note Max Frequency: 72MHz 
 */
uint32_t RCC_Get_AHBClock();

/**
 * @brief Retrieves the APB1 Clock Frequency
 * @return APB1 Frequency 
 * @note Max Frequency: 36MHz
 */
uint32_t RCC_Get_APB1Clock();

/**
 * @brief Retrieves the APB2 Clock Frequency
 * @return APB2 Frequency 
 * @note Max Frequency: 72MHz 
 */
uint32_t RCC_Get_APB2Clock();

#endif /* __OLD_RCC_METHOD__ */

#endif /* __RCC_CONFIG_H__ */