/**
 * @file dma_low_level.h
 * @author Shrey Shah
 * @brief DMA Low Level Driver
 * @version v1.0
 * @date 05-10-2025
 */

#ifndef DMA_LOW_LEVEL_H_
#define DMA_LOW_LEVEL_H_

/*********************************************** Includes ***********************************************/
#include "dma_reg_level.h"

/*********************************************** Macros ***********************************************/
/**
 * @brief Determines DMA Channel Number
 * @param CHANNEL DMA Channel. Refer `DMAX_ChannelY`
 */
#define _DMA_GET_CHANNEL_NUMBER(CHANNEL)																\
(																										\
	(_IS_DMA1_CHANNEL(CHANNEL)) ? ((CHANNEL - DMA1_Channel1)/sizeof(DMA_Channel_TypeDef)) : 			\
	((_IS_DMA2_CHANNEL(CHANNEL)) ? ((CHANNEL - DMA2_Channel1)/sizeof(DMA_Channel_TypeDef)): 0) 		\
)
/*********************************************** Driver Helper APIs ***********************************************/
/**
 * @brief DMA Mapping Helper API
 * @param channel DMA Channel `DMA_x_Channel_Y`
 * @return DMA Controller: `DMA*` 
 */
__STATIC_FORCEINLINE DMA_TypeDef* _DMA_getController(const dma_channel_t channel)
{
	if((channel >= DMA_1_Channel_1) && (channel <= DMA_1_Channel_7))
	{
		return DMA1;
	}
	else if((channel >= DMA_2_Channel_1) && (channel <= DMA_2_Channel_5))
	{
		return DMA2;
	}
}

/**
 * @brief DMA Channel Mapping Helper API
 * @param channel DMA Channel `DMA_x_Channel_Y`
 * @return DMA Channel: `DMA*_Channel*` 
 */
__STATIC_FORCEINLINE DMA_Channel_TypeDef* _DMA_getChannel(const dma_channel_t channel)
{
	extern const DMA_Channel_TypeDef* _driverDMAChannelMapping[]; 
	return _driverDMAChannelMapping[channel];
}

/**
 * @brief DMA Channel IRQ Mapping Helper API
 * @param channel DMA Channel `DMA_x_Channel_Y`
 * @return IRQ Number. Refer `irq_t` 
 */
__STATIC_FORCEINLINE irq_t _DMA_getIRQ(const dma_channel_t channel)
{
	extern const irq_t _driverDMAIRQMapping[];
	return _driverDMAIRQMapping[channel];
}

/**
 * @brief DMA Clock Enable Helper API
 * @param channel DMA Channel `DMA_x_Channel_Y`
 */
__STATIC_FORCEINLINE void _DMA_enableClock(const dma_channel_t channel)
{
	__DMA_enableClock(_DMA_getController(channel));
}

/**
 * @brief DMA Clock Disable Helper API
 * @param channel DMA Channel `DMA_x_Channel_Y`
 */
__STATIC_FORCEINLINE void _DMA_disableClock(const dma_channel_t channel)
{
	__DMA_disableClock(_DMA_getController(channel));
}

/**
 * @brief Enable DMA Channel 
 * @param channel DMA Channel: `DMA_x_Channel_Y`
 */
__STATIC_FORCEINLINE void _DMA_enableChannel(const dma_channel_t channel)
{
	__DMA_enableChannel(_DMA_getChannel(channel));
}

/**
 * @brief Disable DMA Channel 
 * @param channel DMA Channel: `DMA_x_Channel_Y`
 */
__STATIC_FORCEINLINE void _DMA_disableChannel(const dma_channel_t channel)
{
	__DMA_disableChannel(_DMA_getChannel(channel));
}

/**
 * @brief DMA Channel Start Sequence 
 * @param channel DMA Channel: `DMA_x_Channel_Y`
 */
__STATIC_FORCEINLINE void _DMA_startChannel(const dma_channel_t channel)
{
	DMA_Channel_TypeDef* dmaXChannelY = _DMA_getChannel(channel);
	__DMA_enableClockFromChannel(dmaXChannelY);
	__DMA_disableChannel(dmaXChannelY);
}

/**
 * @brief Stop DMA Channel 
 * @param channel DMA Channel: `DMA_x_Channel_Y`
 */
__STATIC_FORCEINLINE void _DMA_stopChannel(const dma_channel_t channel)
{
	DMA_Channel_TypeDef* dmaXChannelY = _DMA_getChannel(channel);
	__DMA_disableChannel(dmaXChannelY);
	__DMA_disableClockFromChannel(dmaXChannelY);
}

/**
 * @brief Fetches DMA Channel Configurations
 * @param channel DMA Channel: `DMA_x_Channel_Y`
 * @return CCR Register Value
 */
