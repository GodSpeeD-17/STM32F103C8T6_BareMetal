# This toolchain file establishes the cross-compilation environment consumed by
# every STM32F103 application before CMake enables a project language. Hardware
# flags remain target-owned in STM32F103Flags.cmake; this file selects tools only.

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(TOOLCHAIN_PATH "/opt/arm-gnu-toolchain-14.3/bin" CACHE PATH "Arm GNU toolchain binary directory")
set(CMAKE_SYSTEM_TOOLCHAIN_PREFIX "arm-none-eabi")
set(TOOLCHAIN_PREFIX "${TOOLCHAIN_PATH}/${CMAKE_SYSTEM_TOOLCHAIN_PREFIX}")

set(CMAKE_C_COMPILER "${TOOLCHAIN_PREFIX}-gcc" CACHE FILEPATH "Arm GNU C compiler")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}-g++" CACHE FILEPATH "Arm GNU C++ compiler")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PREFIX}-gcc" CACHE FILEPATH "Arm GNU assembler driver")

set(CMAKE_OBJCOPY "${TOOLCHAIN_PREFIX}-objcopy" CACHE FILEPATH "Arm GNU object-copy utility")
set(CMAKE_OBJDUMP "${TOOLCHAIN_PREFIX}-objdump" CACHE FILEPATH "Arm GNU object-dump utility")
set(CMAKE_NM "${TOOLCHAIN_PREFIX}-nm" CACHE FILEPATH "Arm GNU symbol utility")
set(CMAKE_SIZE "${TOOLCHAIN_PREFIX}-size" CACHE FILEPATH "Arm GNU size utility")
