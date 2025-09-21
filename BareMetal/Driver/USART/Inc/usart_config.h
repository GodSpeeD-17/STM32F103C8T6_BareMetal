/**
 * @file usart_config.h
 * @author Shrey Shah
 * @brief USART Configuration
 * @version 1.0
 * @date 21-09-2025
 */

/*********************************************** Header Guards ***********************************************/
#ifndef __USART_CONFIG_H__
#define __USART_CONFIG_H__

/*********************************************** Includes ***********************************************/
#include "reg_map.h"
#include "gpio.h"

/*********************************************** USART MACROs ***********************************************/
#define USART_MIN						USART_1
#define USART_MAX						USART_3

/*********************************************** USART1 MACROs ***********************************************/
#define USART1_CK_GPIO					GPIO_PORT_A
#define USART1_CK_PIN					GPIO_PIN_8
#define USART1_TX_GPIO					GPIO_PORT_A
#define USART1_TX_PIN					GPIO_PIN_9
#define USART1_RX_GPIO					GPIO_PORT_A
#define USART1_RX_PIN					GPIO_PIN_10
#define USART1_CTS_GPIO					GPIO_PORT_A
#define USART1_CTS_PIN					GPIO_PIN_11
#define USART1_RTS_GPIO					GPIO_PORT_A
#define USART1_RTS_PIN					GPIO_PIN_12

/*********************************************** USART2 MACROs ***********************************************/
#define USART2_CK_GPIO					GPIO_PORT_A
#define USART2_CK_PIN					GPIO_PIN_4
#define USART2_TX_GPIO					GPIO_PORT_A
#define USART2_TX_PIN					GPIO_PIN_2
#define USART2_RX_GPIO					GPIO_PORT_A
#define USART2_RX_PIN					GPIO_PIN_3
#define USART2_CTS_GPIO					GPIO_PORT_A
#define USART2_CTS_PIN					GPIO_PIN_0
#define USART2_RTS_GPIO					GPIO_PORT_A
#define USART2_RTS_PIN					GPIO_PIN_1

/*********************************************** USART3 MACROs ***********************************************/
#define USART3_CK_GPIO					GPIO_PORT_B
#define USART3_CK_PIN					GPIO_PIN_12
#define USART3_TX_GPIO					GPIO_PORT_B
#define USART3_TX_PIN					GPIO_PIN_10
#define USART3_RX_GPIO					GPIO_PORT_B
#define USART3_RX_PIN					GPIO_PIN_11
#define USART3_CTS_GPIO					GPIO_PORT_B
#define USART3_CTS_PIN					GPIO_PIN_13
#define USART3_RTS_GPIO					GPIO_PORT_B
#define USART3_RTS_PIN					GPIO_PIN_14

/*********************************************** USART Pin Generic Configuration ***********************************************/
#define USART_TX_PIN_MODE				GPIO_MODE_OUTPUT_10MHz
#define USART_TX_PIN_CONFIG				GPIO_PIN_CNF_OUT_AF_PP
#define USART_RX_PIN_MODE				GPIO_MODE_INPUT
#define USART_RX_PIN_CONFIG				GPIO_PIN_CNF_IN_PULL_UP
#define USART_RTS_PIN_MODE				GPIO_MODE_INPUT
#define USART_RTS_PIN_CONFIG			GPIO_PIN_CNF_IN_PULL_UP
#define USART_CTS_PIN_MODE				GPIO_MODE_OUTPUT_10MHz
#define USART_CTS_PIN_CONFIG			GPIO_PIN_CNF_OUT_AF_PP
#define USART_CK_PIN_MODE				GPIO_MODE_OUTPUT_10MHz
#define USART_CK_PIN_CONFIG				GPIO_PIN_CNF_OUT_AF_PP

/*********************************************** USART Data Configuration ***********************************************/
#define USART_DATA_BITS_SHIFT_Pos		(4)
#define USART_DATA_BITS_Mask			(0x01 << USART_DATA_BITS_SHIFT_Pos)
#define USART_EXTRACT_DATA_BITS(X)		(((X) & USART_DATA_BITS_Mask) >> USART_DATA_BITS_SHIFT_Pos)
#define USART_PARITY_SHIFT_Pos			(2)
#define USART_PARITY_Mask				(0x03 << USART_PARITY_SHIFT_Pos)
#define USART_EXTRACT_PARITY(X)			(((X) & USART_PARITY_Mask) >> USART_PARITY_SHIFT_Pos)
#define USART_STOP_BITS_SHIFT_Pos		(0)
#define USART_STOP_BITS_Mask			(0x03 << USART_STOP_BITS_SHIFT_Pos)
#define USART_EXTRACT_STOP_BITS(X)		(((X) & USART_STOP_BITS_Mask) >> USART_STOP_BITS_SHIFT_Pos)

