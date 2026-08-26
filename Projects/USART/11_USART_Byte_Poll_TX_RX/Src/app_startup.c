/**
 * @file	app_startup.c
 * @author	Shrey Shah
 * @brief	Owns the application vector table and reset-to-main sequence
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section APP_STARTUP_C_HIERARCHY Hierarchy
 * - Position: Layer 4 - Processor entry implementation
 * - Invoked by: Processor reset and exception dispatch
 * - Uses: Layer 3 App_BootInit() and main()
 *
 * @section APP_STARTUP_C_RESPONSIBILITY Responsibility
 * This is the only translation unit that defines the vector table and weak
 * fallback handlers. Reset_Handler() copies `.data`, clears `.bss`, calls
 * App_BootInit(), and transfers control to main().
 *
 * @section APP_STARTUP_C_THEORY Reset and C-Runtime Theory
 * At reset, the Cortex-M3 Vector Table Offset Register selects its reset base
 * address `0x00000000`. The STM32F103 boot pins decide which physical memory
 * appears at that address: main Flash for the normal BOOT0-low application
 * boot, the factory system-memory bootloader, or SRAM for the other supported
 * boot selections. This firmware requires normal main-Flash boot, where
 * `0x00000000` is an alias of main Flash at `0x08000000`; the linker therefore
 * keeps this file's vector table at the main-Flash image origin.
 *
 * The reset-exception architecture then reads exactly two 32-bit vector-table
 * entries: word zero becomes the Main Stack Pointer and word one becomes the
 * Program Counter. Those are the only processor state values required to
 * start the reset handler; later vector-table entries are read only if their
 * corresponding exception or interrupt occurs. This hardware-defined entry
 * sequence does not implement the C language requirements for static-storage
 * objects. Before ordinary C code may observe globals or statics, explicitly
 * initialized objects must contain their declared values and uninitialized
 * objects must contain zero.
 *
 * Flash retains the complete firmware image across reset but is not the
 * run-time home for writable C objects. RAM is writable but does not retain
 * the initialized `.data` image supplied by the program. The linker therefore
 * gives `.data` two locations: a load image in Flash and a run-time interval
 * in RAM. In contrast, `.bss` has no Flash load image because its required
 * initial state is uniformly zero; reset code creates that state directly in
 * RAM. Code, constants, and the vector table remain in Flash and are executed
 * or read there, so they require neither a start-up copy nor clearing.
 *
 * @section APP_STARTUP_C_RESET_CONTEXT Reset Processor Context: MSP and PC
 * The Main Stack Pointer (MSP) is the Cortex-M3's primary stack register
 * (`R13`). It contains the current top address of the main stack in RAM. The
 * stack grows downward and supplies temporary storage for function calls,
 * return addresses, local variables, saved registers, and exception-entry
 * context. Cortex-M3 also supports a Process Stack Pointer for selected Thread
 * mode software, but reset begins using MSP and every exception handler uses
 * MSP. A valid MSP is therefore required before the reset code can safely make
 * a C call, allocate a stack local, or service an exception.
 *
 * The Program Counter (PC, `R15`) holds the address of the next instruction to
 * execute. The processor cannot begin firmware execution without it: it needs
 * one defined instruction address after reset, just as a C function call needs
 * a defined return target. The vector table supplies both prerequisites in its
 * architecturally fixed reset entries:
 *
 * @verbatim
 * vector-table word 0  ->  MSP = _estack
 * vector-table word 1  ->  PC  = Reset_Handler address
 * @endverbatim
 *
 * The processor does not call Reset_Handler() through the normal C calling
 * convention. It reads vector-table word one in hardware and loads that value
 * directly into PC, so the first firmware instruction fetched is the first
 * instruction of Reset_Handler(). The handler's address is stored in the
 * vector table because it is the project-defined routine that establishes the
 * C runtime contract before any ordinary application function executes.
 *
 * @section APP_STARTUP_C_IMPLEMENTATION Theory-to-Implementation Mapping
 * `BareMetal/Core/Src/stm32f103c8t6.ld` places `.data` in RAM with `AT >
 * FLASH`. It emits `_sidata` for the Flash load address and `_sdata` / `_edata`
 * for the half-open RAM interval. It places `.bss` only in RAM and emits
 * `_sbss` / `_ebss` for its corresponding interval. The same linker script
 * assigns `_estack` to the top of RAM and keeps this file's `.isr_vector`
 * section at the Flash image origin.
 *
 * The vector table below maps `_estack` to hardware's initial stack-pointer
 * word and Reset_Handler() to its initial program-counter word. Reset_Handler()
 * then copies `[_sidata, ...)` into `[_sdata, _edata)`, writes zero through
 * `[_sbss, _ebss)`, and only then calls App_BootInit() and main(). The half-open
 * interval convention includes each start symbol and excludes each end symbol,
 * so an empty section naturally performs zero loop iterations while a nonempty
 * section stops at its exact linker-defined boundary.
 *
 * @section APP_STARTUP_C_MEMORY_LAYOUT Flash-to-RAM Reset Layout
 * @verbatim
 *
 * Flash                                   RAM
 * ┌───────────────────────────────┐       ┌────────────────────────────────┐
 * │ vector table at 0x08000000    │       │ .data run-time objects         │
 * │ alias: 0x00000000 at reset    │       │ [_sdata, _edata)               │
 * │ word 0: _estack               │       │ copied from _sidata            │
 * │ word 1: Reset_Handler         │       │ .bss objects                   │
 * │ code and read-only constants  │       │ [_sbss, _ebss) = zero          │
 * │ .data image at _sidata        │──────>│ heap / stack; _estack at top   │
 * └───────────────────────────────┘       └────────────────────────────────┘
 *
 * @endverbatim
 *
 * @section APP_STARTUP_C_BOUNDARY Dependency Boundary
 * Startup owns processor and C-runtime handoff only. Peripheral policy, heap
 * adaptation, and application behavior remain in lower modules, and no lower
 * module includes @ref `app_startup.h`.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "app_startup.h"
#include "app_init.h"
#include "main.h"
#include "stm32f1xx.h"

// ==================================================================================================== //
// Private Defines
// ==================================================================================================== //

/** @brief Number of Cortex-M3 core vector entries @def APP_CORE_VECTOR_COUNT */
#define APP_CORE_VECTOR_COUNT			((uint32_t) 16UL)
/** @brief Number of STM32F103C8T6 external interrupt vectors @def APP_EXTERNAL_VECTOR_COUNT */
#define APP_EXTERNAL_VECTOR_COUNT		((uint32_t) 43UL)

