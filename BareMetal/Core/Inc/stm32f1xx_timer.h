/**
 * @file stm32f1xx_timer.h
 * @author Shrey Shah
 * @brief STM32F1 Timer Register-Layer Definitions
 * @version v1.1
 * @date 07-06-2026
 */

// Header Guards
#ifndef STM32F1XX_TIMER_H_
#define STM32F1XX_TIMER_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "stm32f1xx_utils.h"

// --- C++ Safeguards ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup TIM General-Purpose Timer (TIM)
 * @brief STM32F1 timer counting, capture/compare, interrupt, DMA, and trigger infrastructure
 * @details
 * RM0008 describes the TIM2-TIM5-style general-purpose timer block as the
 * hardware engine that:
 * - counts up, down, or center-aligned through `TIMx_CNT`,
 * - scales the timer clock through `TIMx_PSC`,
 * - defines the reload period through `TIMx_ARR`,
 * - generates update, capture/compare, and trigger events,
 * - exposes capture/compare channels through `TIMx_CCMR1`, `TIMx_CCMR2`,
 *   `TIMx_CCER`, and `TIMx_CCR1..CCR4`,
 * - gates interrupt and DMA requests through `TIMx_DIER`.
 *
 * @section TIM_RegisterLayoutBrief Register Layout Brief
 * <table>
 * <tr><th>Register</th><th>Offset</th><th>Primary Practical Role</th></tr>
 * <tr><td><code>TIMx_CR1</code></td><td><code>0x00</code></td><td>Counter enable, update behavior, direction, alignment, preload, and clock division</td></tr>
 * <tr><td><code>TIMx_CR2</code></td><td><code>0x04</code></td><td>DMA capture/compare selection, master-mode output, and TI1 input selection</td></tr>
 * <tr><td><code>TIMx_SMCR</code></td><td><code>0x08</code></td><td>Slave-mode, trigger, master/slave synchronization, and external clock/filter control</td></tr>
 * <tr><td><code>TIMx_DIER</code></td><td><code>0x0C</code></td><td>Interrupt and DMA request enable bits</td></tr>
 * <tr><td><code>TIMx_SR</code></td><td><code>0x10</code></td><td>Status flags for update, capture/compare, trigger, and overcapture events</td></tr>
 * <tr><td><code>TIMx_EGR</code></td><td><code>0x14</code></td><td>Software event generation</td></tr>
 * <tr><td><code>TIMx_CCMR1</code></td><td><code>0x18</code></td><td>Capture/compare mode control for channels 1 and 2</td></tr>
 * <tr><td><code>TIMx_CCMR2</code></td><td><code>0x1C</code></td><td>Capture/compare mode control for channels 3 and 4</td></tr>
 * <tr><td><code>TIMx_CCER</code></td><td><code>0x20</code></td><td>Capture/compare channel enable and polarity control</td></tr>
 * <tr><td><code>TIMx_CNT</code></td><td><code>0x24</code></td><td>Counter value</td></tr>
 * <tr><td><code>TIMx_PSC</code></td><td><code>0x28</code></td><td>Prescaler value</td></tr>
 * <tr><td><code>TIMx_ARR</code></td><td><code>0x2C</code></td><td>Auto-reload value</td></tr>
 * <tr><td><code>TIMx_CCR1</code></td><td><code>0x34</code></td><td>Capture/compare value for channel 1</td></tr>
 * <tr><td><code>TIMx_CCR2</code></td><td><code>0x38</code></td><td>Capture/compare value for channel 2</td></tr>
 * <tr><td><code>TIMx_CCR3</code></td><td><code>0x3C</code></td><td>Capture/compare value for channel 3</td></tr>
 * <tr><td><code>TIMx_CCR4</code></td><td><code>0x40</code></td><td>Capture/compare value for channel 4</td></tr>
 * <tr><td><code>TIMx_DCR</code></td><td><code>0x48</code></td><td>DMA burst base address and burst length</td></tr>
 * <tr><td><code>TIMx_DMAR</code></td><td><code>0x4C</code></td><td>DMA burst transfer access window</td></tr>
 * </table>
 *
 * This codebase documents Timer in layered ownership order:
 * - Register layer: @ref `stm32f1xx_timer.h`
 * - Driver selector vocabulary: @ref `timer_defines.h`
 * - Driver/orchestration layer: @ref `timer.h`
 */

