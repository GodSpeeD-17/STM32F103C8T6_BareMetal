/**
 * @file	rcc.c
 * @author	Shrey Shah
 * @brief	RCC Driver Source File
 * @version	v2.2
 * @date	20-03-2026
 */

/*---------------------------------------------- Includes ----------------------------------------------*/
#include "rcc.h"

/*---------------------------------------------- Macros ----------------------------------------------*/
#define RCC_READY_TIMEOUT					((uint32_t) 1000UL)
#define RCC_DRIVER_INVALID_FIELD			((uint32_t) 0xFFFFFFFFUL)

/*---------------------------------------------- Local Helpers ----------------------------------------------*/
static driver_status_t _RCC_WaitReadyStatus(driver_status_t (*readyGetter)(void), const driver_status_t targetStatus)
{
	uint32_t timeout = RCC_READY_TIMEOUT;

	while (timeout > 0x00UL)
	{
		if (readyGetter() == targetStatus)
		{
			return DRIVER_STATUS_SUCCESS;
		}

		timeout--;
	}

	return DRIVER_STATUS_ERROR_TIMEOUT;
}

static driver_status_t _RCC_WaitSystemClockSource(const rcc_system_clock_t source)
{
	rcc_ll_sysclk_status_t	status = RCC_LL_SYSCLK_STATUS_HSI;
	uint32_t				timeout = RCC_READY_TIMEOUT;

	while (timeout > 0x00UL)
	{
		if (RCC_LL_GetSystemClockStatus(&status) != DRIVER_STATUS_SUCCESS)
		{
			return DRIVER_STATUS_ERROR;
		}

		if (((source == RCC_SYS_CLK_HSI) && (status == RCC_LL_SYSCLK_STATUS_HSI)) ||
			((source == RCC_SYS_CLK_HSE) && (status == RCC_LL_SYSCLK_STATUS_HSE)) ||
			((source == RCC_SYS_CLK_PLL) && (status == RCC_LL_SYSCLK_STATUS_PLL)))
		{
			return DRIVER_STATUS_SUCCESS;
		}

		timeout--;
	}

	return DRIVER_STATUS_ERROR_TIMEOUT;
}

static uint32_t _RCC_MapSystemClockSource(const rcc_system_clock_t source)
{
	switch (source)
	{
		case RCC_SYS_CLK_HSI:
		{
			return RCC_LL_SYSCLK_SRC_HSI;
		}
		case RCC_SYS_CLK_HSE:
		{
			return RCC_LL_SYSCLK_SRC_HSE;
		}
		case RCC_SYS_CLK_PLL:
		{
			return RCC_LL_SYSCLK_SRC_PLL;
		}
		default:
		{
			return RCC_DRIVER_INVALID_FIELD;
		}
	}
}

static uint32_t _RCC_MapPLLSource(const rcc_pll_src_t source)
{
	switch (source)
	{
		case RCC_PLL_SRC_HSI:
		{
			return RCC_LL_PLL_SRC_HSI_DIV2;
		}
		case RCC_PLL_SRC_HSE:
		{
			return RCC_LL_PLL_SRC_HSE;
		}
		default:
		{
			return RCC_DRIVER_INVALID_FIELD;
		}
	}
}

static uint32_t _RCC_MapPLLHSEDivider(const rcc_pll_src_psc_t divider)
{
	switch (divider)
	{
		case RCC_PLL_SRC_HSE_DIV_1:
		{
			return RCC_LL_PLL_HSE_DIV_1;
		}
		case RCC_PLL_SRC_HSE_DIV_2:
		{
			return RCC_LL_PLL_HSE_DIV_2;
		}
		default:
		{
			return RCC_DRIVER_INVALID_FIELD;
		}
	}
}

static uint32_t _RCC_MapPLLMultiplier(const rcc_pll_mul_t multiplier)
{
	switch (multiplier)
	{
		case RCC_PLL_MUL_2:
		{
			return RCC_LL_PLL_MUL_2;
		}
		case RCC_PLL_MUL_3:
		{
			return RCC_LL_PLL_MUL_3;
		}
		case RCC_PLL_MUL_4:
		{
			return RCC_LL_PLL_MUL_4;
		}
		case RCC_PLL_MUL_5:
		{
			return RCC_LL_PLL_MUL_5;
		}
		case RCC_PLL_MUL_6:
		{
			return RCC_LL_PLL_MUL_6;
		}
		case RCC_PLL_MUL_7:
		{
			return RCC_LL_PLL_MUL_7;
		}
		case RCC_PLL_MUL_8:
		{
			return RCC_LL_PLL_MUL_8;
		}
		case RCC_PLL_MUL_9:
		{
			return RCC_LL_PLL_MUL_9;
		}
		case RCC_PLL_MUL_10:
		{
			return RCC_LL_PLL_MUL_10;
		}
		case RCC_PLL_MUL_11:
		{
			return RCC_LL_PLL_MUL_11;
		}
		case RCC_PLL_MUL_12:
		{
			return RCC_LL_PLL_MUL_12;
		}
		case RCC_PLL_MUL_13:
		{
			return RCC_LL_PLL_MUL_13;
		}
		case RCC_PLL_MUL_14:
		{
			return RCC_LL_PLL_MUL_14;
		}
		case RCC_PLL_MUL_15:
		{
			return RCC_LL_PLL_MUL_15;
		}
		case RCC_PLL_MUL_16:
		{
			return RCC_LL_PLL_MUL_16;
		}
		default:
		{
			return RCC_DRIVER_INVALID_FIELD;
		}
	}
}

