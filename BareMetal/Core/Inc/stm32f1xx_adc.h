/**
 * @file stm32f1xx_adc.h
 * @author Shrey Shah
 * @brief STM32F1 Analog-to-Digital Converter Register-Layer Definitions
 * @version v1.0
 * @date 23-08-2026
 * @details
 * This file is the canonical Core-layer owner of the STM32F103C8T6 ADC1 and
 * ADC2 register map and raw register-field positions and masks. It depends
 * only on `stm32f1xx_utils.h`; channel policy, sampling-time selection,
 * calibration sequencing, conversion orchestration, DMA ownership, interrupt
 * handling, and physical-unit conversion belong to the ADC Driver stack.
 */

// Header Guard
#ifndef STM32F1XX_ADC_H_
#define STM32F1XX_ADC_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "stm32f1xx_utils.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup ADC Analog-to-Digital Converter (ADC)
 * @brief STM32F103C8T6 regular, injected, watchdog, trigger, DMA, and multimode conversion hardware
 * @details
 * RM0008 describes ADC1 and ADC2 as 12-bit successive-approximation engines
 * that support up to 16 external channels plus the ADC1-only temperature
 * sensor and internal reference channels. Each converter provides:
 * - regular sequences containing up to 16 programmable ranks,
 * - injected sequences containing up to four programmable ranks and offsets,
 * - per-channel sampling-time selection,
 * - software and timer/external-trigger conversion starts,
 * - single, continuous, scan, and discontinuous conversion modes,
 * - analog-watchdog threshold monitoring,
 * - regular-result DMA requests, interrupts, and ADC1/ADC2 multimode, and
 * - right- or left-aligned result presentation.
 *
 * @section ADC_RegisterLayoutBrief Register Layout Brief
 * <table>
 * <tr><th>Register</th><th>Offset</th><th>Primary Practical Role</th></tr>
 * <tr><td><code>ADCx_SR</code></td><td><code>0x00</code></td><td>Conversion, trigger-start, and analog-watchdog event flags</td></tr>
 * <tr><td><code>ADCx_CR1</code></td><td><code>0x04</code></td><td>Watchdog, scan, discontinuous, multimode, and interrupt-source configuration</td></tr>
 * <tr><td><code>ADCx_CR2</code></td><td><code>0x08</code></td><td>Operation, calibration, trigger, alignment, DMA, and internal-channel control</td></tr>
 * <tr><td><code>ADCx_SMPR1</code></td><td><code>0x0C</code></td><td>Sampling times for channels 10 through 17</td></tr>
 * <tr><td><code>ADCx_SMPR2</code></td><td><code>0x10</code></td><td>Sampling times for channels 0 through 9</td></tr>
 * <tr><td><code>ADCx_JOFR1..4</code></td><td><code>0x14..0x20</code></td><td>Injected-channel result offsets</td></tr>
 * <tr><td><code>ADCx_HTR/LTR</code></td><td><code>0x24/0x28</code></td><td>Analog-watchdog high and low thresholds</td></tr>
 * <tr><td><code>ADCx_SQR1..3</code></td><td><code>0x2C..0x34</code></td><td>Regular-sequence length and rank-to-channel selection</td></tr>
 * <tr><td><code>ADCx_JSQR</code></td><td><code>0x38</code></td><td>Injected-sequence length and rank-to-channel selection</td></tr>
 * <tr><td><code>ADCx_JDR1..4</code></td><td><code>0x3C..0x48</code></td><td>Injected conversion results after offset application</td></tr>
 * <tr><td><code>ADCx_DR</code></td><td><code>0x4C</code></td><td>Regular result and ADC2 dual-mode result</td></tr>
 * </table>
 *
 * @section ADC_DeviceBoundary Device Boundary
 * STM32F103C8T6 implements ADC1 and ADC2. ADC3 belongs to larger STM32F103
 * variants and is intentionally excluded from this device-specific ADC map.
 * Internal temperature-sensor and VREFINT channels are available only through
 * ADC1, while ADC1 and ADC2 share one NVIC interrupt line.
 *
 * This codebase currently documents ADC through one ownership level:
 * - Register layer: `stm32f1xx_adc.h`
 *
 * Future LL, Codec, and Driver layers consume this raw register vocabulary
 * without duplicating it.
 */

/**
 * @defgroup ADC_01_RegisterLayer ADC Register Layer
 * @ingroup ADC
 * @brief Raw STM32F1 ADC register structure and field definitions
 * @details
 * This layer mirrors hardware-visible configuration, event, and conversion
 * state. Driver-facing selectors, sequence validation, clock constraints,
 * calibration, trigger orchestration, DMA integration, and interrupt policy
 * belong above this Core register layer.
 */

/**
 * @addtogroup ADC_01_RegisterLayer
 * @{
 */

// ==================================================================================================== //
// ADC Register Defines
// ==================================================================================================== //

/**
 * @defgroup ADC_01_RegisterLayer_00_RegisterDefines ADC Register Bit Positions and Masks
 * @ingroup ADC_01_RegisterLayer
 * @brief Raw ADC register positions, widths, masks, and field-bit values
 * @details
 * Single-bit fields expose a position, a mask built with @ref REG_BIT_MASK,
 * and an unsuffixed mask alias. Multi-bit fields additionally expose a width
 * and use @ref REG_FIELD_MASK. Raw field-bit values use
 * @ref REG_FIELD_VALUE so every positioned value has one shared construction
 * path. Hardware-name aliases retain compatibility with the earlier
 * `EOS`/`JEOS` vocabulary without removing any existing symbol.
 * @{
 */

/** @brief STM32F103C8T6 ADC1/ADC2 multimode capability marker @def ADC_MULTIMODE_SUPPORT */
#define ADC_MULTIMODE_SUPPORT

// ---------------------------------------------------------------------------------------------------- //
// ADCx_SR
// ---------------------------------------------------------------------------------------------------- //

/** @brief Analog-watchdog event flag (`ADCx_SR.AWD`) bit position @def ADC_SR_AWD_Pos */
#define ADC_SR_AWD_Pos					((reg_bit_pos_t) 0U)
/** @brief Analog-watchdog event flag (`ADCx_SR.AWD`) bit mask @def ADC_SR_AWD_Msk */
#define ADC_SR_AWD_Msk					REG_BIT_MASK(ADC_SR_AWD_Pos)
/** @brief Analog-watchdog event flag (`ADCx_SR.AWD`) bit mask alias @def ADC_SR_AWD */
#define ADC_SR_AWD						ADC_SR_AWD_Msk

/** @brief Regular end of sequence conversions flag (`ADCx_SR.EOS`) bit position @def ADC_SR_EOS_Pos */
#define ADC_SR_EOS_Pos					((reg_bit_pos_t) 1U)
/** @brief Regular end of sequence conversions flag (`ADCx_SR.EOS`) bit mask @def ADC_SR_EOS_Msk */
#define ADC_SR_EOS_Msk					REG_BIT_MASK(ADC_SR_EOS_Pos)
/** @brief Regular end of sequence conversions flag (`ADCx_SR.EOS`) bit mask alias @def ADC_SR_EOS */
#define ADC_SR_EOS						ADC_SR_EOS_Msk

/** @brief Injected end of sequence conversions flag (`ADCx_SR.JEOS`) bit position @def ADC_SR_JEOS_Pos */
#define ADC_SR_JEOS_Pos					((reg_bit_pos_t) 2U)
/** @brief Injected end of sequence conversions flag (`ADCx_SR.JEOS`) bit mask @def ADC_SR_JEOS_Msk */
#define ADC_SR_JEOS_Msk					REG_BIT_MASK(ADC_SR_JEOS_Pos)
/** @brief Injected end of sequence conversions flag (`ADCx_SR.JEOS`) bit mask alias @def ADC_SR_JEOS */
#define ADC_SR_JEOS						ADC_SR_JEOS_Msk

/** @brief Injected conversion start flag (`ADCx_SR.JSTRT`) bit position @def ADC_SR_JSTRT_Pos */
#define ADC_SR_JSTRT_Pos				((reg_bit_pos_t) 3U)
/** @brief Injected conversion start flag (`ADCx_SR.JSTRT`) bit mask @def ADC_SR_JSTRT_Msk */
#define ADC_SR_JSTRT_Msk				REG_BIT_MASK(ADC_SR_JSTRT_Pos)
/** @brief Injected conversion start flag (`ADCx_SR.JSTRT`) bit mask alias @def ADC_SR_JSTRT */
#define ADC_SR_JSTRT					ADC_SR_JSTRT_Msk

/** @brief Regular conversion start flag (`ADCx_SR.STRT`) bit position @def ADC_SR_STRT_Pos */
#define ADC_SR_STRT_Pos					((reg_bit_pos_t) 4U)
/** @brief Regular conversion start flag (`ADCx_SR.STRT`) bit mask @def ADC_SR_STRT_Msk */
#define ADC_SR_STRT_Msk					REG_BIT_MASK(ADC_SR_STRT_Pos)
/** @brief Regular conversion start flag (`ADCx_SR.STRT`) bit mask alias @def ADC_SR_STRT */
#define ADC_SR_STRT						ADC_SR_STRT_Msk

// ---------------------------------------------------------------------------------------------------- //
// Legacy Hardware-Name Compatibility Aliases
// ---------------------------------------------------------------------------------------------------- //

/** @brief Regular-conversion end flag (`ADCx_SR.EOC`) bit position alias @def ADC_SR_EOC_Pos */
#define ADC_SR_EOC_Pos					ADC_SR_EOS_Pos
/** @brief Regular-conversion end flag (`ADCx_SR.EOC`) bit mask alias @def ADC_SR_EOC_Msk */
#define ADC_SR_EOC_Msk					ADC_SR_EOS_Msk
/** @brief Regular-conversion end flag (`ADCx_SR.EOC`) bit mask alias @def ADC_SR_EOC */
#define ADC_SR_EOC						ADC_SR_EOC_Msk

/** @brief Injected-conversion end flag (`ADCx_SR.JEOC`) bit position alias @def ADC_SR_JEOC_Pos */
#define ADC_SR_JEOC_Pos					ADC_SR_JEOS_Pos
/** @brief Injected-conversion end flag (`ADCx_SR.JEOC`) bit mask alias @def ADC_SR_JEOC_Msk */
#define ADC_SR_JEOC_Msk					ADC_SR_JEOS_Msk
/** @brief Injected-conversion end flag (`ADCx_SR.JEOC`) bit mask alias @def ADC_SR_JEOC */
#define ADC_SR_JEOC						ADC_SR_JEOC_Msk

// ---------------------------------------------------------------------------------------------------- //
// ADCx_CR1
// ---------------------------------------------------------------------------------------------------- //

/** @brief Analog-watchdog monitored-channel selection (`ADCx_CR1.AWDCH`) field position @def ADC_CR1_AWDCH_Pos */
#define ADC_CR1_AWDCH_Pos				((reg_bit_pos_t) 0U)
/** @brief Analog-watchdog monitored-channel selection (`ADCx_CR1.AWDCH`) field width @def ADC_CR1_AWDCH_Width */
#define ADC_CR1_AWDCH_Width				((reg_field_width_t) 5U)
/** @brief Analog-watchdog monitored-channel selection (`ADCx_CR1.AWDCH`) field mask @def ADC_CR1_AWDCH_Msk */
#define ADC_CR1_AWDCH_Msk				REG_FIELD_MASK(ADC_CR1_AWDCH_Pos, ADC_CR1_AWDCH_Width)
/** @brief Analog-watchdog monitored-channel selection (`ADCx_CR1.AWDCH`) field mask alias @def ADC_CR1_AWDCH */
#define ADC_CR1_AWDCH					ADC_CR1_AWDCH_Msk
/** @brief Analog-watchdog monitored-channel selection (`ADCx_CR1.AWDCH[0]`) raw field bit 0 mask @def ADC_CR1_AWDCH_0 */
#define ADC_CR1_AWDCH_0					REG_FIELD_VALUE(ADC_CR1_AWDCH_Pos, 0x01UL)
/** @brief Analog-watchdog monitored-channel selection (`ADCx_CR1.AWDCH[1]`) raw field bit 1 mask @def ADC_CR1_AWDCH_1 */
#define ADC_CR1_AWDCH_1					REG_FIELD_VALUE(ADC_CR1_AWDCH_Pos, 0x02UL)
/** @brief Analog-watchdog monitored-channel selection (`ADCx_CR1.AWDCH[2]`) raw field bit 2 mask @def ADC_CR1_AWDCH_2 */
#define ADC_CR1_AWDCH_2					REG_FIELD_VALUE(ADC_CR1_AWDCH_Pos, 0x04UL)
/** @brief Analog-watchdog monitored-channel selection (`ADCx_CR1.AWDCH[3]`) raw field bit 3 mask @def ADC_CR1_AWDCH_3 */
#define ADC_CR1_AWDCH_3					REG_FIELD_VALUE(ADC_CR1_AWDCH_Pos, 0x08UL)
/** @brief Analog-watchdog monitored-channel selection (`ADCx_CR1.AWDCH[4]`) raw field bit 4 mask @def ADC_CR1_AWDCH_4 */
#define ADC_CR1_AWDCH_4					REG_FIELD_VALUE(ADC_CR1_AWDCH_Pos, 0x10UL)

/** @brief Regular end of sequence conversions interrupt-request enable (`ADCx_CR1.EOSIE`) bit position @def ADC_CR1_EOSIE_Pos */
#define ADC_CR1_EOSIE_Pos				((reg_bit_pos_t) 5U)
/** @brief Regular end of sequence conversions interrupt-request enable (`ADCx_CR1.EOSIE`) bit mask @def ADC_CR1_EOSIE_Msk */
#define ADC_CR1_EOSIE_Msk				REG_BIT_MASK(ADC_CR1_EOSIE_Pos)
/** @brief Regular end of sequence conversions interrupt-request enable (`ADCx_CR1.EOSIE`) bit mask alias @def ADC_CR1_EOSIE */
#define ADC_CR1_EOSIE					ADC_CR1_EOSIE_Msk

/** @brief Analog-watchdog interrupt-request enable (`ADCx_CR1.AWDIE`) bit position @def ADC_CR1_AWDIE_Pos */
#define ADC_CR1_AWDIE_Pos				((reg_bit_pos_t) 6U)
/** @brief Analog-watchdog interrupt-request enable (`ADCx_CR1.AWDIE`) bit mask @def ADC_CR1_AWDIE_Msk */
#define ADC_CR1_AWDIE_Msk				REG_BIT_MASK(ADC_CR1_AWDIE_Pos)
/** @brief Analog-watchdog interrupt-request enable (`ADCx_CR1.AWDIE`) bit mask alias @def ADC_CR1_AWDIE */
#define ADC_CR1_AWDIE					ADC_CR1_AWDIE_Msk

/** @brief Injected end of sequence conversions interrupt-request enable (`ADCx_CR1.JEOSIE`) bit position @def ADC_CR1_JEOSIE_Pos */
#define ADC_CR1_JEOSIE_Pos				((reg_bit_pos_t) 7U)
/** @brief Injected end of sequence conversions interrupt-request enable (`ADCx_CR1.JEOSIE`) bit mask @def ADC_CR1_JEOSIE_Msk */
#define ADC_CR1_JEOSIE_Msk				REG_BIT_MASK(ADC_CR1_JEOSIE_Pos)
/** @brief Injected end of sequence conversions interrupt-request enable (`ADCx_CR1.JEOSIE`) bit mask alias @def ADC_CR1_JEOSIE */
#define ADC_CR1_JEOSIE					ADC_CR1_JEOSIE_Msk

/** @brief Scan-mode selection (`ADCx_CR1.SCAN`) bit position @def ADC_CR1_SCAN_Pos */
#define ADC_CR1_SCAN_Pos				((reg_bit_pos_t) 8U)
/** @brief Scan-mode selection (`ADCx_CR1.SCAN`) bit mask @def ADC_CR1_SCAN_Msk */
#define ADC_CR1_SCAN_Msk				REG_BIT_MASK(ADC_CR1_SCAN_Pos)
/** @brief Scan-mode selection (`ADCx_CR1.SCAN`) bit mask alias @def ADC_CR1_SCAN */
#define ADC_CR1_SCAN					ADC_CR1_SCAN_Msk

/** @brief Single-channel or all-channel analog-watchdog selection (`ADCx_CR1.AWDSGL`) bit position @def ADC_CR1_AWDSGL_Pos */
#define ADC_CR1_AWDSGL_Pos				((reg_bit_pos_t) 9U)
/** @brief Single-channel or all-channel analog-watchdog selection (`ADCx_CR1.AWDSGL`) bit mask @def ADC_CR1_AWDSGL_Msk */
#define ADC_CR1_AWDSGL_Msk				REG_BIT_MASK(ADC_CR1_AWDSGL_Pos)
/** @brief Single-channel or all-channel analog-watchdog selection (`ADCx_CR1.AWDSGL`) bit mask alias @def ADC_CR1_AWDSGL */
#define ADC_CR1_AWDSGL					ADC_CR1_AWDSGL_Msk

/** @brief Injected automatic trigger mode (`ADCx_CR1.JAUTO`) bit position @def ADC_CR1_JAUTO_Pos */
#define ADC_CR1_JAUTO_Pos				((reg_bit_pos_t) 10U)
/** @brief Injected automatic trigger mode (`ADCx_CR1.JAUTO`) bit mask @def ADC_CR1_JAUTO_Msk */
#define ADC_CR1_JAUTO_Msk				REG_BIT_MASK(ADC_CR1_JAUTO_Pos)
/** @brief Injected automatic trigger mode (`ADCx_CR1.JAUTO`) bit mask alias @def ADC_CR1_JAUTO */
#define ADC_CR1_JAUTO					ADC_CR1_JAUTO_Msk

/** @brief Regular sequencer discontinuous mode (`ADCx_CR1.DISCEN`) bit position @def ADC_CR1_DISCEN_Pos */
#define ADC_CR1_DISCEN_Pos				((reg_bit_pos_t) 11U)
/** @brief Regular sequencer discontinuous mode (`ADCx_CR1.DISCEN`) bit mask @def ADC_CR1_DISCEN_Msk */
#define ADC_CR1_DISCEN_Msk				REG_BIT_MASK(ADC_CR1_DISCEN_Pos)
/** @brief Regular sequencer discontinuous mode (`ADCx_CR1.DISCEN`) bit mask alias @def ADC_CR1_DISCEN */
#define ADC_CR1_DISCEN					ADC_CR1_DISCEN_Msk

/** @brief Injected sequencer discontinuous mode (`ADCx_CR1.JDISCEN`) bit position @def ADC_CR1_JDISCEN_Pos */
#define ADC_CR1_JDISCEN_Pos				((reg_bit_pos_t) 12U)
/** @brief Injected sequencer discontinuous mode (`ADCx_CR1.JDISCEN`) bit mask @def ADC_CR1_JDISCEN_Msk */
#define ADC_CR1_JDISCEN_Msk				REG_BIT_MASK(ADC_CR1_JDISCEN_Pos)
/** @brief Injected sequencer discontinuous mode (`ADCx_CR1.JDISCEN`) bit mask alias @def ADC_CR1_JDISCEN */
#define ADC_CR1_JDISCEN					ADC_CR1_JDISCEN_Msk

/** @brief Regular sequencer discontinuous number of ranks (`ADCx_CR1.DISCNUM`) field position @def ADC_CR1_DISCNUM_Pos */
#define ADC_CR1_DISCNUM_Pos				((reg_bit_pos_t) 13U)
/** @brief Regular sequencer discontinuous number of ranks (`ADCx_CR1.DISCNUM`) field width @def ADC_CR1_DISCNUM_Width */
#define ADC_CR1_DISCNUM_Width			((reg_field_width_t) 3U)
/** @brief Regular sequencer discontinuous number of ranks (`ADCx_CR1.DISCNUM`) field mask @def ADC_CR1_DISCNUM_Msk */
#define ADC_CR1_DISCNUM_Msk				REG_FIELD_MASK(ADC_CR1_DISCNUM_Pos, ADC_CR1_DISCNUM_Width)
/** @brief Regular sequencer discontinuous number of ranks (`ADCx_CR1.DISCNUM`) field mask alias @def ADC_CR1_DISCNUM */
#define ADC_CR1_DISCNUM					ADC_CR1_DISCNUM_Msk
/** @brief Regular sequencer discontinuous number of ranks (`ADCx_CR1.DISCNUM[0]`) raw field bit 0 mask @def ADC_CR1_DISCNUM_0 */
#define ADC_CR1_DISCNUM_0				REG_FIELD_VALUE(ADC_CR1_DISCNUM_Pos, 0x1UL)
/** @brief Regular sequencer discontinuous number of ranks (`ADCx_CR1.DISCNUM[1]`) raw field bit 1 mask @def ADC_CR1_DISCNUM_1 */
#define ADC_CR1_DISCNUM_1				REG_FIELD_VALUE(ADC_CR1_DISCNUM_Pos, 0x2UL)
/** @brief Regular sequencer discontinuous number of ranks (`ADCx_CR1.DISCNUM[2]`) raw field bit 2 mask @def ADC_CR1_DISCNUM_2 */
#define ADC_CR1_DISCNUM_2				REG_FIELD_VALUE(ADC_CR1_DISCNUM_Pos, 0x4UL)

