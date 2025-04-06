/***************************************************************************************
 *  File: bare_metal.h
 *  Created on: 10/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __BARE_METAL_H__
#define __BARE_METAL_H__

// Core C Libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// STM32F103C8T6 Specific Libraries
#include "adc.h"
#include "exti.h"
#include "gpio.h"
#include "nvic.h"
#include "pwm.h"
#include "rcc.h"
#include "systick.h"
#include "timer.h"
#include "usart.h"
#include "i2c.h"

#endif /* __BARE_METAL_H__ */