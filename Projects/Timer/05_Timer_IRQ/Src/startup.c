/*-------------------------------- Includes ---------------------------*/
#include "startup.h"
/*-------------------------------- Heap Pointer ---------------------------*/
static uint8_t *heap_ptr = &_sheap;

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
void *_sbrk(intptr_t increment)
{
	// Check for heap overflow
	if (heap_ptr + increment > &_eheap)
	{
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

/*-------------------------------- Reset Handler ------------------------*/
/**
 * @brief Function executed upon Reset
 * @note This function is called only when the processor is reset
 */
void Reset_Handler(void)
{
	// Step 1: Copy ".data" [FLASH] -> ".data" [RAM]
	volatile uint32_t *pSrc = (uint32_t *)&_sidata;
	volatile uint32_t *pDst = (uint32_t *)&_sdata;
	// Memory barrier to prevent reordering
	__asm__ volatile ("" ::: "memory");	
	while (pDst < &_edata) *pDst++ = *pSrc++;
	// Step 2: Initialise .bss to 0 in RAM
	pDst = (uint32_t *)&_sbss;
	while (pDst < &_ebss) *pDst++ = 0;
	// Memory barrier to prevent reordering
	__asm__ volatile ("" ::: "memory");		
	// Step 3: Configure SysClock at 72MHz
	if (RCC_Config_72MHz() != DRIVER_STATUS_SUCCESS)
	{
		Default_Handler();
	}
	// Step 4: Configure SysTick and the startup delay service
#ifdef SYSTICK_DELAY__
	// SysTick: Resolution 1us
	SysTick_Config(((RCC_GetBusFreq(RCC_AHB_BUS)) / FREQ_1MHz));
#else
	// SysTick: Resolution 1ms
	SysTick_Config(((RCC_GetBusFreq(RCC_AHB_BUS)) / RCC_FREQ_1kHz));
	//! Enable the dedicated delay Timer clock, then apply the canonical 72 MHz-to-1 MHz configuration.
	if (RCC_APB1_ClockEnable(DELAY_TIMER_CLOCK_ENABLE_MASK) != DRIVER_STATUS_SUCCESS)
	{
		Default_Handler();
	}
	if (TIM_ConfigDelay1MHz(DELAY_TIMER) != DRIVER_STATUS_SUCCESS)
	{
		Default_Handler();
	}
#endif /* SYSTICK_DELAY__ */
	SysTick_Enable();
	// Step 5: Configure OB LED & Enable SysTick
	//! Stop startup when the board LED cannot provide a reliable application status indicator.
	if (OB_LED_Init() != DRIVER_STATUS_SUCCESS)
	{
		Default_Handler();
	}
	OB_LED_Reset();
	// Step 6: Call main()
	main();
	// Step 7: Default Handler (Should never be reached)
	Default_Handler();
}

// Timer Delay Functions
#ifndef SYSTICK_DELAY__
void delay_us(uint32_t delayUs)
{
	while (delayUs != 0UL)
	{
		uint16_t chunkUs;

		//! Bound each public delay request to the Timer API's 16-bit duration contract.
		if (delayUs > 0xFFFFUL)
		{
			chunkUs = 0xFFFFU;
		}
		else
		{
			chunkUs = (uint16_t) delayUs;
		}

		if (TIM_DelayUs(DELAY_TIMER, chunkUs) != DRIVER_STATUS_SUCCESS)
		{
			Default_Handler();
		}
		delayUs -= (uint32_t) chunkUs;
	}
}

void delay_ms(uint32_t delayMs)
{
	if (delayMs != 0UL)
	{
		if (TIM_DelayMs(DELAY_TIMER, delayMs) != DRIVER_STATUS_SUCCESS)
		{
			Default_Handler();
		}
	}
}

#endif /* SYSTICK_DELAY__ */