/** @brief Multimode operating-mode selection (`ADCx_CR1.DUALMOD`) field position @def ADC_CR1_DUALMOD_Pos */
#define ADC_CR1_DUALMOD_Pos				((reg_bit_pos_t) 16U)
/** @brief Multimode operating-mode selection (`ADCx_CR1.DUALMOD`) field width @def ADC_CR1_DUALMOD_Width */
#define ADC_CR1_DUALMOD_Width			((reg_field_width_t) 4U)
/** @brief Multimode operating-mode selection (`ADCx_CR1.DUALMOD`) field mask @def ADC_CR1_DUALMOD_Msk */
#define ADC_CR1_DUALMOD_Msk				REG_FIELD_MASK(ADC_CR1_DUALMOD_Pos, ADC_CR1_DUALMOD_Width)
/** @brief Multimode operating-mode selection (`ADCx_CR1.DUALMOD`) field mask alias @def ADC_CR1_DUALMOD */
#define ADC_CR1_DUALMOD					ADC_CR1_DUALMOD_Msk
/** @brief Multimode operating-mode selection (`ADCx_CR1.DUALMOD[0]`) raw field bit 0 mask @def ADC_CR1_DUALMOD_0 */
#define ADC_CR1_DUALMOD_0				REG_FIELD_VALUE(ADC_CR1_DUALMOD_Pos, 0x1UL)
/** @brief Multimode operating-mode selection (`ADCx_CR1.DUALMOD[1]`) raw field bit 1 mask @def ADC_CR1_DUALMOD_1 */
#define ADC_CR1_DUALMOD_1				REG_FIELD_VALUE(ADC_CR1_DUALMOD_Pos, 0x2UL)
/** @brief Multimode operating-mode selection (`ADCx_CR1.DUALMOD[2]`) raw field bit 2 mask @def ADC_CR1_DUALMOD_2 */
#define ADC_CR1_DUALMOD_2				REG_FIELD_VALUE(ADC_CR1_DUALMOD_Pos, 0x4UL)
/** @brief Multimode operating-mode selection (`ADCx_CR1.DUALMOD[3]`) raw field bit 3 mask @def ADC_CR1_DUALMOD_3 */
#define ADC_CR1_DUALMOD_3				REG_FIELD_VALUE(ADC_CR1_DUALMOD_Pos, 0x8UL)

/** @brief Injected-group analog-watchdog enable (`ADCx_CR1.JAWDEN`) bit position @def ADC_CR1_JAWDEN_Pos */
#define ADC_CR1_JAWDEN_Pos				((reg_bit_pos_t) 22U)
/** @brief Injected-group analog-watchdog enable (`ADCx_CR1.JAWDEN`) bit mask @def ADC_CR1_JAWDEN_Msk */
#define ADC_CR1_JAWDEN_Msk				REG_BIT_MASK(ADC_CR1_JAWDEN_Pos)
/** @brief Injected-group analog-watchdog enable (`ADCx_CR1.JAWDEN`) bit mask alias @def ADC_CR1_JAWDEN */
#define ADC_CR1_JAWDEN					ADC_CR1_JAWDEN_Msk

/** @brief Regular-group analog-watchdog enable (`ADCx_CR1.AWDEN`) bit position @def ADC_CR1_AWDEN_Pos */
#define ADC_CR1_AWDEN_Pos				((reg_bit_pos_t) 23U)
/** @brief Regular-group analog-watchdog enable (`ADCx_CR1.AWDEN`) bit mask @def ADC_CR1_AWDEN_Msk */
#define ADC_CR1_AWDEN_Msk				REG_BIT_MASK(ADC_CR1_AWDEN_Pos)
/** @brief Regular-group analog-watchdog enable (`ADCx_CR1.AWDEN`) bit mask alias @def ADC_CR1_AWDEN */
#define ADC_CR1_AWDEN					ADC_CR1_AWDEN_Msk

// ---------------------------------------------------------------------------------------------------- //
// Legacy Hardware-Name Compatibility Aliases
// ---------------------------------------------------------------------------------------------------- //

/** @brief Regular-conversion end IRQ enable (`ADCx_CR1.EOCIE`) bit position alias @def ADC_CR1_EOCIE_Pos */
#define ADC_CR1_EOCIE_Pos				ADC_CR1_EOSIE_Pos
/** @brief Regular-conversion end IRQ enable (`ADCx_CR1.EOCIE`) bit mask alias @def ADC_CR1_EOCIE_Msk */
#define ADC_CR1_EOCIE_Msk				ADC_CR1_EOSIE_Msk
/** @brief Regular-conversion end IRQ enable (`ADCx_CR1.EOCIE`) bit mask alias @def ADC_CR1_EOCIE */
#define ADC_CR1_EOCIE					ADC_CR1_EOCIE_Msk

/** @brief Injected-conversion end IRQ enable (`ADCx_CR1.JEOCIE`) bit position alias @def ADC_CR1_JEOCIE_Pos */
#define ADC_CR1_JEOCIE_Pos				ADC_CR1_JEOSIE_Pos
/** @brief Injected-conversion end IRQ enable (`ADCx_CR1.JEOCIE`) bit mask alias @def ADC_CR1_JEOCIE_Msk */
#define ADC_CR1_JEOCIE_Msk				ADC_CR1_JEOSIE_Msk
/** @brief Injected-conversion end IRQ enable (`ADCx_CR1.JEOCIE`) bit mask alias @def ADC_CR1_JEOCIE */
#define ADC_CR1_JEOCIE					ADC_CR1_JEOCIE_Msk

// ---------------------------------------------------------------------------------------------------- //
// ADCx_CR2
// ---------------------------------------------------------------------------------------------------- //

/** @brief ADC operation enable (`ADCx_CR2.ADON`) bit position @def ADC_CR2_ADON_Pos */
#define ADC_CR2_ADON_Pos				((reg_bit_pos_t) 0U)
/** @brief ADC operation enable (`ADCx_CR2.ADON`) bit mask @def ADC_CR2_ADON_Msk */
#define ADC_CR2_ADON_Msk				REG_BIT_MASK(ADC_CR2_ADON_Pos)
/** @brief ADC operation enable (`ADCx_CR2.ADON`) bit mask alias @def ADC_CR2_ADON */
#define ADC_CR2_ADON					ADC_CR2_ADON_Msk

/** @brief Regular continuous conversion mode (`ADCx_CR2.CONT`) bit position @def ADC_CR2_CONT_Pos */
#define ADC_CR2_CONT_Pos				((reg_bit_pos_t) 1U)
/** @brief Regular continuous conversion mode (`ADCx_CR2.CONT`) bit mask @def ADC_CR2_CONT_Msk */
#define ADC_CR2_CONT_Msk				REG_BIT_MASK(ADC_CR2_CONT_Pos)
/** @brief Regular continuous conversion mode (`ADCx_CR2.CONT`) bit mask alias @def ADC_CR2_CONT */
#define ADC_CR2_CONT					ADC_CR2_CONT_Msk

/** @brief Calibration action request (`ADCx_CR2.CAL`) bit position @def ADC_CR2_CAL_Pos */
#define ADC_CR2_CAL_Pos					((reg_bit_pos_t) 2U)
/** @brief Calibration action request (`ADCx_CR2.CAL`) bit mask @def ADC_CR2_CAL_Msk */
#define ADC_CR2_CAL_Msk					REG_BIT_MASK(ADC_CR2_CAL_Pos)
/** @brief Calibration action request (`ADCx_CR2.CAL`) bit mask alias @def ADC_CR2_CAL */
#define ADC_CR2_CAL						ADC_CR2_CAL_Msk

/** @brief Calibration-register reset action request (`ADCx_CR2.RSTCAL`) bit position @def ADC_CR2_RSTCAL_Pos */
#define ADC_CR2_RSTCAL_Pos				((reg_bit_pos_t) 3U)
/** @brief Calibration-register reset action request (`ADCx_CR2.RSTCAL`) bit mask @def ADC_CR2_RSTCAL_Msk */
#define ADC_CR2_RSTCAL_Msk				REG_BIT_MASK(ADC_CR2_RSTCAL_Pos)
/** @brief Calibration-register reset action request (`ADCx_CR2.RSTCAL`) bit mask alias @def ADC_CR2_RSTCAL */
#define ADC_CR2_RSTCAL					ADC_CR2_RSTCAL_Msk

/** @brief DMA transfer enable (`ADCx_CR2.DMA`) bit position @def ADC_CR2_DMA_Pos */
#define ADC_CR2_DMA_Pos					((reg_bit_pos_t) 8U)
/** @brief DMA transfer enable (`ADCx_CR2.DMA`) bit mask @def ADC_CR2_DMA_Msk */
#define ADC_CR2_DMA_Msk					REG_BIT_MASK(ADC_CR2_DMA_Pos)
/** @brief DMA transfer enable (`ADCx_CR2.DMA`) bit mask alias @def ADC_CR2_DMA */
#define ADC_CR2_DMA						ADC_CR2_DMA_Msk

/** @brief Conversion-data alignment (`ADCx_CR2.ALIGN`) bit position @def ADC_CR2_ALIGN_Pos */
#define ADC_CR2_ALIGN_Pos				((reg_bit_pos_t) 11U)
/** @brief Conversion-data alignment (`ADCx_CR2.ALIGN`) bit mask @def ADC_CR2_ALIGN_Msk */
#define ADC_CR2_ALIGN_Msk				REG_BIT_MASK(ADC_CR2_ALIGN_Pos)
/** @brief Conversion-data alignment (`ADCx_CR2.ALIGN`) bit mask alias @def ADC_CR2_ALIGN */
#define ADC_CR2_ALIGN					ADC_CR2_ALIGN_Msk

/** @brief Injected external trigger source (`ADCx_CR2.JEXTSEL`) field position @def ADC_CR2_JEXTSEL_Pos */
#define ADC_CR2_JEXTSEL_Pos				((reg_bit_pos_t) 12U)
/** @brief Injected external trigger source (`ADCx_CR2.JEXTSEL`) field width @def ADC_CR2_JEXTSEL_Width */
#define ADC_CR2_JEXTSEL_Width			((reg_field_width_t) 3U)
/** @brief Injected external trigger source (`ADCx_CR2.JEXTSEL`) field mask @def ADC_CR2_JEXTSEL_Msk */
#define ADC_CR2_JEXTSEL_Msk				REG_FIELD_MASK(ADC_CR2_JEXTSEL_Pos, ADC_CR2_JEXTSEL_Width)
/** @brief Injected external trigger source (`ADCx_CR2.JEXTSEL`) field mask alias @def ADC_CR2_JEXTSEL */
#define ADC_CR2_JEXTSEL					ADC_CR2_JEXTSEL_Msk
/** @brief Injected external trigger source (`ADCx_CR2.JEXTSEL[0]`) raw field bit 0 mask @def ADC_CR2_JEXTSEL_0 */
#define ADC_CR2_JEXTSEL_0				REG_FIELD_VALUE(ADC_CR2_JEXTSEL_Pos, 0x1UL)
/** @brief Injected external trigger source (`ADCx_CR2.JEXTSEL[1]`) raw field bit 1 mask @def ADC_CR2_JEXTSEL_1 */
#define ADC_CR2_JEXTSEL_1				REG_FIELD_VALUE(ADC_CR2_JEXTSEL_Pos, 0x2UL)
/** @brief Injected external trigger source (`ADCx_CR2.JEXTSEL[2]`) raw field bit 2 mask @def ADC_CR2_JEXTSEL_2 */
#define ADC_CR2_JEXTSEL_2				REG_FIELD_VALUE(ADC_CR2_JEXTSEL_Pos, 0x4UL)

/** @brief Injected external trigger enable (`ADCx_CR2.JEXTTRIG`) bit position @def ADC_CR2_JEXTTRIG_Pos */
#define ADC_CR2_JEXTTRIG_Pos			((reg_bit_pos_t) 15U)
/** @brief Injected external trigger enable (`ADCx_CR2.JEXTTRIG`) bit mask @def ADC_CR2_JEXTTRIG_Msk */
#define ADC_CR2_JEXTTRIG_Msk			REG_BIT_MASK(ADC_CR2_JEXTTRIG_Pos)
/** @brief Injected external trigger enable (`ADCx_CR2.JEXTTRIG`) bit mask alias @def ADC_CR2_JEXTTRIG */
#define ADC_CR2_JEXTTRIG				ADC_CR2_JEXTTRIG_Msk

/** @brief Regular external trigger source (`ADCx_CR2.EXTSEL`) field position @def ADC_CR2_EXTSEL_Pos */
#define ADC_CR2_EXTSEL_Pos				((reg_bit_pos_t) 17U)
/** @brief Regular external trigger source (`ADCx_CR2.EXTSEL`) field width @def ADC_CR2_EXTSEL_Width */
#define ADC_CR2_EXTSEL_Width			((reg_field_width_t) 3U)
/** @brief Regular external trigger source (`ADCx_CR2.EXTSEL`) field mask @def ADC_CR2_EXTSEL_Msk */
#define ADC_CR2_EXTSEL_Msk				REG_FIELD_MASK(ADC_CR2_EXTSEL_Pos, ADC_CR2_EXTSEL_Width)
/** @brief Regular external trigger source (`ADCx_CR2.EXTSEL`) field mask alias @def ADC_CR2_EXTSEL */
#define ADC_CR2_EXTSEL					ADC_CR2_EXTSEL_Msk
/** @brief Regular external trigger source (`ADCx_CR2.EXTSEL[0]`) raw field bit 0 mask @def ADC_CR2_EXTSEL_0 */
#define ADC_CR2_EXTSEL_0				REG_FIELD_VALUE(ADC_CR2_EXTSEL_Pos, 0x1UL)
/** @brief Regular external trigger source (`ADCx_CR2.EXTSEL[1]`) raw field bit 1 mask @def ADC_CR2_EXTSEL_1 */
#define ADC_CR2_EXTSEL_1				REG_FIELD_VALUE(ADC_CR2_EXTSEL_Pos, 0x2UL)
/** @brief Regular external trigger source (`ADCx_CR2.EXTSEL[2]`) raw field bit 2 mask @def ADC_CR2_EXTSEL_2 */
#define ADC_CR2_EXTSEL_2				REG_FIELD_VALUE(ADC_CR2_EXTSEL_Pos, 0x4UL)

/** @brief Regular external trigger enable (`ADCx_CR2.EXTTRIG`) bit position @def ADC_CR2_EXTTRIG_Pos */
#define ADC_CR2_EXTTRIG_Pos				((reg_bit_pos_t) 20U)
/** @brief Regular external trigger enable (`ADCx_CR2.EXTTRIG`) bit mask @def ADC_CR2_EXTTRIG_Msk */
#define ADC_CR2_EXTTRIG_Msk				REG_BIT_MASK(ADC_CR2_EXTTRIG_Pos)
/** @brief Regular external trigger enable (`ADCx_CR2.EXTTRIG`) bit mask alias @def ADC_CR2_EXTTRIG */
#define ADC_CR2_EXTTRIG					ADC_CR2_EXTTRIG_Msk

/** @brief Injected conversion start (`ADCx_CR2.JSWSTART`) bit position @def ADC_CR2_JSWSTART_Pos */
#define ADC_CR2_JSWSTART_Pos			((reg_bit_pos_t) 21U)
/** @brief Injected conversion start (`ADCx_CR2.JSWSTART`) bit mask @def ADC_CR2_JSWSTART_Msk */
#define ADC_CR2_JSWSTART_Msk			REG_BIT_MASK(ADC_CR2_JSWSTART_Pos)
/** @brief Injected conversion start (`ADCx_CR2.JSWSTART`) bit mask alias @def ADC_CR2_JSWSTART */
#define ADC_CR2_JSWSTART				ADC_CR2_JSWSTART_Msk

/** @brief Regular conversion start (`ADCx_CR2.SWSTART`) bit position @def ADC_CR2_SWSTART_Pos */
#define ADC_CR2_SWSTART_Pos				((reg_bit_pos_t) 22U)
/** @brief Regular conversion start (`ADCx_CR2.SWSTART`) bit mask @def ADC_CR2_SWSTART_Msk */
#define ADC_CR2_SWSTART_Msk				REG_BIT_MASK(ADC_CR2_SWSTART_Pos)
/** @brief Regular conversion start (`ADCx_CR2.SWSTART`) bit mask alias @def ADC_CR2_SWSTART */
#define ADC_CR2_SWSTART					ADC_CR2_SWSTART_Msk

/** @brief Temperature-sensor and VREFINT internal-path enable (`ADCx_CR2.TSVREFE`) bit position @def ADC_CR2_TSVREFE_Pos */
#define ADC_CR2_TSVREFE_Pos				((reg_bit_pos_t) 23U)
/** @brief Temperature-sensor and VREFINT internal-path enable (`ADCx_CR2.TSVREFE`) bit mask @def ADC_CR2_TSVREFE_Msk */
#define ADC_CR2_TSVREFE_Msk				REG_BIT_MASK(ADC_CR2_TSVREFE_Pos)
/** @brief Temperature-sensor and VREFINT internal-path enable (`ADCx_CR2.TSVREFE`) bit mask alias @def ADC_CR2_TSVREFE */
#define ADC_CR2_TSVREFE					ADC_CR2_TSVREFE_Msk

// ---------------------------------------------------------------------------------------------------- //
// ADCx_SMPR1
// ---------------------------------------------------------------------------------------------------- //

/** @brief Channel 10 sampling time selection (`ADCx_SMPR1.SMP10`) field position @def ADC_SMPR1_SMP10_Pos */
#define ADC_SMPR1_SMP10_Pos				((reg_bit_pos_t) 0U)
/** @brief Channel 10 sampling time selection (`ADCx_SMPR1.SMP10`) field width @def ADC_SMPR1_SMP10_Width */
#define ADC_SMPR1_SMP10_Width			((reg_field_width_t) 3U)
/** @brief Channel 10 sampling time selection (`ADCx_SMPR1.SMP10`) field mask @def ADC_SMPR1_SMP10_Msk */
#define ADC_SMPR1_SMP10_Msk				REG_FIELD_MASK(ADC_SMPR1_SMP10_Pos, ADC_SMPR1_SMP10_Width)
/** @brief Channel 10 sampling time selection (`ADCx_SMPR1.SMP10`) field mask alias @def ADC_SMPR1_SMP10 */
#define ADC_SMPR1_SMP10					ADC_SMPR1_SMP10_Msk
/** @brief Channel 10 sampling time selection (`ADCx_SMPR1.SMP10[0]`) raw field bit 0 mask @def ADC_SMPR1_SMP10_0 */
#define ADC_SMPR1_SMP10_0				REG_FIELD_VALUE(ADC_SMPR1_SMP10_Pos, 0x1UL)
/** @brief Channel 10 sampling time selection (`ADCx_SMPR1.SMP10[1]`) raw field bit 1 mask @def ADC_SMPR1_SMP10_1 */
#define ADC_SMPR1_SMP10_1				REG_FIELD_VALUE(ADC_SMPR1_SMP10_Pos, 0x2UL)
/** @brief Channel 10 sampling time selection (`ADCx_SMPR1.SMP10[2]`) raw field bit 2 mask @def ADC_SMPR1_SMP10_2 */
#define ADC_SMPR1_SMP10_2				REG_FIELD_VALUE(ADC_SMPR1_SMP10_Pos, 0x4UL)

