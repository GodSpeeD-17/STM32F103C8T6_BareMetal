/**
 * @file dma_config.c
 * @author Shrey Shah
 * @brief DMA API Driver
 * @version 1.1
 * @date 05-10-2025
 * Logs: Added DMA Configuration Structure
 */

/*********************************************** Includes ***********************************************/
#include "dma_low_level.h"

/*********************************************** Lookup Table ***********************************************/
// --- Driver DMA Address Mapping --- //
const DMA_Channel_TypeDef* _driverDMAChannelMapping[] = 
{
	[DMA_1_Channel_1] = DMA1_Channel1,
	[DMA_1_Channel_2] = DMA1_Channel2,
	[DMA_1_Channel_3] = DMA1_Channel3,
	[DMA_1_Channel_4] = DMA1_Channel4,
	[DMA_1_Channel_5] = DMA1_Channel5,
	[DMA_1_Channel_6] = DMA1_Channel6,
	[DMA_1_Channel_7] = DMA1_Channel7,
	
	[DMA_2_Channel_1] = DMA2_Channel1, 
	[DMA_2_Channel_2] = DMA2_Channel2, 
	[DMA_2_Channel_3] = DMA2_Channel3, 
	[DMA_2_Channel_4] = DMA2_Channel4, 
	[DMA_2_Channel_5] = DMA2_Channel5
};

// --- Driver DMA IRQ Mapping --- //
const irq_t _driverDMAIRQMapping[] = 
{
	[DMA_1_Channel_1] = DMA1_Channel1_IRQn,
	[DMA_1_Channel_2] = DMA1_Channel2_IRQn,
	[DMA_1_Channel_3] = DMA1_Channel2_IRQn,
	[DMA_1_Channel_4] = DMA1_Channel4_IRQn,
	[DMA_1_Channel_5] = DMA1_Channel5_IRQn,
	[DMA_1_Channel_6] = DMA1_Channel6_IRQn,
	[DMA_1_Channel_7] = DMA1_Channel7_IRQn
	#ifndef STM32F103C8T6__
	,[DMA_2_Channel_1] = DMA2_Channel1_IRQn,
	[DMA_2_Channel_2] = DMA2_Channel2_IRQn,
	[DMA_2_Channel_3] = DMA2_Channel3_IRQn,
	[DMA_2_Channel_4] = DMA2_Channel4_5_IRQn,
	[DMA_2_Channel_5] = DMA2_Channel4_5_IRQn
	#endif /* STM32F103C8T6__ */
};

/*********************************************** Helper Low Level Driver APIs ***********************************************/
/**
 * @brief DMA Endpoint Configuration
 * @param dmaPeripheralConfig Peripheral Configuration Structure. Refer `dma_endpoint_t`
 * @param dmaMemoryConfig Memory Configuration Structure. Refer `dma_endpoint_t`
 * @param reg Pointer to Register where the updated configuration needs to be written
 */
void _DMA_configEndPoint(const dma_endpoint_t dmaPeripheralConfig, const dma_endpoint_t dmaMemoryConfig, uint32_t* reg)
{
	*reg &= ~(uint32_t) (
		DMA_CCR_MSIZE_Msk |
		DMA_CCR_PSIZE_Msk |
		DMA_CCR_MINC_Msk |
		DMA_CCR_PINC_Msk
	);
	*reg |= (uint32_t)(
		((dmaMemoryConfig.size & 0x03) << DMA_CCR_MSIZE_Pos) |
		((dmaPeripheralConfig.size & 0x03) << DMA_CCR_PSIZE_Pos) |
		((dmaMemoryConfig.increment & 0x01) << DMA_CCR_MINC_Pos) |
		((dmaPeripheralConfig.increment & 0x01) << DMA_CCR_PINC_Pos)
	);
}

/**
 * @brief DMA Channel Priority Configuration
 * @param priority Channel Priority. Refer `DMA_CHANNEL_PRIORITY_*` 
 * @param reg Pointer to Register where the updated configuration needs to be written
 */
void _DMA_configChannelPriority(const dma_channel_priority_t priority, uint32_t* reg)
{
	*reg &= ~(uint32_t)(DMA_CCR_PL_Msk);
	*reg |= (uint32_t)((priority & 0x03) << DMA_CCR_PL_Pos);
}

/**
 * @brief DMA Channel Direction Configuration
 * @param direction Channel Direction. Refer `DMA_CHANNEL_DIR_*` 
 * @param reg Pointer to Register where the updated configuration needs to be written
 */
void _DMA_configChannelDirection(const dma_transfer_dir_t direction, uint32_t* reg)
{
	*reg &= ~(uint32_t)(DMA_CCR_DIR_Msk);
	*reg |= (uint32_t)((direction & 0x01) << DMA_CCR_DIR_Pos);
}

