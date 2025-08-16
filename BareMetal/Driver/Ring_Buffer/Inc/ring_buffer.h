// Header Guards
#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

// Includes
#include "ring_buffer_config.h"

/**
 * @brief Appends the given data to the ring buffer
 * @param ring_buff Pointer to the ring buffer structure
 * @param src_data Source data to be appended
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