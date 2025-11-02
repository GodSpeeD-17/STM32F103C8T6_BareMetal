# =============================================================================
# Minimum CMake Version
# =============================================================================
cmake_minimum_required(VERSION 3.28)

# =============================================================================
# Cross-Compilation Toolchain Configuration
# =============================================================================
set(TOOLCHAIN_PATH "/opt/arm-gnu-toolchain-14.3/bin")		# Full-path to toolchain
set(CMAKE_SYSTEM_NAME Generic)								# Bare-metal target (no OS)
set(CMAKE_SYSTEM_PROCESSOR arm)								# Target processor architecture
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)			# Required for cross-compilation
set(CMAKE_SYSTEM_TOOLCHAIN_PREFIX ${CMAKE_SYSTEM_PROCESSOR}-none-eabi)
set(TOOLCHAIN_PREFIX ${TOOLCHAIN_PATH}/${CMAKE_SYSTEM_TOOLCHAIN_PREFIX})
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)

# =============================================================================
# Project Configuration
# =============================================================================
get_filename_component(PROJ_DIR "${CMAKE_SOURCE_DIR}" ABSOLUTE)		# Project Root
get_filename_component(REPO_ROOT "${PROJ_DIR}/../../../" ABSOLUTE)	# Repository Root
set(DRIVER_ROOT	${REPO_ROOT}/BareMetal/Driver)						# Hardware abstraction layer
set(CORE_ROOT ${REPO_ROOT}/BareMetal/Core)							# Core system files
set(BUILD_OUTPUT_DIR	${PROJ_DIR}/Build)							# Build artifacts directory

# ---------------------- Flashing/Debugger Executables ----------------------
set(ST_FLASH_PATH 			"/usr/bin/st-flash")						# Full path to st-flash
set(ST_UTIL_PATH  			"/usr/bin/st-util")							# ST-Link GDB server
set(OPENOCD_PATH			"/usr/bin/openocd")							# Full path to OpenOCD
set(ST_UART_FLASH_PORT		"/dev/ttyUSB0")      						# Default UART port for flashing
set(GDB_PATH_MULTIARCH_PATH "/usr/bin/gdb-multiarch")					# ARM GDB debugger

# =============================================================================
# Driver Modules
# =============================================================================
set(DRIVER_MODULE_TREE SHOW_FILENAME_ONLY) # SHOW_FULL_PATH / SHOW_FILENAME_ONLY
set(DRIVER_MODULES
	RCC
    GPIO
	NVIC  
    Timer
)

# =============================================================================
# Project
# =============================================================================
get_filename_component(PROJECT_NAME ${CMAKE_SOURCE_DIR} NAME)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES C CXX ASM)
set(LINKER_FILE ${CORE_ROOT}/Src/stm32f103c8t6.ld)  # Default linker script
set(FLASH_ADDRESS 0x08000000)
set(OPTIMIZATION_LEVEL 1) # Standard Optimization

# =============================================================================
# Include Main CMake Template
# =============================================================================
include(${CORE_ROOT}/Src/CMake_Template.cmake)