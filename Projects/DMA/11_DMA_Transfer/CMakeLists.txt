# =============================================================================
# Minimum CMake Version
# =============================================================================
cmake_minimum_required(VERSION 3.28)

# =============================================================================
# Project Structure & Path Configuration
# =============================================================================

# ---------------------- Project Root Paths ----------------------
get_filename_component(PROJ_DIR "${CMAKE_SOURCE_DIR}" ABSOLUTE)
get_filename_component(REPO_ROOT "${PROJ_DIR}/../../../" ABSOLUTE)
message(STATUS "==========================================")
message(STATUS "Project Paths")
message(STATUS "==========================================")
message(STATUS "Project Directory: ${PROJ_DIR}")
message(STATUS "Repository Root: ${REPO_ROOT}")

# ---------------------- Source Code Directories ----------------------
set(DRIVER_ROOT			${REPO_ROOT}/BareMetal/Driver) 		# Hardware abstraction layer
set(CORE_ROOT			${REPO_ROOT}/BareMetal/Core)  	  	# Core system files
set(BUILD_OUTPUT_DIR	${PROJ_DIR}/Build)					# Build artifacts directory

# Verify critical directories exist
foreach(dir IN ITEMS ${DRIVER_ROOT} ${CORE_ROOT})
	if(NOT EXISTS ${dir})
		message(WARNING "Directory not found: ${dir}")
	endif()
endforeach()

# =============================================================================
# Cross-Compilation Configuration
# =============================================================================
set(CMAKE_SYSTEM_NAME Generic)								# Bare-metal target (no OS)
set(CMAKE_SYSTEM_PROCESSOR arm)								# Target processor architecture
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)			# Required for cross-compilation

# =============================================================================
# Toolchain Configuration
# =============================================================================

# ---------------------- Toolchain Installation Path ----------------------
set(TOOLCHAIN_PATH "/opt/arm-gnu-toolchain-14.3/bin")
if(NOT EXISTS ${TOOLCHAIN_PATH})
    message(WARNING "Toolchain path not found: ${TOOLCHAIN_PATH}")
endif()

# ---------------------- Compiler Executables ----------------------
set(CMAKE_C_COMPILER	${TOOLCHAIN_PATH}/${CMAKE_SYSTEM_PROCESSOR}-none-eabi-gcc)
set(CMAKE_ASM_COMPILER	${TOOLCHAIN_PATH}/${CMAKE_SYSTEM_PROCESSOR}-none-eabi-gcc)
set(CMAKE_CXX_COMPILER	${TOOLCHAIN_PATH}/${CMAKE_SYSTEM_PROCESSOR}-none-eabi-g++)

# ---------------------- Binary Utilities ----------------------
set(CMAKE_OBJCOPY		${TOOLCHAIN_PATH}/${CMAKE_SYSTEM_PROCESSOR}-none-eabi-objcopy)
set(CMAKE_SIZE			${TOOLCHAIN_PATH}/${CMAKE_SYSTEM_PROCESSOR}-none-eabi-size)

# Verify toolchain executables exist
foreach(tool IN ITEMS
    CMAKE_C_COMPILER 
	CMAKE_ASM_COMPILER 
	CMAKE_CXX_COMPILER 
    CMAKE_OBJCOPY CMAKE_SIZE
)
    if(NOT EXISTS ${${tool}})
        message(WARNING "Tool not found: ${${tool}}")
    endif()
endforeach()

# =============================================================================
# Flashing & Debugging Tools Configuration
# =============================================================================

# ---------------------- ST-Link Tools (SWD Programming) ----------------------
set(ST_FLASH      st-flash)							# ST-Link command line flasher
set(ST_FLASH_PATH "/usr/bin/st-flash")				# Full path to st-flash
set(ST_INFO       st-info)							# ST-Link device information
set(ST_UTIL_PATH  "/usr/bin/st-util")				# ST-Link GDB server

# ---------------------- OpenOCD (JTAG/SWD Debugging) ----------------------
set(OPENOCD      	openocd)						# OpenOCD command
set(OPENOCD_PATH	"/usr/bin/openocd")				# Full path to OpenOCD

# ---------------------- Serial Flashing Tools ----------------------
set(ST_UART_FLASH		stm32flash)          		# UART-based flasher
set(ST_UART_FLASH_PORT	"/dev/ttyUSB0")      		# Default UART port for flashing

