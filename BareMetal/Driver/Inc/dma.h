// Header Guards
#ifndef __DMA_H__
#define __DMA_H__

// Dependency
#include "reg_map.h"
#include "nvic.h"		// IRQ

// DMA Configuration Configuration Structure
typedef struct {
	// Direction of data transfer
	// - `DMAX_DIR_READ_FROM_PER`
	// - `DMAX_DIR_READ_FROM_MEM`
	uint8_t direction: 1;
	// Read from Memory & Store it to Memory
	// - `DMAx_MEM2MEM_DISABLE`
	// - `DMAx_MEM2MEM_ENABLE`
	uint8_t mem2mem: 1;
	// Enable Circular Buffer Mode
	// -`DMAx_CIRC_DISABLE`
	// -`DMAx_CIRC_ENABLE`
	uint8_t circular_mode: 1;
	// Priority level
	// - `DMAx_PRIORITY_LOW`
	// - `DMAx_PRIORITY_MEDIUM`
	// - `DMAx_PRIORITY_HIGH`
	// - `DMAx_PRIORITY_VERY_HIGH`
	uint8_t priority: 2;
} dma_channel_config_t;

// DMA Channel Data Configuration Structure
typedef struct {
	// Source Data Size (`PSIZE`)
	// - `DMAx_DATA_SIZE_BIT_8`
	// - `DMAx_DATA_SIZE_BIT_16`
	// - `DMAx_DATA_SIZE_BIT_32`
	uint8_t srcDataSize: 2;
	// Destination Data Size (`MSIZE`)
	// - `DMAx_DATA_SIZE_BIT_8`
	// - `DMAx_DATA_SIZE_BIT_16`
	// - `DMAx_DATA_SIZE_BIT_32`
	uint8_t dstDataSize: 2;
	// Source Increment Mode (`PINC`)
	// - `DMAx_SRCINC_DISABLE`
	// - `DMAx_SRCINC_ENABLE`
	uint8_t srcInc: 1;
	// Destination Increment Mode (`MINC`)
	// - `DMAx_DSTINC_DISABLE`
	// - `DMAx_DSTINC_ENABLE`
	uint8_t dstInc: 1;
} dma_channel_data_t;

// DMA Channel Interrupt Configuration Structure
typedef struct {
	// Transfer Complete Interrupt Enable
	uint8_t TCIE: 1;
	// Half Transfer Interrupt Enable
	uint8_t HTIE: 1;
	// Transfer Error Interrupt Enable
	uint8_t TEIE: 1;
} dma_channel_intr_t;

// I2C1 TX DMA Configuration Structure
static dma_channel_config_t I2C1_TX_DMA_Configuration = {
	.circular_mode = DMAx_CIRC_DISABLE,
	.direction = DMAx_DIR_READ_FROM_MEM,
	.priority = DMAx_PRIORITY_VERY_HIGH,
	.mem2mem = DMAx_MEM2MEM_DISABLE
};

// I2C1 TX DMA Data Configuration Structure
static dma_channel_data_t I2C1_TX_DMA_Data_Configuration = {
	.dstDataSize = DMAx_DATA_SIZE_BIT_8,
	.dstInc = DMAx_INC_DISABLE,
	.srcDataSize = DMAx_DATA_SIZE_BIT_8,
	.srcInc = DMAx_INC_ENABLE,
};

// I2C1 TX DMA Interrupt Configuration Structure
static dma_channel_intr_t I2C1_TX_DMA_IRQ_Configuration = {
	.TEIE = DMAx_IRQ_ENABLE,
	.TCIE = DMAx_IRQ_ENABLE,
	.HTIE = DMAx_IRQ_DISABLE
};

// Temporary Register
static volatile uint32_t reg = 0x00000000;

/**
 * @brief Enables the main DMA Clock
 * @param[in] DMA_channelX DMA Channel 
 */
__INLINE__ void DMA_clk_enable(DMA_CHANNEL_REG_STRUCT* DMA_channelX){
	// Use Register
	reg = RCC->AHBENR.REG;
	// Enable DMA1 Clock
	if((DMA_channelX == DMA1_Channel1) || (DMA_channelX == DMA1_Channel2) ||
		(DMA_channelX == DMA1_Channel3) || (DMA_channelX == DMA1_Channel4) ||
		(DMA_channelX == DMA1_Channel5) || (DMA_channelX == DMA1_Channel6) ||
		(DMA_channelX == DMA1_Channel7))
		reg |= RCC_AHBENR_DMA1EN;
	// Enable DMA2 Clock
	if((DMA_channelX == DMA2_Channel1) || (DMA_channelX == DMA2_Channel2) ||
		(DMA_channelX == DMA2_Channel3) || (DMA_channelX == DMA2_Channel4) ||
		(DMA_channelX == DMA2_Channel5))
		reg |= RCC_AHBENR_DMA2EN;
	// Write Back to Register
	RCC->AHBENR.REG = reg;
}