/*********************************************** USART Instances ***********************************************/
typedef enum {
	USART_1 = (uint8_t) 0x01,
	USART_2,
	USART_3,
	USART_4,
	USART_5
} usart_t;

/*********************************************** USART Baud Rate ***********************************************/
typedef enum {
	USART_BAUD_9600 = 0x00,
	USART_BAUD_19200,
	USART_BAUD_38400,
	USART_BAUD_57600,
	USART_BAUD_115200,
	USART_BAUD_230400,
	USART_BAUD_460800,
	USART_BAUD_921600,
} usart_baud_t;

/*********************************************** USART Hardware Configuration ***********************************************/
typedef enum {
	// Disable All Hardware Pins
	USART_ALL_DISABLE      = (uint8_t)0x00,
	
	// Communication Pins
	USART_TX_ENABLE        = (uint8_t)0x01,
	USART_RX_ENABLE        = (uint8_t)0x02,
	USART_TX_RX_ENABLE     = (uint8_t)(USART_TX_ENABLE | USART_RX_ENABLE),
	
	// Hardware Flow Control Pins
	USART_RTS_ENABLE       = (uint8_t)0x04,
	USART_CTS_ENABLE       = (uint8_t)0x08,
	USART_RTS_CTS_ENABLE   = (uint8_t)(USART_RTS_ENABLE | USART_CTS_ENABLE),
	
	// Clock pin
	USART_CK_ENABLE        = (uint8_t)0x10,
	
	// Common combinations
	USART_FULL_DUPLEX      = (uint8_t)(USART_TX_RX_ENABLE),
	USART_HALF_DUPLEX_TX      = (uint8_t)(USART_TX_ENABLE),
	USART_HALF_DUPLEX_RX      = (uint8_t)(USART_RX_ENABLE),
	
	// USART Full Flow Control
	USART_FULL_FLOW_CONTROL = (uint8_t)(USART_TX_RX_ENABLE | USART_RTS_CTS_ENABLE),
	USART_FULL_FEATURED     = (uint8_t)(USART_TX_RX_ENABLE | USART_RTS_CTS_ENABLE | USART_CK_ENABLE),
	
	// All pins enabled
	USART_ALL_ENABLE       = (uint8_t)(USART_TX_ENABLE | USART_RX_ENABLE | USART_RTS_ENABLE | 
									   USART_CTS_ENABLE | USART_CK_ENABLE)
} usart_hardware_enable_t;

/*********************************************** USART Data Bits ***********************************************/
typedef enum {
	USART_8_BITS = (uint8_t) 0x00,
	USART_9_BITS = (uint8_t) 0x01,
} usart_data_bits_t;

/*********************************************** USART Parity Bits ***********************************************/
typedef enum {
	USART_PARITY_NONE = (uint8_t) 0x00,
	USART_PARITY_EVEN = (uint8_t) 0x02,
	USART_PARITY_ODD = (uint8_t) 0x03
} usart_parity_t;

/*********************************************** USART Stop Bits ***********************************************/
typedef enum {
	USART_STOP_BIT_1 = (uint8_t) 0x00,
	USART_STOP_BIT_0_5 = (uint8_t) 0x01,
	USART_STOP_BIT_2 = (uint8_t) 0x02,
	USART_STOP_BIT_1_5 = (uint8_t) 0x03,
} usart_stop_bits;