# ---------------------- Debugging Tools ----------------------
set(GDB_PATH_MULTIARCH_PATH "/usr/bin/gdb-multiarch")  # ARM GDB debugger

# =============================================================================
# Tool Verification & Diagnostics
# =============================================================================

# Function to verify tool availability
function(verify_tool tool_name tool_path)
    if(EXISTS ${tool_path})
        message(STATUS "${tool_name}: ${tool_path}")
    else()
        message(FATAL_ERROR "${tool_name} not found: ${tool_path}")
    endif()
endfunction()

# Verify all external tools
message(STATUS "==========================================")
message(STATUS "Toolchain Verification")
message(STATUS "==========================================")
verify_tool("GCC Compiler"        ${CMAKE_C_COMPILER})
verify_tool("G++ Compiler"        ${CMAKE_CXX_COMPILER})
verify_tool("Objcopy"             ${CMAKE_OBJCOPY})
verify_tool("Size Utility"        ${CMAKE_SIZE})
verify_tool("ST-Flash"            ${ST_FLASH_PATH})
verify_tool("OpenOCD"             ${OPENOCD_PATH})
verify_tool("GDB Multiarch"       ${GDB_PATH_MULTIARCH_PATH})
verify_tool("ST-Util"             ${ST_UTIL_PATH})

# =============================================================================
# Build Output Configuration
# =============================================================================

# Create build output directory
if(NOT EXISTS ${BUILD_OUTPUT_DIR})
    file(MAKE_DIRECTORY ${BUILD_OUTPUT_DIR})
	get_filename_component(filename ${BUILD_OUTPUT_DIR} NAME)
    message(STATUS "Created build directory: ${filename}")
endif()

# Set build artifacts location
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}) 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})

# =============================================================================
# Configuration Summary
# =============================================================================
message(STATUS "==========================================")
message(STATUS "Build Environment Configuration Summary")
message(STATUS "==========================================")
message(STATUS "Target: ${CMAKE_SYSTEM_PROCESSOR}-none-eabi")
message(STATUS "Toolchain: ${TOOLCHAIN_PATH}")
message(STATUS "Build Output: ${BUILD_OUTPUT_DIR}")
message(STATUS "Flashing Port: ${ST_UART_FLASH_PORT}")

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

# =============================================================================
# File & Path Configuration
# =============================================================================

# ---------------------- Linker Script Configuration ----------------------
set(LINKER_FILE ${CORE_ROOT}/Src/stm32f103c8t6.ld)  # Default linker script
message(STATUS "Linker Script: ${LINKER_FILE}")

# Verify linker script exists
if(NOT EXISTS ${LINKER_FILE})
    message(FATAL_ERROR "Default linker script not found: ${LINKER_FILE}")
    message(STATUS "  → Replace LINKER_FILE variable for custom linker script")
endif()

# ---------------------- IDE & Development Tools ----------------------
set(VSCODE_DIR ${PROJ_DIR}/.vscode)  # VSCode configuration directory
if(NOT EXISTS ${VSCODE_DIR})
    message(STATUS "VSCode directory: ${VSCODE_DIR}")
endif()

