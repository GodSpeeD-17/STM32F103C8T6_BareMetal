# This file is the build entrypoint for the Timer PWM update-IRQ demonstration.
# It owns application identity and direct Driver capability selection. Shared
# compiler, Core, linker, artifact, and utility-target policy remains under
# BareMetal/CMake so this project contains no duplicated platform machinery.

# ====================================================================================================
# CMake Compatibility
# ====================================================================================================

# Require the CMake version against which the shared STM32F103 pipeline is
# maintained. Rejecting older versions avoids partially supported behavior.
cmake_minimum_required(VERSION 3.28)

# ====================================================================================================
# Shared Repository Discovery
# ====================================================================================================

# External projects may explicitly identify the repository containing the
# shared BareMetal platform. An empty value preserves zero-configuration use
# for projects stored anywhere below this repository root.
set(STM32F103_REPO_ROOT "" CACHE PATH "STM32F103C8T6 repository root containing BareMetal")

if(STM32F103_REPO_ROOT)
    # Normalize an explicit absolute or project-relative override before it is
    # validated and consumed by the shared build entrypoint.
    get_filename_component(
        _stm32_repo_root
        "${STM32F103_REPO_ROOT}"
        ABSOLUTE
        BASE_DIR "${CMAKE_CURRENT_LIST_DIR}"
    )
else()
    # Walk upward from the copied project until the shared build entrypoint is
    # found. This permits arbitrary project nesting within the repository.
    set(_stm32_repo_root "${CMAKE_CURRENT_LIST_DIR}")
    while(NOT EXISTS "${_stm32_repo_root}/BareMetal/CMake/STM32F103Project.cmake")
        get_filename_component(_stm32_repo_parent "${_stm32_repo_root}" DIRECTORY)
        # Stop at the filesystem root so a missing repository fails cleanly
        # through the common validation below instead of looping forever.
        if(_stm32_repo_parent STREQUAL _stm32_repo_root)
            break()
        endif()
        set(_stm32_repo_root "${_stm32_repo_parent}")
    endwhile()
endif()

# Validate the one shared entrypoint required by both discovery paths. The
# diagnostic also tells an external application how to repair its configuration.
if(NOT EXISTS "${_stm32_repo_root}/BareMetal/CMake/STM32F103Project.cmake")
    message(
        FATAL_ERROR
        "Unable to locate BareMetal/CMake/STM32F103Project.cmake. "
        "Set STM32F103_REPO_ROOT to the STM32F103C8T6 repository root."
    )
endif()

# Import only the public project-configuration interface. That interface owns
# all lower shared CMake modules and prevents application-level include chains.
include("${_stm32_repo_root}/BareMetal/CMake/STM32F103Project.cmake")

# ====================================================================================================
# Toolchain and Application Identity
# ====================================================================================================

# Select the Arm cross-toolchain before project() allows CMake to probe a host
# compiler. The shared function also enables compile_commands.json generation.
stm32f103_setup_toolchain()

# Derive the application and firmware-target name from the copied directory.
# Renaming the project directory therefore renames its ELF/BIN/HEX/MAP outputs.
# C, C++, and assembly are enabled up front so adding a C++ application source
# does not require restructuring this build entrypoint.
get_filename_component(_stm32_project_name "${CMAKE_CURRENT_LIST_DIR}" NAME)
project(${_stm32_project_name} VERSION 1.0.0 LANGUAGES C CXX ASM)

# ====================================================================================================
# Application Feature Selection
# ====================================================================================================

# These cache options mirror the Template's application-facing hardware
# policy. They control both shared Driver inclusion below and conditional
# Template code through the compile definitions published at the end of
# this file. The demo needs neither the SysTick timebase nor the TIM4 polling
# delay service: the ramp is entirely event-driven by the TIM2 update IRQ, and
# the idle main loop sleeps on __WFI() instead of blocking on App_DelayMs().
option(APP_ENABLE_SYSTICK_TIMEBASE "Enable the SysTick millisecond timebase" OFF)
option(APP_ENABLE_TIMER_US_DELAY "Enable the optional TIM4 microsecond delay service" OFF)
option(APP_ENABLE_ONBOARD_LED "Enable App_Init() on-board LED configuration" ON)
option(APP_ENABLE_PRINTF_FLOAT "Enable newlib-nano floating-point printf/scanf support (-u _printf_float)" ON)

# BSP drives the error-indication LED, NVIC arms the TIM2 update-IRQ line, and
# Timer is required directly by the application for TIM2 PWM. The component
# graph resolves BSP -> GPIO -> RCC and Timer -> RCC automatically.
set(app_driver_modules BSP NVIC Timer)
if(APP_ENABLE_SYSTICK_TIMEBASE)
    list(APPEND app_driver_modules SysTick)
endif()

# ====================================================================================================
# Firmware Build Configuration
# ====================================================================================================

# Hand application policy to the shared pipeline the same way the Template
# does, so this demonstration exercises the modular application layers end
# to end instead of the legacy startup/systick pairing.
stm32f103_configure_project(
    # Keep deployable outputs separate from CMake cache and generator files.
    BUILD_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/Artifacts"
    # Print selected Driver filenames during configuration without full paths.
    DRIVER_MODULE_TREE SHOW_FILENAME_ONLY
    # Compile and expose exactly the shared Driver stacks selected above.
    DRIVER_MODULES
        ${app_driver_modules}
    # Use the shared pipeline's supported -O1 optimization policy.
    OPTIMIZATION_LEVEL 1
    # Link the application at the STM32F103C8T6 internal-Flash base address.
    FLASH_ADDRESS 0x08000000
)

# Publish normalized 0/1 feature states only to this firmware target. Template
# sources and app_config.h consume the same values used for Driver selection,
# keeping compiled application APIs synchronized with linked Driver modules.
target_compile_definitions(${PROJECT_NAME}.elf PRIVATE
    APP_ENABLE_SYSTICK_TIMEBASE=$<BOOL:${APP_ENABLE_SYSTICK_TIMEBASE}>
    APP_ENABLE_TIMER_US_DELAY=$<BOOL:${APP_ENABLE_TIMER_US_DELAY}>
    APP_ENABLE_ONBOARD_LED=$<BOOL:${APP_ENABLE_ONBOARD_LED}>
)

# The shared --specs=nano.specs link policy strips floating-point printf
# support by default. APP_ENABLE_PRINTF_FLOAT controls whether this target
# pulls the newlib-nano float formatter in via -u _printf_float, scoped to
# this one target rather than widening the shared STM32F103Flags.cmake link
# policy for every project.
if(APP_ENABLE_PRINTF_FLOAT)
    target_link_options(${PROJECT_NAME}.elf PRIVATE -u _printf_float)
endif()