/** @brief Channel 11 sampling time selection (`ADCx_SMPR1.SMP11`) field position @def ADC_SMPR1_SMP11_Pos */
#define ADC_SMPR1_SMP11_Pos				((reg_bit_pos_t) 3U)
/** @brief Channel 11 sampling time selection (`ADCx_SMPR1.SMP11`) field width @def ADC_SMPR1_SMP11_Width */
#define ADC_SMPR1_SMP11_Width			((reg_field_width_t) 3U)
/** @brief Channel 11 sampling time selection (`ADCx_SMPR1.SMP11`) field mask @def ADC_SMPR1_SMP11_Msk */
#define ADC_SMPR1_SMP11_Msk				REG_FIELD_MASK(ADC_SMPR1_SMP11_Pos, ADC_SMPR1_SMP11_Width)
/** @brief Channel 11 sampling time selection (`ADCx_SMPR1.SMP11`) field mask alias @def ADC_SMPR1_SMP11 */
#define ADC_SMPR1_SMP11					ADC_SMPR1_SMP11_Msk
/** @brief Channel 11 sampling time selection (`ADCx_SMPR1.SMP11[0]`) raw field bit 0 mask @def ADC_SMPR1_SMP11_0 */
#define ADC_SMPR1_SMP11_0				REG_FIELD_VALUE(ADC_SMPR1_SMP11_Pos, 0x1UL)
/** @brief Channel 11 sampling time selection (`ADCx_SMPR1.SMP11[1]`) raw field bit 1 mask @def ADC_SMPR1_SMP11_1 */
#define ADC_SMPR1_SMP11_1				REG_FIELD_VALUE(ADC_SMPR1_SMP11_Pos, 0x2UL)
/** @brief Channel 11 sampling time selection (`ADCx_SMPR1.SMP11[2]`) raw field bit 2 mask @def ADC_SMPR1_SMP11_2 */
#define ADC_SMPR1_SMP11_2				REG_FIELD_VALUE(ADC_SMPR1_SMP11_Pos, 0x4UL)

/** @brief Channel 12 sampling time selection (`ADCx_SMPR1.SMP12`) field position @def ADC_SMPR1_SMP12_Pos */
#define ADC_SMPR1_SMP12_Pos				((reg_bit_pos_t) 6U)
/** @brief Channel 12 sampling time selection (`ADCx_SMPR1.SMP12`) field width @def ADC_SMPR1_SMP12_Width */
#define ADC_SMPR1_SMP12_Width			((reg_field_width_t) 3U)
/** @brief Channel 12 sampling time selection (`ADCx_SMPR1.SMP12`) field mask @def ADC_SMPR1_SMP12_Msk */
#define ADC_SMPR1_SMP12_Msk				REG_FIELD_MASK(ADC_SMPR1_SMP12_Pos, ADC_SMPR1_SMP12_Width)
/** @brief Channel 12 sampling time selection (`ADCx_SMPR1.SMP12`) field mask alias @def ADC_SMPR1_SMP12 */
#define ADC_SMPR1_SMP12					ADC_SMPR1_SMP12_Msk
/** @brief Channel 12 sampling time selection (`ADCx_SMPR1.SMP12[0]`) raw field bit 0 mask @def ADC_SMPR1_SMP12_0 */
#define ADC_SMPR1_SMP12_0				REG_FIELD_VALUE(ADC_SMPR1_SMP12_Pos, 0x1UL)
/** @brief Channel 12 sampling time selection (`ADCx_SMPR1.SMP12[1]`) raw field bit 1 mask @def ADC_SMPR1_SMP12_1 */
#define ADC_SMPR1_SMP12_1				REG_FIELD_VALUE(ADC_SMPR1_SMP12_Pos, 0x2UL)
/** @brief Channel 12 sampling time selection (`ADCx_SMPR1.SMP12[2]`) raw field bit 2 mask @def ADC_SMPR1_SMP12_2 */
#define ADC_SMPR1_SMP12_2				REG_FIELD_VALUE(ADC_SMPR1_SMP12_Pos, 0x4UL)

/** @brief Channel 13 sampling time selection (`ADCx_SMPR1.SMP13`) field position @def ADC_SMPR1_SMP13_Pos */
#define ADC_SMPR1_SMP13_Pos				((reg_bit_pos_t) 9U)
/** @brief Channel 13 sampling time selection (`ADCx_SMPR1.SMP13`) field width @def ADC_SMPR1_SMP13_Width */
#define ADC_SMPR1_SMP13_Width			((reg_field_width_t) 3U)
/** @brief Channel 13 sampling time selection (`ADCx_SMPR1.SMP13`) field mask @def ADC_SMPR1_SMP13_Msk */
#define ADC_SMPR1_SMP13_Msk				REG_FIELD_MASK(ADC_SMPR1_SMP13_Pos, ADC_SMPR1_SMP13_Width)
/** @brief Channel 13 sampling time selection (`ADCx_SMPR1.SMP13`) field mask alias @def ADC_SMPR1_SMP13 */
#define ADC_SMPR1_SMP13					ADC_SMPR1_SMP13_Msk
/** @brief Channel 13 sampling time selection (`ADCx_SMPR1.SMP13[0]`) raw field bit 0 mask @def ADC_SMPR1_SMP13_0 */
#define ADC_SMPR1_SMP13_0				REG_FIELD_VALUE(ADC_SMPR1_SMP13_Pos, 0x1UL)
/** @brief Channel 13 sampling time selection (`ADCx_SMPR1.SMP13[1]`) raw field bit 1 mask @def ADC_SMPR1_SMP13_1 */
#define ADC_SMPR1_SMP13_1				REG_FIELD_VALUE(ADC_SMPR1_SMP13_Pos, 0x2UL)
/** @brief Channel 13 sampling time selection (`ADCx_SMPR1.SMP13[2]`) raw field bit 2 mask @def ADC_SMPR1_SMP13_2 */
#define ADC_SMPR1_SMP13_2				REG_FIELD_VALUE(ADC_SMPR1_SMP13_Pos, 0x4UL)

/** @brief Channel 14 sampling time selection (`ADCx_SMPR1.SMP14`) field position @def ADC_SMPR1_SMP14_Pos */
#define ADC_SMPR1_SMP14_Pos				((reg_bit_pos_t) 12U)
/** @brief Channel 14 sampling time selection (`ADCx_SMPR1.SMP14`) field width @def ADC_SMPR1_SMP14_Width */
#define ADC_SMPR1_SMP14_Width			((reg_field_width_t) 3U)
/** @brief Channel 14 sampling time selection (`ADCx_SMPR1.SMP14`) field mask @def ADC_SMPR1_SMP14_Msk */
#define ADC_SMPR1_SMP14_Msk				REG_FIELD_MASK(ADC_SMPR1_SMP14_Pos, ADC_SMPR1_SMP14_Width)
/** @brief Channel 14 sampling time selection (`ADCx_SMPR1.SMP14`) field mask alias @def ADC_SMPR1_SMP14 */
#define ADC_SMPR1_SMP14					ADC_SMPR1_SMP14_Msk
/** @brief Channel 14 sampling time selection (`ADCx_SMPR1.SMP14[0]`) raw field bit 0 mask @def ADC_SMPR1_SMP14_0 */
#define ADC_SMPR1_SMP14_0				REG_FIELD_VALUE(ADC_SMPR1_SMP14_Pos, 0x1UL)
/** @brief Channel 14 sampling time selection (`ADCx_SMPR1.SMP14[1]`) raw field bit 1 mask @def ADC_SMPR1_SMP14_1 */
#define ADC_SMPR1_SMP14_1				REG_FIELD_VALUE(ADC_SMPR1_SMP14_Pos, 0x2UL)
/** @brief Channel 14 sampling time selection (`ADCx_SMPR1.SMP14[2]`) raw field bit 2 mask @def ADC_SMPR1_SMP14_2 */
#define ADC_SMPR1_SMP14_2				REG_FIELD_VALUE(ADC_SMPR1_SMP14_Pos, 0x4UL)

/** @brief Channel 15 sampling time selection (`ADCx_SMPR1.SMP15`) field position @def ADC_SMPR1_SMP15_Pos */
#define ADC_SMPR1_SMP15_Pos				((reg_bit_pos_t) 15U)
/** @brief Channel 15 sampling time selection (`ADCx_SMPR1.SMP15`) field width @def ADC_SMPR1_SMP15_Width */
#define ADC_SMPR1_SMP15_Width			((reg_field_width_t) 3U)
/** @brief Channel 15 sampling time selection (`ADCx_SMPR1.SMP15`) field mask @def ADC_SMPR1_SMP15_Msk */
#define ADC_SMPR1_SMP15_Msk				REG_FIELD_MASK(ADC_SMPR1_SMP15_Pos, ADC_SMPR1_SMP15_Width)
/** @brief Channel 15 sampling time selection (`ADCx_SMPR1.SMP15`) field mask alias @def ADC_SMPR1_SMP15 */
#define ADC_SMPR1_SMP15					ADC_SMPR1_SMP15_Msk
/** @brief Channel 15 sampling time selection (`ADCx_SMPR1.SMP15[0]`) raw field bit 0 mask @def ADC_SMPR1_SMP15_0 */
#define ADC_SMPR1_SMP15_0				REG_FIELD_VALUE(ADC_SMPR1_SMP15_Pos, 0x1UL)
/** @brief Channel 15 sampling time selection (`ADCx_SMPR1.SMP15[1]`) raw field bit 1 mask @def ADC_SMPR1_SMP15_1 */
#define ADC_SMPR1_SMP15_1				REG_FIELD_VALUE(ADC_SMPR1_SMP15_Pos, 0x2UL)
/** @brief Channel 15 sampling time selection (`ADCx_SMPR1.SMP15[2]`) raw field bit 2 mask @def ADC_SMPR1_SMP15_2 */
#define ADC_SMPR1_SMP15_2				REG_FIELD_VALUE(ADC_SMPR1_SMP15_Pos, 0x4UL)

/** @brief Channel 16 sampling time selection (`ADCx_SMPR1.SMP16`) field position @def ADC_SMPR1_SMP16_Pos */
#define ADC_SMPR1_SMP16_Pos				((reg_bit_pos_t) 18U)
/** @brief Channel 16 sampling time selection (`ADCx_SMPR1.SMP16`) field width @def ADC_SMPR1_SMP16_Width */
#define ADC_SMPR1_SMP16_Width			((reg_field_width_t) 3U)
/** @brief Channel 16 sampling time selection (`ADCx_SMPR1.SMP16`) field mask @def ADC_SMPR1_SMP16_Msk */
#define ADC_SMPR1_SMP16_Msk				REG_FIELD_MASK(ADC_SMPR1_SMP16_Pos, ADC_SMPR1_SMP16_Width)
/** @brief Channel 16 sampling time selection (`ADCx_SMPR1.SMP16`) field mask alias @def ADC_SMPR1_SMP16 */
#define ADC_SMPR1_SMP16					ADC_SMPR1_SMP16_Msk
/** @brief Channel 16 sampling time selection (`ADCx_SMPR1.SMP16[0]`) raw field bit 0 mask @def ADC_SMPR1_SMP16_0 */
#define ADC_SMPR1_SMP16_0				REG_FIELD_VALUE(ADC_SMPR1_SMP16_Pos, 0x1UL)
/** @brief Channel 16 sampling time selection (`ADCx_SMPR1.SMP16[1]`) raw field bit 1 mask @def ADC_SMPR1_SMP16_1 */
#define ADC_SMPR1_SMP16_1				REG_FIELD_VALUE(ADC_SMPR1_SMP16_Pos, 0x2UL)
/** @brief Channel 16 sampling time selection (`ADCx_SMPR1.SMP16[2]`) raw field bit 2 mask @def ADC_SMPR1_SMP16_2 */
#define ADC_SMPR1_SMP16_2				REG_FIELD_VALUE(ADC_SMPR1_SMP16_Pos, 0x4UL)

/** @brief Channel 17 sampling time selection (`ADCx_SMPR1.SMP17`) field position @def ADC_SMPR1_SMP17_Pos */
#define ADC_SMPR1_SMP17_Pos				((reg_bit_pos_t) 21U)
/** @brief Channel 17 sampling time selection (`ADCx_SMPR1.SMP17`) field width @def ADC_SMPR1_SMP17_Width */
#define ADC_SMPR1_SMP17_Width			((reg_field_width_t) 3U)
/** @brief Channel 17 sampling time selection (`ADCx_SMPR1.SMP17`) field mask @def ADC_SMPR1_SMP17_Msk */
#define ADC_SMPR1_SMP17_Msk				REG_FIELD_MASK(ADC_SMPR1_SMP17_Pos, ADC_SMPR1_SMP17_Width)
/** @brief Channel 17 sampling time selection (`ADCx_SMPR1.SMP17`) field mask alias @def ADC_SMPR1_SMP17 */
#define ADC_SMPR1_SMP17					ADC_SMPR1_SMP17_Msk
/** @brief Channel 17 sampling time selection (`ADCx_SMPR1.SMP17[0]`) raw field bit 0 mask @def ADC_SMPR1_SMP17_0 */
#define ADC_SMPR1_SMP17_0				REG_FIELD_VALUE(ADC_SMPR1_SMP17_Pos, 0x1UL)
/** @brief Channel 17 sampling time selection (`ADCx_SMPR1.SMP17[1]`) raw field bit 1 mask @def ADC_SMPR1_SMP17_1 */
#define ADC_SMPR1_SMP17_1				REG_FIELD_VALUE(ADC_SMPR1_SMP17_Pos, 0x2UL)
/** @brief Channel 17 sampling time selection (`ADCx_SMPR1.SMP17[2]`) raw field bit 2 mask @def ADC_SMPR1_SMP17_2 */
#define ADC_SMPR1_SMP17_2				REG_FIELD_VALUE(ADC_SMPR1_SMP17_Pos, 0x4UL)

// ---------------------------------------------------------------------------------------------------- //
// ADCx_SMPR2
// ---------------------------------------------------------------------------------------------------- //

/** @brief Channel 0 sampling time selection (`ADCx_SMPR2.SMP0`) field position @def ADC_SMPR2_SMP0_Pos */
#define ADC_SMPR2_SMP0_Pos				((reg_bit_pos_t) 0U)
/** @brief Channel 0 sampling time selection (`ADCx_SMPR2.SMP0`) field width @def ADC_SMPR2_SMP0_Width */
#define ADC_SMPR2_SMP0_Width			((reg_field_width_t) 3U)
/** @brief Channel 0 sampling time selection (`ADCx_SMPR2.SMP0`) field mask @def ADC_SMPR2_SMP0_Msk */
#define ADC_SMPR2_SMP0_Msk				REG_FIELD_MASK(ADC_SMPR2_SMP0_Pos, ADC_SMPR2_SMP0_Width)
/** @brief Channel 0 sampling time selection (`ADCx_SMPR2.SMP0`) field mask alias @def ADC_SMPR2_SMP0 */
#define ADC_SMPR2_SMP0					ADC_SMPR2_SMP0_Msk
/** @brief Channel 0 sampling time selection (`ADCx_SMPR2.SMP0[0]`) raw field bit 0 mask @def ADC_SMPR2_SMP0_0 */
#define ADC_SMPR2_SMP0_0				REG_FIELD_VALUE(ADC_SMPR2_SMP0_Pos, 0x1UL)
/** @brief Channel 0 sampling time selection (`ADCx_SMPR2.SMP0[1]`) raw field bit 1 mask @def ADC_SMPR2_SMP0_1 */
#define ADC_SMPR2_SMP0_1				REG_FIELD_VALUE(ADC_SMPR2_SMP0_Pos, 0x2UL)
/** @brief Channel 0 sampling time selection (`ADCx_SMPR2.SMP0[2]`) raw field bit 2 mask @def ADC_SMPR2_SMP0_2 */
#define ADC_SMPR2_SMP0_2				REG_FIELD_VALUE(ADC_SMPR2_SMP0_Pos, 0x4UL)

/** @brief Channel 1 sampling time selection (`ADCx_SMPR2.SMP1`) field position @def ADC_SMPR2_SMP1_Pos */
#define ADC_SMPR2_SMP1_Pos				((reg_bit_pos_t) 3U)
/** @brief Channel 1 sampling time selection (`ADCx_SMPR2.SMP1`) field width @def ADC_SMPR2_SMP1_Width */
#define ADC_SMPR2_SMP1_Width			((reg_field_width_t) 3U)
/** @brief Channel 1 sampling time selection (`ADCx_SMPR2.SMP1`) field mask @def ADC_SMPR2_SMP1_Msk */
#define ADC_SMPR2_SMP1_Msk				REG_FIELD_MASK(ADC_SMPR2_SMP1_Pos, ADC_SMPR2_SMP1_Width)
/** @brief Channel 1 sampling time selection (`ADCx_SMPR2.SMP1`) field mask alias @def ADC_SMPR2_SMP1 */
#define ADC_SMPR2_SMP1					ADC_SMPR2_SMP1_Msk
/** @brief Channel 1 sampling time selection (`ADCx_SMPR2.SMP1[0]`) raw field bit 0 mask @def ADC_SMPR2_SMP1_0 */
#define ADC_SMPR2_SMP1_0				REG_FIELD_VALUE(ADC_SMPR2_SMP1_Pos, 0x1UL)
/** @brief Channel 1 sampling time selection (`ADCx_SMPR2.SMP1[1]`) raw field bit 1 mask @def ADC_SMPR2_SMP1_1 */
#define ADC_SMPR2_SMP1_1				REG_FIELD_VALUE(ADC_SMPR2_SMP1_Pos, 0x2UL)
/** @brief Channel 1 sampling time selection (`ADCx_SMPR2.SMP1[2]`) raw field bit 2 mask @def ADC_SMPR2_SMP1_2 */
#define ADC_SMPR2_SMP1_2				REG_FIELD_VALUE(ADC_SMPR2_SMP1_Pos, 0x4UL)

/** @brief Channel 2 sampling time selection (`ADCx_SMPR2.SMP2`) field position @def ADC_SMPR2_SMP2_Pos */
#define ADC_SMPR2_SMP2_Pos				((reg_bit_pos_t) 6U)
/** @brief Channel 2 sampling time selection (`ADCx_SMPR2.SMP2`) field width @def ADC_SMPR2_SMP2_Width */
#define ADC_SMPR2_SMP2_Width			((reg_field_width_t) 3U)
/** @brief Channel 2 sampling time selection (`ADCx_SMPR2.SMP2`) field mask @def ADC_SMPR2_SMP2_Msk */
#define ADC_SMPR2_SMP2_Msk				REG_FIELD_MASK(ADC_SMPR2_SMP2_Pos, ADC_SMPR2_SMP2_Width)
/** @brief Channel 2 sampling time selection (`ADCx_SMPR2.SMP2`) field mask alias @def ADC_SMPR2_SMP2 */
#define ADC_SMPR2_SMP2					ADC_SMPR2_SMP2_Msk
/** @brief Channel 2 sampling time selection (`ADCx_SMPR2.SMP2[0]`) raw field bit 0 mask @def ADC_SMPR2_SMP2_0 */
#define ADC_SMPR2_SMP2_0				REG_FIELD_VALUE(ADC_SMPR2_SMP2_Pos, 0x1UL)
/** @brief Channel 2 sampling time selection (`ADCx_SMPR2.SMP2[1]`) raw field bit 1 mask @def ADC_SMPR2_SMP2_1 */
#define ADC_SMPR2_SMP2_1				REG_FIELD_VALUE(ADC_SMPR2_SMP2_Pos, 0x2UL)
/** @brief Channel 2 sampling time selection (`ADCx_SMPR2.SMP2[2]`) raw field bit 2 mask @def ADC_SMPR2_SMP2_2 */
#define ADC_SMPR2_SMP2_2				REG_FIELD_VALUE(ADC_SMPR2_SMP2_Pos, 0x4UL)

/** @brief Channel 3 sampling time selection (`ADCx_SMPR2.SMP3`) field position @def ADC_SMPR2_SMP3_Pos */
#define ADC_SMPR2_SMP3_Pos				((reg_bit_pos_t) 9U)
/** @brief Channel 3 sampling time selection (`ADCx_SMPR2.SMP3`) field width @def ADC_SMPR2_SMP3_Width */
#define ADC_SMPR2_SMP3_Width			((reg_field_width_t) 3U)
/** @brief Channel 3 sampling time selection (`ADCx_SMPR2.SMP3`) field mask @def ADC_SMPR2_SMP3_Msk */
#define ADC_SMPR2_SMP3_Msk				REG_FIELD_MASK(ADC_SMPR2_SMP3_Pos, ADC_SMPR2_SMP3_Width)
/** @brief Channel 3 sampling time selection (`ADCx_SMPR2.SMP3`) field mask alias @def ADC_SMPR2_SMP3 */
#define ADC_SMPR2_SMP3					ADC_SMPR2_SMP3_Msk
/** @brief Channel 3 sampling time selection (`ADCx_SMPR2.SMP3[0]`) raw field bit 0 mask @def ADC_SMPR2_SMP3_0 */
#define ADC_SMPR2_SMP3_0				REG_FIELD_VALUE(ADC_SMPR2_SMP3_Pos, 0x1UL)
/** @brief Channel 3 sampling time selection (`ADCx_SMPR2.SMP3[1]`) raw field bit 1 mask @def ADC_SMPR2_SMP3_1 */
#define ADC_SMPR2_SMP3_1				REG_FIELD_VALUE(ADC_SMPR2_SMP3_Pos, 0x2UL)
/** @brief Channel 3 sampling time selection (`ADCx_SMPR2.SMP3[2]`) raw field bit 2 mask @def ADC_SMPR2_SMP3_2 */
#define ADC_SMPR2_SMP3_2				REG_FIELD_VALUE(ADC_SMPR2_SMP3_Pos, 0x4UL)

