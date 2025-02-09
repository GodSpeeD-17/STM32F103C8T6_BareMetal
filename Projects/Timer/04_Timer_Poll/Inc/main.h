// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

/*-------------------------------------------------------------------------------*/
// Headers
#include "bare_metal.h"
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
// MACROS
#define LOOP_DELAY_MS						((uint32_t) 1000)
#define ARR_VALUE                           ((uint16_t) 1000)
/*-------------------------------------------------------------------------------*/
// Timer 2 Configuration Structure
// - Freq = 1MHz, ARR = 1000
// - Update Event = Freq x ARR =  1MHz x 1000
// - Update Event = 1ms
timer_config_t TIM2_Config = {
	.arpe = TIMx_ARPE_ENABLE,
	.auto_reload = ARR_VALUE,
	.channel = TIMx_CHANNEL_3,
	.cms_mode = TIMx_CMS_EDGE,
	.count = 0,
	.direction = TIMx_DIR_COUNT_UP,
	.enable_IRQ = TIMx_IRQ_DISABLE,
	.GPIO_CONFIGx = NULL,
	.one_pulse = TIMx_OPM_ENABLE,
	.prescaler = (36 - 1),
	.TIMx = TIM2,
};

void TIMx_Delay_ms(volatile uint32_t delayMs);

#endif /* __MAIN_H__ */ 