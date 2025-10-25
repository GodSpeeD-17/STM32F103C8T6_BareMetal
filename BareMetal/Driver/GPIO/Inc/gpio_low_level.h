/**
 * @file gpio_low_level.h
 * @author Shrey Shah
 * @brief GPIO Driver - Register Interaction 
 * @version v1.2
 * @date 25-10-2025
 */
#ifndef GPIO_LOW_LEVEL_H_
#define GPIO_LOW_LEVEL_H_

/*---------------------------------------------- C++ Safeguard ----------------------------------------------*/
#ifdef _cplusplus
extern "C" {
#endif /* _cplusplus */

/*---------------------------------------------- MACROs ----------------------------------------------*/
#define GPIO_CLK_POS(gpio) \
	BIT_POS((gpio), GPIOA, GPIO_TypeDef)

/*---------------------------------------------- Includes ----------------------------------------------*/
/**
 * @section GPIO_Includes Includes
 * @addtogroup  GPIO
 * @brief GPIO Includes
 */
#include "gpio_types.h"

/*---------------------------------------------- GPIO Clocks ----------------------------------------------*/
/**
 * @section GPIO_Clocks GPIO Clocks
 * @defgroup 10_01_GPIO_API_Clock
 * @addtogroup  10_GPIO_API
 * @brief Provides access to RCC Clocks for each GPIO
 * @{
 */

/**
 * @brief Enables GPIO Clock
 * 
 * @param[in] gpio Pointer to `GPIO_TypeDef`. 
 * 					- `GPIOA`
 * 					- `GPIOB`
 * 					- `GPIOC`
 * 					- `GPIOD`
 * 					- `GPIOE`
 * 					- `GPIOF`
 * 					- `GPIOG`
 * 
 */
__STATIC_FORCEINLINE void _GPIO_EnableClock(const GPIO_TypeDef* const gpio)
{
	RCC->APB2ENR.REG |= (0x01 << (RCC_APB2ENR_IOPAEN_Pos + GPIO_CLK_POS(gpio)));
}
__STATIC_FORCEINLINE void _GPIO_DisableClock(const GPIO_TypeDef* const gpio);

/** @} */ // 10_01_GPIO_API_Clock

/*---------------------------------------------- C++ Safeguard ----------------------------------------------*/
#ifdef _cplusplus
}
#endif /* _cplusplus */

#endif /* GPIO_LOW_LEVEL_H_ */
