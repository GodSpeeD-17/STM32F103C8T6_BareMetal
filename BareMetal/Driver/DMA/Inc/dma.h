/**
 * @file dma.h
 * @author Shrey Shah
 * @brief DMA API Driver
 * @version 1.1
 * @date 05-10-2025
 */

 // Header Guards
#ifndef DMA_H_
#define DMA_H_

// --- Includes ---
#include "dma_low_level.h"

/**
 * @brief DMA Channel Endpoint Configuration
 * @param endpointConfig Pointer to Endpoint Configuration Structure `dma_endpoint_t`
 * @param size Data Size to be transfered.  
 * 	@par \c `DMA_ENDPOINT_DATA_SIZE_8_BIT` 8-bit data transfer
 * 	@par \c `DMA_ENDPOINT_DATA_SIZE_16_BIT` 16-bit data transfer
 * 	@par \c `DMA_ENDPOINT_DATA_SIZE_32_BIT` 32-bit data transfer
 * @param increment Address Increment
 * 	@par \c `DMA_ENDPOINT_MEMORY_INCREMENT_DISABLE` Address Remains Constant
 * 	@par \c `DMA_ENDPOINT_MEMORY_INCREMENT_ENABLE` Address Increment after each transfer
 */
__STATIC_FORCEINLINE void DMA_ConfigureChannelEndPoint
(
    dma_endpoint_t* const endpointConfig,
    const dma_endpoint_data_size_t size, 
    const dma_endpoint_memory_increment_t increment
)
{
    endpointConfig->size = size;
    endpointConfig->increment = increment;
}

/**
 * @brief DMA Channel Properties Configuration
 * @param channelPropertiesConfig Pointer to Channel Properties Configuration Structure. Refer `dma_channel_properties_t`
 * @param priority DMA Channel Priority
 * 	@sa DMA_CHANNEL_PRIORITY_LOW 
 * 	@sa DMA_CHANNEL_PRIORITY_MEDIUM
 * 	@sa DMA_CHANNEL_PRIORITY_HIGH
 * 	@sa DMA_CHANNEL_PRIORITY_VERY_HIGH
 * @param direction DMA Channel Transfer Direction
 * 	@par \c `DMA_CHANNEL_DIR_PERIPHERAL_TO_MEMORY` From Peripheral to Memory (RX - Default)
 * 	@par \c `DMA_CHANNEL_DIR_MEMORY_TO_PERIPHERAL` From Memory to Peripheral (TX)
 * @param circular DMA Channel Circular Mode Transfer
 * 	@par \c `DMA_CHANNEL_CIRCULAR_MODE_DISABLE` Circular Mode (Constant RX/TX) Disabled
 * 	@par \c `DMA_CHANNEL_CIRCULAR_MODE_ENABLE` Circular Mode (Constant RX/TX) Enabled
 * @param mem2mem DMA Channel Memory to Memory Transfer
 * 	@par \c `DMA_CHANNEL_MEM2MEM_MODE_DISABLE` Memory to Memory Transfer Disabled
 * 	@par \c `DMA_CHANNEL_MEM2MEM_MODE_ENABLE` Memory to Memory Transfer Enabled
 */
__STATIC_FORCEINLINE void DMA_ConfigureChannelProperties
(
	dma_channel_properties_t* const channelPropertiesConfig,
	const dma_channel_nvic_priority_t priority,
	const dma_transfer_dir_t direction,
	const dma_circular_mode_t circular,
	const dma_mem2mem_mode_t mem2mem
)
{
	channelPropertiesConfig->priority = priority;
	channelPropertiesConfig->direction = direction;
	channelPropertiesConfig->circular = circular;
	channelPropertiesConfig->mem2mem = mem2mem;
}

/**
 * @brief Configures for MEM2MEM Mode for transferring 8-bit data
 * @param dmaConfig Pointer to DMA Channel Configuration Structure
 * @note Assumes the following:
 * @note - Priority: Medium
 * @note - Direction: Peripheral to Memory
 * @note - Circular: Disabled
 * @note - Data Size: 8 bits
 * @note - Memory: Increment
 */
