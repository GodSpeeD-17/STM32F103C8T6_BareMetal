# ---------------------- Minimum CMake Version ----------------------
cmake_minimum_required(VERSION 3.28)

# ---------------------- Paths ----------------------
get_filename_component(PROJ_DIR "${CMAKE_SOURCE_DIR}" ABSOLUTE)
get_filename_component(REPO_ROOT "${PROJ_DIR}/../../../" ABSOLUTE) # Adjust this as per project structure
set(DRIVER_ROOT ${REPO_ROOT}/BareMetal/Driver)
set(CORE_ROOT ${REPO_ROOT}/BareMetal/Core)
set(BUILD_OUTPUT_DIR ${PROJ_DIR}/Build)

# ---------------------- Cross Compilation ----------------------
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(TOOLCHAIN_PATH /opt/arm-gnu-toolchain-14.3/bin)

# ---------------------- Toolchain ----------------------
set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/${CMAKE_SYSTEM_PROCESSOR}-none-eabi-gcc)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PATH}/${CMAKE_SYSTEM_PROCESSOR}-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/${CMAKE_SYSTEM_PROCESSOR}-none-eabi-g++)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PATH}/${CMAKE_SYSTEM_PROCESSOR}-none-eabi-objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PATH}/${CMAKE_SYSTEM_PROCESSOR}-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(ST_FLASH st-flash)
set(ST_FLASH_PATH /usr/bin/st-flash)
set(GDB_PATH_MULTIARCH_PATH "/usr/bin/gdb-multiarch")
set(OPENOCD openocd)
set(OPENOCD_PATH /usr/bin/openocd)
set(ST_INFO st-info)
set(ST_UTIL_PATH /usr/bin/st-util)
set(ST_UART_FLASH stm32flash)
set(ST_UART_FLASH_PORT /dev/ttyUSB0)

# =============================================================================
# Project
# =============================================================================
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES C CXX ASM)

# =============================================================================
# MCU Configuration
# =============================================================================
set(MCU_DEFINE STM32F103C8T6__)
set(MCU_CPU_DEFINE CORTEX_M3__)
set(MCU_CPU cortex-m3)
set(FLASH_ADDRESS 0x08000000)

# =============================================================================
# Language Standards
# =============================================================================
set(C_STD gnu11)
set(CXX_STD c++17)

# =============================================================================
# Optimization & Debugging
# =============================================================================
set(OPTIMIZATION_LEVEL 0)  # 0: Debug, 1: Balanced, 2: Performance, 3: Size
set(DEBUG_LEVEL 2)         # 0: None, 1: Minimal, 2: Standard, 3: Maximum

# =============================================================================
# Base Compiler Flags
# =============================================================================
set(DEFAULT_FLAGS 
    -mcpu=${MCU_CPU}
    -mthumb
    -mfloat-abi=soft
    --specs=nano.specs    # Use reduced libc
    --specs=nosys.specs   # No system calls
    -lc -lm
    -MMD -MP              # Dependency generation
    -save-temps           # Keep intermediate files
)

# =============================================================================
# Common Flags (C & C++)
# =============================================================================
set(COMMON_FLAGS ${DEFAULT_FLAGS}
    -O${OPTIMIZATION_LEVEL}
    -Wall                 # All standard warnings
    -Wextra               # Extra warnings
    -Wpedantic            # Strict ISO compliance
    -fstack-usage         # Generate stack usage info
    -fdata-sections       # Enable data section garbage collection
    -ffunction-sections   # Enable function section garbage collection
    -D${MCU_DEFINE}       # MCU-specific define
    -D${MCU_CPU_DEFINE}   # CPU architecture define
    -g -gdwarf-2          # Debug info with DWARF2 format
)

# =============================================================================
# Language-Specific Flags
# =============================================================================

# C specific flags
set(C_FLAGS ${COMMON_FLAGS}
    -std=${C_STD}
    -Wstrict-prototypes   # Warn about non-ANSI function prototypes
    -Wmissing-prototypes  # Warn about missing function prototypes
)

