/**
 * @file ring_buffer.h
 * @author Shrey Shah
 * @version v1.2
 * @date 22-10-2025
 * 
 * @brief This module provides documentation for Ring Buffer APIs
 * @defgroup RingBuffer_API Ring Buffer APIs
 * @ingroup RingBuffer
 * 
 * @{
 */

// Header Guards
#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

// Includes
#include "ring_buffer_types.h"

//-----------------------------------------------------------------------------
// Ring Buffer Core Functions
//-----------------------------------------------------------------------------

/**
 * @brief Initializes the Ring Buffer structure.
 * @ingroup RingBuffer
 * @details Sets up the buffer pointers and indices. **It is mandatory** that
 * the provided buffer size is a **power of 2** for the fast bitwise index wrapping to work.
 * @param rb Pointer to the ring_buffer_t structure to initialize.
 * @param buffer Pointer to the data buffer (must be of size `size`).
 * @param size The size of the buffer. Must be a power of 2 (e.g., 2, 4, 8, ...).
 * @returns Driver Operation Status:
 * @returns - `DRIVER_SUCCESS`: Initialization Successful
 * @returns - `DRIVER_FAIL`: `size` is not a power of 2
 */
driver_status_t RingBuffer_Init(ring_buffer_t* rb, ring_buffer_data_t* const buffer, const ring_buffer_size_t size)
{
	// Size should be power of 2
	if(_isPowerOf2(size) != 0x01)
	{
		return DRIVER_FAIL;
	}

	// Init Ring Buffer
	rb->buffer = buffer;
	rb->size = size;
	rb->readIdx = 0;
	rb->writeIdx = 0;

	return DRIVER_SUCCESS;
}

/**
 * @brief Checks if the Ring Buffer is empty
 * @param rb Pointer to the constant ring_buffer_t structure.
 * @returns Ring Buffer Empty Status:
 * @returns - `RINGBUFFER_EMPTY`: Ring Buffer Empty
 * @returns - `RINGBUFFER_NOT_EMPTY`: Otherwise
 * @details The buffer is empty when the read index equals the write index
 */
__STATIC_FORCEINLINE ring_buffer_empty_status_t RingBuffer_isEmpty(const ring_buffer_t* const rb)
{
	return ((ring_buffer_empty_status_t) (rb->readIdx == rb->writeIdx));
}

/**
 * @brief Checks if the Ring Buffer is full
 * @param rb Pointer to the constant ring_buffer_t structure.
 * @returns Ring Buffer Full Status:
 * @returns - `RINGBUFFER_FULL`: Ring Buffer Full
 * @returns - `RINGBUFFER_NOT_FULL`: Otherwise
 * @details The buffer is considered full when the next write index (calculated
 * using fast power-of-2 wrapping) equals the current read index
 */
__STATIC_FORCEINLINE ring_buffer_full_status_t RingBuffer_isFull(const ring_buffer_t* const rb)
{
	return ((ring_buffer_full_status_t) (((rb->readIdx + 1) & (rb->size - 1)) == rb->writeIdx));
}

/**
 * @brief Gets the current number of elements stored in the Ring Buffer
 * @param rb Pointer to the constant `ring_buffer_t` structure
 * @return The number of currently stored elements
 * @details Calculates the number of elements by finding the modular difference
 * between the write and read indices
 */
__STATIC_FORCEINLINE ring_buffer_size_t RingBuffer_Count(const ring_buffer_t* const rb)
{
    return ((ring_buffer_size_t)(((uint32_t)(rb->writeIdx - rb->readIdx)) & ((uint32_t)(rb->size - 1))));
}

/**
 * @brief Writes a single data element into the Ring Buffer
 * @param rb Pointer to the `ring_buffer_t` structure
 * @param data The `ring_buffer_data_t` data element to write
 * @returns Driver Operation Status:
 * @returns - `DRIVER_SUCCESS`: Data written into Ring Buffer
 * @returns - `DRIVER_FAIL`: Ring Buffer Full
 * @details Appends data at the current write index and increments the index using
 * the fast bitwise AND wrapping. The operation fails if the buffer is full.
 */