# ---------------------- Build Artifacts ----------------------
set(BINARY_FILE ${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.bin)  # Raw binary output
set(HEX_FILE    ${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.hex)  # Intel HEX output

# =============================================================================
# Build Output Configuration
# =============================================================================

# ---------------------- Ensure Build Directory Exists ----------------------
if(NOT EXISTS ${BUILD_OUTPUT_DIR})
    file(MAKE_DIRECTORY ${BUILD_OUTPUT_DIR})
	get_filename_component(filename ${BUILD_OUTPUT_DIR} NAME)
    message(STATUS "Created build directory: ${filename}")
else()
	get_filename_component(filename ${BUILD_OUTPUT_DIR} NAME)
    message(STATUS "Build directory: ${filename}")
endif()

# ---------------------- CMake Output Directories ----------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${BUILD_OUTPUT_DIR})  # Executables
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${BUILD_OUTPUT_DIR})  # Static libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${BUILD_OUTPUT_DIR})  # Shared libraries

# =============================================================================
# Source Code Management
# =============================================================================

# ---------------------- Driver Module Collections ----------------------
# These lists will be populated by the `add_driver_module()` function
set(SELECTED_DRIVER_SOURCES  "")  # Collection of driver source files
set(SELECTED_DRIVER_INCLUDES "")  # Collection of driver include directories

# =============================================================================
# Driver Module Management
# =============================================================================
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
	# Information
	message(STATUS "==========================================")
	message(STATUS "Library")
	message(STATUS "==========================================")
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
	message(STATUS "==========================================")
endfunction()

# =============================================================================
# Driver Module Registration
# =============================================================================
# First Argument Option: SHOW_FULL_PATH / SHOW_FILENAME_ONLY
add_driver_module(SHOW_FILENAME_ONLY
    GPIO
    RCC 
    Timer
    DMA 
)

# =============================================================================
# Source File
# =============================================================================
# Project Source Files
file(GLOB_RECURSE PROJECT_SOURCES "${PROJ_DIR}/Src/*.c")
# Core Source Files (if any)
file(GLOB_RECURSE CORE_SOURCES "${CORE_ROOT}/Src/*.c")
# Compiled Source File List
set(ALL_SOURCE_FILES
    ${PROJECT_SOURCES}				# Application code
    ${SELECTED_DRIVER_SOURCES}		# Hardware drivers
    ${CORE_SOURCES}					# System core files
)

# =============================================================================
# Executable Target Definition
# =============================================================================
add_executable(${PROJECT_NAME}.elf ${ALL_SOURCE_FILES})

# =============================================================================
# Include Directory Configuration
# =============================================================================
set(ALL_INCLUDE_DIRS
    ${CORE_ROOT}/Inc					# Core system headers
    ${DRIVER_ROOT}						# Driver root directory
    ${SELECTED_DRIVER_INCLUDES}			# Module-specific includes
    ${PROJ_DIR}/Inc						# Project-specific headers
)
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${ALL_INCLUDE_DIRS})

# =============================================================================
# Compiler Flags Configuration
# =============================================================================
target_compile_options(${PROJECT_NAME}.elf PRIVATE
    $<$<COMPILE_LANGUAGE:C>:${C_FLAGS}>		# C source flags
    $<$<COMPILE_LANGUAGE:CXX>:${CXX_FLAGS}>	# C++ source flags  
    $<$<COMPILE_LANGUAGE:ASM>:${ASM_FLAGS}>	# Assembly source flags
)

# =============================================================================
# Linker Configuration
# =============================================================================
target_link_options(${PROJECT_NAME}.elf PRIVATE
    # MCU architecture options
    -mcpu=${MCU_CPU} -mthumb -mfloat-abi=soft
    # Linker script and map file
    -T${LINKER_FILE} -Wl,-Map=${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.map
    # Standard libraries (nano version for size)
    -lc -lm --specs=nano.specs
    # Optimization and analysis
    -Wl,--gc-sections          # Remove unused sections
    -Wl,--print-memory-usage   # Display memory usage
    -Wl,--stats                # Linker statistics
    -Wl,--cref                 # Cross-reference table
    # Bare-metal environment
    -static -nostartfiles -nodefaultlibs -nostdlib
)

# =============================================================================
# Post-Build Operations
# =============================================================================
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    # Generate binary file for flashing
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BINARY_FILE}
    # Generate HEX file for alternative programmers
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
    # Display memory section sizes
    COMMAND ${CMAKE_SIZE} --format=berkeley ${PROJECT_NAME}.elf
    COMMENT "Generating binary artifacts and memory report..."
)

# =============================================================================
# VSCode Configuration Generation
# =============================================================================
# This section auto-generates VSCode configuration files for seamless
# development experience. Files generated:
# - launch.json    : Debug configuration for Cortex-Debug extension
# - settings.json  : Tool paths and debug settings  
# - tasks.json     : Build and clean tasks
# - c_cpp_properties.json : IntelliSense configuration
# =============================================================================

# -----------------------------------------------------------------------------
# Helper Function: Create Generator Script
# -----------------------------------------------------------------------------
# Creates a CMake script that will generate VSCode configuration files
# during the build process. This ensures paths are properly expanded.
# -----------------------------------------------------------------------------
function(create_vscode_script name content)
    set(script "${CMAKE_CURRENT_BINARY_DIR}/gen_${name}.cmake")
    file(WRITE ${script} "${content}")
    message(STATUS "  Generated script: ${name}")
