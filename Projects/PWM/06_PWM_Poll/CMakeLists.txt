# =============================================================================
# Minimum CMake Version
# =============================================================================
cmake_minimum_required(VERSION 3.28)

# =============================================================================
# Project
# =============================================================================
get_filename_component(PROJECT_NAME ${CMAKE_SOURCE_DIR} NAME)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES C CXX ASM)

# =============================================================================
# Project Configuration
# =============================================================================
get_filename_component(PROJ_DIR "${CMAKE_SOURCE_DIR}" ABSOLUTE)		# Project Root
get_filename_component(REPO_ROOT "${PROJ_DIR}/../../../" ABSOLUTE)	# Repository Root
set(DRIVER_ROOT	${REPO_ROOT}/BareMetal/Driver)						# Hardware abstraction layer
set(CORE_ROOT ${REPO_ROOT}/BareMetal/Core)							# Core system files

# =============================================================================
# Toolchain Path
# =============================================================================
set(TOOLCHAIN_PATH 			"/opt/arm-gnu-toolchain-14.3/bin")			# Full-path to toolchain
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
    NVIC
    GPIO  
    RCC
    Timer
    DMA
)

# =============================================================================
# Include Main CMake Template
# =============================================================================
include(${CORE_ROOT}/Src/CMake_Template.cmake)