# C++ specific flags  
set(CXX_FLAGS 
	${COMMON_FLAGS}
    -std=${CXX_STD}
    -fno-exceptions       # Disable exception handling
    -fno-rtti             # Disable RTTI
    -fno-use-cxa-atexit   # Use atexit() instead of __cxa_atexit
    -fno-threadsafe-statics # Disable thread-safe static initialization
    -Wold-style-cast      # Warn about C-style casts in C++
    -Woverloaded-virtual  # Warn about overloaded virtual functions
)

# Assembly-specific flags
set(ASM_FLAGS 
	${DEFAULT_FLAGS}
    -x assembler-with-cpp # Preprocess assembly files
    -Wa,--warn            # Enable assembler warnings
)


# set(MCU_DEFINE STM32F103C8T6__)
# set(MCU_CPU_DEFINE CORTEX_M3__)
# set(MCU_CPU cortex-m3)
# set(C_STD gnu11)
# set(CXX_STD c++17)
# set(OPTIMIZATION_LEVEL 0)
# set(FLASH_ADDRESS 0x08000000)
# set (DEFAULT_FLAGS -mcpu=${MCU_CPU} -mthumb -mfloat-abi=soft --specs=nano.specs -lc -lm -MMD -MP -save-temps)
# set(COMMON_FLAGS ${DEFAULT_FLAGS} -O${OPTIMIZATION_LEVEL} -Wall -fstack-usage -fdata-sections -ffunction-sections -D${MCU_DEFINE} -D${MCU_CPU_DEFINE} -g -gdwarf-2 )

# # C specific flags
# set(C_FLAGS ${COMMON_FLAGS} -std=${C_STD})
# # C++ specific flags
# set(CXX_FLAGS ${COMMON_FLAGS} -std=${CXX_STD} -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics)
# # Assembly-specific flags
# set(ASM_FLAGS ${DEFAULT_FLAGS} -x assembler-with-cpp)