/** @brief Channel 4 sampling time selection (`ADCx_SMPR2.SMP4`) field position @def ADC_SMPR2_SMP4_Pos */
#define ADC_SMPR2_SMP4_Pos				((reg_bit_pos_t) 12U)
/** @brief Channel 4 sampling time selection (`ADCx_SMPR2.SMP4`) field width @def ADC_SMPR2_SMP4_Width */
#define ADC_SMPR2_SMP4_Width			((reg_field_width_t) 3U)
/** @brief Channel 4 sampling time selection (`ADCx_SMPR2.SMP4`) field mask @def ADC_SMPR2_SMP4_Msk */
#define ADC_SMPR2_SMP4_Msk				REG_FIELD_MASK(ADC_SMPR2_SMP4_Pos, ADC_SMPR2_SMP4_Width)
/** @brief Channel 4 sampling time selection (`ADCx_SMPR2.SMP4`) field mask alias @def ADC_SMPR2_SMP4 */
#define ADC_SMPR2_SMP4					ADC_SMPR2_SMP4_Msk
/** @brief Channel 4 sampling time selection (`ADCx_SMPR2.SMP4[0]`) raw field bit 0 mask @def ADC_SMPR2_SMP4_0 */
#define ADC_SMPR2_SMP4_0				REG_FIELD_VALUE(ADC_SMPR2_SMP4_Pos, 0x1UL)
/** @brief Channel 4 sampling time selection (`ADCx_SMPR2.SMP4[1]`) raw field bit 1 mask @def ADC_SMPR2_SMP4_1 */
#define ADC_SMPR2_SMP4_1				REG_FIELD_VALUE(ADC_SMPR2_SMP4_Pos, 0x2UL)
/** @brief Channel 4 sampling time selection (`ADCx_SMPR2.SMP4[2]`) raw field bit 2 mask @def ADC_SMPR2_SMP4_2 */
#define ADC_SMPR2_SMP4_2				REG_FIELD_VALUE(ADC_SMPR2_SMP4_Pos, 0x4UL)

/** @brief Channel 5 sampling time selection (`ADCx_SMPR2.SMP5`) field position @def ADC_SMPR2_SMP5_Pos */
#define ADC_SMPR2_SMP5_Pos				((reg_bit_pos_t) 15U)
/** @brief Channel 5 sampling time selection (`ADCx_SMPR2.SMP5`) field width @def ADC_SMPR2_SMP5_Width */
#define ADC_SMPR2_SMP5_Width			((reg_field_width_t) 3U)
/** @brief Channel 5 sampling time selection (`ADCx_SMPR2.SMP5`) field mask @def ADC_SMPR2_SMP5_Msk */
#define ADC_SMPR2_SMP5_Msk				REG_FIELD_MASK(ADC_SMPR2_SMP5_Pos, ADC_SMPR2_SMP5_Width)
/** @brief Channel 5 sampling time selection (`ADCx_SMPR2.SMP5`) field mask alias @def ADC_SMPR2_SMP5 */
#define ADC_SMPR2_SMP5					ADC_SMPR2_SMP5_Msk
/** @brief Channel 5 sampling time selection (`ADCx_SMPR2.SMP5[0]`) raw field bit 0 mask @def ADC_SMPR2_SMP5_0 */
#define ADC_SMPR2_SMP5_0				REG_FIELD_VALUE(ADC_SMPR2_SMP5_Pos, 0x1UL)
/** @brief Channel 5 sampling time selection (`ADCx_SMPR2.SMP5[1]`) raw field bit 1 mask @def ADC_SMPR2_SMP5_1 */
#define ADC_SMPR2_SMP5_1				REG_FIELD_VALUE(ADC_SMPR2_SMP5_Pos, 0x2UL)
/** @brief Channel 5 sampling time selection (`ADCx_SMPR2.SMP5[2]`) raw field bit 2 mask @def ADC_SMPR2_SMP5_2 */
#define ADC_SMPR2_SMP5_2				REG_FIELD_VALUE(ADC_SMPR2_SMP5_Pos, 0x4UL)

/** @brief Channel 6 sampling time selection (`ADCx_SMPR2.SMP6`) field position @def ADC_SMPR2_SMP6_Pos */
#define ADC_SMPR2_SMP6_Pos				((reg_bit_pos_t) 18U)
/** @brief Channel 6 sampling time selection (`ADCx_SMPR2.SMP6`) field width @def ADC_SMPR2_SMP6_Width */
#define ADC_SMPR2_SMP6_Width			((reg_field_width_t) 3U)
/** @brief Channel 6 sampling time selection (`ADCx_SMPR2.SMP6`) field mask @def ADC_SMPR2_SMP6_Msk */
#define ADC_SMPR2_SMP6_Msk				REG_FIELD_MASK(ADC_SMPR2_SMP6_Pos, ADC_SMPR2_SMP6_Width)
/** @brief Channel 6 sampling time selection (`ADCx_SMPR2.SMP6`) field mask alias @def ADC_SMPR2_SMP6 */
#define ADC_SMPR2_SMP6					ADC_SMPR2_SMP6_Msk
/** @brief Channel 6 sampling time selection (`ADCx_SMPR2.SMP6[0]`) raw field bit 0 mask @def ADC_SMPR2_SMP6_0 */
#define ADC_SMPR2_SMP6_0				REG_FIELD_VALUE(ADC_SMPR2_SMP6_Pos, 0x1UL)
/** @brief Channel 6 sampling time selection (`ADCx_SMPR2.SMP6[1]`) raw field bit 1 mask @def ADC_SMPR2_SMP6_1 */
#define ADC_SMPR2_SMP6_1				REG_FIELD_VALUE(ADC_SMPR2_SMP6_Pos, 0x2UL)
/** @brief Channel 6 sampling time selection (`ADCx_SMPR2.SMP6[2]`) raw field bit 2 mask @def ADC_SMPR2_SMP6_2 */
#define ADC_SMPR2_SMP6_2				REG_FIELD_VALUE(ADC_SMPR2_SMP6_Pos, 0x4UL)

/** @brief Channel 7 sampling time selection (`ADCx_SMPR2.SMP7`) field position @def ADC_SMPR2_SMP7_Pos */
#define ADC_SMPR2_SMP7_Pos				((reg_bit_pos_t) 21U)
/** @brief Channel 7 sampling time selection (`ADCx_SMPR2.SMP7`) field width @def ADC_SMPR2_SMP7_Width */
#define ADC_SMPR2_SMP7_Width			((reg_field_width_t) 3U)
/** @brief Channel 7 sampling time selection (`ADCx_SMPR2.SMP7`) field mask @def ADC_SMPR2_SMP7_Msk */
#define ADC_SMPR2_SMP7_Msk				REG_FIELD_MASK(ADC_SMPR2_SMP7_Pos, ADC_SMPR2_SMP7_Width)
/** @brief Channel 7 sampling time selection (`ADCx_SMPR2.SMP7`) field mask alias @def ADC_SMPR2_SMP7 */
#define ADC_SMPR2_SMP7					ADC_SMPR2_SMP7_Msk
/** @brief Channel 7 sampling time selection (`ADCx_SMPR2.SMP7[0]`) raw field bit 0 mask @def ADC_SMPR2_SMP7_0 */
#define ADC_SMPR2_SMP7_0				REG_FIELD_VALUE(ADC_SMPR2_SMP7_Pos, 0x1UL)
/** @brief Channel 7 sampling time selection (`ADCx_SMPR2.SMP7[1]`) raw field bit 1 mask @def ADC_SMPR2_SMP7_1 */
#define ADC_SMPR2_SMP7_1				REG_FIELD_VALUE(ADC_SMPR2_SMP7_Pos, 0x2UL)
/** @brief Channel 7 sampling time selection (`ADCx_SMPR2.SMP7[2]`) raw field bit 2 mask @def ADC_SMPR2_SMP7_2 */
#define ADC_SMPR2_SMP7_2				REG_FIELD_VALUE(ADC_SMPR2_SMP7_Pos, 0x4UL)

/** @brief Channel 8 sampling time selection (`ADCx_SMPR2.SMP8`) field position @def ADC_SMPR2_SMP8_Pos */
#define ADC_SMPR2_SMP8_Pos				((reg_bit_pos_t) 24U)
/** @brief Channel 8 sampling time selection (`ADCx_SMPR2.SMP8`) field width @def ADC_SMPR2_SMP8_Width */
#define ADC_SMPR2_SMP8_Width			((reg_field_width_t) 3U)
/** @brief Channel 8 sampling time selection (`ADCx_SMPR2.SMP8`) field mask @def ADC_SMPR2_SMP8_Msk */
#define ADC_SMPR2_SMP8_Msk				REG_FIELD_MASK(ADC_SMPR2_SMP8_Pos, ADC_SMPR2_SMP8_Width)
/** @brief Channel 8 sampling time selection (`ADCx_SMPR2.SMP8`) field mask alias @def ADC_SMPR2_SMP8 */
#define ADC_SMPR2_SMP8					ADC_SMPR2_SMP8_Msk
/** @brief Channel 8 sampling time selection (`ADCx_SMPR2.SMP8[0]`) raw field bit 0 mask @def ADC_SMPR2_SMP8_0 */
#define ADC_SMPR2_SMP8_0				REG_FIELD_VALUE(ADC_SMPR2_SMP8_Pos, 0x1UL)
/** @brief Channel 8 sampling time selection (`ADCx_SMPR2.SMP8[1]`) raw field bit 1 mask @def ADC_SMPR2_SMP8_1 */
#define ADC_SMPR2_SMP8_1				REG_FIELD_VALUE(ADC_SMPR2_SMP8_Pos, 0x2UL)
/** @brief Channel 8 sampling time selection (`ADCx_SMPR2.SMP8[2]`) raw field bit 2 mask @def ADC_SMPR2_SMP8_2 */
#define ADC_SMPR2_SMP8_2				REG_FIELD_VALUE(ADC_SMPR2_SMP8_Pos, 0x4UL)

/** @brief Channel 9 sampling time selection (`ADCx_SMPR2.SMP9`) field position @def ADC_SMPR2_SMP9_Pos */
#define ADC_SMPR2_SMP9_Pos				((reg_bit_pos_t) 27U)
/** @brief Channel 9 sampling time selection (`ADCx_SMPR2.SMP9`) field width @def ADC_SMPR2_SMP9_Width */
#define ADC_SMPR2_SMP9_Width			((reg_field_width_t) 3U)
/** @brief Channel 9 sampling time selection (`ADCx_SMPR2.SMP9`) field mask @def ADC_SMPR2_SMP9_Msk */
#define ADC_SMPR2_SMP9_Msk				REG_FIELD_MASK(ADC_SMPR2_SMP9_Pos, ADC_SMPR2_SMP9_Width)
/** @brief Channel 9 sampling time selection (`ADCx_SMPR2.SMP9`) field mask alias @def ADC_SMPR2_SMP9 */
#define ADC_SMPR2_SMP9					ADC_SMPR2_SMP9_Msk
/** @brief Channel 9 sampling time selection (`ADCx_SMPR2.SMP9[0]`) raw field bit 0 mask @def ADC_SMPR2_SMP9_0 */
#define ADC_SMPR2_SMP9_0				REG_FIELD_VALUE(ADC_SMPR2_SMP9_Pos, 0x1UL)
/** @brief Channel 9 sampling time selection (`ADCx_SMPR2.SMP9[1]`) raw field bit 1 mask @def ADC_SMPR2_SMP9_1 */
#define ADC_SMPR2_SMP9_1				REG_FIELD_VALUE(ADC_SMPR2_SMP9_Pos, 0x2UL)
/** @brief Channel 9 sampling time selection (`ADCx_SMPR2.SMP9[2]`) raw field bit 2 mask @def ADC_SMPR2_SMP9_2 */
#define ADC_SMPR2_SMP9_2				REG_FIELD_VALUE(ADC_SMPR2_SMP9_Pos, 0x4UL)

// ---------------------------------------------------------------------------------------------------- //
// ADCx_JOFR1
// ---------------------------------------------------------------------------------------------------- //

/** @brief Injected sequencer rank 1 offset value (`ADCx_JOFR1.JOFFSET1`) field position @def ADC_JOFR1_JOFFSET1_Pos */
#define ADC_JOFR1_JOFFSET1_Pos			((reg_bit_pos_t) 0U)
/** @brief Injected sequencer rank 1 offset value (`ADCx_JOFR1.JOFFSET1`) field width @def ADC_JOFR1_JOFFSET1_Width */
#define ADC_JOFR1_JOFFSET1_Width		((reg_field_width_t) 12U)
/** @brief Injected sequencer rank 1 offset value (`ADCx_JOFR1.JOFFSET1`) field mask @def ADC_JOFR1_JOFFSET1_Msk */
#define ADC_JOFR1_JOFFSET1_Msk			REG_FIELD_MASK(ADC_JOFR1_JOFFSET1_Pos, ADC_JOFR1_JOFFSET1_Width)
/** @brief Injected sequencer rank 1 offset value (`ADCx_JOFR1.JOFFSET1`) field mask alias @def ADC_JOFR1_JOFFSET1 */
#define ADC_JOFR1_JOFFSET1				ADC_JOFR1_JOFFSET1_Msk

// ---------------------------------------------------------------------------------------------------- //
// ADCx_JOFR2
// ---------------------------------------------------------------------------------------------------- //

/** @brief Injected sequencer rank 2 offset value (`ADCx_JOFR2.JOFFSET2`) field position @def ADC_JOFR2_JOFFSET2_Pos */
#define ADC_JOFR2_JOFFSET2_Pos			((reg_bit_pos_t) 0U)
/** @brief Injected sequencer rank 2 offset value (`ADCx_JOFR2.JOFFSET2`) field width @def ADC_JOFR2_JOFFSET2_Width */
#define ADC_JOFR2_JOFFSET2_Width		((reg_field_width_t) 12U)
/** @brief Injected sequencer rank 2 offset value (`ADCx_JOFR2.JOFFSET2`) field mask @def ADC_JOFR2_JOFFSET2_Msk */
#define ADC_JOFR2_JOFFSET2_Msk			REG_FIELD_MASK(ADC_JOFR2_JOFFSET2_Pos, ADC_JOFR2_JOFFSET2_Width)
/** @brief Injected sequencer rank 2 offset value (`ADCx_JOFR2.JOFFSET2`) field mask alias @def ADC_JOFR2_JOFFSET2 */
#define ADC_JOFR2_JOFFSET2				ADC_JOFR2_JOFFSET2_Msk

// ---------------------------------------------------------------------------------------------------- //
// ADCx_JOFR3
// ---------------------------------------------------------------------------------------------------- //

/** @brief Injected sequencer rank 3 offset value (`ADCx_JOFR3.JOFFSET3`) field position @def ADC_JOFR3_JOFFSET3_Pos */
#define ADC_JOFR3_JOFFSET3_Pos			((reg_bit_pos_t) 0U)
/** @brief Injected sequencer rank 3 offset value (`ADCx_JOFR3.JOFFSET3`) field width @def ADC_JOFR3_JOFFSET3_Width */
#define ADC_JOFR3_JOFFSET3_Width		((reg_field_width_t) 12U)
/** @brief Injected sequencer rank 3 offset value (`ADCx_JOFR3.JOFFSET3`) field mask @def ADC_JOFR3_JOFFSET3_Msk */
#define ADC_JOFR3_JOFFSET3_Msk			REG_FIELD_MASK(ADC_JOFR3_JOFFSET3_Pos, ADC_JOFR3_JOFFSET3_Width)
/** @brief Injected sequencer rank 3 offset value (`ADCx_JOFR3.JOFFSET3`) field mask alias @def ADC_JOFR3_JOFFSET3 */
#define ADC_JOFR3_JOFFSET3				ADC_JOFR3_JOFFSET3_Msk

// ---------------------------------------------------------------------------------------------------- //
// ADCx_JOFR4
// ---------------------------------------------------------------------------------------------------- //

/** @brief Injected sequencer rank 4 offset value (`ADCx_JOFR4.JOFFSET4`) field position @def ADC_JOFR4_JOFFSET4_Pos */
#define ADC_JOFR4_JOFFSET4_Pos			((reg_bit_pos_t) 0U)
/** @brief Injected sequencer rank 4 offset value (`ADCx_JOFR4.JOFFSET4`) field width @def ADC_JOFR4_JOFFSET4_Width */
#define ADC_JOFR4_JOFFSET4_Width		((reg_field_width_t) 12U)
/** @brief Injected sequencer rank 4 offset value (`ADCx_JOFR4.JOFFSET4`) field mask @def ADC_JOFR4_JOFFSET4_Msk */
#define ADC_JOFR4_JOFFSET4_Msk			REG_FIELD_MASK(ADC_JOFR4_JOFFSET4_Pos, ADC_JOFR4_JOFFSET4_Width)
/** @brief Injected sequencer rank 4 offset value (`ADCx_JOFR4.JOFFSET4`) field mask alias @def ADC_JOFR4_JOFFSET4 */
#define ADC_JOFR4_JOFFSET4				ADC_JOFR4_JOFFSET4_Msk

// ---------------------------------------------------------------------------------------------------- //
// ADCx_HTR
// ---------------------------------------------------------------------------------------------------- //

/** @brief Analog watchdog 1 threshold high (`ADCx_HTR.HT`) field position @def ADC_HTR_HT_Pos */
#define ADC_HTR_HT_Pos					((reg_bit_pos_t) 0U)
/** @brief Analog watchdog 1 threshold high (`ADCx_HTR.HT`) field width @def ADC_HTR_HT_Width */
#define ADC_HTR_HT_Width				((reg_field_width_t) 12U)
/** @brief Analog watchdog 1 threshold high (`ADCx_HTR.HT`) field mask @def ADC_HTR_HT_Msk */
#define ADC_HTR_HT_Msk					REG_FIELD_MASK(ADC_HTR_HT_Pos, ADC_HTR_HT_Width)
/** @brief Analog watchdog 1 threshold high (`ADCx_HTR.HT`) field mask alias @def ADC_HTR_HT */
#define ADC_HTR_HT						ADC_HTR_HT_Msk

// ---------------------------------------------------------------------------------------------------- //
// ADCx_LTR
// ---------------------------------------------------------------------------------------------------- //

/** @brief Analog watchdog 1 threshold low (`ADCx_LTR.LT`) field position @def ADC_LTR_LT_Pos */
#define ADC_LTR_LT_Pos					((reg_bit_pos_t) 0U)
/** @brief Analog watchdog 1 threshold low (`ADCx_LTR.LT`) field width @def ADC_LTR_LT_Width */
#define ADC_LTR_LT_Width				((reg_field_width_t) 12U)
/** @brief Analog watchdog 1 threshold low (`ADCx_LTR.LT`) field mask @def ADC_LTR_LT_Msk */
#define ADC_LTR_LT_Msk					REG_FIELD_MASK(ADC_LTR_LT_Pos, ADC_LTR_LT_Width)
/** @brief Analog watchdog 1 threshold low (`ADCx_LTR.LT`) field mask alias @def ADC_LTR_LT */
#define ADC_LTR_LT						ADC_LTR_LT_Msk

// ---------------------------------------------------------------------------------------------------- //
// ADCx_SQR1
// ---------------------------------------------------------------------------------------------------- //

