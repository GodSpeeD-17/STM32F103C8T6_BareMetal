/**
 * @file usart_config.c
 * @author Shrey Shah
 * @brief USART Lookup Table Configuration
 * @version 1.0
 * @date 21-09-2025
 */

/*********************************************** Includes ***********************************************/
#include "usart_config.h"

/*********************************************** USART GPIO Mapping ***********************************************/
static const usart_gpio_t __usartDriverGPIOMapping__[] = {
	// USART1 GPIO Mapping
	[USART_1] = {
		.TX = {
			.GPIO = USART1_TX_GPIO,
			.setup = {
				.pin = USART1_TX_PIN,
				.mode = USART_TX_PIN_MODE,
				.config = USART_TX_PIN_CONFIG
			}
		},
		.RX = {
			.GPIO = USART1_RX_GPIO,
			.setup = {
				.pin = USART1_RX_PIN,
				.mode = USART_RX_PIN_MODE,
				.config = USART_RX_PIN_CONFIG
			}
		},
		.RTS = {
			.GPIO = USART1_RTS_GPIO,
			.setup = {
				.pin = USART1_RTS_PIN,
				.mode = USART_RTS_PIN_MODE,
				.config = USART_RTS_PIN_CONFIG
			}
		},
		.CTS = {
			.GPIO = USART1_CTS_GPIO,
			.setup = {
				.pin = USART1_CTS_PIN,
				.mode = USART_CTS_PIN_MODE,
				.config = USART_CTS_PIN_CONFIG,
			}
		},
		.CK = {
			.GPIO = USART1_CK_GPIO,
			.setup = {
				.pin = USART1_CK_PIN,
				.mode = USART_CK_PIN_MODE,
				.config = USART_CK_PIN_CONFIG,
			}
		}
	},
	// USART2 GPIO Mapping
	[USART_2] = {
		.TX = {
			.GPIO = USART2_TX_GPIO,
			.setup = {
				.pin = USART2_TX_PIN,
				.mode = USART_TX_PIN_MODE,
				.config = USART_TX_PIN_CONFIG
			}
		},
		.RX = {
			.GPIO = USART2_RX_GPIO,
			.setup = {
				.pin = USART2_RX_PIN,
				.mode = USART_RX_PIN_MODE,
				.config = USART_RX_PIN_CONFIG
			}
		},
		.RTS = {
			.GPIO = USART2_RTS_GPIO,
			.setup = {
				.pin = USART2_RTS_PIN,
				.mode = USART_RTS_PIN_MODE,
				.config = USART_RTS_PIN_CONFIG
			}
		},
		.CTS = {
			.GPIO = USART2_CTS_GPIO,
			.setup = {
				.pin = USART2_CTS_PIN,
				.mode = USART_CTS_PIN_MODE,
				.config = USART_CTS_PIN_CONFIG,
			}
		},
		.CK = {
			.GPIO = USART2_CK_GPIO,
			.setup = {
				.pin = USART2_CK_PIN,
				.mode = USART_CK_PIN_MODE,
				.config = USART_CK_PIN_CONFIG,
			}
		}
	},
	// USART3 GPIO Mapping
	[USART_3] = {
		.TX = {
			.GPIO = USART3_TX_GPIO,
			.setup = {
				.pin = USART3_TX_PIN,
				.mode = USART_TX_PIN_MODE,
				.config = USART_TX_PIN_CONFIG
			}
		},
		.RX = {
			.GPIO = USART3_RX_GPIO,
			.setup = {
				.pin = USART3_RX_PIN,
				.mode = USART_RX_PIN_MODE,
				.config = USART_RX_PIN_CONFIG
			}
		},
		.RTS = {
			.GPIO = USART3_RTS_GPIO,
			.setup = {
				.pin = USART3_RTS_PIN,
				.mode = USART_RTS_PIN_MODE,
				.config = USART_RTS_PIN_CONFIG
			}
		},
		.CTS = {
			.GPIO = USART3_CTS_GPIO,
			.setup = {
				.pin = USART3_CTS_PIN,
				.mode = USART_CTS_PIN_MODE,
				.config = USART_CTS_PIN_CONFIG,
			}
		},
		.CK = {
			.GPIO = USART3_CK_GPIO,
			.setup = {
				.pin = USART3_CK_PIN,
				.mode = USART_CK_PIN_MODE,
				.config = USART_CK_PIN_CONFIG,
			}
		}
	},
};

/*********************************************** USART IRQn Mapping ***********************************************/
const irq_t __usartDriverIRQnMapping__[] = {
	[USART_1] = USART1_IRQn,
	[USART_2] = USART2_IRQn,
	[USART_3] = USART3_IRQn
};

/*********************************************** USART Register Mapping ***********************************************/
const USART_TypeDef* __usartDriverRegisterMapping__[] = {
	[USART_1] = USART1,
	[USART_2] = USART2,
	[USART_3] = USART3
};

/*********************************************** APIs ***********************************************/
/**
 * @brief Retrieves USART GPIO Configuration
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`  
 * @return usart_gpio_t* Pointer to USART GPIO Configuration Structure
 */
usart_gpio_t* USART_Get_GPIO_Config(const usart_t thisUSART){
	// USART GPIO Configuration
	return &__usartDriverGPIOMapping__[thisUSART];
}

/**
 * @brief Retrieves USART TX Pin GPIO Configuration
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`  
 * @return usart_pin_t* Pointer to USART TX GPIO Configuration Structure
 */
usart_pin_t* USART_TX_Get_GPIO_Config(const usart_t thisUSART){
	// USART TX GPIO Configuration
	return &__usartDriverGPIOMapping__[thisUSART].TX;
}

/**
 * @brief Retrieves USART RX Pin GPIO Configuration
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`  
 * @return usart_pin_t* Pointer to USART RX GPIO Configuration Structure
 */
usart_pin_t* USART_RX_Get_GPIO_Config(const usart_t thisUSART){
	// USART RX GPIO Configuration
	return &__usartDriverGPIOMapping__[thisUSART].RX;
}

/**
 * @brief Retrieves USART RTS Pin GPIO Configuration
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`  
 * @return usart_pin_t* Pointer to USART RTS GPIO Configuration Structure
 */
usart_pin_t* USART_RTS_Get_GPIO_Config(const usart_t thisUSART){
	// USART RTS GPIO Configuration
	return &__usartDriverGPIOMapping__[thisUSART].RTS;
}

/**
 * @brief Retrieves USART CTS Pin GPIO Configuration
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`  
 * @return usart_pin_t* Pointer to USART CTS GPIO Configuration Structure
 */
usart_pin_t* USART_CTS_Get_GPIO_Config(const usart_t thisUSART){
	// USART CTS GPIO Configuration
	return &__usartDriverGPIOMapping__[thisUSART].CTS;
}

/**
 * @brief Retrieves USART CK Pin GPIO Configuration
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`  
 * @return usart_pin_t* Pointer to USART CK GPIO Configuration Structure
 */
usart_pin_t* USART_CK_Get_GPIO_Config(const usart_t thisUSART){
	// USART CK GPIO Configuration
	return &__usartDriverGPIOMapping__[thisUSART].CK;
}