/**
 * @brief Declares a processor handler as a weak alias of Default_Handler()
 * @details A project may override any declaration with one strong handler definition.
 * @param[in] handlerName Processor-defined exception or interrupt handler identifier
 * @def APP_DECLARE_DEFAULT_HANDLER
 */
#define APP_DECLARE_DEFAULT_HANDLER(handlerName)		\
	void __attribute__((weak, alias("Default_Handler"))) handlerName(void)

// ==================================================================================================== //
// Weak Exception Handlers
// ==================================================================================================== //

APP_DECLARE_DEFAULT_HANDLER(NMI_Handler);
APP_DECLARE_DEFAULT_HANDLER(HardFault_Handler);
APP_DECLARE_DEFAULT_HANDLER(MemManage_Handler);
APP_DECLARE_DEFAULT_HANDLER(BusFault_Handler);
APP_DECLARE_DEFAULT_HANDLER(UsageFault_Handler);
APP_DECLARE_DEFAULT_HANDLER(SVC_Handler);
APP_DECLARE_DEFAULT_HANDLER(DebugMon_Handler);
APP_DECLARE_DEFAULT_HANDLER(PendSV_Handler);
APP_DECLARE_DEFAULT_HANDLER(SysTick_Handler);
APP_DECLARE_DEFAULT_HANDLER(WWDG_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(PVD_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(TAMPER_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(RTC_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(FLASH_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(RCC_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(EXTI0_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(EXTI1_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(EXTI2_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(EXTI3_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(EXTI4_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(DMA1_Channel1_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(DMA1_Channel2_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(DMA1_Channel3_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(DMA1_Channel4_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(DMA1_Channel5_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(DMA1_Channel6_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(DMA1_Channel7_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(ADC1_2_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(USB_HP_CAN_TX_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(USB_LP_CAN_RX0_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(CAN_RX1_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(CAN_SCE_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(EXTI9_5_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(TIM1_BRK_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(TIM1_UP_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(TIM1_TRG_COM_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(TIM1_CC_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(TIM2_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(TIM3_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(TIM4_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(I2C1_EV_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(I2C1_ER_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(I2C2_EV_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(I2C2_ER_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(SPI1_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(SPI2_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(USART1_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(USART2_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(USART3_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(EXTI15_10_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(RTCAlarm_IRQHandler);
APP_DECLARE_DEFAULT_HANDLER(USBWakeUp_IRQHandler);

// ==================================================================================================== //
// Vector Table
// ==================================================================================================== //

/**
 * @brief Project-owned processor vector table placed at the Flash image origin
 * @details Contains 16 Cortex-M3 core entries followed by 43 device IRQ entries.
 */
__attribute__((used, section(".isr_vector"))) static const uintptr_t appVectorTable[APP_CORE_VECTOR_COUNT + APP_EXTERNAL_VECTOR_COUNT] =
{
	(uintptr_t) &_estack,
	(uintptr_t) Reset_Handler,
	(uintptr_t) NMI_Handler,
	(uintptr_t) HardFault_Handler,
	(uintptr_t) MemManage_Handler,
	(uintptr_t) BusFault_Handler,
	(uintptr_t) UsageFault_Handler,
	0UL,
	0UL,
	0UL,
	0UL,
	(uintptr_t) SVC_Handler,
	(uintptr_t) DebugMon_Handler,
	0UL,
	(uintptr_t) PendSV_Handler,
	(uintptr_t) SysTick_Handler,
	(uintptr_t) WWDG_IRQHandler,
	(uintptr_t) PVD_IRQHandler,
	(uintptr_t) TAMPER_IRQHandler,
	(uintptr_t) RTC_IRQHandler,
	(uintptr_t) FLASH_IRQHandler,
	(uintptr_t) RCC_IRQHandler,
	(uintptr_t) EXTI0_IRQHandler,
	(uintptr_t) EXTI1_IRQHandler,
	(uintptr_t) EXTI2_IRQHandler,
	(uintptr_t) EXTI3_IRQHandler,
	(uintptr_t) EXTI4_IRQHandler,
	(uintptr_t) DMA1_Channel1_IRQHandler,
	(uintptr_t) DMA1_Channel2_IRQHandler,
	(uintptr_t) DMA1_Channel3_IRQHandler,
	(uintptr_t) DMA1_Channel4_IRQHandler,
	(uintptr_t) DMA1_Channel5_IRQHandler,
	(uintptr_t) DMA1_Channel6_IRQHandler,
	(uintptr_t) DMA1_Channel7_IRQHandler,
	(uintptr_t) ADC1_2_IRQHandler,
	(uintptr_t) USB_HP_CAN_TX_IRQHandler,
	(uintptr_t) USB_LP_CAN_RX0_IRQHandler,
	(uintptr_t) CAN_RX1_IRQHandler,
	(uintptr_t) CAN_SCE_IRQHandler,
	(uintptr_t) EXTI9_5_IRQHandler,
	(uintptr_t) TIM1_BRK_IRQHandler,
	(uintptr_t) TIM1_UP_IRQHandler,
	(uintptr_t) TIM1_TRG_COM_IRQHandler,
	(uintptr_t) TIM1_CC_IRQHandler,
	(uintptr_t) TIM2_IRQHandler,
	(uintptr_t) TIM3_IRQHandler,
	(uintptr_t) TIM4_IRQHandler,
	(uintptr_t) I2C1_EV_IRQHandler,
	(uintptr_t) I2C1_ER_IRQHandler,
	(uintptr_t) I2C2_EV_IRQHandler,
	(uintptr_t) I2C2_ER_IRQHandler,
	(uintptr_t) SPI1_IRQHandler,
	(uintptr_t) SPI2_IRQHandler,
	(uintptr_t) USART1_IRQHandler,
	(uintptr_t) USART2_IRQHandler,
	(uintptr_t) USART3_IRQHandler,
	(uintptr_t) EXTI15_10_IRQHandler,
	(uintptr_t) RTCAlarm_IRQHandler,
	(uintptr_t) USBWakeUp_IRQHandler
};

// ==================================================================================================== //
// Default Exception Handler
// ==================================================================================================== //

void Default_Handler(void)
{
	while (1)
	{
		//! Contain the fault without consuming cycles while a debugger inspects processor state.
		__WFI();
	}
}

// ==================================================================================================== //
// Reset Handler
// ==================================================================================================== //

/**
 * @brief Establishes the C runtime storage contract and starts the application
 * @details Copies the Flash `.data` load image into RAM, clears `.bss`, then
 * calls App_BootInit() and main() only after global and static C storage is valid.
 * @returns Does not return
 */
__attribute__((noreturn)) void Reset_Handler(void)
{
	//! The linker aligns `.data` to four bytes and this loop copies dereferenceable 32-bit words, so
	//! `uint32_t*` exposes its actual transfer width and alignment. `uintptr_t` only stores an address
	//! as an integer; it would require a cast back to `uint32_t*` before every `*` access and hide this
	//! word-copy contract without making the linker-symbol addresses more accurate.
	uint32_t* pSource = &_sidata;
	uint32_t* pDestination = &_sdata;

	//! Materialize initialized C objects from their linker-defined Flash load image.
	while (pDestination < &_edata)
	{
		*pDestination = *pSource;
		pDestination++;
		pSource++;
	}

	//! Establish the zero-initialization guarantee required before any C service executes.
	pDestination = &_sbss;
	while (pDestination < &_ebss)
	{
		*pDestination = 0UL;
		pDestination++;
	}

	//! Prevent partially initialized hardware from reaching application behavior.
	if (App_BootInit() != DRIVER_STATUS_SUCCESS)
	{
		Default_Handler();
	}

	//! Transfer control only after every selected application service is ready.
	(void) main();

	//! Contain an application that unexpectedly returns through the reset entry path.
	while (1)
	{
		Default_Handler();
	}
}
