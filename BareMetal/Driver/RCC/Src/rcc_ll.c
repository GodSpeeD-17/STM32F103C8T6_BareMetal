/**
 * @file	rcc_ll.c
 * @author	Shrey Shah
 * @brief	RCC Low-Level Register Control Implementation
 * @version	v2.4
 * @date	22-03-2026
 *
 * @details
 * This source file implements the register-near RCC operations declared in
 * `rcc_ll.h`. It intentionally stays close to the RCC registers and keeps
 * validation limited to raw field legality and mask sanity.
 */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //
#include "rcc_ll.h"

// ==================================================================================================== //
//                               RCC LL Internal Validation and Helpers                                 //
// ==================================================================================================== //

/**
 * @addtogroup RCC_02_LL_03_SystemClock
 * @{
 */

static bool _RCC_LL_IsSystemClockSource(const rcc_ll_sysclk_src_t source)
{
	if ((source == RCC_LL_SYSCLK_SRC_HSI) || (source == RCC_LL_SYSCLK_SRC_HSE) || (source == RCC_LL_SYSCLK_SRC_PLL))
	{
		return true;
	}
	else
	{
		return false;
	}
}

static bool _RCC_LL_IsPLLSource(const rcc_ll_pll_src_t source)
{
	if ((source == RCC_LL_PLL_SRC_HSI_DIV2) || (source == RCC_LL_PLL_SRC_HSE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

static bool _RCC_LL_IsPLLHSEDivider(const rcc_ll_pll_hse_div_t divider)
{
	if ((divider == RCC_LL_PLL_HSE_DIV_1) || (divider == RCC_LL_PLL_HSE_DIV_2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

static bool _RCC_LL_IsPLLMultiplier(const rcc_ll_pll_mul_t multiplier)
{
	switch (multiplier)
	{
		case RCC_LL_PLL_MUL_2:
		case RCC_LL_PLL_MUL_3:
		case RCC_LL_PLL_MUL_4:
		case RCC_LL_PLL_MUL_5:
		case RCC_LL_PLL_MUL_6:
		case RCC_LL_PLL_MUL_7:
		case RCC_LL_PLL_MUL_8:
		case RCC_LL_PLL_MUL_9:
		case RCC_LL_PLL_MUL_10:
		case RCC_LL_PLL_MUL_11:
		case RCC_LL_PLL_MUL_12:
		case RCC_LL_PLL_MUL_13:
		case RCC_LL_PLL_MUL_14:
		case RCC_LL_PLL_MUL_15:
		case RCC_LL_PLL_MUL_16:
		{
			return true;
		}
		default:
		{
			return false;
		}
	}
}

/** @} */ // RCC_02_LL_03_SystemClock

/**
 * @addtogroup RCC_02_LL_04_Prescalers
 * @{
 */

static bool _RCC_LL_IsAHBPrescaler(const rcc_ll_ahb_prescaler_t prescaler)
{
	switch (prescaler)
	{
		case RCC_LL_AHB_DIV_1:
		case RCC_LL_AHB_DIV_2:
		case RCC_LL_AHB_DIV_4:
		case RCC_LL_AHB_DIV_8:
		case RCC_LL_AHB_DIV_16:
		case RCC_LL_AHB_DIV_64:
		case RCC_LL_AHB_DIV_128:
		case RCC_LL_AHB_DIV_256:
		case RCC_LL_AHB_DIV_512:
		{
			return true;
		}
		default:
		{
			return false;
		}
	}
}

static bool _RCC_LL_IsAPBPrescaler(const rcc_ll_apb_prescaler_t prescaler)
{
	if ((prescaler == RCC_LL_APB_DIV_1) || (prescaler == RCC_LL_APB_DIV_2) || (prescaler == RCC_LL_APB_DIV_4) ||
		(prescaler == RCC_LL_APB_DIV_8) || (prescaler == RCC_LL_APB_DIV_16))
	{
		return true;
	}
	else
	{
		return false;
	}
}

static bool _RCC_LL_IsADCPrescaler(const rcc_ll_adc_prescaler_t prescaler)
{
	if ((prescaler == RCC_LL_ADC_DIV_2) || (prescaler == RCC_LL_ADC_DIV_4) || (prescaler == RCC_LL_ADC_DIV_6) ||
		(prescaler == RCC_LL_ADC_DIV_8))
	{
		return true;
	}
	else
	{
		return false;
	}
}

static bool _RCC_LL_IsUSBPrescaler(const rcc_ll_usb_prescaler_t prescaler)
{
	if ((prescaler == RCC_LL_USB_DIV_1_5) || (prescaler == RCC_LL_USB_DIV_1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/** @} */ // RCC_02_LL_04_Prescalers

/**
 * @addtogroup RCC_02_LL_05_ClockReset
 * @{
 */

static driver_status_t _RCC_LL_ValidateMask(const uint32_t mask)
{
	if (mask == 0x00UL)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	else
	{
		return DRIVER_STATUS_SUCCESS;
	}
}


/** @} */ // RCC_02_LL_05_ClockReset

// ==================================================================================================== //
//                                   RCC LL System Clock Implementation                                 //
// ==================================================================================================== //

/**
 * @addtogroup RCC_02_LL_03_SystemClock
 * @{
 */

driver_status_t RCC_LL_SetSystemClockSource(const rcc_ll_sysclk_src_t source)
{
	if (_RCC_LL_IsSystemClockSource(source) == false)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_MODIFY(RCC, CFGR, RCC_CFGR_SW_Msk, source);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetSystemClockSource(rcc_ll_sysclk_src_t* const pSource)
{
	if (pSource == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	*pSource = (RCC->CFGR.REG & RCC_CFGR_SW_Msk);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetSystemClockStatus(rcc_ll_sysclk_status_t* const pStatus)
{
	if (pStatus == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	*pStatus = (RCC->CFGR.REG & RCC_CFGR_SWS_Msk);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_SetPLLSource(const rcc_ll_pll_src_t source)
{
	if (_RCC_LL_IsPLLSource(source) == false)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_MODIFY(RCC, CFGR, RCC_CFGR_PLLSRC_Msk, source);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetPLLSource(rcc_ll_pll_src_t* const pSource)
{
	if (pSource == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	*pSource = (RCC->CFGR.REG & RCC_CFGR_PLLSRC_Msk);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_SetPLLHSEDivider(const rcc_ll_pll_hse_div_t divider)
{
	if (_RCC_LL_IsPLLHSEDivider(divider) == false)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_MODIFY(RCC, CFGR, RCC_CFGR_PLLXTPRE_Msk, divider);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetPLLHSEDivider(rcc_ll_pll_hse_div_t* const pDivider)
{
	if (pDivider == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	*pDivider = (RCC->CFGR.REG & RCC_CFGR_PLLXTPRE_Msk);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_SetPLLMultiplier(const rcc_ll_pll_mul_t multiplier)
{
	if (_RCC_LL_IsPLLMultiplier(multiplier) == false)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_MODIFY(RCC, CFGR, RCC_CFGR_PLLMUL_Msk, multiplier);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetPLLMultiplier(rcc_ll_pll_mul_t* const pMultiplier)
{
	if (pMultiplier == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	*pMultiplier = (RCC->CFGR.REG & RCC_CFGR_PLLMUL_Msk);
	return DRIVER_STATUS_SUCCESS;
}

/** @} */ // RCC_02_LL_03_SystemClock

// ==================================================================================================== //
//                                    RCC LL Prescaler Implementation                                   //
// ==================================================================================================== //

/**
 * @addtogroup RCC_02_LL_04_Prescalers
 * @{
 */

driver_status_t RCC_LL_SetAHBPrescaler(const rcc_ll_ahb_prescaler_t prescaler)
{
	if (_RCC_LL_IsAHBPrescaler(prescaler) == false)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_MODIFY(RCC, CFGR, RCC_CFGR_HPRE_Msk, prescaler);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetAHBPrescaler(rcc_ll_ahb_prescaler_t* const pPrescaler)
{
	if (pPrescaler == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	*pPrescaler = (RCC->CFGR.REG & RCC_CFGR_HPRE_Msk);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_SetAPB1Prescaler(const rcc_ll_apb_prescaler_t prescaler)
{
	if (_RCC_LL_IsAPBPrescaler(prescaler) == false)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_MODIFY(RCC, CFGR, RCC_CFGR_PPRE1_Msk, prescaler);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetAPB1Prescaler(rcc_ll_apb_prescaler_t* const pPrescaler)
{
	if (pPrescaler == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	*pPrescaler = (RCC->CFGR.REG & RCC_CFGR_PPRE1_Msk);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_SetAPB2Prescaler(const rcc_ll_apb_prescaler_t prescaler)
{
	if (_RCC_LL_IsAPBPrescaler(prescaler) == false)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_MODIFY(RCC, CFGR, RCC_CFGR_PPRE2_Msk, (((prescaler >> RCC_CFGR_PPRE1_Pos) << RCC_CFGR_PPRE2_Pos) & RCC_CFGR_PPRE2_Msk));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetAPB2Prescaler(rcc_ll_apb_prescaler_t* const pPrescaler)
{
	if (pPrescaler == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	*pPrescaler = ((RCC->CFGR.REG & RCC_CFGR_PPRE2_Msk) >> (RCC_CFGR_PPRE2_Pos - RCC_CFGR_PPRE1_Pos)) << RCC_CFGR_PPRE1_Pos;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_SetADCPrescaler(const rcc_ll_adc_prescaler_t prescaler)
{
	if (_RCC_LL_IsADCPrescaler(prescaler) == false)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_MODIFY(RCC, CFGR, RCC_CFGR_ADCPRE_Msk, prescaler);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetADCPrescaler(rcc_ll_adc_prescaler_t* const pPrescaler)
{
	if (pPrescaler == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	*pPrescaler = (RCC->CFGR.REG & RCC_CFGR_ADCPRE_Msk);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_SetUSBPrescaler(const rcc_ll_usb_prescaler_t prescaler)
{
	if (_RCC_LL_IsUSBPrescaler(prescaler) == false)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_MODIFY(RCC, CFGR, RCC_CFGR_USBPRE_Msk, prescaler);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetUSBPrescaler(rcc_ll_usb_prescaler_t* const pPrescaler)
{
	if (pPrescaler == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	*pPrescaler = (RCC->CFGR.REG & RCC_CFGR_USBPRE);
	return DRIVER_STATUS_SUCCESS;
}


// ==================================================================================================== //
//                                      RCC LL Clock Gate and Reset                                      //
/** @} */ // RCC_02_LL_04_Prescalers

// ==================================================================================================== //
//                                   RCC LL Clock Reset Implementation                                  //
// ==================================================================================================== //

/**
 * @addtogroup RCC_02_LL_05_ClockReset
 * @{
 */

driver_status_t RCC_LL_AHB_EnableClock(const uint32_t mask)
{
	ASSERT_DRIVER_STATUS(_RCC_LL_ValidateMask(mask));
	RCC_LL_SET(RCC, AHBENR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_AHB_DisableClock(const uint32_t mask)
{
	ASSERT_DRIVER_STATUS(_RCC_LL_ValidateMask(mask));
	RCC_LL_CLEAR(RCC, AHBENR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_APB2_EnableClock(const uint32_t mask)
{
	ASSERT_DRIVER_STATUS(_RCC_LL_ValidateMask(mask));
	RCC_LL_SET(RCC, APB2ENR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_APB2_DisableClock(const uint32_t mask)
{
	ASSERT_DRIVER_STATUS(_RCC_LL_ValidateMask(mask));
	RCC_LL_CLEAR(RCC, APB2ENR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_APB1_EnableClock(const uint32_t mask)
{
	ASSERT_DRIVER_STATUS(_RCC_LL_ValidateMask(mask));
	RCC_LL_SET(RCC, APB1ENR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_APB1_DisableClock(const uint32_t mask)
{
	ASSERT_DRIVER_STATUS(_RCC_LL_ValidateMask(mask));
	RCC_LL_CLEAR(RCC, APB1ENR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_APB2_ForceReset(const uint32_t mask)
{
	ASSERT_DRIVER_STATUS(_RCC_LL_ValidateMask(mask));
	RCC_LL_SET(RCC, APB2RSTR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_APB2_ReleaseReset(const uint32_t mask)
{
	ASSERT_DRIVER_STATUS(_RCC_LL_ValidateMask(mask));
	RCC_LL_CLEAR(RCC, APB2RSTR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_APB1_ForceReset(const uint32_t mask)
{
	ASSERT_DRIVER_STATUS(_RCC_LL_ValidateMask(mask));
	RCC_LL_SET(RCC, APB1RSTR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_APB1_ReleaseReset(const uint32_t mask)
{
	ASSERT_DRIVER_STATUS(_RCC_LL_ValidateMask(mask));
	RCC_LL_CLEAR(RCC, APB1RSTR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_APB2_ResetPulse(const uint32_t mask)
{
	ASSERT_DRIVER_STATUS(RCC_LL_APB2_ForceReset(mask));
	ASSERT_DRIVER_STATUS(RCC_LL_APB2_ReleaseReset(mask));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_APB1_ResetPulse(const uint32_t mask)
{
	ASSERT_DRIVER_STATUS(RCC_LL_APB1_ForceReset(mask));
	ASSERT_DRIVER_STATUS(RCC_LL_APB1_ReleaseReset(mask));
	return DRIVER_STATUS_SUCCESS;
}

/** @} */ // RCC_02_LL_05_ClockReset
