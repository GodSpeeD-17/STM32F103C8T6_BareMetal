include_guard(GLOBAL)

function(stm32_configure_build_flags)
    set(MCU STM32F103C8T6 PARENT_SCOPE)
    set(MCU_DEFINE STM32F103C8T6__ PARENT_SCOPE)
    set(MCU_CPU_DEFINE CORTEX_M3__ PARENT_SCOPE)
    set(MCU_CPU cortex-m3 PARENT_SCOPE)
    set(C_STD gnu11 PARENT_SCOPE)
    set(CXX_STD c++17 PARENT_SCOPE)
    set(FLASH_SIZE_BYTES 65536 PARENT_SCOPE)
    set(RAM_SIZE_BYTES 20480 PARENT_SCOPE)

    set(DEFAULT_FLAGS
        -mcpu=cortex-m3
        -mthumb
        -mfloat-abi=soft
        -lc -lm -lstdc++ -lsupc++
        --specs=nano.specs
        --specs=nosys.specs
        -MMD -MP
    )

    if(SAVE_TEMPS)
        list(APPEND DEFAULT_FLAGS -save-temps)
    endif()

    set(COMMON_FLAGS
        ${DEFAULT_FLAGS}
        -O${OPTIMIZATION_LEVEL}
        -Wall
        -Wextra
        -Wpedantic
        -fstack-usage
        -fdata-sections
        -ffunction-sections
        -DSTM32F103C8T6__
        -DCORTEX_M3__
        -g -gdwarf-2
    )

    set(C_FLAGS
        ${COMMON_FLAGS}
        -std=gnu11
        -Wstrict-prototypes
        -Wmissing-prototypes
    )

    set(CXX_FLAGS
        ${COMMON_FLAGS}
        -std=c++17
        -fno-exceptions
        -fno-rtti
        -fno-use-cxa-atexit
        -fno-threadsafe-statics
        -Wold-style-cast
        -Woverloaded-virtual
    )

    set(ASM_FLAGS
        ${DEFAULT_FLAGS}
        -x assembler-with-cpp
        -Wa,--warn
    )

    set(LINKER_FLAGS
        -mcpu=cortex-m3
        -mthumb
        -mfloat-abi=soft
        -T${LINKER_FILE}
        -Wl,-Map=${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.map
        -lc -lm -lstdc++ -lsupc++
        --specs=nano.specs
        -Wl,--gc-sections
        -Wl,--cref
        -static
    )

    set(DEFAULT_FLAGS "${DEFAULT_FLAGS}" PARENT_SCOPE)
    set(COMMON_FLAGS "${COMMON_FLAGS}" PARENT_SCOPE)
    set(C_FLAGS "${C_FLAGS}" PARENT_SCOPE)
    set(CXX_FLAGS "${CXX_FLAGS}" PARENT_SCOPE)
    set(ASM_FLAGS "${ASM_FLAGS}" PARENT_SCOPE)
    set(LINKER_FLAGS "${LINKER_FLAGS}" PARENT_SCOPE)
endfunction()
