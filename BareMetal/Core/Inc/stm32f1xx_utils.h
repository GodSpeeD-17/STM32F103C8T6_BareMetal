/**
 * @file stm32f1xx_utils.h
 * @author	Shrey Shah
 * @brief	Basic Utilities for STM32F1xx
 * @version v1.0
 * @date 01-03-2026
 * @defgroup 01_STM32F1xx_Utilities Basic Utilities
 * @ingroup STM32F1xx
 * @details
 * This module provides basic utilities for STM32F1xx series including:
 * - Bit manipulation macros
 * - Driver status codes and assertions
 * - Register operation utilities
 *
 * These utilities are designed to be used across all peripheral drivers and application code.
 * 
 * @details
 *******************************************************************************************************************
 *  Basic Notes:-
 *  YouTube Reference Video: https://youtu.be/zvTd3Zxtiek
 *  `uint32_t` inside every BIT struct because of padding alignment
 *  `volatile` used for ensuring no further optimization by compiler
 *  `: x` indicates only x bit(s) to be used from that 32-bit
 ****************************************************************************************************************
 *                        🔧 Bit Manipulation Built-ins (GCC)
 * -------------------------------------------------------------------------------------
 * | Built-in Function      | Description                                          |
 * |--------------------------|------------------------------------------------------|
 * | __builtin_clz(x)       | Counts leading zeros from MSB (Undefined if x == 0) |
 * | __builtin_ctz(x)       | Counts trailing zeros from LSB (Undefined if x == 0)|
 * | __builtin_popcount(x)  | Counts number of bits set to 1 (Hamming weight)     |
 * | __builtin_parity(x)    | Returns 1 if number of 1-bits is odd, else 0        |
 * | __builtin_ffsl(x)      | Index (1-based) of first bit set (LSB side)         |
 * | __builtin_bswap16(x)   | Swaps byte order for 16-bit integer                  |
 * | __builtin_bswap32(x)   | Swaps byte order for 32-bit integer                  |
 * | __builtin_bswap64(x)   | Swaps byte order for 64-bit integer                  |
 * -------------------------------------------------------------------------------------
 * 
 * @note
 * - All __builtin_* functions are evaluated at compile-time if argument is constant.
 * - __builtin_clz/ctz are undefined if input is zero; guard input accordingly.
 * - These generate single assembly instructions on ARM Cortex-M.  
 */

// Header Guards
#ifndef STM32F1XX_UTILS_H_
#define STM32F1XX_UTILS_H_

// --- C++ Safeguards ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------
#include "stm32f1xx_data_types.h"

// ------------------------------------------------------------------------------------------
// Bit Manipulation Utilities
// ------------------------------------------------------------------------------------------

/**
 * @defgroup 01_STM32F1xx_Utilities_01_Bit Bit Manipulation Utilities
 * @ingroup 01_STM32F1xx_Utilities
 * @{
 */

/** 
 * @brief Provides bit mask for input position
 * @def BIT_MASK
 * @param[in] X Bit position (0-based)
 * @returns Bit mask with only bit at position X set (1 << X)
 * @note Assumes 32-bit width; adjust type if using with different widths
 */
#define BIT_MASK(X)								((uint32_t) (0x01UL << (X)))

/** 
 * @brief Sets bit at `POS`
 * @param[in] POS Bit position
 * @note Assumed 32-bits
 */
#define BIT_SET(POS)							((uint32_t) (0x01UL << (POS)))

/**
 * @brief   Compute peripheral index based on base addresses and peripheral size
 * @addtogroup 01_STM32F1xx_Utilities_01_Bit
 *
 * @details
 * This macro computes the **zero-based peripheral index** (or bit position)
 * of a given peripheral instance by comparing its memory-mapped address
 * with that of a reference instance of the same peripheral family.
 *
 * The computation uses the **known peripheral memory spacing** (in bytes)
 * rather than the structure size (`sizeof()`), ensuring accurate results even
 * when peripheral register blocks do not occupy their entire memory region.
 *
 * It is primarily used to determine **clock-enable bit positions** or
 * **array indices** for peripherals of the same type (e.g., GPIOA–GPIOG,
 * USART1–USART3, TIM2–TIM5, etc.).
 *
 * @note
 * - Performs **pure compile-time address arithmetic** when constant operands are used.
 * - No hardware register access is performed.
 * - Peripheral instances must have equal address spacing in the memory map.
 *
 * @param[in] value   The address (or pointer) of the target peripheral instance  
 *					(e.g., @ref GPIOC, @ref USART2, @ref TIM4)
 * @param[in] base	The address (or pointer) of the reference peripheral instance  
 *					(e.g., @ref GPIOA, @ref USART1, @ref TIM2)
 * @param[in] size	The memory spacing (in bytes) between consecutive instances  
 *					of the same peripheral type  
 *					(e.g., @ref GPIO_PERIPHERAL_SIZE "GPIO_PERIPHERAL_SIZE")
 *
 * @return The **zero-based index** of the target peripheral relative to the base.
 *
 * @pre Both `base` and `value` must belong to peripherals of the same family
 *	  and share the same address spacing.
 *
 * @warning
 * - The result is undefined if `base` and `value` are not aligned to `size`.
 * - Passing an incorrect `size` value may result in invalid peripheral indices.
 *
 * @see @ref GPIO_PERIPHERAL_SIZE for GPIO memory spacing.
 * @see @ref RCC_APB2ENR for clock enable bit positions.
 * @def BIT_POS
 */
