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
 * @defgroup GPIO_03_Driver_02_Codec GPIO Codec Translation, Staging, and Extraction APIs
 * @ingroup	GPIO_03_Driver
 * @details
 * These APIs own selector translation and staged register-image mutation for
 * the GPIO driver. They assume the driver already validated public inputs and
 * never touch hardware registers directly.
 * @{
 */

/**
 * @brief Checks whether a GPIO pin index maps to the CRH register image
 * @param[in] pinIndex Zero-based GPIO pin index
 * @returns CRH target state for @p pinIndex
 * @retval - @ref `DRIVER_STATUS_OFF`: @p pinIndex maps to `CRL`
 * @retval - @ref `DRIVER_STATUS_ON`: @p pinIndex maps to `CRH`
 * @note Caller owns pin-index validation before using this helper.
 */
__STATIC_FORCEINLINE driver_status_t Codec_GPIO_PinIndexTargetsCRH(const gpio_pin_index_t pinIndex)
{
	return (pinIndex >= ((gpio_pin_index_t) (GPIO_PORT_PIN_COUNT / 2U))) ? DRIVER_STATUS_ON : DRIVER_STATUS_OFF;
}

/**
 * @brief Stages one complete GPIO config/mode selector pair into CRL/CRH and ODR images
 * @param[in] crxRegImage Caller-owned CRL/CRH image before replacement
 * @param[in] odrRegImage Caller-owned ODR image before replacement
 * @param[in] pinIndex Zero-based GPIO pin index
 * @param[in] config Driver-facing GPIO configuration selector
 * @param[in] mode Driver-facing GPIO mode selector
 * @param[out] pCrxRegImage Destination for the updated CRL/CRH image
 * @param[out] pOdrRegImage Destination for the updated ODR image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: CRL/CRH and ODR images were staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCrxRegImage or @p pOdrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The config/mode field could not be encoded
 * @note Caller owns validation of @p pinIndex, @p config, @p mode, and the
 * mode/config compatibility pair. The ODR image is changed only for
 * @ref `GPIO_PIN_CONFIG_INPUT_PULL_DOWN` and @ref `GPIO_PIN_CONFIG_INPUT_PULL_UP`
 * when @p mode is @ref `GPIO_PIN_MODE_INPUT`.
 */
driver_status_t Codec_GPIO_StagePinConfigMode
(
	const reg					crxRegImage,
	const reg					odrRegImage,
	const gpio_pin_index_t		pinIndex,
	const gpio_pin_config_t		config,
	const gpio_pin_mode_t		mode,
	reg* const					pCrxRegImage,
	reg* const					pOdrRegImage
);

/**
 * @brief Extracts one complete GPIO config/mode selector pair from CRL/CRH and ODR images
 * @param[in] crxRegImage Caller-owned CRL/CRH image containing the target pin field
 * @param[in] odrRegImage Caller-owned ODR image used to resolve input pull-up/pull-down
 * @param[in] pinIndex Zero-based GPIO pin index
 * @param[out] pConfig Optional destination for decoded GPIO configuration selector
 * @param[out] pMode Optional destination for decoded GPIO mode selector
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin config/mode selectors were extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pConfig and @p pMode are both `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Extracted raw MODE/CNF field is not decodable
 * @note Caller owns validation that @p pinIndex is inside the supported GPIO pin range.
 */
driver_status_t Codec_GPIO_ExtractPinConfigMode
(
	const reg					crxRegImage,
	const reg					odrRegImage,
	const gpio_pin_index_t		pinIndex,
	gpio_pin_config_t* const	pConfig,
	gpio_pin_mode_t* const		pMode
);

/**
 * @brief Stages one GPIO output state inside an ODR image
 * @param[in] odrRegImage Caller-owned ODR image before replacement
 * @param[in] pinIndex Zero-based GPIO pin index
 * @param[in] pinState Requested output latch state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Clear the selected ODR bit
 * - @ref `DRIVER_STATUS_ON`: Set the selected ODR bit
 * @param[out] pOdrRegImage Destination for the updated ODR image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: ODR image was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pOdrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pinState is not an accepted state
 * @note Caller owns validation that @p pinIndex is inside the supported GPIO pin range.
 */
driver_status_t Codec_GPIO_StagePinOutputState
(
	const reg					odrRegImage,
	const gpio_pin_index_t		pinIndex,
	const driver_status_t		pinState,
	reg* const					pOdrRegImage
);

/**
 * @brief Extracts one GPIO output latch state from an ODR image
 * @param[in] odrRegImage Caller-owned ODR image
 * @param[in] pinIndex Zero-based GPIO pin index
 * @param[out] pPinState Destination for the extracted output latch state
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Output state was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPinState is `NULL`
 * @note Writes @ref `DRIVER_STATUS_OFF` when the selected ODR bit is clear and
 * @ref `DRIVER_STATUS_ON` when it is set. Caller owns validation that
 * @p pinIndex is inside the supported GPIO pin range.
 */
driver_status_t Codec_GPIO_ExtractPinOutputState
(
	const reg					odrRegImage,
	const gpio_pin_index_t		pinIndex,
	driver_status_t* const		pPinState
);

/**
 * @brief Extracts one GPIO sampled input state from an IDR image
 * @param[in] idrRegImage Caller-owned IDR image
 * @param[in] pinIndex Zero-based GPIO pin index
 * @param[out] pPinState Destination for the extracted sampled input state
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Input state was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPinState is `NULL`
 * @note Writes @ref `DRIVER_STATUS_OFF` when the selected IDR bit is clear and
 * @ref `DRIVER_STATUS_ON` when it is set. Caller owns validation that
 * @p pinIndex is inside the supported GPIO pin range.
 */
driver_status_t Codec_GPIO_ExtractPinInputState
(
	const reg					idrRegImage,
	const gpio_pin_index_t		pinIndex,
	driver_status_t* const		pPinState
);

/**
 * @brief Stages one GPIO configuration lock bit inside an LCKR image
 * @param[in] lckrRegImage Caller-owned LCKR image before replacement
 * @param[in] pinIndex Zero-based GPIO pin index
 * @param[in] lockState Requested per-pin lock bit state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Clear the selected LCK bit
 * - @ref `DRIVER_STATUS_ON`: Set the selected LCK bit
 * @param[out] pLckrRegImage Destination for the updated LCKR image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: LCKR image was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pLckrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p lockState is not an accepted state
 * @note Caller owns validation that @p pinIndex is inside the supported GPIO pin range.
 */
driver_status_t Codec_GPIO_StagePinLockState
(
	const reg					lckrRegImage,
	const gpio_pin_index_t		pinIndex,
	const driver_status_t		lockState,
	reg* const					pLckrRegImage
);

/**
 * @brief Extracts one GPIO configuration lock bit from an LCKR image
 * @param[in] lckrRegImage Caller-owned LCKR image
 * @param[in] pinIndex Zero-based GPIO pin index
 * @param[out] pLockState Destination for the extracted per-pin lock bit state
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Per-pin lock state was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pLockState is `NULL`
 * @note Writes @ref `DRIVER_STATUS_OFF` when the selected LCK bit is clear and
 * @ref `DRIVER_STATUS_ON` when it is set. Caller owns validation that
 * @p pinIndex is inside the supported GPIO pin range.
 */
driver_status_t Codec_GPIO_ExtractPinLockState
(
	const reg					lckrRegImage,
	const gpio_pin_index_t		pinIndex,
	driver_status_t* const		pLockState
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

/** @} */ // GPIO_03_Driver_02_Codec

/** @} */ // GPIO_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_CODEC_H_ */
