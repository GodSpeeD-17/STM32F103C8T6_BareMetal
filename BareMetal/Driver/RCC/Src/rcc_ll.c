/**
 * @file	rcc_ll.c
 * @author	Shrey Shah
 * @brief	RCC Low-Level Control Implementation
 * @version	v3.0
 * @date	22-03-2026
 *
 * @details
 * This source file implements the thin RCC low-level wrapper declared in
 * @ref rcc_ll.h. The implementation stays register-near and validates only
 * raw LL selector legality and basic mask sanity.
 */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //
#include "rcc_ll.h"

// ==================================================================================================== //
//                                   RCC LL System Clock Implementation                                 //
// ==================================================================================================== //

/**
 * @addtogroup RCC_02_LL_02_SystemClock
 * @{
 */

driver_status_t RCC_LL_SetSystemClockSource(const uint32_t sysClkSrcField)
{
	if (RCC_LL_IS_SYSTEM_CLOCK_SOURCE_VALID(sysClkSrcField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	RCC_LL_MODIFY_REG(CFGR, RCC_CFGR_SW_Msk, sysClkSrcField);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetSystemClockSource(uint32_t* const pSysClkSrcField)
{
	if (pSysClkSrcField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	RCC_LL_READ_REG(CFGR, *pSysClkSrcField);
	*pSysClkSrcField &= RCC_CFGR_SW_Msk;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetSystemClockStatus(uint32_t* const pSysClkStatusField)
{
	if (pSysClkStatusField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	RCC_LL_READ_REG(CFGR, *pSysClkStatusField);
	*pSysClkStatusField &= RCC_CFGR_SWS_Msk;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_SetPLLSource(const uint32_t pllSrcField)
{
	if (RCC_LL_IS_PLL_SOURCE_VALID(pllSrcField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	RCC_LL_MODIFY_REG(CFGR, RCC_CFGR_PLLSRC_Msk, pllSrcField);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetPLLSource(uint32_t* const pPllSrcField)
{
	if (pPllSrcField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	RCC_LL_READ_REG(CFGR, *pPllSrcField);
	*pPllSrcField &= RCC_CFGR_PLLSRC_Msk;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_SetPLLHSEDivider(const uint32_t pllHseDividerField)
{
	if (RCC_LL_IS_PLL_HSE_DIVIDER_VALID(pllHseDividerField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	RCC_LL_MODIFY_REG(CFGR, RCC_CFGR_PLLXTPRE_Msk, pllHseDividerField);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetPLLHSEDivider(uint32_t* const pPllHseDividerField)
{
	if (pPllHseDividerField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	RCC_LL_READ_REG(CFGR, *pPllHseDividerField);
	*pPllHseDividerField &= RCC_CFGR_PLLXTPRE_Msk;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_SetPLLMultiplier(const uint32_t pllMulField)
{
	if (RCC_LL_IS_PLL_MULTIPLIER_VALID(pllMulField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	RCC_LL_MODIFY_REG(CFGR, RCC_CFGR_PLLMUL_Msk, pllMulField);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetPLLMultiplier(uint32_t* const pPllMulField)
{
	if (pPllMulField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	RCC_LL_READ_REG(CFGR, *pPllMulField);
	*pPllMulField &= RCC_CFGR_PLLMUL_Msk;
	return DRIVER_STATUS_SUCCESS;
}

/** @} */ // RCC_02_LL_02_SystemClock

// ==================================================================================================== //
//                                    RCC LL Prescaler Implementation                                   //
// ==================================================================================================== //

/**
 * @addtogroup RCC_02_LL_03_Prescalers
 * @{
 */

driver_status_t RCC_LL_SetAHBPrescaler(const uint32_t ahbPrescalerField)
{
	if (RCC_LL_IS_AHB_PRESCALER_VALID(ahbPrescalerField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	RCC_LL_MODIFY_REG(CFGR, RCC_CFGR_HPRE_Msk, ahbPrescalerField);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetAHBPrescaler(uint32_t* const pAhbPrescalerField)
{
	if (pAhbPrescalerField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	RCC_LL_READ_REG(CFGR, *pAhbPrescalerField);
	*pAhbPrescalerField &= RCC_CFGR_HPRE_Msk;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_SetAPB1Prescaler(const uint32_t apb1PrescalerField)
{
	if (RCC_LL_IS_APB1_PRESCALER_VALID(apb1PrescalerField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	RCC_LL_MODIFY_REG(CFGR, RCC_CFGR_PPRE1_Msk, apb1PrescalerField);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetAPB1Prescaler(uint32_t* const pApb1PrescalerField)
{
	if (pApb1PrescalerField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	RCC_LL_READ_REG(CFGR, *pApb1PrescalerField);
	*pApb1PrescalerField &= RCC_CFGR_PPRE1_Msk;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_SetAPB2Prescaler(const uint32_t apb2PrescalerField)
{
	if (((apb2PrescalerField & ~RCC_CFGR_PPRE2_Msk) != 0x00UL) ||
		(RCC_LL_IS_APB2_PRESCALER_VALID((apb2PrescalerField & RCC_CFGR_PPRE2_Msk)) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	RCC_LL_MODIFY_REG(CFGR, RCC_CFGR_PPRE2_Msk, (apb2PrescalerField & RCC_CFGR_PPRE2_Msk));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetAPB2Prescaler(uint32_t* const pApb2PrescalerField)
{
	if (pApb2PrescalerField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	RCC_LL_READ_REG(CFGR, *pApb2PrescalerField);
	*pApb2PrescalerField &= RCC_CFGR_PPRE2_Msk;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_SetADCPrescaler(const uint32_t adcPrescalerField)
{
	if (RCC_LL_IS_ADC_PRESCALER_VALID(adcPrescalerField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	RCC_LL_MODIFY_REG(CFGR, RCC_CFGR_ADCPRE_Msk, adcPrescalerField);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetADCPrescaler(uint32_t* const pAdcPrescalerField)
{
	if (pAdcPrescalerField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	RCC_LL_READ_REG(CFGR, *pAdcPrescalerField);
	*pAdcPrescalerField &= RCC_CFGR_ADCPRE_Msk;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_SetUSBPrescaler(const uint32_t usbPrescalerField)
{
	if (RCC_LL_IS_USB_PRESCALER_VALID(usbPrescalerField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	RCC_LL_MODIFY_REG(CFGR, RCC_CFGR_USBPRE_Msk, usbPrescalerField);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_GetUSBPrescaler(uint32_t* const pUsbPrescalerField)
{
	if (pUsbPrescalerField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	RCC_LL_READ_REG(CFGR, *pUsbPrescalerField);
	*pUsbPrescalerField &= RCC_CFGR_USBPRE_Msk;
	return DRIVER_STATUS_SUCCESS;
}

/** @} */ // RCC_02_LL_03_Prescalers

// ==================================================================================================== //
//                                   RCC LL Clock Reset Implementation                                  //
// ==================================================================================================== //

/**
 * @addtogroup RCC_02_LL_04_ClockReset
 * @{
 */

driver_status_t RCC_LL_EnableAHBClock(const uint32_t mask)
{
	if (RCC_LL_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_SET_BITS(AHBENR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_DisableAHBClock(const uint32_t mask)
{
	if (RCC_LL_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_CLEAR_BITS(AHBENR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_EnableAPB2Clock(const uint32_t mask)
{
	if (RCC_LL_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_SET_BITS(APB2ENR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_DisableAPB2Clock(const uint32_t mask)
{
	if (RCC_LL_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_CLEAR_BITS(APB2ENR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_EnableAPB1Clock(const uint32_t mask)
{
	if (RCC_LL_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_SET_BITS(APB1ENR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_DisableAPB1Clock(const uint32_t mask)
{
	if (RCC_LL_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_CLEAR_BITS(APB1ENR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_ForceAPB2Reset(const uint32_t mask)
{
	if (RCC_LL_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_SET_BITS(APB2RSTR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_ReleaseAPB2Reset(const uint32_t mask)
{
	if (RCC_LL_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_CLEAR_BITS(APB2RSTR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_ForceAPB1Reset(const uint32_t mask)
{
	if (RCC_LL_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_SET_BITS(APB1RSTR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_ReleaseAPB1Reset(const uint32_t mask)
{
	if (RCC_LL_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	RCC_LL_CLEAR_BITS(APB1RSTR, mask);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_PulseAPB2Reset(const uint32_t mask)
{
	ASSERT_DRIVER_STATUS(RCC_LL_ForceAPB2Reset(mask));
	ASSERT_DRIVER_STATUS(RCC_LL_ReleaseAPB2Reset(mask));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_LL_PulseAPB1Reset(const uint32_t mask)
{
	ASSERT_DRIVER_STATUS(RCC_LL_ForceAPB1Reset(mask));
	ASSERT_DRIVER_STATUS(RCC_LL_ReleaseAPB1Reset(mask));
	return DRIVER_STATUS_SUCCESS;
}

/** @} */ // RCC_02_LL_04_ClockReset
