/*********************************************** Header Guards ***********************************************/
#ifndef DMA_REG_LEVEL
#define DMA_REG_LEVEL

/*********************************************** Includes ***********************************************/
#include "stm32f1xx.h"
#include "dma_types.h"

/*********************************************** MACROs ***********************************************/
/**
 * @brief Determines if the input channel belongs to DMA1
 * @param CHANNEL DMA Channel. Refer `DMAX_ChannelY`
 */
#define _IS_DMA1_CHANNEL(CHANNEL) \
	((((uint32_t) (CHANNEL)) >= (uint32_t) DMA1_Channel1) && \
	(((uint32_t) (CHANNEL)) <= (uint32_t) DMA1_Channel7))
/**
 * @brief Determines if the input channel belongs to DMA2
 * @param CHANNEL DMA Channel. Refer `DMAX_ChannelY` 
 */
#define _IS_DMA2_CHANNEL(CHANNEL) \
	((((uint32_t) (CHANNEL)) >= (uint32_t) DMA2_Channel1) && \
	(((uint32_t) (CHANNEL)) <= (uint32_t) DMA2_Channel5))
/**
 * @brief Determines DMA1/DMA2 based on input channel
 * @param CHANNEL DMA Channel. Refer `DMAX_ChannelY`
 */
#define _DMA_GET_CONTROLLER(CHANNEL) \
	(_IS_DMA1_CHANNEL((CHANNEL)) ? DMA1 : \
	_IS_DMA2_CHANNEL((CHANNEL)) ? DMA2 : NULL)

/*********************************************** Helpers ***********************************************/
/**
 * @brief Enable DMA Clock
 * @param dmaX DMA Controller: `DMA1`/`DMA2`
 */
__STATIC_FORCEINLINE void __DMA_enableClock(DMA_TypeDef* dmaX)
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
__STATIC_FORCEINLINE void __DMA_disableClock(DMA_TypeDef* dmaX)
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
__STATIC_FORCEINLINE void __DMA_enableClockFromChannel(DMA_Channel_TypeDef* dmaXChannelY)
{
	__DMA_enableClock(_DMA_GET_CONTROLLER(dmaXChannelY));
}

/**
 * @brief Disbale DMA Clock
 * @param dmaXChannelY DMA Channel: `DMAxChannelY`
 */
__STATIC_FORCEINLINE void __DMA_disableClockFromChannel(DMA_Channel_TypeDef* dmaXChannelY)
{
	__DMA_disableClock(_DMA_GET_CONTROLLER(dmaXChannelY));
}

/**
 * @brief Enable DMA Channel
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 */
__STATIC_FORCEINLINE void __DMA_enableChannel(DMA_Channel_TypeDef* dmaXChannelY)
{
	dmaXChannelY->CCR.REG |= DMA_CCR_EN;
}

/**
 * @brief Disable DMA Channel
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 */
__STATIC_FORCEINLINE void __DMA_disableChannel(DMA_Channel_TypeDef* dmaXChannelY)
{
	dmaXChannelY->CCR.REG &= ~DMA_CCR_EN;
}

/**
 * @brief Read from DMA Interrupt Status Register (ISR)
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @return ISR value
 */
__STATIC_FORCEINLINE uint32_t __DMA_getISR(DMA_Channel_TypeDef* dmaXChannelY)
{
	return _DMA_GET_CONTROLLER(dmaXChannelY)->ISR.REG;
}

/**
 * @brief Set the DMA Interrupt Flag Clear Register (IFCR)
 * @param dmaX DMA Controller: `DMA1`/`DMA2`
 * @param channelY Channel Number Offset from Channel 1: 0 - 6
 * @param dmaIrqAck DMA IRQ Combination
 * 	@par \c `DMA_IRQ_NONE` 
 * 	@par \c `DMA_IRQ_TRANSFER_COMPLETE`
 * 	@par \c `DMA_IRQ_HALF_TRANSFER_COMPLETE`
 * 	@par \c `DMA_IRQ_TRANSFER_ERROR`
 */
__STATIC_FORCEINLINE void __DMA_setIFCR(DMA_TypeDef* dmaX, const dma_channel_number_t channelY, const dma_irq_t dmaIrqAck)
{
	dmaX->IFCR.REG |= (dmaIrqAck << (channelY << 2));
}

/**
 * @brief Read from Channel Configuration Register (CCR)
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @return CCR value
 */
__STATIC_FORCEINLINE uint32_t __DMA_getChannelCCR(DMA_Channel_TypeDef* dmaXChannelY)
{
	return dmaXChannelY->CCR.REG;
}

/**
 * @brief Write to Channel Configuration Register (CCR)
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @param value Updated CCR Value
 * @return CCR value
 */
__STATIC_FORCEINLINE void __DMA_setChannelCCR(DMA_Channel_TypeDef* dmaXChannelY, const uint32_t value)
{
	dmaXChannelY->CCR.REG = value;
}

/**
 * @brief Read Channel Peripheral Address Register (CPAR)
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @return CPAR Value
 */
__STATIC_FORCEINLINE uint32_t __DMA_getChannelCPAR(DMA_Channel_TypeDef* dmaXChannelY)
{
	return dmaXChannelY->CPAR.REG;
}

/**
 * @brief Set Channel Peripheral Address Register (CPAR)
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @param value Modified register value
 */
__STATIC_FORCEINLINE void __DMA_setChannelCPAR(DMA_Channel_TypeDef* dmaXChannelY, const uint32_t value)
{
	dmaXChannelY->CPAR.REG = value;
}

/**
 * @brief Read Channel Memory Address Register (CMAR) 
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @return CMAR Value
 */
__STATIC_FORCEINLINE uint32_t __DMA_getChannelCMAR(DMA_Channel_TypeDef* dmaXChannelY)
{
	return dmaXChannelY->CMAR.REG;
}

/**
 * @brief Set Channel Memory Address Register (CMAR)
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @param value Modified register value
 */
__STATIC_FORCEINLINE void __DMA_setChannelCMAR(DMA_Channel_TypeDef* dmaXChannelY, const uint32_t value)
{
	dmaXChannelY->CMAR.REG = value;
}

/**
 * @brief Read Channel Number of Data Register (CNDTR)
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @return CNDTR Value
 * @note Number of data left for transfer 
 */
__STATIC_FORCEINLINE uint32_t __DMA_getChannelCNDTR(DMA_Channel_TypeDef* dmaXChannelY)
{
	return dmaXChannelY->CNDTR.REG;
}

/**
 * @brief Set Channel Number of Data Register (CNDTR)
 * @param dmaXChannelY DMA Channel: `DMAX_ChannelY`
 * @param value Modified register value
 * @note Number of data to transfer 
 */
__STATIC_FORCEINLINE void __DMA_setChannelCNDTR(DMA_Channel_TypeDef* dmaXChannelY, const uint32_t value)
{
	dmaXChannelY->CNDTR.REG = value;
}

#endif /* DMA_REG_LEVEL */