/**
 * @defgroup TIM_01_RegisterLayer Timer Register Layer
 * @ingroup TIM
 * @brief Raw STM32F1 Timer register structure and hardware-visible register views
 * @details
 * This layer mirrors the hardware register map. It intentionally owns only raw
 * register structure layout and named bitfield views. Driver-facing selectors,
 * validation, encoding, read-modify-write batching, and interrupt policy belong
 * in higher Timer layers.
 */

/**
 * @addtogroup TIM_01_RegisterLayer
 * @{
 */

// ==================================================================================================== //
//											Timer Register Map											//
// ==================================================================================================== //

/**
 * @defgroup TIM_01_RegisterLayer_01_RegisterMap Timer Register Block Map
 * @ingroup TIM_01_RegisterLayer
 * @brief Memory-mapped Timer register block and practical register layout
 * @details
 * @section TIM_RegisterMap_Theory Theory and Practical Role
 * @ref TIM_TypeDef is the raw peripheral view consumed by Timer low-level code.
 * It exposes full-register `.REG` access for register-image operations and
 * named `.BIT` views for direct field inspection where useful.
 *
 * @section TIM_RegisterMap_Structure Timer Register Block Structure
 * The structure below is ordered by the STM32F1 general-purpose timer memory
 * map. Reserved words are kept in the structure so later registers remain at
 * their hardware offsets.
 * @{
 */

/**
 * @brief General-purpose Timer register block structure
 * @details
 * Complete memory-mapped register map for the TIM2-TIM5-style general-purpose
 * timer peripheral. On STM32F103C8T6, public base-address exposure determines
 * which concrete TIM instances are available.
 *
 * @see RM0008 Section 15.4 TIMx registers
 * @typedef TIM_TypeDef
 */
