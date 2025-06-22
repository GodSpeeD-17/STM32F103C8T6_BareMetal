/*
	Reference: https://maldus512.medium.com/bare-metal-programming-on-an-stm32f103-3a0f4e50ca29
	weak: Allows to overwrite a function
	alias: Calls the Function Name defined when addressed
	section: Stores the code in the partition declared in Linker Script
*/
/*--------------------------------------------- HEADERS ----------------------------------*/
// Dependency
#include <stdint.h>
// For System Clock Configuration (72MHz)
#include "rcc.h"
// SysTick Configuration
#include "systick.h"
// GPIO Configuration
#include "gpio.h"
// Required for `errno` in standard `malloc`
#include <errno.h>
/*-------------------------------------------- MACROS ----------------------------------*/
#define ARM_IRQ						((uint8_t) 11)
#define RESERVED					((uint8_t) 6)
#define STM32F103C8_IRQ				((uint8_t) 59)
/*----------------------------------- LINKER SCRIPT --------------------------------------------*/
// Start address of initialized data in FLASH
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
// Current heap pointer
static uint8_t *heap_ptr = &_sheap;
/*-------------------------------------------------------------------------------*/
// External Main Function
__attribute__((weak, naked)) extern int main(void);    
/*-------------------------------------------------------------------------------*/
// Function Prototypes
__attribute__((weak)) void Default_Handler(void);
__attribute__((weak, naked, noreturn))          void Reset_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void NMI_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void HardFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void MemManage_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void BusFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void UsageFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void SVC_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void DebugMon_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void PendSV_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void SysTick_Handler(void);
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
__attribute__((weak, alias("Default_Handler"))) void TIM4_IRQHandler(void);
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
/*-------------------------------------------------------------------------------*/
// Vector Table (Placed in ".isr_vector" section)
__attribute__((section(".isr_vector"))) const uint32_t vector_table[ARM_IRQ + RESERVED + STM32F103C8_IRQ] = {
	(uint32_t) (&_estack),
	(uint32_t) Reset_Handler,
	(uint32_t) NMI_Handler,
	(uint32_t) HardFault_Handler,
	(uint32_t) MemManage_Handler,
	(uint32_t) BusFault_Handler,
	(uint32_t) UsageFault_Handler,
	(uint32_t) 0,	// Reserved (STM32F103C8 Datasheet NVIC Section)
	(uint32_t) 0,	// Reserved (STM32F103C8 Datasheet NVIC Section)
	(uint32_t) 0,	// Reserved (STM32F103C8 Datasheet NVIC Section)
	(uint32_t) 0,	// Reserved (STM32F103C8 Datasheet NVIC Section)
	(uint32_t) SVC_Handler,
	(uint32_t) DebugMon_Handler,
	(uint32_t) 0,	// Reserved (STM32F103C8 Datasheet NVIC Section)
	(uint32_t) PendSV_Handler,
	(uint32_t) SysTick_Handler,
	(uint32_t) WWDG_IRQHandler,
	(uint32_t) PVD_IRQHandler,
	(uint32_t) TAMPER_IRQHandler,
	(uint32_t) RTC_IRQHandler,
	(uint32_t) FLASH_IRQHandler,
	(uint32_t) RCC_IRQHandler, 
	(uint32_t) EXTI0_IRQHandler,
	(uint32_t) EXTI1_IRQHandler,
	(uint32_t) EXTI2_IRQHandler,
	(uint32_t) EXTI3_IRQHandler,
	(uint32_t) EXTI4_IRQHandler,
	(uint32_t) DMA1_Channel1_IRQHandler,
	(uint32_t) DMA1_Channel2_IRQHandler,
	(uint32_t) DMA1_Channel3_IRQHandler,
	(uint32_t) DMA1_Channel4_IRQHandler,
	(uint32_t) DMA1_Channel5_IRQHandler,
	(uint32_t) DMA1_Channel6_IRQHandler,
	(uint32_t) DMA1_Channel7_IRQHandler,
	(uint32_t) ADC1_2_IRQHandler,
	(uint32_t) USB_HP_CAN_TX_IRQHandler,
	(uint32_t) USB_LP_CAN_RX0_IRQHandler,
	(uint32_t) CAN_RX1_IRQHandler,
	(uint32_t) CAN_SCE_IRQHandler,
	(uint32_t) EXTI9_5_IRQHandler,
	(uint32_t) TIM1_BRK_IRQHandler,
	(uint32_t) TIM1_UP_IRQHandler,
	(uint32_t) TIM1_TRG_COM_IRQHandler,
	(uint32_t) TIM1_CC_IRQHandler,
	(uint32_t) TIM2_IRQHandler,
	(uint32_t) TIM3_IRQHandler,
	(uint32_t) TIM4_IRQHandler,
	(uint32_t) I2C1_EV_IRQHandler,
	(uint32_t) I2C1_ER_IRQHandler,
	(uint32_t) I2C2_EV_IRQHandler,
	(uint32_t) I2C2_ER_IRQHandler,
	(uint32_t) SPI1_IRQHandler,
	(uint32_t) SPI2_IRQHandler,
	(uint32_t) USART1_IRQHandler,
	(uint32_t) USART2_IRQHandler,
	(uint32_t) USART3_IRQHandler,
	(uint32_t) EXTI15_10_IRQHandler,
	(uint32_t) RTC_Alarm_IRQHandler,
	(uint32_t) 0,	// Reserved (STM32F103C8 Datasheet NVIC Section)
	(uint32_t) TIM8_BRK_IRQHandler,
	(uint32_t) TIM8_UP_IRQHandler,
	(uint32_t) TIM8_TRG_COM_IRQHandler,
	(uint32_t) TIM8_CC_IRQHandler,
	(uint32_t) ADC3_IRQHandler,
	(uint32_t) FSMC_IRQHandler,
	(uint32_t) SDIO_IRQHandler,
	(uint32_t) TIM5_IRQHandler,
	(uint32_t) SPI3_IRQHandler,
	(uint32_t) UART4_IRQHandler,
	(uint32_t) UART5_IRQHandler,
	(uint32_t) TIM6_IRQHandler,
	(uint32_t) TIM7_IRQHandler,
	(uint32_t) DMA2_Channel1_IRQHandler,
	(uint32_t) DMA2_Channel2_IRQHandler,
	(uint32_t) DMA2_Channel3_IRQHandler,
	(uint32_t) DMA2_Channel4_5_IRQHandler
};
/*-------------------------------------------------------------------------------*/
/**
 * @brief Function executed upon Reset 
 * @note This function is called only when the processor is reset
 */ 