__STATIC_FORCEINLINE void DMA_LoadDefaultConfigForMEM2MEM(dma_channel_config_t* const dmaConfig)
{
	// DMA Channel Properties
	DMA_ConfigureChannelProperties
	(
		&dmaConfig->properties,
		DMA_CHANNEL_PRIORITY_MEDIUM,
		DMA_CHANNEL_DIR_PERIPHERAL_TO_MEMORY,
		DMA_CHANNEL_CIRCULAR_MODE_DISABLE,
		DMA_CHANNEL_MEM2MEM_MODE_ENABLE
	);
	// Peripheral Configuration
	DMA_ConfigureChannelEndPoint
	(
		&dmaConfig->peripheral,
		DMA_ENDPOINT_DATA_SIZE_8_BIT,
		DMA_ENDPOINT_MEMORY_INCREMENT_ENABLE
	);
	// Memory Configuration
	DMA_ConfigureChannelEndPoint
	(
		&dmaConfig->memory,
		DMA_ENDPOINT_DATA_SIZE_8_BIT,
		DMA_ENDPOINT_MEMORY_INCREMENT_ENABLE
	);
}

/**
 * @brief Configures DMA Channel for 8-bit Peripheral-to-Memory transfers (RX)
 * @param dmaConfig Pointer to DMA Channel configuration structure
 * @note Default configuration:
 * @note - Priority: Medium
 * @note - Direction: Peripheral to Memory  
 * @note - Circular: Disabled
 * @note - Data Size: 8 bits (both ends)
 * @note - Peripheral: Fixed address
 * @note - Memory: Increment address
 */
__STATIC_FORCEINLINE void DMA_LoadDefaultConfigForPER2MEM(dma_channel_config_t* const dmaConfig)
{
	// DMA Channel Properties
	DMA_ConfigureChannelProperties
	(
		&dmaConfig->properties,
		DMA_CHANNEL_PRIORITY_MEDIUM,
		DMA_CHANNEL_DIR_PERIPHERAL_TO_MEMORY,
		DMA_CHANNEL_CIRCULAR_MODE_DISABLE,
		DMA_CHANNEL_MEM2MEM_MODE_DISABLE
	);
	// Source: Peripheral Configuration
	DMA_ConfigureChannelEndPoint
	(
		&dmaConfig->peripheral,
		DMA_ENDPOINT_DATA_SIZE_8_BIT,
		DMA_ENDPOINT_MEMORY_INCREMENT_DISABLE
	);
	// Destination: Memory Configuration
	DMA_ConfigureChannelEndPoint
	(
		&dmaConfig->memory,
		DMA_ENDPOINT_DATA_SIZE_8_BIT,
		DMA_ENDPOINT_MEMORY_INCREMENT_ENABLE
	);
}

/**
 * @brief Configures DMA Channel for 8-bit Memory-to-Peripheral transfers (TX)
 * @param dmaConfig Pointer to DMA Channel configuration structure
 * @note Default configuration:
 * @note - Priority: Medium
 * @note - Direction: Peripheral to Memory  
 * @note - Circular: Disabled
 * @note - Data Size: 8 bits (both ends)
 * @note - Peripheral: Fixed address
 * @note - Memory: Increment address
 */
__STATIC_FORCEINLINE void DMA_LoadDefaultConfigForMEM2PER(dma_channel_config_t* const dmaConfig)
{
	// DMA Channel Properties
	DMA_ConfigureChannelProperties
	(
		&dmaConfig->properties,
		DMA_CHANNEL_PRIORITY_MEDIUM,
		DMA_CHANNEL_DIR_MEMORY_TO_PERIPHERAL,
		DMA_CHANNEL_CIRCULAR_MODE_DISABLE,
		DMA_CHANNEL_MEM2MEM_MODE_DISABLE
	);
	// Destination: Peripheral Configuration
	DMA_ConfigureChannelEndPoint
	(
		&dmaConfig->peripheral,
		DMA_ENDPOINT_DATA_SIZE_8_BIT,
		DMA_ENDPOINT_MEMORY_INCREMENT_DISABLE
	);
	// Source: Memory Configuration
	DMA_ConfigureChannelEndPoint
	(
		&dmaConfig->memory,
		DMA_ENDPOINT_DATA_SIZE_8_BIT,
		DMA_ENDPOINT_MEMORY_INCREMENT_ENABLE
	);
}

/**
 * @brief Polls the DMA Channel for Transfer Completion
 * @param dmaChannel DMA Channel. Refer `DMA_x_Channel_Y`
 */
__STATIC_FORCEINLINE void DMA_PollForTransferCompletion(const dma_channel_t dmaChannel)
{
	// Wait for completion
	while(_DMA_getIRQStatus(dmaChannel, DMA_IRQ_TRANSFER_COMPLETE) != DMA_IRQ_STATUS_TRANSFER_COMPLETE);
	// Acknowledge the IRQ
	_DMA_ackIRQStatus(dmaChannel, DMA_IRQ_TRANSFER_COMPLETE);
}

