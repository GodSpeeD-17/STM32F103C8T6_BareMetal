include_guard(GLOBAL)

function(stm32_validate_project_inputs)
    foreach(required_var
        PROJ_DIR
        REPO_ROOT
        BAREMETAL_ROOT
        CMAKE_ROOT
        CORE_ROOT
        DRIVER_ROOT
        LINKER_FILE
        TOOLCHAIN_PATH
        TOOLCHAIN_PREFIX
        BUILD_OUTPUT_DIR
    )
        if(NOT DEFINED ${required_var} OR "${${required_var}}" STREQUAL "")
            message(FATAL_ERROR "${required_var} must be defined before including CMake_Template.cmake")
        endif()
    endforeach()
endfunction()

function(stm32_apply_project_defaults)
    set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}-objcopy PARENT_SCOPE)
    set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}-objdump PARENT_SCOPE)
    set(CMAKE_NM ${TOOLCHAIN_PREFIX}-nm PARENT_SCOPE)
    set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}-size PARENT_SCOPE)

    if(NOT DEFINED DRIVER_MODULES OR "${DRIVER_MODULES}" STREQUAL "")
        message(FATAL_ERROR "DRIVER_MODULES not set! Please set it before including this template")
    endif()

    if(NOT DEFINED OPTIMIZATION_LEVEL)
        message(WARNING "OPTIMIZATION_LEVEL not set! Assuming -O1")
        set(OPTIMIZATION_LEVEL 1 PARENT_SCOPE)
    endif()

    if(NOT DEFINED FLASH_ADDRESS)
        message(WARNING "FLASH_ADDRESS not set! Assuming 0x08000000")
        set(FLASH_ADDRESS 0x08000000 PARENT_SCOPE)
    endif()

    if(NOT DEFINED DRIVER_MODULE_TREE)
        message(WARNING "DRIVER_MODULE_TREE not set! Assuming SHOW_FILENAME_ONLY")
        set(DRIVER_MODULE_TREE SHOW_FILENAME_ONLY PARENT_SCOPE)
    endif()

    if(NOT DEFINED ST_UART_FLASH_PORT)
        message(WARNING "ST_UART_FLASH_PORT not set! Assuming /dev/ttyUSB0")
        set(ST_UART_FLASH_PORT "/dev/ttyUSB0" PARENT_SCOPE)
    endif()

    if(NOT DEFINED SAVE_TEMPS)
        set(SAVE_TEMPS OFF PARENT_SCOPE)
    endif()
endfunction()