static uint32_t _RCC_MapAHBPrescaler(const rcc_bus_prescaler_t divider)
{
	switch (divider)
	{
		case RCC_AHB_DIV_1:
		{
			return RCC_LL_AHB_DIV_1;
		}
		case RCC_AHB_DIV_2:
		{
			return RCC_LL_AHB_DIV_2;
		}
		case RCC_AHB_DIV_4:
		{
			return RCC_LL_AHB_DIV_4;
		}
		case RCC_AHB_DIV_8:
		{
			return RCC_LL_AHB_DIV_8;
		}
		case RCC_AHB_DIV_16:
		{
			return RCC_LL_AHB_DIV_16;
		}
		case RCC_AHB_DIV_64:
		{
			return RCC_LL_AHB_DIV_64;
		}
		case RCC_AHB_DIV_128:
		{
			return RCC_LL_AHB_DIV_128;
		}
		case RCC_AHB_DIV_256:
		{
			return RCC_LL_AHB_DIV_256;
		}
		case RCC_AHB_DIV_512:
		{
			return RCC_LL_AHB_DIV_512;
		}
		default:
		{
			return RCC_DRIVER_INVALID_FIELD;
		}
	}
}

static uint32_t _RCC_MapAPBPrescaler(const rcc_bus_prescaler_t divider)
{
	switch (divider)
	{
		case RCC_APB1_DIV_1:
		{
			return RCC_LL_APB_DIV_1;
		}
		case RCC_APB1_DIV_2:
		{
			return RCC_LL_APB_DIV_2;
		}
		case RCC_APB1_DIV_4:
		{
			return RCC_LL_APB_DIV_4;
		}
		case RCC_APB1_DIV_8:
		{
			return RCC_LL_APB_DIV_8;
		}
		case RCC_APB1_DIV_16:
		{
			return RCC_LL_APB_DIV_16;
		}
		default:
		{
			return RCC_DRIVER_INVALID_FIELD;
		}
	}
}

static uint32_t _RCC_MapADCPrescaler(const rcc_component_prescaler_t divider)
{
	switch (divider)
	{
		case RCC_ADC_DIV_2:
		{
			return RCC_LL_ADC_DIV_2;
		}
		case RCC_ADC_DIV_4:
		{
			return RCC_LL_ADC_DIV_4;
		}
		case RCC_ADC_DIV_6:
		{
			return RCC_LL_ADC_DIV_6;
		}
		case RCC_ADC_DIV_8:
		{
			return RCC_LL_ADC_DIV_8;
		}
		default:
		{
			return RCC_DRIVER_INVALID_FIELD;
		}
	}
}

static uint32_t _RCC_MapUSBPrescaler(const rcc_component_prescaler_t divider)
{
	switch (divider)
	{
		case RCC_USB_DIV_1_5:
		{
			return RCC_LL_USB_DIV_1_5;
		}
		case RCC_USB_DIV_1:
		{
			return RCC_LL_USB_DIV_1;
		}
		default:
		{
			return RCC_DRIVER_INVALID_FIELD;
		}
	}
}

static rcc_system_clock_t _RCC_DecodeSystemClockStatus(const rcc_ll_sysclk_status_t status)
{
	switch (status)
	{
		case RCC_LL_SYSCLK_STATUS_HSI:
		{
			return RCC_SYS_CLK_HSI;
		}
		case RCC_LL_SYSCLK_STATUS_HSE:
		{
			return RCC_SYS_CLK_HSE;
		}
		case RCC_LL_SYSCLK_STATUS_PLL:
		{
			return RCC_SYS_CLK_PLL;
		}
		default:
		{
			return RCC_SYS_CLK_HSI;
		}
	}
}

