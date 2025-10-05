// Header Guards
#ifndef DMA_REG_LEVEL
#define DMA_REG_LEVEL

/*********************************************** Includes ***********************************************/
#include "dma_types.h"

/*********************************************** MACROs ***********************************************/
/**
 * @brief Determines if the input channel belongs to DMA1
 */
#define IS_DMA1_CHANNEL(CHANNEL) \
	((((uint32_t) (CHANNEL)) >= (uint32_t) DMA1_Channel1) && \
	(((uint32_t) (CHANNEL)) <= (uint32_t) DMA1_Channel7))
/**
 * @brief Determines if the input channel belongs to DMA2
 */
#define IS_DMA2_CHANNEL(CHANNEL) \
	((((uint32_t) (CHANNEL)) >= (uint32_t) DMA2_Channel1) && \
	(((uint32_t) (CHANNEL)) <= (uint32_t) DMA2_Channel5))
/**
 * @brief Determines DMA1/DMA2 based on input channel
 */
#define GET_DMA_CONTROLLER(CHANNEL) \
	(IS_DMA1_CHANNEL((CHANNEL)) ? DMA1 : \
	IS_DMA2_CHANNEL((CHANNEL)) ? DMA2 : NULL)

/*********************************************** Helpers ***********************************************/
/**
 * @brief Enable DMA Clock
 * @param dmaX DMA Controller: `DMA1`/`DMA2`
 */
__STATIC_INLINE__ void __DMA_enableClock(DMA_TypeDef* dmaX)
{
	if(dmaX == DMA1)
	{
		RCC->AHBENR.REG |= RCC_AHBENR_DMA1EN;
	}
	else if (dmaX == DMA2)
	{
		RCC->AHBENR.REG |= RCC_AHBENR_DMA2EN;
	}
}

/**
 * @brief Disbale DMA Clock
 * @param dmaX DMA Controller: `DMA1`/`DMA2`
 */
__STATIC_INLINE__ void __DMA_disableClock(DMA_TypeDef* dmaX)
{
	if(dmaX == DMA1)
	{
		RCC->AHBENR.REG &= ~RCC_AHBENR_DMA1EN;
	}
	else if (dmaX == DMA2)
	{
		RCC->AHBENR.REG &= ~RCC_AHBENR_DMA2EN;
	}
}

/**
 * @brief Enable DMA Clock
 * @param dmaXChannelY DMA Channel: `DMAxChannelY`
 */
__STATIC_INLINE__ void __DMA_enableClockFromChannel(DMA_Channel_TypeDef* dmaXChannelY)
{
	__DMA_enableClock(GET_DMA_CONTROLLER(dmaXChannelY));
}

/**
 * @brief Disbale DMA Clock
 * @param dmaXChannelY DMA Channel: `DMAxChannelY`
 */
__STATIC_INLINE__ void __DMA_disableClockFromChannel(DMA_Channel_TypeDef* dmaXChannelY)
{
	__DMA_disableClock(GET_DMA_CONTROLLER(dmaXChannelY));
}

/**
 * @brief Enable DMA Channel
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 */
__STATIC_INLINE__ void __DMA_enableChannel(DMA_Channel_TypeDef* dmaXChannelY)
{
	dmaXChannelY->CCR.REG |= DMA_CCR_EN;
}

/**
 * @brief Disable DMA Channel
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 */
__STATIC_INLINE__ void __DMA_disableChannel(DMA_Channel_TypeDef* dmaXChannelY)
{
	dmaXChannelY->CCR.REG &= ~DMA_CCR_EN;
}

/**
 * @brief Read from CCR
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @return CCR value
 */
__STATIC_INLINE__ uint32_t __DMA_getCCR(DMA_Channel_TypeDef* dmaXChannelY)
{
	return dmaXChannelY->CCR.REG;
}

/**
 * @brief Write to CCR
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @param value Updated CCR Value
 * @return CCR value
 */
__STATIC_INLINE__ uint32_t __DMA_setCCR(DMA_Channel_TypeDef* dmaXChannelY, const uint32_t value)
{
	dmaXChannelY->CCR.REG = value;
}

/**
 * @brief Read Peripheral Address 
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @return CPAR Value
 */
__STATIC_INLINE__ uint32_t __DMA_getCPAR(DMA_Channel_TypeDef* dmaXChannelY)
{
	return dmaXChannelY->CPAR.REG;
}

/**
 * @brief Set Peripheral Address
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @param value Modified register value
 */
__STATIC_INLINE__ void __DMA_setCPAR(DMA_Channel_TypeDef* dmaXChannelY, const uint32_t value)
{
	dmaXChannelY->CPAR.REG = value;
}

/**
 * @brief Read Memory Address 
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @return CMAR Value
 */
__STATIC_INLINE__ uint32_t __DMA_getCMAR(DMA_Channel_TypeDef* dmaXChannelY)
{
	return dmaXChannelY->CMAR.REG;
}

/**
 * @brief Set Memory Address
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @param value Modified register value
 */
__STATIC_INLINE__ void __DMA_setCMAR(DMA_Channel_TypeDef* dmaXChannelY, const uint32_t value)
{
	dmaXChannelY->CMAR.REG = value;
}

/**
 * @brief Read number of data register for transfer 
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @return CNDTR Value
 */
__STATIC_INLINE__ uint32_t __DMA_getCNDTR(DMA_Channel_TypeDef* dmaXChannelY)
{
	return dmaXChannelY->CNDTR.REG;
}

/**
 * @brief Set number of data register for transfer
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @param value Modified register value
 */
__STATIC_INLINE__ void __DMA_setCNDTR(DMA_Channel_TypeDef* dmaXChannelY, const uint32_t value)
{
	dmaXChannelY->CNDTR.REG = value;
}

#endif /* DMA_REG_LEVEL */
