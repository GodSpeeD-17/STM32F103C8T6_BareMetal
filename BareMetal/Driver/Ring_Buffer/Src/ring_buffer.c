/**
 * @file ring_buffer.c
 * @author Shrey Shah
 * @brief Implementation of Ring Buffer
 * @version 1.0
 * @date 06-07-2025
 * 
 * Details about the ring buffer implementation:
 * - Circular buffer implementation
 * - Supports enqueue and dequeue operations
 * - Full Condition: Head index is one position before the tail index
 * - Empty Condition: Head index is equal to the tail index 
 */

// Includes
#include "ring_buffer.h"

/**
 * @brief Appends the given data to the ring buffer
 * @param ring_buff Pointer to the ring buffer structure
 * @param src_data Source data to be appended
 * @returns Status of the operation
 * @returns - 0x00: Failure (Not enough space in the ring buffer)
 * @returns - 0x01: Success
 */
uint8_t Ring_Buffer_Enqueue(ring_buffer_t* ring_buff, uint8_t src_data){
	// Ring Buffer is full
	if(Ring_Buffer_Is_Full(ring_buff) != 0x01){
		// No space available in the ring buffer
		return 0x00;
	}
	// Store the data in the buffer at the head index
	ring_buff->buffer[ring_buff->head] = src_data;
	// Update the head index
	ring_buff->head = ((ring_buff->head + 1) & (ring_buff->size - 1));
	// Success
	return 0x01;
}

/**
 * @brief Retrieves data from the ring buffer
 * @param ring_buff Pointer to the ring buffer structure
 * @param dst_data Pointer to the destination data where the retrieved data will be stored
 * @returns Status of the operation
 * @returns - 0: Failure (No new data available in the ring buffer)
 * @returns - 1: Success
 */
uint8_t Ring_Buffer_Dequeue(ring_buffer_t* ring_buff, uint8_t* dst_data){
	// Buffer is Empty
	if(Ring_Buffer_Is_Empty(ring_buff) != 0x01) {
		// No new data available in the ring buffer
		return 0x00;
	}
	// Retrieve the data from the buffer at the tail index
	*dst_data = ring_buff->buffer[ring_buff->tail];
	// Update the tail index
	ring_buff->tail = ((ring_buff->tail + 1) & (ring_buff->size - 1));
	// Success
	return 0x01;
}

/**
 * @brief Enqueues multiple bytes of data into the ring buffer
 * @param ring_buff Pointer to the ring buffer structure
 * @param src_data Pointer to the source data
 * @param src_len Source data length
 * @return Status of the operation
 * @return - 0x01: Success (All bytes enqueued successfully)
 * @return - 0xFFFF: Failure (Not enough space in the ring buffer) 
 * @return - `index`: Failure (Enqueue operation failed for one or more bytes from the returned index)
 */
uint16_t Ring_Buffer_Enqueue_Multiple(ring_buffer_t* ring_buff, const uint8_t* src_data, uint16_t src_len){
	// Check if there is enough space in the ring buffer
	if(Ring_Buffer_Available_Space(ring_buff) < src_len){
		// Not enough space in the ring buffer
		return 0xFFFF;
	}
	// Copy the data from the source to the ring buffer
	for(uint16_t index = 0; index < src_len; index++){
		if(Ring_Buffer_Enqueue(ring_buff, src_data[index]) != 0x01){
			// If enqueue fails, return index for failure
			return index;
		}
	}
	// Success
	return 0x0001;
}

/**
 * @brief Dequeues multiple bytes of data from the ring buffer
 * @param ring_buff Pointer to the ring buffer structure
 * @param dest_data Pointer to the destination buffer to store dequeued data
 * @param dest_len Number of bytes to dequeue
 * @return Status of the operation
 * @return - 0x01: Success (All bytes dequeued successfully)
 * @return - 0xFFFF: Failure (Not enough data in the ring buffer)
 * @return - `index`: Failure (Dequeue operation failed at this index)
 */
uint16_t Ring_Buffer_Dequeue_Multiple(ring_buffer_t* ring_buff, uint8_t* dest_data, uint16_t dest_len){
	// Check if there is enough data to dequeue
	if (Ring_Buffer_Filled_Space(ring_buff) < dest_len) {
		// Not enough data in the ring buffer
		return 0xFFFF;
	}
	// Copy data from the ring buffer to the destination buffer
	for (uint16_t index = 0; index < dest_len; index++) {
		if (!Ring_Buffer_Dequeue(ring_buff, &dest_data[index])) {
			// If dequeue fails, return index where it failed
			return index;
		}
	}
	// Success
	return 0x0001;
}

/**
 * @brief Initializes the ring buffer
 * @param ring_buff Pointer to the ring buffer structure
 * @param buffer Pointer to the buffer where the ring buffer
 * @param size Pointer to the size of the buffer
 * @note - The size must be a power of 2
 * @note - If not, it will be rounded up to the next power of 2
 */
void Ring_Buffer_Config(ring_buffer_t* ring_buff, uint8_t* buffer, uint16_t size){
	// Initialize the ring buffer structure
	ring_buff->buffer = buffer;
	ring_buff->head = 0;
	ring_buff->tail = 0;
	// Ensure the size is a power of 2
	if (!Is_Power_Of_2(size)) {
		size = Round_Up_Power_of_2(size);
	}
	// Update the size of the ring buffer & provide it back to user
	ring_buff->size = size;
}
