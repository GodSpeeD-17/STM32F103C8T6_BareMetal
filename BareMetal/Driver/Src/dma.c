// Library
#include "dma.h"

/**
 * @brief Configures the DMA Channel
 * @param[in] DMA_channelX DMA Channel
 * @param[in] config DMA Channel Configuration Structure
 */
void DMA_CH_Config(DMA_CHANNEL_REG_STRUCT* DMA_channelX, dma_channel_config_t* config){
	// Enable the DMA Clock
	DMA_clk_enable(DMA_channelX);
	// Disable the DMA Channel
	DMA_CH_disable(DMA_channelX);
	// Update the Register
	reg = (uint32_t)(((config->mem2mem & 0x01) << DMA_CCR_MEM2MEM_Pos) |
							  ((config->priority & 0x03) << DMA_CCR_PL_Pos) |
							  ((config->circular_mode & 0x01) << DMA_CCR_CIRC_Pos) |
							  ((config->direction & 0x01) << DMA_CCR_DIR_Pos));
	// Update the Register
	DMA_channelX->CCR.REG = reg;
}

/**
 * @brief Configures the data related parameters of the DMA Channel
 * @param[in] DMA_channelX DMA Channel
 * @param[in] config DMA Channel Data Configuration Structure
 */
void DMA_CH_dataConfig(DMA_CHANNEL_REG_STRUCT* DMA_channelX, dma_channel_data_t* config){
	// Fetch the Register
	reg = DMA_channelX->CCR.REG;
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
	// Update the Register
	DMA_channelX->CCR.REG = reg;
}

/**
 * @brief Configures the Interrupt related parameters of the DMA Channel
 * @param[in] DMA_channelX DMA Channel
 * @param[in] config DMA Channel Data Configuration Structure
 */
void DMA_CH_IRQ_Config(DMA_CHANNEL_REG_STRUCT* DMA_channelX, dma_channel_intr_t* config){
	// Fetch the Register
	reg = DMA_channelX->CCR.REG;
	// Clear the Position
	reg &= ~((uint32_t)((0x01 << DMA_CCR_TEIE_Pos) |
						(0x01 << DMA_CCR_HTIE_Pos) | 
						(0x01 << DMA_CCR_TCIE_Pos)));
	// Update with current values
	reg |= (uint32_t)(((config->TEIE) << DMA_CCR_TEIE_Pos) |
					  ((config->HTIE) << DMA_CCR_HTIE_Pos) |
					  ((config->TCIE) << DMA_CCR_TCIE_Pos));
	// Update the Register
	DMA_channelX->CCR.REG = reg;

	// Enable NVIC IRQ
	if((config->TEIE) || (config->TCIE) || (config->HTIE)){
		NVIC_IRQ_Enable(DMA_CH_get_IRQn(DMA_channelX));
	}
}

/**
 * @brief Configures the Transfer of the DMA Channel
 * @param[in] DMA_channelX DMA Channel
 * @param[in] src Pointer to Source
 * @param[in] dst Pointer to Destination
 * @param[in] size Size of the data to be transferred
 */
void DMA_CH_Transfer_Config(DMA_CHANNEL_REG_STRUCT* DMA_channelX, void* src, void* dst, uint16_t size){
	// Disable the DMA Channel
	DMA_CH_disable(DMA_channelX);
	// Source Address
	DMA_channelX->CPAR.REG = (uint32_t)(src);
	// Destination Address
	DMA_channelX->CMAR.REG = (uint32_t)(dst);
	// Size of Data Transfer
	DMA_channelX->CNDTR.REG = size;
}