/*********************************************** USART Data Configuration ***********************************************/
typedef enum {
	USART_8N1 = (uint8_t) ((USART_8_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_NONE << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_1 << USART_STOP_BITS_SHIFT_Pos)),
	USART_8N0_5 = (uint8_t) ((USART_8_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_NONE << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_0_5 << USART_STOP_BITS_SHIFT_Pos)),
	USART_8N1_5 = (uint8_t) ((USART_8_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_NONE << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_1_5 << USART_STOP_BITS_SHIFT_Pos)),
	USART_8N2 = (uint8_t) ((USART_8_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_NONE << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_2 << USART_STOP_BITS_SHIFT_Pos)),
	USART_8E1 = (uint8_t) ((USART_8_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_EVEN << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_1 << USART_STOP_BITS_SHIFT_Pos)),
	USART_8E0_5 = (uint8_t) ((USART_8_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_EVEN << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_0_5 << USART_STOP_BITS_SHIFT_Pos)),
	USART_8E1_5 = (uint8_t) ((USART_8_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_EVEN << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_1_5 << USART_STOP_BITS_SHIFT_Pos)),
	USART_8E2 = (uint8_t) ((USART_8_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_EVEN << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_2 << USART_STOP_BITS_SHIFT_Pos)),
	USART_8O1 = (uint8_t) ((USART_8_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_ODD << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_1 << USART_STOP_BITS_SHIFT_Pos)),
	USART_8O0_5 = (uint8_t) ((USART_8_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_ODD << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_0_5 << USART_STOP_BITS_SHIFT_Pos)),
	USART_8O1_5 = (uint8_t) ((USART_8_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_ODD << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_1_5 << USART_STOP_BITS_SHIFT_Pos)),
	USART_8O2 = (uint8_t) ((USART_8_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_ODD << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_2 << USART_STOP_BITS_SHIFT_Pos)),
	USART_9N1 = (uint8_t) ((USART_9_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_NONE << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_1 << USART_STOP_BITS_SHIFT_Pos)),
	USART_9N0_5 = (uint8_t) ((USART_9_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_NONE << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_0_5 << USART_STOP_BITS_SHIFT_Pos)),
	USART_9N1_5 = (uint8_t) ((USART_9_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_NONE << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_1_5 << USART_STOP_BITS_SHIFT_Pos)),
	USART_9N2 = (uint8_t) ((USART_9_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_NONE << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_2 << USART_STOP_BITS_SHIFT_Pos)),
	USART_9E1 = (uint8_t) ((USART_9_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_EVEN << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_1 << USART_STOP_BITS_SHIFT_Pos)),
	USART_9E0_5 = (uint8_t) ((USART_9_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_EVEN << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_0_5 << USART_STOP_BITS_SHIFT_Pos)),
	USART_9E1_5 = (uint8_t) ((USART_9_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_EVEN << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_1_5 << USART_STOP_BITS_SHIFT_Pos)),
	USART_9E2 = (uint8_t) ((USART_9_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_EVEN << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_2 << USART_STOP_BITS_SHIFT_Pos)),
	USART_9O1 = (uint8_t) ((USART_9_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_ODD << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_1 << USART_STOP_BITS_SHIFT_Pos)),
	USART_9O0_5 = (uint8_t) ((USART_9_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_ODD << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_0_5 << USART_STOP_BITS_SHIFT_Pos)),
	USART_9O1_5 = (uint8_t) ((USART_9_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_ODD << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_1_5 << USART_STOP_BITS_SHIFT_Pos)),
	USART_9O2 = (uint8_t) ((USART_9_BITS << USART_DATA_BITS_SHIFT_Pos) | (USART_PARITY_ODD << USART_PARITY_SHIFT_Pos) | (USART_STOP_BIT_2 << USART_STOP_BITS_SHIFT_Pos)),
} usart_data_config_t;

/*********************************************** Custom USART Hardware Mapping Structure ***********************************************/
typedef struct {
	// GPIO Port
	gpio_port_t GPIO;
	// GPIO Pin Configuration
	gpio_config_t setup;
} usart_pin_t;

/*********************************************** USART GPIO Mapping Structure ***********************************************/
typedef struct {
	// USART TX Pin
	usart_pin_t TX;
	// USART RX Pin
	usart_pin_t RX;
	// USART RTS Pin
	usart_pin_t RTS;
	// USART CTS Pin
	usart_pin_t CTS;
	// USART Clock
	usart_pin_t CK;
} usart_gpio_t;

/*********************************************** USART Configuration Structure ***********************************************/
typedef struct {
	// USART Hardware Pins
	usart_hardware_enable_t hardware: 5;
	// Baud Rate
	usart_baud_t baud_rate: 4;
	// Parity Bit
	usart_parity_t parity: 2;
	// USART Configuration
	usart_data_config_t config: 5;
} usart_config_t;

/*********************************************** USART Clock APIs ***********************************************/
/**
 * @brief Enables the USART Clock
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`  
 */
__STATIC_INLINE__ void __USART_enableClock__(const usart_t thisUSART){
	// USART 1
	if(thisUSART == USART_1){
		RCC->APB2ENR.REG |= RCC_APB2ENR_USART1EN;
	}
	// USART2~5
	else {
		RCC->APB1ENR.REG |= (1 << ((thisUSART - USART_2) + RCC_APB1ENR_USART2EN_Pos));
	}
}

/**
 * @brief Disables the USART Clock
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`  
 */
