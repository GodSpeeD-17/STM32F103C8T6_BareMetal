#include <errno.h>
#include <stdint.h>

extern uint8_t _sheap;
extern uint8_t _eheap;

void* _sbrk(intptr_t increment);

static uint8_t* pHeapEnd = &_sheap;

/**
 * @brief Moves the application heap boundary for the C library allocator
 * @param[in] increment Signed byte adjustment requested by the allocator
 * @returns Previous heap boundary on success or `(void*) -1` on failure
 * @warning The application owns synchronization when allocation is used from multiple contexts
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
		if (incrementMagnitude > (heapLimitAddress - currentHeapAddress))
		{
			errno = ENOMEM;
			return (void*) -1;
		}

		pHeapEnd += incrementMagnitude;
	}
	else
	{
		incrementMagnitude = ((uintptr_t) (-(increment + 1))) + 1UL;
		if (incrementMagnitude > (currentHeapAddress - heapStartAddress))
		{
			errno = ENOMEM;
			return (void*) -1;
		}

		pHeapEnd -= incrementMagnitude;
	}

	return pPreviousHeapEnd;
}
