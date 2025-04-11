# Makefile for STM32F103C8T6 Baremetal Programming

# Root directory
ROOT_DIR := /home/shrey_shah/Desktop/STM32/STM32F103C8T6

# Target name
TARGET := main

# Build type: Debug or Release
BUILD_TYPE := Debug
BUILD_DIR := $(shell pwd)/Build

# Toolchain
TRIPLE  = arm-none-eabi
CC      = $(TRIPLE)-gcc
LD      = $(TRIPLE)-ld
AS      = $(TRIPLE)-as
OBJCOPY = $(TRIPLE)-objcopy

# Include directories
INCFLAGS := -I$(ROOT_DIR)/BareMetal/Core/Inc \
			-I$(ROOT_DIR)/BareMetal/Driver/Inc \
			-I$(shell pwd)/Inc

# Compiler flags
CFLAGS := -mcpu=cortex-m3 -mfloat-abi=soft -mthumb --specs=nano.specs $(INCFLAGS) -std=gnu11 -O0 -Wall -fstack-usage -fdata-sections -ffunction-sections -DSTM32F103xB
# Assembler flags
ASFLAGS := -mcpu=cortex-m3 -mfloat-abi=soft -mthumb --specs=nano.specs $(INCFLAGS) -x assembler-with-cpp
# Linker flags
LDFLAGS := -mcpu=cortex-m3 -mfloat-abi=soft -mthumb --specs=nosys.specs $(INCFLAGS)

# Add debug flags if build type is debug
ifeq ($(BUILD_TYPE), Debug)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP
ASFLAGS += -MMD -MP

# Source and startup files
SRC_DIR := $(shell pwd)/Src
STARTUP_DIR := $(shell pwd)/Startup