endfunction()

# -----------------------------------------------------------------------------
# Prepare Include Paths for JSON Format
# -----------------------------------------------------------------------------
# Convert CMake list to proper JSON array format for IntelliSense
# -----------------------------------------------------------------------------
set(INTELLISENSE_INCLUDE_PATHS "")
foreach(include_dir IN LISTS ALL_INCLUDE_DIRS)
    string(APPEND INTELLISENSE_INCLUDE_PATHS "        \\\"${include_dir}/**\\\",\n")
endforeach()
string(APPEND INTELLISENSE_INCLUDE_PATHS "        \\\"\\${workspaceFolder}/**\\\"")

# -----------------------------------------------------------------------------
# Generator Script: launch.json (Debug Configuration)
# -----------------------------------------------------------------------------
# Configures Cortex-Debug extension for STM32F103C8T6 with:
# - OpenOCD as debug server
# - SVD file for peripheral register view
# - Pre-launch build task integration
# -----------------------------------------------------------------------------
create_vscode_script(launch_json "
# Ensure VSCode directory exists
file(MAKE_DIRECTORY \\\"${VSCODE_DIR}\\\")

# Write launch configuration
file(WRITE \\\"${VSCODE_DIR}/launch.json\\\" \\\"{
  \\\\\\\"version\\\\\\\": \\\\\\\"0.2.0\\\\\\\",
  \\\\\\\"configurations\\\\\\\": [
    {
      \\\\\\\"name\\\\\\\": \\\\\\\"Debug: ${PROJECT_NAME}\\\\\\\",
      \\\\\\\"executable\\\\\\\": \\\\\\\"${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.elf\\\\\\\",
      \\\\\\\"request\\\\\\\": \\\\\\\"launch\\\\\\\",
      \\\\\\\"type\\\\\\\": \\\\\\\"cortex-debug\\\\\\\",
      \\\\\\\"servertype\\\\\\\": \\\\\\\"openocd\\\\\\\",
      \\\\\\\"device\\\\\\\": \\\\\\\"STM32F103C8\\\\\\\",
      \\\\\\\"configFiles\\\\\\\": [
        \\\\\\\"${CORE_ROOT}/Src/stlink.cfg\\\\\\\",
        \\\\\\\"${CORE_ROOT}/Src/stm32f1x.cfg\\\\\\\"
      ],
      \\\\\\\"svdFile\\\\\\\": \\\\\\\"${CORE_ROOT}/Src/stm32f103c8t6.svd\\\\\\\",
      \\\\\\\"runToEntryPoint\\\\\\\": \\\\\\\"main\\\\\\\",
      \\\\\\\"preLaunchTask\\\\\\\": \\\\\\\"Build Project\\\\\\\"
    }
  ]
}\\\")
")

