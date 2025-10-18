// Header Guards
#ifndef STM32F1XX_WATCHDOG_H_
#define STM32F1XX_WATCHDOG_H_

// C++ Safeguard
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// Includes
#include <stdint.h>

// Independent WatchDog
typedef struct 
{
	// Key Register
	// - Write only, if read will yeild 0x0000
	// - Otherwise the watchdog generates a reset when the counter reaches 0x0000
	// - Writing 0x5555: Enable access to `PR` & `RLR`
	// - Writing 0xCCCC: Starts the watchdog
	// - Writing 0xAAAA: Regular intervals to feed the watchdog
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct
		{
			// Write here
			uint32_t KEY: 16;
			uint32_t RESERVED: 16;
		} BIT;
	} KR;
	// Prescaler Register
	// - Write access protected
	// - Select the prescaler divider feeding the counter clock
	// - PVU bit of IWDG_SR must be reset in order to be able to change the prescaler divider
	// - NOTE: value read from this register is valid only when the PVU bit in the `SR` register is reset.
	union
	{
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct
		{
			uint32_t PR: 3;
			uint32_t RESERVED: 29;
		} BIT;
	} PR;
	// Reload Register
	// - Defines the value to be loaded in the watchdog counter each time the value `0xAAAA` is written in the `KR`
	// - The watchdog counter counts down from this value. 
	// - The timeout period is a function of this value and the clock prescaler
	// - The RVU bit in the `SR` must be reset in order to be able to change the reload value
	union
	{
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct
		{
			uint32_t RLR: 12;
			uint32_t RESERVED: 20;
		} BIT;
	} RLR;
	// Status Register
	union
	{
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct
		{
			// Update of the prescaler value is ongoing
			uint32_t PVU: 1;
			// Update of the reload value is ongoing
			uint32_t RVU: 1;
			uint32_t RESERVED: 30;
		} BIT;
	} SR;
} IWDG_TypeDef;


// Window WatchDog
typedef struct {
	// Control Register (CR)
	union 
	{
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t T: 7;
			volatile uint32_t WDGA: 1;
			volatile uint32_t reserved: 24;
		} BIT;
	} CR;
	// Configuration Register (CFGR)
	union
	{
		uint32_t REG;
		struct 
		{
			volatile uint32_t W: 7;
			volatile uint32_t WDGTB: 2;
			volatile uint32_t EWI: 1;
			volatile uint32_t RESERVED: 22;
		} BIT;
	} CFGR;
	// Status Register (SR)
	union
	{
		uint32_t REG;
		struct
		{
			// Early wakeup interrupt flag
			uint32_t EWIF: 1;
			uint32_t RESERVED: 31;
		} BIT;
	} SR;
} WWDG_TypeDef;

// C++ Safeguards
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_WATCHDOG_H_ */