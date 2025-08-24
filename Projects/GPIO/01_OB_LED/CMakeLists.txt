# ---------------------- Minimum CMake Version ----------------------
cmake_minimum_required(VERSION 3.28)

# ---------------------- Project ----------------------
project(01_OB_LED C ASM)

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

# ---------------------- Paths ----------------------
get_filename_component(PROJ_DIR "${CMAKE_SOURCE_DIR}" ABSOLUTE)
get_filename_component(REPO_ROOT "${PROJ_DIR}/../../../" ABSOLUTE)
set(DRIVER_ROOT ${REPO_ROOT}/BareMetal/Driver)
set(CORE_ROOT ${REPO_ROOT}/BareMetal/Core)
set(BUILD_OUTPUT_DIR ${PROJ_DIR}/Build)
set(LINKER_FILE ${PROJ_DIR}/Startup/stm32f1_ls.ld)

# ---------------------- Output directories ----------------------
file(MAKE_DIRECTORY ${BUILD_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})
# ---------------------- Sources ----------------------
file(GLOB_RECURSE PROJECT_SOURCES "${PROJ_DIR}/Src/*.c")
file(GLOB_RECURSE DRIVER_SOURCES "${DRIVER_ROOT}/*/Src/*.c") 
file(GLOB_RECURSE CORE_SOURCES "${CORE_ROOT}/Src/*.c")
set(ALL_SOURCES
	${PROJECT_SOURCES}
	${DRIVER_SOURCES}
	${CORE_SOURCES}
)
message(STATUS "All sources: ${ALL_SOURCES}")

# ---------------------- Executable ----------------------
add_executable(${PROJECT_NAME}.elf
	${ALL_SOURCES}
)

# ---------------------- Include Dirs ----------------------
file(GLOB DRIVER_DIR "${DRIVER_ROOT}")
message(STATUS "Driver directory: ${DRIVER_DIR}")
file(GLOB DRIVER_INC_DIRS "${DRIVER_ROOT}/*/Inc")
message(STATUS "Driver include directories: ${DRIVER_INC_DIRS}")
file(GLOB CORE_INC_DIRS "${CORE_ROOT}/Inc")
message(STATUS "Core include directory: ${CORE_INC_DIRS}")
file(GLOB PROJECT_INC_DIRS "${PROJ_DIR}/Inc")
message(STATUS "Project include directory: ${PROJECT_INC_DIRS}")
target_include_directories(${PROJECT_NAME}.elf PRIVATE
	${CORE_INC_DIRS}
	${DRIVER_DIR}
	${DRIVER_INC_DIRS}
	${PROJECT_INC_DIRS}
)

# ---------------------- Flags ----------------------
target_compile_options(${PROJECT_NAME}.elf PRIVATE
	-mcpu=cortex-m3 -mthumb -mfloat-abi=soft
	-O0 -g -Wall
	-ffunction-sections -fdata-sections
	-fstack-usage
	-DSTM32F103C8T6
)

target_link_options(${PROJECT_NAME}.elf PRIVATE
	-mcpu=cortex-m3 -mthumb -mfloat-abi=soft
	-T${LINKER_FILE}
	-Wl,-Map=${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.map
	-Wl,--gc-sections
)

# ---------------------- Size Command ----------------------
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.bin
	COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${PROJECT_NAME}.elf> ${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.hex
	COMMAND ${CMAKE_SIZE}    $<TARGET_FILE:${PROJECT_NAME}.elf>
	COMMENT "Generating .bin/.hex and printing size"
)

# ---------------------- Custom Targets ----------------------
# Flash Binary to MCU
add_custom_target(flash
	DEPENDS ${PROJECT_NAME}.elf
	COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	COMMAND ${CMAKE_COMMAND} -E echo "║         🚀 Flashing Binary to STM32 MCU 🚀               ║"
	COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMAND ${ST_FLASH} --reset write ${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.bin 0x08000000
	COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	COMMAND ${CMAKE_COMMAND} -E echo "║           🎯 Your binary is now on the STM32 MCU!        ║"
	COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMENT "Flashing binary to MCU"
)

# Clean Target
add_custom_target(clean_all
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${BUILD_OUTPUT_DIR}
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJ_DIR}/.vscode
	COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	COMMAND ${CMAKE_COMMAND} -E echo "║                    🧹 Project Cleaned                    ║"
	COMMAND ${CMAKE_COMMAND} -E echo "║      ✔✔✔ Build files and VSCode configs removed ✔✔✔      ║"
	COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMENT "Cleaning project"
)

# ST-Link Information
add_custom_target(info
	COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	COMMAND ${CMAKE_COMMAND} -E echo "║             🔍 ST-Link Debug Probe Info                  ║"
	COMMAND ${CMAKE_COMMAND} -E echo "╠══════════════════════════════════════════════════════════╣"
	COMMAND ${ST_INFO} --probe
	COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMENT "Showing ST-Link info"
)

# Flash Erase
add_custom_target(erase_flash
	COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
	COMMAND ${CMAKE_COMMAND} -E echo "║              💥 Flash Erased Successfully! 💥            ║"
	COMMAND ${ST_FLASH} erase
	COMMAND ${CMAKE_COMMAND} -E echo "║            ✔✔✔ MCU Flash memory wiped clean              ║"
	COMMAND ${CMAKE_COMMAND} -E echo "║            💡 Ready to program with: make flash          ║"
	COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
	COMMENT "Erasing flash memory"
)

# Generate VSCode configuration files
add_custom_target(vscode_files
	COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJ_DIR}/.vscode
	COMMAND ${CMAKE_COMMAND} -E echo "Generating VSCode configuration files..."
	COMMAND ${CMAKE_COMMAND} 
		-DPROJECT_NAME=${PROJECT_NAME}
		-DBUILD_OUTPUT_DIR=${BUILD_OUTPUT_DIR}
		-DCORE_ROOT=${CORE_ROOT}
		-DDRIVER_ROOT=${DRIVER_ROOT}
		-DPROJ_DIR=${PROJ_DIR}
		-P ${CMAKE_CURRENT_SOURCE_DIR}/generate_vscode.cmake
)

