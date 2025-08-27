/*-------------------------------- Includes ---------------------------*/
#include "startup.h"

// Uncomment this to achieve delay from SysTick
// #define __SYSTICK_DELAY__

#ifndef __SYSTICK_DELAY__
#include "timer.h"
/*-------------------------------- Local Variables ------------------------*/
timer_config_t TIM_Configuration = {
	// Timer
	.TIM = DELAY_TIMER,
	// Channel
	.channel = DELAY_TIMER_CHANNEL,
};

#endif /* __SYSTICK_DELAY__ */

/*-------------------------------- Heap Pointer ---------------------------*/
static uint8_t *heap_ptr = &_sheap;

/*-------------------------------- Vector Table ------------------------*/
// NOTE: Placed in ".isr_vector" section
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

/*-------------------------------- Reset Handler ------------------------*/
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
	// Step 4: Configure SysTick & Timer
	#ifdef __SYSTICK_DELAY__
		// SysTick: Resolution 1us
		SysTick_Config(((RCC_Get_AHBClock())/FREQ_1MHz));
	#else
		// SysTick: Resolution 1ms
		SysTick_Config(((RCC_Get_AHBClock())/FREQ_1kHz));
		// TIM Configuration for 1us resolution
		TIM_1MHz_Load_Default(&TIM_Configuration);
		// Configure TIM
		TIM_Config(&TIM_Configuration);
	#endif /* __SYSTICK_DELAY__ */
	SysTick_Enable();
	// Step 5: Configure OB LED & Enable SysTick
	OB_LED_Config();
	// Step 6: Call main()
	main();
	// Step 7: Default Handler (Should never be reached)
	Default_Handler();
}

/*-------------------------------- Default Handler ---------------------*/
// Default Handler (Overwrite This)
__attribute__((weak)) void Default_Handler(void){
	// Read the fault status registers
	__asm volatile (
		"MRS r0, MSP\n"             // Get the main stack pointer
		"B hard_fault_handler_c\n"  // Branch to C handler
	);
}

void hard_fault_handler_c(uint32_t *stack) {
	// Inspect the stack frame
	uint32_t r0 = stack[0];
	uint32_t r1 = stack[1];
	uint32_t r2 = stack[2];
	uint32_t r3 = stack[3];
	uint32_t r12 = stack[4];
	uint32_t lr = stack[5];
	uint32_t pc = stack[6];
	uint32_t psr = stack[7];
	// You can log these values or inspect them in the debugger
	while (1); // Loop forever
}

/*-------------------------------- Dynamic Memory Management ---------------------*/
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
void* _sbrk(intptr_t increment){
	// Check for heap overflow
	if(heap_ptr + increment > &_eheap){
		// Set standard `errno` for `malloc` compatibility
		errno = ENOMEM;
		return (void *)-1;
	}
	// Update Previous Heap Pointer
	uint8_t *prev_heap_ptr = heap_ptr;
	// Update heap pointer
	heap_ptr += increment;
	// Return previous heap pointer
	return (void *)prev_heap_ptr;
}
/*-------------------------------------------------------------------------------*/