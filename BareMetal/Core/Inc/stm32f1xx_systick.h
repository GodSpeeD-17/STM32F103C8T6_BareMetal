/**
 * @file	stm32f1xx_systick.h
 * @author	Shrey Shah
 * @brief	Cortex-M3 SysTick register-layer definitions
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section SYSTICK_CORE_H_HIERARCHY Hierarchy
 * - Position: Layer 0 - Core register model
 * - Used by: Layer 1 shared SysTick Driver and legacy direct-register examples
 * - Uses: Shared register types and register-field utilities
 *
 * @section SYSTICK_CORE_H_RESPONSIBILITY Responsibility
 * This header owns every raw SysTick register-field macro and the complete
 * memory-mapped register structure with canonical `.REG` and documentary
 * `.BIT` views.
 *
 * @section SYSTICK_CORE_H_BOUNDARY Dependency Boundary
 * This file contains no Driver selector policy, application time unit,
 * interrupt callback, or software tick accumulator. Dependencies flow from
 * the Driver into this register layer, never upward.
 */

// Header Guard
#ifndef STM32F1XX_SYSTICK_H_
#define STM32F1XX_SYSTICK_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "stm32f1xx_data_types.h"
#include "stm32f1xx_base_address.h"
#include "stm32f1xx_utils.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup SYSTICK Cortex-M3 System Timer (SysTick)
 * @brief Cortex-M3 24-bit system timer register model and Driver stack
 */

/**
 * @defgroup SYSTICK_01_RegisterLayer SysTick Register Layer
 * @ingroup SYSTICK
 * @brief Raw SysTick register fields and memory map
 * @details
 * This layer mirrors the Cortex-M3 SysTick register bank. Driver validation,
 * configuration sequencing, IRQ-source policy, and application timekeeping
 * belong above this layer.
 * @see SYSTICK_Peripheral_Guide
 * @{
 */

// ==================================================================================================== //
// SysTick CTRL Register Defines
// ==================================================================================================== //

/** @brief Counter enable (`SysTick_CTRL.ENABLE`) bit position @def SysTick_CTRL_ENABLE_Pos */
#define SysTick_CTRL_ENABLE_Pos			((reg_bit_pos_t) 0U)
/** @brief Counter enable (`SysTick_CTRL.ENABLE`) bit mask @def SysTick_CTRL_ENABLE_Msk */
#define SysTick_CTRL_ENABLE_Msk			REG_BIT_MASK(SysTick_CTRL_ENABLE_Pos)
/** @brief Counter enable (`SysTick_CTRL.ENABLE`) bit mask alias @def SysTick_CTRL_ENABLE */
#define SysTick_CTRL_ENABLE				SysTick_CTRL_ENABLE_Msk

/** @brief Exception request enable (`SysTick_CTRL.TICKINT`) bit position @def SysTick_CTRL_TICKINT_Pos */
#define SysTick_CTRL_TICKINT_Pos		((reg_bit_pos_t) 1U)
/** @brief Exception request enable (`SysTick_CTRL.TICKINT`) bit mask @def SysTick_CTRL_TICKINT_Msk */
#define SysTick_CTRL_TICKINT_Msk		REG_BIT_MASK(SysTick_CTRL_TICKINT_Pos)
/** @brief Exception request enable (`SysTick_CTRL.TICKINT`) bit mask alias @def SysTick_CTRL_TICKINT */
#define SysTick_CTRL_TICKINT			SysTick_CTRL_TICKINT_Msk