# Debug target
add_custom_target(debug
	DEPENDS ${PROJECT_NAME}.elf
	DEPENDS vscode_files
	COMMAND ${CMAKE_COMMAND} -E echo "***********************************************************************"
	COMMAND ${CMAKE_COMMAND} -E echo "Debug Configurations Ready!"
	COMMAND ${CMAKE_COMMAND} -E echo "***********************************************************************"
	COMMENT "Preparing debug environment"
)

# ---------------------- Make Targets Available ----------------------
# Use different names for custom targets to avoid conflicts with CMake reserved names
add_custom_target(flash_mcu DEPENDS flash)
add_custom_target(clean_project DEPENDS clean_all)
add_custom_target(stlink_info DEPENDS info)
add_custom_target(erase_mcu DEPENDS erase_flash)
add_custom_target(debug_config DEPENDS debug)

# ---------------------- Replace ----------------------

# Target to see what will be replaced first (dry run)
# add_custom_target(replace_cmake_dry
#     COMMAND ${CMAKE_COMMAND} -E echo "Files that will be replaced:"
#     COMMAND find ${REPO_ROOT}/Projects -name "CMakeLists.txt" -not -path "${PROJ_DIR}/CMakeLists.txt"
#     COMMAND ${CMAKE_COMMAND} -E echo "Total files to replace:"
#     COMMAND find ${REPO_ROOT}/Projects -name "CMakeLists.txt" -not -path "${PROJ_DIR}/CMakeLists.txt" | wc -l
#     COMMENT "Dry run: Showing which CMakeLists.txt files will be replaced"
# )

# Target to replace CMakeLists.txt files - WORKING
# add_custom_target(replace_cmake
#     COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
#     COMMAND ${CMAKE_COMMAND} -E echo "║         🔄 Replacing CMakeLists.txt in all projects      ║"
#     COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
    
#     # Display files being replaced
#     COMMAND ${CMAKE_COMMAND} -E echo "Files being replaced:"
# 	COMMAND find ${REPO_ROOT}/Projects -name "CMakeLists.txt" -not -path "${PROJ_DIR}/CMakeLists.txt" | wc -l
#     COMMAND find ${REPO_ROOT}/Projects -name "CMakeLists.txt" -not -path "${PROJ_DIR}/CMakeLists.txt"
    
#     # Actual replacement
#     # COMMAND find ${REPO_ROOT}/Projects -name "CMakeLists.txt" -not -path "${PROJ_DIR}/CMakeLists.txt" -exec cp "${PROJ_DIR}/CMakeLists.txt" {} \\;
    
#     COMMAND ${CMAKE_COMMAND} -E echo "╔══════════════════════════════════════════════════════════╗"
#     COMMAND ${CMAKE_COMMAND} -E echo "║         ✅ All CMakeLists.txt files replaced!           ║"
#     COMMAND ${CMAKE_COMMAND} -E echo "╚══════════════════════════════════════════════════════════╝"
#     COMMENT "Replacing CMakeLists.txt in other projects"
# )

# Target to replace CMakeLists.txt files - WORKING
add_custom_target(replace_cmake
    COMMAND ${CMAKE_COMMAND} -E echo "Replacing CMakeLists.txt files..."
    
    # Use xargs instead of -exec (more reliable)
    COMMAND find ${REPO_ROOT}/Projects -name CMakeLists.txt -not -path "${PROJ_DIR}/CMakeLists.txt" -print0 | xargs -0 -I {} cp "${PROJ_DIR}/CMakeLists.txt" "{}"
    
    COMMAND ${CMAKE_COMMAND} -E echo "Replacement complete!"
    COMMENT "Replacing CMakeLists.txt in other projects"
)



