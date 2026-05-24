/**
 * @file	gpio_helper.h
 * @author	Shrey Shah
 * @brief	GPIO Internal Translation and Staging Helper Interface
 * @version	v1.0
 * @date	24-05-2026
 *
 * @details
 * This header defines the GPIO helper layer between GPIO LL and the public
 * GPIO driver. Helper APIs translate driver-facing selectors into raw STM32F1
 * GPIO fields and mutate caller-owned register images. They do not read or
 * write peripheral hardware.
 */

#ifndef GPIO_HELPER_H_
#define GPIO_HELPER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //

#include "gpio_ll.h"

/**
 * @addtogroup GPIO_03_Driver
 * @{
 */

/**
 * @brief	GPIO Helper Translation and Staging APIs
 * @defgroup GPIO_03_Driver_02_Helper GPIO Helper Translation and Staging APIs
 * @ingroup	GPIO_03_Driver
 * @details
 * These APIs own selector translation and staged register-image mutation for
 * the GPIO driver. They may validate translation inputs and return
 * @ref driver_status_t, but they must not touch hardware registers directly.
 * @{
 */

/**
 * @brief Stages one pin's complete CRL/CRH mode/config field in a register image
 * @param[in]		pin				GPIO single-pin mask
 * @param[in]		mode			Driver-facing GPIO mode selector
 * @param[in]		config			Driver-facing GPIO configuration selector
 * @param[in,out]	pCrxRegImage	Caller-owned CRL or CRH image
 * @returns Staging status for the requested pin mode/config field
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin mode/config field was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCrxRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin, @p mode, or @p config is invalid
 */
driver_status_t GPIO_Helper_StagePinModeConfigImage
(
	const gpio_pin_t		pin,
	const gpio_pin_mode_t	mode,
	const gpio_pin_config_t	config,
	uint32_t* const			pCrxRegImage
);

/**
 * @brief Stages one pin's CRL/CRH MODE field in a register image
 * @param[in]		pin				GPIO single-pin mask
 * @param[in]		mode			Driver-facing GPIO mode selector
 * @param[in,out]	pCrxRegImage	Caller-owned CRL or CRH image
 * @returns Staging status for the requested pin MODE field
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin MODE field was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCrxRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin or @p mode is invalid
 */
driver_status_t GPIO_Helper_StagePinModeImage
(
	const gpio_pin_t		pin,
	const gpio_pin_mode_t	mode,
	uint32_t* const			pCrxRegImage
);

/**
 * @brief Stages one pin's CRL/CRH CNF field in a register image
 * @param[in]		pin				GPIO single-pin mask
 * @param[in]		config			Driver-facing GPIO configuration selector
 * @param[in,out]	pCrxRegImage	Caller-owned CRL or CRH image
 * @returns Staging status for the requested pin CNF field
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin CNF field was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCrxRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin or @p config is invalid
 */
driver_status_t GPIO_Helper_StagePinConfigImage
(
	const gpio_pin_t		pin,
	const gpio_pin_config_t	config,
	uint32_t* const			pCrxRegImage
);

/**
 * @brief Stages one pin's reset CRL/CRH field in a register image
 * @param[in]		pin				GPIO single-pin mask
 * @param[in,out]	pCrxRegImage	Caller-owned CRL or CRH image
 * @returns Staging status for the requested pin reset field
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin reset field was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCrxRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin is invalid
 */
driver_status_t GPIO_Helper_StagePinResetConfigImage
(
	const gpio_pin_t	pin,
	uint32_t* const		pCrxRegImage
);

/**
 * @brief Stages one pin's input pull state in an ODR register image
 * @param[in]		pin				GPIO single-pin mask
 * @param[in]		config			Driver-facing GPIO pull configuration selector
 * @param[in,out]	pOdrRegImage	Caller-owned ODR image
 * @returns Staging status for the requested pull state
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pull state was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pOdrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin or @p config is invalid
 */
driver_status_t GPIO_Helper_StagePinPullImage
(
	const gpio_pin_t		pin,
	const gpio_pin_config_t	config,
	uint32_t* const			pOdrRegImage
);

/**
 * @brief Decodes one raw MODE/CNF field and ODR image into driver-facing selectors
 * @param[in]	crxField	Right-aligned raw `CNF[1:0] | MODE[1:0]` field
 * @param[in]	odrRegImage	ODR image used to resolve input pull-up/pull-down state
 * @param[in]	pin			GPIO single-pin mask
 * @param[out]	pMode		Destination for decoded GPIO mode selector
 * @param[out]	pConfig	Destination for decoded GPIO configuration selector
 * @returns Decode status for the requested pin state
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin state was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: Both @p pMode and @p pConfig are `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin or @p crxField is invalid
 */
driver_status_t GPIO_Helper_DecodePinModeConfigField
(
	const gpio_pin_config_bits_t	crxField,
	const uint32_t				odrRegImage,
	const gpio_pin_t			pin,
	gpio_pin_mode_t* const		pMode,
	gpio_pin_config_t* const		pConfig
);

/** @} */ // GPIO_03_Driver_02_Helper
/** @} */ // GPIO_03_Driver

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_HELPER_H_ */
