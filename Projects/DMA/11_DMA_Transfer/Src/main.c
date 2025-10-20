/*-------------------------------------------------------------------------------*/
// Header Files
#include "reg_map.h"
#include "main.h"
/*-------------------------------------------------------------------------------*/
// Macros
#define DMA_CHANNEL 					DMA_1_Channel_4
#define DMA_DATA_COUNT					100
#define DMA_SRC_DUMMY_VALUE				0x24
#define DMA_DST_DUMMY_VALUE				0x55
/*-------------------------------------------------------------------------------*/
// Global Variables
typedef uint8_t dma_data_type_t; 
dma_data_type_t srcData[DMA_DATA_COUNT] =
{
	[0 ... (DMA_DATA_COUNT - 1)] = DMA_SRC_DUMMY_VALUE
};
dma_data_type_t dstData[DMA_DATA_COUNT] =
{
	[0 ... (DMA_DATA_COUNT - 1)] = DMA_DST_DUMMY_VALUE
};

/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main()
{
	// Initialisation
	DMA_ConfigChannelForMem2Mem(DMA_CHANNEL);
	_DMA_enableChannel(DMA_CHANNEL);
	// Transfer Configure
	dma_transfer_t transferConfig = {
		.src = (dma_src_t) srcData,
		.dst = (dma_dst_t) dstData,
		.size = (dma_size_t) DMA_DATA_COUNT
	};
	// Initiate the Transfer
	DMA_Transfer(
		DMA_CHANNEL,
		&transferConfig
	);
	// Wait for Transfer Completion
	DMA_PollForTransferCompletion(DMA_CHANNEL);

	// Infinite Loop
	while(1){
		// Toggle OB LED
		OB_LED_Toggle();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/