__STATIC_FORCEINLINE uint32_t _DMA_getChannelConfiguration(const dma_channel_t channel)
{
	return __DMA_getChannelCCR(_DMA_getChannel(channel));
}

/**
 * @brief Fetches DMA Channel Priority
 * @param channel DMA Channel: `DMA_x_Channel_Y`
 * @returns DMA Channel Priority
 * @returns - `DMA_CHANNEL_PRIORITY_LOW`
 * @returns - `DMA_CHANNEL_PRIORITY_MEDIUM`
 * @returns - `DMA_CHANNEL_PRIORITY_HIGH`
 * @returns - `DMA_CHANNEL_PRIORITY_VERY_HIGH`
 */
__STATIC_FORCEINLINE dma_channel_nvic_priority_t _DMA_getChannelPriority(const dma_channel_t channel)
{
	return (dma_channel_nvic_priority_t) ((__DMA_getChannelCCR(_DMA_getChannel(channel)) & DMA_CCR_PL_Msk) >> DMA_CCR_PL_Pos);
}

/**
 * @brief Fetches DMA Channel Direction
 * @param channel DMA Channel: `DMA_x_Channel_Y`
 * @returns DMA Channel Transfer Direction
 * @returns - `DMA_CHANNEL_DIR_PERIPHERAL_TO_MEMORY`
 * @returns - `DMA_CHANNEL_DIR_MEMORY_TO_PERIPHERAL`
 */
__STATIC_FORCEINLINE dma_transfer_dir_t _DMA_getChannelDirection(const dma_channel_t channel)
{
	return (dma_transfer_dir_t) ((__DMA_getChannelCCR(_DMA_getChannel(channel)) & DMA_CCR_DIR_Msk) >> DMA_CCR_DIR_Pos);
}

/**
 * @brief Fetches DMA Channel Circular Mode
 * @param channel DMA Channel: `DMA_x_Channel_Y`
 * @returns DMA Circular Mode 
 * @returns - `DMA_CHANNEL_CIRCULAR_MODE_DISABLE` 
 * @returns - `DMA_CHANNEL_CIRCULAR_MODE_ENABLE` 
 */ 
__STATIC_FORCEINLINE dma_circular_mode_t _DMA_getChannelCircularMode(const dma_channel_t channel)
{
	return (dma_circular_mode_t) ((__DMA_getChannelCCR(_DMA_getChannel(channel)) & DMA_CCR_CIRC_Msk) >> DMA_CCR_CIRC_Pos);
}

/**
 * @brief Fetches DMA Channel MEM2MEM Mode
 * @param channel DMA Channel: `DMA_x_Channel_Y`
 * @returns DMA MEM2MEM Mode
 * @returns - `DMA_CHANNEL_MEM2MEM_MODE_DISABLE`
 * @returns - `DMA_CHANNEL_MEM2MEM_MODE_ENABLE`
 */ 
__STATIC_FORCEINLINE dma_mem2mem_mode_t _DMA_getChannelMEM2MEM(const dma_channel_t channel)
{
	return (dma_mem2mem_mode_t) ((__DMA_getChannelCCR(_DMA_getChannel(channel)) & DMA_CCR_MEM2MEM_Msk) >> DMA_CCR_MEM2MEM_Pos);
}

/**
 * @brief Fetches DMA Channel Configurations
 * @param channel DMA Channel: `DMA_x_Channel_Y`
 */
__STATIC_FORCEINLINE void _DMA_setChannelConfiguration(const dma_channel_t channel, const uint32_t value)
{
	__DMA_setChannelCCR(_DMA_getChannel(channel), value);
}

/**
 * @brief Retrieves the IRQ Status for DMA Channel
 * @param dmaChannel DMA Channel
 * @param dmaIRQ DMA IRQ Combination
 * 	@par \c `DMA_IRQ_NONE` 
 * 	@par \c `DMA_IRQ_TRANSFER_COMPLETE`
 * 	@par \c `DMA_IRQ_HALF_TRANSFER_COMPLETE`
 * 	@par \c `DMA_IRQ_TRANSFER_ERROR`
 * @return Status of the IRQs in the logical combination of:
 * @return - `DMA_IRQ_STATUS_NONE`
 * @return - `DMA_IRQ_STATUS_TRANSFER_COMPLETE`
 * @return - `DMA_IRQ_STATUS_HALF_TRANSFER_COMPLETE`
 * @return - `DMA_IRQ_STATUS_TRANSFER_ERROR`
 */
__STATIC_FORCEINLINE dma_irq_status_t _DMA_getIRQStatus(const dma_channel_t dmaChannel, dma_irq_t dmaIRQ)
{
	uint32_t reg = __DMA_getISR(_DMA_getChannel(dmaChannel));
	reg >>= ((dmaChannel - ((dmaChannel < DMA_2_Channel_1) ? DMA_1_Channel_1 : DMA_2_Channel_1)) << 2);
	return ((uint8_t) (reg & dmaIRQ));
}