/**
 * @brief DMA Channel Circular Mode Configuration
 * @param circular Circular Mode. Refer `DMA_CHANNEL_CIRCULAR_MODE_*` 
 * @param reg Pointer to Register where the updated configuration needs to be written
 */
void _DMA_configChannelCircularMode(const dma_circular_mode_t circular, uint32_t* reg)
{
	*reg &= ~(uint32_t)(DMA_CCR_CIRC_Msk);
	*reg |= (uint32_t)((circular & 0x01) << DMA_CCR_CIRC_Pos);
}

/**
 * @brief DMA Channel MEM2MEM Configuration
 * @param circular MEM2MEM . Refer `DMA_CHANNEL_MEM2MEM_MODE_*` 
 * @param reg Pointer to Register where the updated configuration needs to be written
 */
void _DMA_configChannelMEM2MEM(const dma_circular_mode_t mem2mem, uint32_t* reg)
{
	*reg &= ~(uint32_t)(DMA_CCR_MEM2MEM_Msk);
	*reg |= (uint32_t)((mem2mem & 0x01) << DMA_CCR_MEM2MEM_Pos);
}

/**
 * @brief DMA Channel Mode Configuration
 * @param mode Pointer to Channel Mode Configuration Structure. Refer `dma_channel_properties_t` 
 * @param reg Pointer to Register where the updated configuration needs to be written
 */
void _DMA_configChannelProperties(const dma_channel_properties_t* const mode, uint32_t* reg)
{
	// Priority
	_DMA_configChannelPriority(mode->priority, reg);
	// Direction
	_DMA_configChannelDirection(mode->direction, reg);
	// Circular Mode
	_DMA_configChannelCircularMode(mode->circular, reg);
	// MEM2MEM
	_DMA_configChannelMEM2MEM(mode->mem2mem, reg);
}

/**
 * @brief Configures the transfer for DMA
 * @param dmaChannel DMA Channel
 * @param dmaTransfer DMA Transfer configuration
 */
void _DMA_configTransfer(const dma_channel_t dmaChannel, const dma_transfer_t* const dmaTransfer)
{
	// Default Case - RX (Into Memory)
	DMA_Channel_TypeDef* dmaXChannelY = _DMA_getChannel(dmaChannel); 
	if(_DMA_getChannelDirection(dmaChannel) == DMA_CHANNEL_DIR_PERIPHERAL_TO_MEMORY)
	{
		__DMA_setChannelCPAR(dmaXChannelY, (uint32_t) dmaTransfer->src);
		__DMA_setChannelCMAR(dmaXChannelY, (uint32_t) dmaTransfer->dst);
	}
	// Different Case - TX (Into Peripheral)
	else
	{
		__DMA_setChannelCMAR(dmaXChannelY, (uint32_t) dmaTransfer->src);
		__DMA_setChannelCPAR(dmaXChannelY, (uint32_t) dmaTransfer->dst);
	}
	// Set the data size
	__DMA_setChannelCNDTR(dmaXChannelY, dmaTransfer->size);
}

/**
 * @brief Enables IRQ for DMA
 * @param dmaChannel DMA Channel
 * @param dmaIRQ Any logical combination of:
 * 				 - `DMA_IRQ_TRANSFER_COMPLETE`
 * 				 - `DMA_IRQ_HALF_TRANSFER_COMPLETE`
 * 				 - `DMA_IRQ_TRANSFER_ERROR`
 */
void _DMA_enableIRQ(const dma_channel_t dmaChannel, dma_irq_t dmaIRQ)
{
	// DMA Level
	uint32_t reg = __DMA_getChannelCCR(_DMA_getChannel(dmaChannel));
	reg |= (uint32_t) ((dmaIRQ & 0x07) << DMA_CCR_TCIE_Pos);
	__DMA_setChannelCCR(_DMA_getChannel(dmaChannel), reg);
	// Global Level
	NVIC_IRQEnable(_driverDMAIRQMapping[dmaChannel]);
}

/**
 * @brief Disables IRQ for DMA 
 * @param dmaChannel DMA Channel
 * @param dmaIRQ Any logical combination of:
 * 				 - `DMA_IRQ_TRANSFER_COMPLETE`
 * 				 - `DMA_IRQ_HALF_TRANSFER_COMPLETE`
 * 				 - `DMA_IRQ_TRANSFER_ERROR`
 */
void _DMA_disableIRQ(const dma_channel_t dmaChannel, dma_irq_t dmaIRQ)
{
	// DMA Level
	uint32_t reg = __DMA_getChannelCCR(_DMA_getChannel(dmaChannel));
	reg &= ~(uint32_t) ((dmaIRQ & 0x07) << DMA_CCR_TCIE_Pos);
	__DMA_setChannelCCR(_DMA_getChannel(dmaChannel), reg);
	// Global Level
	NVIC_IRQDisable(_driverDMAIRQMapping[dmaChannel]);
}

