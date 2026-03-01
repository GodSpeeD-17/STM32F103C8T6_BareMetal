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
// Driver Operation Status Type
// ------------------------------------------------------------------------------------------

/**
 * @brief Driver Operation Status Type
 * @defgroup 01_STM32F1xx_Utilities_02_DriverStatus Driver Status Definitions
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
#define DRIVER_RETURN_IF_NOT_SUCCESS(expr)		\
do												\
{												\
	driver_status_t _st = (expr);				\
	if (_st != DRIVER_STATUS_SUCCESS)			\
	{											\
		return _st;								\
	}									 		\
} while (0)

/** @} */ // 01_STM32F1xx_Utilities_02_DriverStatus

// --- C++ Safeguards ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_DATA_TYPES_H_ */
