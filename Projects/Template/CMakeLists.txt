cmake_minimum_required(VERSION 3.28)

set(_stm32_repo_search_dir "${CMAKE_CURRENT_LIST_DIR}")
while(NOT EXISTS "${_stm32_repo_search_dir}/BareMetal/CMake/STM32F103Project.cmake")
    get_filename_component(_stm32_repo_parent "${_stm32_repo_search_dir}" DIRECTORY)
    if(_stm32_repo_parent STREQUAL _stm32_repo_search_dir)
        message(FATAL_ERROR "Unable to locate BareMetal/CMake/STM32F103Project.cmake from ${CMAKE_CURRENT_LIST_DIR}")
    endif()
    set(_stm32_repo_search_dir "${_stm32_repo_parent}")
endwhile()

include("${_stm32_repo_search_dir}/BareMetal/CMake/STM32F103Project.cmake")

stm32f103_setup_toolchain()

get_filename_component(_stm32_project_name "${CMAKE_CURRENT_LIST_DIR}" NAME)
project(${_stm32_project_name} VERSION 1.0.0 LANGUAGES C ASM)

# Application feature selection. Each enabled hardware-backed service adds
# only its owning Driver module and the matching application API.
option(APP_ENABLE_SYSTICK_TIMEBASE "Enable the SysTick millisecond timebase" ON)
option(APP_ENABLE_TIMER_US_DELAY "Enable the optional TIM4 microsecond delay service" OFF)

set(app_driver_modules RCC)
if(APP_ENABLE_SYSTICK_TIMEBASE)
    list(APPEND app_driver_modules SysTick)
endif()
if(APP_ENABLE_TIMER_US_DELAY)
    list(APPEND app_driver_modules Timer)
endif()

stm32f103_configure_project(
    BUILD_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/Artifacts"
    DRIVER_MODULE_TREE SHOW_FILENAME_ONLY
    DRIVER_MODULES
        ${app_driver_modules}
    OPTIMIZATION_LEVEL 1
    FLASH_ADDRESS 0x08000000
)

target_compile_definitions(${PROJECT_NAME}.elf PRIVATE
    APP_ENABLE_SYSTICK_TIMEBASE=$<BOOL:${APP_ENABLE_SYSTICK_TIMEBASE}>
    APP_ENABLE_TIMER_US_DELAY=$<BOOL:${APP_ENABLE_TIMER_US_DELAY}>
)