static rcc_bus_prescaler_t _RCC_DecodeAHBPrescaler(const rcc_ll_ahb_prescaler_t prescaler)
{
	switch (prescaler)
	{
		case RCC_LL_AHB_DIV_1:
		{
			return RCC_AHB_DIV_1;
		}
		case RCC_LL_AHB_DIV_2:
		{
			return RCC_AHB_DIV_2;
		}
		case RCC_LL_AHB_DIV_4:
		{
			return RCC_AHB_DIV_4;
		}
		case RCC_LL_AHB_DIV_8:
		{
			return RCC_AHB_DIV_8;
		}
		case RCC_LL_AHB_DIV_16:
		{
			return RCC_AHB_DIV_16;
		}
		case RCC_LL_AHB_DIV_64:
		{
			return RCC_AHB_DIV_64;
		}
		case RCC_LL_AHB_DIV_128:
		{
			return RCC_AHB_DIV_128;
		}
		case RCC_LL_AHB_DIV_256:
		{
			return RCC_AHB_DIV_256;
		}
		case RCC_LL_AHB_DIV_512:
		{
			return RCC_AHB_DIV_512;
		}
		default:
		{
			return RCC_AHB_DIV_1;
		}
	}
}

static rcc_bus_prescaler_t _RCC_DecodeAPBPrescaler(const rcc_ll_apb_prescaler_t prescaler)
{
	switch (prescaler)
	{
		case RCC_LL_APB_DIV_1:
		{
			return RCC_APB1_DIV_1;
		}
		case RCC_LL_APB_DIV_2:
		{
			return RCC_APB1_DIV_2;
		}
		case RCC_LL_APB_DIV_4:
		{
			return RCC_APB1_DIV_4;
		}
		case RCC_LL_APB_DIV_8:
		{
			return RCC_APB1_DIV_8;
		}
		case RCC_LL_APB_DIV_16:
		{
			return RCC_APB1_DIV_16;
		}
		default:
		{
			return 1U;
		}
	}
}

static rcc_component_prescaler_t _RCC_DecodeADCPrescaler(const rcc_ll_adc_prescaler_t prescaler)
{
	switch (prescaler)
	{
		case RCC_LL_ADC_DIV_2:
		{
			return RCC_ADC_DIV_2;
		}
		case RCC_LL_ADC_DIV_4:
		{
			return RCC_ADC_DIV_4;
		}
		case RCC_LL_ADC_DIV_6:
		{
			return RCC_ADC_DIV_6;
		}
		case RCC_LL_ADC_DIV_8:
		{
			return RCC_ADC_DIV_8;
		}
		default:
		{
			return RCC_ADC_DIV_2;
		}
	}
}

static rcc_component_prescaler_t _RCC_DecodeUSBPrescaler(const rcc_ll_usb_prescaler_t prescaler)
{
	if (prescaler == RCC_LL_USB_DIV_1)
	{
		return RCC_USB_DIV_1;
	}
	else
	{
		return RCC_USB_DIV_1_5;
	}
}

static _rcc_freq_t _RCC_ComputePLLInputFreq(const rcc_clock_tree_config_t* const clockTree)
{
	if (clockTree->system.pll.source == RCC_PLL_SRC_HSI)
	{
		return (_RCC_HSI_FREQ >> 1);
	}
	else
	{
		if (clockTree->system.pll.source_prescaler == RCC_PLL_SRC_HSE_DIV_2)
		{
			return (_RCC_HSE_FREQ >> 1);
		}
		else
		{
			return _RCC_HSE_FREQ;
		}
	}
}

static _rcc_freq_t _RCC_ComputeSYSCLK(const rcc_clock_tree_config_t* const clockTree)
{
	switch (clockTree->system.clk_src)
	{
		case RCC_SYS_CLK_HSI:
		{
			return _RCC_HSI_FREQ;
		}
		case RCC_SYS_CLK_HSE:
		{
			return _RCC_HSE_FREQ;
		}
		case RCC_SYS_CLK_PLL:
		{
			return (_RCC_ComputePLLInputFreq(clockTree) * (_rcc_freq_t) clockTree->system.pll.multiplication_factor);
		}
		default:
		{
			return 0x00UL;
		}
	}
}

static _rcc_freq_t _RCC_ComputeHCLK(const rcc_clock_tree_config_t* const clockTree)
{
	return (_RCC_ComputeSYSCLK(clockTree) / (_rcc_freq_t) clockTree->bus.AHB);
}

static _rcc_freq_t _RCC_ComputePCLK1(const rcc_clock_tree_config_t* const clockTree)
{
	return (_RCC_ComputeHCLK(clockTree) / (_rcc_freq_t) clockTree->bus.APB1);
}

static _rcc_freq_t _RCC_ComputePCLK2(const rcc_clock_tree_config_t* const clockTree)
{
	return (_RCC_ComputeHCLK(clockTree) / (_rcc_freq_t) clockTree->bus.APB2);
}

static _rcc_freq_t _RCC_ComputeADCCLK(const rcc_clock_tree_config_t* const clockTree)
{
	return (_RCC_ComputePCLK2(clockTree) / (_rcc_freq_t) clockTree->component.ADC);
}

