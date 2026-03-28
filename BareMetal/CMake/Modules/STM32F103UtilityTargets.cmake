include_guard(GLOBAL)

function(stm32_add_vscode_targets)
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
      COMMAND ${CMAKE_COMMAND} -E echo "    //   \\\"runToEntryPoint\\\": \\\"Reset_Handler\\\", // startup.c" >> ${VSCODE_DIR}/launch.json
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
    add_custom_target(debug_flash
        COMMAND ${CMAKE_COMMAND} -E echo "ST_FLASH: ${ST_FLASH}"
        COMMAND ${CMAKE_COMMAND} -E echo "BINARY_FILE: ${BINARY_FILE}"
        COMMAND ${CMAKE_COMMAND} -E echo "FLASH_ADDRESS: ${FLASH_ADDRESS}"
        COMMAND ${CMAKE_COMMAND} -E echo "Full command: ${ST_FLASH} --reset write ${BINARY_FILE} ${FLASH_ADDRESS}"
    )

    add_custom_target(flash
        DEPENDS ${PROJECT_NAME}.elf
        COMMAND ${ST_FLASH} --reset write ${BINARY_FILE} ${FLASH_ADDRESS}
        COMMENT "Flashing ${PROJECT_NAME}.bin to STM32 via ST-Link v2 (SWD)"
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
        COMMAND ${ST_FLASH} erase
        COMMENT "Erasing entire STM32 flash memory via ST-Link"
    )

    add_custom_target(erase_flash_uart
        COMMAND sudo ${ST_UART_FLASH} -o ${ST_UART_FLASH_PORT}
        COMMENT "Erasing STM32 flash memory via UART bootloader"
    )

endfunction()

function(stm32_add_maintenance_targets)
    add_custom_target(clean_all
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${BUILD_OUTPUT_DIR}
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${VSCODE_DIR}
        COMMENT "Completely cleaning project: build artifacts and VSCode configurations"
    )

    function(add_replace_target TARGET_NAME FILE_PATH IN_PROJECT_DIR)
        add_custom_target(${TARGET_NAME}
            COMMAND ${CMAKE_COMMAND} -E echo "Replacing ${FILE_PATH} in all projects"
            COMMAND find ${REPO_ROOT}/Projects -name "${FILE_PATH}" -not -path "${IN_PROJECT_DIR}/${FILE_PATH}" -print0 | xargs -0 -I {} cp "${IN_PROJECT_DIR}/${FILE_PATH}" "{}"
        )
    endfunction()

    add_replace_target(replace_main_h "main.h" "${PROJ_DIR}/Inc")
    add_replace_target(replace_systick_h "systick.h" "${PROJ_DIR}/Inc")
    add_replace_target(replace_systick_c "systick.c" "${PROJ_DIR}/Src")
    add_replace_target(replace_startup_c "startup.c" "${PROJ_DIR}/Src")
    add_replace_target(replace_cmake "CMakeLists.txt" "${PROJ_DIR}")
endfunction()
