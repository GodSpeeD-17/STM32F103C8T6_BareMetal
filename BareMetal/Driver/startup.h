/*
	Reference: https://maldus512.medium.com/bare-metal-programming-on-an-stm32f103-3a0f4e50ca29
	weak: Allows to overwrite a function
	alias: Calls the Function Name defined when addressed
	section: Stores the code in the partition declared in Linker Script
*/
// Header Guards
#ifndef __STARTUP_H__
#define __STARTUP_H__
/*--------------------------------------------- Headers ----------------------------------*/
// Dependency
#include <stdint.h>
// Required for `errno` in standard `malloc`
#include <errno.h>
// SysTick Configuration
#include "systick.h"
#include "rcc.h"
// GPIO Configuration
#include "gpio.h"
// Use Timer for Delay
#ifndef __SYSTICK_DELAY__
#include "timer.h"
#endif /* __SYSTICK_DELAY__ */

/*-------------------------------------------- MACROS ----------------------------------*/
#define ARM_IRQ									(11)
#define RESERVED								(6)
#define STM32F103C8_IRQ							(59)

// Uncomment this to achieve delay from SysTick
// #define __SYSTICK_DELAY__

// Use Timer for Delay
#ifndef __SYSTICK_DELAY__
// Timer used for Delay
#define DELAY_TIMER							TIM4
// Channel for Timer used for Delay
#define DELAY_TIMER_CHANNEL					TIMx_CHANNEL_NONE
// Timer Interrupt Handler
#define DELAY_TIMER_IRQHandler				TIM4_IRQHandler
#endif /* __SYSTICK_DELAY__ */

/*----------------------------------- Linker Script --------------------------------------------*/
// Start address of initialized data in Flash
extern uint32_t _sidata;
// Start of .data in RAM
extern uint32_t _sdata;
// End of .data in RAM
extern uint32_t _edata;
// Start of .bss
extern uint32_t _sbss;
// End of .bss
extern uint32_t _ebss;
// Top of stack from linker
extern uint32_t _estack;
// Start of heap
extern uint8_t _sheap;
// End of heap
extern uint8_t _eheap;

/*-------------------------------- Handler Prototypes ---------------------*/
__attribute__((weak)) void Default_Handler(void);
__attribute__((weak, naked, noreturn)) void Reset_Handler(void);

/*-------------------------------- Function Prototypes ---------------------*/
__attribute__((weak, alias("Default_Handler"))) void NMI_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void HardFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void MemManage_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void BusFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void UsageFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void SVC_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void DebugMon_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void PendSV_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void WWDG_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void PVD_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TAMPER_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void RTC_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void FLASH_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void RCC_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI0_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI4_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Channel1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Channel2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Channel3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Channel4_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Channel5_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Channel6_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Channel7_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void ADC1_2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void USB_HP_CAN_TX_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void USB_LP_CAN_RX0_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void CAN_RX1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void CAN_SCE_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI9_5_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM1_BRK_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM1_UP_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM1_TRG_COM_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM1_CC_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM3_IRQHandler(void);
#ifdef __SYSTICK_DELAY__
__attribute__((weak, alias("Default_Handler"))) void TIM4_IRQHandler(void);
#else
/**
 * @brief Delay Timer Interrupt Handler
 */
void TIM4_IRQHandler(void);
#endif /* __SYSTICK_DELAY__ */
__attribute__((weak, alias("Default_Handler"))) void I2C1_EV_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void I2C1_ER_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void I2C2_EV_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void I2C2_ER_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void SPI1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void SPI2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void USART1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void USART2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void USART3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI15_10_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void RTC_Alarm_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM8_BRK_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM8_UP_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM8_TRG_COM_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM8_CC_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void ADC3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void FSMC_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void SDIO_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM5_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void SPI3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void UART4_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void UART5_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM6_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM7_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA2_Channel1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA2_Channel2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA2_Channel3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA2_Channel4_5_IRQHandler(void);

/*-------------------------------- Delay Function Prototypes ---------------------*/
#ifndef __SYSTICK_DELAY__
/**
 * @brief Provides a blocking delay in microseconds using TIMx
 * @param delayUs Delay time in microseconds
 * @note Maximum delay achievable is 4,294,967 us (~4.29 seconds)
 * @note - Assumes 1MHz timer frequency
 * @note - Timer is configured in Upcounting Mode
 * @note - Timer is disabled after delay is complete
 * @note - Uses polling method to check for delay completion
 */
void delay_us(uint32_t delayUs);

/**
 * @brief Provides a blocking delay in milliseconds using TIMx
 * @param delayMs Delay time in milliseconds
 * @note Maximum delay achievable is 4,294,967 ms (~4294 seconds or ~71 minutes)
 * @note - Assumes 1MHz timer frequency
 * @note - Timer is configured in Upcounting Mode
 * @note - Timer is disabled after delay is complete
 * @note - Uses polling method to check for delay completion
 */
void delay_ms(uint32_t delayMs);
#endif /* __SYSTICK_DELAY__ */

/*-------------------------------- Main Entry -----------------------------*/
extern int main(void);

/*-------------------------------------------------------------------------------*/
#endif /* __STARTUP_H__ */