typedef volatile struct __TIM_TypeDef
{
	/**
	 * @section TIM_TypeDef_CR1 Timer Control Register 1 (CR1)
	 * @brief [R/W] Counter control, update behavior, direction, alignment, preload, and clock division
	 * @details
	 * `TIMx_CR1` owns the primary runtime counter controls. The Timer codec layer
	 * should translate driver-facing count-mode selectors into the raw `DIR` and
	 * `CMS` fields rather than letting public driver code write those fields directly.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_CR1` register image */
		_IO REG;
		/** @brief Named `TIMx_CR1` bitfield view */
		struct
		{
			_IO CEN : 1;			/**< Counter enable */
			_IO UDIS : 1;			/**< Update disable */
			_IO URS : 1;			/**< Update request source */
			_IO OPM : 1;			/**< One-pulse mode */
			_IO DIR : 1;			/**< Direction */
			_IO CMS : 2;			/**< Center-aligned mode selection */
			_IO ARPE : 1;			/**< Auto-reload preload enable */
			_IO CKD : 2;			/**< Clock division */
			_IO reserved : 22;		/**< Reserved */
		} BIT;
	} CR1;

	/**
	 * @section TIM_TypeDef_CR2 Timer Control Register 2 (CR2)
	 * @brief [R/W] Capture/compare DMA selection, master-mode output, and TI1 selection
	 * @details
	 * `TIMx_CR2` configures secondary timer behavior used for DMA request
	 * routing and timer synchronization through trigger output.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_CR2` register image */
		_IO REG;
		/** @brief Named `TIMx_CR2` bitfield view */
		struct
		{
			_IO reserved_1 : 3;		/**< Reserved */
			_IO CCDS : 1;			/**< Capture/compare DMA selection */
			_IO MMS : 3;			/**< Master mode selection */
			_IO TI1S : 1;			/**< TI1 selection */
			_IO reserved_2 : 24;	/**< Reserved */
		} BIT;
	} CR2;

	/**
	 * @section TIM_TypeDef_SMCR Timer Slave Mode Control Register (SMCR)
	 * @brief [R/W] Slave-mode, trigger, synchronization, and external clock/filter control
	 * @details
	 * `TIMx_SMCR` selects slave-mode behavior, trigger source, master/slave
	 * synchronization, external trigger filtering, and external clock mode bits.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_SMCR` register image */
		_IO REG;
		/** @brief Named `TIMx_SMCR` bitfield view */
		struct
		{
			_IO SMS : 3;			/**< Slave mode selection */
			_IO reserved_1 : 1;		/**< Reserved */
			_IO TS : 3;				/**< Trigger selection */
			_IO MSM : 1;			/**< Master/slave mode */
			_IO ETF : 4;			/**< External trigger filter */
			_IO ETPS : 2;			/**< External trigger prescaler */
			_IO ECE : 1;			/**< External clock enable */
			_IO ETP : 1;			/**< External trigger polarity */
			_IO reserved_2 : 16;	/**< Reserved */
		} BIT;
	} SMCR;

	/**
	 * @section TIM_TypeDef_DIER Timer DMA/Interrupt Enable Register (DIER)
	 * @brief [R/W] Interrupt and DMA request enables
	 * @details
	 * `TIMx_DIER` gates update, capture/compare, and trigger interrupt/DMA
	 * requests. NVIC enable/disable policy is intentionally outside this raw
	 * register layer.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_DIER` register image */
		_IO REG;
		/** @brief Named `TIMx_DIER` bitfield view */
		struct
		{
			_IO UIE : 1;			/**< Update interrupt enable */
			_IO CC1IE : 1;			/**< Capture/compare 1 interrupt enable */
			_IO CC2IE : 1;			/**< Capture/compare 2 interrupt enable */
			_IO CC3IE : 1;			/**< Capture/compare 3 interrupt enable */
			_IO CC4IE : 1;			/**< Capture/compare 4 interrupt enable */
			_IO reserved_1 : 1;		/**< Reserved */
			_IO TIE : 1;			/**< Trigger interrupt enable */
			_IO reserved_2 : 1;		/**< Reserved */
			_IO UDE : 1;			/**< Update DMA request enable */
			_IO CC1DE : 1;			/**< Capture/compare 1 DMA request enable */
			_IO CC2DE : 1;			/**< Capture/compare 2 DMA request enable */
			_IO CC3DE : 1;			/**< Capture/compare 3 DMA request enable */
			_IO CC4DE : 1;			/**< Capture/compare 4 DMA request enable */
			_IO reserved_3 : 1;		/**< Reserved */
			_IO TDE : 1;			/**< Trigger DMA request enable */
			_IO reserved_4 : 17;	/**< Reserved */
		} BIT;
	} DIER;

	/**
	 * @section TIM_TypeDef_SR Timer Status Register (SR)
	 * @brief [R/W] Event flags for update, capture/compare, trigger, and overcapture status
	 * @details
	 * `TIMx_SR` reports timer event flags. Software clears supported flags by
	 * writing the hardware-defined clear value through a full-register or field
	 * access path owned by higher layers.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_SR` register image */
		_IO REG;
		/** @brief Named `TIMx_SR` bitfield view */
		struct
		{
			_IO UIF : 1;			/**< Update interrupt flag */
			_IO CC1IF : 1;			/**< Capture/compare 1 interrupt flag */
			_IO CC2IF : 1;			/**< Capture/compare 2 interrupt flag */
			_IO CC3IF : 1;			/**< Capture/compare 3 interrupt flag */
			_IO CC4IF : 1;			/**< Capture/compare 4 interrupt flag */
			_IO reserved_1 : 1;		/**< Reserved */
			_IO TIF : 1;			/**< Trigger interrupt flag */
			_IO reserved_2 : 2;		/**< Reserved */
			_IO CC1OF : 1;			/**< Capture/compare 1 overcapture flag */
			_IO CC2OF : 1;			/**< Capture/compare 2 overcapture flag */
			_IO CC3OF : 1;			/**< Capture/compare 3 overcapture flag */
			_IO CC4OF : 1;			/**< Capture/compare 4 overcapture flag */
			_IO reserved_3 : 19;	/**< Reserved */
		} BIT;
	} SR;

	/**
	 * @section TIM_TypeDef_EGR Timer Event Generation Register (EGR)
	 * @brief [W] Software event-generation register
	 * @details
	 * `TIMx_EGR` lets software request update, capture/compare, and trigger
	 * events. Event-generation sequencing belongs in the driver layer.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_EGR` register image */
		_IO REG;
		/** @brief Named `TIMx_EGR` bitfield view */
		struct
		{
			_IO UG : 1;				/**< Update generation */
			_IO CC1G : 1;			/**< Capture/compare 1 generation */
			_IO CC2G : 1;			/**< Capture/compare 2 generation */
			_IO CC3G : 1;			/**< Capture/compare 3 generation */
			_IO CC4G : 1;			/**< Capture/compare 4 generation */
			_IO reserved_1 : 1;		/**< Reserved */
			_IO TG : 1;				/**< Trigger generation */
			_IO reserved_2 : 25;	/**< Reserved */
		} BIT;
	} EGR;

	/**
	 * @section TIM_TypeDef_CCMR1 Timer Capture/Compare Mode Register 1 (CCMR1)
	 * @brief [R/W] Capture/compare mode control for channels 1 and 2
	 * @details
	 * `TIMx_CCMR1` has two hardware interpretations: output-compare mode (`OCM`)
	 * and input-capture mode (`ICM`). The `CC1S` and `CC2S` fields select which
	 * interpretation is meaningful for each channel.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_CCMR1` register image */
		_IO REG;
		/** @brief Output-compare and input-capture bitfield views for `TIMx_CCMR1` */
		union
		{
			/** @brief Output-compare mode field view for channels 1 and 2 */
			struct
			{
				_IO CC1S : 2;		/**< Capture/compare 1 selection */
				_IO OC1FE : 1;		/**< Output compare 1 fast enable */
				_IO OC1PE : 1;		/**< Output compare 1 preload enable */
				_IO OC1M : 3;		/**< Output compare 1 mode */
				_IO OC1CE : 1;		/**< Output compare 1 clear enable */
				_IO CC2S : 2;		/**< Capture/compare 2 selection */
				_IO OC2FE : 1;		/**< Output compare 2 fast enable */
				_IO OC2PE : 1;		/**< Output compare 2 preload enable */
				_IO OC2M : 3;		/**< Output compare 2 mode */
				_IO OC2CE : 1;		/**< Output compare 2 clear enable */
				_IO reserved : 16;	/**< Reserved */
			} OCM;
			/** @brief Input-capture mode field view for channels 1 and 2 */
			struct
			{
				_IO CC1S : 2;		/**< Capture/compare 1 selection */
				_IO IC1PSC : 2;		/**< Input capture 1 prescaler */
				_IO IC1F : 4;		/**< Input capture 1 filter */
				_IO CC2S : 2;		/**< Capture/compare 2 selection */
				_IO IC2PSC : 2;		/**< Input capture 2 prescaler */
				_IO IC2F : 4;		/**< Input capture 2 filter */
				_IO reserved : 16;	/**< Reserved */
			} ICM;
		} BIT;
	} CCMR1;

	/**
	 * @section TIM_TypeDef_CCMR2 Timer Capture/Compare Mode Register 2 (CCMR2)
	 * @brief [R/W] Capture/compare mode control for channels 3 and 4
	 * @details
	 * `TIMx_CCMR2` has the same output-compare/input-capture split as
	 * `TIMx_CCMR1`, but applies to channels 3 and 4.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_CCMR2` register image */
		_IO REG;
		/** @brief Output-compare and input-capture bitfield views for `TIMx_CCMR2` */
		union
		{
			/** @brief Output-compare mode field view for channels 3 and 4 */
			struct
			{
				_IO CC3S : 2;		/**< Capture/compare 3 selection */
				_IO OC3FE : 1;		/**< Output compare 3 fast enable */
				_IO OC3PE : 1;		/**< Output compare 3 preload enable */
				_IO OC3M : 3;		/**< Output compare 3 mode */
				_IO OC3CE : 1;		/**< Output compare 3 clear enable */
				_IO CC4S : 2;		/**< Capture/compare 4 selection */
				_IO OC4FE : 1;		/**< Output compare 4 fast enable */
				_IO OC4PE : 1;		/**< Output compare 4 preload enable */
				_IO OC4M : 3;		/**< Output compare 4 mode */
				_IO OC4CE : 1;		/**< Output compare 4 clear enable */
				_IO reserved : 16;	/**< Reserved */
			} OCM;
			/** @brief Input-capture mode field view for channels 3 and 4 */
			struct
			{
				_IO CC3S : 2;		/**< Capture/compare 3 selection */
				_IO IC3PSC : 2;		/**< Input capture 3 prescaler */
				_IO IC3F : 4;		/**< Input capture 3 filter */
				_IO CC4S : 2;		/**< Capture/compare 4 selection */
				_IO IC4PSC : 2;		/**< Input capture 4 prescaler */
				_IO IC4F : 4;		/**< Input capture 4 filter */
				_IO reserved : 16;	/**< Reserved */
			} ICM;
		} BIT;
	} CCMR2;

	/**
	 * @section TIM_TypeDef_CCER Timer Capture/Compare Enable Register (CCER)
	 * @brief [R/W] Capture/compare output enable and polarity control
	 * @details
	 * `TIMx_CCER` enables each capture/compare channel and controls the active
	 * polarity for each channel signal.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_CCER` register image */
		_IO REG;
		/** @brief Named `TIMx_CCER` bitfield view */
		struct
		{
			_IO CC1E : 1;			/**< Capture/compare 1 output enable */
			_IO CC1P : 1;			/**< Capture/compare 1 output polarity */
			_IO reserved_1 : 2;		/**< Reserved */
			_IO CC2E : 1;			/**< Capture/compare 2 output enable */
			_IO CC2P : 1;			/**< Capture/compare 2 output polarity */
			_IO reserved_2 : 2;		/**< Reserved */
			_IO CC3E : 1;			/**< Capture/compare 3 output enable */
			_IO CC3P : 1;			/**< Capture/compare 3 output polarity */
			_IO reserved_3 : 2;		/**< Reserved */
			_IO CC4E : 1;			/**< Capture/compare 4 output enable */
			_IO CC4P : 1;			/**< Capture/compare 4 output polarity */
			_IO reserved_4 : 18;	/**< Reserved */
		} BIT;
	} CCER;

	/**
	 * @section TIM_TypeDef_CNT Timer Counter Register (CNT)
	 * @brief [R/W] Current counter value
	 * @details
	 * `TIMx_CNT` holds the current timer counter value. General-purpose timers in
	 * this target family use the low 16 bits.
	 */
	_IO CNT;

	/**
	 * @section TIM_TypeDef_PSC Timer Prescaler Register (PSC)
	 * @brief [R/W] Counter clock prescaler value
	 * @details
	 * `TIMx_PSC` divides the timer input clock by `PSC + 1`.
	 */
	_IO PSC;

	/**
	 * @section TIM_TypeDef_ARR Timer Auto-Reload Register (ARR)
	 * @brief [R/W] Auto-reload period value
	 * @details
	 * `TIMx_ARR` holds the period boundary used by update-event generation.
	 */
	_IO ARR;

	/** @brief Reserved word at offset `0x30` */
	_IO RESERVED_1;

	/**
	 * @section TIM_TypeDef_CCR1 Timer Capture/Compare Register 1 (CCR1)
	 * @brief [R/W] Capture/compare value for channel 1
	 * @details
	 * `CC1_IN` and `CC1_OUT` are aliases for the same hardware register image.
	 * The active meaning depends on the channel mode selected in `TIMx_CCMR1`.
	 */
	union
	{
		_IO CC1_IN;				/**< Input-capture view of channel 1 capture/compare value */
		_IO CC1_OUT;			/**< Output-compare view of channel 1 capture/compare value */
	} CCR1;

	/**
	 * @section TIM_TypeDef_CCR2 Timer Capture/Compare Register 2 (CCR2)
	 * @brief [R/W] Capture/compare value for channel 2
	 * @details
	 * `CC2_IN` and `CC2_OUT` are aliases for the same hardware register image.
	 * The active meaning depends on the channel mode selected in `TIMx_CCMR1`.
	 */
	union
	{
		_IO CC2_IN;				/**< Input-capture view of channel 2 capture/compare value */
		_IO CC2_OUT;			/**< Output-compare view of channel 2 capture/compare value */
	} CCR2;

	/**
	 * @section TIM_TypeDef_CCR3 Timer Capture/Compare Register 3 (CCR3)
	 * @brief [R/W] Capture/compare value for channel 3
	 * @details
	 * `CC3_IN` and `CC3_OUT` are aliases for the same hardware register image.
	 * The active meaning depends on the channel mode selected in `TIMx_CCMR2`.
	 */
	union
	{
		_IO CC3_IN;				/**< Input-capture view of channel 3 capture/compare value */
		_IO CC3_OUT;			/**< Output-compare view of channel 3 capture/compare value */
	} CCR3;

	/**
	 * @section TIM_TypeDef_CCR4 Timer Capture/Compare Register 4 (CCR4)
	 * @brief [R/W] Capture/compare value for channel 4
	 * @details
	 * `CC4_IN` and `CC4_OUT` are aliases for the same hardware register image.
	 * The active meaning depends on the channel mode selected in `TIMx_CCMR2`.
	 */
	union
	{
		_IO CC4_IN;				/**< Input-capture view of channel 4 capture/compare value */
		_IO CC4_OUT;			/**< Output-compare view of channel 4 capture/compare value */
	} CCR4;

	/** @brief Reserved word at offset `0x44` */
	_IO RESERVED_2;

	/**
	 * @section TIM_TypeDef_DCR Timer DMA Control Register (DCR)
	 * @brief [R/W] DMA burst base address and burst length configuration
	 * @details
	 * `TIMx_DCR` configures the starting register offset and number of transfers
	 * used by timer DMA burst operations through `TIMx_DMAR`.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_DCR` register image */
		_IO REG;
		/** @brief Named `TIMx_DCR` bitfield view */
		struct
		{
			_IO DBA : 5;			/**< DMA base address */
			_IO reserved_1 : 3;		/**< Reserved */
			_IO DBL : 5;			/**< DMA burst length */
			_IO reserved_2 : 19;	/**< Reserved */
		} BIT;
	} DCR;

	/**
	 * @section TIM_TypeDef_DMAR Timer DMA Address Register (DMAR)
	 * @brief [R/W] DMA burst transfer register access window
	 * @details
	 * `TIMx_DMAR` is the data access window used for DMA burst transfers
	 * configured by `TIMx_DCR`.
	 */
	_IO DMAR;
} TIM_TypeDef;

/** @} */ // TIM_01_RegisterLayer_01_RegisterMap

/** @} */ // TIM_01_RegisterLayer

// --- C++ Safeguards ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_TIMER_H_ */
