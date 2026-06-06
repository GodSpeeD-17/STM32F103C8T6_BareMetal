/**
 * @file	gpio_codec.h
 * @author	Shrey Shah
 * @brief	GPIO Selector Codec Interface
 * @version	v1.1
 * @date	30-05-2026
 *
 * @details
 * This header defines the GPIO codec layer between GPIO LL and the public
 * GPIO driver. Codec APIs encode driver-facing selectors into raw STM32F1 GPIO
 * fields, decode raw fields back into driver-facing selectors, and return
 * updated caller-owned register images. They do not read or write peripheral
 * hardware.
 */

#ifndef GPIO_CODEC_H_
#define GPIO_CODEC_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "gpio_defines.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GPIO_03_Driver
 * @{
 */

/**
 * @brief	GPIO Codec Translation, Staging, and Extraction APIs
 * @defgroup GPIO_03_Driver_03_Codec GPIO Codec Translation, Staging, and Extraction APIs
 * @ingroup	GPIO_03_Driver
 * @details
 * These APIs own selector translation and staged register-image mutation for
 * the GPIO driver. They assume the driver already validated public inputs and
 * never touch hardware registers directly.
 * @{
 */

// ==================================================================================================== //
//										GPIO Pin Config/Mode Codecs										//
// ==================================================================================================== //

/**
 * @brief Extracts one complete GPIO config/mode selector pair from CRL/CRH and ODR images
 * @param[in] crxRegImage Caller-owned CRL/CRH image containing the target pin field
 * @param[in] odrRegImage Caller-owned ODR image used to resolve input pull-up/pull-down
 * @param[in] pin GPIO single-pin mask
 * @param[out] pConfig Optional destination for decoded GPIO configuration selector
 * @param[out] pMode Optional destination for decoded GPIO mode selector
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin config/mode selectors were extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pConfig and @p pMode are both `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin is not a single valid pin or extracted raw MODE/CNF field is not decodable
 * @note Codec owns conversion of @p pin to the target register field position.
 */
driver_status_t Codec_GPIO_ExtractPinConfigMode
(
	const reg					crxRegImage,
	const reg					odrRegImage,
	const gpio_pin_t			pin,
	gpio_pin_config_t* const		pConfig,
	gpio_pin_mode_t* const		pMode
);

/**
 * @brief Stages one complete GPIO config/mode selector pair into CRL/CRH and ODR images
 * @param[in] crxRegImage Caller-owned CRL/CRH image before replacement
 * @param[in] odrRegImage Caller-owned ODR image before replacement
 * @param[in] pin GPIO single-pin mask
 * @param[in] config Driver-facing GPIO configuration selector
 * @param[in] mode Driver-facing GPIO mode selector
 * @param[out] pCrxRegImage Destination for the updated CRL/CRH image
 * @param[out] pOdrRegImage Destination for the updated ODR image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: CRL/CRH and ODR images were staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCrxRegImage or @p pOdrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin is not a single valid pin or the config/mode field could not be encoded
 * @note Caller owns validation of @p config, @p mode, and the mode/config
 * compatibility pair. Codec owns conversion of @p pin to the target register
 * field position. The driver layer decides whether the staged ODR delta is
 * applied through ODR, BSRR, or BRR.
 */
driver_status_t Codec_GPIO_StagePinConfigMode
(
	const reg					crxRegImage,
	const reg					odrRegImage,
	const gpio_pin_t			pin,
	const gpio_pin_config_t		config,
	const gpio_pin_mode_t		mode,
	reg* const					pCrxRegImage,
	reg* const					pOdrRegImage
);

// ==================================================================================================== //
//										GPIO Pin Output State Codecs									//
// ==================================================================================================== //

/**
 * @brief Extracts one GPIO output latch state from an ODR image
 * @param[in] odrRegImage Caller-owned ODR image
 * @param[in] pin GPIO single-pin mask
 * @param[out] pPinState Destination for the extracted output latch state
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Output state was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPinState is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin is not a single valid pin
 * @note Writes @ref `DRIVER_STATUS_OFF` when the selected ODR bit is clear and
 * @ref `DRIVER_STATUS_ON` when it is set. Codec owns conversion of @p pin to
 * the target register bit.
 */
driver_status_t Codec_GPIO_ExtractPinOutputState
(
	const reg					odrRegImage,
	const gpio_pin_t			pin,
	driver_status_t* const		pPinState
);

/**
 * @brief Stages one GPIO output state inside an ODR image
 * @param[in] odrRegImage Caller-owned ODR image before replacement
 * @param[in] pin GPIO single-pin mask
 * @param[in] pinState Requested output latch state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Clear the selected ODR bit
 * - @ref `DRIVER_STATUS_ON`: Set the selected ODR bit
 * @param[out] pOdrRegImage Destination for the updated ODR image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: ODR image was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pOdrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin is not a single valid pin or @p pinState is not an accepted state
 * @note Codec owns conversion of @p pin to the target register bit.
 */
driver_status_t Codec_GPIO_StagePinOutputState
(
	const reg					odrRegImage,
	const gpio_pin_t			pin,
	const driver_status_t		pinState,
	reg* const					pOdrRegImage
);

// ==================================================================================================== //
//										GPIO Pin Input State Codecs										//
// ==================================================================================================== //

/**
 * @brief Extracts one GPIO sampled input state from an IDR image
 * @param[in] idrRegImage Caller-owned IDR image
 * @param[in] pin GPIO single-pin mask
 * @param[out] pPinState Destination for the extracted sampled input state
 * Updated Values:
 * - @ref `DRIVER_STATUS_OFF`: Pin is logic LOW
 * - @ref `DRIVER_STATUS_ON`: Pin is logic HIGH
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Input state was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPinState is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin is not a single valid pin
 * @note Writes @ref `DRIVER_STATUS_OFF` when the selected IDR bit is clear and
 * @ref `DRIVER_STATUS_ON` when it is set. Codec owns conversion of @p pin to
 * the target register bit.
 */
driver_status_t Codec_GPIO_ExtractPinInputState
(
	const reg					idrRegImage,
	const gpio_pin_t			pin,
	driver_status_t* const		pPinState
);

// ==================================================================================================== //
//										GPIO Lock State Codecs											//
// ==================================================================================================== //

/**
 * @brief Extracts one GPIO configuration lock bit from an LCKR image
 * @param[in] lckrRegImage Caller-owned LCKR image
 * @param[in] pin GPIO single-pin mask
 * @param[out] pLockState Destination for the extracted per-pin lock bit state
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Per-pin lock state was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pLockState is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin is not a single valid pin
 * @note Writes @ref `DRIVER_STATUS_OFF` when the selected LCK bit is clear and
 * @ref `DRIVER_STATUS_ON` when it is set. Codec owns conversion of @p pin to
 * the target register bit.
 */
driver_status_t Codec_GPIO_ExtractPinLockState
(
	const reg					lckrRegImage,
	const gpio_pin_t			pin,
	driver_status_t* const		pLockState
);

/**
 * @brief Stages one GPIO configuration lock bit inside an LCKR image
 * @param[in] lckrRegImage Caller-owned LCKR image before replacement
 * @param[in] pin GPIO single-pin mask
 * @param[in] lockState Requested per-pin lock bit state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Clear the selected LCK bit
 * - @ref `DRIVER_STATUS_ON`: Set the selected LCK bit
 * @param[out] pLckrRegImage Destination for the updated LCKR image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: LCKR image was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pLckrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin is not a single valid pin or @p lockState is not an accepted state
 * @note Codec owns conversion of @p pin to the target register bit.
 */
driver_status_t Codec_GPIO_StagePinLockState
(
	const reg					lckrRegImage,
	const gpio_pin_t			pin,
	const driver_status_t		lockState,
	reg* const					pLckrRegImage
);

/**
 * @brief Extracts the GPIO lock-key bit from an LCKR image
 * @param[in] lckrRegImage Caller-owned LCKR image
 * @param[out] pLockKeyState Destination for the extracted lock-key bit state
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Lock-key state was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pLockKeyState is `NULL`
 * @note Writes @ref `DRIVER_STATUS_OFF` when `LCKK` is clear and
 * @ref `DRIVER_STATUS_ON` when it is set.
 */
driver_status_t Codec_GPIO_ExtractLockKeyState
(
	const reg					lckrRegImage,
	driver_status_t* const		pLockKeyState
);

/**
 * @brief Stages the GPIO lock-key bit inside an LCKR image
 * @param[in] lckrRegImage Caller-owned LCKR image before replacement
 * @param[in] lockKeyState Requested lock-key bit state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Clear `LCKK`
 * - @ref `DRIVER_STATUS_ON`: Set `LCKK`
 * @param[out] pLckrRegImage Destination for the updated LCKR image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: LCKR image was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pLckrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p lockKeyState is not an accepted state
 * @note The STM32F1 lock-key write/read sequence belongs above Codec. This API
 * only stages the `LCKK` bit in the caller-owned image.
 */
driver_status_t Codec_GPIO_StageLockKeyState
(
	const reg					lckrRegImage,
	const driver_status_t		lockKeyState,
	reg* const					pLckrRegImage
);

/** @} */ // GPIO_03_Driver_03_Codec

/** @} */ // GPIO_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_CODEC_H_ */
