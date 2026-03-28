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

# Shared toolchain bootstrap.
stm32f103_setup_toolchain()
project(02_PB_Poll VERSION 1.0.0 LANGUAGES C CXX ASM)

# Project-specific configuration stays here.
stm32f103_configure_project(
    DRIVER_MODULE_TREE SHOW_FILENAME_ONLY
    DRIVER_MODULES
        RCC
        GPIO
        NVIC
        Timer
    OPTIMIZATION_LEVEL 1
    FLASH_ADDRESS 0x08000000
)