/** @brief Regular sequencer rank 13 (`ADCx_SQR1.SQ13`) field position @def ADC_SQR1_SQ13_Pos */
#define ADC_SQR1_SQ13_Pos				((reg_bit_pos_t) 0U)
/** @brief Regular sequencer rank 13 (`ADCx_SQR1.SQ13`) field width @def ADC_SQR1_SQ13_Width */
#define ADC_SQR1_SQ13_Width				((reg_field_width_t) 5U)
/** @brief Regular sequencer rank 13 (`ADCx_SQR1.SQ13`) field mask @def ADC_SQR1_SQ13_Msk */
#define ADC_SQR1_SQ13_Msk				REG_FIELD_MASK(ADC_SQR1_SQ13_Pos, ADC_SQR1_SQ13_Width)
/** @brief Regular sequencer rank 13 (`ADCx_SQR1.SQ13`) field mask alias @def ADC_SQR1_SQ13 */
#define ADC_SQR1_SQ13					ADC_SQR1_SQ13_Msk
/** @brief Regular sequencer rank 13 (`ADCx_SQR1.SQ13[0]`) raw field bit 0 mask @def ADC_SQR1_SQ13_0 */
#define ADC_SQR1_SQ13_0					REG_FIELD_VALUE(ADC_SQR1_SQ13_Pos, 0x01UL)
/** @brief Regular sequencer rank 13 (`ADCx_SQR1.SQ13[1]`) raw field bit 1 mask @def ADC_SQR1_SQ13_1 */
#define ADC_SQR1_SQ13_1					REG_FIELD_VALUE(ADC_SQR1_SQ13_Pos, 0x02UL)
/** @brief Regular sequencer rank 13 (`ADCx_SQR1.SQ13[2]`) raw field bit 2 mask @def ADC_SQR1_SQ13_2 */
#define ADC_SQR1_SQ13_2					REG_FIELD_VALUE(ADC_SQR1_SQ13_Pos, 0x04UL)
/** @brief Regular sequencer rank 13 (`ADCx_SQR1.SQ13[3]`) raw field bit 3 mask @def ADC_SQR1_SQ13_3 */
#define ADC_SQR1_SQ13_3					REG_FIELD_VALUE(ADC_SQR1_SQ13_Pos, 0x08UL)
/** @brief Regular sequencer rank 13 (`ADCx_SQR1.SQ13[4]`) raw field bit 4 mask @def ADC_SQR1_SQ13_4 */
#define ADC_SQR1_SQ13_4					REG_FIELD_VALUE(ADC_SQR1_SQ13_Pos, 0x10UL)

/** @brief Regular sequencer rank 14 (`ADCx_SQR1.SQ14`) field position @def ADC_SQR1_SQ14_Pos */
#define ADC_SQR1_SQ14_Pos				((reg_bit_pos_t) 5U)
/** @brief Regular sequencer rank 14 (`ADCx_SQR1.SQ14`) field width @def ADC_SQR1_SQ14_Width */
#define ADC_SQR1_SQ14_Width				((reg_field_width_t) 5U)
/** @brief Regular sequencer rank 14 (`ADCx_SQR1.SQ14`) field mask @def ADC_SQR1_SQ14_Msk */
#define ADC_SQR1_SQ14_Msk				REG_FIELD_MASK(ADC_SQR1_SQ14_Pos, ADC_SQR1_SQ14_Width)
/** @brief Regular sequencer rank 14 (`ADCx_SQR1.SQ14`) field mask alias @def ADC_SQR1_SQ14 */
#define ADC_SQR1_SQ14					ADC_SQR1_SQ14_Msk
/** @brief Regular sequencer rank 14 (`ADCx_SQR1.SQ14[0]`) raw field bit 0 mask @def ADC_SQR1_SQ14_0 */
#define ADC_SQR1_SQ14_0					REG_FIELD_VALUE(ADC_SQR1_SQ14_Pos, 0x01UL)
/** @brief Regular sequencer rank 14 (`ADCx_SQR1.SQ14[1]`) raw field bit 1 mask @def ADC_SQR1_SQ14_1 */
#define ADC_SQR1_SQ14_1					REG_FIELD_VALUE(ADC_SQR1_SQ14_Pos, 0x02UL)
/** @brief Regular sequencer rank 14 (`ADCx_SQR1.SQ14[2]`) raw field bit 2 mask @def ADC_SQR1_SQ14_2 */
#define ADC_SQR1_SQ14_2					REG_FIELD_VALUE(ADC_SQR1_SQ14_Pos, 0x04UL)
/** @brief Regular sequencer rank 14 (`ADCx_SQR1.SQ14[3]`) raw field bit 3 mask @def ADC_SQR1_SQ14_3 */
#define ADC_SQR1_SQ14_3					REG_FIELD_VALUE(ADC_SQR1_SQ14_Pos, 0x08UL)
/** @brief Regular sequencer rank 14 (`ADCx_SQR1.SQ14[4]`) raw field bit 4 mask @def ADC_SQR1_SQ14_4 */
#define ADC_SQR1_SQ14_4					REG_FIELD_VALUE(ADC_SQR1_SQ14_Pos, 0x10UL)

/** @brief Regular sequencer rank 15 (`ADCx_SQR1.SQ15`) field position @def ADC_SQR1_SQ15_Pos */
#define ADC_SQR1_SQ15_Pos				((reg_bit_pos_t) 10U)
/** @brief Regular sequencer rank 15 (`ADCx_SQR1.SQ15`) field width @def ADC_SQR1_SQ15_Width */
#define ADC_SQR1_SQ15_Width				((reg_field_width_t) 5U)
/** @brief Regular sequencer rank 15 (`ADCx_SQR1.SQ15`) field mask @def ADC_SQR1_SQ15_Msk */
#define ADC_SQR1_SQ15_Msk				REG_FIELD_MASK(ADC_SQR1_SQ15_Pos, ADC_SQR1_SQ15_Width)
/** @brief Regular sequencer rank 15 (`ADCx_SQR1.SQ15`) field mask alias @def ADC_SQR1_SQ15 */
#define ADC_SQR1_SQ15					ADC_SQR1_SQ15_Msk
/** @brief Regular sequencer rank 15 (`ADCx_SQR1.SQ15[0]`) raw field bit 0 mask @def ADC_SQR1_SQ15_0 */
#define ADC_SQR1_SQ15_0					REG_FIELD_VALUE(ADC_SQR1_SQ15_Pos, 0x01UL)
/** @brief Regular sequencer rank 15 (`ADCx_SQR1.SQ15[1]`) raw field bit 1 mask @def ADC_SQR1_SQ15_1 */
#define ADC_SQR1_SQ15_1					REG_FIELD_VALUE(ADC_SQR1_SQ15_Pos, 0x02UL)
/** @brief Regular sequencer rank 15 (`ADCx_SQR1.SQ15[2]`) raw field bit 2 mask @def ADC_SQR1_SQ15_2 */
#define ADC_SQR1_SQ15_2					REG_FIELD_VALUE(ADC_SQR1_SQ15_Pos, 0x04UL)
/** @brief Regular sequencer rank 15 (`ADCx_SQR1.SQ15[3]`) raw field bit 3 mask @def ADC_SQR1_SQ15_3 */
#define ADC_SQR1_SQ15_3					REG_FIELD_VALUE(ADC_SQR1_SQ15_Pos, 0x08UL)
/** @brief Regular sequencer rank 15 (`ADCx_SQR1.SQ15[4]`) raw field bit 4 mask @def ADC_SQR1_SQ15_4 */
#define ADC_SQR1_SQ15_4					REG_FIELD_VALUE(ADC_SQR1_SQ15_Pos, 0x10UL)

/** @brief Regular sequencer rank 16 (`ADCx_SQR1.SQ16`) field position @def ADC_SQR1_SQ16_Pos */
#define ADC_SQR1_SQ16_Pos				((reg_bit_pos_t) 15U)
/** @brief Regular sequencer rank 16 (`ADCx_SQR1.SQ16`) field width @def ADC_SQR1_SQ16_Width */
#define ADC_SQR1_SQ16_Width				((reg_field_width_t) 5U)
/** @brief Regular sequencer rank 16 (`ADCx_SQR1.SQ16`) field mask @def ADC_SQR1_SQ16_Msk */
#define ADC_SQR1_SQ16_Msk				REG_FIELD_MASK(ADC_SQR1_SQ16_Pos, ADC_SQR1_SQ16_Width)
/** @brief Regular sequencer rank 16 (`ADCx_SQR1.SQ16`) field mask alias @def ADC_SQR1_SQ16 */
#define ADC_SQR1_SQ16					ADC_SQR1_SQ16_Msk
/** @brief Regular sequencer rank 16 (`ADCx_SQR1.SQ16[0]`) raw field bit 0 mask @def ADC_SQR1_SQ16_0 */
#define ADC_SQR1_SQ16_0					REG_FIELD_VALUE(ADC_SQR1_SQ16_Pos, 0x01UL)
/** @brief Regular sequencer rank 16 (`ADCx_SQR1.SQ16[1]`) raw field bit 1 mask @def ADC_SQR1_SQ16_1 */
#define ADC_SQR1_SQ16_1					REG_FIELD_VALUE(ADC_SQR1_SQ16_Pos, 0x02UL)
/** @brief Regular sequencer rank 16 (`ADCx_SQR1.SQ16[2]`) raw field bit 2 mask @def ADC_SQR1_SQ16_2 */
#define ADC_SQR1_SQ16_2					REG_FIELD_VALUE(ADC_SQR1_SQ16_Pos, 0x04UL)
/** @brief Regular sequencer rank 16 (`ADCx_SQR1.SQ16[3]`) raw field bit 3 mask @def ADC_SQR1_SQ16_3 */
#define ADC_SQR1_SQ16_3					REG_FIELD_VALUE(ADC_SQR1_SQ16_Pos, 0x08UL)
/** @brief Regular sequencer rank 16 (`ADCx_SQR1.SQ16[4]`) raw field bit 4 mask @def ADC_SQR1_SQ16_4 */
#define ADC_SQR1_SQ16_4					REG_FIELD_VALUE(ADC_SQR1_SQ16_Pos, 0x10UL)

/** @brief Regular sequencer scan length (`ADCx_SQR1.L`) field position @def ADC_SQR1_L_Pos */
#define ADC_SQR1_L_Pos					((reg_bit_pos_t) 20U)
/** @brief Regular sequencer scan length (`ADCx_SQR1.L`) field width @def ADC_SQR1_L_Width */
#define ADC_SQR1_L_Width				((reg_field_width_t) 4U)
/** @brief Regular sequencer scan length (`ADCx_SQR1.L`) field mask @def ADC_SQR1_L_Msk */
#define ADC_SQR1_L_Msk					REG_FIELD_MASK(ADC_SQR1_L_Pos, ADC_SQR1_L_Width)
/** @brief Regular sequencer scan length (`ADCx_SQR1.L`) field mask alias @def ADC_SQR1_L */
#define ADC_SQR1_L						ADC_SQR1_L_Msk
/** @brief Regular sequencer scan length (`ADCx_SQR1.L[0]`) raw field bit 0 mask @def ADC_SQR1_L_0 */
#define ADC_SQR1_L_0					REG_FIELD_VALUE(ADC_SQR1_L_Pos, 0x1UL)
/** @brief Regular sequencer scan length (`ADCx_SQR1.L[1]`) raw field bit 1 mask @def ADC_SQR1_L_1 */
#define ADC_SQR1_L_1					REG_FIELD_VALUE(ADC_SQR1_L_Pos, 0x2UL)
/** @brief Regular sequencer scan length (`ADCx_SQR1.L[2]`) raw field bit 2 mask @def ADC_SQR1_L_2 */
#define ADC_SQR1_L_2					REG_FIELD_VALUE(ADC_SQR1_L_Pos, 0x4UL)
/** @brief Regular sequencer scan length (`ADCx_SQR1.L[3]`) raw field bit 3 mask @def ADC_SQR1_L_3 */
#define ADC_SQR1_L_3					REG_FIELD_VALUE(ADC_SQR1_L_Pos, 0x8UL)

// ---------------------------------------------------------------------------------------------------- //
// ADCx_SQR2
// ---------------------------------------------------------------------------------------------------- //

/** @brief Regular sequencer rank 7 (`ADCx_SQR2.SQ7`) field position @def ADC_SQR2_SQ7_Pos */
#define ADC_SQR2_SQ7_Pos				((reg_bit_pos_t) 0U)
/** @brief Regular sequencer rank 7 (`ADCx_SQR2.SQ7`) field width @def ADC_SQR2_SQ7_Width */
#define ADC_SQR2_SQ7_Width				((reg_field_width_t) 5U)
/** @brief Regular sequencer rank 7 (`ADCx_SQR2.SQ7`) field mask @def ADC_SQR2_SQ7_Msk */
#define ADC_SQR2_SQ7_Msk				REG_FIELD_MASK(ADC_SQR2_SQ7_Pos, ADC_SQR2_SQ7_Width)
/** @brief Regular sequencer rank 7 (`ADCx_SQR2.SQ7`) field mask alias @def ADC_SQR2_SQ7 */
#define ADC_SQR2_SQ7					ADC_SQR2_SQ7_Msk
/** @brief Regular sequencer rank 7 (`ADCx_SQR2.SQ7[0]`) raw field bit 0 mask @def ADC_SQR2_SQ7_0 */
#define ADC_SQR2_SQ7_0					REG_FIELD_VALUE(ADC_SQR2_SQ7_Pos, 0x01UL)
/** @brief Regular sequencer rank 7 (`ADCx_SQR2.SQ7[1]`) raw field bit 1 mask @def ADC_SQR2_SQ7_1 */
#define ADC_SQR2_SQ7_1					REG_FIELD_VALUE(ADC_SQR2_SQ7_Pos, 0x02UL)
/** @brief Regular sequencer rank 7 (`ADCx_SQR2.SQ7[2]`) raw field bit 2 mask @def ADC_SQR2_SQ7_2 */
#define ADC_SQR2_SQ7_2					REG_FIELD_VALUE(ADC_SQR2_SQ7_Pos, 0x04UL)
/** @brief Regular sequencer rank 7 (`ADCx_SQR2.SQ7[3]`) raw field bit 3 mask @def ADC_SQR2_SQ7_3 */
#define ADC_SQR2_SQ7_3					REG_FIELD_VALUE(ADC_SQR2_SQ7_Pos, 0x08UL)
/** @brief Regular sequencer rank 7 (`ADCx_SQR2.SQ7[4]`) raw field bit 4 mask @def ADC_SQR2_SQ7_4 */
#define ADC_SQR2_SQ7_4					REG_FIELD_VALUE(ADC_SQR2_SQ7_Pos, 0x10UL)

/** @brief Regular sequencer rank 8 (`ADCx_SQR2.SQ8`) field position @def ADC_SQR2_SQ8_Pos */
#define ADC_SQR2_SQ8_Pos				((reg_bit_pos_t) 5U)
/** @brief Regular sequencer rank 8 (`ADCx_SQR2.SQ8`) field width @def ADC_SQR2_SQ8_Width */
#define ADC_SQR2_SQ8_Width				((reg_field_width_t) 5U)
/** @brief Regular sequencer rank 8 (`ADCx_SQR2.SQ8`) field mask @def ADC_SQR2_SQ8_Msk */
#define ADC_SQR2_SQ8_Msk				REG_FIELD_MASK(ADC_SQR2_SQ8_Pos, ADC_SQR2_SQ8_Width)
/** @brief Regular sequencer rank 8 (`ADCx_SQR2.SQ8`) field mask alias @def ADC_SQR2_SQ8 */
#define ADC_SQR2_SQ8					ADC_SQR2_SQ8_Msk
/** @brief Regular sequencer rank 8 (`ADCx_SQR2.SQ8[0]`) raw field bit 0 mask @def ADC_SQR2_SQ8_0 */
#define ADC_SQR2_SQ8_0					REG_FIELD_VALUE(ADC_SQR2_SQ8_Pos, 0x01UL)
/** @brief Regular sequencer rank 8 (`ADCx_SQR2.SQ8[1]`) raw field bit 1 mask @def ADC_SQR2_SQ8_1 */
#define ADC_SQR2_SQ8_1					REG_FIELD_VALUE(ADC_SQR2_SQ8_Pos, 0x02UL)
/** @brief Regular sequencer rank 8 (`ADCx_SQR2.SQ8[2]`) raw field bit 2 mask @def ADC_SQR2_SQ8_2 */
#define ADC_SQR2_SQ8_2					REG_FIELD_VALUE(ADC_SQR2_SQ8_Pos, 0x04UL)
/** @brief Regular sequencer rank 8 (`ADCx_SQR2.SQ8[3]`) raw field bit 3 mask @def ADC_SQR2_SQ8_3 */
#define ADC_SQR2_SQ8_3					REG_FIELD_VALUE(ADC_SQR2_SQ8_Pos, 0x08UL)
/** @brief Regular sequencer rank 8 (`ADCx_SQR2.SQ8[4]`) raw field bit 4 mask @def ADC_SQR2_SQ8_4 */
#define ADC_SQR2_SQ8_4					REG_FIELD_VALUE(ADC_SQR2_SQ8_Pos, 0x10UL)

/** @brief Regular sequencer rank 9 (`ADCx_SQR2.SQ9`) field position @def ADC_SQR2_SQ9_Pos */
#define ADC_SQR2_SQ9_Pos				((reg_bit_pos_t) 10U)
/** @brief Regular sequencer rank 9 (`ADCx_SQR2.SQ9`) field width @def ADC_SQR2_SQ9_Width */
#define ADC_SQR2_SQ9_Width				((reg_field_width_t) 5U)
/** @brief Regular sequencer rank 9 (`ADCx_SQR2.SQ9`) field mask @def ADC_SQR2_SQ9_Msk */
#define ADC_SQR2_SQ9_Msk				REG_FIELD_MASK(ADC_SQR2_SQ9_Pos, ADC_SQR2_SQ9_Width)
/** @brief Regular sequencer rank 9 (`ADCx_SQR2.SQ9`) field mask alias @def ADC_SQR2_SQ9 */
#define ADC_SQR2_SQ9					ADC_SQR2_SQ9_Msk
/** @brief Regular sequencer rank 9 (`ADCx_SQR2.SQ9[0]`) raw field bit 0 mask @def ADC_SQR2_SQ9_0 */
#define ADC_SQR2_SQ9_0					REG_FIELD_VALUE(ADC_SQR2_SQ9_Pos, 0x01UL)
/** @brief Regular sequencer rank 9 (`ADCx_SQR2.SQ9[1]`) raw field bit 1 mask @def ADC_SQR2_SQ9_1 */
#define ADC_SQR2_SQ9_1					REG_FIELD_VALUE(ADC_SQR2_SQ9_Pos, 0x02UL)
/** @brief Regular sequencer rank 9 (`ADCx_SQR2.SQ9[2]`) raw field bit 2 mask @def ADC_SQR2_SQ9_2 */
#define ADC_SQR2_SQ9_2					REG_FIELD_VALUE(ADC_SQR2_SQ9_Pos, 0x04UL)
/** @brief Regular sequencer rank 9 (`ADCx_SQR2.SQ9[3]`) raw field bit 3 mask @def ADC_SQR2_SQ9_3 */
#define ADC_SQR2_SQ9_3					REG_FIELD_VALUE(ADC_SQR2_SQ9_Pos, 0x08UL)
/** @brief Regular sequencer rank 9 (`ADCx_SQR2.SQ9[4]`) raw field bit 4 mask @def ADC_SQR2_SQ9_4 */
#define ADC_SQR2_SQ9_4					REG_FIELD_VALUE(ADC_SQR2_SQ9_Pos, 0x10UL)

/** @brief Regular sequencer rank 10 (`ADCx_SQR2.SQ10`) field position @def ADC_SQR2_SQ10_Pos */
#define ADC_SQR2_SQ10_Pos				((reg_bit_pos_t) 15U)
/** @brief Regular sequencer rank 10 (`ADCx_SQR2.SQ10`) field width @def ADC_SQR2_SQ10_Width */
#define ADC_SQR2_SQ10_Width				((reg_field_width_t) 5U)
/** @brief Regular sequencer rank 10 (`ADCx_SQR2.SQ10`) field mask @def ADC_SQR2_SQ10_Msk */
#define ADC_SQR2_SQ10_Msk				REG_FIELD_MASK(ADC_SQR2_SQ10_Pos, ADC_SQR2_SQ10_Width)
/** @brief Regular sequencer rank 10 (`ADCx_SQR2.SQ10`) field mask alias @def ADC_SQR2_SQ10 */
#define ADC_SQR2_SQ10					ADC_SQR2_SQ10_Msk
/** @brief Regular sequencer rank 10 (`ADCx_SQR2.SQ10[0]`) raw field bit 0 mask @def ADC_SQR2_SQ10_0 */
#define ADC_SQR2_SQ10_0					REG_FIELD_VALUE(ADC_SQR2_SQ10_Pos, 0x01UL)
/** @brief Regular sequencer rank 10 (`ADCx_SQR2.SQ10[1]`) raw field bit 1 mask @def ADC_SQR2_SQ10_1 */
#define ADC_SQR2_SQ10_1					REG_FIELD_VALUE(ADC_SQR2_SQ10_Pos, 0x02UL)
/** @brief Regular sequencer rank 10 (`ADCx_SQR2.SQ10[2]`) raw field bit 2 mask @def ADC_SQR2_SQ10_2 */
#define ADC_SQR2_SQ10_2					REG_FIELD_VALUE(ADC_SQR2_SQ10_Pos, 0x04UL)
/** @brief Regular sequencer rank 10 (`ADCx_SQR2.SQ10[3]`) raw field bit 3 mask @def ADC_SQR2_SQ10_3 */
#define ADC_SQR2_SQ10_3					REG_FIELD_VALUE(ADC_SQR2_SQ10_Pos, 0x08UL)
/** @brief Regular sequencer rank 10 (`ADCx_SQR2.SQ10[4]`) raw field bit 4 mask @def ADC_SQR2_SQ10_4 */
#define ADC_SQR2_SQ10_4					REG_FIELD_VALUE(ADC_SQR2_SQ10_Pos, 0x10UL)

