// Library
#include "dma.h"

/**
 * @brief DMA Configuration
 * @param[in] instance DMA Configuration Structure
 */
void DMA_Config(dma_config_t* instance){
	// Register
	uint32_t reg = 0x00;
	// Enable the DMA Clock
	DMA_clk_enable(instance->DMA_Channel);
	// Disable the DMA Channel
	DMA_CH_disable(instance->DMA_Channel);
	// Initialise Register
	reg = instance->DMA_Channel->CCR.REG;
	// DMA Channel Configuration
	reg = (uint32_t)(((instance->channel.mem2mem & 0x01) << DMA_CCR_MEM2MEM_Pos) |
					((instance->channel.priority & 0x03) << DMA_CCR_PL_Pos) |
					((instance->channel.circular_mode & 0x01) << DMA_CCR_CIRC_Pos) |
					((instance->channel.direction & 0x01) << DMA_CCR_DIR_Pos));
	// DMA Data Configuration
	reg &= ~((uint32_t)((0x03 << DMA_CCR_MSIZE_Pos) |
						(0x03 << DMA_CCR_PSIZE_Pos) |
						(0x01 << DMA_CCR_MINC_Pos) |
						(0x01 << DMA_CCR_PINC_Pos)));
	// Data Outside Memory -> Interchange Source (Memory) & Destination (Peripheral)
	if(instance->channel.direction){
		reg |= (uint32_t)(((instance->data.srcDataSize) << DMA_CCR_MSIZE_Pos) |
								((instance->data.dstDataSize) << DMA_CCR_PSIZE_Pos) |
								((instance->data.srcInc) << DMA_CCR_MINC_Pos) |
								((instance->data.dstInc) << DMA_CCR_PINC_Pos));
	}
	else{
		reg |= (uint32_t)(((instance->data.dstDataSize) << DMA_CCR_MSIZE_Pos) |
						  ((instance->data.srcDataSize) << DMA_CCR_PSIZE_Pos) |
						  ((instance->data.dstInc) << DMA_CCR_MINC_Pos) |
						  ((instance->data.srcInc) << DMA_CCR_PINC_Pos));
	}
	// DMA Channel Interrupt Configuration
	reg &= ~((uint32_t)((0x01 << DMA_CCR_TEIE_Pos) |
						(0x01 << DMA_CCR_HTIE_Pos) | 
						(0x01 << DMA_CCR_TCIE_Pos)));
	reg |= (uint32_t)(((instance->interrupt.TEIE) << DMA_CCR_TEIE_Pos) |
					  ((instance->interrupt.HTIE) << DMA_CCR_HTIE_Pos) |
					  ((instance->interrupt.TCIE) << DMA_CCR_TCIE_Pos));
	// Enable NVIC IRQ
	if((instance->interrupt.TEIE) || (instance->interrupt.TCIE) || (instance->interrupt.HTIE)){
		NVIC_IRQ_Enable(DMA_CH_get_IRQn(instance->DMA_Channel));
	}
	// Update the CCR Register
	instance->DMA_Channel->CCR.REG = reg;
}

/**
 * @brief Configures the Transfer of the DMA Channel
 * @param[in] DMA_channelX DMA Channel
 * @param[in] src Pointer to Source
 * @param[in] dst Pointer to Destination
 * @param[in] size Size of the data to be transferred
 */
void DMA_Transfer(DMA_CHANNEL_REG_STRUCT* DMA_channelX, void* src, void* dst, uint16_t size){
	// Disable the DMA Channel
	DMA_CH_disable(DMA_channelX);
	// Out of Memory
	if(DMA_channelX->CCR.REG & DMA_CCR_DIR){
		// Source Address
		DMA_channelX->CMAR.REG = (uint32_t)src;
		// Destination Address
		DMA_channelX->CPAR.REG = (uint32_t)dst;
	}
	// In Memory
	else{
		// Source Address
		DMA_channelX->CPAR.REG = (uint32_t)src;
		// Destination Address
		DMA_channelX->CMAR.REG = (uint32_t)dst;
	}
	// Size of Data Transfer
	DMA_channelX->CNDTR.REG = size;
}

/**
 * @brief Loads the default configuration for Memory to Memory Transfer
 * @param[in] instance DMA Configuration Structure
 */
void DMA_Load_Default_MEM2MEM(dma_config_t* instance){
	// DMA Channel (Default)
	instance->DMA_Channel = DMA1_Channel1;
	// DMA Channel Data Configuration
	instance->data.dstDataSize = DMAx_DATA_SIZE_BIT_32;
	instance->data.srcDataSize = DMAx_DATA_SIZE_BIT_32;
	instance->data.dstInc = DMAx_INC_ENABLE;
	instance->data.srcInc = DMAx_INC_ENABLE;
	// DMA Interrupt Configuration
	instance->interrupt.HTIE = DMAx_IRQ_DISABLE;
	instance->interrupt.TCIE = DMAx_IRQ_ENABLE;
	instance->interrupt.TEIE = DMAx_IRQ_ENABLE;
	// DMA Channel Configuration
	instance->channel.direction = DMAx_DIR_MEM_IN;
	instance->channel.mem2mem = DMAx_MEM2MEM_ENABLE;
	instance->channel.circular_mode = DMAx_CIRC_DISABLE;
	instance->channel.priority = DMAx_PRIORITY_MEDIUM;	
}

/**
 * @brief Loads the default configuration for Peripheral to Memory Transfer
 * @param[in] instance DMA Configuration Structure
 */
void DMA_Load_Default_PER2MEM(dma_config_t* instance){
	// DMA Channel (Default)
	instance->DMA_Channel = DMA1_Channel1;
	// DMA Channel Data Configuration
	instance->data.dstDataSize = DMAx_DATA_SIZE_BIT_8;
	instance->data.srcDataSize = DMAx_DATA_SIZE_BIT_8;
	instance->data.dstInc = DMAx_INC_DISABLE;
	instance->data.srcInc = DMAx_INC_DISABLE;
	// DMA Interrupt Configuration
	instance->interrupt.HTIE = DMAx_IRQ_DISABLE;
	instance->interrupt.TCIE = DMAx_IRQ_ENABLE;
	instance->interrupt.TEIE = DMAx_IRQ_ENABLE;
	// DMA Channel Configuration
	instance->channel.direction = DMAx_DIR_MEM_OUT;
	instance->channel.mem2mem = DMAx_MEM2MEM_DISABLE;
	instance->channel.circular_mode = DMAx_CIRC_DISABLE;
	instance->channel.priority = DMAx_PRIORITY_HIGH;	
}