static _rcc_freq_t _RCC_ComputeUSBCLK(const rcc_clock_tree_config_t* const clockTree)
{
	const _rcc_freq_t pllClock = _RCC_ComputePLLInputFreq(clockTree) * (_rcc_freq_t) clockTree->system.pll.multiplication_factor;

	if (clockTree->system.clk_src != RCC_SYS_CLK_PLL)
	{
		return 0x00UL;
	}

	if (clockTree->component.USB == RCC_USB_DIV_1)
	{
		return pllClock;
	}
	else
	{
		return ((pllClock << 1) / 3U);
	}
}

/*---------------------------------------------- Driver Clock Gate and Reset APIs ----------------------------------------------*/
driver_status_t RCC_AHB_ClockEnable(const uint32_t clockMask)
{
	return RCC_LL_AHB_EnableClock(clockMask);
}

driver_status_t RCC_AHB_ClockDisable(const uint32_t clockMask)
{
	return RCC_LL_AHB_DisableClock(clockMask);
}

driver_status_t RCC_APB2_ClockEnable(const uint32_t clockMask)
{
	return RCC_LL_APB2_EnableClock(clockMask);
}

driver_status_t RCC_APB2_ClockDisable(const uint32_t clockMask)
{
	return RCC_LL_APB2_DisableClock(clockMask);
}

driver_status_t RCC_APB1_ClockEnable(const uint32_t clockMask)
{
	return RCC_LL_APB1_EnableClock(clockMask);
}

driver_status_t RCC_APB1_ClockDisable(const uint32_t clockMask)
{
	return RCC_LL_APB1_DisableClock(clockMask);
}

driver_status_t RCC_APB2_ResetPulse(const uint32_t resetMask)
{
	return RCC_LL_APB2_ResetPulse(resetMask);
}

driver_status_t RCC_APB1_ResetPulse(const uint32_t resetMask)
{
	return RCC_LL_APB1_ResetPulse(resetMask);
}