# ---------------------- Paths ----------------------
set(LINKER_FILE ${CORE_ROOT}/Src/stm32f103c8t6.ld) # Replace this for customer linker file
set(VSCODE_DIR ${PROJ_DIR}/.vscode)
set(BINARY_FILE ${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.bin)
set(HEX_FILE ${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.hex)

# ---------------------- Output directories ----------------------
file(MAKE_DIRECTORY ${BUILD_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})

# ---------------------- Listing Function ----------------------
set(SELECTED_DRIVER_SOURCES "")
set(SELECTED_DRIVER_INCLUDES "")

# Function to add a driver module
function(add_driver_module)
    # Parse arguments - first argument can be SHOW_FULL_PATH or SHOW_FILENAME_ONLY
    set(show_full_path OFF)
    set(module_names "")
    
    foreach(arg IN LISTS ARGN)
        if(arg STREQUAL "SHOW_FULL_PATH")
            set(show_full_path ON)
        elseif(arg STREQUAL "SHOW_FILENAME_ONLY")
            set(show_full_path OFF)
        else()
            list(APPEND module_names ${arg})
        endif()
    endforeach()

    # Iterate over each module name
    foreach(module_name IN LISTS module_names)
        # Construct module path
        set(DRIVER_MODULE_DIR ${DRIVER_ROOT}/${module_name})
        # Check if directory exists
        if(EXISTS ${DRIVER_MODULE_DIR})
            # Collect sources & append to list
            file(GLOB MODULE_SOURCES ${DRIVER_MODULE_DIR}/Src/*.c)
            list(APPEND SELECTED_DRIVER_SOURCES ${MODULE_SOURCES})

            # Collect includes & append to list
            if(EXISTS ${DRIVER_MODULE_DIR}/Inc)
                list(APPEND SELECTED_DRIVER_INCLUDES ${DRIVER_MODULE_DIR}/Inc)
            endif()

            # Push lists to parent scope
            set(SELECTED_DRIVER_SOURCES "${SELECTED_DRIVER_SOURCES}" PARENT_SCOPE)
            set(SELECTED_DRIVER_INCLUDES "${SELECTED_DRIVER_INCLUDES}" PARENT_SCOPE)

            # ------------------------ Pretty print tree ------------------------
            message(STATUS "-- ${module_name}")

            # Header File Tree
            if(EXISTS ${DRIVER_MODULE_DIR}/Inc)
                message(STATUS "   |-- Inc")
                file(GLOB MODULE_HEADERS ${DRIVER_MODULE_DIR}/Inc/*.h)
                foreach(hdr IN LISTS MODULE_HEADERS)
                    if(show_full_path)
                        message(STATUS "   |    |-- ${hdr}")
                    else()
                        get_filename_component(filename ${hdr} NAME)
                        message(STATUS "   |    |-- ${filename}")
                    endif()
                endforeach()
                message(STATUS "   |")
            endif()
            
            # Source File Tree
            if(EXISTS ${DRIVER_MODULE_DIR}/Src)
                message(STATUS "   |-- Src")
                file(GLOB MODULE_SOURCES ${DRIVER_MODULE_DIR}/Src/*.c)
                foreach(src IN LISTS MODULE_SOURCES)
                    if(show_full_path)
                        message(STATUS "        |-- ${src}")
                    else()
                        get_filename_component(filename ${src} NAME)
                        message(STATUS "        |-- ${filename}")
                    endif()
                endforeach()
            endif()
        else()
            message(WARNING "Driver module ${module_name} not found at ${DRIVER_MODULE_DIR}")
        endif()
    endforeach()
endfunction()

# ---------------------- Sources ----------------------
# Project Source Files
file(GLOB_RECURSE PROJECT_SOURCES "${PROJ_DIR}/Src/*.c")
# Core Source Files (if any)
file(GLOB_RECURSE CORE_SOURCES "${CORE_ROOT}/Src/*.c")

# ----------------------------------- Add driver modules -----------------------------------
# First Argument Option: SHOW_FULL_PATH / SHOW_FILENAME_ONLY
add_driver_module(SHOW_FILENAME_ONLY
	GPIO
	RCC
	Timer
	DMA
)

set(
	ALL_SOURCE_FILES
	${PROJECT_SOURCES}
	${SELECTED_DRIVER_SOURCES}
	${CORE_SOURCES}
)

# ---------------------- Executable ----------------------
add_executable(
	${PROJECT_NAME}.elf
	${ALL_SOURCE_FILES}
)

# ---------------------- Include Dirs ----------------------
set(ALL_INCLUDE_DIRS
	${CORE_ROOT}/Inc
	${DRIVER_ROOT}
	${SELECTED_DRIVER_INCLUDES}
	${PROJ_DIR}/Inc
)

target_include_directories(${PROJECT_NAME}.elf PRIVATE ${ALL_INCLUDE_DIRS})
# ---------------------- Flags ----------------------

target_compile_options(${PROJECT_NAME}.elf PRIVATE
	$<$<COMPILE_LANGUAGE:C>:${C_FLAGS}>
	$<$<COMPILE_LANGUAGE:CXX>:${CXX_FLAGS}>
	$<$<COMPILE_LANGUAGE:ASM>:${ASM_FLAGS}>
)

# Enhanced linker options
target_link_options(${PROJECT_NAME}.elf PRIVATE
	-mcpu=${MCU_CPU} -mthumb -mfloat-abi=soft -T${LINKER_FILE}
	-lc -lm -Wl,-Map=${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.map
	-Wl,--gc-sections -Wl,--print-memory-usage -Wl,--stats -Wl,--cref
	-static -nostartfiles -nodefaultlibs -nostdlib
)

# ---------------------- Size Command ----------------------
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BINARY_FILE}
	COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
	COMMAND ${CMAKE_SIZE} --format=berkeley ${PROJECT_NAME}.elf
	COMMENT "Size of sections (.text, .data, .bss)"
)

# ---------------------- VSCode Configuration Generation ----------------------
# This section auto-generates VSCode configuration files (launch.json,
# settings.json, tasks.json, and c_cpp_properties.json) from CMake.
# Each file has its own custom target, and a master target `vscode_files`
# depends on all of them.-

# -----------------------------------------------------------------------------
# Helper function: create a generator script
# -----------------------------------------------------------------------------
# For each VSCode file, we generate a small .cmake script in the build dir.
# That script is later executed by a custom target to actually write the file.
# -----------------------------------------------------------------------------
function(create_vscode_script name content)
	set(script "${CMAKE_CURRENT_BINARY_DIR}/gen_${name}.cmake")
	file(WRITE ${script} "${content}")
endfunction()

# -----------------------------------------------------------------------------
# Generator script: launch.json
# -----------------------------------------------------------------------------
# - Configures Cortex-Debug to run with OpenOCD for STM32F103C8T6
# - Points to the .elf binary
# - Includes SVD file for peripheral registers
# - By default runs to 'main', but 'Reset_Handler' is provided as an option
# -----------------------------------------------------------------------------
create_vscode_script(launch_json "
file(WRITE ${VSCODE_DIR}/launch.json \"{
  \\\"version\\\": \\\"0.2.0\\\",
  \\\"configurations\\\": [
	{
	  \\\"name\\\": \\\"Debug: ${PROJECT_NAME}\\\",
	  \\\"executable\\\": \\\"${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.elf\\\",
	  \\\"request\\\": \\\"launch\\\",
	  \\\"type\\\": \\\"cortex-debug\\\",
	  \\\"servertype\\\": \\\"openocd\\\",
	  \\\"device\\\": \\\"STM32F103C8\\\",
	  \\\"configFiles\\\": [
		\\\"${CORE_ROOT}/Src/stlink.cfg\\\",
		\\\"${CORE_ROOT}/Src/stm32f1x.cfg\\\"
	  ],
	  \\\"svdFile\\\": \\\"${CORE_ROOT}/Src/stm32f103c8t6.svd\\\",
	  \\\"runToEntryPoint\\\": \\\"main\\\", // Entry point is main
	  // \\\"runToEntryPoint\\\": \\\"Reset_Handler\\\", // Entry point is Reset_Handler
	  \\\"preLaunchTask\\\": \\\"Build Project\\\"
	}
  ]
}\")
")

# -----------------------------------------------------------------------------
# Generator script: settings.json
# -----------------------------------------------------------------------------
# - Defines paths for gdb-multiarch, openocd, and st-util
# - Controls variable formatting in Cortex-Debug
# -----------------------------------------------------------------------------
create_vscode_script(settings_json "
file(WRITE ${VSCODE_DIR}/settings.json \"{
  \\\"cortex-debug.gdbPath\\\": \\\"${GDB_PATH_MULTIARCH_PATH}\\\",
  \\\"cortex-debug.openocdPath\\\": \\\"${OPENOCD_PATH}\\\",
  \\\"cortex-debug.stutilPath\\\": \\\"${ST_UTIL_PATH}\\\",
  \\\"cortex-debug.variableUseNaturalFormat\\\": false
}\")
")

# -----------------------------------------------------------------------------
# Generator script: tasks.json
# -----------------------------------------------------------------------------
# - Defines build and clean tasks using CMake
# - Integrates with VSCode's build system (`Ctrl+Shift+B`)
# -----------------------------------------------------------------------------
create_vscode_script(tasks_json "
file(WRITE ${VSCODE_DIR}/tasks.json \"{
  \\\"version\\\": \\\"2.0.0\\\",
  \\\"tasks\\\": [
	{
	  \\\"label\\\": \\\"Build Project\\\",
	  \\\"type\\\": \\\"shell\\\",
	  \\\"command\\\": \\\"cmake\\\",
	  \\\"args\\\": [\\\"--build\\\", \\\"${BUILD_OUTPUT_DIR}\\\"],
	  \\\"group\\\": { \\\"kind\\\": \\\"build\\\", \\\"isDefault\\\": true },
	  \\\"problemMatcher\\\": [\\\"\\$gcc\\\"],
	  \\\"detail\\\": \\\"Build the current project using CMake\\\"
	},
	{
	  \\\"label\\\": \\\"Clean Project\\\",
	  \\\"type\\\": \\\"shell\\\",
	  \\\"command\\\": \\\"cmake\\\",
	  \\\"args\\\": [\\\"--build\\\", \\\"${BUILD_OUTPUT_DIR}\\\", \\\"--target\\\", \\\"clean_all\\\"],
	  \\\"group\\\": \\\"build\\\",
	  \\\"problemMatcher\\\": [],
	  \\\"detail\\\": \\\"Clean the build directory\\\"
	}
  ]
}\")
")

# -----------------------------------------------------------------------------
# Generator script: c_cpp_properties.json
# -----------------------------------------------------------------------------
# - Configures IntelliSense for STM32 project
# - Defines include paths, compiler, and standards
# -----------------------------------------------------------------------------
create_vscode_script(cpp_properties_json "
file(WRITE ${VSCODE_DIR}/c_cpp_properties.json \"{
  \\\"configurations\\\": [
	{
	  \\\"name\\\": \\\"Linux\\\",
	  \\\"includePath\\\": [
		\\\"${CORE_ROOT}/**\\\",
		\\\"${DRIVER_ROOT}/**\\\",
		\\\"${PROJ_DIR}/**\\\",
		\\\"${ALL_INCLUDE_DIRS}\\\",
	  ],
	  \\\"defines\\\": [\\\"STM32F103C8T6__\\\", \\\"CORTEX_M3__\\\"],
	  \\\"compilerPath\\\": \\\"${CMAKE_C_COMPILER}\\\",
	  \\\"cStandard\\\": \\\"${C_STD}\\\",
	  \\\"cppStandard\\\": \\\"${CXX_STD}\\\",
	  \\\"intelliSenseMode\\\": \\\"linux-gcc-arm\\\"
	}
  ],
  \\\"version\\\": 4
}\")
")

# -----------------------------------------------------------------------------
# Per-file custom targets
# -----------------------------------------------------------------------------
# Each target calls its respective generator script.
# You can run them individually (e.g. `make launch_json`) or all together.
# -----------------------------------------------------------------------------
add_custom_target(launch_json
	COMMAND ${CMAKE_COMMAND} -E make_directory ${VSCODE_DIR}
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/gen_launch_json.cmake
	COMMENT "Generating launch.json"
)

add_custom_target(settings_json
	COMMAND ${CMAKE_COMMAND} -E make_directory ${VSCODE_DIR}
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/gen_settings_json.cmake
	COMMENT "Generating settings.json"
)

add_custom_target(tasks_json
	COMMAND ${CMAKE_COMMAND} -E make_directory ${VSCODE_DIR}
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/gen_tasks_json.cmake
	COMMENT "Generating tasks.json"
)

add_custom_target(c_cpp_properties_json
	COMMAND ${CMAKE_COMMAND} -E make_directory ${VSCODE_DIR}
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/gen_cpp_properties_json.cmake
	COMMENT "Generating c_cpp_properties.json"
)

# -----------------------------------------------------------------------------
# Master target
# -----------------------------------------------------------------------------
# The `vscode_files` target depends on all of the above.
# Running `make vscode_files` regenerates *all* VSCode configuration files.
# -----------------------------------------------------------------------------
add_custom_target(vscode_files
	DEPENDS 
	launch_json 
	settings_json 
	tasks_json 
	c_cpp_properties_json
)

# -----------------------------------------------------------------------------
# Debug target
# -----------------------------------------------------------------------------
add_custom_target(debug
	DEPENDS ${PROJECT_NAME}.elf
	DEPENDS vscode_files
	COMMAND ${CMAKE_COMMAND} -E echo "***********************************************************************"
	COMMAND ${CMAKE_COMMAND} -E echo "Debug Configurations Ready!"
	COMMAND ${CMAKE_COMMAND} -E echo "***********************************************************************"
	COMMENT "Preparing debug environment"
)

# ---------------------- Custom Targets ----------------------
# -----------------------------------------------------------------------------
# Flash target (ST-Linkv2 st-flash)
# -----------------------------------------------------------------------------
add_custom_target(flash
	DEPENDS ${PROJECT_NAME}.elf
	COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	COMMAND ${CMAKE_COMMAND} -E echo "║         🚀 Flashing Binary to STM32 MCU 🚀               ║"
	COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMAND ${ST_FLASH} --reset write ${BINARY_FILE} ${FLASH_ADDRESS}
	COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	COMMAND ${CMAKE_COMMAND} -E echo "║           🎯 Your binary is now on the STM32 MCU!        ║"
	COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMENT "Flashing binary to MCU"
)

# -----------------------------------------------------------------------------
# Flash target (UART bootloader via stm32flash)
# -----------------------------------------------------------------------------
add_custom_target(flash_uart
	DEPENDS ${PROJECT_NAME}.elf
	# COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	# COMMAND ${CMAKE_COMMAND} -E echo "║         🚀 Flashing Binary to STM32 MCU (UART) 🚀        ║"
	# COMMAND ${CMAKE_COMMAND} -E echo "║				✔✔ Ensure BOOT0 is pulled high!				 ║"
	# COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMAND sudo ${ST_UART_FLASH} -w ${BINARY_FILE} -v -g 0x0 ${ST_UART_FLASH_PORT}
	# COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	# COMMAND ${CMAKE_COMMAND} -E echo "║           🎯 Your binary is now on the STM32 MCU!        ║"
	# COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMENT "Flashing ${PROJECT_NAME}.bin to STM32 over UART"
)

# -----------------------------------------------------------------------------
# Clean Project (delete Build and .vscode safely)
# -----------------------------------------------------------------------------
add_custom_target(clean_all
	COMMAND ${CMAKE_COMMAND} -E echo ""
	COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	COMMAND ${CMAKE_COMMAND} -E echo "║                   🧹 Project Cleaned                     ║"
	COMMAND ${CMAKE_COMMAND} -E echo "║      ✔✔✔ Build files and VSCode configs removed ✔✔✔      ║"
	COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${BUILD_OUTPUT_DIR}
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${VSCODE_DIR}
	COMMENT "Cleaning project"
)

# -----------------------------------------------------------------------------
# ST-Link Information
# -----------------------------------------------------------------------------
add_custom_target(info
	COMMAND ${CMAKE_COMMAND} -E echo ""
	COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	COMMAND ${CMAKE_COMMAND} -E echo "║                  🔍 ST-Link Debug Probe Info             ║"
	COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMAND ${ST_INFO} --probe
	COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	COMMAND ${CMAKE_COMMAND} -E echo "║        📡 Probe details displayed successfully!          ║"
	COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMENT "Showing ST-Link debug probe info"
)

add_custom_target(info_uart
	COMMENT ""
	# COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	# COMMAND ${CMAKE_COMMAND} -E echo "║           🔍 ST-Link Debug Probe Info (UART)             ║"
	# COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMAND sudo ${ST_UART_FLASH} ${ST_UART_FLASH_PORT}
	# COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	# COMMAND ${CMAKE_COMMAND} -E echo "║        📡 Probe details displayed successfully!          ║"
	# COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMENT "Showing ST-Link debug probe info"
)

# -----------------------------------------------------------------------------
# Flash Erase
# -----------------------------------------------------------------------------
add_custom_target(erase_flash
	COMMAND ${CMAKE_COMMAND} -E echo ""
	COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	COMMAND ${CMAKE_COMMAND} -E echo "║                💥 Erasing STM32 Flash Memory 💥          ║"
	COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMAND ${ST_FLASH} erase
	COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	COMMAND ${CMAKE_COMMAND} -E echo "║        ✔ Flash memory successfully erased!               ║"
	COMMAND ${CMAKE_COMMAND} -E echo "║        💡 Next step: run make flash to program           ║"
	COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMENT "Erasing flash memory"
)


# -----------------------------------------------------------------------------
# Flash Erase (UART)
# -----------------------------------------------------------------------------
add_custom_target(erase_flash_uart
	COMMENT ""
	# COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	# COMMAND ${CMAKE_COMMAND} -E echo "║         💥 Erasing STM32 Flash Memory (UART) 💥          ║"
	# COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMAND sudo ${ST_UART_FLASH} -o ${ST_UART_FLASH_PORT}
	# COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	# COMMAND ${CMAKE_COMMAND} -E echo "║        ✔ Flash memory successfully erased!               ║"
	# COMMAND ${CMAKE_COMMAND} -E echo "║     💡 Next step: run make flash_uart to program         ║"
	# COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMENT "Erasing flash memory...."
)

# ---------------------- Make Targets Available ----------------------
# Use different names for custom targets to avoid conflicts with CMake reserved names
add_custom_target(flash_mcu DEPENDS flash)
add_custom_target(clean_project DEPENDS clean_all)
add_custom_target(stlink_info DEPENDS info)
add_custom_target(erase_mcu DEPENDS erase_flash)
add_custom_target(debug_config DEPENDS debug)

# ---------------------- Replace ----------------------
# Function to create a replace target
function(add_replace_target TARGET_NAME FILE_PATH IN_PROJECT_DIR)
	# Create Custom Target
	add_custom_target(${TARGET_NAME}
		# Display header
		COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
		COMMAND ${CMAKE_COMMAND} -E echo "║         🔄 Replacing ${FILE_PATH} in all projects        ║"
		COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"

		# Count files to be replaced
		COMMAND ${CMAKE_COMMAND} -E echo "Files being replaced:"
		COMMAND find ${REPO_ROOT}/Projects -name "${FILE_PATH}" -not -path "${IN_PROJECT_DIR}/${FILE_PATH}" | wc -l
		COMMAND find ${REPO_ROOT}/Projects -name "${FILE_PATH}" -not -path "${IN_PROJECT_DIR}/${FILE_PATH}"

		# Replace files using xargs
		COMMAND find ${REPO_ROOT}/Projects -name "${FILE_PATH}" -not -path "${IN_PROJECT_DIR}/${FILE_PATH}" -print0 | xargs -0 -I {} cp "${IN_PROJECT_DIR}/${FILE_PATH}" "{}"

		# Display footer
		COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
		COMMAND ${CMAKE_COMMAND} -E echo "║         ✅ All ${FILE_PATH} files replaced!              ║"
		COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	)
endfunction()

# Replace main.h
add_replace_target(replace_main_h "main.h" "${PROJ_DIR}/Inc")

# Replace systick.h
add_replace_target(replace_systick_h "systick.h" "${PROJ_DIR}/Inc")

# Replace systick.c
add_replace_target(replace_systick_c "systick.c" "${PROJ_DIR}/Src")

# Replace startup.c
add_replace_target(replace_startup_c "startup.c" "${PROJ_DIR}/Src")

# Replace linker script
add_replace_target(replace_linker "stm32f1_ls.ld" "${PROJ_DIR}/Startup")

# Replace CMakeLists.txt
add_replace_target(replace_cmake "CMakeLists.txt" "${PROJ_DIR}")