# -----------------------------------------------------------------------------
# Generator Script: settings.json (Tool Paths)
# -----------------------------------------------------------------------------
# Defines paths for debugging tools and configures debug display options
# -----------------------------------------------------------------------------
create_vscode_script(settings_json "
# Ensure VSCode directory exists
file(MAKE_DIRECTORY \\\"${VSCODE_DIR}\\\")

# Write settings configuration
file(WRITE \\\"${VSCODE_DIR}/settings.json\\\" \\\"{
  \\\\\\\"cortex-debug.gdbPath\\\\\\\": \\\\\\\"${GDB_PATH_MULTIARCH_PATH}\\\\\\\",
  \\\\\\\"cortex-debug.openocdPath\\\\\\\": \\\\\\\"${OPENOCD_PATH}\\\\\\\",
  \\\\\\\"cortex-debug.stutilPath\\\\\\\": \\\\\\\"${ST_UTIL_PATH}\\\\\\\",
  \\\\\\\"cortex-debug.variableUseNaturalFormat\\\\\\\": false
}\\\")
")

# -----------------------------------------------------------------------------
# Generator Script: tasks.json (Build Tasks)
# -----------------------------------------------------------------------------
# Defines build system integration for VSCode:
# - Build Project (Ctrl+Shift+B): Compiles using CMake
# - Clean Project: Cleans build directory
# -----------------------------------------------------------------------------
create_vscode_script(tasks_json "
# Ensure VSCode directory exists
file(MAKE_DIRECTORY \\\"${VSCODE_DIR}\\\")

# Write tasks configuration
file(WRITE \\\"${VSCODE_DIR}/tasks.json\\\" \\\"{
  \\\\\\\"version\\\\\\\": \\\\\\\"2.0.0\\\\\\\",
  \\\\\\\"tasks\\\\\\\": [
    {
      \\\\\\\"label\\\\\\\": \\\\\\\"Build Project\\\\\\\",
      \\\\\\\"type\\\\\\\": \\\\\\\"shell\\\\\\\",
      \\\\\\\"command\\\\\\\": \\\\\\\"cmake\\\\\\\",
      \\\\\\\"args\\\\\\\": [\\\\\\\"--build\\\\\\\", \\\\\\\"${BUILD_OUTPUT_DIR}\\\\\\\"],
      \\\\\\\"group\\\\\\\": { \\\\\\\"kind\\\\\\\": \\\\\\\"build\\\\\\\", \\\\\\\"isDefault\\\\\\\": true },
      \\\\\\\"problemMatcher\\\\\\\": [\\\\\\\"\\\\\\$gcc\\\\\\\"],
      \\\\\\\"detail\\\\\\\": \\\\\\\"Build the current project using CMake\\\\\\\"
    },
    {
      \\\\\\\"label\\\\\\\": \\\\\\\"Clean Project\\\\\\\",
      \\\\\\\"type\\\\\\\": \\\\\\\"shell\\\\\\\",
      \\\\\\\"command\\\\\\\": \\\\\\\"cmake\\\\\\\",
      \\\\\\\"args\\\\\\\": [\\\\\\\"--build\\\\\\\", \\\\\\\"${BUILD_OUTPUT_DIR}\\\\\\\", \\\\\\\"--target\\\\\\\", \\\\\\\"clean_all\\\\\\\"],
      \\\\\\\"group\\\\\\\": \\\\\\\"build\\\\\\\",
      \\\\\\\"problemMatcher\\\\\\\": [],
      \\\\\\\"detail\\\\\\\": \\\\\\\"Clean the build directory\\\\\\\"
    }
  ]
}\\\")
")

# -----------------------------------------------------------------------------
# Generator Script: c_cpp_properties.json (IntelliSense)
# -----------------------------------------------------------------------------
# Configures C/C++ extension for proper code navigation and completion:
# - Include paths for all project directories in proper JSON array format
# - MCU-specific defines and compiler settings
# - Language standard configuration
# -----------------------------------------------------------------------------
create_vscode_script(cpp_properties_json "
# Ensure VSCode directory exists
file(MAKE_DIRECTORY \\\"${VSCODE_DIR}\\\")

# Write C/C++ properties configuration with properly formatted include paths
file(WRITE \\\"${VSCODE_DIR}/c_cpp_properties.json\\\" \\\"{
  \\\\\\\"configurations\\\\\\\": [
    {
      \\\\\\\"name\\\\\\\": \\\\\\\"Linux\\\\\\\",
      \\\\\\\"includePath\\\\\\\": [
		${INTELLISENSE_INCLUDE_PATHS}
      ],
      \\\\\\\"defines\\\\\\\": [
        \\\\\\\"${MCU_DEFINE}\\\\\\\",
        \\\\\\\"${MCU_CPU_DEFINE}\\\\\\\",
        \\\\\\\"\\\\\\$\\\\\\{workspaceFolder\\\\}/**\\\\\\\"
      ],
      \\\\\\\"compilerPath\\\\\\\": \\\\\\\"${CMAKE_C_COMPILER}\\\\\\\",
      \\\\\\\"cStandard\\\\\\\": \\\\\\\"${C_STD}\\\\\\\",
      \\\\\\\"cppStandard\\\\\\\": \\\\\\\"${CXX_STD}\\\\\\\",
      \\\\\\\"intelliSenseMode\\\\\\\": \\\\\\\"linux-gcc-arm\\\\\\\",
      \\\\\\\"compilerArgs\\\\\\\": [
        \\\\\\\"-mcpu=${MCU_CPU}\\\\\\\",
        \\\\\\\"-mthumb\\\\\\\",
        \\\\\\\"-mfloat-abi=soft\\\\\\\"
      ]
    }
  ],
  \\\\\\\"version\\\\\\\": 4
}\\\")
")

# =============================================================================
# Custom Targets for VSCode File Generation
# =============================================================================

# Individual targets for each VSCode configuration file
add_custom_target(vscode_launch
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/gen_launch_json.cmake
    COMMENT "Generating VSCode launch.json for debugging"
)

add_custom_target(vscode_settings  
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/gen_settings_json.cmake
    COMMENT "Generating VSCode settings.json with tool paths"
)

add_custom_target(vscode_tasks
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/gen_tasks_json.cmake
    COMMENT "Generating VSCode tasks.json for build system"
)

add_custom_target(vscode_cpp_properties
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/gen_cpp_properties_json.cmake
    COMMENT "Generating VSCode c_cpp_properties.json for IntelliSense"
)

# Master target that generates all VSCode configuration files
add_custom_target(vscode_files
    DEPENDS vscode_launch vscode_settings vscode_tasks vscode_cpp_properties
    COMMENT "Generating all VSCode configuration files"
)

# =============================================================================
# Custom Build Targets
# =============================================================================
# This section defines custom targets for development workflows:
# - Debug environment setup
# - Flashing via ST-Link and UART
# - Project maintenance and cleanup
# - Device information and management
# =============================================================================

# -----------------------------------------------------------------------------
# Debug Environment Setup Target
# -----------------------------------------------------------------------------
# Prepares the development environment by building the project and
# generating VSCode configuration files for seamless debugging experience.
# -----------------------------------------------------------------------------
add_custom_target(debug
    DEPENDS ${PROJECT_NAME}.elf vscode_files
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
    COMMAND ${CMAKE_COMMAND} -E echo "║               🛠️  Debug Environment Ready!                ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║                                                          ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  • Project built successfully                            ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  • VSCode configurations generated                       ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  • Ready for debugging in VSCode                         ║"
    COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
    COMMENT "Setting up debug environment: building project and generating VSCode configs"
)

# -----------------------------------------------------------------------------
# ST-Link Flashing Target
# -----------------------------------------------------------------------------
# Flashes the compiled binary to the STM32 MCU using ST-Link v2 debug probe
# via SWD interface. This is the primary flashing method for development.
# -----------------------------------------------------------------------------
add_custom_target(flash
    DEPENDS ${PROJECT_NAME}.elf
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
    COMMAND ${CMAKE_COMMAND} -E echo "║                🚀 Flashing via ST-Link v2                ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║                                                          ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Target: ${PROJECT_NAME}.bin                             ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Address: ${FLASH_ADDRESS}                               ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Method: ST-Link (SWD)                                   ║"
    COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
    COMMAND ${ST_FLASH} --reset write ${BINARY_FILE} ${FLASH_ADDRESS}
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
    COMMAND ${CMAKE_COMMAND} -E echo "║                  ✅ Flashing Complete!                   ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║                                                          ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Firmware successfully programmed to STM32               ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  MCU automatically reset and running                     ║"
    COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
    COMMENT "Flashing ${PROJECT_NAME}.bin to STM32 via ST-Link v2"
)

# -----------------------------------------------------------------------------
# UART Bootloader Flashing Target
# -----------------------------------------------------------------------------
# Flashes the compiled binary using the built-in UART bootloader.
# Requires BOOT0 pin to be pulled high before reset for bootloader entry.
# -----------------------------------------------------------------------------
add_custom_target(flash_uart
    DEPENDS ${PROJECT_NAME}.elf
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
    COMMAND ${CMAKE_COMMAND} -E echo "║               🔄 Flashing via UART Bootloader            ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║                                                          ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  ⚠️   Ensure BOOT0 is pulled HIGH before proceeding!     ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Target: ${PROJECT_NAME}.bin                             ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Port: ${ST_UART_FLASH_PORT}                             ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Method: UART Bootloader                                 ║"
    COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
    COMMAND sudo ${ST_UART_FLASH} -w ${BINARY_FILE} -v -g 0x0 ${ST_UART_FLASH_PORT}
    COMMENT "Flashing ${PROJECT_NAME}.bin to STM32 via UART bootloader"
)

# -----------------------------------------------------------------------------
# Project Cleanup Target
# -----------------------------------------------------------------------------
# Safely removes all build artifacts and generated configuration files.
# Use this to start with a completely clean build environment.
# -----------------------------------------------------------------------------
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
    COMMAND ${CMAKE_COMMAND} -E echo "║                     🧹 Project Cleanup                   ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║                                                          ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Removing:                                               ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║    • Build directory: ${BUILD_OUTPUT_DIR}                ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║    • VSCode configs: ${VSCODE_DIR}                       ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║    • Generated binaries and objects                      ║"
    COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BUILD_OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${VSCODE_DIR}
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
    COMMAND ${CMAKE_COMMAND} -E echo "║                  ✅ Cleanup Complete!                    ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║                                                          ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  All build artifacts and configurations removed          ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Ready for fresh build                                   ║"
    COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
    COMMENT "Completely cleaning project: build artifacts and VSCode configurations"
)