# Use wildcard to gather all .c/.s files from the directories
SRCS := $(wildcard $(ROOT_DIR)/BareMetal/Driver/Src/*.c) \
		$(wildcard $(SRC_DIR)/*.c) \
		$(wildcard $(STARTUP_DIR)/*.c)

# Object files
OBJS := $(SRCS:.c=.o)
# Add the Build directory prefix, keeping only the file names (no paths)
BUILD_OBJ := $(patsubst %.o, $(BUILD_DIR)/%.o, $(notdir $(OBJS)))

# Ensure the build directory exists
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# '.bin' file rules
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin

# '.elf' rules
$(BUILD_DIR)/$(TARGET).elf: $(OBJS) $(STARTUP_DIR)/stm32f1_ls.ld
	$(CC) $(LDFLAGS) -o $@ $(BUILD_OBJ) -T $(STARTUP_DIR)/stm32f1_ls.ld -Wl,-Map="$(BUILD_DIR)/$(TARGET).map" -Wl,--gc-sections -static

# Compile C source files
%.o: %.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

# Compile assembly source files
%.o: %.s $(BUILD_DIR)
	$(CC) $(ASFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

# Flashing command (adjust as necessary)
flash: all
	st-flash --reset write $(BUILD_DIR)/$(TARGET).bin 0x08000000
	@echo "***********************************************************************"
	@echo "Flashed!"
	@echo "***********************************************************************"

# Flash Clean Project
erase_flash: clean
	st-flash erase
	@echo "***********************************************************************"
	@echo "Flashed Erased!"
	@echo "***********************************************************************"

# ST-Link Information
info:
	@echo "***********************************************************************"
	st-info --probe
	@echo "***********************************************************************"

# All target
all: $(BUILD_DIR)/$(TARGET).bin generate_c_cpp_properties_json
	@echo "***********************************************************************"
	@echo "Build Successful!"
	@echo "***********************************************************************"

# Clean target
clean:
	@rm -r $(BUILD_DIR) || true
	@rm -r ./.vscode || true
	@echo "***********************************************************************"
	@echo "Cleaned Project"
	@echo "***********************************************************************"

# Debug
debug: $(BUILD_DIR)/$(TARGET).elf vscode_files
	@echo "***********************************************************************"
	@echo "Debug Configurations Ready!"
	@echo "***********************************************************************"

# Generate all necessary files in .vscode directory
vscode_files:
	$(MAKE) generate_launch_json
	$(MAKE) generate_settings_json
	$(MAKE) generate_tasks_json
	$(MAKE) generate_c_cpp_properties_json

# Ensure the .vscode directory exists
.vscode:
	@mkdir -p ./.vscode

# launch.json
generate_launch_json: .vscode
	@printf '{\n  "version": "0.2.0",\n  "configurations": [\n    {\n      "name": "Debug: $(notdir $(shell pwd))",\n      "executable": "$(BUILD_DIR)/$(TARGET).elf",\n      "request": "launch",\n      "type": "cortex-debug",\n      "servertype": "openocd",\n      "device": "STM32F103C8",\n      "configFiles": [\n        "$(ROOT_DIR)/BareMetal/Core/Src/stlink.cfg",\n        "$(ROOT_DIR)/BareMetal/Core/Src/stm32f1x.cfg"\n      ],\n      "svdFile": "$(ROOT_DIR)/BareMetal/Core/Src/STM32F103.svd",\n      "runToEntryPoint": "main",\n      "preLaunchTask": "Build Project"\n    }\n  ]\n}' > .vscode/launch.json

# settings.json
generate_settings_json: .vscode
	@printf '{\n    "cortex-debug.gdbPath": "/usr/bin/gdb-multiarch",\n    "cortex-debug.openocdPath": "/usr/local/bin/openocd",\n    "cortex-debug.stutilPath": "/usr/bin/st-util",\n    "cortex-debug.variableUseNaturalFormat": false\n}' > .vscode/settings.json

# tasks.json
generate_tasks_json: .vscode
	@printf '{\n    "version": "2.0.0",\n    "tasks": [\n        {\n            "label": "Build Project",\n            "type": "shell",\n            "command": "make",\n            "args": ["all", "debug"],\n            "group": {\n                "kind": "build",\n                "isDefault": true\n            },\n            "problemMatcher": ["$$gcc"],\n            "detail": "Build the current project using Makefile",\n            "dependsOn": "Clean Project"\n        },\n        {\n            "label": "Clean Project",\n            "type": "shell",\n            "command": "make",\n            "args": ["clean"],\n            "group": "build",\n            "problemMatcher": [],\n            "detail": "Clean the build directory"\n        }\n    ]\n}' > .vscode/tasks.json

# c_cpp_properties.json
generate_c_cpp_properties_json: .vscode
	@printf '{\n    "configurations": [\n        {\n            "name": "Linux",\n            "includePath": [\n                "$(ROOT_DIR)/BareMetal/Core/Inc/**",\n                "$(ROOT_DIR)/BareMetal/Driver/Inc/**",\n                "../Inc/**"\n            ],\n            "defines": [],\n            "compilerPath": "/usr/bin/arm-none-eabi-gcc",\n            "cStandard": "c11",\n            "cppStandard": "gnu++17",\n            "intelliSenseMode": "linux-gcc-arm"\n        }\n    ],\n    "version": 4\n}' > .vscode/c_cpp_properties.json	

# Define the target for replacing Makefiles within $(ROOT_DIR)/Projects
# replace_makefiles:
# 	@echo "***********************************************************************"
# 	@echo "Current directory: $$(realpath --relative-to=$(ROOT_DIR)/Projects $$(pwd))"
# 	@echo "***********************************************************************"
# 	@echo "The Makefiles present in the following directory will be replaced:" && \
# 	find $(ROOT_DIR)/Projects -type f -name "Makefile" -not -path "$$(pwd)/*" -exec sh -c 'for f; do echo "Relative Path: $$(dirname $$f | sed "s|^$(ROOT_DIR)/Projects/||")/"; done' _ {} + && \
# 	find $(ROOT_DIR)/Projects -type f -name "Makefile" -not -path "$$(pwd)/*" -exec cp $$(pwd)/Makefile {} \;
# 	@echo "***********************************************************************"
# 	@echo "All the above mentioned directories having Makefiles have been replaced!"
# 	@echo "***********************************************************************"

# Robust cross-platform file replacement
# Usage: make replace FILE=<filename> FOLDER=<foldername> [TYPE=all|numbered]
replace:
	@echo "***********************************************************************"
	@echo "Starting file replacement process"
	@echo "***********************************************************************"
	
	# Parameter validation
	@if [ -z "$(FILE)" ]; then \
		echo "ERROR: FILE parameter not specified"; \
		echo "Usage: make replace FILE=<filename> FOLDER=<foldername> [TYPE=all|numbered]"; \
		exit 1; \
	fi
	@if [ -z "$(FOLDER)" ]; then \
		echo "ERROR: FOLDER parameter not specified"; \
		echo "Usage: make replace FILE=<filename> FOLDER=<foldername> [TYPE=all|numbered]"; \
		exit 1; \
	fi
	
	# Set defaults
	@TYPE=${TYPE:-numbered}
	@SOURCE_FILE="$(FOLDER)/$(FILE)"
	
	# Verify source file exists
	@if [ ! -f "$$SOURCE_FILE" ]; then \
		echo "ERROR: Source file $$SOURCE_FILE not found"; \
		echo "Please run from directory containing the source file"; \
		exit 1; \
	fi
	
	@echo "Replacing: $(FILE)"
	@echo "From folder: $(FOLDER)"
	@echo "Mode: $$TYPE"
	@echo "Source path: $$SOURCE_FILE"
	@echo "***********************************************************************"
	@echo "Files to be replaced:"
	
	# Find and display target files
	@if [ "$$TYPE" = "numbered" ]; then \
		echo "Searching in numbered folders (##_*)"; \
		for dir in $(ROOT_DIR)/Projects/*/[0-9][0-9]_*/$(FOLDER)/; do \
			if [ -f "$$dir/$(FILE)" ]; then \
				echo "$$dir/$(FILE)" | sed "s|$(ROOT_DIR)/Projects/||"; \
			fi; \
		done; \
	else \
		echo "Searching in all folders"; \
		for dir in $(ROOT_DIR)/Projects/*/*/$(FOLDER)/; do \
			if [ -f "$$dir/$(FILE)" ]; then \
				echo "$$dir/$(FILE)" | sed "s|$(ROOT_DIR)/Projects/||"; \
			fi; \
		done; \
	fi
	
	@echo "***********************************************************************"
	@echo "Confirm replacement? (y/n)"; \
	read -r answer; \
	if [ "$$answer" != "y" ] && [ "$$answer" != "Y" ]; then \
		echo "Replacement cancelled"; \
		exit 0; \
	fi
	
	# Perform replacement
	@echo "Starting replacement..."
	@if [ "$$TYPE" = "numbered" ]; then \
		for dir in $(ROOT_DIR)/Projects/*/[0-9][0-9]_*/$(FOLDER)/; do \
			if [ -f "$$dir/$(FILE)" ]; then \
				cp -v "$$SOURCE_FILE" "$$dir/$(FILE)"; \
			fi; \
		done; \
	else \
		for dir in $(ROOT_DIR)/Projects/*/*/$(FOLDER)/; do \
			if [ -f "$$dir/$(FILE)" ]; then \
				cp -v "$$SOURCE_FILE" "$$dir/$(FILE)"; \
			fi; \
		done; \
	fi
	
	@echo "***********************************************************************"
	@echo "Replacement complete!"
	@echo "***********************************************************************"

# Predefined aliases
replace_makefiles: FILE=Makefile FOLDER=.
replace_makefiles: replace

replace_startup: FILE=stm32f1_startup.c FOLDER=Startup
replace_startup: TYPE=numbered
replace_startup: replace

replace_linkerscript: FILE=stm32f1_ls.ld FOLDER=Startup
replace_linkerscript: TYPE=numbered
replace_linkerscript: replace


# Alias for replacing Makefiles
replace_makefiles:
	make replace FILE=Makefile

# Alias for replacing Startup
replace_startup:
	make FILE=stm32f1_startup.c FOLDER=Startup

# Alias for replacing Startup
replace_linker:
	make FILE=stm32f1_ls.ld FOLDER=Startup

# Include dependency files
-include $(OBJS:.o=.d)

.PHONY: clean generate_c_cpp_properties_json all flash erase_flash
