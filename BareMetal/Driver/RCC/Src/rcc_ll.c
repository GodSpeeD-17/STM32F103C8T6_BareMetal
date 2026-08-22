/**
 * @file	rcc_ll.c
 * @author	Shrey Shah
 * @brief	RCC Low-Level Register Access Implementation
 * @version	v4.0
 * @date	22-08-2026
 *
 * @details
 * This source file implements the thin RCC low-level wrapper declared in
 * @ref rcc_ll.h. Every field-level accessor stages its read-modify-write
 * sequence through the named full-register accessors, which in turn delegate
 * to the shared @ref LL_RCC_ReadRegister / @ref LL_RCC_WriteRegister primitive
 * pair. The implementation stays register-near and validates only raw LL
 * selector legality and basic mask sanity.
 */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //
#include "rcc_ll.h"

// ==================================================================================================== //
//                                   RCC LL System Clock Implementation                                 //
// ==================================================================================================== //

/**
 * @addtogroup RCC_02_LL_03_SystemClock
 * @{
 */

driver_status_t LL_RCC_SetSystemClockSource(const uint32_t sysClkSrcField)
{
	// Local Variable
	reg cfgrImage = 0x00000000UL;

	if (LL_RCC_IS_SYSTEM_CLOCK_SOURCE_VALID(sysClkSrcField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Replace only the SW field so every other CFGR selector remains untouched.
	cfgrImage = LL_RCC_ReadCFGR();
	cfgrImage = (cfgrImage & ~RCC_CFGR_SW_Msk) | (sysClkSrcField & RCC_CFGR_SW_Msk);
	LL_RCC_WriteCFGR(cfgrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_GetSystemClockSource(uint32_t* const pSysClkSrcField)
{
	if (pSysClkSrcField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Isolate the SW field from a single coherent CFGR snapshot.
	*pSysClkSrcField = (LL_RCC_ReadCFGR() & RCC_CFGR_SW_Msk);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_GetSystemClockStatus(uint32_t* const pSysClkStatusField)
{
	if (pSysClkStatusField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Isolate the SWS field from a single coherent CFGR snapshot.
	*pSysClkStatusField = (LL_RCC_ReadCFGR() & RCC_CFGR_SWS_Msk);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_SetPLLSource(const uint32_t pllSrcField)
{
	// Local Variable
	reg cfgrImage = 0x00000000UL;

	if (LL_RCC_IS_PLL_SOURCE_VALID(pllSrcField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Replace only the PLLSRC field so every other CFGR selector remains untouched.
	cfgrImage = LL_RCC_ReadCFGR();
	cfgrImage = (cfgrImage & ~RCC_CFGR_PLLSRC_Msk) | (pllSrcField & RCC_CFGR_PLLSRC_Msk);
	LL_RCC_WriteCFGR(cfgrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_GetPLLSource(uint32_t* const pPllSrcField)
{
	if (pPllSrcField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Isolate the PLLSRC field from a single coherent CFGR snapshot.
	*pPllSrcField = (LL_RCC_ReadCFGR() & RCC_CFGR_PLLSRC_Msk);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_SetPLLHSEDivider(const uint32_t pllHseDividerField)
{
	// Local Variable
	reg cfgrImage = 0x00000000UL;

	if (LL_RCC_IS_PLL_HSE_DIVIDER_VALID(pllHseDividerField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Replace only the PLLXTPRE field so every other CFGR selector remains untouched.
	cfgrImage = LL_RCC_ReadCFGR();
	cfgrImage = (cfgrImage & ~RCC_CFGR_PLLXTPRE_Msk) | (pllHseDividerField & RCC_CFGR_PLLXTPRE_Msk);
	LL_RCC_WriteCFGR(cfgrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_GetPLLHSEDivider(uint32_t* const pPllHseDividerField)
{
	if (pPllHseDividerField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Isolate the PLLXTPRE field from a single coherent CFGR snapshot.
	*pPllHseDividerField = (LL_RCC_ReadCFGR() & RCC_CFGR_PLLXTPRE_Msk);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_SetPLLMultiplier(const uint32_t pllMulField)
{
	// Local Variable
	reg cfgrImage = 0x00000000UL;

	if (LL_RCC_IS_PLL_MULTIPLIER_VALID(pllMulField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Replace only the PLLMUL field so every other CFGR selector remains untouched.
	cfgrImage = LL_RCC_ReadCFGR();
	cfgrImage = (cfgrImage & ~RCC_CFGR_PLLMUL_Msk) | (pllMulField & RCC_CFGR_PLLMUL_Msk);
	LL_RCC_WriteCFGR(cfgrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_GetPLLMultiplier(uint32_t* const pPllMulField)
{
	if (pPllMulField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Isolate the PLLMUL field from a single coherent CFGR snapshot.
	*pPllMulField = (LL_RCC_ReadCFGR() & RCC_CFGR_PLLMUL_Msk);
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

driver_status_t LL_RCC_SetAHBPrescaler(const uint32_t ahbPrescalerField)
{
	// Local Variable
	reg cfgrImage = 0x00000000UL;

	if (LL_RCC_IS_AHB_PRESCALER_VALID(ahbPrescalerField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Replace only the HPRE field so every other CFGR selector remains untouched.
	cfgrImage = LL_RCC_ReadCFGR();
	cfgrImage = (cfgrImage & ~RCC_CFGR_HPRE_Msk) | (ahbPrescalerField & RCC_CFGR_HPRE_Msk);
	LL_RCC_WriteCFGR(cfgrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_GetAHBPrescaler(uint32_t* const pAhbPrescalerField)
{
	if (pAhbPrescalerField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Isolate the HPRE field from a single coherent CFGR snapshot.
	*pAhbPrescalerField = (LL_RCC_ReadCFGR() & RCC_CFGR_HPRE_Msk);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_SetAPB1Prescaler(const uint32_t apb1PrescalerField)
{
	// Local Variable
	reg cfgrImage = 0x00000000UL;

	if (LL_RCC_IS_APB1_PRESCALER_VALID(apb1PrescalerField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Replace only the PPRE1 field so every other CFGR selector remains untouched.
	cfgrImage = LL_RCC_ReadCFGR();
	cfgrImage = (cfgrImage & ~RCC_CFGR_PPRE1_Msk) | (apb1PrescalerField & RCC_CFGR_PPRE1_Msk);
	LL_RCC_WriteCFGR(cfgrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_GetAPB1Prescaler(uint32_t* const pApb1PrescalerField)
{
	if (pApb1PrescalerField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Isolate the PPRE1 field from a single coherent CFGR snapshot.
	*pApb1PrescalerField = (LL_RCC_ReadCFGR() & RCC_CFGR_PPRE1_Msk);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_SetAPB2Prescaler(const uint32_t apb2PrescalerField)
{
	// Local Variable
	reg cfgrImage = 0x00000000UL;

	//! Preserve the historical stricter check that also rejects stray bits outside PPRE2.
	if (((apb2PrescalerField & ~RCC_CFGR_PPRE2_Msk) != 0x00UL) ||
		(LL_RCC_IS_APB2_PRESCALER_VALID((apb2PrescalerField & RCC_CFGR_PPRE2_Msk)) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	cfgrImage = LL_RCC_ReadCFGR();
	cfgrImage = (cfgrImage & ~RCC_CFGR_PPRE2_Msk) | (apb2PrescalerField & RCC_CFGR_PPRE2_Msk);
	LL_RCC_WriteCFGR(cfgrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_GetAPB2Prescaler(uint32_t* const pApb2PrescalerField)
{
	if (pApb2PrescalerField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Isolate the PPRE2 field from a single coherent CFGR snapshot.
	*pApb2PrescalerField = (LL_RCC_ReadCFGR() & RCC_CFGR_PPRE2_Msk);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_SetADCPrescaler(const uint32_t adcPrescalerField)
{
	// Local Variable
	reg cfgrImage = 0x00000000UL;

	if (LL_RCC_IS_ADC_PRESCALER_VALID(adcPrescalerField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Replace only the ADCPRE field so every other CFGR selector remains untouched.
	cfgrImage = LL_RCC_ReadCFGR();
	cfgrImage = (cfgrImage & ~RCC_CFGR_ADCPRE_Msk) | (adcPrescalerField & RCC_CFGR_ADCPRE_Msk);
	LL_RCC_WriteCFGR(cfgrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_GetADCPrescaler(uint32_t* const pAdcPrescalerField)
{
	if (pAdcPrescalerField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Isolate the ADCPRE field from a single coherent CFGR snapshot.
	*pAdcPrescalerField = (LL_RCC_ReadCFGR() & RCC_CFGR_ADCPRE_Msk);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_SetUSBPrescaler(const uint32_t usbPrescalerField)
{
	// Local Variable
	reg cfgrImage = 0x00000000UL;

	if (LL_RCC_IS_USB_PRESCALER_VALID(usbPrescalerField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Replace only the USBPRE field so every other CFGR selector remains untouched.
	cfgrImage = LL_RCC_ReadCFGR();
	cfgrImage = (cfgrImage & ~RCC_CFGR_USBPRE_Msk) | (usbPrescalerField & RCC_CFGR_USBPRE_Msk);
	LL_RCC_WriteCFGR(cfgrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_GetUSBPrescaler(uint32_t* const pUsbPrescalerField)
{
	if (pUsbPrescalerField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Isolate the USBPRE field from a single coherent CFGR snapshot.
	*pUsbPrescalerField = (LL_RCC_ReadCFGR() & RCC_CFGR_USBPRE_Msk);
	return DRIVER_STATUS_SUCCESS;
}

/** @} */ // RCC_02_LL_04_Prescalers

// ==================================================================================================== //
//                                   RCC LL Clock Reset Implementation                                  //
// ==================================================================================================== //

/**
 * @addtogroup RCC_02_LL_05_ClockReset
 * @{
 */

driver_status_t LL_RCC_EnableAHBClock(const uint32_t mask)
{
	// Local Variable
	reg ahbenrImage = 0x00000000UL;

	if (LL_RCC_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Preserve every other AHB clock gate while setting only the requested mask.
	ahbenrImage = LL_RCC_ReadAHBENR();
	ahbenrImage |= mask;
	LL_RCC_WriteAHBENR(ahbenrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_DisableAHBClock(const uint32_t mask)
{
	// Local Variable
	reg ahbenrImage = 0x00000000UL;

	if (LL_RCC_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Preserve every other AHB clock gate while clearing only the requested mask.
	ahbenrImage = LL_RCC_ReadAHBENR();
	ahbenrImage &= ~mask;
	LL_RCC_WriteAHBENR(ahbenrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_EnableAPB2Clock(const uint32_t mask)
{
	// Local Variable
	reg apb2enrImage = 0x00000000UL;

	if (LL_RCC_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Preserve every other APB2 clock gate while setting only the requested mask.
	apb2enrImage = LL_RCC_ReadAPB2ENR();
	apb2enrImage |= mask;
	LL_RCC_WriteAPB2ENR(apb2enrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_DisableAPB2Clock(const uint32_t mask)
{
	// Local Variable
	reg apb2enrImage = 0x00000000UL;

	if (LL_RCC_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Preserve every other APB2 clock gate while clearing only the requested mask.
	apb2enrImage = LL_RCC_ReadAPB2ENR();
	apb2enrImage &= ~mask;
	LL_RCC_WriteAPB2ENR(apb2enrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_EnableAPB1Clock(const uint32_t mask)
{
	// Local Variable
	reg apb1enrImage = 0x00000000UL;

	if (LL_RCC_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Preserve every other APB1 clock gate while setting only the requested mask.
	apb1enrImage = LL_RCC_ReadAPB1ENR();
	apb1enrImage |= mask;
	LL_RCC_WriteAPB1ENR(apb1enrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_DisableAPB1Clock(const uint32_t mask)
{
	// Local Variable
	reg apb1enrImage = 0x00000000UL;

	if (LL_RCC_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Preserve every other APB1 clock gate while clearing only the requested mask.
	apb1enrImage = LL_RCC_ReadAPB1ENR();
	apb1enrImage &= ~mask;
	LL_RCC_WriteAPB1ENR(apb1enrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_ForceAPB2Reset(const uint32_t mask)
{
	// Local Variable
	reg apb2rstrImage = 0x00000000UL;

	if (LL_RCC_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Preserve every other APB2 reset bit while asserting only the requested mask.
	apb2rstrImage = LL_RCC_ReadAPB2RSTR();
	apb2rstrImage |= mask;
	LL_RCC_WriteAPB2RSTR(apb2rstrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_ReleaseAPB2Reset(const uint32_t mask)
{
	// Local Variable
	reg apb2rstrImage = 0x00000000UL;

	if (LL_RCC_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Preserve every other APB2 reset bit while releasing only the requested mask.
	apb2rstrImage = LL_RCC_ReadAPB2RSTR();
	apb2rstrImage &= ~mask;
	LL_RCC_WriteAPB2RSTR(apb2rstrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_ForceAPB1Reset(const uint32_t mask)
{
	// Local Variable
	reg apb1rstrImage = 0x00000000UL;

	if (LL_RCC_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Preserve every other APB1 reset bit while asserting only the requested mask.
	apb1rstrImage = LL_RCC_ReadAPB1RSTR();
	apb1rstrImage |= mask;
	LL_RCC_WriteAPB1RSTR(apb1rstrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_ReleaseAPB1Reset(const uint32_t mask)
{
	// Local Variable
	reg apb1rstrImage = 0x00000000UL;

	if (LL_RCC_IS_MASK_VALID(mask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Preserve every other APB1 reset bit while releasing only the requested mask.
	apb1rstrImage = LL_RCC_ReadAPB1RSTR();
	apb1rstrImage &= ~mask;
	LL_RCC_WriteAPB1RSTR(apb1rstrImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_PulseAPB2Reset(const uint32_t mask)
{
	ASSERT_DRIVER_STATUS(LL_RCC_ForceAPB2Reset(mask));
	ASSERT_DRIVER_STATUS(LL_RCC_ReleaseAPB2Reset(mask));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t LL_RCC_PulseAPB1Reset(const uint32_t mask)
{
	ASSERT_DRIVER_STATUS(LL_RCC_ForceAPB1Reset(mask));
	ASSERT_DRIVER_STATUS(LL_RCC_ReleaseAPB1Reset(mask));
	return DRIVER_STATUS_SUCCESS;
}

/** @} */ // RCC_02_LL_05_ClockReset
