/**
 * @file	rcc_codec.h
 * @author	Shrey Shah
 * @brief	Declares pure RCC selector and field transformations
 * @version	v2.1
 * @date	23-08-2026
 *
 * @details
 * @section RCC_CODEC_H_HIERARCHY Hierarchy
 * - Position: Layer 2 RCC pure transformation layer
 * - Used by: Layer 3 RCC Driver implementation
 * - Uses: RCC selector definitions and Core-owned raw RCC field definitions
 *
 * @section RCC_CODEC_H_RESPONSIBILITY Responsibility
 * Codec APIs encode configuration selectors into raw STM32F1 fields, decode
 * raw fields into semantic selectors, and resolve prescaler selectors into
 * arithmetic dividers.
 *
 * @section RCC_CODEC_H_BOUNDARY Dependency Boundary
 * This layer has no peripheral pointer, volatile I/O, sequencing, timeout,
 * cache, or application policy. It never includes `rcc.h` or `rcc_ll.h` and
 * publishes an output only after validating its caller-owned destination.
 */

// Header Guard
#ifndef RCC_CODEC_H_
#define RCC_CODEC_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "rcc_defines.h"
#include "stm32f1xx_rcc.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup RCC_03_Driver
 * @{
 */

/**
 * @brief RCC Codec Selector Translation APIs
 * @defgroup RCC_03_Driver_08_Codec RCC Codec Selector Translation APIs
 * @ingroup RCC_03_Driver
 * @details
 * These APIs own selector-to-field encoding, field-to-selector decoding, and
 * prescaler-selector-to-divider resolution for the RCC driver. They assume
 * the driver layer owns public validation, hardware register reads/writes,
 * sequencing, and status reporting.
 *
 * @note Encode/decode functions never dereference a peripheral instance and
 * never perform volatile I/O; they only translate between the driver-facing
 * selector vocabulary and the raw hardware field values from
 * @ref stm32f1xx_rcc.h.
 * @see @ref RCC_Peripheral_Guide "STM32F103C8T6 RCC Architecture"
 * @{
 */

// ==================================================================================================== //
// RCC System Clock Source Codec
// ==================================================================================================== //

/**
 * @brief Encodes a system clock source selector into its `RCC_CFGR_SW` field
 * @param[in] source System clock source selector to encode
 * Accepted values:
 * - @ref `RCC_SYS_CLK_HSI`: Encodes to `RCC_CFGR_SW_HSI`
 * - @ref `RCC_SYS_CLK_HSE`: Encodes to `RCC_CFGR_SW_HSE`
 * - @ref `RCC_SYS_CLK_PLL`: Encodes to `RCC_CFGR_SW_PLL`
 * @param[out] pField Destination for the encoded `RCC_CFGR_SW` field value
 * Expected values:
 * - Non-`NULL`: Encoded field is published only after @p source is validated
 * @returns @ref driver_status_t "System clock source encode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p source was encoded successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pField is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p source is not a supported selector
 */
driver_status_t Codec_RCC_EncodeSystemClockSource(const rcc_system_clock_t source, reg* const pField);

/**
 * @brief Decodes an `RCC_CFGR_SWS` status field into a system clock source selector
 * @param[in] statusField Raw `RCC_CFGR_SWS` hardware status field to decode
 * Accepted values:
 * - Any @ref reg image; an unrecognized field uses the documented reset-state fallback
 * @param[out] pSource Destination for the decoded system clock source selector
 * Expected values:
 * - @ref `RCC_SYS_CLK_HSI`: Decoded from `RCC_CFGR_SWS_HSI` or any unrecognized field
 * - @ref `RCC_SYS_CLK_HSE`: Decoded from `RCC_CFGR_SWS_HSE`
 * - @ref `RCC_SYS_CLK_PLL`: Decoded from `RCC_CFGR_SWS_PLL`
 * @returns @ref driver_status_t "System clock status decode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p statusField was decoded successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSource is `NULL`
 * @note An unrecognized @p statusField decodes to @ref `RCC_SYS_CLK_HSI` and still
 * returns @ref `DRIVER_STATUS_SUCCESS`, matching the reset-state hardware default.
 */
driver_status_t Codec_RCC_DecodeSystemClockSource(const reg statusField, rcc_system_clock_t* const pSource);

// ==================================================================================================== //
// RCC PLL Field Codec
// ==================================================================================================== //

/**
 * @brief Encodes a PLL source selector into its `RCC_CFGR_PLLSRC` field
 * @param[in] source PLL source selector to encode
 * Accepted values:
 * - @ref `RCC_PLL_SRC_HSI`: Encodes to `RCC_CFGR_PLLSRC_HSI_DIV2`
 * - @ref `RCC_PLL_SRC_HSE`: Encodes to `RCC_CFGR_PLLSRC_HSE`
 * @param[out] pField Destination for the encoded `RCC_CFGR_PLLSRC` field value
 * Expected values:
 * - Non-`NULL`: Encoded field is published only after @p source is validated
 * @returns @ref driver_status_t "PLL source encode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p source was encoded successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pField is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p source is not a supported selector
 */
driver_status_t Codec_RCC_EncodePLLSource(const rcc_pll_src_t source, reg* const pField);

/**
 * @brief Encodes an HSE PLL input divider selector into its `RCC_CFGR_PLLXTPRE` field
 * @param[in] divider HSE PLL input divider selector to encode
 * Accepted values:
 * - @ref `RCC_PLL_SRC_HSE_DIV_1`: Encodes to `RCC_CFGR_PLLXTPRE_HSE`
 * - @ref `RCC_PLL_SRC_HSE_DIV_2`: Encodes to `RCC_CFGR_PLLXTPRE_HSE_DIV2`
 * @param[out] pField Destination for the encoded `RCC_CFGR_PLLXTPRE` field value
 * Expected values:
 * - Non-`NULL`: Encoded field is published only after @p divider is validated
 * @returns @ref driver_status_t "PLL HSE divider encode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p divider was encoded successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pField is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p divider is not a supported selector
 */
driver_status_t Codec_RCC_EncodePLLHSEDivider(const rcc_pll_src_psc_t divider, reg* const pField);

/**
 * @brief Encodes a PLL multiplication factor into its `RCC_CFGR_PLLMUL` field
 * @param[in] multiplier PLL multiplication factor to encode
 * Accepted values:
 * - @ref `RCC_PLL_MUL_2`
 * - @ref `RCC_PLL_MUL_3`
 * - @ref `RCC_PLL_MUL_4`
 * - @ref `RCC_PLL_MUL_5`
 * - @ref `RCC_PLL_MUL_6`
 * - @ref `RCC_PLL_MUL_7`
 * - @ref `RCC_PLL_MUL_8`
 * - @ref `RCC_PLL_MUL_9`
 * - @ref `RCC_PLL_MUL_10`
 * - @ref `RCC_PLL_MUL_11`
 * - @ref `RCC_PLL_MUL_12`
 * - @ref `RCC_PLL_MUL_13`
 * - @ref `RCC_PLL_MUL_14`
 * - @ref `RCC_PLL_MUL_15`
 * - @ref `RCC_PLL_MUL_16`
 * @param[out] pField Destination for the encoded `RCC_CFGR_PLLMUL` field value
 * Expected values:
 * - Non-`NULL`: Encoded field is published only after @p multiplier is validated
 * @returns @ref driver_status_t "PLL multiplier encode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p multiplier was encoded successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pField is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p multiplier is outside `RCC_PLL_MUL_2..RCC_PLL_MUL_16`
 */
driver_status_t Codec_RCC_EncodePLLMultiplier(const rcc_pll_mul_t multiplier, reg* const pField);

// ==================================================================================================== //
// RCC Bus Prescaler Codec
// ==================================================================================================== //

/**
 * @brief Encodes an AHB prescaler selector into its `RCC_CFGR_HPRE` field
 * @param[in] selector AHB prescaler selector to encode
 * Accepted values:
 * - @ref `RCC_AHB_DIV_1`
 * - @ref `RCC_AHB_DIV_2`
 * - @ref `RCC_AHB_DIV_4`
 * - @ref `RCC_AHB_DIV_8`
 * - @ref `RCC_AHB_DIV_16`
 * - @ref `RCC_AHB_DIV_64`
 * - @ref `RCC_AHB_DIV_128`
 * - @ref `RCC_AHB_DIV_256`
 * - @ref `RCC_AHB_DIV_512`
 * @param[out] pField Destination for the encoded `RCC_CFGR_HPRE` field value
 * Expected values:
 * - Non-`NULL`: Encoded field is published only after @p selector is validated
 * @returns @ref driver_status_t "AHB prescaler encode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p selector was encoded successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pField is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p selector is not a supported selector
 */
driver_status_t Codec_RCC_EncodeAHBPrescaler(const rcc_bus_prescaler_t selector, reg* const pField);

/**
 * @brief Decodes an `RCC_CFGR_HPRE` field into an AHB prescaler selector
 * @param[in] field Raw `RCC_CFGR_HPRE` hardware field to decode
 * Accepted values:
 * - Any @ref reg image; an unrecognized field uses the documented reset-state fallback
 * @param[out] pSelector Destination for the decoded AHB prescaler selector
 * Expected values:
 * - @ref `RCC_AHB_DIV_1`: Decoded from divide-by-one or any unrecognized field
 * - @ref `RCC_AHB_DIV_2`
 * - @ref `RCC_AHB_DIV_4`
 * - @ref `RCC_AHB_DIV_8`
 * - @ref `RCC_AHB_DIV_16`
 * - @ref `RCC_AHB_DIV_64`
 * - @ref `RCC_AHB_DIV_128`
 * - @ref `RCC_AHB_DIV_256`
 * - @ref `RCC_AHB_DIV_512`
 * @returns @ref driver_status_t "AHB prescaler decode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p field was decoded successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSelector is `NULL`
 * @note An unrecognized @p field decodes to @ref `RCC_AHB_DIV_1` and still returns
 * @ref `DRIVER_STATUS_SUCCESS`, matching the reset-state hardware default.
 */
driver_status_t Codec_RCC_DecodeAHBPrescaler(const reg field, rcc_bus_prescaler_t* const pSelector);

/**
 * @brief Encodes an APB1 prescaler selector into its `RCC_CFGR_PPRE1` field
 * @param[in] selector APB1 prescaler selector to encode
 * Accepted values:
 * - @ref `RCC_APB1_DIV_1`
 * - @ref `RCC_APB1_DIV_2`
 * - @ref `RCC_APB1_DIV_4`
 * - @ref `RCC_APB1_DIV_8`
 * - @ref `RCC_APB1_DIV_16`
 * @param[out] pField Destination for the encoded `RCC_CFGR_PPRE1` field value
 * Expected values:
 * - Non-`NULL`: Encoded field is published only after @p selector is validated
 * @returns @ref driver_status_t "APB1 prescaler encode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p selector was encoded successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pField is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p selector is not a supported selector
 */
driver_status_t Codec_RCC_EncodeAPB1Prescaler(const rcc_bus_prescaler_t selector, reg* const pField);

/**
 * @brief Decodes an `RCC_CFGR_PPRE1` field into an APB1 prescaler selector
 * @param[in] field Raw `RCC_CFGR_PPRE1` hardware field to decode
 * Accepted values:
 * - Any @ref reg image; an unrecognized field uses the documented reset-state fallback
 * @param[out] pSelector Destination for the decoded APB1 prescaler selector
 * Expected values:
 * - @ref `RCC_APB1_DIV_1`: Decoded from divide-by-one or any unrecognized field
 * - @ref `RCC_APB1_DIV_2`
 * - @ref `RCC_APB1_DIV_4`
 * - @ref `RCC_APB1_DIV_8`
 * - @ref `RCC_APB1_DIV_16`
 * @returns @ref driver_status_t "APB1 prescaler decode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p field was decoded successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSelector is `NULL`
 * @note An unrecognized @p field decodes to @ref `RCC_APB1_DIV_1` and still returns
 * @ref `DRIVER_STATUS_SUCCESS`, matching the reset-state hardware default.
 */
driver_status_t Codec_RCC_DecodeAPB1Prescaler(const reg field, rcc_bus_prescaler_t* const pSelector);

/**
 * @brief Encodes an APB2 prescaler selector into its `RCC_CFGR_PPRE2` field
 * @param[in] selector APB2 prescaler selector to encode
 * Accepted values:
 * - @ref `RCC_APB2_DIV_1`
 * - @ref `RCC_APB2_DIV_2`
 * - @ref `RCC_APB2_DIV_4`
 * - @ref `RCC_APB2_DIV_8`
 * - @ref `RCC_APB2_DIV_16`
 * @param[out] pField Destination for the encoded `RCC_CFGR_PPRE2` field value
 * Expected values:
 * - Non-`NULL`: Encoded field is published only after @p selector is validated
 * @returns @ref driver_status_t "APB2 prescaler encode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p selector was encoded successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pField is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p selector is not a supported selector
 */
driver_status_t Codec_RCC_EncodeAPB2Prescaler(const rcc_bus_prescaler_t selector, reg* const pField);

/**
 * @brief Decodes an `RCC_CFGR_PPRE2` field into an APB2 prescaler selector
 * @param[in] field Raw `RCC_CFGR_PPRE2` hardware field to decode
 * Accepted values:
 * - Any @ref reg image; an unrecognized field uses the documented reset-state fallback
 * @param[out] pSelector Destination for the decoded APB2 prescaler selector
 * Expected values:
 * - @ref `RCC_APB2_DIV_1`: Decoded from divide-by-one or any unrecognized field
 * - @ref `RCC_APB2_DIV_2`
 * - @ref `RCC_APB2_DIV_4`
 * - @ref `RCC_APB2_DIV_8`
 * - @ref `RCC_APB2_DIV_16`
 * @returns @ref driver_status_t "APB2 prescaler decode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p field was decoded successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSelector is `NULL`
 * @note An unrecognized @p field decodes to @ref `RCC_APB2_DIV_1` and still returns
 * @ref `DRIVER_STATUS_SUCCESS`, matching the reset-state hardware default.
 */
driver_status_t Codec_RCC_DecodeAPB2Prescaler(const reg field, rcc_bus_prescaler_t* const pSelector);

// ==================================================================================================== //
// RCC Component Prescaler Codec
// ==================================================================================================== //

/**
 * @brief Encodes an ADC prescaler selector into its `RCC_CFGR_ADCPRE` field
 * @param[in] selector ADC prescaler selector to encode
 * Accepted values:
 * - @ref `RCC_ADC_DIV_2`
 * - @ref `RCC_ADC_DIV_4`
 * - @ref `RCC_ADC_DIV_6`
 * - @ref `RCC_ADC_DIV_8`
 * @param[out] pField Destination for the encoded `RCC_CFGR_ADCPRE` field value
 * Expected values:
 * - Non-`NULL`: Encoded field is published only after @p selector is validated
 * @returns @ref driver_status_t "ADC prescaler encode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p selector was encoded successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pField is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p selector is not a supported selector
 */
driver_status_t Codec_RCC_EncodeADCPrescaler(const rcc_component_prescaler_t selector, reg* const pField);

/**
 * @brief Decodes an `RCC_CFGR_ADCPRE` field into an ADC prescaler selector
 * @param[in] field Raw `RCC_CFGR_ADCPRE` hardware field to decode
 * Accepted values:
 * - Any @ref reg image; an unrecognized field uses the documented reset-state fallback
 * @param[out] pSelector Destination for the decoded ADC prescaler selector
 * Expected values:
 * - @ref `RCC_ADC_DIV_2`: Decoded from divide-by-two or any unrecognized field
 * - @ref `RCC_ADC_DIV_4`
 * - @ref `RCC_ADC_DIV_6`
 * - @ref `RCC_ADC_DIV_8`
 * @returns @ref driver_status_t "ADC prescaler decode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p field was decoded successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSelector is `NULL`
 * @note An unrecognized @p field decodes to @ref `RCC_ADC_DIV_2` and still returns
 * @ref `DRIVER_STATUS_SUCCESS`, matching the reset-state hardware default.
 */
driver_status_t Codec_RCC_DecodeADCPrescaler(const reg field, rcc_component_prescaler_t* const pSelector);

/**
 * @brief Encodes a USB prescaler selector into its `RCC_CFGR_USBPRE` field
 * @param[in] selector USB prescaler selector to encode
 * Accepted values:
 * - @ref `RCC_USB_DIV_1_5`: Encodes to `RCC_CFGR_USBPRE_DIV1_5`
 * - @ref `RCC_USB_DIV_1`: Encodes to `RCC_CFGR_USBPRE_DIRECT`
 * @param[out] pField Destination for the encoded `RCC_CFGR_USBPRE` field value
 * Expected values:
 * - Non-`NULL`: Encoded field is published only after @p selector is validated
 * @returns @ref driver_status_t "USB prescaler encode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p selector was encoded successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pField is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p selector is not a supported selector
 */
driver_status_t Codec_RCC_EncodeUSBPrescaler(const rcc_component_prescaler_t selector, reg* const pField);

/**
 * @brief Decodes an `RCC_CFGR_USBPRE` field into a USB prescaler selector
 * @param[in] field Raw `RCC_CFGR_USBPRE` hardware field to decode
 * Accepted values:
 * - Any @ref reg image; an unrecognized field uses the documented reset-state fallback
 * @param[out] pSelector Destination for the decoded USB prescaler selector
 * Expected values:
 * - @ref `RCC_USB_DIV_1_5`: Decoded from `RCC_CFGR_USBPRE_DIV1_5` or any unrecognized field
 * - @ref `RCC_USB_DIV_1`: Decoded from `RCC_CFGR_USBPRE_DIRECT`
 * @returns @ref driver_status_t "USB prescaler decode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p field was decoded successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSelector is `NULL`
 * @note An unrecognized @p field decodes to @ref `RCC_USB_DIV_1_5` and still returns
 * @ref `DRIVER_STATUS_SUCCESS`, matching the reset-state hardware default.
 */
driver_status_t Codec_RCC_DecodeUSBPrescaler(const reg field, rcc_component_prescaler_t* const pSelector);

// ==================================================================================================== //
// RCC Prescaler Divider Resolution
// ==================================================================================================== //

/**
 * @brief Resolves the effective numeric divider represented by an AHB prescaler selector
 * @param[in] selector AHB prescaler selector to resolve
 * Accepted values:
 * - @ref `RCC_AHB_DIV_1`
 * - @ref `RCC_AHB_DIV_2`
 * - @ref `RCC_AHB_DIV_4`
 * - @ref `RCC_AHB_DIV_8`
 * - @ref `RCC_AHB_DIV_16`
 * - @ref `RCC_AHB_DIV_64`
 * - @ref `RCC_AHB_DIV_128`
 * - @ref `RCC_AHB_DIV_256`
 * - @ref `RCC_AHB_DIV_512`
 * - Any other value resolves to the documented fallback
 * @param[out] pDivider Destination for the resolved divider value
 * Expected values:
 * - `1UL`, `2UL`, `4UL`, `8UL`, `16UL`, `64UL`, `128UL`, `256UL`, `512UL`: Divider for a recognized selector
 * - `1UL`: Divider used for any unrecognized selector
 * @returns @ref driver_status_t "AHB divider resolution status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p selector was resolved successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pDivider is `NULL`
 * @note An unrecognized @p selector resolves to a `1UL` divider and still returns
 * @ref `DRIVER_STATUS_SUCCESS`, matching the pre-migration fallback behavior.
 */
driver_status_t Codec_RCC_GetAHBPrescalerDivider(const rcc_bus_prescaler_t selector, uint32_t* const pDivider);

/**
 * @brief Resolves the effective numeric divider represented by an APB prescaler selector
 * @details Shared by both APB1 and APB2 because both buses use the same
 * five-selector divider progression.
 * @param[in] selector APB1 or APB2 prescaler selector to resolve
 * Accepted values:
 * - @ref `RCC_APB1_DIV_1` or @ref `RCC_APB2_DIV_1`
 * - @ref `RCC_APB1_DIV_2` or @ref `RCC_APB2_DIV_2`
 * - @ref `RCC_APB1_DIV_4` or @ref `RCC_APB2_DIV_4`
 * - @ref `RCC_APB1_DIV_8` or @ref `RCC_APB2_DIV_8`
 * - @ref `RCC_APB1_DIV_16` or @ref `RCC_APB2_DIV_16`
 * - Any other value resolves to the documented fallback
 * @param[out] pDivider Destination for the resolved divider value
 * Expected values:
 * - `1UL`, `2UL`, `4UL`, `8UL`, `16UL`: Divider for a recognized selector
 * - `1UL`: Divider used for any unrecognized selector
 * @returns @ref driver_status_t "APB divider resolution status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p selector was resolved successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pDivider is `NULL`
 * @note An unrecognized @p selector resolves to a `1UL` divider and still returns
 * @ref `DRIVER_STATUS_SUCCESS`, matching the pre-migration fallback behavior.
 */
driver_status_t Codec_RCC_GetAPBPrescalerDivider(const rcc_bus_prescaler_t selector, uint32_t* const pDivider);

/**
 * @brief Resolves the effective numeric divider represented by an ADC prescaler selector
 * @param[in] selector ADC prescaler selector to resolve
 * Accepted values:
 * - @ref `RCC_ADC_DIV_2`
 * - @ref `RCC_ADC_DIV_4`
 * - @ref `RCC_ADC_DIV_6`
 * - @ref `RCC_ADC_DIV_8`
 * - Any other value resolves to the documented fallback
 * @param[out] pDivider Destination for the resolved divider value
 * Expected values:
 * - `2UL`, `4UL`, `6UL`, `8UL`: Divider for a recognized selector
 * - `2UL`: Divider used for any unrecognized selector
 * @returns @ref driver_status_t "ADC divider resolution status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p selector was resolved successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pDivider is `NULL`
 * @note An unrecognized @p selector resolves to a `2UL` divider and still returns
 * @ref `DRIVER_STATUS_SUCCESS`, matching the pre-migration fallback behavior.
 */
driver_status_t Codec_RCC_GetADCPrescalerDivider(const rcc_component_prescaler_t selector, uint32_t* const pDivider);

/** @} */ // RCC_03_Driver_08_Codec

/** @} */ // RCC_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_CODEC_H_ */
