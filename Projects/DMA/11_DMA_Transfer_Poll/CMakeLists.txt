# This file is the build entrypoint for the DMA memory-to-memory poll demonstration.
# It owns application identity and direct Driver capability selection. Shared
# compiler, Core, linker, artifact, and utility-target policy remains under
# BareMetal/CMake so this project contains no duplicated platform machinery.

# ====================================================================================================
# CMake Compatibility
# ====================================================================================================

# Require the minimum version supported by the shared STM32F103 pipeline.
cmake_minimum_required(VERSION 3.28)

# ====================================================================================================
# Shared Repository Discovery
# ====================================================================================================

# Projects kept outside this repository may supply the directory containing
# BareMetal explicitly. An empty value enables automatic upward discovery.
set(STM32F103_REPO_ROOT "" CACHE PATH "STM32F103C8T6 repository root containing BareMetal")

if(STM32F103_REPO_ROOT)
    # Normalize an absolute or project-relative caller override before use.
    get_filename_component(
        _stm32_repo_root
        "${STM32F103_REPO_ROOT}"
        ABSOLUTE
        BASE_DIR "${CMAKE_CURRENT_LIST_DIR}"
    )
else()
    # Walk upward so any project nested inside the repository configures with
    # no caller-supplied path.
    set(_stm32_repo_root "${CMAKE_CURRENT_LIST_DIR}")
    while(NOT EXISTS "${_stm32_repo_root}/BareMetal/CMake/STM32F103Project.cmake")
        get_filename_component(_stm32_repo_parent "${_stm32_repo_root}" DIRECTORY)
        if(_stm32_repo_parent STREQUAL _stm32_repo_root)
            break()
        endif()
        set(_stm32_repo_root "${_stm32_repo_parent}")
    endwhile()
endif()

# Fail with the exact external-project remedy when neither discovery path
# resolves the shared build entrypoint.
if(NOT EXISTS "${_stm32_repo_root}/BareMetal/CMake/STM32F103Project.cmake")
    message(
        FATAL_ERROR
        "Unable to locate BareMetal/CMake/STM32F103Project.cmake. "
        "Set STM32F103_REPO_ROOT to the STM32F103C8T6 repository root."
    )
endif()

# Import the single public CMake interface; it owns every lower build module.
include("${_stm32_repo_root}/BareMetal/CMake/STM32F103Project.cmake")

# ====================================================================================================
# Toolchain and Application Identity
# ====================================================================================================

# Select the canonical Arm toolchain before project() probes a compiler.
stm32f103_setup_toolchain()

# Keep the target and generated artifact names synchronized with this folder.
get_filename_component(_stm32_project_name "${CMAKE_CURRENT_LIST_DIR}" NAME)
project(${_stm32_project_name} VERSION 1.0.0 LANGUAGES C CXX ASM)

# ====================================================================================================
# Application Feature Selection
# ====================================================================================================

# These cache options mirror the Template's application-facing hardware
# policy. They control both shared Driver inclusion below and conditional
# Template code through the compile definitions published at the end of
# this file.
option(APP_ENABLE_SYSTICK_TIMEBASE "Enable the SysTick millisecond timebase" ON)
option(APP_ENABLE_TIMER_US_DELAY "Enable the optional TIM4 microsecond delay service" OFF)
option(APP_ENABLE_ONBOARD_LED "Enable App_Init() on-board LED configuration" ON)
option(APP_ENABLE_PRINTF_FLOAT "Enable newlib-nano floating-point printf/scanf support (-u _printf_float)" ON)

# DMA is required directly by the application for the memory-to-memory
# transfer; it has no Driver dependencies of its own. BSP drives the
# heartbeat LED and resolves GPIO -> RCC automatically.
set(app_driver_modules BSP DMA)
if(APP_ENABLE_SYSTICK_TIMEBASE)
    list(APPEND app_driver_modules SysTick)
endif()
if(APP_ENABLE_TIMER_US_DELAY)
    list(APPEND app_driver_modules Timer)
endif()

# ====================================================================================================
# Firmware Build Configuration
# ====================================================================================================

# Hand application policy to the shared pipeline the same way the Template
# does, so this demonstration exercises the modular application layers end
# to end instead of the legacy startup/systick pairing.
stm32f103_configure_project(
    # Store deployable firmware separately from CMake generator metadata.
    BUILD_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/Artifacts"
    # Keep the configuration summary compact while retaining module detail.
    DRIVER_MODULE_TREE SHOW_FILENAME_ONLY
    # Compile and expose exactly the shared Driver stacks selected above.
    DRIVER_MODULES
        ${app_driver_modules}
    # Preserve the demonstration's established optimization and Flash origin.
    OPTIMIZATION_LEVEL 1
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
