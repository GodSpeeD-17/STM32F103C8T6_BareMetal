# ---------------------- Minimum CMake Version ----------------------
cmake_minimum_required(VERSION 3.28)

# ---------------------- Project ----------------------
# Get the current source directory name
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME} C CXX ASM)

# ---------------------- Cross Compilation ----------------------
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# ---------------------- Toolchain ----------------------
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_SIZE    arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(ST_FLASH st-flash)
set(OPENOCD openocd)
set(ST_INFO st-info)

# ---------------------- C Flags ----------------------
set(MCU_MODEL STM32F103C8T6)
set(MCU_CPU cortex-m3)
set(C_STD gnu11)
set(OPTIMIZATION_LEVEL 0)
set(FLASH_ADDRESS 0x08000000)

# ---------------------- Paths ----------------------
get_filename_component(PROJ_DIR "${CMAKE_SOURCE_DIR}" ABSOLUTE)
get_filename_component(REPO_ROOT "${PROJ_DIR}/../../../" ABSOLUTE)
set(DRIVER_ROOT ${REPO_ROOT}/BareMetal/Driver)
set(CORE_ROOT ${REPO_ROOT}/BareMetal/Core)
set(BUILD_OUTPUT_DIR ${PROJ_DIR}/Build)
set(LINKER_FILE ${PROJ_DIR}/Startup/stm32f1_ls.ld)
set(VSCODE_DIR ${PROJ_DIR}/.vscode)
set(BINARY_FILE ${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.bin)
set(HEX_FILE ${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.hex)

# ---------------------- Output directories ----------------------
file(MAKE_DIRECTORY ${BUILD_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})
set(SELECTED_DRIVER_SOURCES "")

# ---------------------- Sources ----------------------
set(SELECTED_DRIVER_SOURCES "")
set(SELECTED_DRIVER_INCLUDES "")

# Function to add a driver module
function(add_driver_module)
	# Iterate over each module name passed as argument
	foreach(module_name IN LISTS ARGN)
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
			message(STATUS "   |    |-- ${hdr}")
			endforeach()
			message(STATUS "   |")
			endif()
			
			# Source File Tree
			if(EXISTS ${DRIVER_MODULE_DIR}/Src)
				message(STATUS "   |-- Src")
				file(GLOB MODULE_SOURCES ${DRIVER_MODULE_DIR}/Src/*.c)
				foreach(src IN LISTS MODULE_SOURCES)
					message(STATUS "        |-- ${src}")
				endforeach()
			endif()
		else()
			message(WARNING "Driver module ${module_name} not found at ${DRIVER_MODULE_DIR}")
		endif()
	endforeach()
endfunction()

# ---------------------- Includes & Sources ----------------------
# Project Source Files
file(GLOB_RECURSE PROJECT_SOURCES "${PROJ_DIR}/Src/*.c")
# Core Source Files (if any)
file(GLOB_RECURSE CORE_SOURCES "${CORE_ROOT}/Src/*.c")

# ----------------------------------- Add driver modules -----------------------------------
add_driver_module(
	GPIO 
	RCC
	Timer
	USART
)

# ---------------------- Executable ----------------------
add_executable(${PROJECT_NAME}.elf
	${PROJECT_SOURCES}
	${SELECTED_DRIVER_SOURCES}
	${CORE_SOURCES}
)

# ---------------------- Include Dirs ----------------------
set(ALL_INCLUDE_DIRS
	${PROJ_DIR}/Inc
	${CORE_ROOT}/Inc
	${DRIVER_ROOT}
	${SELECTED_DRIVER_INCLUDES}
)

target_include_directories(${PROJECT_NAME}.elf 
	PRIVATE 
	${ALL_INCLUDE_DIRS}
)
# ---------------------- Flags ----------------------

# For the .elf target (C Language)
target_compile_options(${PROJECT_NAME}.elf PRIVATE
	-mcpu=${MCU_CPU} -mthumb -mfloat-abi=soft 
	--specs=nano.specs -lc -lm
	-std=${C_STD} -O${OPTIMIZATION_LEVEL} -Wall
	-fstack-usage -fdata-sections -ffunction-sections 
	-D${MCU_MODEL} -MMD -MP -g -gdwarf-2
)

# For the .elf target (Assembly Language)
target_compile_options(${PROJECT_NAME}.elf PRIVATE
	$<$<COMPILE_LANGUAGE:ASM>:-mcpu=${MCU_CPU} -mthumb -mfloat-abi=soft 
	--specs=nano.specs -lc -lm -x assembler-with-cpp -MMD -MP>
)

target_link_options(${PROJECT_NAME}.elf PRIVATE
	-mcpu=${MCU_CPU} -mthumb -mfloat-abi=soft
	-T${LINKER_FILE} -lc -lm
	-Wl,-Map=${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.map
	-Wl,--gc-sections
)

# ---------------------- Size Command ----------------------
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Generating .bin/.hex and printing size"
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BINARY_FILE}
    COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --black
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}.elf>
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
	  \\\"svdFile\\\": \\\"${CORE_ROOT}/Src/STM32F103.svd\\\",
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
  \\\"cortex-debug.gdbPath\\\": \\\"/usr/bin/gdb-multiarch\\\",
  \\\"cortex-debug.openocdPath\\\": \\\"/usr/local/bin/openocd\\\",
  \\\"cortex-debug.stutilPath\\\": \\\"/usr/bin/st-util\\\",
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
		\\\"${CORE_ROOT}/Inc/**\\\",
		\\\"${DRIVER_ROOT}/*/Inc/**\\\",
		\\\"${PROJ_DIR}/Inc/**\\\"
	  ],
	  \\\"defines\\\": [\\\"STM32F103C8T6\\\"],
	  \\\"compilerPath\\\": \\\"/usr/bin/arm-none-eabi-gcc\\\",
	  \\\"cStandard\\\": \\\"c11\\\",
	  \\\"cppStandard\\\": \\\"gnu++17\\\",
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
# Flash Binary to MCU
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
# Clean Project (delete Build and .vscode safely)
# -----------------------------------------------------------------------------
add_custom_target(clean_all
	COMMAND ${CMAKE_COMMAND} -E echo ""
	COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	COMMAND ${CMAKE_COMMAND} -E echo "║                    🧹 Project Cleaned                    ║"
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