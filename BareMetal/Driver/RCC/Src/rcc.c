/**
 * @file rcc.c
 * @author Shrey Shah
 * @brief RCC Driver Source File
 * @version v2.1
 * @date 20-03-2026
 */

/*---------------------------------------------- Includes ----------------------------------------------*/
#include "rcc.h"

/*---------------------------------------------- Macros ----------------------------------------------*/
#define RCC_READY_TIMEOUT						((uint32_t) 0x000FFFFFUL)
#define RCC_DRIVER_INVALID_FIELD			((uint32_t) 0xFFFFFFFFUL)

/*---------------------------------------------- Local Functions ----------------------------------------------*/
static driver_status_t RCC_PrivateWaitFlag(volatile uint32_t* reg, const uint32_t mask, const bool set)
{
	uint32_t timeout = RCC_READY_TIMEOUT;
	while (timeout--)
	{
		const bool state = ((*reg) & mask) != 0x00UL;
		if (state == set) return DRIVER_STATUS_SUCCESS;
	}
	return DRIVER_STATUS_ERROR_TIMEOUT;
}

static driver_status_t RCC_PrivateWaitSystemClockSource(const rcc_system_clock_t source)
{
	uint32_t timeout = RCC_READY_TIMEOUT;
	while (timeout--)
	{
		if (RCC_GetSysClkSrc() == source) return DRIVER_STATUS_SUCCESS;
	}
	return DRIVER_STATUS_ERROR_TIMEOUT;
}

static uint32_t RCC_PrivateEncodeSystemClock(const rcc_system_clock_t source)
{
	switch (source)
	{
		case RCC_SYS_CLK_HSI: return RCC_CFGR_SW_HSI;
		case RCC_SYS_CLK_HSE: return RCC_CFGR_SW_HSE;
		case RCC_SYS_CLK_PLL: return RCC_CFGR_SW_PLL;
		default: return RCC_DRIVER_INVALID_FIELD;
	}
}

static rcc_system_clock_t RCC_PrivateDecodeSystemClock(const uint32_t cfgrReg)
{
	switch (cfgrReg & RCC_CFGR_SWS_Msk)
	{
		case RCC_CFGR_SWS_HSI: return RCC_SYS_CLK_HSI;
		case RCC_CFGR_SWS_HSE: return RCC_SYS_CLK_HSE;
		case RCC_CFGR_SWS_PLL: return RCC_SYS_CLK_PLL;
		default: return RCC_SYS_CLK_HSI;
	}
}

static uint32_t RCC_PrivateEncodeAHBPrescaler(const rcc_bus_prescaler_t divider)
{
	switch (divider)
	{
		case RCC_AHB_DIV_1: return RCC_CFGR_HPRE_DIV1;
		case RCC_AHB_DIV_2: return RCC_CFGR_HPRE_DIV2;
		case RCC_AHB_DIV_4: return RCC_CFGR_HPRE_DIV4;
		case RCC_AHB_DIV_8: return RCC_CFGR_HPRE_DIV8;
		case RCC_AHB_DIV_16: return RCC_CFGR_HPRE_DIV16;
		case RCC_AHB_DIV_64: return RCC_CFGR_HPRE_DIV64;
		case RCC_AHB_DIV_128: return RCC_CFGR_HPRE_DIV128;
		case RCC_AHB_DIV_256: return RCC_CFGR_HPRE_DIV256;
		case RCC_AHB_DIV_512: return RCC_CFGR_HPRE_DIV512;
		default: return RCC_DRIVER_INVALID_FIELD;
	}
}

static uint32_t RCC_PrivateEncodeAPBPrescaler(const rcc_bus_prescaler_t divider, const rcc_bus_t bus)
{
	const bool isApb1 = (bus == RCC_APB1_BUS);
	switch (divider)
	{
		case 1U: return isApb1 ? RCC_CFGR_PPRE1_DIV1 : RCC_CFGR_PPRE2_DIV1;
		case 2U: return isApb1 ? RCC_CFGR_PPRE1_DIV2 : RCC_CFGR_PPRE2_DIV2;
		case 4U: return isApb1 ? RCC_CFGR_PPRE1_DIV4 : RCC_CFGR_PPRE2_DIV4;
		case 8U: return isApb1 ? RCC_CFGR_PPRE1_DIV8 : RCC_CFGR_PPRE2_DIV8;
		case 16U: return isApb1 ? RCC_CFGR_PPRE1_DIV16 : RCC_CFGR_PPRE2_DIV16;
		default: return RCC_DRIVER_INVALID_FIELD;
	}
}

