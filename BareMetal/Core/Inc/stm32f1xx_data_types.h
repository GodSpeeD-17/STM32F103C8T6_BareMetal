/**
 * @file	stm32f1xx_data_types.h
 * @author	Shrey Shah
 * @brief	STM32F1xx Custom Data Types
 * @version v1.0
 * @date 01-03-2026
 */
#ifndef STM32F1XX_DATA_TYPES_H_
#define STM32F1XX_DATA_TYPES_H_

// --- C++ Safeguards ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// ------------------------------------------------------------------------------------------
// Register Modification Type
// ------------------------------------------------------------------------------------------

/**
 * @brief Read/Write access type
 * 
 * @details
 * - Used for registers that support both read and write operations
 * - Qualifies the register as volatile to prevent compiler optimizations
 * - Ensures each access is performed as specified in code
 * 
 * @note This is the most commonly used type for peripheral registers
 */
typedef volatile uint32_t						_IO;

/**
 * @brief Read-only access type
 * 
 * @details
 * - Used for registers that are read-only (status registers, flags)
 * - Qualifies as volatile to ensure fresh read on each access
 * - Writing to these registers may have undefined behavior
 * 
 * @note Hardware may update these registers asynchronously
 */
typedef volatile const uint32_t					_I;

/**
 * @brief Write-only access type
 * 
 * @details
 * - Used for registers that are write-only (data output, control)
 * - Qualifies as volatile to ensure write is not optimized away
 * - Reading from these registers may return garbage values
 * 
 * @note Common for FIFO buffers and output-only control registers
 */
typedef volatile uint32_t						_O;

// ------------------------------------------------------------------------------------------
// Driver Operation Status Type
// ------------------------------------------------------------------------------------------

/**
 * @brief Driver Operation Status Type
 * @defgroup 01_STM32F1xx_Utilities_03_DriverStatus Driver Status Definitions
 * @ingroup 01_STM32F1xx_Utilities
 * @{
 */

/**
 * @brief Driver status codes enumeration
 * @enum driver_status_t
 * @note Link individual codes using @ref `DRIVER_STATUS_xxx`.
 * 
 * @details
 * Contract:
 *  - Values <= DRIVER_STATUS_ERROR (0) indicate an error.
 *  - DRIVER_STATUS_SUCCESS (1) indicates success.
 *  - Values >= DRIVER_STATUS_OFF (2) indicate non-error states. 
 */
typedef enum _driver_status_t
{
	/** @brief Peripheral or driver is currently executing an operation. */
	DRIVER_STATUS_ERROR_BUSY		=	-6,
	/** @brief Operation requested in an invalid driver or peripheral state. */
	DRIVER_STATUS_ERROR_STATE		=	-5,
	/** @brief Operation timed out waiting for hardware or condition. */
	DRIVER_STATUS_ERROR_TIMEOUT		=	-4,
	/** @brief Operation failed due to a non-specific error. */
	DRIVER_STATUS_ERROR_FAIL		=	-3,
	/** @brief An input parameter was invalid or out of range. */
	DRIVER_STATUS_ERROR_INVALID_ARG	=	-2,
	/** @brief Operation failed due to a null pointer. */
	DRIVER_STATUS_ERROR_NULL_PTR	=	-1,
	/** @brief Generic error (baseline error code). */
	DRIVER_STATUS_ERROR				=	 0,
	/** @brief Operation completed successfully. */
	DRIVER_STATUS_SUCCESS			=	 1,
	/** @brief Target state: Disabled or turned OFF. */
	DRIVER_STATUS_OFF				=	 2,
	/** @brief Target state: Enabled or turned ON. */
	DRIVER_STATUS_ON				=	 3,
	/** @brief Peripheral or driver is configured and ready for an operation. */
	DRIVER_STATUS_READY				=	 4
} driver_status_t;

/**
 * @brief Asserts Driver Status
 * @param[in] expr @ref driver_status_t "Expression to evaluate"
 * @returns Returns the evaluated status
 * @retval - Input Expression if not @ref `DRIVER_STATUS_SUCCESS`
 */
#define ASSERT_DRIVER_STATUS(expr)				\
do												\
{												\
	driver_status_t _st = (expr);				\
	if (_st != DRIVER_STATUS_SUCCESS)			\
	{											\
		return _st;								\
	}									 		\
} while (0)

/** 
 * @brief Calculates the number of elements in an array
 * @def ARRAY_SIZE
 * @param[in] arr The array
 * @returns Number of elements in the array
 */
#define ARRAY_SIZE(arr)							(sizeof(arr) / sizeof((arr)[0]))

/** @} */ // 01_STM32F1xx_Utilities_03_DriverStatus

/**
 * @brief RCC Shared Scalar Aliases
 * @defgroup RCC_03_Driver_01_DataTypes RCC Driver Data Types
 * @ingroup RCC_03_Driver
 * @details
 * This group owns the scalar aliases shared by the RCC driver stack.
 *
 * Dependency route:
 * - `stm32f1xx_data_types.h` defines portable scalar aliases.
 * - `stm32f1xx_rcc.h` defines the RCC register model and bit fields.
 * - `stm32f1xx.h` publishes board-level RCC operating limits.
 * - `rcc_ll.h` and `rcc_ll.c` implement register-near control.
 * - `rcc.h` and `rcc.c` implement policy, validation, and orchestration.
 *
 * Keeping these aliases here allows every RCC layer to share the same type
 * names without introducing circular header dependencies.
 * @{
 */

/** @brief RCC bus selector type @typedef rcc_bus_t */
typedef uint8_t									rcc_bus_t;
/** @brief Bus prescaler divider selector type @typedef rcc_bus_prescaler_t */
typedef uint8_t									rcc_bus_prescaler_t;
/** @brief Component prescaler selector type @typedef rcc_component_prescaler_t */
typedef uint8_t									rcc_component_prescaler_t;
/** @brief Flash latency type @typedef rcc_flash_latency_t */
typedef uint8_t									rcc_flash_latency_t;
/** @brief Flash prefetch selector type @typedef rcc_flash_prefetch_t */
typedef uint8_t									rcc_flash_prefetch_t;
/** @brief System clock source selector type @typedef rcc_system_clock_t */
typedef uint8_t									rcc_system_clock_t;
/** @brief PLL source selector type @typedef rcc_pll_src_t */
typedef uint8_t									rcc_pll_src_t;
/** @brief PLL input prescaler selector type @typedef rcc_pll_src_psc_t */
typedef uint8_t									rcc_pll_src_psc_t;
/** @brief PLL multiplication factor type @typedef rcc_pll_mul_t */
typedef uint8_t									rcc_pll_mul_t;
/** @brief RCC frequency unit type @typedef rcc_freq_t */
typedef uint32_t								rcc_freq_t;

/** @} */ // RCC_03_Driver_01_DataTypes

// --- C++ Safeguards ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_DATA_TYPES_H_ */
