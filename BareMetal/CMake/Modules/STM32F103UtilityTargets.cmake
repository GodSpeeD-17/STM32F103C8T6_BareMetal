include_guard(GLOBAL)

# Non-firmware helper targets live here: VS Code metadata generation, flashing,
# erase helpers, and repository maintenance shortcuts.

function(stm32_add_vscode_targets)
    # Generate VS Code launch.json for Cortex-Debug / OpenOCD flows.
    add_custom_target(vscode_launch
      COMMAND ${CMAKE_COMMAND} -E make_directory ${VSCODE_DIR}
      COMMAND ${CMAKE_COMMAND} -E echo "{"                                          >  ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "  \\\"version\\\": \\\"0.2.0\\\","          >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "  \\\"configurations\\\": ["                >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "    {"                                      >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"name\\\": \\\"Debug: ${PROJECT_NAME}\\\"," >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"executable\\\": \\\"${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.elf\\\"," >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"request\\\": \\\"launch\\\","     >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"type\\\": \\\"cortex-debug\\\","  >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"servertype\\\": \\\"openocd\\\"," >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"device\\\": \\\"STM32F103C8\\\"," >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"configFiles\\\": ["               >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "        \\\"${CORE_ROOT}/Src/stlink.cfg\\\"," >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "        \\\"${CORE_ROOT}/Src/stm32f1x.cfg\\\""  >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "      ],"                                   >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"svdFile\\\": \\\"${CORE_ROOT}/Src/stm32f103c8t6.svd\\\"," >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"runToEntryPoint\\\": \\\"main\\\", // main.c" >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "    //   \\\"runToEntryPoint\\\": \\\"Reset_Handler\\\", // app_startup.c" >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"preLaunchTask\\\": \\\"Build Project\\\"," >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"postLaunchCommands\\\": ["         >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "        \\\"monitor reset init\\\","         >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "        \\\"load\\\","                       >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "        \\\"monitor reset halt\\\""          >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "      ]"                                    >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "    }"                                      >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "  ]"                                        >> ${VSCODE_DIR}/launch.json
      COMMAND ${CMAKE_COMMAND} -E echo "}"                                          >> ${VSCODE_DIR}/launch.json
      COMMENT "----------------------------------- launch.json -----------------------------------"
    )

    # Tool paths are written separately so local workstation differences can be
    # regenerated from CMake instead of hand-editing JSON files.
    add_custom_target(vscode_settings
      COMMAND ${CMAKE_COMMAND} -E make_directory ${VSCODE_DIR}
      COMMAND ${CMAKE_COMMAND} -E echo "{"                                          >  ${VSCODE_DIR}/settings.json
      COMMAND ${CMAKE_COMMAND} -E echo "  \\\"cortex-debug.gdbPath\\\": \\\"${GDB_PATH_MULTIARCH_PATH}\\\"," >> ${VSCODE_DIR}/settings.json
      COMMAND ${CMAKE_COMMAND} -E echo "  \\\"cortex-debug.openocdPath\\\": \\\"${OPENOCD_PATH}\\\"," >> ${VSCODE_DIR}/settings.json
      COMMAND ${CMAKE_COMMAND} -E echo "  \\\"cortex-debug.stutilPath\\\": \\\"${ST_UTIL_PATH}\\\"," >> ${VSCODE_DIR}/settings.json
      COMMAND ${CMAKE_COMMAND} -E echo "  \\\"cortex-debug.variableUseNaturalFormat\\\": true" >> ${VSCODE_DIR}/settings.json
      COMMAND ${CMAKE_COMMAND} -E echo "}"                                          >> ${VSCODE_DIR}/settings.json
      COMMENT "----------------------------------- settings.json -----------------------------------"
    )

    # Keep VS Code tasks aligned with the same CMake build entrypoints the
    # terminal workflow already uses.
    add_custom_target(vscode_tasks
      COMMAND ${CMAKE_COMMAND} -E make_directory ${VSCODE_DIR}
      COMMAND ${CMAKE_COMMAND} -E echo "{"                                          >  ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "  \\\"version\\\": \\\"2.0.0\\\","          >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "  \\\"tasks\\\": ["                         >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "    {"                                      >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"label\\\": \\\"Build Project\\\"," >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"type\\\": \\\"shell\\\","         >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"command\\\": \\\"cmake\\\","      >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"args\\\": [\\\"--build\\\", \\\"${BUILD_OUTPUT_DIR}\\\"]," >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"group\\\": { \\\"kind\\\": \\\"build\\\", \\\"isDefault\\\": true }," >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"problemMatcher\\\": [\\\"$gcc\\\"]" >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "    },"                                     >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "    {"                                      >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"label\\\": \\\"Clean Project\\\"," >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"type\\\": \\\"shell\\\","         >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"command\\\": \\\"cmake\\\","      >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"args\\\": [\\\"--build\\\", \\\"${BUILD_OUTPUT_DIR}\\\", \\\"--target\\\", \\\"clean_all\\\"]," >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"group\\\": \\\"build\\\","        >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"problemMatcher\\\": [],"          >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"detail\\\": \\\"Clean the build directory\\\"" >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "    }"                                      >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "  ]"                                        >> ${VSCODE_DIR}/tasks.json
      COMMAND ${CMAKE_COMMAND} -E echo "}"                                          >> ${VSCODE_DIR}/tasks.json
      COMMENT "----------------------------------- tasks.json -----------------------------------"
    )

    # IntelliSense settings mirror the active build configuration so headers
    # and MCU defines stay consistent in the editor.
    add_custom_target(vscode_c_cpp_properties
      COMMAND ${CMAKE_COMMAND} -E make_directory ${VSCODE_DIR}
      COMMAND ${CMAKE_COMMAND} -E make_directory "${VSCODE_DIR}"
      COMMAND ${CMAKE_COMMAND} -E echo "{"                                          >  "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "  \\\"configurations\\\": ["                >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "    {"                                      >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"name\\\": \\\"Linux\\\","         >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"includePath\\\": ["               >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "        \\\"${CORE_ROOT}/Inc/**\\\","       >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "        \\\"${DRIVER_ROOT}/**\\\","         >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "        \\\"${PROJ_DIR}/Inc/**\\\""         >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "      ],"                                   >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"defines\\\": [\\\"${MCU_DEFINE}\\\", \\\"${MCU_CPU_DEFINE}\\\"]," >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"compilerPath\\\": \\\"${CMAKE_C_COMPILER}\\\"," >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"cStandard\\\": \\\"${C_STD}\\\"," >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"cppStandard\\\": \\\"${CXX_STD}\\\"," >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "      \\\"intelliSenseMode\\\": \\\"linux-gcc-arm\\\"" >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "    }"                                      >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "  ],"                                       >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "  \\\"version\\\": 4"                       >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMAND ${CMAKE_COMMAND} -E echo "}"                                          >> "${VSCODE_DIR}/c_cpp_properties.json"
      COMMENT "----------------------------------- c_cpp_properties.json -----------------------------------"
    )

    add_custom_target(vscode_files
        DEPENDS
            vscode_launch
            vscode_tasks
            vscode_c_cpp_properties
        COMMENT "----------------------------------- Generating vscode files -----------------------------------"
    )

    add_custom_target(debug
        DEPENDS ${PROJECT_NAME}.elf vscode_files
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "Debug environment ready."
        COMMENT "Setting up debug environment: building project and generating VSCode configs"
    )