__STATIC_INLINE__ void __USART_disableClock__(const usart_t thisUSART){
	// USART 1
	if(thisUSART == USART_1){
		RCC->APB2ENR.REG &= ~RCC_APB2ENR_USART1EN;
	}
	// USART2~5
	else {
		RCC->APB1ENR.REG &= ~(1 << ((thisUSART - USART_2) + RCC_APB1ENR_USART2EN_Pos));
	}
}

/*********************************************** USART Module APIs ***********************************************/
/**
 * @brief Enables the USART Module
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`  
 */
__STATIC_INLINE__ void USART_Enable(const usart_t thisUSART){
	// Enable the USART Module
	USART_Get_Mapping(thisUSART)->CR1.REG |= USART_CR1_UE;
}

/**
 * @brief Disables the USART Module
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`  
 */
__STATIC_INLINE__ void USART_Disable(const usart_t thisUSART){
	// Disable the USART Module
	USART_Get_Mapping(thisUSART)->CR1.REG &= ~USART_CR1_UE;
}

/*********************************************** USART Module APIs ***********************************************/
/**
 * @brief Enables the TX using DMA
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`
 */
__STATIC_INLINE__ void USART_DMA_TX_Enable(const usart_t thisUSART){
	// Enable the DMA TX
	USART_Get_Mapping(thisUSART)->CR3.REG |= USART_CR3_DMAT;
}

/**
 * @brief Disables the TX using DMA
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3` 
 */
__STATIC_INLINE__ void USART_DMA_TX_Disable(const usart_t thisUSART){
	// Disable the DMA TX
	USART_Get_Mapping(thisUSART)->CR3.REG &= ~USART_CR3_DMAT;
}

/**
 * @brief Enables the RX using DMA
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3` 
 */
__STATIC_INLINE__ void USART_DMA_RX_Enable(const usart_t thisUSART){
	// Enable the DMA RX
	USART_Get_Mapping(thisUSART)->CR3.REG |= USART_CR3_DMAR;
}

/**
 * @brief Disables the RX using DMA
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3` 
 */
__STATIC_INLINE__ void USART_DMA_RX_Disable(const usart_t thisUSART){
	// Disable the DMA RX
	USART_Get_Mapping(thisUSART)->CR3.REG &= ~USART_CR3_DMAR;
}

/*********************************************** USART Configuration Retrieving APIs ***********************************************/
/**
 * @brief Retrieves the USART Register Mapping Structure
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`
 * @return GPIO_TypeDef* Pointer to USART Register Mapping Structure
 */
USART_TypeDef* USART_Get_Mapping(const usart_t thisUSART);

/**
 * @brief Retrieves USART GPIO Configuration
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`  
 * @return usart_gpio_t* Pointer to USART GPIO Configuration Structure
 */
usart_gpio_t* USART_Get_GPIO_Config(const usart_t thisUSART);

/**
 * @brief Retrieves USART TX Pin GPIO Configuration
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`  
 * @return usart_pin_t* Pointer to USART TX GPIO Configuration Structure
 */
usart_pin_t* USART_TX_Get_GPIO_Config(const usart_t thisUSART);

/**
 * @brief Retrieves USART RX Pin GPIO Configuration
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`  
 * @return usart_pin_t* Pointer to USART RX GPIO Configuration Structure
 */
usart_pin_t* USART_RX_Get_GPIO_Config(const usart_t thisUSART);

/**
 * @brief Retrieves USART RTS Pin GPIO Configuration
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`  
 * @return usart_pin_t* Pointer to USART RTS GPIO Configuration Structure
 */
usart_pin_t* USART_RTS_Get_GPIO_Config(const usart_t thisUSART);

/**
 * @brief Retrieves USART CTS Pin GPIO Configuration
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`  
 * @return usart_pin_t* Pointer to USART CTS GPIO Configuration Structure
 */
usart_pin_t* USART_CTS_Get_GPIO_Config(const usart_t thisUSART);

/**
 * @brief Retrieves USART CK Pin GPIO Configuration
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`  
 * @return usart_pin_t* Pointer to USART CK GPIO Configuration Structure
 */
usart_pin_t* USART_CK_Get_GPIO_Config(const usart_t thisUSART);

/**
 * @brief Retrieves the USART IRQn Number
 * @param thisUSART USART Instance: `USART_1`, `USART_2`, `USART_3`
 * @return irq_t IRQ Number
 */
irq_t USART_Get_IRQn(const usart_t thisUSART);

#endif /* __USART_CONFIG_H__ */