/** @brief Regular sequencer rank 1 (`ADCx_SQR2.SQ11`) field position @def ADC_SQR2_SQ11_Pos */
#define ADC_SQR2_SQ11_Pos				((reg_bit_pos_t) 20U)
/** @brief Regular sequencer rank 1 (`ADCx_SQR2.SQ11`) field width @def ADC_SQR2_SQ11_Width */
#define ADC_SQR2_SQ11_Width				((reg_field_width_t) 5U)
/** @brief Regular sequencer rank 1 (`ADCx_SQR2.SQ11`) field mask @def ADC_SQR2_SQ11_Msk */
#define ADC_SQR2_SQ11_Msk				REG_FIELD_MASK(ADC_SQR2_SQ11_Pos, ADC_SQR2_SQ11_Width)
/** @brief Regular sequencer rank 1 (`ADCx_SQR2.SQ11`) field mask alias @def ADC_SQR2_SQ11 */
#define ADC_SQR2_SQ11					ADC_SQR2_SQ11_Msk
/** @brief Regular sequencer rank 1 (`ADCx_SQR2.SQ11[0]`) raw field bit 0 mask @def ADC_SQR2_SQ11_0 */
#define ADC_SQR2_SQ11_0					REG_FIELD_VALUE(ADC_SQR2_SQ11_Pos, 0x01UL)
/** @brief Regular sequencer rank 1 (`ADCx_SQR2.SQ11[1]`) raw field bit 1 mask @def ADC_SQR2_SQ11_1 */
#define ADC_SQR2_SQ11_1					REG_FIELD_VALUE(ADC_SQR2_SQ11_Pos, 0x02UL)
/** @brief Regular sequencer rank 1 (`ADCx_SQR2.SQ11[2]`) raw field bit 2 mask @def ADC_SQR2_SQ11_2 */
#define ADC_SQR2_SQ11_2					REG_FIELD_VALUE(ADC_SQR2_SQ11_Pos, 0x04UL)
/** @brief Regular sequencer rank 1 (`ADCx_SQR2.SQ11[3]`) raw field bit 3 mask @def ADC_SQR2_SQ11_3 */
#define ADC_SQR2_SQ11_3					REG_FIELD_VALUE(ADC_SQR2_SQ11_Pos, 0x08UL)
/** @brief Regular sequencer rank 1 (`ADCx_SQR2.SQ11[4]`) raw field bit 4 mask @def ADC_SQR2_SQ11_4 */
#define ADC_SQR2_SQ11_4					REG_FIELD_VALUE(ADC_SQR2_SQ11_Pos, 0x10UL)

/** @brief Regular sequencer rank 12 (`ADCx_SQR2.SQ12`) field position @def ADC_SQR2_SQ12_Pos */
#define ADC_SQR2_SQ12_Pos				((reg_bit_pos_t) 25U)
/** @brief Regular sequencer rank 12 (`ADCx_SQR2.SQ12`) field width @def ADC_SQR2_SQ12_Width */
#define ADC_SQR2_SQ12_Width				((reg_field_width_t) 5U)
/** @brief Regular sequencer rank 12 (`ADCx_SQR2.SQ12`) field mask @def ADC_SQR2_SQ12_Msk */
#define ADC_SQR2_SQ12_Msk				REG_FIELD_MASK(ADC_SQR2_SQ12_Pos, ADC_SQR2_SQ12_Width)
/** @brief Regular sequencer rank 12 (`ADCx_SQR2.SQ12`) field mask alias @def ADC_SQR2_SQ12 */
#define ADC_SQR2_SQ12					ADC_SQR2_SQ12_Msk
/** @brief Regular sequencer rank 12 (`ADCx_SQR2.SQ12[0]`) raw field bit 0 mask @def ADC_SQR2_SQ12_0 */
#define ADC_SQR2_SQ12_0					REG_FIELD_VALUE(ADC_SQR2_SQ12_Pos, 0x01UL)
/** @brief Regular sequencer rank 12 (`ADCx_SQR2.SQ12[1]`) raw field bit 1 mask @def ADC_SQR2_SQ12_1 */
#define ADC_SQR2_SQ12_1					REG_FIELD_VALUE(ADC_SQR2_SQ12_Pos, 0x02UL)
/** @brief Regular sequencer rank 12 (`ADCx_SQR2.SQ12[2]`) raw field bit 2 mask @def ADC_SQR2_SQ12_2 */
#define ADC_SQR2_SQ12_2					REG_FIELD_VALUE(ADC_SQR2_SQ12_Pos, 0x04UL)
/** @brief Regular sequencer rank 12 (`ADCx_SQR2.SQ12[3]`) raw field bit 3 mask @def ADC_SQR2_SQ12_3 */
#define ADC_SQR2_SQ12_3					REG_FIELD_VALUE(ADC_SQR2_SQ12_Pos, 0x08UL)
/** @brief Regular sequencer rank 12 (`ADCx_SQR2.SQ12[4]`) raw field bit 4 mask @def ADC_SQR2_SQ12_4 */
#define ADC_SQR2_SQ12_4					REG_FIELD_VALUE(ADC_SQR2_SQ12_Pos, 0x10UL)

// ---------------------------------------------------------------------------------------------------- //
// ADCx_SQR3
// ---------------------------------------------------------------------------------------------------- //

/** @brief Regular sequencer rank 1 (`ADCx_SQR3.SQ1`) field position @def ADC_SQR3_SQ1_Pos */
#define ADC_SQR3_SQ1_Pos				((reg_bit_pos_t) 0U)
/** @brief Regular sequencer rank 1 (`ADCx_SQR3.SQ1`) field width @def ADC_SQR3_SQ1_Width */
#define ADC_SQR3_SQ1_Width				((reg_field_width_t) 5U)
/** @brief Regular sequencer rank 1 (`ADCx_SQR3.SQ1`) field mask @def ADC_SQR3_SQ1_Msk */
#define ADC_SQR3_SQ1_Msk				REG_FIELD_MASK(ADC_SQR3_SQ1_Pos, ADC_SQR3_SQ1_Width)
/** @brief Regular sequencer rank 1 (`ADCx_SQR3.SQ1`) field mask alias @def ADC_SQR3_SQ1 */
#define ADC_SQR3_SQ1					ADC_SQR3_SQ1_Msk
/** @brief Regular sequencer rank 1 (`ADCx_SQR3.SQ1[0]`) raw field bit 0 mask @def ADC_SQR3_SQ1_0 */
#define ADC_SQR3_SQ1_0					REG_FIELD_VALUE(ADC_SQR3_SQ1_Pos, 0x01UL)
/** @brief Regular sequencer rank 1 (`ADCx_SQR3.SQ1[1]`) raw field bit 1 mask @def ADC_SQR3_SQ1_1 */
#define ADC_SQR3_SQ1_1					REG_FIELD_VALUE(ADC_SQR3_SQ1_Pos, 0x02UL)
/** @brief Regular sequencer rank 1 (`ADCx_SQR3.SQ1[2]`) raw field bit 2 mask @def ADC_SQR3_SQ1_2 */
#define ADC_SQR3_SQ1_2					REG_FIELD_VALUE(ADC_SQR3_SQ1_Pos, 0x04UL)
/** @brief Regular sequencer rank 1 (`ADCx_SQR3.SQ1[3]`) raw field bit 3 mask @def ADC_SQR3_SQ1_3 */
#define ADC_SQR3_SQ1_3					REG_FIELD_VALUE(ADC_SQR3_SQ1_Pos, 0x08UL)
/** @brief Regular sequencer rank 1 (`ADCx_SQR3.SQ1[4]`) raw field bit 4 mask @def ADC_SQR3_SQ1_4 */
#define ADC_SQR3_SQ1_4					REG_FIELD_VALUE(ADC_SQR3_SQ1_Pos, 0x10UL)

/** @brief Regular sequencer rank 2 (`ADCx_SQR3.SQ2`) field position @def ADC_SQR3_SQ2_Pos */
#define ADC_SQR3_SQ2_Pos				((reg_bit_pos_t) 5U)
/** @brief Regular sequencer rank 2 (`ADCx_SQR3.SQ2`) field width @def ADC_SQR3_SQ2_Width */
#define ADC_SQR3_SQ2_Width				((reg_field_width_t) 5U)
/** @brief Regular sequencer rank 2 (`ADCx_SQR3.SQ2`) field mask @def ADC_SQR3_SQ2_Msk */
#define ADC_SQR3_SQ2_Msk				REG_FIELD_MASK(ADC_SQR3_SQ2_Pos, ADC_SQR3_SQ2_Width)
/** @brief Regular sequencer rank 2 (`ADCx_SQR3.SQ2`) field mask alias @def ADC_SQR3_SQ2 */
#define ADC_SQR3_SQ2					ADC_SQR3_SQ2_Msk
/** @brief Regular sequencer rank 2 (`ADCx_SQR3.SQ2[0]`) raw field bit 0 mask @def ADC_SQR3_SQ2_0 */
#define ADC_SQR3_SQ2_0					REG_FIELD_VALUE(ADC_SQR3_SQ2_Pos, 0x01UL)
/** @brief Regular sequencer rank 2 (`ADCx_SQR3.SQ2[1]`) raw field bit 1 mask @def ADC_SQR3_SQ2_1 */
#define ADC_SQR3_SQ2_1					REG_FIELD_VALUE(ADC_SQR3_SQ2_Pos, 0x02UL)
/** @brief Regular sequencer rank 2 (`ADCx_SQR3.SQ2[2]`) raw field bit 2 mask @def ADC_SQR3_SQ2_2 */
#define ADC_SQR3_SQ2_2					REG_FIELD_VALUE(ADC_SQR3_SQ2_Pos, 0x04UL)
/** @brief Regular sequencer rank 2 (`ADCx_SQR3.SQ2[3]`) raw field bit 3 mask @def ADC_SQR3_SQ2_3 */
#define ADC_SQR3_SQ2_3					REG_FIELD_VALUE(ADC_SQR3_SQ2_Pos, 0x08UL)
/** @brief Regular sequencer rank 2 (`ADCx_SQR3.SQ2[4]`) raw field bit 4 mask @def ADC_SQR3_SQ2_4 */
#define ADC_SQR3_SQ2_4					REG_FIELD_VALUE(ADC_SQR3_SQ2_Pos, 0x10UL)

/** @brief Regular sequencer rank 3 (`ADCx_SQR3.SQ3`) field position @def ADC_SQR3_SQ3_Pos */
#define ADC_SQR3_SQ3_Pos				((reg_bit_pos_t) 10U)
/** @brief Regular sequencer rank 3 (`ADCx_SQR3.SQ3`) field width @def ADC_SQR3_SQ3_Width */
#define ADC_SQR3_SQ3_Width				((reg_field_width_t) 5U)
/** @brief Regular sequencer rank 3 (`ADCx_SQR3.SQ3`) field mask @def ADC_SQR3_SQ3_Msk */
#define ADC_SQR3_SQ3_Msk				REG_FIELD_MASK(ADC_SQR3_SQ3_Pos, ADC_SQR3_SQ3_Width)
/** @brief Regular sequencer rank 3 (`ADCx_SQR3.SQ3`) field mask alias @def ADC_SQR3_SQ3 */
#define ADC_SQR3_SQ3					ADC_SQR3_SQ3_Msk
/** @brief Regular sequencer rank 3 (`ADCx_SQR3.SQ3[0]`) raw field bit 0 mask @def ADC_SQR3_SQ3_0 */
#define ADC_SQR3_SQ3_0					REG_FIELD_VALUE(ADC_SQR3_SQ3_Pos, 0x01UL)
/** @brief Regular sequencer rank 3 (`ADCx_SQR3.SQ3[1]`) raw field bit 1 mask @def ADC_SQR3_SQ3_1 */
#define ADC_SQR3_SQ3_1					REG_FIELD_VALUE(ADC_SQR3_SQ3_Pos, 0x02UL)
/** @brief Regular sequencer rank 3 (`ADCx_SQR3.SQ3[2]`) raw field bit 2 mask @def ADC_SQR3_SQ3_2 */
#define ADC_SQR3_SQ3_2					REG_FIELD_VALUE(ADC_SQR3_SQ3_Pos, 0x04UL)
/** @brief Regular sequencer rank 3 (`ADCx_SQR3.SQ3[3]`) raw field bit 3 mask @def ADC_SQR3_SQ3_3 */
#define ADC_SQR3_SQ3_3					REG_FIELD_VALUE(ADC_SQR3_SQ3_Pos, 0x08UL)
/** @brief Regular sequencer rank 3 (`ADCx_SQR3.SQ3[4]`) raw field bit 4 mask @def ADC_SQR3_SQ3_4 */
#define ADC_SQR3_SQ3_4					REG_FIELD_VALUE(ADC_SQR3_SQ3_Pos, 0x10UL)

/** @brief Regular sequencer rank 4 (`ADCx_SQR3.SQ4`) field position @def ADC_SQR3_SQ4_Pos */
#define ADC_SQR3_SQ4_Pos				((reg_bit_pos_t) 15U)
/** @brief Regular sequencer rank 4 (`ADCx_SQR3.SQ4`) field width @def ADC_SQR3_SQ4_Width */
#define ADC_SQR3_SQ4_Width				((reg_field_width_t) 5U)
/** @brief Regular sequencer rank 4 (`ADCx_SQR3.SQ4`) field mask @def ADC_SQR3_SQ4_Msk */
#define ADC_SQR3_SQ4_Msk				REG_FIELD_MASK(ADC_SQR3_SQ4_Pos, ADC_SQR3_SQ4_Width)
/** @brief Regular sequencer rank 4 (`ADCx_SQR3.SQ4`) field mask alias @def ADC_SQR3_SQ4 */
#define ADC_SQR3_SQ4					ADC_SQR3_SQ4_Msk
/** @brief Regular sequencer rank 4 (`ADCx_SQR3.SQ4[0]`) raw field bit 0 mask @def ADC_SQR3_SQ4_0 */
#define ADC_SQR3_SQ4_0					REG_FIELD_VALUE(ADC_SQR3_SQ4_Pos, 0x01UL)
/** @brief Regular sequencer rank 4 (`ADCx_SQR3.SQ4[1]`) raw field bit 1 mask @def ADC_SQR3_SQ4_1 */
#define ADC_SQR3_SQ4_1					REG_FIELD_VALUE(ADC_SQR3_SQ4_Pos, 0x02UL)
/** @brief Regular sequencer rank 4 (`ADCx_SQR3.SQ4[2]`) raw field bit 2 mask @def ADC_SQR3_SQ4_2 */
#define ADC_SQR3_SQ4_2					REG_FIELD_VALUE(ADC_SQR3_SQ4_Pos, 0x04UL)
/** @brief Regular sequencer rank 4 (`ADCx_SQR3.SQ4[3]`) raw field bit 3 mask @def ADC_SQR3_SQ4_3 */
#define ADC_SQR3_SQ4_3					REG_FIELD_VALUE(ADC_SQR3_SQ4_Pos, 0x08UL)
/** @brief Regular sequencer rank 4 (`ADCx_SQR3.SQ4[4]`) raw field bit 4 mask @def ADC_SQR3_SQ4_4 */
#define ADC_SQR3_SQ4_4					REG_FIELD_VALUE(ADC_SQR3_SQ4_Pos, 0x10UL)

/** @brief Regular sequencer rank 5 (`ADCx_SQR3.SQ5`) field position @def ADC_SQR3_SQ5_Pos */
#define ADC_SQR3_SQ5_Pos				((reg_bit_pos_t) 20U)
/** @brief Regular sequencer rank 5 (`ADCx_SQR3.SQ5`) field width @def ADC_SQR3_SQ5_Width */
#define ADC_SQR3_SQ5_Width				((reg_field_width_t) 5U)
/** @brief Regular sequencer rank 5 (`ADCx_SQR3.SQ5`) field mask @def ADC_SQR3_SQ5_Msk */
#define ADC_SQR3_SQ5_Msk				REG_FIELD_MASK(ADC_SQR3_SQ5_Pos, ADC_SQR3_SQ5_Width)
/** @brief Regular sequencer rank 5 (`ADCx_SQR3.SQ5`) field mask alias @def ADC_SQR3_SQ5 */
#define ADC_SQR3_SQ5					ADC_SQR3_SQ5_Msk
/** @brief Regular sequencer rank 5 (`ADCx_SQR3.SQ5[0]`) raw field bit 0 mask @def ADC_SQR3_SQ5_0 */
#define ADC_SQR3_SQ5_0					REG_FIELD_VALUE(ADC_SQR3_SQ5_Pos, 0x01UL)
/** @brief Regular sequencer rank 5 (`ADCx_SQR3.SQ5[1]`) raw field bit 1 mask @def ADC_SQR3_SQ5_1 */
#define ADC_SQR3_SQ5_1					REG_FIELD_VALUE(ADC_SQR3_SQ5_Pos, 0x02UL)
/** @brief Regular sequencer rank 5 (`ADCx_SQR3.SQ5[2]`) raw field bit 2 mask @def ADC_SQR3_SQ5_2 */
#define ADC_SQR3_SQ5_2					REG_FIELD_VALUE(ADC_SQR3_SQ5_Pos, 0x04UL)
/** @brief Regular sequencer rank 5 (`ADCx_SQR3.SQ5[3]`) raw field bit 3 mask @def ADC_SQR3_SQ5_3 */
#define ADC_SQR3_SQ5_3					REG_FIELD_VALUE(ADC_SQR3_SQ5_Pos, 0x08UL)
/** @brief Regular sequencer rank 5 (`ADCx_SQR3.SQ5[4]`) raw field bit 4 mask @def ADC_SQR3_SQ5_4 */
#define ADC_SQR3_SQ5_4					REG_FIELD_VALUE(ADC_SQR3_SQ5_Pos, 0x10UL)

/** @brief Regular sequencer rank 6 (`ADCx_SQR3.SQ6`) field position @def ADC_SQR3_SQ6_Pos */
#define ADC_SQR3_SQ6_Pos				((reg_bit_pos_t) 25U)
/** @brief Regular sequencer rank 6 (`ADCx_SQR3.SQ6`) field width @def ADC_SQR3_SQ6_Width */
#define ADC_SQR3_SQ6_Width				((reg_field_width_t) 5U)
/** @brief Regular sequencer rank 6 (`ADCx_SQR3.SQ6`) field mask @def ADC_SQR3_SQ6_Msk */
#define ADC_SQR3_SQ6_Msk				REG_FIELD_MASK(ADC_SQR3_SQ6_Pos, ADC_SQR3_SQ6_Width)
/** @brief Regular sequencer rank 6 (`ADCx_SQR3.SQ6`) field mask alias @def ADC_SQR3_SQ6 */
#define ADC_SQR3_SQ6					ADC_SQR3_SQ6_Msk
/** @brief Regular sequencer rank 6 (`ADCx_SQR3.SQ6[0]`) raw field bit 0 mask @def ADC_SQR3_SQ6_0 */
#define ADC_SQR3_SQ6_0					REG_FIELD_VALUE(ADC_SQR3_SQ6_Pos, 0x01UL)
/** @brief Regular sequencer rank 6 (`ADCx_SQR3.SQ6[1]`) raw field bit 1 mask @def ADC_SQR3_SQ6_1 */
#define ADC_SQR3_SQ6_1					REG_FIELD_VALUE(ADC_SQR3_SQ6_Pos, 0x02UL)
/** @brief Regular sequencer rank 6 (`ADCx_SQR3.SQ6[2]`) raw field bit 2 mask @def ADC_SQR3_SQ6_2 */
#define ADC_SQR3_SQ6_2					REG_FIELD_VALUE(ADC_SQR3_SQ6_Pos, 0x04UL)
/** @brief Regular sequencer rank 6 (`ADCx_SQR3.SQ6[3]`) raw field bit 3 mask @def ADC_SQR3_SQ6_3 */
#define ADC_SQR3_SQ6_3					REG_FIELD_VALUE(ADC_SQR3_SQ6_Pos, 0x08UL)
/** @brief Regular sequencer rank 6 (`ADCx_SQR3.SQ6[4]`) raw field bit 4 mask @def ADC_SQR3_SQ6_4 */
#define ADC_SQR3_SQ6_4					REG_FIELD_VALUE(ADC_SQR3_SQ6_Pos, 0x10UL)