static rcc_bus_prescaler_t RCC_PrivateDecodeAHBPrescaler(const uint32_t cfgrReg)
{
	switch (cfgrReg & RCC_CFGR_HPRE_Msk)
	{
		case RCC_CFGR_HPRE_DIV1: return RCC_AHB_DIV_1;
		case RCC_CFGR_HPRE_DIV2: return RCC_AHB_DIV_2;
		case RCC_CFGR_HPRE_DIV4: return RCC_AHB_DIV_4;
		case RCC_CFGR_HPRE_DIV8: return RCC_AHB_DIV_8;
		case RCC_CFGR_HPRE_DIV16: return RCC_AHB_DIV_16;
		case RCC_CFGR_HPRE_DIV64: return RCC_AHB_DIV_64;
		case RCC_CFGR_HPRE_DIV128: return RCC_AHB_DIV_128;
		case RCC_CFGR_HPRE_DIV256: return RCC_AHB_DIV_256;
		case RCC_CFGR_HPRE_DIV512: return RCC_AHB_DIV_512;
		default: return RCC_AHB_DIV_1;
	}
}

static rcc_bus_prescaler_t RCC_PrivateDecodeAPB1Prescaler(const uint32_t cfgrReg)
{
	switch (cfgrReg & RCC_CFGR_PPRE1_Msk)
	{
		case RCC_CFGR_PPRE1_DIV1: return RCC_APB1_DIV_1;
		case RCC_CFGR_PPRE1_DIV2: return RCC_APB1_DIV_2;
		case RCC_CFGR_PPRE1_DIV4: return RCC_APB1_DIV_4;
		case RCC_CFGR_PPRE1_DIV8: return RCC_APB1_DIV_8;
		case RCC_CFGR_PPRE1_DIV16: return RCC_APB1_DIV_16;
		default: return RCC_APB1_DIV_1;
	}
}

static rcc_bus_prescaler_t RCC_PrivateDecodeAPB2Prescaler(const uint32_t cfgrReg)
{
	switch (cfgrReg & RCC_CFGR_PPRE2_Msk)
	{
		case RCC_CFGR_PPRE2_DIV1: return RCC_APB2_DIV_1;
		case RCC_CFGR_PPRE2_DIV2: return RCC_APB2_DIV_2;
		case RCC_CFGR_PPRE2_DIV4: return RCC_APB2_DIV_4;
		case RCC_CFGR_PPRE2_DIV8: return RCC_APB2_DIV_8;
		case RCC_CFGR_PPRE2_DIV16: return RCC_APB2_DIV_16;
		default: return RCC_APB2_DIV_1;
	}
}

static uint32_t RCC_PrivateEncodeADCPrescaler(const rcc_component_prescaler_t divider)
{
	switch (divider)
	{
		case RCC_ADC_DIV_2: return RCC_CFGR_ADCPRE_DIV2;
		case RCC_ADC_DIV_4: return RCC_CFGR_ADCPRE_DIV4;
		case RCC_ADC_DIV_6: return RCC_CFGR_ADCPRE_DIV6;
		case RCC_ADC_DIV_8: return RCC_CFGR_ADCPRE_DIV8;
		default: return RCC_DRIVER_INVALID_FIELD;
	}
}

static rcc_component_prescaler_t RCC_PrivateDecodeADCPrescaler(const uint32_t cfgrReg)
{
	switch (cfgrReg & RCC_CFGR_ADCPRE_Msk)
	{
		case RCC_CFGR_ADCPRE_DIV2: return RCC_ADC_DIV_2;
		case RCC_CFGR_ADCPRE_DIV4: return RCC_ADC_DIV_4;
		case RCC_CFGR_ADCPRE_DIV6: return RCC_ADC_DIV_6;
		case RCC_CFGR_ADCPRE_DIV8: return RCC_ADC_DIV_8;
		default: return RCC_ADC_DIV_2;
	}
}

static uint32_t RCC_PrivateEncodeUSBPrescaler(const rcc_component_prescaler_t divider)
{
	switch (divider)
	{
		case RCC_USB_DIV_1_5: return RCC_CFGR_USBPRE_DIV1_5;
		case RCC_USB_DIV_1: return RCC_CFGR_USBPRE_DIRECT;
		default: return RCC_DRIVER_INVALID_FIELD;
	}
}

static rcc_component_prescaler_t RCC_PrivateDecodeUSBPrescaler(const uint32_t cfgrReg)
{
	return ((cfgrReg & RCC_CFGR_USBPRE_Msk) == RCC_CFGR_USBPRE_DIRECT) ? RCC_USB_DIV_1 : RCC_USB_DIV_1_5;
}

