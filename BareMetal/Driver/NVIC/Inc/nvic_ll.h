/**
 * @file	nvic_ll.h
 * @author	Shrey Shah
 * @brief	NVIC Low-Level Register Interface
 * @version	v1.0
 * @date	16-08-2026
 *
 * @details
 * These declarations expose exact-width, one-access NVIC and AIRCR register
 * primitives. They do not validate IRQ numbers or own driver policy.
 */

// Header Guards
#ifndef NVIC_LL_H_
#define NVIC_LL_H_

#include "stm32f1xx.h"
#include "nvic_data_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup NVIC_02_LL NVIC Low-Level Register Access
 * @ingroup NVIC_Driver
 * @brief One-access NVIC and SCB AIRCR primitives
 * @{
 */

/**
 * @brief Reads one complete NVIC ISER enable-state image
 * @param[in] registerIndex Zero-based ISER bank index
 * Accepted values:
 * - `0U..1U` for the exact STM32F103C8T6 target
 * @returns Full 32-bit ISER state image
 * @pre Caller owns register-index validation.
 */
reg LL_NVIC_ReadISER(const uint8_t registerIndex);
/**
 * @brief Issues one direct NVIC ISER write-one-to-set action
 * @param[in] registerIndex Zero-based ISER bank index
 * Accepted values:
 * - `0U..1U` for the exact STM32F103C8T6 target
 * @param[in] actionMask Register-positioned IRQ action mask
 * Accepted values:
 * - One validated target IRQ bit
 * @returns Void.
 * @pre Caller owns register-index and action-mask validation.
 */
void LL_NVIC_WriteISER(const uint8_t registerIndex, const reg actionMask);
/**
 * @brief Issues one direct NVIC ICER write-one-to-clear action
 * @param[in] registerIndex Zero-based ICER bank index
 * Accepted values:
 * - `0U..1U` for the exact STM32F103C8T6 target
 * @param[in] actionMask Register-positioned IRQ action mask
 * Accepted values:
 * - One validated target IRQ bit
 * @returns Void.
 * @pre Caller owns validation and post-write synchronization.
 */
void LL_NVIC_WriteICER(const uint8_t registerIndex, const reg actionMask);
/**
 * @brief Reads one complete NVIC ISPR pending-state image
 * @param[in] registerIndex Zero-based ISPR bank index
 * Accepted values:
 * - `0U..1U` for the exact STM32F103C8T6 target
 * @returns Full 32-bit ISPR state image
 * @pre Caller owns register-index validation.
 */
reg LL_NVIC_ReadISPR(const uint8_t registerIndex);
/**
 * @brief Issues one direct NVIC ICPR write-one-to-clear action
 * @param[in] registerIndex Zero-based ICPR bank index
 * Accepted values:
 * - `0U..1U` for the exact STM32F103C8T6 target
 * @param[in] actionMask Register-positioned IRQ action mask
 * Accepted values:
 * - One validated target IRQ bit
 * @returns Void.
 * @pre Caller owns register-index and action-mask validation.
 */
void LL_NVIC_WriteICPR(const uint8_t registerIndex, const reg actionMask);
/**
 * @brief Reads one complete read-only NVIC IABR active-state image
 * @param[in] registerIndex Zero-based IABR bank index
 * Accepted values:
 * - `0U..1U` for the exact STM32F103C8T6 target
 * @returns Full 32-bit IABR state image
 * @pre Caller owns register-index validation.
 */
reg LL_NVIC_ReadIABR(const uint8_t registerIndex);
/**
 * @brief Reads exactly one IRQ priority byte
 * @param[in] IRQn Validated external IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns Raw eight-bit IPR field image
 * @pre Caller owns IRQ validation.
 */
reg_field_t LL_NVIC_ReadIPR(const irq_t IRQn);
/**
 * @brief Writes exactly one IRQ priority byte
 * @param[in] IRQn Validated external IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @param[in] priorityFieldImage Complete raw IPR byte image
 * Accepted values:
 * - `0x00U..0xF0U` with implemented priority in bits 7 through 4
 * @returns Void.
 * @pre Caller owns IRQ and image validation.
 */
void LL_NVIC_WriteIPR(const irq_t IRQn, const reg_field_t priorityFieldImage);
/**
 * @brief Issues one direct NVIC STIR software-trigger action
 * @param[in] IRQn Validated external IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns Void.
 * @pre Caller owns IRQ validation and privilege policy.
 */
void LL_NVIC_WriteSTIR(const irq_t IRQn);
/**
 * @brief Reads the complete SCB AIRCR image
 * @returns Full 32-bit AIRCR image
 */
reg LL_SCB_ReadAIRCR(void);
/**
 * @brief Writes one caller-staged keyed SCB AIRCR image
 * @param[in] aircrRegImage Complete keyed AIRCR write image
 * Accepted values:
 * - A Codec-staged image containing VECTKEY and a canonical PRIGROUP field
 * @returns Void.
 * @pre Caller owns AIRCR staging and global transaction ownership.
 */
void LL_SCB_WriteAIRCR(const reg aircrRegImage);

/** @} */ // NVIC_02_LL

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NVIC_LL_H_ */
