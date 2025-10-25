/*
	Reference: https://maldus512.medium.com/bare-metal-programming-on-an-stm32f103-3a0f4e50ca29
	weak: Allows to overwrite a function
	alias: Calls the Function Name defined when addressed
	section: Stores the code in the partition declared in Linker Script
*/
// Header Guards
#ifndef STARTUP_H_
#define STARTUP_H_
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
#ifndef SYSTICK_DELAY__
	#include "timer.h"
#endif /* SYSTICK_DELAY__ */

/*-------------------------------------------- MACROS ----------------------------------*/
#define ARM_IRQ									(11)
#define RESERVED								(6)
#define STM32F103C8_IRQ							(59)

// #define SYSTICK_DELAY__			// Uncomment this to achieve delay from SysTick
// Use Timer for Delay
#ifndef SYSTICK_DELAY__
	// Timer used for Delay
	#define DELAY_TIMER							TIM4
	// Channel for Timer used for Delay
	#define DELAY_TIMER_CHANNEL					TIMx_CHANNEL_NONE
// Timer Interrupt Handler
#define DELAY_TIMER_IRQHandler					TIM4_IRQHandler
#endif /* SYSTICK_DELAY__ */

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

/*-------------------------------- Function Prototypes -----------------------------*/
void Default_Handler(void);
/**
 * @brief Function executed upon Reset 
 * @note This function is called only when the processor is reset
 */ 
void Reset_Handler(void);
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
void* _sbrk(intptr_t increment);
/*-------------------------------- Main Entry -----------------------------*/
extern int main(void);

/*-------------------------------- Delay Function Prototypes ---------------------*/
#ifndef SYSTICK_DELAY__
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

#endif /* SYSTICK_DELAY__ */

/*-------------------------------------------------------------------------------*/
#endif /* STARTUP_H_ */