static uint32_t RCC_PrivateEncodePLLMultiplier(const rcc_pll_mul_t multiplier)
{
	switch (multiplier)
	{
		case RCC_PLL_MUL_2: return RCC_CFGR_PLLMUL_2;
		case RCC_PLL_MUL_3: return RCC_CFGR_PLLMUL_3;
		case RCC_PLL_MUL_4: return RCC_CFGR_PLLMUL_4;
		case RCC_PLL_MUL_5: return RCC_CFGR_PLLMUL_5;
		case RCC_PLL_MUL_6: return RCC_CFGR_PLLMUL_6;
		case RCC_PLL_MUL_7: return RCC_CFGR_PLLMUL_7;
		case RCC_PLL_MUL_8: return RCC_CFGR_PLLMUL_8;
		case RCC_PLL_MUL_9: return RCC_CFGR_PLLMUL_9;
		case RCC_PLL_MUL_10: return RCC_CFGR_PLLMUL_10;
		case RCC_PLL_MUL_11: return RCC_CFGR_PLLMUL_11;
		case RCC_PLL_MUL_12: return RCC_CFGR_PLLMUL_12;
		case RCC_PLL_MUL_13: return RCC_CFGR_PLLMUL_13;
		case RCC_PLL_MUL_14: return RCC_CFGR_PLLMUL_14;
		case RCC_PLL_MUL_15: return RCC_CFGR_PLLMUL_15;
		case RCC_PLL_MUL_16: return RCC_CFGR_PLLMUL_16;
		default: return RCC_DRIVER_INVALID_FIELD;
	}
}

static rcc_pll_mul_t RCC_PrivateDecodePLLMultiplier(const uint32_t cfgrReg)
{
	switch (cfgrReg & RCC_CFGR_PLLMUL_Msk)
	{
		case RCC_CFGR_PLLMUL_2: return RCC_PLL_MUL_2;
		case RCC_CFGR_PLLMUL_3: return RCC_PLL_MUL_3;
		case RCC_CFGR_PLLMUL_4: return RCC_PLL_MUL_4;
		case RCC_CFGR_PLLMUL_5: return RCC_PLL_MUL_5;
		case RCC_CFGR_PLLMUL_6: return RCC_PLL_MUL_6;
		case RCC_CFGR_PLLMUL_7: return RCC_PLL_MUL_7;
		case RCC_CFGR_PLLMUL_8: return RCC_PLL_MUL_8;
		case RCC_CFGR_PLLMUL_9: return RCC_PLL_MUL_9;
		case RCC_CFGR_PLLMUL_10: return RCC_PLL_MUL_10;
		case RCC_CFGR_PLLMUL_11: return RCC_PLL_MUL_11;
		case RCC_CFGR_PLLMUL_12: return RCC_PLL_MUL_12;
		case RCC_CFGR_PLLMUL_13: return RCC_PLL_MUL_13;
		case RCC_CFGR_PLLMUL_14: return RCC_PLL_MUL_14;
		case RCC_CFGR_PLLMUL_15: return RCC_PLL_MUL_15;
		case RCC_CFGR_PLLMUL_16: return RCC_PLL_MUL_16;
		default: return RCC_PLL_MUL_2;
	}
}

static _rcc_freq_t RCC_PrivateComputeSYSCLK(const rcc_config_t* cfg)
{
	if (cfg->system.clk_src == RCC_SYS_CLK_HSI) return _RCC_HSI_FREQ;
	if (cfg->system.clk_src == RCC_SYS_CLK_HSE) return _RCC_HSE_FREQ;

	if (cfg->system.pll.source == RCC_PLL_SRC_HSI)
	{
		return (_RCC_HSI_FREQ >> 1) * (_rcc_freq_t) cfg->system.pll.multiplication_factor;
	}

	{
		_rcc_freq_t pllInput = _RCC_HSE_FREQ;
		if (cfg->system.pll.source_prescaler == RCC_PLL_SRC_HSE_DIV_2) pllInput >>= 1;
		return pllInput * (_rcc_freq_t) cfg->system.pll.multiplication_factor;
	}
}

static _rcc_freq_t RCC_PrivateComputeHCLK(const rcc_config_t* cfg)
{
	return (RCC_PrivateComputeSYSCLK(cfg) / (_rcc_freq_t) cfg->prescaler.bus.AHB);
}

static _rcc_freq_t RCC_PrivateComputePCLK1(const rcc_config_t* cfg)
{
	return (RCC_PrivateComputeHCLK(cfg) / (_rcc_freq_t) cfg->prescaler.bus.APB1);
}

static _rcc_freq_t RCC_PrivateComputePCLK2(const rcc_config_t* cfg)
{
	return (RCC_PrivateComputeHCLK(cfg) / (_rcc_freq_t) cfg->prescaler.bus.APB2);
}

static _rcc_freq_t RCC_PrivateComputeADCCLK(const rcc_config_t* cfg)
{
	return (RCC_PrivateComputePCLK2(cfg) / (_rcc_freq_t) cfg->prescaler.component.ADC);
}

static _rcc_freq_t RCC_PrivateComputeUSBCLK(const rcc_config_t* cfg)
{
	const _rcc_freq_t pllClk = RCC_PrivateComputeSYSCLK(cfg);
	if (cfg->system.clk_src != RCC_SYS_CLK_PLL) return 0x00UL;
	return (cfg->prescaler.component.USB == RCC_USB_DIV_1) ? pllClk : ((pllClk << 1) / 3U);
}

