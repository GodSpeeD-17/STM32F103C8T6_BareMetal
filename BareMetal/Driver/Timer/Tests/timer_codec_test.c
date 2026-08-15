#include <assert.h>

#include "timer_codec.h"

static void test_counter_config_round_trip(void)
{
	const reg ownedMask = TIM_CR1_DIR | TIM_CR1_CMS | TIM_CR1_OPM |
		TIM_CR1_ARPE | TIM_CR1_URS | TIM_CR1_CKD;
	const reg preservedBits = 0xA5A50000UL | TIM_CR1_CEN | TIM_CR1_UDIS;
	reg cr1RegImage = preservedBits;
	tim_config_counter_t extracted;
	const tim_config_counter_t requested =
	{
		.direction = TIMx_DIR_COUNT_DOWN,
		.alignment = TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING,
		.one_pulse = TIMx_OPM_ENABLE,
		.auto_reload_preload = TIMx_ARPE_ENABLE,
		.update_source = TIMx_UPDATE_SOURCE_OVF_DMA,
		.clock_division = TIMx_CKD_CLK_4_FREQ
	};

	assert(Codec_TIM_StageCounterConfig(&cr1RegImage, &requested) == DRIVER_STATUS_SUCCESS);
	assert((cr1RegImage & ~ownedMask) == (preservedBits & ~ownedMask));
	assert(Codec_TIM_ExtractCounterConfig(cr1RegImage, &extracted) == DRIVER_STATUS_SUCCESS);
	assert(extracted.direction == requested.direction);
	assert(extracted.alignment == requested.alignment);
	assert(extracted.one_pulse == requested.one_pulse);
	assert(extracted.auto_reload_preload == requested.auto_reload_preload);
	assert(extracted.update_source == requested.update_source);
	assert(extracted.clock_division == requested.clock_division);
	assert(Codec_TIM_ExtractClockDivision(TIM_CR1_CKD_RESERVED, &extracted.clock_division) == DRIVER_STATUS_ERROR_INVALID_ARG);
}

static void test_timebase_round_trip(void)
{
	reg pscRegImage = 0xA5A50000UL;
	reg arrRegImage = 0x5A5A0000UL;
	reg cntRegImage = 0xFFFF0000UL;
	tim_config_timebase_t extracted;
	const tim_config_timebase_t requested =
	{
		.prescaler = (tim_prescaler_t) 71U,
		.auto_reload = (tim_auto_reload_t) 999U,
		.initial_count = (tim_counter_value_t) 123U
	};

	assert(Codec_TIM_StageTimeBaseConfig(&pscRegImage, &arrRegImage, &cntRegImage, &requested) == DRIVER_STATUS_SUCCESS);
	assert((pscRegImage & 0xFFFF0000UL) == 0xA5A50000UL);
	assert((arrRegImage & 0xFFFF0000UL) == 0x5A5A0000UL);
	assert((cntRegImage & 0xFFFF0000UL) == 0xFFFF0000UL);
	assert(Codec_TIM_ExtractTimeBaseConfig(pscRegImage, arrRegImage, cntRegImage, &extracted) == DRIVER_STATUS_SUCCESS);
	assert(extracted.prescaler == requested.prescaler);
	assert(extracted.auto_reload == requested.auto_reload);
	assert(extracted.initial_count == requested.initial_count);
}

static void test_irq_codec(void)
{
	reg dierRegImage = 0x80000000UL;
	reg srRegImage = TIM_SR_UIF | TIM_SR_CC1IF | TIM_SR_CC3IF;
	tim_irq_t irqMask = (tim_irq_t) 0U;

	assert(Codec_TIM_StageIRQEnableMask
	(
		&dierRegImage,
		(tim_irq_t) (TIMx_IRQ_OVF_UVF | TIMx_IRQ_OUT_CMP_CH3),
		TIMx_IRQ_ENABLE
	) == DRIVER_STATUS_SUCCESS);
	assert((dierRegImage & 0x80000000UL) != 0UL);
	assert(Codec_TIM_ExtractIRQEnableMask(dierRegImage, &irqMask) == DRIVER_STATUS_SUCCESS);
	assert(irqMask == (tim_irq_t) (TIMx_IRQ_OVF_UVF | TIMx_IRQ_OUT_CMP_CH3));

	assert(Codec_TIM_StageIRQAckMask(&srRegImage, TIMx_IRQ_OVF_UVF) == DRIVER_STATUS_SUCCESS);
	assert((srRegImage & TIM_SR_UIF) == 0UL);
	assert((srRegImage & TIM_SR_CC1IF) != 0UL);
	assert((srRegImage & TIM_SR_CC3IF) != 0UL);
}

int main(void)
{
	test_counter_config_round_trip();
	test_timebase_round_trip();
	test_irq_codec();
	return 0;
}
