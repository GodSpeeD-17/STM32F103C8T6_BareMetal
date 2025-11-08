/*-------------------------------- Includes ---------------------------*/
#include "startup.h"
/*-------------------------------- Local Variables ------------------------*/
// Timer Delay Configuration
#ifndef SYSTICK_DELAY__
// Timer Configuration Structure
static timer_config_t TIM_Configuration = {
#ifdef __OLD_TIMER_METHOD__
	// Timer
	.TIM = DELAY_TIMER,
	// Channel
	.channel = DELAY_TIMER_CHANNEL,
#else
	// Timer
	.instance = DELAY_TIMER,
	// Channel
	.channel.instance = DELAY_TIMER_CHANNEL,
#endif /* __OLD_TIMER_METHOD__ */
};
#endif /* SYSTICK_DELAY__ */

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
	uint32_t *pSrc = (uint32_t *)&_sidata;
	uint32_t *pDst = (uint32_t *)&_sdata;
	while (pDst < &_edata) *pDst++ = *pSrc++;
	// Step 2: Initialise .bss to 0 in RAM
	pDst = (uint32_t *)&_sbss;
	while (pDst < &_ebss) *pDst++ = 0;
	// Step 3: Configure SysClock at 72MHz
	RCC_Config_72MHz();
// Step 4: Configure SysTick & Timer
#ifdef SYSTICK_DELAY__
	// SysTick: Resolution 1us
	SysTick_Config(((RCC_AHBClockFreq_Get()) / FREQ_1MHz));
#else
	// SysTick: Resolution 1ms
	SysTick_Config(((RCC_AHBClockFreq_Get()) / FREQ_1kHz));
	// TIM Configuration for 1us resolution
	TIM_1MHz_Load_Default(&TIM_Configuration);
	// Configure TIM with the parameters
	TIM_Config(&TIM_Configuration);
	// Configure TIM Interrupt for Overflow
	TIM_IRQ_Enable(DELAY_TIMER, TIMx_IRQ_OVF_UVF);
#endif /* SYSTICK_DELAY__ */
	SysTick_Enable();
	// Step 5: Configure OB LED & Enable SysTick
	OB_LED_Init();
	OB_LED_Reset();
	// Step 6: Call main()
	main();
	// Step 7: Default Handler (Should never be reached)
	Default_Handler();
}

/*-------------------------------- Timer Handler ------------------------*/
// Timer Delay Functions
#ifndef SYSTICK_DELAY__
// Delay Counter
static volatile uint8_t delayCompleted = 0x00;

/**
 * @brief Provides a blocking delay in microseconds using TIMx
 * @param delayUs Delay time in microseconds
 * @note Maximum delay achievable is 4,294,967 us (~4.29 seconds)
 * @note - Assumes 1MHz timer frequency
 * @note - Timer is configured in Upcounting Mode
 * @note - Timer is disabled after delay is complete
 * @note - Uses polling method to check for delay completion
 */
void delay_us(uint32_t delayUs)
{
	// Disable the Timer
	TIM_Disable(DELAY_TIMER);
	// Configure Timer Count Value
	DELAY_TIMER->CNT = TIMx_DEFAULT_CNT;
	// Configure Delay Time
	DELAY_TIMER->ARR = (delayUs - 1);
	// Enable the Timer
	TIM_Enable(DELAY_TIMER);
	// Wait until delay is done
	while (delayCompleted != 0x01);
	delayCompleted = 0x00;
	// Disable the Timer
	TIM_Disable(DELAY_TIMER);
	// Clear the UIF Flag
	DELAY_TIMER->SR.REG &= ~TIM_SR_UIF;
}

/**
 * @brief Provides a blocking delay in milliseconds using TIMx
 * @param delayMs Delay time in milliseconds
 * @note Maximum delay achievable is 4,294,967 ms (~4294 seconds or ~71 minutes)
 * @note - Assumes 1MHz timer frequency
 * @note - Timer is configured in Upcounting Mode
 * @note - Timer is disabled after delay is complete
 * @note - Uses polling method to check for delay completion
 */
void delay_ms(uint32_t delayMs)
{
	// Iteration for each number of milliseconds
	while (delayMs--)
	{
		// Create delay of ~998us
		delay_us(998);
	}
}

/**
 * @brief Timer Interrupt Handler
 */
void DELAY_TIMER_IRQHandler(void)
{
	// Check for Interrupt Flag
	if (TIM_IRQ_Get_OVF_UVF(DELAY_TIMER))
	{
		// Status for Delay Complete
		delayCompleted = 0x01;
		// Acknowledge the Interrupt Flag
		TIM_IRQ_Ack_OVF_UVF(DELAY_TIMER);
	}
}

#endif /* SYSTICK_DELAY__ */