__attribute__((weak, naked, noreturn)) void Reset_Handler(void){
	// Step 1: Copy ".data" [FLASH] -> ".data" [RAM]
	uint32_t* pSrc = (uint32_t *) &_sidata;
	uint32_t* pDst = (uint32_t *) &_sdata;
	while(pDst < &_edata){
		*pDst++ = *pSrc++;
	}
	// Step 2: Initialise .bss to 0 in RAM
	pDst = (uint32_t *)&_sbss;
	while(pDst < &_ebss){
		*pDst++ = 0;
	}
	// Step 3: Configure SysClock at 72MHz
	RCC_Config_72MHz();
	// Step 4: Configure SysTick (Resolution us)
	SysTick_Config((RCC_Get_AHBClock()/FREQ_1MHz));
	// Step 5: Configure OB LED
	OB_LED_Config();
	OB_LED_Reset();
	// Step 6: Call main()
	main();
	// Step 7: Infinite Loop (Backup)
	while(1) 
		(void) 0;
}
/*-------------------------------------------------------------------------------*/
// Default Handler (Overwrite This)
__attribute__((weak)) void Default_Handler(void){
	// Infinite Loop
	while(1) 
		(void) 0;
}
/*-------------------------------------------------------------------------------*/
/**
 * @brief Requests additional heap memory from the system
 * 
 * @param increment Number of bytes to increase the heap by
 * @return void* 
 *   - On success: Pointer to the start of the newly allocated memory block
 *   - On failure: (void*)-1 with errno set to ENOMEM (heap overflow)
 * 
 * @note This is the low-level memory allocator used by malloc()/calloc()
 * @warning The heap grows upward while stack grows downward - ensure they don't collide!
 * @warning Not thread-safe - use in single-threaded environments only
 * 
 * Memory layout:
 * 
 * RAM: [.data][.bss][heap → ... ← stack]
 *            _sheap   heap_ptr   _eheap
 *                   (grows up)
 */
void *_sbrk(intptr_t increment){
	// Update Previous Heap Pointer
    uint8_t *prev_heap_ptr = heap_ptr;
    // Check for heap overflow
    if (heap_ptr + increment > &_eheap) {
		// Set standard `errno` for `malloc` compatibility
        errno = ENOMEM;
        return (void *)-1;
    }
	// Update heap pointer
    heap_ptr += increment;
	// Return previous heap pointer
    return (void *)prev_heap_ptr;
}