/** @brief Clock-source selection (`SysTick_CTRL.CLKSOURCE`) bit position @def SysTick_CTRL_CLKSOURCE_Pos */
#define SysTick_CTRL_CLKSOURCE_Pos		((reg_bit_pos_t) 2U)
/** @brief Clock-source selection (`SysTick_CTRL.CLKSOURCE`) bit mask @def SysTick_CTRL_CLKSOURCE_Msk */
#define SysTick_CTRL_CLKSOURCE_Msk		REG_BIT_MASK(SysTick_CTRL_CLKSOURCE_Pos)
/** @brief Clock-source selection (`SysTick_CTRL.CLKSOURCE`) bit mask alias @def SysTick_CTRL_CLKSOURCE */
#define SysTick_CTRL_CLKSOURCE			SysTick_CTRL_CLKSOURCE_Msk

/** @brief Counter-wrap flag (`SysTick_CTRL.COUNTFLAG`) bit position @def SysTick_CTRL_COUNTFLAG_Pos */
#define SysTick_CTRL_COUNTFLAG_Pos		((reg_bit_pos_t) 16U)
/** @brief Counter-wrap flag (`SysTick_CTRL.COUNTFLAG`) bit mask @def SysTick_CTRL_COUNTFLAG_Msk */
#define SysTick_CTRL_COUNTFLAG_Msk		REG_BIT_MASK(SysTick_CTRL_COUNTFLAG_Pos)
/** @brief Counter-wrap flag (`SysTick_CTRL.COUNTFLAG`) bit mask alias @def SysTick_CTRL_COUNTFLAG */
#define SysTick_CTRL_COUNTFLAG			SysTick_CTRL_COUNTFLAG_Msk

// ==================================================================================================== //
// SysTick LOAD Register Defines
// ==================================================================================================== //

/** @brief Reload value (`SysTick_LOAD.RELOAD`) field position @def SysTick_LOAD_RELOAD_Pos */
#define SysTick_LOAD_RELOAD_Pos			((reg_bit_pos_t) 0U)
/** @brief Reload value (`SysTick_LOAD.RELOAD`) field width @def SysTick_LOAD_RELOAD_Width */
#define SysTick_LOAD_RELOAD_Width		((reg_field_width_t) 24U)
/** @brief Reload value (`SysTick_LOAD.RELOAD`) field mask @def SysTick_LOAD_RELOAD_Msk */
#define SysTick_LOAD_RELOAD_Msk			REG_FIELD_MASK(SysTick_LOAD_RELOAD_Pos, SysTick_LOAD_RELOAD_Width)
/** @brief Reload value (`SysTick_LOAD.RELOAD`) field mask alias @def SysTick_LOAD_RELOAD */
#define SysTick_LOAD_RELOAD				SysTick_LOAD_RELOAD_Msk

// ==================================================================================================== //
// SysTick VAL Register Defines
// ==================================================================================================== //

/** @brief Current value (`SysTick_VAL.CURRENT`) field position @def SysTick_VAL_CURRENT_Pos */
#define SysTick_VAL_CURRENT_Pos			((reg_bit_pos_t) 0U)
/** @brief Current value (`SysTick_VAL.CURRENT`) field width @def SysTick_VAL_CURRENT_Width */
#define SysTick_VAL_CURRENT_Width		((reg_field_width_t) 24U)
/** @brief Current value (`SysTick_VAL.CURRENT`) field mask @def SysTick_VAL_CURRENT_Msk */
#define SysTick_VAL_CURRENT_Msk			REG_FIELD_MASK(SysTick_VAL_CURRENT_Pos, SysTick_VAL_CURRENT_Width)
/** @brief Current value (`SysTick_VAL.CURRENT`) field mask alias @def SysTick_VAL_CURRENT */
#define SysTick_VAL_CURRENT				SysTick_VAL_CURRENT_Msk

// ==================================================================================================== //
// SysTick CALIB Register Defines
// ==================================================================================================== //

