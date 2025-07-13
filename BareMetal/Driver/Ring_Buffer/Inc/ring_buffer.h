// Header Guards
#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

// Includes
#include "reg_map.h"
#include <string.h>

// Ring Buffer Structure
typedef struct {
	// Pointer to the buffer
	uint8_t* buffer;
	// Index of the head of the buffer
	uint16_t head;
	// Index of the tail of the buffer
	uint16_t tail;
    // Size of the buffer
    uint16_t size;
} ring_buffer_t;

/**
 * @brief Checks if Ring Buffer is Empty
 * @param ring_buffer Pointer to the ring buffer structure
 * @returns Status of the operation
 * @returns - 0: Ring Buffer is Not Empty
 * @returns - 1: Ring Buffer is Empty  
 */
__STATIC_INLINE__ uint8_t Ring_Buffer_Is_Empty(const ring_buffer_t *ring_buffer) {
    // Check if Ring Buffer is Empty
	return (ring_buffer->head == ring_buffer->tail);
}

/**
 * @brief Checks if Ring Buffer is Full
 * @param ring_buffer Pointer to the ring buffer structure
 * @return Status of the operation
 * @returns - 0: Ring Buffer is Not Full
 * @returns - 1: Ring Buffer is Full
 */
__STATIC_INLINE__ uint8_t Ring_Buffer_Is_Full(const ring_buffer_t *ring_buffer) {
    // Check if Ring Buffer is Full
	return (((ring_buffer->head + 1) & (ring_buffer->size - 1)) == ring_buffer->tail);
}

/**
 * @brief Gets the available spaces currently in the ring buffer
 * @param ring_buff Pointer to the ring buffer structure
 * @returns Available Spaces currently in the ring buffer
 */
__STATIC_INLINE__ uint16_t Ring_Buffer_Available_Space(const ring_buffer_t *ring_buff) {
	// Provides Empty Spaces currently in the ring buffer
    return ((ring_buff->tail - ring_buff->head - 1 + ring_buff->size) & (ring_buff->size - 1));
}

/**
 * @brief Gets the filled spaces currently in the ring buffer
 * @param ring_buff Pointer to the ring buffer structure
 * @return Filled Spaces currently in the ring buffer
 */
__STATIC_INLINE__ uint16_t Ring_Buffer_Filled_Space(const ring_buffer_t* ring_buff) {
	// Provides Filled Spaces currently in the ring buffer
    return ((ring_buff->head - ring_buff->tail + ring_buff->size) & (ring_buff->size - 1));
}

/**
 * @brief Peeks the data at the head of the ring buffer 
 * @param ring_buff Pointer to the ring buffer structure
 * @return Data at the head of the ring buffer
 * @note - It only retrieves the data at the head of the ring buffer
 * @note - The data at the head of the ring buffer is not removed from the buffer
 */
__STATIC_INLINE__ uint8_t Ring_Buffer_Peek_Head(const ring_buffer_t* ring_buff){
	// Peek the data at the head of the ring buffer
	return (ring_buff->buffer[ring_buff->head]);
}

/**
 * @brief Peeks the data at the tail of the ring buffer 
 * @param ring_buff Pointer to the ring buffer structure
 * @return Data at the tail of the ring buffer
 * @note - It only retrieves the data at the tail of the ring buffer
 * @note - The data at the tail of the ring buffer is not removed from the buffer
 */
__STATIC_INLINE__ uint8_t Ring_Buffer_Peek_Tail(const ring_buffer_t* ring_buff){
	// Peek the data at the head of the ring buffer
	return (ring_buff->buffer[ring_buff->tail]);
}

/**
 * @brief Peeks the data at the specified offset from the tail of the ring buffer
 * @param ring_buff Pointer to the ring buffer structure
 * @param position Offset Location from the Tail
 * @return Data at the tail of the ring buffer
 * @note - It only retrieves the data at the tail of the ring buffer
 * @note - The data at the tail of the ring buffer is not removed from the buffer
 */
__STATIC_INLINE__ uint8_t Ring_Buffer_Peek_Tail_Offset(const ring_buffer_t* ring_buff, uint16_t position){
	// Peek the data at the offset location from the tail of the ring buffer
	return (ring_buff->buffer[(ring_buff->tail + position) & (ring_buff->size - 1)]);
}

/**
 * @brief Appends the given data to the ring buffer
 * @param ring_buff Pointer to the ring buffer structure
 * @param src_data Pointer to the source data to be appended
 * @returns Status of the operation
 * @returns - 0: Failure (Not enough space in the ring buffer)
 * @returns - 1: Success
 */
uint8_t Ring_Buffer_Enqueue(ring_buffer_t* ring_buff, uint8_t src_data);

/**
 * @brief Retrieves data from the ring buffer
 * @param ring_buff Pointer to the ring buffer structure
 * @param dst_data Pointer to the destination data where the retrieved data will be stored
 * @returns Status of the operation
 * @returns - 0: Failure (No new data available in the ring buffer)
 * @returns - 1: Success
 */
uint8_t Ring_Buffer_Dequeue(ring_buffer_t* ring_buff, uint8_t* dst_data);

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
uint16_t Ring_Buffer_Enqueue_Multiple(ring_buffer_t* ring_buff, const uint8_t* src_data, uint16_t src_len);

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
uint16_t Ring_Buffer_Dequeue_Multiple(ring_buffer_t* ring_buff, uint8_t* dest_data, uint16_t dest_len);

/**
 * @brief Initializes the ring buffer
 * @param ring_buff Pointer to the ring buffer structure
 * @param buffer Pointer to the buffer where the ring buffer
 * @param size Pointer to the size of the buffer
 * @note - The size must be a power of 2
 * @note - If not, it will be rounded up to the next power of 2
 */
void Ring_Buffer_Config(ring_buffer_t* ring_buff, uint8_t* buffer, uint16_t size);

#endif /* __RING_BUFFER_H__ */