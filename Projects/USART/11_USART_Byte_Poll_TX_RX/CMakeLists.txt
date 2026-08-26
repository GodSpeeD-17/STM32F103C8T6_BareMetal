# This file is the build entrypoint for the USART byte TX/RX polling demonstration.
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

# These cache options define Project 11's application-facing hardware policy.
# The timebase source selects exactly one interrupt-driven hardware owner while
# its fixed 1 kHz interrupt defines a 1 ms application tick. Floating-point
# application logic and generic debug code remain independent features;
# together they select floating-point diagnostics.
set(APP_TIMEBASE_SOURCE "SYSTICK" CACHE STRING "Application timebase source: OFF, SYSTICK, TIM2, TIM3, or TIM4")
set_property(CACHE APP_TIMEBASE_SOURCE PROPERTY STRINGS OFF SYSTICK TIM2 TIM3 TIM4)
option(APP_ENABLE_TIMER_US_DELAY "Enable the optional TIM4 microsecond delay service" OFF)
option(APP_ENABLE_ONBOARD_LED "Enable App_BootInit() on-board LED configuration" ON)
option(APP_ENABLE_FLOAT "Enable application float and double dependent code" OFF)
option(APP_ENABLE_DEBUG "Enable application debug code" OFF)

# Normalize the human-readable selector once, then publish the corresponding
# application token so CMake module resolution and C preprocessing consume one
# coherent source decision.
string(TOUPPER "${APP_TIMEBASE_SOURCE}" _app_timebase_source)
if(_app_timebase_source STREQUAL "OFF")
    set(_app_timebase_source_define APP_TIME_SOURCE_NONE)
elseif(_app_timebase_source STREQUAL "SYSTICK")
    set(_app_timebase_source_define APP_TIME_SOURCE_SYSTICK)
elseif(_app_timebase_source STREQUAL "TIM2")
    set(_app_timebase_source_define APP_TIME_SOURCE_TIM2)
elseif(_app_timebase_source STREQUAL "TIM3")
    set(_app_timebase_source_define APP_TIME_SOURCE_TIM3)
elseif(_app_timebase_source STREQUAL "TIM4")
    set(_app_timebase_source_define APP_TIME_SOURCE_TIM4)
else()
    message(FATAL_ERROR "APP_TIMEBASE_SOURCE must be OFF, SYSTICK, TIM2, TIM3, or TIM4.")
endif()

# BSP_TIMER owns TIM4 exclusively as a polling-only microsecond-delay source;
# one firmware cannot simultaneously assign TIM4 to the interrupt timebase.
if(APP_ENABLE_TIMER_US_DELAY AND _app_timebase_source STREQUAL "TIM4")
    message(FATAL_ERROR "APP_TIMEBASE_SOURCE=TIM4 conflicts with APP_ENABLE_TIMER_US_DELAY=ON because BSP_TIMER exclusively reserves TIM4.")
endif()

# RCC is required unconditionally because App_BootInit() establishes the
# system clock. Each source adds only its hardware path: SysTick has no RCC or
# NVIC dependency, while TIM2-TIM4 need Timer plus external NVIC delivery.
# The application always polls the USART Driver directly. Without debug it also
# requests GPIO for its explicit initialization path; debug instead requests
# BSP_USART, whose capability dependency supplies GPIO for the boot transport.
# LED and TIM4 polling delay remain independently selected capabilities.
set(app_driver_modules RCC USART)
if(APP_ENABLE_DEBUG)
    list(APPEND app_driver_modules BSP_USART)
else()
    list(APPEND app_driver_modules GPIO)
endif()
if(APP_ENABLE_ONBOARD_LED)
    list(APPEND app_driver_modules BSP_GPIO)
endif()
if(_app_timebase_source STREQUAL "SYSTICK")
    list(APPEND app_driver_modules SysTick)
elseif(_app_timebase_source MATCHES "^TIM[234]$")
    list(APPEND app_driver_modules Timer NVIC)
endif()
if(APP_ENABLE_TIMER_US_DELAY)
    list(APPEND app_driver_modules BSP_TIMER)
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

# Publish the selected source and normalized optional feature states only to
# this firmware target. Project 11 sources consume the same values used for
# Driver selection, keeping compiled APIs synchronized with linked modules.
target_compile_definitions(${PROJECT_NAME}.elf PRIVATE
    APP_TIMEBASE_SOURCE=${_app_timebase_source_define}
    APP_ENABLE_TIMER_US_DELAY=$<BOOL:${APP_ENABLE_TIMER_US_DELAY}>
    APP_ENABLE_ONBOARD_LED=$<BOOL:${APP_ENABLE_ONBOARD_LED}>
    APP_ENABLE_FLOAT=$<BOOL:${APP_ENABLE_FLOAT}>
    APP_ENABLE_DEBUG=$<BOOL:${APP_ENABLE_DEBUG}>
)

# The shared --specs=nano.specs link policy strips floating-point printf
# support by default. A `%f` conversion is compiled only when independently
# selected float behavior and debug output meet in this project, so only that
# conjunction pulls newlib-nano's formatter in via -u _printf_float.
if(APP_ENABLE_FLOAT AND APP_ENABLE_DEBUG)
    target_link_options(${PROJECT_NAME}.elf PRIVATE -u _printf_float)
endif()
