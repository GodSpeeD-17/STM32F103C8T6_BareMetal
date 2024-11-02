// Header Guards
#ifndef __WWDG_REG_MAP_H__
#define __WWDG_REG_MAP_H__

// Core C Library
#include <stdint.h>

// Window WatchDog
typedef struct {
	// Control Register (CR)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t T: 7;
			volatile uint32_t WDGA: 1;
			volatile uint32_t reserved: 24;
		} BIT;
	} CR;
} WWDG_REG_STRUCT;

#endif /* __WWDG_REG_MAP_H__ */