/**
 * @brief Acknowledges the IRQ for DMA Channel
 * @param dmaChannel DMA Channel
 * @param dmaIRQ DMA IRQ Combination
 * 	@par \c `DMA_IRQ_NONE` 
 * 	@par \c `DMA_IRQ_TRANSFER_COMPLETE`
 * 	@par \c `DMA_IRQ_HALF_TRANSFER_COMPLETE`
 * 	@par \c `DMA_IRQ_TRANSFER_ERROR`
 */
__STATIC_FORCEINLINE void _DMA_ackIRQStatus(const dma_channel_t dmaChannel, const dma_irq_t dmaIRQ)
{
	DMA_Channel_TypeDef* dmaXChannelY = _DMA_getChannel(dmaChannel);
	__DMA_setIFCR(_DMA_GET_CONTROLLER(dmaXChannelY), (dma_channel_number_t) _DMA_GET_CHANNEL_NUMBER(dmaXChannelY), dmaIRQ);
}

/*********************************************** Driver APIs ***********************************************/
/**
 * @brief DMA Endpoint Configuration
 * @param dmaPeripheralConfig Peripheral Configuration Structure. Refer `dma_endpoint_t`
 * @param dmaMemoryConfig Memory Configuration Structure. Refer `dma_endpoint_t`
 * @param reg Pointer to Register where the updated configuration needs to be written
 */
void _DMA_configEndPoint(const dma_endpoint_t dmaPeripheralConfig, const dma_endpoint_t dmaMemoryConfig, uint32_t* reg);

/**
 * @brief DMA Channel Priority Configuration
 * @param priority Channel Priority. Refer `DMA_CHANNEL_PRIORITY_*` 
 * @param reg Pointer to Register where the updated configuration needs to be written
 */
void _DMA_configChannelPriority(const dma_channel_nvic_priority_t priority, uint32_t* reg);

/**
 * @brief DMA Channel Direction Configuration
 * @param direction Channel Direction. Refer `DMA_CHANNEL_DIR_*` 
 * @param reg Pointer to Register where the updated configuration needs to be written
 */
void _DMA_configChannelDirection(const dma_transfer_dir_t direction, uint32_t* reg);

/**
 * @brief DMA Channel Circular Mode Configuration
 * @param circular Circular Mode. Refer `DMA_CHANNEL_CIRCULAR_MODE_*` 
 * @param reg Pointer to Register where the updated configuration needs to be written
 */
void _DMA_configChannelCircularMode(const dma_circular_mode_t circular, uint32_t* reg);

/**
 * @brief DMA Channel MEM2MEM Configuration
 * @param circular MEM2MEM . Refer `DMA_CHANNEL_MEM2MEM_MODE_*` 
 * @param reg Pointer to Register where the updated configuration needs to be written
 */
void _DMA_configChannelMEM2MEM(const dma_circular_mode_t mem2mem, uint32_t* reg);

/**
 * @brief DMA Channel Mode Configuration
 * @param mode Pointer to Channel Mode Configuration Structure. Refer `dma_channel_properties_t` 
 * @param reg Pointer to Register where the updated configuration needs to be written
 */
void _DMA_configChannelProperties(const dma_channel_properties_t* const mode, uint32_t* reg);

/**
 * @brief Configures the transfer for DMA
 * @param dmaChannel DMA Channel 
 * @param dmaTransfer DMA Transfer configuration
 */
void _DMA_configTransfer(const dma_channel_t dmaChannel, const dma_transfer_t* const dmaTransfer);

/**
 * @brief Enables IRQ for DMA 
 * @param dmaChannel DMA Channel
 * @param dmaIRQ Any logical combination of:
 * 				 - `DMA_IRQ_TRANSFER_COMPLETE`
 * 				 - `DMA_IRQ_HALF_TRANSFER_COMPLETE`
 * 				 - `DMA_IRQ_TRANSFER_ERROR`
 */
void _DMA_enableIRQ(const dma_channel_t dmaChannel, dma_irq_t dmaIRQ);

/**
 * @brief Disables IRQ for DMA 
 * @param dmaChannel DMA Channel
 * @param dmaIRQ Any logical combination of:
 * 				 - `DMA_IRQ_TRANSFER_COMPLETE`
 * 				 - `DMA_IRQ_HALF_TRANSFER_COMPLETE`
 * 				 - `DMA_IRQ_TRANSFER_ERROR`
 */
void _DMA_disableIRQ(const dma_channel_t dmaChannel, dma_irq_t dmaIRQ);

#endif /* DMA_LOW_LEVEL_H_ */
