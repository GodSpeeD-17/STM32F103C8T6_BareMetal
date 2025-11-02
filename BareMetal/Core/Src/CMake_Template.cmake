# =============================================================================
# Header Guard
# =============================================================================
include_guard(GLOBAL)

# =============================================================================
# Tool Verification & Diagnostics
# =============================================================================
function(verify_tool tool_name tool_path)
    if(EXISTS ${tool_path})
        message(STATUS "${tool_name}: ${tool_path}")
    else()
        message(FATAL_ERROR "${tool_name} not found: ${tool_path}")
    endif()
endfunction()

# =============================================================================
# Project Path Validation
# =============================================================================
message(STATUS "====================================================================================")
message(STATUS "Project Paths Summary:")
message(STATUS "====================================================================================")
verify_tool("Project Directory"			${PROJ_DIR})
verify_tool("Repository Root"			${REPO_ROOT})
verify_tool("Core Root"					${CORE_ROOT})
verify_tool("Driver Root"				${DRIVER_ROOT})
verify_tool("Linker Script"				${LINKER_FILE})
verify_tool("Toolchain Path"			${TOOLCHAIN_PATH})
verify_tool("ST-Flash"					${ST_FLASH_PATH})
verify_tool("ST-Util"					${ST_UTIL_PATH})
verify_tool("OpenOCD"					${OPENOCD_PATH})
verify_tool("GDB Multiarch"				${GDB_PATH_MULTIARCH_PATH})

# ---------------------- Binary Utilities ----------------------
set(CMAKE_OBJCOPY				  ${TOOLCHAIN_PREFIX}-objcopy)
set(CMAKE_OBJDUMP				  ${TOOLCHAIN_PREFIX}-objdump)
set(CMAKE_NM					  ${TOOLCHAIN_PREFIX}-nm)
set(CMAKE_SIZE					  ${TOOLCHAIN_PREFIX}-size)

verify_tool("GCC Compiler"        ${CMAKE_C_COMPILER})
verify_tool("ASM Compiler"        ${CMAKE_ASM_COMPILER})
verify_tool("G++ Compiler"        ${CMAKE_CXX_COMPILER})
verify_tool("Objcopy"             ${CMAKE_OBJCOPY})
verify_tool("Objdump"             ${CMAKE_OBJDUMP})
verify_tool("NM"        		  ${CMAKE_NM})
verify_tool("Size Utility"        ${CMAKE_SIZE})

# Modules registered
if(NOT DEFINED DRIVER_MODULES)
	message(FATAL_ERROR "DRIVER_MODULES not set! Please set this in your project's CMakeLists.txt before including this template")
# Optimization Level
elseif(NOT DEFINED OPTIMIZATION_LEVEL)
	message(WARNING "OPTIMIZATION_LEVEL not set! Assuming it to be O1")
	set(OPTIMIZATION_LEVEL 1)
# Flash Address
elseif(NOT DEFINED FLASH_ADDRESS)
	message(WARNING "FLASH_ADDRESS not set! Assuming 0x08000000")
	set(FLASH_ADDRESS 0x08000000)
# Driver Module Tree View
elseif(NOT DEFINED DRIVER_MODULE_TREE)
	message(WARNING "DRIVER_MODULE_TREE not set! Assuming SHOW_FILENAME_ONLY")
	set(DRIVER_MODULE_TREE SHOW_FILENAME_ONLY)
# UART Flashing Port
elseif(NOT DEFINED ST_UART_FLASH_PORT)
	message(WARNING "ST_UART_FLASH_PORT not set! Assuming /dev/ttyUSB0")
	set(ST_UART_FLASH_PORT "/dev/ttyUSB0")
endif()

# =============================================================================
# Flashing & Debugging Tools Configuration
# =============================================================================
set(ST_FLASH      				  st-flash)					# ST-Link command line flasher
set(ST_INFO       				  st-info)					# ST-Link device information
set(OPENOCD      				  openocd)					# OpenOCD command
set(ST_UART_FLASH				  stm32flash)          		# UART-based flasher

# =============================================================================
# Build Output Configuration
# =============================================================================

# Create build output directory
if(NOT EXISTS ${BUILD_OUTPUT_DIR})
    message(FATAL_ERROR "${BUILD_OUTPUT_DIR} Missing!")
endif() 

# =============================================================================
# MCU Configuration
# =============================================================================
set(MCU STM32F103C8T6)
set(MCU_DEFINE ${MCU}__)
set(MCU_CPU_DEFINE CORTEX_M3__)
set(MCU_CPU cortex-m3)