/**
 * @brief Disables the main DMA Clock
 * @param[in] DMA_channelX DMA Channel 
 */
__INLINE__ void DMA_clk_disable(DMA_CHANNEL_REG_STRUCT* DMA_channelX){
	// Use Register
	reg = RCC->AHBENR.REG;
	// Enable DMA1 Clock
	if((DMA_channelX == DMA1_Channel1) || (DMA_channelX == DMA1_Channel2) ||
		(DMA_channelX == DMA1_Channel3) || (DMA_channelX == DMA1_Channel4) ||
		(DMA_channelX == DMA1_Channel5) || (DMA_channelX == DMA1_Channel6) ||
		(DMA_channelX == DMA1_Channel7))
		reg &= ~RCC_AHBENR_DMA1EN;
	// Enable DMA2 Clock
	if((DMA_channelX == DMA2_Channel1) || (DMA_channelX == DMA2_Channel2) ||
		(DMA_channelX == DMA2_Channel3) || (DMA_channelX == DMA2_Channel4) ||
		(DMA_channelX == DMA2_Channel5))
		reg &= ~RCC_AHBENR_DMA2EN;
	// Write Back to Register
	RCC->AHBENR.REG = reg;
}

/**
 * @brief Disable the DMA Channel
 * @param[in] DMA_channelX DMA Channel
 */
__INLINE__ void DMA_CH_disable(DMA_CHANNEL_REG_STRUCT* DMA_channelX){
	// Disable the Channel
	DMA_channelX->CCR.REG &= ~DMA_CCR_EN;
}

/**
 * @brief Enable the DMA Channel
 * @param[in] DMA_channelX DMA Channel
 */
__INLINE__ void DMA_CH_enable(DMA_CHANNEL_REG_STRUCT* DMA_channelX){
	// Enable the Channel
	DMA_channelX->CCR.REG |= DMA_CCR_EN;
}

/**
 * @brief Get the DMA Channel IRQ Number
 * @param[in] DMA_channelX DMA Channel Number
 * @returns The DMA Channel IRQ Number
 */
__INLINE__ uint8_t DMA_CH_get_IRQn(DMA_CHANNEL_REG_STRUCT* DMA_channelX){
	// Return the IRQn
	if(DMA_channelX == DMA1_Channel1){
		return DMA1_Channel1_IRQn;
	}
	else if(DMA_channelX == DMA1_Channel2){
		return DMA1_Channel2_IRQn;
	}
	else if(DMA_channelX == DMA1_Channel3){
		return DMA1_Channel3_IRQn;
	}
	else if(DMA_channelX == DMA1_Channel4){
		return DMA1_Channel4_IRQn;
	}
	else if(DMA_channelX == DMA1_Channel5){
		return DMA1_Channel5_IRQn;
	}
	else if(DMA_channelX == DMA1_Channel6){
		return DMA1_Channel6_IRQn;
	}
	else if(DMA_channelX == DMA1_Channel7){
		return DMA1_Channel7_IRQn;
	}
	else if(DMA_channelX == DMA2_Channel1){
		return DMA2_Channel1_IRQn;
	}
	else if(DMA_channelX == DMA2_Channel2){
		return DMA2_Channel2_IRQn;
	}
	else if(DMA_channelX == DMA2_Channel3){
		return DMA2_Channel3_IRQn;
	}
	else if((DMA_channelX == DMA2_Channel4) || (DMA_channelX == DMA2_Channel5)){
		return DMA2_Channel4_5_IRQn;
	}
}

/**
 * @brief Configures the DMA
 * @param[in] config DMA Configuration Structure
 */
void DMA_CH_Config(DMA_CHANNEL_REG_STRUCT* DMA_channelX, dma_channel_config_t* config);

/**
 * @brief Configures the data related parameters of the DMA Channel
 * @param[in] DMA_channelX DMA Channel
 * @param[in] config DMA Channel Data Configuration Structure
 */
void DMA_CH_dataConfig(DMA_CHANNEL_REG_STRUCT* DMA_channelX, dma_channel_data_t* config);

/**
 * @brief Configures the Interrupt related parameters of the DMA Channel
 * @param[in] DMA_channelX DMA Channel
 * @param[in] config DMA Channel Data Configuration Structure
 */
void DMA_CH_IRQ_Config(DMA_CHANNEL_REG_STRUCT* DMA_channelX, dma_channel_intr_t* config);


/**
 * @brief Configures the Transfer of the DMA Channel
 * @param[in] DMA_channelX DMA Channel
 * @param[in] src Pointer to Source
 * @param[in] dst Pointer to Destination
 * @param[in] size Size of the data to be transferred
 */
void DMA_CH_Transfer_Config(DMA_CHANNEL_REG_STRUCT* DMA_channelX, void* src, void* dst, uint16_t size);

#endif /* __DMA_H__ */