__STATIC_FORCEINLINE driver_status_t RingBuffer_Write(ring_buffer_t* const rb, const ring_buffer_data_t data)
{
	// Ring Buffer Full?
	if(RingBuffer_isFull(rb) == RINGBUFFER_FULL)
	{
		return DRIVER_FAIL;
	}
	// Append the data
	rb->buffer[rb->writeIdx] = data;
	// Increment the write index
	rb->writeIdx = (rb->writeIdx + 1) & (rb->size - 1);

	return DRIVER_SUCCESS;
}

/**
 * @brief Reads a single data element from the Ring Buffer.
 * @param rb Pointer to the `ring_buffer_t` structure
 * @param data Pointer to store the read `ring_buffer_data_t` data element
 * @returns Driver Operation Status:
 * @returns - `DRIVER_SUCCESS`: Data was read successfully from Ring Buffer
 * @returns - `DRIVER_FAIL`: Ring Buffer Empty
 * @details Reads data from the current read index and increments the index using
 * the fast bitwise AND wrapping. The operation fails if the buffer is empty.
 */
__STATIC_FORCEINLINE driver_status_t RingBuffer_Read(ring_buffer_t* const rb, ring_buffer_data_t* const data)
{
	// Ring Buffer Empty?
	if(RingBuffer_isEmpty(rb) == RINGBUFFER_EMPTY)
	{
		return DRIVER_FAIL;
	}
	// Read the data
	*data = rb->buffer[rb->readIdx];
	// Increment the read index
	rb->readIdx = (rb->readIdx + 1) & (rb->size - 1);

	return DRIVER_SUCCESS;
}


/**
 * @brief Peeks at a data element relative to the read index
 * @param rb Pointer to the ring_buffer_t structure.
 * @param data Pointer to store the peeked 8-bit data element.
 * @param offset Positive offset from the read index (0 is the next element to be read).
 * @returns Driver Operation Status:
 * @returns - `DRIVER_SUCCESS`: Data peeked successfully
 * @returns - `DRIVER_FAIL`: Ring Buffer Empty or the `offset` is out of bounds
 * @details Retrieves data from an element at a positive offset from the current read index
 * without modifying the read index or the buffer state.
 */
__STATIC_FORCEINLINE driver_status_t RingBuffer_PeekRead(const ring_buffer_t* const rb, ring_buffer_data_t* const data, const ring_buffer_size_t offset)
{
	// Data Available?
	if (offset >= RingBuffer_Count(rb))
	{
		return DRIVER_FAIL;
	}
	// Calculate the peek index with fast wrapping: (readIdx + offset) & (size - 1)
	const ring_buffer_size_t peekIdx = (rb->readIdx + offset) & (rb->size - 1);
	// Read the data
	*data = rb->buffer[peekIdx];
	return DRIVER_SUCCESS;
}

/**
 * @brief Peeks at a data element relative to the write index (backwards).
 * @ingroup RingBuffer
 * @details Retrieves data from an element at a positive offset *backwards* from the current
 * write index without modifying the write index or the buffer state.
 * @param rb Pointer to the ring_buffer_t structure.
 * @param data Pointer to store the peeked 8-bit data element.
 * @param offset Positive offset backwards from the write index (1 is the last written element).
 * @return driver_status_t:
 * - **DRIVER_SUCCESS** if the data was peeked successfully.
 * - **DRIVER_FAIL** if the buffer is empty or the offset is out of bounds (> count).
 */
__STATIC_FORCEINLINE driver_status_t RingBuffer_PeekWrite(const ring_buffer_t* const rb, ring_buffer_data_t* const data, const ring_buffer_size_t offset)
{
	// Check if the offset is valid (must be > 0 and <= count)
	const ring_buffer_size_t count = RingBuffer_Count(rb);

	if (offset == 0 || offset > count)
	{
		// Out of bounds (0 offset or offset greater than available data)
		return DRIVER_FAIL;
	}
	// Calculate the peek index backwards with fast wrapping: (writeIdx - offset) & (size - 1)
	const ring_buffer_size_t peekIdx = (rb->writeIdx - offset) & (rb->size - 1);
	// Read the data
	*data = rb->buffer[peekIdx];

	return DRIVER_SUCCESS;
}

/**
 * @}
 */ // RingBuffer_API

#endif /* RING_BUFFER_H_ */