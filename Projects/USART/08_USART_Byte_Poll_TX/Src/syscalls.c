/**
 * @file	syscalls.c
 * @author	Shrey Shah
 * @brief	Adapts the linker-defined application heap to the C library
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section SYSCALLS_C_HIERARCHY Hierarchy
 * - Position: Platform adapter outside the application runtime layers
 * - Called by: C library allocation routines
 * - Uses: Linker-provided `_sheap` / `_eheap` symbols and Core shared types
 *
 * @section SYSCALLS_C_RESPONSIBILITY Responsibility
 * _sbrk() owns the current program break and admits allocations only inside
 * the heap interval defined by the linker script.
 *
 * @section SYSCALLS_C_BOUNDARY Dependency Boundary
 * This module has no dependency on startup, application services, Core
 * registers, or peripheral Drivers.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include <errno.h>
#include "stm32f1xx_data_types.h"

// ==================================================================================================== //
// Linker Symbols
// ==================================================================================================== //

/** @brief First byte of the linker-defined application heap */
extern uint8_t _sheap;
/** @brief One-past-last byte of the linker-defined application heap */
extern uint8_t _eheap;

// ==================================================================================================== //
// C Library Declaration
// ==================================================================================================== //

void* _sbrk(intptr_t increment);

// ==================================================================================================== //
// Private Data
// ==================================================================================================== //

/** @brief Current application heap boundary managed by _sbrk() */
static uint8_t* pHeapEnd = &_sheap;

// ==================================================================================================== //
// C Library Heap Adapter
// ==================================================================================================== //

/**
 * @brief Moves the application heap boundary for the C library allocator
 * @details
 * Applies a signed byte adjustment only when the resulting boundary remains
 * inside the linker-defined interval. Positive adjustments allocate upward;
 * negative adjustments release previously admitted heap space.
 * @param[in] increment Signed byte adjustment requested by the allocator
 * Expected values:
 * - Non-negative values no larger than the remaining heap capacity
 * - Negative values whose magnitude does not exceed the admitted heap growth
 * @returns Previous heap boundary on success or the C library failure sentinel
 * @retval - `&_sheap..&_eheap`: Previous heap boundary after an admitted adjustment
 * @retval - `(void*) -1`: The requested adjustment crossed a linker-defined
 * heap boundary and `errno` was set to `ENOMEM`
 * @warning This implementation is not reentrant; the application must serialize allocation across execution contexts
 * @warning Do not allocate memory from interrupt handlers
 */
void* _sbrk(intptr_t increment)
{
	const uintptr_t heapStartAddress = (uintptr_t) &_sheap;
	const uintptr_t heapLimitAddress = (uintptr_t) &_eheap;
	const uintptr_t currentHeapAddress = (uintptr_t) pHeapEnd;
	uintptr_t incrementMagnitude = 0UL;
	void* pPreviousHeapEnd = pHeapEnd;

	if (increment >= 0)
	{
		incrementMagnitude = (uintptr_t) increment;
		//! Reject upward growth before pointer arithmetic can cross the heap limit.
		if (incrementMagnitude > (heapLimitAddress - currentHeapAddress))
		{
			errno = ENOMEM;
			return (void*) -1;
		}

		//! Commit upward growth only after proving the complete adjustment fits.
		pHeapEnd += incrementMagnitude;
	}
	else
	{
		incrementMagnitude = ((uintptr_t) (-(increment + 1))) + 1UL;
		//! Admit heap contraction only while the boundary remains at or above its origin.
		if (incrementMagnitude > (currentHeapAddress - heapStartAddress))
		{
			errno = ENOMEM;
			return (void*) -1;
		}

		//! Commit contraction only after proving the original heap boundary is preserved.
		pHeapEnd -= incrementMagnitude;
	}

	return pPreviousHeapEnd;
}
