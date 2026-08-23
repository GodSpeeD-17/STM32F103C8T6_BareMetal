/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Implements the DMA memory-to-memory poll demo application behavior
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior implementation
 * - Called by: Layer 4 Reset_Handler() after App_Init() succeeds
 * - Uses: Layer 2 `app_delay` and Layer 1 DMA/BSP Drivers
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * Performs one polled DMA memory-to-memory transfer from a source buffer to
 * a destination buffer, then toggles the on-board LED forever as a heartbeat.
 *
 * @section MAIN_C_BOUNDARY Dependency Boundary
 * Application behavior belongs here. Processor startup, clock configuration,
 * and service initialization do not.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "main.h"
#include "app_delay.h"
#include "bsp.h"
#include "dma.h"

// ==================================================================================================== //
// Private Defines
// ==================================================================================================== //

/** @brief DMA channel used by the memory-to-memory transfer demo @def DMA_CHANNEL */
#define DMA_CHANNEL						DMA_1_Channel_4
/** @brief Number of elements transferred by the demo @def DMA_DATA_COUNT */
#define DMA_DATA_COUNT					(100)
/** @brief Source buffer fill value before the transfer @def DMA_SRC_DUMMY_VALUE */
#define DMA_SRC_DUMMY_VALUE				(0x24)
/** @brief Destination buffer fill value before the transfer @def DMA_DST_DUMMY_VALUE */
#define DMA_DST_DUMMY_VALUE				(0x55)
/** @brief On-board LED heartbeat delay in milliseconds @def LOOP_DELAY_MS */
#define LOOP_DELAY_MS					((uint32_t) 1000UL)

// ==================================================================================================== //
// Local Variables
// ==================================================================================================== //

typedef uint8_t dma_data_type_t;

/** @brief Source buffer transferred by the demo */
static dma_data_type_t srcData[DMA_DATA_COUNT] =
{
	[0 ... (DMA_DATA_COUNT - 1)] = DMA_SRC_DUMMY_VALUE
};
/** @brief Destination buffer written by the demo */
static dma_data_type_t dstData[DMA_DATA_COUNT] =
{
	[0 ... (DMA_DATA_COUNT - 1)] = DMA_DST_DUMMY_VALUE
};

// ==================================================================================================== //
// Application Entry Point
// ==================================================================================================== //

int main(void)
{
	const dma_transfer_t transferConfig =
	{
		.src = (dma_src_t) srcData,
		.dst = (dma_dst_t) dstData,
		.size = (dma_size_t) DMA_DATA_COUNT
	};

	DMA_ConfigChannelForMem2Mem(DMA_CHANNEL);
	DMA_Transfer(DMA_CHANNEL, &transferConfig);
	DMA_PollForTransferCompletion(DMA_CHANNEL);

	while (1)
	{
		BSP_OB_LED_Toggle();
		(void) App_DelayMs(LOOP_DELAY_MS);
	}
}
