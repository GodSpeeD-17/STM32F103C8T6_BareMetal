// Main Header
#include "main.h"

// Main Entry Point for User Code
int main(void){
    
    // Configure Clock
    config_SYSCLK_MHz(SYSCLK_MHz);

    // SysTick Timer (1ms)
    config_SysTick(CoreClock/1000);

    // Error Check
    IS_TIMx_GPT(GP_TIMER);

    // Disable Timer
    disable_GPT(GP_TIMER);

    // Configure Timer
    config_GPT(GP_TIMER, TIMER_ARR, TIMER_FREQ, TIMER_CNT);

    // Infinite Loop
    while(1){

    }
    
    // Return Value
    return 0;
}