/*---------------------------------------------- Driver Clock Gate and Reset APIs ----------------------------------------------*/
/**
 * @brief Enables AHB peripheral clock bits
 * @param[in] clockMask Bitmask from @ref RCC_AHBENR
 * @return Driver operation status
 */
driver_status_t RCC_AHB_ClockEnable(const uint32_t clockMask)
{
	if (clockMask == 0x00UL) return DRIVER_STATUS_ERROR_INVALID_ARG;
	REGOPS_SET(&RCC->AHBENR.REG, clockMask);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Disables AHB peripheral clock bits
 * @param[in] clockMask Bitmask from @ref RCC_AHBENR
 * @return Driver operation status
 */
driver_status_t RCC_AHB_ClockDisable(const uint32_t clockMask)
{
	if (clockMask == 0x00UL) return DRIVER_STATUS_ERROR_INVALID_ARG;
	REGOPS_CLEAR(&RCC->AHBENR.REG, clockMask);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Enables APB2 peripheral clock bits
 * @param[in] clockMask Bitmask from @ref RCC_APB2ENR
 * @return Driver operation status
 */
driver_status_t RCC_APB2_ClockEnable(const uint32_t clockMask)
{
	if (clockMask == 0x00UL) return DRIVER_STATUS_ERROR_INVALID_ARG;
	REGOPS_SET(&RCC->APB2ENR.REG, clockMask);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Disables APB2 peripheral clock bits
 * @param[in] clockMask Bitmask from @ref RCC_APB2ENR
 * @return Driver operation status
 */
driver_status_t RCC_APB2_ClockDisable(const uint32_t clockMask)
{
	if (clockMask == 0x00UL) return DRIVER_STATUS_ERROR_INVALID_ARG;
	REGOPS_CLEAR(&RCC->APB2ENR.REG, clockMask);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Enables APB1 peripheral clock bits
 * @param[in] clockMask Bitmask from @ref RCC_APB1ENR
 * @return Driver operation status
 */
driver_status_t RCC_APB1_ClockEnable(const uint32_t clockMask)
{
	if (clockMask == 0x00UL) return DRIVER_STATUS_ERROR_INVALID_ARG;
	REGOPS_SET(&RCC->APB1ENR.REG, clockMask);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Disables APB1 peripheral clock bits
 * @param[in] clockMask Bitmask from @ref RCC_APB1ENR
 * @return Driver operation status
 */
driver_status_t RCC_APB1_ClockDisable(const uint32_t clockMask)
{
	if (clockMask == 0x00UL) return DRIVER_STATUS_ERROR_INVALID_ARG;
	REGOPS_CLEAR(&RCC->APB1ENR.REG, clockMask);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Pulses APB2 peripheral reset bits
 * @param[in] resetMask Bitmask from @ref RCC_APB2RSTR
 * @return Driver operation status
 */
driver_status_t RCC_APB2_ResetPulse(const uint32_t resetMask)
{
	if (resetMask == 0x00UL) return DRIVER_STATUS_ERROR_INVALID_ARG;
	REGOPS_SET(&RCC->APB2RSTR.REG, resetMask);
	REGOPS_CLEAR(&RCC->APB2RSTR.REG, resetMask);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Pulses APB1 peripheral reset bits
 * @param[in] resetMask Bitmask from @ref RCC_APB1RSTR
 * @return Driver operation status
 */
driver_status_t RCC_APB1_ResetPulse(const uint32_t resetMask)
{
	if (resetMask == 0x00UL) return DRIVER_STATUS_ERROR_INVALID_ARG;
	REGOPS_SET(&RCC->APB1RSTR.REG, resetMask);
	REGOPS_CLEAR(&RCC->APB1RSTR.REG, resetMask);
	return DRIVER_STATUS_SUCCESS;
}

/*---------------------------------------------- Driver Configuration APIs ----------------------------------------------*/
/**
 * @brief Validates complete RCC configuration before applying it
 * @param[in] cfg Pointer to @ref rcc_config_t
 * @return Driver operation status
 */
driver_status_t RCC_ValidateConfig(const rcc_config_t* cfg)
{
	if (cfg == NULL) return DRIVER_STATUS_ERROR_NULL_PTR;
	if (RCC_PrivateEncodeSystemClock(cfg->system.clk_src) == RCC_DRIVER_INVALID_FIELD) return DRIVER_STATUS_ERROR_INVALID_ARG;
	if (RCC_PrivateEncodeAHBPrescaler(cfg->prescaler.bus.AHB) == RCC_DRIVER_INVALID_FIELD) return DRIVER_STATUS_ERROR_INVALID_ARG;
	if (RCC_PrivateEncodeAPBPrescaler(cfg->prescaler.bus.APB1, RCC_APB1_BUS) == RCC_DRIVER_INVALID_FIELD) return DRIVER_STATUS_ERROR_INVALID_ARG;
	if (RCC_PrivateEncodeAPBPrescaler(cfg->prescaler.bus.APB2, RCC_APB2_BUS) == RCC_DRIVER_INVALID_FIELD) return DRIVER_STATUS_ERROR_INVALID_ARG;
	if (RCC_PrivateEncodeADCPrescaler(cfg->prescaler.component.ADC) == RCC_DRIVER_INVALID_FIELD) return DRIVER_STATUS_ERROR_INVALID_ARG;
	if (RCC_PrivateEncodeUSBPrescaler(cfg->prescaler.component.USB) == RCC_DRIVER_INVALID_FIELD) return DRIVER_STATUS_ERROR_INVALID_ARG;
	if ((cfg->flash.latency > RCC_FLASH_LATENCY_2) || (cfg->flash.prefetch > RCC_FLASH_PREFETCH_ENABLE)) return DRIVER_STATUS_ERROR_INVALID_ARG;

	if (cfg->system.clk_src == RCC_SYS_CLK_PLL)
	{
		if ((cfg->system.pll.source != RCC_PLL_SRC_HSI) && (cfg->system.pll.source != RCC_PLL_SRC_HSE)) return DRIVER_STATUS_ERROR_INVALID_ARG;
		if ((cfg->system.pll.multiplication_factor < RCC_PLL_MUL_2) || (cfg->system.pll.multiplication_factor > RCC_PLL_MUL_16)) return DRIVER_STATUS_ERROR_INVALID_ARG;
		if ((cfg->system.pll.source == RCC_PLL_SRC_HSI) && (cfg->system.pll.source_prescaler != RCC_PLL_SRC_HSI_DIV_2)) return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	{
		const _rcc_freq_t sysClk = RCC_PrivateComputeSYSCLK(cfg);
		const _rcc_freq_t hClk = RCC_PrivateComputeHCLK(cfg);
		const _rcc_freq_t pClk1 = RCC_PrivateComputePCLK1(cfg);
		const _rcc_freq_t pClk2 = RCC_PrivateComputePCLK2(cfg);
		const _rcc_freq_t adcClk = RCC_PrivateComputeADCCLK(cfg);
		const _rcc_freq_t usbClk = RCC_PrivateComputeUSBCLK(cfg);

		if (sysClk > _RCC_SYSCLK_MAX_FREQ) return DRIVER_STATUS_ERROR_INVALID_ARG;
		if (hClk > _RCC_SYSCLK_MAX_FREQ) return DRIVER_STATUS_ERROR_INVALID_ARG;
		if (pClk1 > _RCC_PCLK1_MAX_FREQ) return DRIVER_STATUS_ERROR_INVALID_ARG;
		if (pClk2 > _RCC_PCLK2_MAX_FREQ) return DRIVER_STATUS_ERROR_INVALID_ARG;
		if (adcClk > _RCC_ADCCLK_MAX_FREQ) return DRIVER_STATUS_ERROR_INVALID_ARG;
		if ((cfg->system.clk_src == RCC_SYS_CLK_PLL) && (usbClk != 0x00UL) && (usbClk != _RCC_USBCLK_TARGET_FREQ)) return DRIVER_STATUS_ERROR_INVALID_ARG;

		if ((sysClk <= 24000000UL) && (cfg->flash.latency != RCC_FLASH_LATENCY_0)) return DRIVER_STATUS_ERROR_INVALID_ARG;
		if ((sysClk > 24000000UL) && (sysClk <= 48000000UL) && (cfg->flash.latency != RCC_FLASH_LATENCY_1)) return DRIVER_STATUS_ERROR_INVALID_ARG;
		if ((sysClk > 48000000UL) && (cfg->flash.latency != RCC_FLASH_LATENCY_2)) return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Configures Flash latency and prefetch settings
 * @param[in] flash Pointer to @ref rcc_flash_config_t
 * @return Driver operation status
 */
driver_status_t RCC_ConfigFlash(const rcc_flash_config_t* flash)
{
	uint32_t flashLatency = FLASH_ACR_LATENCY_0;

	if (flash == NULL) return DRIVER_STATUS_ERROR_NULL_PTR;

	switch (flash->latency)
	{
		case RCC_FLASH_LATENCY_0: flashLatency = FLASH_ACR_LATENCY_0; break;
		case RCC_FLASH_LATENCY_1: flashLatency = FLASH_ACR_LATENCY_1; break;
		case RCC_FLASH_LATENCY_2: flashLatency = FLASH_ACR_LATENCY_2; break;
		default: return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	REGOPS_MODIFY(&FLASH->ACR.REG, FLASH_ACR_LATENCY_Msk, flashLatency);
	if (flash->prefetch == RCC_FLASH_PREFETCH_ENABLE) REGOPS_SET(&FLASH->ACR.REG, FLASH_ACR_PRFTBE);
	else REGOPS_CLEAR(&FLASH->ACR.REG, FLASH_ACR_PRFTBE);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Configures AHB, APB1 and APB2 prescalers
 * @param[in] busCfg Pointer to @ref rcc_bus_config_t
 * @return Driver operation status
 */
driver_status_t RCC_ConfigBusPrescaler(const rcc_bus_config_t* busCfg)
{
	uint32_t cfgrReg = 0x00UL;
	uint32_t ahbPrescaler = 0x00UL;
	uint32_t apb1Prescaler = 0x00UL;
	uint32_t apb2Prescaler = 0x00UL;

	if (busCfg == NULL) return DRIVER_STATUS_ERROR_NULL_PTR;

	ahbPrescaler = RCC_PrivateEncodeAHBPrescaler(busCfg->AHB);
	apb1Prescaler = RCC_PrivateEncodeAPBPrescaler(busCfg->APB1, RCC_APB1_BUS);
	apb2Prescaler = RCC_PrivateEncodeAPBPrescaler(busCfg->APB2, RCC_APB2_BUS);
	if ((ahbPrescaler == RCC_DRIVER_INVALID_FIELD) || (apb1Prescaler == RCC_DRIVER_INVALID_FIELD) || (apb2Prescaler == RCC_DRIVER_INVALID_FIELD)) return DRIVER_STATUS_ERROR_INVALID_ARG;

	cfgrReg = RCC->CFGR.REG;
	cfgrReg &= ~(RCC_CFGR_HPRE_Msk | RCC_CFGR_PPRE1_Msk | RCC_CFGR_PPRE2_Msk);
	cfgrReg |= (ahbPrescaler | apb1Prescaler | apb2Prescaler);
	REGOPS_WRITE(&RCC->CFGR.REG, cfgrReg);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Configures ADC and USB prescalers
 * @param[in] componentCfg Pointer to @ref rcc_component_config_t
 * @return Driver operation status
 */
driver_status_t RCC_ConfigComponentPrescaler(const rcc_component_config_t* componentCfg)
{
	uint32_t cfgrReg = 0x00UL;
	uint32_t adcPrescaler = 0x00UL;
	uint32_t usbPrescaler = 0x00UL;

	if (componentCfg == NULL) return DRIVER_STATUS_ERROR_NULL_PTR;

	adcPrescaler = RCC_PrivateEncodeADCPrescaler(componentCfg->ADC);
	usbPrescaler = RCC_PrivateEncodeUSBPrescaler(componentCfg->USB);
	if ((adcPrescaler == RCC_DRIVER_INVALID_FIELD) || (usbPrescaler == RCC_DRIVER_INVALID_FIELD)) return DRIVER_STATUS_ERROR_INVALID_ARG;

	cfgrReg = RCC->CFGR.REG;
	cfgrReg &= ~(RCC_CFGR_ADCPRE_Msk | RCC_CFGR_USBPRE_Msk);
	cfgrReg |= (adcPrescaler | usbPrescaler);
	REGOPS_WRITE(&RCC->CFGR.REG, cfgrReg);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Configures the complete RCC clock tree
 * @param[in] cfg Pointer to @ref rcc_config_t
 * @return Driver operation status
 */
driver_status_t RCC_Config(const rcc_config_t* cfg)
{
	uint32_t cfgrReg = 0x00UL;
	uint32_t sysClkSource = 0x00UL;
	driver_status_t status = RCC_ValidateConfig(cfg);
	if (status != DRIVER_STATUS_SUCCESS) return status;

	REGOPS_SET(&RCC->CR.REG, RCC_CR_HSION);
	DRIVER_RETURN_IF_NOT_SUCCESS(RCC_PrivateWaitFlag(&RCC->CR.REG, RCC_CR_HSIRDY, true));

	if (RCC_GetSysClkSrc() == RCC_SYS_CLK_PLL)
	{
		REGOPS_MODIFY(&RCC->CFGR.REG, RCC_CFGR_SW_Msk, RCC_CFGR_SW_HSI);
		DRIVER_RETURN_IF_NOT_SUCCESS(RCC_PrivateWaitSystemClockSource(RCC_SYS_CLK_HSI));
	}

	if ((cfg->system.clk_src == RCC_SYS_CLK_HSE) || ((cfg->system.clk_src == RCC_SYS_CLK_PLL) && (cfg->system.pll.source == RCC_PLL_SRC_HSE)))
	{
		REGOPS_SET(&RCC->CR.REG, RCC_CR_HSEON);
		DRIVER_RETURN_IF_NOT_SUCCESS(RCC_PrivateWaitFlag(&RCC->CR.REG, RCC_CR_HSERDY, true));
	}

	if (RCC->CR.REG & RCC_CR_PLLON)
	{
		REGOPS_CLEAR(&RCC->CR.REG, RCC_CR_PLLON);
		DRIVER_RETURN_IF_NOT_SUCCESS(RCC_PrivateWaitFlag(&RCC->CR.REG, RCC_CR_PLLRDY, false));
	}

	DRIVER_RETURN_IF_NOT_SUCCESS(RCC_ConfigFlash(&cfg->flash));

	cfgrReg = RCC->CFGR.REG;
	cfgrReg &= ~(RCC_CFGR_HPRE_Msk |
				 RCC_CFGR_PPRE1_Msk |
				 RCC_CFGR_PPRE2_Msk |
				 RCC_CFGR_ADCPRE_Msk |
				 RCC_CFGR_PLLSRC_Msk |
				 RCC_CFGR_PLLXTPRE_Msk |
				 RCC_CFGR_PLLMUL_Msk |
				 RCC_CFGR_USBPRE_Msk);

	cfgrReg |= RCC_PrivateEncodeAHBPrescaler(cfg->prescaler.bus.AHB);
	cfgrReg |= RCC_PrivateEncodeAPBPrescaler(cfg->prescaler.bus.APB1, RCC_APB1_BUS);
	cfgrReg |= RCC_PrivateEncodeAPBPrescaler(cfg->prescaler.bus.APB2, RCC_APB2_BUS);
	cfgrReg |= RCC_PrivateEncodeADCPrescaler(cfg->prescaler.component.ADC);
	cfgrReg |= RCC_PrivateEncodeUSBPrescaler(cfg->prescaler.component.USB);

	if (cfg->system.clk_src == RCC_SYS_CLK_PLL)
	{
		cfgrReg |= RCC_PrivateEncodePLLMultiplier(cfg->system.pll.multiplication_factor);
		if (cfg->system.pll.source == RCC_PLL_SRC_HSE)
		{
			cfgrReg |= RCC_CFGR_PLLSRC_HSE;
			if (cfg->system.pll.source_prescaler == RCC_PLL_SRC_HSE_DIV_2) cfgrReg |= RCC_CFGR_PLLXTPRE_HSE_DIV2;
		}
	}

	REGOPS_WRITE(&RCC->CFGR.REG, cfgrReg);

	if (cfg->system.clk_src == RCC_SYS_CLK_PLL)
	{
		REGOPS_SET(&RCC->CR.REG, RCC_CR_PLLON);
		DRIVER_RETURN_IF_NOT_SUCCESS(RCC_PrivateWaitFlag(&RCC->CR.REG, RCC_CR_PLLRDY, true));
	}

	sysClkSource = RCC_PrivateEncodeSystemClock(cfg->system.clk_src);
	REGOPS_MODIFY(&RCC->CFGR.REG, RCC_CFGR_SW_Msk, sysClkSource);
	DRIVER_RETURN_IF_NOT_SUCCESS(RCC_PrivateWaitSystemClockSource(cfg->system.clk_src));
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Loads default 72 MHz Blue Pill RCC configuration
 * @param[in] cfg Pointer to @ref rcc_config_t
 */
void RCC_72MHz_LoadDefaultConfig(rcc_config_t* cfg)
{
	if (cfg == NULL) return;

	cfg->flash.latency = RCC_FLASH_LATENCY_2;
	cfg->flash.prefetch = RCC_FLASH_PREFETCH_ENABLE;

	cfg->system.clk_src = RCC_SYS_CLK_PLL;
	cfg->system.pll.source = RCC_PLL_SRC_HSE;
	cfg->system.pll.source_prescaler = RCC_PLL_SRC_HSE_DIV_1;
	cfg->system.pll.multiplication_factor = RCC_PLL_MUL_9;

	cfg->prescaler.bus.AHB = RCC_AHB_DIV_1;
	cfg->prescaler.bus.APB1 = RCC_APB1_DIV_2;
	cfg->prescaler.bus.APB2 = RCC_APB2_DIV_1;

	cfg->prescaler.component.ADC = RCC_ADC_DIV_6;
	cfg->prescaler.component.USB = RCC_USB_DIV_1_5;
}

/**
 * @brief Applies default 72 MHz Blue Pill RCC configuration
 * @return Driver operation status
 */
driver_status_t RCC_Config_72MHz(void)
{
	rcc_config_t cfg;
	RCC_72MHz_LoadDefaultConfig(&cfg);
	return RCC_Config(&cfg);
}

/*---------------------------------------------- Driver Status and Frequency APIs ----------------------------------------------*/
/**
 * @brief Retrieves active system clock source from hardware
 * @returns @ref rcc_system_clock_t
 */
rcc_system_clock_t RCC_GetSysClkSrc(void)
{
	return RCC_PrivateDecodeSystemClock(RCC->CFGR.REG);
}

/**
 * @brief Retrieves active PLL source from hardware
 * @returns @ref rcc_pll_src_t
 */
rcc_pll_src_t RCC_GetPLLSource(void)
{
	return ((RCC->CFGR.REG & RCC_CFGR_PLLSRC_Msk) == RCC_CFGR_PLLSRC_HSE) ? RCC_PLL_SRC_HSE : RCC_PLL_SRC_HSI;
}

/**
 * @brief Retrieves active PLL source prescaler from hardware
 * @returns @ref rcc_pll_src_psc_t
 */
rcc_pll_src_psc_t RCC_GetPLLSourcePrescaler(void)
{
	if (RCC_GetPLLSource() == RCC_PLL_SRC_HSI) return RCC_PLL_SRC_HSI_DIV_2;
	return ((RCC->CFGR.REG & RCC_CFGR_PLLXTPRE_Msk) == RCC_CFGR_PLLXTPRE_HSE_DIV2) ? RCC_PLL_SRC_HSE_DIV_2 : RCC_PLL_SRC_HSE_DIV_1;
}

/**
 * @brief Retrieves active PLL multiplication factor from hardware
 * @returns @ref rcc_pll_mul_t
 */
rcc_pll_mul_t RCC_GetPLLMultiplier(void)
{
	return RCC_PrivateDecodePLLMultiplier(RCC->CFGR.REG);
}

/**
 * @brief Retrieves current core clock frequency before AHB prescaler
 * @returns Core clock frequency in Hz
 */
_rcc_freq_t RCC_GetCoreClockFreq(void)
{
	switch (RCC_GetSysClkSrc())
	{
		case RCC_SYS_CLK_HSI:
			return _RCC_HSI_FREQ;
		case RCC_SYS_CLK_HSE:
			return _RCC_HSE_FREQ;
		case RCC_SYS_CLK_PLL:
		{
			_rcc_freq_t pllInput = (RCC_GetPLLSource() == RCC_PLL_SRC_HSE) ? _RCC_HSE_FREQ : (_RCC_HSI_FREQ >> 1);
			if (RCC_GetPLLSourcePrescaler() == RCC_PLL_SRC_HSE_DIV_2) pllInput >>= 1;
			return pllInput * (_rcc_freq_t) RCC_GetPLLMultiplier();
		}
		default:
			return _RCC_HSI_FREQ;
	}
}

/**
 * @brief Retrieves configured bus prescaler divider
 * @param[in] bus Target bus identifier
 * @returns Prescaler divider value
 */
rcc_bus_prescaler_t RCC_GetBusPrescaler(const rcc_bus_t bus)
{
	const uint32_t cfgrReg = RCC->CFGR.REG;
	switch (bus)
	{
		case RCC_AHB_BUS: return RCC_PrivateDecodeAHBPrescaler(cfgrReg);
		case RCC_APB1_BUS: return RCC_PrivateDecodeAPB1Prescaler(cfgrReg);
		case RCC_APB2_BUS: return RCC_PrivateDecodeAPB2Prescaler(cfgrReg);
		default: return 1U;
	}
}

/**
 * @brief Retrieves current bus clock frequency
 * @param[in] bus Target bus identifier
 * @returns Bus frequency in Hz
 */
_rcc_freq_t RCC_GetBusFreq(const rcc_bus_t bus)
{
	const _rcc_freq_t sysClk = RCC_GetCoreClockFreq();
	const _rcc_freq_t hClk = (sysClk / (_rcc_freq_t) RCC_GetBusPrescaler(RCC_AHB_BUS));

	switch (bus)
	{
		case RCC_AHB_BUS: return hClk;
		case RCC_APB1_BUS: return (hClk / (_rcc_freq_t) RCC_GetBusPrescaler(RCC_APB1_BUS));
		case RCC_APB2_BUS: return (hClk / (_rcc_freq_t) RCC_GetBusPrescaler(RCC_APB2_BUS));
		default: return hClk;
	}
}

/**
 * @brief Retrieves ADC clock frequency
 * @returns ADC clock frequency in Hz
 */
_rcc_freq_t RCC_GetADCFreq(void)
{
	return (RCC_GetBusFreq(RCC_APB2_BUS) / (_rcc_freq_t) RCC_PrivateDecodeADCPrescaler(RCC->CFGR.REG));
}

/**
 * @brief Retrieves USB clock frequency
 * @returns USB clock frequency in Hz
 */
_rcc_freq_t RCC_GetUSBFreq(void)
{
	const _rcc_freq_t pllClk = (RCC_GetSysClkSrc() == RCC_SYS_CLK_PLL) ? RCC_GetCoreClockFreq() : 0x00UL;
	if (pllClk == 0x00UL) return 0x00UL;
	return (RCC_PrivateDecodeUSBPrescaler(RCC->CFGR.REG) == RCC_USB_DIV_1) ? pllClk : ((pllClk << 1) / 3U);
}
