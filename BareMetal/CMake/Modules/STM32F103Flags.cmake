include_guard(GLOBAL)

# This module owns target-scoped MCU definitions, language flags, and final
# linker policy. Tool selection belongs to the toolchain file; applications and
# Driver components consume the shared stm32_build_options interface target.

function(stm32_configure_build_flags)
    # Publish device metadata for diagnostics, generated tooling, and memory
    # reporting without making individual projects repeat hardware constants.
    set(MCU STM32F103C8T6 PARENT_SCOPE)
    set(MCU_DEFINE STM32F103C8T6__ PARENT_SCOPE)
    set(MCU_CPU_DEFINE CORTEX_M3__ PARENT_SCOPE)
    set(MCU_CPU cortex-m3 PARENT_SCOPE)
    set(C_STD gnu11 PARENT_SCOPE)
    set(CXX_STD c++17 PARENT_SCOPE)
    set(FLASH_SIZE_BYTES 65536 PARENT_SCOPE)
    set(RAM_SIZE_BYTES 20480 PARENT_SCOPE)

    # Architecture flags are shared by every compiled language. Library and
    # linker-only options deliberately remain outside compilation commands.
    set(architecture_flags
        -mcpu=cortex-m3
        -mthumb
        -mfloat-abi=soft
    )

    set(common_compile_flags
        ${architecture_flags}
        -O${OPTIMIZATION_LEVEL}
        -Wall
        -Wextra
        -Wpedantic
        -fstack-usage
        -fdata-sections
        -ffunction-sections
        -g
        -gdwarf-2
    )

    if(SAVE_TEMPS)
        list(APPEND common_compile_flags -save-temps)
    endif()

    set(c_compile_flags
        ${common_compile_flags}
        -std=gnu11
        -Wstrict-prototypes
        -Wmissing-prototypes
    )

    set(cxx_compile_flags
        ${common_compile_flags}
        -std=c++17
        -fno-exceptions
        -fno-rtti
        -fno-use-cxa-atexit
        -fno-threadsafe-statics
        -Wold-style-cast
        -Woverloaded-virtual
    )

    set(asm_compile_flags
        ${architecture_flags}
        -x
        assembler-with-cpp
        -Wa,--warn
    )

    # An interface target gives project, Core, and Driver sources one source of
    # truth for compile requirements without relying on directory-wide flags.
    add_library(stm32_build_options INTERFACE)
    add_library(stm32::build_options ALIAS stm32_build_options)
    target_compile_definitions(stm32_build_options INTERFACE
        STM32F103C8T6__
        CORTEX_M3__
    )
    target_compile_options(stm32_build_options INTERFACE
        $<$<COMPILE_LANGUAGE:C>:${c_compile_flags}>
        $<$<COMPILE_LANGUAGE:CXX>:${cxx_compile_flags}>
        $<$<COMPILE_LANGUAGE:ASM>:${asm_compile_flags}>
    )

    # Link options remain application-owned because only the final ELF target
    # owns the linker script, memory map, and section-garbage collection.
    set(linker_flags
        ${architecture_flags}
        -T${LINKER_FILE}
        -Wl,-Map=${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.map
        --specs=nano.specs
        -Wl,--gc-sections
        -Wl,--cref
        -static
    )
    set(link_libraries
        c
        m
        stdc++
        supc++
    )

    set(LINKER_FLAGS "${linker_flags}" PARENT_SCOPE)
    set(STM32_LINK_LIBRARIES "${link_libraries}" PARENT_SCOPE)
endfunction()