/**
 * @brief Enable IRQ for DMA Channel
 * @param dmaChannel DMA Channel
 * @param dmaIRQ Any logical combination of:
 * 				 - `DMA_IRQ_TRANSFER_COMPLETE`
 * 				 - `DMA_IRQ_HALF_TRANSFER_COMPLETE`
 * 				 - `DMA_IRQ_TRANSFER_ERROR`
 * @return Status of Driver Operation
 * @returns - `DRIVER_STATUS_ERROR_FAIL`: Failure
 * @returns - `DRIVER_STATUS_SUCCESS`: Success
 */
__STATIC_FORCEINLINE driver_status_t DMA_EnableChannelIRQ(const dma_channel_t dmaChannel, dma_irq_t dmaIRQ)
{
	_DMA_enableIRQ(dmaChannel, dmaIRQ);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Disable IRQ for DMA Channel
 * @param dmaChannel DMA Channel
 * @param dmaIRQ Any logical combination of:
 * 				 - `DMA_IRQ_TRANSFER_COMPLETE`
 * 				 - `DMA_IRQ_HALF_TRANSFER_COMPLETE`
 * 				 - `DMA_IRQ_TRANSFER_ERROR`
 * @return Status of Driver Operation
 * @returns - `DRIVER_STATUS_ERROR_FAIL`: Failure
 * @returns - `DRIVER_STATUS_SUCCESS`: Success
 */
__STATIC_FORCEINLINE driver_status_t DMA_DisableChannelIRQ(const dma_channel_t dmaChannel, dma_irq_t dmaIRQ)
{
	_DMA_disableIRQ(dmaChannel, dmaIRQ);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief DMA Channel Configuration
 * @param dmaChannel DMA Channel. Refer `DMA_x_Channel_Y`
 * @param dmaConfig Pointer to DMA Channel Configuration Structure
 * @return Status of Driver Operation
 * @returns - `DRIVER_STATUS_ERROR_FAIL`: Failure
 * @returns - `DRIVER_STATUS_SUCCESS`: Success
 */
driver_status_t DMA_ConfigChannel(const dma_channel_t dmaChannel, const dma_channel_config_t* const dmaConfig);

/**
 * @brief Configures the DMA Channel for memory to memory transfer mode
 * @param dmaChannel DMA Channel. Refer `DMA_x_Channel_Y`
 * @return Status of Driver Operation
 * @returns - `DRIVER_STATUS_ERROR_FAIL`: Failure
 * @returns - `DRIVER_STATUS_SUCCESS`: Success
 */
driver_status_t DMA_ConfigChannelForMem2Mem(const dma_channel_t dmaChannel);

/**
 * @brief Configures the DMA Channel for peripheral to memory transfer mode (RX)
 * @param dmaChannel DMA Channel. Refer `DMA_x_Channel_Y`
 * @return Status of Driver Operation
 * @returns - `DRIVER_STATUS_ERROR_FAIL`: Failure
 * @returns - `DRIVER_STATUS_SUCCESS`: Success
 */
driver_status_t DMA_ConfigChannelForPer2Mem(const dma_channel_t dmaChannel);

/**
 * @brief Configures the DMA Channel for memory to peripheral transfer mode (TX)
 * @param dmaChannel DMA Channel. Refer `DMA_x_Channel_Y`
 * @return Status of Driver Operation
 * @returns - `DRIVER_STATUS_ERROR_FAIL`: Failure
 * @returns - `DRIVER_STATUS_SUCCESS`: Success
 */
driver_status_t DMA_ConfigChannelForMem2Per(const dma_channel_t dmaChannel);

/**
 * @brief Configures transfer for DMA Channel
 * @param dmaChannel DMA Channel
 * @param dmaTransfer DMA Transfer
 * @return Status of Driver Operation
 * @returns - `DRIVER_STATUS_ERROR_FAIL`: Failure
 * @returns - `DRIVER_STATUS_SUCCESS`: Success
 */
driver_status_t DMA_Transfer(const dma_channel_t dmaChannel, const dma_transfer_t* const dmaTransfer);

#ifdef __OLD_DMA_METHOD__
#define DMA_I2C1_TX_Config()				DMA_Config(&DMA_I2C1_TX_Configuration)

//------------------------------------------------------------------------------
// DMA Channel Configuration Structure
//------------------------------------------------------------------------------
typedef struct {
	// Direction of data transfer
	// - `DMAx_DIR_MEM2MEM`
	// - `DMAx_DIR_PER2MEM`
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

//------------------------------------------------------------------------------
// DMA Channel Data Configuration Structure
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
// DMA Channel Interrupt Configuration Structure
//------------------------------------------------------------------------------
typedef struct {
	// Transfer Complete Interrupt Enable
	uint8_t TCIE: 1;
	// Half Transfer Interrupt Enable
	uint8_t HTIE: 1;
	// Transfer Error Interrupt Enable
	uint8_t TEIE: 1;
} dma_channel_intr_t;

// DMA Configuration Structure
typedef struct {
	// DMA Channel
	DMA_Channel_TypeDef *DMA_Channel;
	// Channel Configuration
	dma_channel_config_t channel;
	// Data Configuration Structure
	dma_channel_data_t data;
	// Interrupt Configuration Structure
	dma_channel_intr_t interrupt;
} dma_config_t;

//------------------------------------------------------------------------------
// I2C1 TX DMA Channel Configuration Structure
//------------------------------------------------------------------------------
static dma_config_t DMA_I2C1_TX_Configuration = {
	// DMA Channel
	.DMA_Channel = DMA_I2C1_TX,
	// Channel Properties
	.channel = {
		.direction = DMAx_DIR_READ_MEM,
		.mem2mem = DMAx_MEM2MEM_DISABLE,
		.circular_mode = DMAx_CIRC_DISABLE,
		.priority = DMAx_PRIORITY_VERY_HIGH
	},
	// Data Properties
	.data = {
		.srcDataSize = DMAx_DATA_SIZE_BIT_8,
		.dstDataSize = DMAx_DATA_SIZE_BIT_8,
		.srcInc = DMAx_INC_ENABLE,
		.dstInc = DMAx_INC_DISABLE
	},
	// Interrupt
	.interrupt = {
		.TCIE = DMAx_IRQ_ENABLE,
		.HTIE = DMAx_IRQ_DISABLE,
		.TEIE = DMAx_IRQ_ENABLE
	},
};

/**
 * @brief Enables the main DMA Clock
 * @param[in] DMA_channelX DMA Channel 
 */
__STATIC_FORCEINLINE void DMA_clk_enable(DMA_Channel_TypeDef* DMA_channelX){
	// Use Register
	uint32_t reg = RCC->AHBENR.REG;
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
__STATIC_FORCEINLINE void DMA_clk_disable(DMA_Channel_TypeDef* DMA_channelX){
	// Use Register
	uint32_t reg = RCC->AHBENR.REG;
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
 * @brief Enable the DMA Channel
 * @param[in] DMA_channelX DMA Channel
 */
__STATIC_FORCEINLINE void DMA_CH_enable(DMA_Channel_TypeDef* DMA_channelX){
	// Enable the Channel
	DMA_channelX->CCR.REG |= DMA_CCR_EN;
}

/**
 * @brief Disable the DMA Channel
 * @param[in] DMA_channelX DMA Channel
 */
__STATIC_FORCEINLINE void DMA_CH_disable(DMA_Channel_TypeDef* DMA_channelX){
	// Disable the Channel
	DMA_channelX->CCR.REG &= ~DMA_CCR_EN;
}

/**
 * @brief Get the DMA Channel IRQ Number
 * @param[in] DMA_channelX DMA Channel Number
 * @returns The DMA Channel IRQ Number
 */
__STATIC_FORCEINLINE uint8_t DMA_CH_get_IRQn(DMA_Channel_TypeDef* DMA_channelX){
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
 * @brief DMA Configuration
 * @param[in] instance DMA Configuration Structure
 */
void DMA_Config(dma_config_t* instance);

/**
 * @brief Configures the Transfer of the DMA Channel
 * @param[in] DMA_channelX DMA Channel
 * @param[in] src Pointer to Source
 * @param[in] dst Pointer to Destination
 * @param[in] size Size of the data to be transferred
 */
void DMA_Transfer_Config(DMA_Channel_TypeDef* DMA_channelX, void* src, void* dst, uint16_t size);

/**
 * @brief Loads the default configuration for Memory to Memory Transfer
 * @param[in] instance DMA Configuration Structure
 */
void DMA_Load_Default_MEM2MEM(dma_config_t* instance);

/**
 * @brief Loads the default configuration for Peripheral to Memory Transfer
 * @param[in] instance DMA Configuration Structure
 */
void DMA_Load_Default_PER2MEM(dma_config_t* instance);

/**
 * @brief Loads the default configuration for Memory to Peripheral Transfer
 * @param[in] instance DMA Configuration Structure
 */
void DMA_Load_Default_MEM2PER(dma_config_t* instance);
#endif /* __OLD_DMA_METHOD__ */

#endif /* DMA_H_ */