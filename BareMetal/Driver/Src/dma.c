// Library
#include "dma.h"

/**
 * @brief Configures the DMA Channel
 * @param[in] DMA_channelX DMA Channel
 * @param[in] config DMA Channel Configuration Structure
 */
static void DMA_CH_Config(DMA_CHANNEL_REG_STRUCT* DMA_channelX, dma_channel_config_t* config){
	// Update the Register
	reg = (uint32_t)(((config->mem2mem & 0x01) << DMA_CCR_MEM2MEM_Pos) |
					((config->priority & 0x03) << DMA_CCR_PL_Pos) |
					((config->circular_mode & 0x01) << DMA_CCR_CIRC_Pos) |
					((config->direction & 0x01) << DMA_CCR_DIR_Pos));
}

/**
 * @brief Configures the data related parameters of the DMA Channel
 * @param[in] DMA_channelX DMA Channel
 * @param[in] config DMA Channel Data Configuration Structure
 */
static void DMA_CH_Data_Config(DMA_CHANNEL_REG_STRUCT* DMA_channelX, dma_channel_data_t* config){
	// Clear the Position
	reg &= ~((uint32_t)((0x03 << DMA_CCR_MSIZE_Pos) |
						(0x03 << DMA_CCR_PSIZE_Pos) |
						(0x01 << DMA_CCR_MINC_Pos) |
						(0x01 << DMA_CCR_PINC_Pos)));
	// Update with current values
	reg |= (uint32_t)(((config->dstDataSize) << DMA_CCR_MSIZE_Pos) |
					  ((config->srcDataSize) << DMA_CCR_PSIZE_Pos) |
					  ((config->dstInc) << DMA_CCR_MINC_Pos) |
					  ((config->srcInc) << DMA_CCR_PINC_Pos));
}

/**
 * @brief Configures the Interrupt related parameters of the DMA Channel
 * @param[in] DMA_channelX DMA Channel
 * @param[in] config DMA Channel Data Configuration Structure
 */
static void DMA_CH_IRQ_Config(DMA_CHANNEL_REG_STRUCT* DMA_channelX, dma_channel_intr_t* config){
	// Clear the Position
	reg &= ~((uint32_t)((0x01 << DMA_CCR_TEIE_Pos) |
						(0x01 << DMA_CCR_HTIE_Pos) | 
						(0x01 << DMA_CCR_TCIE_Pos)));
	// Update with current values
	reg |= (uint32_t)(((config->TEIE) << DMA_CCR_TEIE_Pos) |
					  ((config->HTIE) << DMA_CCR_HTIE_Pos) |
					  ((config->TCIE) << DMA_CCR_TCIE_Pos));
	// Enable NVIC IRQ
	if((config->TEIE) || (config->TCIE) || (config->HTIE)){
		NVIC_IRQ_Enable(DMA_CH_get_IRQn(DMA_channelX));
	}
}

/**
 * @brief DMA Configuration
 * @param[in] instance DMA Configuration Structure
 */
void DMA_Config(dma_config_t* instance){
	// Enable the DMA Clock
	DMA_clk_enable(instance->DMA_Channel);
	// Disable the DMA Channel
	DMA_CH_disable(instance->DMA_Channel);
	// Initialise Register
	reg = instance->DMA_Channel->CCR.REG;
	// DMA Channel Configuration
	DMA_CH_Config(instance->DMA_Channel, &(instance->channel));
	// DMA Data Configuration
	DMA_CH_Data_Config(instance->DMA_Channel, &(instance->data));
	// DMA Channel Interrupt Configuration
	DMA_CH_IRQ_Config(instance->DMA_Channel, &(instance->interrupt));
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