#define BIT_POS(value, base, size) \
	((uint32_t)((((uint32_t)(value)) - ((uint32_t)(base))) / (uint32_t)(size)))

/** @} */ // 01_STM32F1xx_Utilities_01_Bit

// ------------------------------------------------------------------------------------------
// Register Operations Utilities
// ------------------------------------------------------------------------------------------

/**
 * @brief		Register Operations Utilities
 * @defgroup	01_STM32F1xx_Utilities_03_RegisterOps Register Operations Utilities
 * @ingroup		01_STM32F1xx_Utilities
 * @{
 */

/**
 * @brief Read a 32-bit memory-mapped register.
 *
 * @param[in]	reg			Pointer to the memory-mapped register.
 * @param[out]	out_value	Pointer to variable receiving the register value.
 *
 * @retval DRIVER_STATUS_SUCCESS			Read completed successfully.
 * @retval DRIVER_STATUS_ERR_INVALID_ARG	One or more arguments are NULL.
 *
 * @note
 * This API does not validate the address range. It assumes `reg` points to valid Memory Mapped IO
 */
driver_status_t	RegOps_Read(volatile uint32_t *reg, uint32_t *out_value);

/**
 * @brief Write a 32-bit memory-mapped register.
 *
 * @param[in]	reg		Pointer to the memory-mapped register.
 * @param[in]	value	Value to write.
 *
 * @returns @ref driver_status_t "Driver Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`:				Operation completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`:	@c reg is NULL.
 */
driver_status_t	RegOps_Write(volatile uint32_t *reg, uint32_t value);

/**
 * @brief Set bits in a 32-bit memory-mapped register (OR operation).
 *
 * @param[in]	reg		Pointer to the memory-mapped register.
 * @param[in]	mask	Bit mask to set.
 *
 * @returns @ref driver_status_t "Driver Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`:				Operation completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`:	@c reg is NULL.
 */
driver_status_t	RegOps_Set(volatile uint32_t *reg, uint32_t mask);

/**
 * @brief Clear bits in a 32-bit memory-mapped register (AND with ~mask).
 *
 * @param[in]	reg		Pointer to the memory-mapped register.
 * @param[in]	mask	Bit mask to clear.
 *
 * @returns @ref driver_status_t "Driver Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`:				Operation completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`:	@c reg is NULL.
 */
driver_status_t	RegOps_Clear(volatile uint32_t *reg, uint32_t mask);

/**
 * @brief Toggle bits in a 32-bit memory-mapped register (XOR operation).
 *
 * @param[in]	reg		Pointer to the memory-mapped register.
 * @param[in]	mask	Bit mask to toggle.
 *
 * @returns @ref driver_status_t "Driver Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`:				Operation completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`:	@c reg is NULL.
 */
driver_status_t	RegOps_Toggle(volatile uint32_t *reg, uint32_t mask);

/**
 * @brief Write a masked field inside a 32-bit register.
 *
 * @details
 * This helper performs: `reg = (reg & ~mask) | (value & mask)`.
 * Use it for writing bitfields where `value` is already aligned to the mask position.
 *
 * @param[in]	reg		Pointer to the memory-mapped register.
 * @param[in]	mask	Field mask (already shifted to position).
 * @param[in]	value	Field value (already shifted to position).
 *
 * @returns @ref driver_status_t "Driver Operation Status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`:				Operation completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`:	@c reg is NULL.
 *
 * @warning
 * Caller must ensure `value` is correctly shifted and does not set bits outside `mask`.
 */
driver_status_t	RegOps_WriteMasked(volatile uint32_t *reg, uint32_t mask, uint32_t value);

/** @} */ // 01_STM32F1xx_Utilities_03_RegisterOps

// --- C++ Safeguards ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_UTILS_H_ */