endfunction()

function(stm32_add_flash_targets)
    # `debug_flash` is a dry-run helper that prints the resolved flash command
    # without touching hardware.
    add_custom_target(debug_flash
        COMMAND ${CMAKE_COMMAND} -E echo "ST_FLASH: ${ST_FLASH}"
        COMMAND ${CMAKE_COMMAND} -E echo "BINARY_FILE: ${BINARY_FILE}"
        COMMAND ${CMAKE_COMMAND} -E echo "FLASH_ADDRESS: ${FLASH_ADDRESS}"
        COMMAND ${CMAKE_COMMAND} -E echo "Full command: ${ST_FLASH} --reset write ${BINARY_FILE} ${FLASH_ADDRESS}"
    )

    # `flash` and `erase_flash` delegate to helper scripts so they can retry
    # with connect-under-reset when the target cannot be attached normally.
    add_custom_target(flash
        DEPENDS ${PROJECT_NAME}.elf
        COMMAND ${CMAKE_COMMAND}
            -DST_FLASH=${ST_FLASH}
            -DBINARY_FILE=${BINARY_FILE}
            -DFLASH_ADDRESS=${FLASH_ADDRESS}
            -P ${CMAKE_ROOT}/STM32F103Flash.cmake
        COMMENT "Flashing ${PROJECT_NAME}.bin to STM32 via ST-Link v2 (SWD) with automatic recovery"
    )

    add_custom_target(flash_uart
        DEPENDS ${PROJECT_NAME}.elf
        COMMAND sudo ${ST_UART_FLASH} -w ${BINARY_FILE} -v -g 0x0 ${ST_UART_FLASH_PORT}
        COMMENT "Flashing ${PROJECT_NAME}.bin to STM32 via UART bootloader"
    )

    add_custom_target(info
        COMMAND ${ST_INFO} --probe
        COMMENT "Show connected ST-Link probe information"
    )

    add_custom_target(erase_flash
        COMMAND ${CMAKE_COMMAND}
            -DST_FLASH=${ST_FLASH}
            -P ${CMAKE_ROOT}/STM32F103EraseFlash.cmake
        COMMENT "Erasing entire STM32 flash memory via ST-Link with automatic recovery"
    )

    add_custom_target(erase_flash_uart
        COMMAND sudo ${ST_UART_FLASH} -o ${ST_UART_FLASH_PORT}
        COMMENT "Erasing STM32 flash memory via UART bootloader"
    )

endfunction()

function(stm32_add_maintenance_targets)
    # `clean_all` intentionally removes both generated firmware artifacts and
    # generated editor metadata to bring the project back to a clean state.
    add_custom_target(clean_all
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${BUILD_OUTPUT_DIR}
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${VSCODE_DIR}
        COMMENT "Completely cleaning project: build artifacts and VSCode configurations"
    )

    # Repository-wide sync helpers are convenience targets for template-style
    # files that are intentionally kept identical across multiple projects.
    function(add_replace_target TARGET_NAME FILE_PATH IN_PROJECT_DIR)
        add_custom_target(${TARGET_NAME}
            COMMAND ${CMAKE_COMMAND} -E echo "Replacing ${FILE_PATH} in all projects"
            COMMAND find ${REPO_ROOT}/Projects -name "${FILE_PATH}" -not -path "${IN_PROJECT_DIR}/${FILE_PATH}" -print0 | xargs -0 -I {} cp "${IN_PROJECT_DIR}/${FILE_PATH}" "{}"
        )
    endfunction()

    add_replace_target(replace_main_h "main.h" "${PROJ_DIR}/Inc")
    add_replace_target(replace_app_startup_h "app_startup.h" "${PROJ_DIR}/Inc")
    add_replace_target(replace_systick_h "systick.h" "${PROJ_DIR}/Inc")
    add_replace_target(replace_systick_c "systick.c" "${PROJ_DIR}/Src")
    add_replace_target(replace_app_startup_c "app_startup.c" "${PROJ_DIR}/Src")
    add_replace_target(replace_cmake "CMakeLists.txt" "${PROJ_DIR}")
endfunction()