// ---------------------------------------------------------------------------------------------------- //
// ADCx_JSQR
// ---------------------------------------------------------------------------------------------------- //

/** @brief Injected sequencer rank 1 (`ADCx_JSQR.JSQ1`) field position @def ADC_JSQR_JSQ1_Pos */
#define ADC_JSQR_JSQ1_Pos				((reg_bit_pos_t) 0U)
/** @brief Injected sequencer rank 1 (`ADCx_JSQR.JSQ1`) field width @def ADC_JSQR_JSQ1_Width */
#define ADC_JSQR_JSQ1_Width				((reg_field_width_t) 5U)
/** @brief Injected sequencer rank 1 (`ADCx_JSQR.JSQ1`) field mask @def ADC_JSQR_JSQ1_Msk */
#define ADC_JSQR_JSQ1_Msk				REG_FIELD_MASK(ADC_JSQR_JSQ1_Pos, ADC_JSQR_JSQ1_Width)
/** @brief Injected sequencer rank 1 (`ADCx_JSQR.JSQ1`) field mask alias @def ADC_JSQR_JSQ1 */
#define ADC_JSQR_JSQ1					ADC_JSQR_JSQ1_Msk
/** @brief Injected sequencer rank 1 (`ADCx_JSQR.JSQ1[0]`) raw field bit 0 mask @def ADC_JSQR_JSQ1_0 */
#define ADC_JSQR_JSQ1_0					REG_FIELD_VALUE(ADC_JSQR_JSQ1_Pos, 0x01UL)
/** @brief Injected sequencer rank 1 (`ADCx_JSQR.JSQ1[1]`) raw field bit 1 mask @def ADC_JSQR_JSQ1_1 */
#define ADC_JSQR_JSQ1_1					REG_FIELD_VALUE(ADC_JSQR_JSQ1_Pos, 0x02UL)
/** @brief Injected sequencer rank 1 (`ADCx_JSQR.JSQ1[2]`) raw field bit 2 mask @def ADC_JSQR_JSQ1_2 */
#define ADC_JSQR_JSQ1_2					REG_FIELD_VALUE(ADC_JSQR_JSQ1_Pos, 0x04UL)
/** @brief Injected sequencer rank 1 (`ADCx_JSQR.JSQ1[3]`) raw field bit 3 mask @def ADC_JSQR_JSQ1_3 */
#define ADC_JSQR_JSQ1_3					REG_FIELD_VALUE(ADC_JSQR_JSQ1_Pos, 0x08UL)
/** @brief Injected sequencer rank 1 (`ADCx_JSQR.JSQ1[4]`) raw field bit 4 mask @def ADC_JSQR_JSQ1_4 */
#define ADC_JSQR_JSQ1_4					REG_FIELD_VALUE(ADC_JSQR_JSQ1_Pos, 0x10UL)

/** @brief Injected sequencer rank 2 (`ADCx_JSQR.JSQ2`) field position @def ADC_JSQR_JSQ2_Pos */
#define ADC_JSQR_JSQ2_Pos				((reg_bit_pos_t) 5U)
/** @brief Injected sequencer rank 2 (`ADCx_JSQR.JSQ2`) field width @def ADC_JSQR_JSQ2_Width */
#define ADC_JSQR_JSQ2_Width				((reg_field_width_t) 5U)
/** @brief Injected sequencer rank 2 (`ADCx_JSQR.JSQ2`) field mask @def ADC_JSQR_JSQ2_Msk */
#define ADC_JSQR_JSQ2_Msk				REG_FIELD_MASK(ADC_JSQR_JSQ2_Pos, ADC_JSQR_JSQ2_Width)
/** @brief Injected sequencer rank 2 (`ADCx_JSQR.JSQ2`) field mask alias @def ADC_JSQR_JSQ2 */
#define ADC_JSQR_JSQ2					ADC_JSQR_JSQ2_Msk
/** @brief Injected sequencer rank 2 (`ADCx_JSQR.JSQ2[0]`) raw field bit 0 mask @def ADC_JSQR_JSQ2_0 */
#define ADC_JSQR_JSQ2_0					REG_FIELD_VALUE(ADC_JSQR_JSQ2_Pos, 0x01UL)
/** @brief Injected sequencer rank 2 (`ADCx_JSQR.JSQ2[1]`) raw field bit 1 mask @def ADC_JSQR_JSQ2_1 */
#define ADC_JSQR_JSQ2_1					REG_FIELD_VALUE(ADC_JSQR_JSQ2_Pos, 0x02UL)
/** @brief Injected sequencer rank 2 (`ADCx_JSQR.JSQ2[2]`) raw field bit 2 mask @def ADC_JSQR_JSQ2_2 */
#define ADC_JSQR_JSQ2_2					REG_FIELD_VALUE(ADC_JSQR_JSQ2_Pos, 0x04UL)
/** @brief Injected sequencer rank 2 (`ADCx_JSQR.JSQ2[3]`) raw field bit 3 mask @def ADC_JSQR_JSQ2_3 */
#define ADC_JSQR_JSQ2_3					REG_FIELD_VALUE(ADC_JSQR_JSQ2_Pos, 0x08UL)
/** @brief Injected sequencer rank 2 (`ADCx_JSQR.JSQ2[4]`) raw field bit 4 mask @def ADC_JSQR_JSQ2_4 */
#define ADC_JSQR_JSQ2_4					REG_FIELD_VALUE(ADC_JSQR_JSQ2_Pos, 0x10UL)

/** @brief Injected sequencer rank 3 (`ADCx_JSQR.JSQ3`) field position @def ADC_JSQR_JSQ3_Pos */
#define ADC_JSQR_JSQ3_Pos				((reg_bit_pos_t) 10U)
/** @brief Injected sequencer rank 3 (`ADCx_JSQR.JSQ3`) field width @def ADC_JSQR_JSQ3_Width */
#define ADC_JSQR_JSQ3_Width				((reg_field_width_t) 5U)
/** @brief Injected sequencer rank 3 (`ADCx_JSQR.JSQ3`) field mask @def ADC_JSQR_JSQ3_Msk */
#define ADC_JSQR_JSQ3_Msk				REG_FIELD_MASK(ADC_JSQR_JSQ3_Pos, ADC_JSQR_JSQ3_Width)
/** @brief Injected sequencer rank 3 (`ADCx_JSQR.JSQ3`) field mask alias @def ADC_JSQR_JSQ3 */
#define ADC_JSQR_JSQ3					ADC_JSQR_JSQ3_Msk
/** @brief Injected sequencer rank 3 (`ADCx_JSQR.JSQ3[0]`) raw field bit 0 mask @def ADC_JSQR_JSQ3_0 */
#define ADC_JSQR_JSQ3_0					REG_FIELD_VALUE(ADC_JSQR_JSQ3_Pos, 0x01UL)
/** @brief Injected sequencer rank 3 (`ADCx_JSQR.JSQ3[1]`) raw field bit 1 mask @def ADC_JSQR_JSQ3_1 */
#define ADC_JSQR_JSQ3_1					REG_FIELD_VALUE(ADC_JSQR_JSQ3_Pos, 0x02UL)
/** @brief Injected sequencer rank 3 (`ADCx_JSQR.JSQ3[2]`) raw field bit 2 mask @def ADC_JSQR_JSQ3_2 */
#define ADC_JSQR_JSQ3_2					REG_FIELD_VALUE(ADC_JSQR_JSQ3_Pos, 0x04UL)
/** @brief Injected sequencer rank 3 (`ADCx_JSQR.JSQ3[3]`) raw field bit 3 mask @def ADC_JSQR_JSQ3_3 */
#define ADC_JSQR_JSQ3_3					REG_FIELD_VALUE(ADC_JSQR_JSQ3_Pos, 0x08UL)
/** @brief Injected sequencer rank 3 (`ADCx_JSQR.JSQ3[4]`) raw field bit 4 mask @def ADC_JSQR_JSQ3_4 */
#define ADC_JSQR_JSQ3_4					REG_FIELD_VALUE(ADC_JSQR_JSQ3_Pos, 0x10UL)

/** @brief Injected sequencer rank 4 (`ADCx_JSQR.JSQ4`) field position @def ADC_JSQR_JSQ4_Pos */
#define ADC_JSQR_JSQ4_Pos				((reg_bit_pos_t) 15U)
/** @brief Injected sequencer rank 4 (`ADCx_JSQR.JSQ4`) field width @def ADC_JSQR_JSQ4_Width */
#define ADC_JSQR_JSQ4_Width				((reg_field_width_t) 5U)
/** @brief Injected sequencer rank 4 (`ADCx_JSQR.JSQ4`) field mask @def ADC_JSQR_JSQ4_Msk */
#define ADC_JSQR_JSQ4_Msk				REG_FIELD_MASK(ADC_JSQR_JSQ4_Pos, ADC_JSQR_JSQ4_Width)
/** @brief Injected sequencer rank 4 (`ADCx_JSQR.JSQ4`) field mask alias @def ADC_JSQR_JSQ4 */
#define ADC_JSQR_JSQ4					ADC_JSQR_JSQ4_Msk
/** @brief Injected sequencer rank 4 (`ADCx_JSQR.JSQ4[0]`) raw field bit 0 mask @def ADC_JSQR_JSQ4_0 */
#define ADC_JSQR_JSQ4_0					REG_FIELD_VALUE(ADC_JSQR_JSQ4_Pos, 0x01UL)
/** @brief Injected sequencer rank 4 (`ADCx_JSQR.JSQ4[1]`) raw field bit 1 mask @def ADC_JSQR_JSQ4_1 */
#define ADC_JSQR_JSQ4_1					REG_FIELD_VALUE(ADC_JSQR_JSQ4_Pos, 0x02UL)
/** @brief Injected sequencer rank 4 (`ADCx_JSQR.JSQ4[2]`) raw field bit 2 mask @def ADC_JSQR_JSQ4_2 */
#define ADC_JSQR_JSQ4_2					REG_FIELD_VALUE(ADC_JSQR_JSQ4_Pos, 0x04UL)
/** @brief Injected sequencer rank 4 (`ADCx_JSQR.JSQ4[3]`) raw field bit 3 mask @def ADC_JSQR_JSQ4_3 */
#define ADC_JSQR_JSQ4_3					REG_FIELD_VALUE(ADC_JSQR_JSQ4_Pos, 0x08UL)
/** @brief Injected sequencer rank 4 (`ADCx_JSQR.JSQ4[4]`) raw field bit 4 mask @def ADC_JSQR_JSQ4_4 */
#define ADC_JSQR_JSQ4_4					REG_FIELD_VALUE(ADC_JSQR_JSQ4_Pos, 0x10UL)

/** @brief Injected sequencer scan length (`ADCx_JSQR.JL`) field position @def ADC_JSQR_JL_Pos */
#define ADC_JSQR_JL_Pos					((reg_bit_pos_t) 20U)
/** @brief Injected sequencer scan length (`ADCx_JSQR.JL`) field width @def ADC_JSQR_JL_Width */
#define ADC_JSQR_JL_Width				((reg_field_width_t) 2U)
/** @brief Injected sequencer scan length (`ADCx_JSQR.JL`) field mask @def ADC_JSQR_JL_Msk */
#define ADC_JSQR_JL_Msk					REG_FIELD_MASK(ADC_JSQR_JL_Pos, ADC_JSQR_JL_Width)
/** @brief Injected sequencer scan length (`ADCx_JSQR.JL`) field mask alias @def ADC_JSQR_JL */
#define ADC_JSQR_JL						ADC_JSQR_JL_Msk
/** @brief Injected sequencer scan length (`ADCx_JSQR.JL[0]`) raw field bit 0 mask @def ADC_JSQR_JL_0 */
#define ADC_JSQR_JL_0					REG_FIELD_VALUE(ADC_JSQR_JL_Pos, 0x1UL)
/** @brief Injected sequencer scan length (`ADCx_JSQR.JL[1]`) raw field bit 1 mask @def ADC_JSQR_JL_1 */
#define ADC_JSQR_JL_1					REG_FIELD_VALUE(ADC_JSQR_JL_Pos, 0x2UL)

// ---------------------------------------------------------------------------------------------------- //
// ADCx_JDR1
// ---------------------------------------------------------------------------------------------------- //

/** @brief Injected sequencer rank 1 conversion data (`ADCx_JDR1.JDATA`) field position @def ADC_JDR1_JDATA_Pos */
#define ADC_JDR1_JDATA_Pos				((reg_bit_pos_t) 0U)
/** @brief Injected sequencer rank 1 conversion data (`ADCx_JDR1.JDATA`) field width @def ADC_JDR1_JDATA_Width */
#define ADC_JDR1_JDATA_Width			((reg_field_width_t) 16U)
/** @brief Injected sequencer rank 1 conversion data (`ADCx_JDR1.JDATA`) field mask @def ADC_JDR1_JDATA_Msk */
#define ADC_JDR1_JDATA_Msk				REG_FIELD_MASK(ADC_JDR1_JDATA_Pos, ADC_JDR1_JDATA_Width)
/** @brief Injected sequencer rank 1 conversion data (`ADCx_JDR1.JDATA`) field mask alias @def ADC_JDR1_JDATA */
#define ADC_JDR1_JDATA					ADC_JDR1_JDATA_Msk

// ---------------------------------------------------------------------------------------------------- //
// ADCx_JDR2
// ---------------------------------------------------------------------------------------------------- //

/** @brief Injected sequencer rank 2 conversion data (`ADCx_JDR2.JDATA`) field position @def ADC_JDR2_JDATA_Pos */
#define ADC_JDR2_JDATA_Pos				((reg_bit_pos_t) 0U)
/** @brief Injected sequencer rank 2 conversion data (`ADCx_JDR2.JDATA`) field width @def ADC_JDR2_JDATA_Width */
#define ADC_JDR2_JDATA_Width			((reg_field_width_t) 16U)
/** @brief Injected sequencer rank 2 conversion data (`ADCx_JDR2.JDATA`) field mask @def ADC_JDR2_JDATA_Msk */
#define ADC_JDR2_JDATA_Msk				REG_FIELD_MASK(ADC_JDR2_JDATA_Pos, ADC_JDR2_JDATA_Width)
/** @brief Injected sequencer rank 2 conversion data (`ADCx_JDR2.JDATA`) field mask alias @def ADC_JDR2_JDATA */
#define ADC_JDR2_JDATA					ADC_JDR2_JDATA_Msk

// ---------------------------------------------------------------------------------------------------- //
// ADCx_JDR3
// ---------------------------------------------------------------------------------------------------- //

/** @brief Injected sequencer rank 3 conversion data (`ADCx_JDR3.JDATA`) field position @def ADC_JDR3_JDATA_Pos */
#define ADC_JDR3_JDATA_Pos				((reg_bit_pos_t) 0U)
/** @brief Injected sequencer rank 3 conversion data (`ADCx_JDR3.JDATA`) field width @def ADC_JDR3_JDATA_Width */
#define ADC_JDR3_JDATA_Width			((reg_field_width_t) 16U)
/** @brief Injected sequencer rank 3 conversion data (`ADCx_JDR3.JDATA`) field mask @def ADC_JDR3_JDATA_Msk */
#define ADC_JDR3_JDATA_Msk				REG_FIELD_MASK(ADC_JDR3_JDATA_Pos, ADC_JDR3_JDATA_Width)
/** @brief Injected sequencer rank 3 conversion data (`ADCx_JDR3.JDATA`) field mask alias @def ADC_JDR3_JDATA */
#define ADC_JDR3_JDATA					ADC_JDR3_JDATA_Msk

// ---------------------------------------------------------------------------------------------------- //
// ADCx_JDR4
// ---------------------------------------------------------------------------------------------------- //

/** @brief Injected sequencer rank 4 conversion data (`ADCx_JDR4.JDATA`) field position @def ADC_JDR4_JDATA_Pos */
#define ADC_JDR4_JDATA_Pos				((reg_bit_pos_t) 0U)
/** @brief Injected sequencer rank 4 conversion data (`ADCx_JDR4.JDATA`) field width @def ADC_JDR4_JDATA_Width */
#define ADC_JDR4_JDATA_Width			((reg_field_width_t) 16U)
/** @brief Injected sequencer rank 4 conversion data (`ADCx_JDR4.JDATA`) field mask @def ADC_JDR4_JDATA_Msk */
#define ADC_JDR4_JDATA_Msk				REG_FIELD_MASK(ADC_JDR4_JDATA_Pos, ADC_JDR4_JDATA_Width)
/** @brief Injected sequencer rank 4 conversion data (`ADCx_JDR4.JDATA`) field mask alias @def ADC_JDR4_JDATA */
#define ADC_JDR4_JDATA					ADC_JDR4_JDATA_Msk

// ---------------------------------------------------------------------------------------------------- //
// ADCx_DR
// ---------------------------------------------------------------------------------------------------- //

/** @brief Regular conversion data (`ADCx_DR.DATA`) field position @def ADC_DR_DATA_Pos */
#define ADC_DR_DATA_Pos					((reg_bit_pos_t) 0U)
/** @brief Regular conversion data (`ADCx_DR.DATA`) field width @def ADC_DR_DATA_Width */
#define ADC_DR_DATA_Width				((reg_field_width_t) 16U)
/** @brief Regular conversion data (`ADCx_DR.DATA`) field mask @def ADC_DR_DATA_Msk */
#define ADC_DR_DATA_Msk					REG_FIELD_MASK(ADC_DR_DATA_Pos, ADC_DR_DATA_Width)
/** @brief Regular conversion data (`ADCx_DR.DATA`) field mask alias @def ADC_DR_DATA */
#define ADC_DR_DATA						ADC_DR_DATA_Msk

/** @brief Regular conversion data for ADC slave, in multimode (`ADCx_DR.ADC2DATA`) field position @def ADC_DR_ADC2DATA_Pos */
#define ADC_DR_ADC2DATA_Pos				((reg_bit_pos_t) 16U)
/** @brief Regular conversion data for ADC slave, in multimode (`ADCx_DR.ADC2DATA`) field width @def ADC_DR_ADC2DATA_Width */
#define ADC_DR_ADC2DATA_Width			((reg_field_width_t) 16U)
/** @brief Regular conversion data for ADC slave, in multimode (`ADCx_DR.ADC2DATA`) field mask @def ADC_DR_ADC2DATA_Msk */
#define ADC_DR_ADC2DATA_Msk				REG_FIELD_MASK(ADC_DR_ADC2DATA_Pos, ADC_DR_ADC2DATA_Width)
/** @brief Regular conversion data for ADC slave, in multimode (`ADCx_DR.ADC2DATA`) field mask alias @def ADC_DR_ADC2DATA */
#define ADC_DR_ADC2DATA					ADC_DR_ADC2DATA_Msk

/** @} */ // ADC_01_RegisterLayer_00_RegisterDefines

// ==================================================================================================== //
// ADC Register Map
// ==================================================================================================== //

/**
 * @defgroup ADC_01_RegisterLayer_01_RegisterMap ADC Register Block Map
 * @ingroup ADC_01_RegisterLayer
 * @brief Memory-mapped ADC register block and practical register semantics
 * @details
 * @ref ADC_TypeDef is the raw peripheral view consumed by register-near code.
 * Full-register `.REG` members support register-image operations while `.BIT`
 * members expose named hardware fields. Action, write-zero-to-clear, and
 * read-to-clear behavior must follow each register's documented semantics.
 * @{
 */

/**
 * @brief ADC peripheral register block structure
 * @details Complete memory-mapped register map shared by ADC1 and ADC2. The
 * map preserves hardware access semantics, explicit reserved space, and the
 * ADC1 dual-mode packing of ADC2 data in the upper half of `DR`.
 * @see RM0008 Section 11.12 ADC registers
 * @struct ADC_TypeDef
 */