# =============================================================================
# Language Standards
# =============================================================================
set(C_STD gnu11)
set(CXX_STD c++17)

# =============================================================================
# Base Compiler Flags
# =============================================================================
set(DEFAULT_FLAGS 
    -mcpu=${MCU_CPU}
    -mthumb
    -mfloat-abi=soft
    -lc -lm -lstdc++ -lsupc++
    --specs=nano.specs    # Use reduced libc
    --specs=nosys.specs   # No system calls
    -MMD -MP              # Dependency generation
    -save-temps           # Keep intermediate files
)

# =============================================================================
# Common Flags (C & C++)
# =============================================================================
set(COMMON_FLAGS 
	${DEFAULT_FLAGS}
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
set(C_FLAGS 
	${COMMON_FLAGS}
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

# Linker Flags
set(LINKER_FLAGS
    -mcpu=${MCU_CPU} -mthumb -mfloat-abi=soft # MCU architecture options
    -T${LINKER_FILE} -Wl,-Map=${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.map     # Linker script and map file
    -lc -lm -lstdc++ -lsupc++ --specs=nano.specs # Standard libraries (nano version for size)
    -Wl,--gc-sections          # Remove unused sections
    -Wl,--print-memory-usage   # Display memory usage
    -Wl,--stats                # Linker statistics
    -Wl,--cref                 # Cross-reference table
    # Bare-metal environment
    -static 
	# -nostartfiles -nodefaultlibs -nostdlib
)
# =============================================================================
# File & Path Configuration
# =============================================================================

# ---------------------- IDE & Development Tools ----------------------
set(VSCODE_DIR ${PROJ_DIR}/.vscode)  # VSCode configuration directory
if(NOT EXISTS ${VSCODE_DIR})
	file(MAKE_DIRECTORY ${VSCODE_DIR})
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
	message(STATUS "====================================================================================")
	message(STATUS "Library")
	message(STATUS "====================================================================================")
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
	message(STATUS "====================================================================================")
endfunction()

# =============================================================================
# Driver Module Registration
# =============================================================================
# First Argument Option: SHOW_FULL_PATH / SHOW_FILENAME_ONLY
add_driver_module(
	${DRIVER_MODULE_TREE}
    ${DRIVER_MODULES}
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
    ${LINKER_FLAGS}
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
# VSCode: launch.json (Debug Configuration)
# -----------------------------------------------------------------------------
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
  COMMAND ${CMAKE_COMMAND} -E echo "      \\\"runToEntryPoint\\\": \\\"main\\\", // Main" >> ${VSCODE_DIR}/launch.json
  COMMAND ${CMAKE_COMMAND} -E echo "//    \\\"runToEntryPoint\\\": \\\"Reset_Handler\\\", // Reset Handler" >> ${VSCODE_DIR}/launch.json
  COMMAND ${CMAKE_COMMAND} -E echo "      \\\"preLaunchTask\\\": \\\"Build Project\\\"," >> ${VSCODE_DIR}/launch.json
  COMMAND ${CMAKE_COMMAND} -E echo "      \\\"postLaunchCommands\\\": [" 		>> ${VSCODE_DIR}/launch.json
  COMMAND ${CMAKE_COMMAND} -E echo "        \\\"monitor reset init\\\"," 		>> ${VSCODE_DIR}/launch.json
  COMMAND ${CMAKE_COMMAND} -E echo "        \\\"load\\\"," 		>> ${VSCODE_DIR}/launch.json
  COMMAND ${CMAKE_COMMAND} -E echo "        \\\"monitor reset halt\\\"" 		>> ${VSCODE_DIR}/launch.json
  COMMAND ${CMAKE_COMMAND} -E echo "      ]" 									>> ${VSCODE_DIR}/launch.json
  COMMAND ${CMAKE_COMMAND} -E echo "    }"                                      >> ${VSCODE_DIR}/launch.json
  COMMAND ${CMAKE_COMMAND} -E echo "  ]"                                        >> ${VSCODE_DIR}/launch.json
  COMMAND ${CMAKE_COMMAND} -E echo "}"                                          >> ${VSCODE_DIR}/launch.json
  COMMENT "----------------------------------- launch.json -----------------------------------"
)

# -----------------------------------------------------------------------------
# VSCode: settings.json (Tool Paths)
# -----------------------------------------------------------------------------
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

# -----------------------------------------------------------------------------
# VSCode: tasks.json (Build Tasks)
# -----------------------------------------------------------------------------
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
  COMMAND ${CMAKE_COMMAND} -E echo "      \\\"problemMatcher\\\": [\\\"\\$gcc\\\"]," >> ${VSCODE_DIR}/tasks.json
  COMMAND ${CMAKE_COMMAND} -E echo "      \\\"detail\\\": \\\"Build the current project using CMake\\\"" >> ${VSCODE_DIR}/tasks.json
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

# -----------------------------------------------------------------------------
# VSCode: c_cpp_properties.json
# -----------------------------------------------------------------------------
add_custom_target(vscode_c_cpp_properties
  COMMAND ${CMAKE_COMMAND} -E make_directory ${VSCODE_DIR}
  COMMAND ${CMAKE_COMMAND} -E make_directory "${VSCODE_DIR}"
  COMMAND ${CMAKE_COMMAND} -E echo "{"                                          >  "${VSCODE_DIR}/c_cpp_properties.json"
  COMMAND ${CMAKE_COMMAND} -E echo "  \\\"configurations\\\": ["                >> "${VSCODE_DIR}/c_cpp_properties.json"
  COMMAND ${CMAKE_COMMAND} -E echo "    {"                                      >> "${VSCODE_DIR}/c_cpp_properties.json"
  COMMAND ${CMAKE_COMMAND} -E echo "      \\\"name\\\": \\\"Linux\\\","         >> "${VSCODE_DIR}/c_cpp_properties.json"
  COMMAND ${CMAKE_COMMAND} -E echo "      \\\"includePath\\\": ["               >> "${VSCODE_DIR}/c_cpp_properties.json"
  COMMAND ${CMAKE_COMMAND} -E echo "        \\\"${CORE_ROOT}/Inc/**\\\","		>> "${VSCODE_DIR}/c_cpp_properties.json"
  COMMAND ${CMAKE_COMMAND} -E echo "        \\\"${DRIVER_ROOT}/**\\\","			>> "${VSCODE_DIR}/c_cpp_properties.json"
  COMMAND ${CMAKE_COMMAND} -E echo "        \\\"${PROJ_DIR}/Inc/**\\\""			>> "${VSCODE_DIR}/c_cpp_properties.json"
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
  
# Master target that generates all VSCode configuration files
add_custom_target(vscode_files
	DEPENDS 
		# vscode_settings
		vscode_launch 
		vscode_tasks 
		vscode_c_cpp_properties
	COMMENT "----------------------------------- Generating vscode files -----------------------------------"
)

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

# Debug target to see the actual command
add_custom_target(debug_flash
    COMMAND ${CMAKE_COMMAND} -E echo "ST_FLASH: ${ST_FLASH}"
    COMMAND ${CMAKE_COMMAND} -E echo "BINARY_FILE: ${BINARY_FILE}"
    COMMAND ${CMAKE_COMMAND} -E echo "FLASH_ADDRESS: ${FLASH_ADDRESS}"
    COMMAND ${CMAKE_COMMAND} -E echo "Full command: ${ST_FLASH} --reset write ${BINARY_FILE} ${FLASH_ADDRESS}"
)


# -----------------------------------------------------------------------------
# ST-Link Flashing Target
# -----------------------------------------------------------------------------
add_custom_target(flash
    DEPENDS ${PROJECT_NAME}.elf
    COMMAND ${ST_FLASH} --reset write ${BINARY_FILE} ${FLASH_ADDRESS}
    COMMENT "Flashing ${PROJECT_NAME}.bin to STM32 via ST-Link v2 (SWD)"
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
    COMMAND ${CMAKE_COMMAND} -E echo "║               🔍 UART Device Information                 ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║                                                          ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Querying UART port: ${ST_UART_FLASH_PORT}               ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  ⚠️   Ensure BOOT0 is pulled HIGH for bootloader mode    ║"
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
    COMMAND ${CMAKE_COMMAND} -E echo "║                 💥 Flash Memory Erase                    ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║                                                          ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Erasing entire flash memory via ST-Link...              ║"
    COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
    COMMAND ${ST_FLASH} erase
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
    COMMAND ${CMAKE_COMMAND} -E echo "║                  ✅ Erase Complete!                      ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║                                                          ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Flash memory successfully erased                        ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Next: Run 'make flash' to program new firmware          ║"
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
    COMMAND ${CMAKE_COMMAND} -E echo "║              💥 Flash Erase via UART                     ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║                                                          ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  ⚠️   Ensure BOOT0 is pulled HIGH for bootloader mode    ║"
    COMMAND ${CMAKE_COMMAND} -E echo "║  Port: ${ST_UART_FLASH_PORT}                             ║"
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

# Replace CMakeLists.txt
add_replace_target(replace_cmake "CMakeLists.txt" "${PROJ_DIR}")