# -----------------------------------------------------------------------------
# ST-Link Information Target
# -----------------------------------------------------------------------------
# Displays information about connected ST-Link debug probes and their status.
# Useful for verifying hardware connections and probe functionality.
# -----------------------------------------------------------------------------
add_custom_target(info
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
    COMMAND ${CMAKE_COMMAND} -E echo "║                 🔍 ST-Link Probe Information             ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║                                                          ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Querying connected ST-Link debug probes...              ║"
    COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
    COMMAND ${ST_INFO} --probe
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
    COMMAND ${CMAKE_COMMAND} -E echo "║                📡 Probe Information Complete             ║"
    COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
    COMMENT "Displaying ST-Link debug probe information and status"
)

# -----------------------------------------------------------------------------
# UART Device Information Target
# -----------------------------------------------------------------------------
# Queries UART-connected STM32 devices for information using the bootloader.
# Useful for verifying UART connections and device presence.
# -----------------------------------------------------------------------------
add_custom_target(info_uart
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
    COMMAND ${CMAKE_COMMAND} -E echo "║               🔍 UART Device Information                ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║                                                        ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Querying UART port: ${ST_UART_FLASH_PORT}              ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  ⚠️   Ensure BOOT0 is pulled HIGH for bootloader mode   ║"
    COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
    COMMAND sudo ${ST_UART_FLASH} ${ST_UART_FLASH_PORT}
    COMMENT "Querying STM32 device information via UART bootloader"
)

