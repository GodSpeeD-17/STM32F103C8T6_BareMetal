/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(void){
	// Initialisation
	(void) TIM_ConfigTickFrequency(TIM3, (tim_frequency_t) 10000UL);
	(void) TIM_SetAutoReload(TIM3, (tim_auto_reload_t) 9999U);
	// Enable the Timer 3 update interrupt
	(void) TIM_SetIRQState(TIM3, TIMx_IRQ_OVF_UVF, DRIVER_STATUS_ON);
	// Enable Timer 3
	(void) TIM_SetOperationState(TIM3, DRIVER_STATUS_ON);
	// Infinite Loop
	while(1){
		// Do Nothing
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/
// Timer IRQ Handler
void TIM3_IRQHandler(void){
	tim_irq_t pendingMask = (tim_irq_t) 0U;
	(void) TIM_GetPendingIRQMask(TIM3, &pendingMask);
	// Overflow/Underflow detected
	if((pendingMask & TIMx_IRQ_OVF_UVF) != (tim_irq_t) 0U){
		// Toggle OB LED
		OB_LED_Toggle();
		// Acknowledge the Interrupt
		(void) TIM_AcknowledgeIRQ(TIM3, TIMx_IRQ_OVF_UVF);
	}

}
/*-------------------------------------------------------------------------------*/