/*---------------------------------------------- Driver Configuration APIs ----------------------------------------------*/
driver_status_t RCC_ValidateConfig(const rcc_config_t* const cfg)
{
	const rcc_clock_tree_config_t* clockTree = NULL;
	_rcc_freq_t sysClk = 0x00UL;
	_rcc_freq_t hClk = 0x00UL;
	_rcc_freq_t pClk1 = 0x00UL;
	_rcc_freq_t pClk2 = 0x00UL;
	_rcc_freq_t adcClk = 0x00UL;
	_rcc_freq_t usbClk = 0x00UL;

	if (cfg == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	clockTree = &cfg->clock_tree;

	if (_RCC_MapSystemClockSource(clockTree->system.clk_src) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_MapAHBPrescaler(clockTree->bus.AHB) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_MapAPBPrescaler(clockTree->bus.APB1) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_MapAPBPrescaler(clockTree->bus.APB2) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_MapADCPrescaler(clockTree->component.ADC) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_MapUSBPrescaler(clockTree->component.USB) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if ((cfg->flash.latency > RCC_FLASH_LATENCY_2) || (cfg->flash.prefetch > RCC_FLASH_PREFETCH_ENABLE))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (clockTree->system.clk_src == RCC_SYS_CLK_PLL)
	{
		if (_RCC_MapPLLSource(clockTree->system.pll.source) == RCC_DRIVER_INVALID_FIELD)
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}

		if (_RCC_MapPLLMultiplier(clockTree->system.pll.multiplication_factor) == RCC_DRIVER_INVALID_FIELD)
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}

		if (clockTree->system.pll.source == RCC_PLL_SRC_HSI)
		{
			if (clockTree->system.pll.source_prescaler != RCC_PLL_SRC_HSI_DIV_2)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}
		}
		else
		{
			if (_RCC_MapPLLHSEDivider(clockTree->system.pll.source_prescaler) == RCC_DRIVER_INVALID_FIELD)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}
		}
	}

	sysClk = _RCC_ComputeSYSCLK(clockTree);
	hClk = _RCC_ComputeHCLK(clockTree);
	pClk1 = _RCC_ComputePCLK1(clockTree);
	pClk2 = _RCC_ComputePCLK2(clockTree);
	adcClk = _RCC_ComputeADCCLK(clockTree);
	usbClk = _RCC_ComputeUSBCLK(clockTree);

	if (sysClk > _RCC_SYSCLK_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (hClk > _RCC_HCLK_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (pClk1 > _RCC_PCLK1_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (pClk2 > _RCC_PCLK2_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (adcClk > _RCC_ADCCLK_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if ((clockTree->system.clk_src == RCC_SYS_CLK_PLL) && (usbClk != 0x00UL) && (usbClk != _RCC_USBCLK_TARGET_FREQ))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if ((sysClk <= 24000000UL) && (cfg->flash.latency != RCC_FLASH_LATENCY_0))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if ((sysClk > 24000000UL) && (sysClk <= 48000000UL) && (cfg->flash.latency != RCC_FLASH_LATENCY_1))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if ((sysClk > 48000000UL) && (cfg->flash.latency != RCC_FLASH_LATENCY_2))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_ConfigFlash(const rcc_flash_config_t* const flash)
{
	uint32_t flashLatency = FLASH_ACR_LATENCY_0;

	if (flash == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (flash->latency)
	{
		case RCC_FLASH_LATENCY_0:
		{
			flashLatency = FLASH_ACR_LATENCY_0;
			break;
		}
		case RCC_FLASH_LATENCY_1:
		{
			flashLatency = FLASH_ACR_LATENCY_1;
			break;
		}
		case RCC_FLASH_LATENCY_2:
		{
			flashLatency = FLASH_ACR_LATENCY_2;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	REGOPS_MODIFY(&FLASH->ACR.REG, FLASH_ACR_LATENCY_Msk, flashLatency);

	if (flash->prefetch == RCC_FLASH_PREFETCH_ENABLE)
	{
		REGOPS_SET(&FLASH->ACR.REG, FLASH_ACR_PRFTBE);
	}
	else
	{
		REGOPS_CLEAR(&FLASH->ACR.REG, FLASH_ACR_PRFTBE);
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_ConfigBusPrescaler(const rcc_bus_config_t* const busCfg)
{
	uint32_t ahbPrescaler = 0x00UL;
	uint32_t apb1Prescaler = 0x00UL;
	uint32_t apb2Prescaler = 0x00UL;

	if (busCfg == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ahbPrescaler = _RCC_MapAHBPrescaler(busCfg->AHB);
	apb1Prescaler = _RCC_MapAPBPrescaler(busCfg->APB1);
	apb2Prescaler = _RCC_MapAPBPrescaler(busCfg->APB2);

	if ((ahbPrescaler == RCC_DRIVER_INVALID_FIELD) || (apb1Prescaler == RCC_DRIVER_INVALID_FIELD) || (apb2Prescaler == RCC_DRIVER_INVALID_FIELD))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	DRIVER_RETURN_IF_NOT_SUCCESS(RCC_LL_SetAHBPrescaler((rcc_ll_ahb_prescaler_t) ahbPrescaler));
	DRIVER_RETURN_IF_NOT_SUCCESS(RCC_LL_SetAPB1Prescaler((rcc_ll_apb_prescaler_t) apb1Prescaler));
	DRIVER_RETURN_IF_NOT_SUCCESS(RCC_LL_SetAPB2Prescaler((rcc_ll_apb_prescaler_t) apb2Prescaler));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_ConfigComponentPrescaler(const rcc_component_config_t* const componentCfg)
{
	uint32_t adcPrescaler = 0x00UL;
	uint32_t usbPrescaler = 0x00UL;

	if (componentCfg == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	adcPrescaler = _RCC_MapADCPrescaler(componentCfg->ADC);
	usbPrescaler = _RCC_MapUSBPrescaler(componentCfg->USB);

	if ((adcPrescaler == RCC_DRIVER_INVALID_FIELD) || (usbPrescaler == RCC_DRIVER_INVALID_FIELD))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	DRIVER_RETURN_IF_NOT_SUCCESS(RCC_LL_SetADCPrescaler((rcc_ll_adc_prescaler_t) adcPrescaler));
	DRIVER_RETURN_IF_NOT_SUCCESS(RCC_LL_SetUSBPrescaler((rcc_ll_usb_prescaler_t) usbPrescaler));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_SwitchClockSourceToHSI(void)
{
	RCC_LL_HSI_Enable();
	DRIVER_RETURN_IF_NOT_SUCCESS(_RCC_WaitReadyStatus(RCC_LL_HSI_GetReadyStatus, DRIVER_STATUS_READY));
	DRIVER_RETURN_IF_NOT_SUCCESS(RCC_LL_SetSystemClockSource(RCC_LL_SYSCLK_SRC_HSI));
	DRIVER_RETURN_IF_NOT_SUCCESS(_RCC_WaitSystemClockSource(RCC_SYS_CLK_HSI));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_SwitchClockSourceToHSE(void)
{
	RCC_LL_HSE_Enable();
	DRIVER_RETURN_IF_NOT_SUCCESS(_RCC_WaitReadyStatus(RCC_LL_HSE_GetReadyStatus, DRIVER_STATUS_READY));
	DRIVER_RETURN_IF_NOT_SUCCESS(RCC_LL_SetSystemClockSource(RCC_LL_SYSCLK_SRC_HSE));
	DRIVER_RETURN_IF_NOT_SUCCESS(_RCC_WaitSystemClockSource(RCC_SYS_CLK_HSE));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_SwitchClockSourceToPLL(void)
{
	if (RCC_LL_PLL_GetReadyStatus() != DRIVER_STATUS_READY)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	DRIVER_RETURN_IF_NOT_SUCCESS(RCC_LL_SetSystemClockSource(RCC_LL_SYSCLK_SRC_PLL));
	DRIVER_RETURN_IF_NOT_SUCCESS(_RCC_WaitSystemClockSource(RCC_SYS_CLK_PLL));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_ConfigClockTree(const rcc_clock_tree_config_t* const clockTree)
{
	rcc_system_clock_t activeSource = RCC_SYS_CLK_HSI;
	uint32_t pllSource = 0x00UL;
	uint32_t pllDivider = 0x00UL;
	uint32_t pllMultiplier = 0x00UL;

	if (clockTree == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	activeSource = RCC_GetSysClkSrc();
	RCC_LL_HSI_Enable();
	DRIVER_RETURN_IF_NOT_SUCCESS(_RCC_WaitReadyStatus(RCC_LL_HSI_GetReadyStatus, DRIVER_STATUS_READY));

	if (activeSource == RCC_SYS_CLK_PLL)
	{
		DRIVER_RETURN_IF_NOT_SUCCESS(RCC_SwitchClockSourceToHSI());
	}

	if ((clockTree->system.clk_src == RCC_SYS_CLK_HSE) ||
		((clockTree->system.clk_src == RCC_SYS_CLK_PLL) && (clockTree->system.pll.source == RCC_PLL_SRC_HSE)))
	{
		RCC_LL_HSE_Enable();
		DRIVER_RETURN_IF_NOT_SUCCESS(_RCC_WaitReadyStatus(RCC_LL_HSE_GetReadyStatus, DRIVER_STATUS_READY));
	}

	if (RCC_LL_PLL_GetReadyStatus() == DRIVER_STATUS_READY)
	{
		RCC_LL_PLL_Disable();
		DRIVER_RETURN_IF_NOT_SUCCESS(_RCC_WaitReadyStatus(RCC_LL_PLL_GetReadyStatus, DRIVER_STATUS_OFF));
	}

	DRIVER_RETURN_IF_NOT_SUCCESS(RCC_ConfigBusPrescaler(&clockTree->bus));
	DRIVER_RETURN_IF_NOT_SUCCESS(RCC_ConfigComponentPrescaler(&clockTree->component));

	if (clockTree->system.clk_src == RCC_SYS_CLK_PLL)
	{
		pllSource = _RCC_MapPLLSource(clockTree->system.pll.source);
		pllMultiplier = _RCC_MapPLLMultiplier(clockTree->system.pll.multiplication_factor);

		if ((pllSource == RCC_DRIVER_INVALID_FIELD) || (pllMultiplier == RCC_DRIVER_INVALID_FIELD))
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}

		DRIVER_RETURN_IF_NOT_SUCCESS(RCC_LL_SetPLLSource((rcc_ll_pll_src_t) pllSource));

		if (clockTree->system.pll.source == RCC_PLL_SRC_HSE)
		{
			pllDivider = _RCC_MapPLLHSEDivider(clockTree->system.pll.source_prescaler);
			if (pllDivider == RCC_DRIVER_INVALID_FIELD)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}

			DRIVER_RETURN_IF_NOT_SUCCESS(RCC_LL_SetPLLHSEDivider((rcc_ll_pll_hse_div_t) pllDivider));
		}

		DRIVER_RETURN_IF_NOT_SUCCESS(RCC_LL_SetPLLMultiplier((rcc_ll_pll_mul_t) pllMultiplier));
		RCC_LL_PLL_Enable();
		DRIVER_RETURN_IF_NOT_SUCCESS(_RCC_WaitReadyStatus(RCC_LL_PLL_GetReadyStatus, DRIVER_STATUS_READY));
	}

	switch (clockTree->system.clk_src)
	{
		case RCC_SYS_CLK_HSI:
		{
			DRIVER_RETURN_IF_NOT_SUCCESS(RCC_SwitchClockSourceToHSI());
			break;
		}
		case RCC_SYS_CLK_HSE:
		{
			DRIVER_RETURN_IF_NOT_SUCCESS(RCC_SwitchClockSourceToHSE());
			break;
		}
		case RCC_SYS_CLK_PLL:
		{
			DRIVER_RETURN_IF_NOT_SUCCESS(RCC_SwitchClockSourceToPLL());
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}
driver_status_t RCC_Config(const rcc_config_t* const cfg)
{
	driver_status_t status = DRIVER_STATUS_SUCCESS;

	status = RCC_ValidateConfig(cfg);
	if (status != DRIVER_STATUS_SUCCESS)
	{
		return status;
	}

	DRIVER_RETURN_IF_NOT_SUCCESS(RCC_ConfigFlash(&cfg->flash));
	DRIVER_RETURN_IF_NOT_SUCCESS(RCC_ConfigClockTree(&cfg->clock_tree));
	return DRIVER_STATUS_SUCCESS;
}

void RCC_72MHz_LoadDefaultConfig(rcc_config_t* const cfg)
{
	if (cfg == NULL)
	{
		return;
	}

	cfg->flash.latency = RCC_FLASH_LATENCY_2;
	cfg->flash.prefetch = RCC_FLASH_PREFETCH_ENABLE;

	cfg->clock_tree.system.clk_src = RCC_SYS_CLK_PLL;
	cfg->clock_tree.system.pll.source = RCC_PLL_SRC_HSE;
	cfg->clock_tree.system.pll.source_prescaler = RCC_PLL_SRC_HSE_DIV_1;
	cfg->clock_tree.system.pll.multiplication_factor = RCC_PLL_MUL_9;

	cfg->clock_tree.bus.AHB = RCC_AHB_DIV_1;
	cfg->clock_tree.bus.APB1 = RCC_APB1_DIV_2;
	cfg->clock_tree.bus.APB2 = RCC_APB2_DIV_1;

	cfg->clock_tree.component.ADC = RCC_ADC_DIV_6;
	cfg->clock_tree.component.USB = RCC_USB_DIV_1_5;
}

driver_status_t RCC_Config_72MHz(void)
{
	rcc_config_t cfg;

	RCC_72MHz_LoadDefaultConfig(&cfg);
	return RCC_Config(&cfg);
}

/*---------------------------------------------- Driver Status and Frequency APIs ----------------------------------------------*/
rcc_system_clock_t RCC_GetSysClkSrc(void)
{
	rcc_ll_sysclk_status_t status = RCC_LL_SYSCLK_STATUS_HSI;

	if (RCC_LL_GetSystemClockStatus(&status) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_SYS_CLK_HSI;
	}

	return _RCC_DecodeSystemClockStatus(status);
}

rcc_pll_src_t RCC_GetPLLSource(void)
{
	rcc_ll_pll_src_t source = RCC_LL_PLL_SRC_HSI_DIV2;

	if (RCC_LL_GetPLLSource(&source) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_PLL_SRC_HSI;
	}

	if (source == RCC_LL_PLL_SRC_HSE)
	{
		return RCC_PLL_SRC_HSE;
	}
	else
	{
		return RCC_PLL_SRC_HSI;
	}
}

rcc_pll_src_psc_t RCC_GetPLLSourcePrescaler(void)
{
	rcc_ll_pll_hse_div_t divider = RCC_LL_PLL_HSE_DIV_1;

	if (RCC_GetPLLSource() == RCC_PLL_SRC_HSI)
	{
		return RCC_PLL_SRC_HSI_DIV_2;
	}

	if (RCC_LL_GetPLLHSEDivider(&divider) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_PLL_SRC_HSE_DIV_1;
	}

	if (divider == RCC_LL_PLL_HSE_DIV_2)
	{
		return RCC_PLL_SRC_HSE_DIV_2;
	}
	else
	{
		return RCC_PLL_SRC_HSE_DIV_1;
	}
}

rcc_pll_mul_t RCC_GetPLLMultiplier(void)
{
	rcc_ll_pll_mul_t multiplier = RCC_LL_PLL_MUL_2;

	if (RCC_LL_GetPLLMultiplier(&multiplier) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_PLL_MUL_2;
	}

	switch (multiplier)
	{
		case RCC_LL_PLL_MUL_2:
		{
			return RCC_PLL_MUL_2;
		}
		case RCC_LL_PLL_MUL_3:
		{
			return RCC_PLL_MUL_3;
		}
		case RCC_LL_PLL_MUL_4:
		{
			return RCC_PLL_MUL_4;
		}
		case RCC_LL_PLL_MUL_5:
		{
			return RCC_PLL_MUL_5;
		}
		case RCC_LL_PLL_MUL_6:
		{
			return RCC_PLL_MUL_6;
		}
		case RCC_LL_PLL_MUL_7:
		{
			return RCC_PLL_MUL_7;
		}
		case RCC_LL_PLL_MUL_8:
		{
			return RCC_PLL_MUL_8;
		}
		case RCC_LL_PLL_MUL_9:
		{
			return RCC_PLL_MUL_9;
		}
		case RCC_LL_PLL_MUL_10:
		{
			return RCC_PLL_MUL_10;
		}
		case RCC_LL_PLL_MUL_11:
		{
			return RCC_PLL_MUL_11;
		}
		case RCC_LL_PLL_MUL_12:
		{
			return RCC_PLL_MUL_12;
		}
		case RCC_LL_PLL_MUL_13:
		{
			return RCC_PLL_MUL_13;
		}
		case RCC_LL_PLL_MUL_14:
		{
			return RCC_PLL_MUL_14;
		}
		case RCC_LL_PLL_MUL_15:
		{
			return RCC_PLL_MUL_15;
		}
		case RCC_LL_PLL_MUL_16:
		{
			return RCC_PLL_MUL_16;
		}
		default:
		{
			return RCC_PLL_MUL_2;
		}
	}
}

_rcc_freq_t RCC_GetCoreClockFreq(void)
{
	_rcc_freq_t pllInput = 0x00UL;

	switch (RCC_GetSysClkSrc())
	{
		case RCC_SYS_CLK_HSI:
		{
			return _RCC_HSI_FREQ;
		}
		case RCC_SYS_CLK_HSE:
		{
			return _RCC_HSE_FREQ;
		}
		case RCC_SYS_CLK_PLL:
		{
			pllInput = (RCC_GetPLLSource() == RCC_PLL_SRC_HSE) ? _RCC_HSE_FREQ : (_RCC_HSI_FREQ >> 1);
			if (RCC_GetPLLSourcePrescaler() == RCC_PLL_SRC_HSE_DIV_2)
			{
				pllInput >>= 1;
			}
			return (pllInput * (_rcc_freq_t) RCC_GetPLLMultiplier());
		}
		default:
		{
			return _RCC_HSI_FREQ;
		}
	}
}

rcc_bus_prescaler_t RCC_GetBusPrescaler(const rcc_bus_t bus)
{
	rcc_ll_ahb_prescaler_t ahbPrescaler = RCC_LL_AHB_DIV_1;
	rcc_ll_apb_prescaler_t apbPrescaler = RCC_LL_APB_DIV_1;

	switch (bus)
	{
		case RCC_AHB_BUS:
		{
			if (RCC_LL_GetAHBPrescaler(&ahbPrescaler) != DRIVER_STATUS_SUCCESS)
			{
				return RCC_AHB_DIV_1;
			}
			return _RCC_DecodeAHBPrescaler(ahbPrescaler);
		}
		case RCC_APB1_BUS:
		{
			if (RCC_LL_GetAPB1Prescaler(&apbPrescaler) != DRIVER_STATUS_SUCCESS)
			{
				return RCC_APB1_DIV_1;
			}
			return _RCC_DecodeAPBPrescaler(apbPrescaler);
		}
		case RCC_APB2_BUS:
		{
			if (RCC_LL_GetAPB2Prescaler(&apbPrescaler) != DRIVER_STATUS_SUCCESS)
			{
				return RCC_APB2_DIV_1;
			}
			return _RCC_DecodeAPBPrescaler(apbPrescaler);
		}
		default:
		{
			return 1U;
		}
	}
}

_rcc_freq_t RCC_GetBusFreq(const rcc_bus_t bus)
{
	const _rcc_freq_t sysClk = RCC_GetCoreClockFreq();
	const _rcc_freq_t hClk = (sysClk / (_rcc_freq_t) RCC_GetBusPrescaler(RCC_AHB_BUS));

	switch (bus)
	{
		case RCC_AHB_BUS:
		{
			return hClk;
		}
		case RCC_APB1_BUS:
		{
			return (hClk / (_rcc_freq_t) RCC_GetBusPrescaler(RCC_APB1_BUS));
		}
		case RCC_APB2_BUS:
		{
			return (hClk / (_rcc_freq_t) RCC_GetBusPrescaler(RCC_APB2_BUS));
		}
		default:
		{
			return hClk;
		}
	}
}

_rcc_freq_t RCC_GetADCFreq(void)
{
	rcc_ll_adc_prescaler_t adcPrescaler = RCC_LL_ADC_DIV_2;

	if (RCC_LL_GetADCPrescaler(&adcPrescaler) != DRIVER_STATUS_SUCCESS)
	{
		return 0x00UL;
	}

	return (RCC_GetBusFreq(RCC_APB2_BUS) / (_rcc_freq_t) _RCC_DecodeADCPrescaler(adcPrescaler));
}

_rcc_freq_t RCC_GetUSBFreq(void)
{
	rcc_ll_usb_prescaler_t usbPrescaler = RCC_LL_USB_DIV_1_5;
	const _rcc_freq_t pllClock = (RCC_GetSysClkSrc() == RCC_SYS_CLK_PLL) ? RCC_GetCoreClockFreq() : 0x00UL;

	if (pllClock == 0x00UL)
	{
		return 0x00UL;
	}

	if (RCC_LL_GetUSBPrescaler(&usbPrescaler) != DRIVER_STATUS_SUCCESS)
	{
		return 0x00UL;
	}

	if (_RCC_DecodeUSBPrescaler(usbPrescaler) == RCC_USB_DIV_1)
	{
		return pllClock;
	}
	else
	{
		return ((pllClock << 1) / 3U);
	}
}