# -----------------------------------------------------------------------------
# Flash Memory Erase Target (ST-Link)
# -----------------------------------------------------------------------------
# Erases the entire flash memory of the STM32 MCU using ST-Link.
# Useful for complete firmware removal or when starting fresh.
# -----------------------------------------------------------------------------
add_custom_target(erase_flash
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
    COMMAND ${CMAKE_COMMAND} -E echo "║                 💥 Flash Memory Erase                   ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║                                                        ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Erasing entire flash memory via ST-Link...           ║"
    COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
    COMMAND ${ST_FLASH} erase
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
    COMMAND ${CMAKE_COMMAND} -E echo "║                  ✅ Erase Complete!                      ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║                                                        ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Flash memory successfully erased                      ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Next: Run 'make flash' to program new firmware        ║"
    COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
    COMMENT "Erasing entire STM32 flash memory via ST-Link"
)

# -----------------------------------------------------------------------------
# Flash Memory Erase Target (UART)
# -----------------------------------------------------------------------------
# Erases the flash memory using the UART bootloader interface.
# Requires BOOT0 pin to be pulled high for bootloader mode.
# -----------------------------------------------------------------------------
add_custom_target(erase_flash_uart
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
    COMMAND ${CMAKE_COMMAND} -E echo "║              💥 Flash Erase via UART                    ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║                                                        ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  ⚠️   Ensure BOOT0 is pulled HIGH for bootloader mode   ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Port: ${ST_UART_FLASH_PORT}                            ║"
    COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
    COMMAND sudo ${ST_UART_FLASH} -o ${ST_UART_FLASH_PORT}
    COMMENT "Erasing STM32 flash memory via UART bootloader"
)

# =============================================================================
# Alias Targets for Better Usability
# =============================================================================
# These targets provide alternative names for better command-line experience
# and to avoid potential conflicts with CMake reserved target names.
# -----------------------------------------------------------------------------

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