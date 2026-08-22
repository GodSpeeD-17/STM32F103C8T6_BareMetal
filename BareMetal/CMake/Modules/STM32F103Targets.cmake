include_guard(GLOBAL)

# Firmware target creation is intentionally minimal here: one ELF target plus
# post-build artifact generation and reporting.

function(stm32_add_firmware_target)
    add_executable(${PROJECT_NAME}.elf ${ALL_SOURCE_FILES})

    # Driver include directories are filtered earlier, so by this point the
    # target can receive the final merged include path list directly.
    set(ALL_INCLUDE_DIRS
        ${PROJ_DIR}/Inc
        ${CORE_ROOT}/Inc
        ${DRIVER_ROOT}
        ${SELECTED_DRIVER_INCLUDES}
    )
    target_include_directories(${PROJECT_NAME}.elf PRIVATE ${ALL_INCLUDE_DIRS})

    target_compile_options(${PROJECT_NAME}.elf PRIVATE
        $<$<COMPILE_LANGUAGE:C>:${C_FLAGS}>
        $<$<COMPILE_LANGUAGE:CXX>:${CXX_FLAGS}>
        $<$<COMPILE_LANGUAGE:ASM>:${ASM_FLAGS}>
    )

    target_link_options(${PROJECT_NAME}.elf PRIVATE
        ${LINKER_FLAGS}
    )

    # Some workflows remove the Build directory before relinking. Recreate it
    # here so the map file and other outputs always have a valid destination.
    add_custom_command(TARGET ${PROJECT_NAME}.elf PRE_LINK
        COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD_OUTPUT_DIR}
        COMMENT "Ensuring firmware output directory exists..."
    )

    # Convert the ELF into deployable formats and print the memory summary
    # immediately after a successful link step.
    add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BINARY_FILE}
        COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_COMMAND}
            -DSIZE_TOOL=${CMAKE_SIZE}
            -DELF_FILE=$<TARGET_FILE:${PROJECT_NAME}.elf>
            -DPROJECT_LABEL=${PROJECT_NAME}.elf
            -DFLASH_SIZE_BYTES=${FLASH_SIZE_BYTES}
            -DRAM_SIZE_BYTES=${RAM_SIZE_BYTES}
            -P ${CMAKE_ROOT}/STM32F103MemoryReport.cmake
        COMMENT "Generating binary artifacts and memory report..."
    )
endfunction()