/** @brief Ten-millisecond calibration (`SysTick_CALIB.TENMS`) field position @def SysTick_CALIB_TENMS_Pos */
#define SysTick_CALIB_TENMS_Pos			((reg_bit_pos_t) 0U)
/** @brief Ten-millisecond calibration (`SysTick_CALIB.TENMS`) field width @def SysTick_CALIB_TENMS_Width */
#define SysTick_CALIB_TENMS_Width		((reg_field_width_t) 24U)
/** @brief Ten-millisecond calibration (`SysTick_CALIB.TENMS`) field mask @def SysTick_CALIB_TENMS_Msk */
#define SysTick_CALIB_TENMS_Msk			REG_FIELD_MASK(SysTick_CALIB_TENMS_Pos, SysTick_CALIB_TENMS_Width)
/** @brief Ten-millisecond calibration (`SysTick_CALIB.TENMS`) field mask alias @def SysTick_CALIB_TENMS */
#define SysTick_CALIB_TENMS				SysTick_CALIB_TENMS_Msk

/** @brief Calibration inexactness (`SysTick_CALIB.SKEW`) bit position @def SysTick_CALIB_SKEW_Pos */
#define SysTick_CALIB_SKEW_Pos			((reg_bit_pos_t) 30U)
/** @brief Calibration inexactness (`SysTick_CALIB.SKEW`) bit mask @def SysTick_CALIB_SKEW_Msk */
#define SysTick_CALIB_SKEW_Msk			REG_BIT_MASK(SysTick_CALIB_SKEW_Pos)
/** @brief Calibration inexactness (`SysTick_CALIB.SKEW`) bit mask alias @def SysTick_CALIB_SKEW */
#define SysTick_CALIB_SKEW				SysTick_CALIB_SKEW_Msk

/** @brief External reference absence (`SysTick_CALIB.NOREF`) bit position @def SysTick_CALIB_NOREF_Pos */
#define SysTick_CALIB_NOREF_Pos			((reg_bit_pos_t) 31U)
/** @brief External reference absence (`SysTick_CALIB.NOREF`) bit mask @def SysTick_CALIB_NOREF_Msk */
#define SysTick_CALIB_NOREF_Msk			REG_BIT_MASK(SysTick_CALIB_NOREF_Pos)
/** @brief External reference absence (`SysTick_CALIB.NOREF`) bit mask alias @def SysTick_CALIB_NOREF */
#define SysTick_CALIB_NOREF				SysTick_CALIB_NOREF_Msk

// ==================================================================================================== //
// SysTick Register Map
// ==================================================================================================== //

/**
 * @brief Cortex-M3 SysTick register structure
 * @details
 * Every register occupies one 32-bit word. `.REG` is the canonical LL access
 * path; `.BIT` documents the implemented field placement.
 */
typedef struct _SysTick_TypeDef
{
	/** @brief Control and status register at offset `0x00` */
	union
	{
		_IO REG;
		struct
		{
			_IO ENABLE : 1;
			_IO TICKINT : 1;
			_IO CLKSOURCE : 1;
			_IO reserved_1 : 13;
			_IO COUNTFLAG : 1;
			_IO reserved_2 : 15;
		} BIT;
	} CTRL;

	/** @brief Reload value register at offset `0x04` */
	union
	{
		_IO REG;
		struct
		{
			_IO RELOAD : 24;
			_IO reserved : 8;
		} BIT;
	} LOAD;

	/** @brief Current value register at offset `0x08` */
	union
	{
		_IO REG;
		struct
		{
			_IO CURRENT : 24;
			_IO reserved : 8;
		} BIT;
	} VAL;

	/** @brief Calibration value register at offset `0x0C` */
	union
	{
		_I REG;
		struct
		{
			_I TENMS : 24;
			_I reserved : 6;
			_I SKEW : 1;
			_I NOREF : 1;
		} BIT;
	} CALIB;
} SysTick_TypeDef;

/** @brief Cortex-M3 SysTick register-bank instance @def SysTick */
#define SysTick		((SysTick_TypeDef*) SysTick_BASE_ADDR)

/** @} */ // SYSTICK_01_RegisterLayer

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_SYSTICK_H_ */
