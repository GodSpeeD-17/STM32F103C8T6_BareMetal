/**
 * @file ring_buffer_types.h
 * @author Shrey Shah
 * @defgroup RingBuffer Ring Buffer
 * @brief This module provides a brief on Ring Buffer Usage
 * @version v1.2
 * @date 22-10-2025
 * 
 * @details
 * A ring buffer (circular buffer) is a fixed-size FIFO data structure that 
 * uses a single, fixed-size buffer as if it were connected end-to-end.
 * 
 * Key Characteristics:
 * - O(1) time complexity for enqueue and dequeue operations
 * - Fixed memory footprint (no dynamic allocation)
 * - Ideal for ISR and real-time embedded systems
 * - Single producer, single consumer pattern
 * 
 * Operation Principle:
 * The buffer uses two indices (read and write) that wrap around when they 
 * reach the end of the buffer. The buffer is empty when read == write, and
 * full when (write + 1) & (size - 1) == read (in the case of one unused slot).
 * 
 * Memory Layout:
 * [buffer] -> |0|1|2|3|4|...|size-1| (circular)
 * read index: points to next element to read
 * write index: points to next slot to write
 * 
 * @warning For enhanced performance, driver is written assuming the ring buffer size is a power of 2
 *  
 */
// Header Guards
#ifndef RING_BUFFER_TYPES_H_
#define RING_BUFFER_TYPES_H_

// Includes
#include "stm32f1xx.h"

/**
 * @brief Configures a buffer storing 8-bit data iinto a Ring Buffer
 * @defgroup RingBuffer_Returns Ring Buffer Return Types 
 * @ingroup RingBuffer
 * @note Supports a buffer having max 65,536 elements
 * 
 * @{
 */
typedef uint8_t 						ring_buffer_empty_status_t;			/**< @brief Ring Buffer Empty Status */
#define RINGBUFFER_NOT_EMPTY			((ring_buffer_empty_status_t) 0x00) /**< @brief Ring Buffer Not Empty */
#define RINGBUFFER_EMPTY				((ring_buffer_empty_status_t) 0x01) /**< @brief Ring Buffer Empty */
typedef uint8_t 						ring_buffer_full_status_t;			/**< @brief Ring Buffer Full Status */
#define RINGBUFFER_NOT_FULL 			((ring_buffer_full_status_t) 0x00) 	/**< @brief Ring Buffer Full */
#define RINGBUFFER_FULL 				((ring_buffer_full_status_t) 0x01) 	/**< @brief Ring Buffer Not Full */

/**
 * @}
 */ // RingBuffer_Returns
 
/**
 * @brief Configures a buffer storing 8-bit data into a Ring Buffer
 * @defgroup RingBuffer_Configuration Ring Buffer Configuration Structure 
 * @ingroup RingBuffer
 * @note Supports a buffer having max 65,536 elements
 * 
 * @{
 */
typedef uint16_t ring_buffer_size_t; 		/**< @brief Ring Buffer Size */
typedef uint16_t ring_buffer_index_t;		/**< @brief Ring Buffer Index */
typedef uint8_t ring_buffer_data_t;			/**< @brief Ring Buffer Data Size */

/**
 * @brief Ring Buffer Structure
 * 
 * Contains all state and configuration for a ring buffer instance.
 * Multiple instances can coexist independently.
 * 
 * @note Size should be a power of 2
 */
typedef struct _ring_buffer_t
{
	ring_buffer_data_t* buffer; 			/**< @brief Pointer to Buffer */
	ring_buffer_index_t readIdx;			/**< @brief Read Index */
	ring_buffer_index_t writeIdx;			/**< @brief Write Index */
	ring_buffer_size_t size;				/**< @brief Ring Buffer Size */
} ring_buffer_t;

/**
 * @}
 */ // RingBuffer_Configuration


/*----------------------------------------------- Helper Functions -----------------------------------------------*/
// Size of an array
#define SIZEOF(X) (sizeof((X)) / sizeof((X)[0]))

/**
 * @brief Validates that a Ring Buffer size is a power of two
 * @param[in] size Ring Buffer size to validate
 * Accepted values:
 * - `1U..0x8000U`: Any power of two representable by @ref ring_buffer_size_t
 * @returns @ref driver_status_t "Ring Buffer size validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p size is a non-zero power of two
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p size is zero or is not a power of two
 */
__STATIC_FORCEINLINE driver_status_t RingBuffer_ValidateSize(const ring_buffer_size_t size)
{
	//! Power-of-two values contain exactly one set bit; zero is explicitly invalid.
	if ((size != 0U) && ((((uint32_t) size) & (((uint32_t) size) - 1UL)) == 0x00000000UL))
	{
		return DRIVER_STATUS_SUCCESS;
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
}

/**
 * @brief Rounds up a number to the next power of 2
 * @details This function finds the smallest power of 2 that is greater than or
 * equal to the input number 'n'. It uses bitwise operations for performance.
 * @param n The 32-bit unsigned integer to round up
 * @return Rounded up power of 2
 */
__STATIC_FORCEINLINE uint32_t _logicalRoundToNearestPowerOf2(uint32_t n)
{
    // Case 1: If input is 0, the next power of 2 is 1.
    if (n == 0) 
	{
        return 1;
    }

    // Case 2: Handle powers of 2 (e.g., 8, 16, 32) correctly.
    // By subtracting 1, if n was a power of 2, it becomes all ones below that power.
    // If n was not a power of 2, the bit corresponding to the next power of 2 is cleared.
    n--;

    // Step 2: Propagate the highest set bit to the right
    // This fills all bits below the highest original set bit with ones.
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;

    // Step 3: Add 1 to get the next power of 2
    // Adding 1 flips all the trailing ones back to zero, and sets the next highest bit.
    return n + 1;
}

/**
 * @brief Rounds up a number to the next power of 2
 * @details Finds the smallest power of 2 greater than or equal to the input 'x'.
 * This implementation uses the highly optimized GCC/Clang built-in function
 * __builtin_clz (Count Leading Zeros), which maps directly to the CLZ instruction
 * on ARM Cortex-M microcontrollers for maximum performance.
 *
 * The core logic is: 2^log₂(x)
 *
 * @param x The 32-bit unsigned integer to round up.
 * @return The rounded up power of 2. 
 * @note Returns 1 if x is 0.
 */
__STATIC_FORCEINLINE uint32_t _roundToNearestPowerOf2(const uint32_t x)
{
    // Case 1: If input is 0, return 1 (2^0)
    if (x == 0) 
	{
        return 0x00000001;
    }

    /*
     * Implementation using __builtin_clz(x - 1):
     * - Subtracting 1 handles the case where x is already a power of 2,
     * ensuring the result is x itself (e.g., 8 -> 7 -> clz(7)=29 -> 32-29=3 -> 1<<3=8).
     * - __builtin_clz(N) returns the number of leading zero bits in N.
     * - (32 - __builtin_clz(N)) gives the position of the most significant bit,
     * which is equal to log₂(N)
     */
    return (1 << (32 - __builtin_clz(x - 1)));
}


#endif /* RING_BUFFER_TYPES_H_ */