typedef volatile struct __ADC_TypeDef
{
	/**
	 * @section ADC_TypeDef_SR ADC Status Register (SR)
	 * @brief [R and write-zero-to-clear] Conversion, trigger-start, and analog-watchdog events
	 * @details
	 * All five event fields clear when software writes zero to the corresponding bit.
	 * Use a write-zero-to-clear image; a generic read-modify-write can clear events
	 * that become asserted between the read and write.
	 */
	union ADC_SR
	{
		/** @brief Full 32-bit `ADCx_SR` register image */
		_IO REG;
		/** @brief Named `ADCx_SR` bitfield view */
		struct
		{
			_IO AWD : 1;				/**< Analog-watchdog event; write zero to clear */
			_IO EOC : 1;				/**< Regular-conversion end event; write zero to clear */
			_IO JEOC : 1;				/**< Injected-conversion end event; write zero to clear */
			_IO JSTRT : 1;				/**< Injected-conversion start event; write zero to clear */
			_IO STRT : 1;				/**< Regular-conversion start event; write zero to clear */
			_IO reserved_1 : 27;		/**< Reserved */
		} BIT;
	} SR;		/**< ADC status event image and named-field views */

	/**
	 * @section ADC_TypeDef_CR1 ADC Control Register 1 (CR1)
	 * @brief [R/W] Watchdog, scan, discontinuous, multimode, and interrupt-source control
	 * @details
	 * `DUALMOD` is effective through ADC1 and coordinates ADC1 with ADC2.
	 * Interrupt-source enables are independent from the shared ADC1_2 NVIC line,
	 * priority, and pending state.
	 */
	union ADC_CR1
	{
		/** @brief Full 32-bit `ADCx_CR1` register image */
		_IO REG;
		/** @brief Named `ADCx_CR1` bitfield view */
		struct
		{
			_IO AWDCH : 5;				/**< Analog-watchdog monitored channel */
			_IO EOCIE : 1;				/**< Regular-conversion end interrupt-request enable */
			_IO AWDIE : 1;				/**< Analog-watchdog interrupt-request enable */
			_IO JEOCIE : 1;				/**< Injected-conversion end interrupt-request enable */
			_IO SCAN : 1;				/**< Scan-mode enable */
			_IO AWDSGL : 1;				/**< Single-channel watchdog selection */
			_IO JAUTO : 1;				/**< Automatic injected conversion enable */
			_IO DISCEN : 1;				/**< Regular discontinuous-mode enable */
			_IO JDISCEN : 1;			/**< Injected discontinuous-mode enable */
			_IO DISCNUM : 3;			/**< Regular discontinuous conversion count minus one */
			_IO DUALMOD : 4;			/**< ADC1/ADC2 multimode selection */
			_IO reserved_1 : 2;			/**< Reserved */
			_IO JAWDEN : 1;				/**< Injected-group watchdog enable */
			_IO AWDEN : 1;				/**< Regular-group watchdog enable */
			_IO reserved_2 : 8;			/**< Reserved */
		} BIT;
	} CR1;		/**< ADC control register 1 image and named-field views */

	/**
	 * @section ADC_TypeDef_CR2 ADC Control Register 2 (CR2)
	 * @brief [R/W and action] Operation, calibration, trigger, alignment, DMA, and internal-channel control
	 * @details
	 * `CAL` and `RSTCAL` launch hardware calibration actions and clear when done.
	 * `JSWSTART` and `SWSTART` launch conversions only when their trigger-enable
	 * conditions are satisfied. ADC wake-up, calibration, and start timing must follow
	 * the RM0008 sequencing requirements.
	 */
	union ADC_CR2
	{
		/** @brief Full 32-bit `ADCx_CR2` register image */
		_IO REG;
		/** @brief Named `ADCx_CR2` bitfield view */
		struct
		{
			_IO ADON : 1;				/**< ADC operation and wake-up control */
			_IO CONT : 1;				/**< Continuous-conversion enable */
			_IO CAL : 1;				/**< Calibration action request/state */
			_IO RSTCAL : 1;				/**< Calibration-register reset action request/state */
			_IO reserved_1 : 4;			/**< Reserved */
			_IO DMA : 1;				/**< Regular-conversion DMA request enable */
			_IO reserved_2 : 2;			/**< Reserved */
			_IO ALIGN : 1;				/**< Conversion-data alignment selection */
			_IO JEXTSEL : 3;			/**< Injected external-trigger selection */
			_IO JEXTTRIG : 1;			/**< Injected external-trigger enable */
			_IO reserved_3 : 1;			/**< Reserved */
			_IO EXTSEL : 3;				/**< Regular external-trigger selection */
			_IO EXTTRIG : 1;			/**< Regular external-trigger enable */
			_IO JSWSTART : 1;			/**< Injected software-start action */
			_IO SWSTART : 1;			/**< Regular software-start action */
			_IO TSVREFE : 1;			/**< Temperature sensor and VREFINT enable */
			_IO reserved_4 : 8;			/**< Reserved */
		} BIT;
	} CR2;		/**< ADC control register 2 image and named-field views */

	/**
	 * @section ADC_TypeDef_SMPR1 ADC Sample Time Register 1 (SMPR1)
	 * @brief [R/W] Sampling-cycle selection for channels 10 through 17
	 * @details
	 * Each field selects one of eight sample durations. Channel 16 is the ADC1
	 * temperature sensor and channel 17 is ADC1 VREFINT; both require `TSVREFE`.
	 */
	union ADC_SMPR1
	{
		/** @brief Full 32-bit `ADCx_SMPR1` register image */
		_IO REG;
		/** @brief Named `ADCx_SMPR1` bitfield view */
		struct
		{
			_IO SMP10 : 3;				/**< Channel 10 sampling-time selection */
			_IO SMP11 : 3;				/**< Channel 11 sampling-time selection */
			_IO SMP12 : 3;				/**< Channel 12 sampling-time selection */
			_IO SMP13 : 3;				/**< Channel 13 sampling-time selection */
			_IO SMP14 : 3;				/**< Channel 14 sampling-time selection */
			_IO SMP15 : 3;				/**< Channel 15 sampling-time selection */
			_IO SMP16 : 3;				/**< Channel 16 sampling-time selection */
			_IO SMP17 : 3;				/**< Channel 17 sampling-time selection */
			_IO reserved_1 : 8;			/**< Reserved */
		} BIT;
	} SMPR1;	/**< ADC sample-time register 1 image and named-field views */

	/**
	 * @section ADC_TypeDef_SMPR2 ADC Sample Time Register 2 (SMPR2)
	 * @brief [R/W] Sampling-cycle selection for channels 0 through 9
	 * @details
	 * Each field selects one of eight sample durations. Sampling time must satisfy
	 * the source-impedance and ADC-clock constraints of the connected signal.
	 */
	union ADC_SMPR2
	{
		/** @brief Full 32-bit `ADCx_SMPR2` register image */
		_IO REG;
		/** @brief Named `ADCx_SMPR2` bitfield view */
		struct
		{
			_IO SMP0 : 3;				/**< Channel 0 sampling-time selection */
			_IO SMP1 : 3;				/**< Channel 1 sampling-time selection */
			_IO SMP2 : 3;				/**< Channel 2 sampling-time selection */
			_IO SMP3 : 3;				/**< Channel 3 sampling-time selection */
			_IO SMP4 : 3;				/**< Channel 4 sampling-time selection */
			_IO SMP5 : 3;				/**< Channel 5 sampling-time selection */
			_IO SMP6 : 3;				/**< Channel 6 sampling-time selection */
			_IO SMP7 : 3;				/**< Channel 7 sampling-time selection */
			_IO SMP8 : 3;				/**< Channel 8 sampling-time selection */
			_IO SMP9 : 3;				/**< Channel 9 sampling-time selection */
			_IO reserved_1 : 2;			/**< Reserved */
		} BIT;
	} SMPR2;	/**< ADC sample-time register 2 image and named-field views */

	/**
	 * @section ADC_TypeDef_JOFR1 ADC Injected Channel Data Offset Register 1 (JOFR1)
	 * @brief [R/W] Injected rank 1 result offset
	 * @details
	 * Hardware subtracts this 12-bit value from the associated injected
	 * conversion result and publishes the signed result through `JDR1`.
	 */
	union ADC_JOFR1
	{
		/** @brief Full 32-bit `ADCx_JOFR1` register image */
		_IO REG;
		/** @brief Named `ADCx_JOFR1` bitfield view */
		struct
		{
			_IO JOFFSET1 : 12;			/**< Injected rank 1 data offset */
			_IO reserved_1 : 20;		/**< Reserved */
		} BIT;
	} JOFR1;	/**< ADC injected offset register 1 image and named-field views */

	/**
	 * @section ADC_TypeDef_JOFR2 ADC Injected Channel Data Offset Register 2 (JOFR2)
	 * @brief [R/W] Injected rank 2 result offset
	 * @details
	 * Hardware subtracts this 12-bit value from the associated injected
	 * conversion result and publishes the signed result through `JDR2`.
	 */
	union ADC_JOFR2
	{
		/** @brief Full 32-bit `ADCx_JOFR2` register image */
		_IO REG;
		/** @brief Named `ADCx_JOFR2` bitfield view */
		struct
		{
			_IO JOFFSET2 : 12;			/**< Injected rank 2 data offset */
			_IO reserved_1 : 20;		/**< Reserved */
		} BIT;
	} JOFR2;	/**< ADC injected offset register 2 image and named-field views */

	/**
	 * @section ADC_TypeDef_JOFR3 ADC Injected Channel Data Offset Register 3 (JOFR3)
	 * @brief [R/W] Injected rank 3 result offset
	 * @details
	 * Hardware subtracts this 12-bit value from the associated injected
	 * conversion result and publishes the signed result through `JDR3`.
	 */
	union ADC_JOFR3
	{
		/** @brief Full 32-bit `ADCx_JOFR3` register image */
		_IO REG;
		/** @brief Named `ADCx_JOFR3` bitfield view */
		struct
		{
			_IO JOFFSET3 : 12;			/**< Injected rank 3 data offset */
			_IO reserved_1 : 20;		/**< Reserved */
		} BIT;
	} JOFR3;	/**< ADC injected offset register 3 image and named-field views */

	/**
	 * @section ADC_TypeDef_JOFR4 ADC Injected Channel Data Offset Register 4 (JOFR4)
	 * @brief [R/W] Injected rank 4 result offset
	 * @details
	 * Hardware subtracts this 12-bit value from the associated injected
	 * conversion result and publishes the signed result through `JDR4`.
	 */
	union ADC_JOFR4
	{
		/** @brief Full 32-bit `ADCx_JOFR4` register image */
		_IO REG;
		/** @brief Named `ADCx_JOFR4` bitfield view */
		struct
		{
			_IO JOFFSET4 : 12;			/**< Injected rank 4 data offset */
			_IO reserved_1 : 20;		/**< Reserved */
		} BIT;
	} JOFR4;	/**< ADC injected offset register 4 image and named-field views */

	/**
	 * @section ADC_TypeDef_HTR ADC Watchdog High Threshold Register (HTR)
	 * @brief [R/W] Analog-watchdog upper threshold
	 * @details
	 * A monitored conversion outside the inclusive low/high window raises the
	 * analog-watchdog event according to the configured regular/injected scope.
	 */
	union ADC_HTR
	{
		/** @brief Full 32-bit `ADCx_HTR` register image */
		_IO REG;
		/** @brief Named `ADCx_HTR` bitfield view */
		struct
		{
			_IO HT : 12;				/**< Analog-watchdog high threshold */
			_IO reserved_1 : 20;		/**< Reserved */
		} BIT;
	} HTR;		/**< ADC watchdog high-threshold image and named-field views */

	/**
	 * @section ADC_TypeDef_LTR ADC Watchdog Low Threshold Register (LTR)
	 * @brief [R/W] Analog-watchdog lower threshold
	 * @details
	 * The low threshold must not exceed `HTR.HT` when analog-watchdog window
	 * monitoring is active.
	 */
	union ADC_LTR
	{
		/** @brief Full 32-bit `ADCx_LTR` register image */
		_IO REG;
		/** @brief Named `ADCx_LTR` bitfield view */
		struct
		{
			_IO LT : 12;				/**< Analog-watchdog low threshold */
			_IO reserved_1 : 20;		/**< Reserved */
		} BIT;
	} LTR;		/**< ADC watchdog low-threshold image and named-field views */

	/**
	 * @section ADC_TypeDef_SQR1 ADC Regular Sequence Register 1 (SQR1)
	 * @brief [R/W] Regular ranks 13 through 16 and complete sequence length
	 * @details
	 * `L` stores the regular sequence length minus one and is four bits wide.
	 * Ranks beyond the selected sequence length are ignored.
	 */
	union ADC_SQR1
	{
		/** @brief Full 32-bit `ADCx_SQR1` register image */
		_IO REG;
		/** @brief Named `ADCx_SQR1` bitfield view */
		struct
		{
			_IO SQ13 : 5;				/**< Regular rank 13 channel selection */
			_IO SQ14 : 5;				/**< Regular rank 14 channel selection */
			_IO SQ15 : 5;				/**< Regular rank 15 channel selection */
			_IO SQ16 : 5;				/**< Regular rank 16 channel selection */
			_IO L : 4;					/**< Regular sequence length minus one */
			_IO reserved_1 : 8;			/**< Reserved */
		} BIT;
	} SQR1;		/**< ADC regular sequence register 1 image and named-field views */

	/**
	 * @section ADC_TypeDef_SQR2 ADC Regular Sequence Register 2 (SQR2)
	 * @brief [R/W] Regular ranks 7 through 12
	 * @details
	 * Every five-bit rank field selects one ADC input channel. Sequence length is
	 * owned exclusively by `SQR1.L`.
	 */
	union ADC_SQR2
	{
		/** @brief Full 32-bit `ADCx_SQR2` register image */
		_IO REG;
		/** @brief Named `ADCx_SQR2` bitfield view */
		struct
		{
			_IO SQ7 : 5;				/**< Regular rank 7 channel selection */
			_IO SQ8 : 5;				/**< Regular rank 8 channel selection */
			_IO SQ9 : 5;				/**< Regular rank 9 channel selection */
			_IO SQ10 : 5;				/**< Regular rank 10 channel selection */
			_IO SQ11 : 5;				/**< Regular rank 11 channel selection */
			_IO SQ12 : 5;				/**< Regular rank 12 channel selection */
			_IO reserved_1 : 2;			/**< Reserved */
		} BIT;
	} SQR2;		/**< ADC regular sequence register 2 image and named-field views */

	/**
	 * @section ADC_TypeDef_SQR3 ADC Regular Sequence Register 3 (SQR3)
	 * @brief [R/W] Regular ranks 1 through 6
	 * @details
	 * `SQ1` is the first regular conversion rank. Every five-bit field selects
	 * one ADC input channel.
	 */
	union ADC_SQR3
	{
		/** @brief Full 32-bit `ADCx_SQR3` register image */
		_IO REG;
		/** @brief Named `ADCx_SQR3` bitfield view */
		struct
		{
			_IO SQ1 : 5;				/**< Regular rank 1 channel selection */
			_IO SQ2 : 5;				/**< Regular rank 2 channel selection */
			_IO SQ3 : 5;				/**< Regular rank 3 channel selection */
			_IO SQ4 : 5;				/**< Regular rank 4 channel selection */
			_IO SQ5 : 5;				/**< Regular rank 5 channel selection */
			_IO SQ6 : 5;				/**< Regular rank 6 channel selection */
			_IO reserved_1 : 2;			/**< Reserved */
		} BIT;
	} SQR3;		/**< ADC regular sequence register 3 image and named-field views */

	/**
	 * @section ADC_TypeDef_JSQR ADC Injected Sequence Register (JSQR)
	 * @brief [R/W] Injected sequence length and rank-to-channel selection
	 * @details
	 * `JL` stores the injected sequence length minus one. RM0008 right-aligns the
	 * active injected ranks within `JSQ1..JSQ4`; software must place channel
	 * selections according to the programmed length.
	 */
	union ADC_JSQR
	{
		/** @brief Full 32-bit `ADCx_JSQR` register image */
		_IO REG;
		/** @brief Named `ADCx_JSQR` bitfield view */
		struct
		{
			_IO JSQ1 : 5;				/**< Injected sequence slot 1 channel selection */
			_IO JSQ2 : 5;				/**< Injected sequence slot 2 channel selection */
			_IO JSQ3 : 5;				/**< Injected sequence slot 3 channel selection */
			_IO JSQ4 : 5;				/**< Injected sequence slot 4 channel selection */
			_IO JL : 2;					/**< Injected sequence length minus one */
			_IO reserved_1 : 10;		/**< Reserved */
		} BIT;
	} JSQR;		/**< ADC injected sequence image and named-field views */

	/**
	 * @section ADC_TypeDef_JDR1 ADC Injected Data Register 1 (JDR1)
	 * @brief [R] Injected conversion result 1 after offset application
	 * @details
	 * The 16-bit field represents the signed injected result produced after
	 * subtracting `JOFR1.JOFFSET1` from the 12-bit conversion result.
	 */
	union ADC_JDR1
	{
		/** @brief Full 32-bit `ADCx_JDR1` observation image */
		_I REG;
		/** @brief Named `ADCx_JDR1` bitfield view */
		struct
		{
			_I JDATA1 : 16;				/**< Injected conversion result 1 */
			_I reserved_1 : 16;			/**< Reserved */
		} BIT;
	} JDR1;		/**< ADC injected result 1 observation and named-field views */

	/**
	 * @section ADC_TypeDef_JDR2 ADC Injected Data Register 2 (JDR2)
	 * @brief [R] Injected conversion result 2 after offset application
	 * @details
	 * The 16-bit field represents the signed injected result produced after
	 * subtracting `JOFR2.JOFFSET2` from the 12-bit conversion result.
	 */
	union ADC_JDR2
	{
		/** @brief Full 32-bit `ADCx_JDR2` observation image */
		_I REG;
		/** @brief Named `ADCx_JDR2` bitfield view */
		struct
		{
			_I JDATA2 : 16;				/**< Injected conversion result 2 */
			_I reserved_1 : 16;			/**< Reserved */
		} BIT;
	} JDR2;		/**< ADC injected result 2 observation and named-field views */

	/**
	 * @section ADC_TypeDef_JDR3 ADC Injected Data Register 3 (JDR3)
	 * @brief [R] Injected conversion result 3 after offset application
	 * @details
	 * The 16-bit field represents the signed injected result produced after
	 * subtracting `JOFR3.JOFFSET3` from the 12-bit conversion result.
	 */
	union ADC_JDR3
	{
		/** @brief Full 32-bit `ADCx_JDR3` observation image */
		_I REG;
		/** @brief Named `ADCx_JDR3` bitfield view */
		struct
		{
			_I JDATA3 : 16;				/**< Injected conversion result 3 */
			_I reserved_1 : 16;			/**< Reserved */
		} BIT;
	} JDR3;		/**< ADC injected result 3 observation and named-field views */

	/**
	 * @section ADC_TypeDef_JDR4 ADC Injected Data Register 4 (JDR4)
	 * @brief [R] Injected conversion result 4 after offset application
	 * @details
	 * The 16-bit field represents the signed injected result produced after
	 * subtracting `JOFR4.JOFFSET4` from the 12-bit conversion result.
	 */
	union ADC_JDR4
	{
		/** @brief Full 32-bit `ADCx_JDR4` observation image */
		_I REG;
		/** @brief Named `ADCx_JDR4` bitfield view */
		struct
		{
			_I JDATA4 : 16;				/**< Injected conversion result 4 */
			_I reserved_1 : 16;			/**< Reserved */
		} BIT;
	} JDR4;		/**< ADC injected result 4 observation and named-field views */

	/**
	 * @section ADC_TypeDef_DR ADC Regular Data Register (DR)
	 * @brief [R data port] Regular result and ADC2 result in dual mode
	 * @details
	 * `DATA` occupies the low halfword. For ADC1 dual modes, `ADC2DATA` occupies
	 * the high halfword; otherwise the high halfword is not meaningful. Reading
	 * `DR` clears the regular end-of-conversion event, so this is an observation
	 * port rather than stable storage.
	 */
	union ADC_DR
	{
		/** @brief Full 32-bit `ADCx_DR` observation image */
		_I REG;
		/** @brief Named `ADCx_DR` bitfield view */
		struct
		{
			_I DATA : 16;				/**< Regular conversion result */
			_I ADC2DATA : 16;			/**< ADC2 regular result in dual mode */
		} BIT;
	} DR;		/**< ADC regular and dual-mode result observation views */
} ADC_TypeDef;

/** @} */ // ADC_01_RegisterLayer_01_RegisterMap

/** @} */ // ADC_01_RegisterLayer

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_ADC_H_ */
