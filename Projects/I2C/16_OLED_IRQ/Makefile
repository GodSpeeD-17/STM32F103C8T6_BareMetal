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

# Target to list files, count them, and replace them based on the FILE parameter
replace_files:
	@if [ -z "$(FILE)" ]; then \
		echo "ERROR: FILE parameter not specified"; \
		echo "Usage: make replace_files FILE=<pattern>"; \
		exit 1; \
	fi
	@echo "***********************************************************************"
	@echo "Current directory: $$(realpath --relative-to=$(ROOT_DIR)/Projects $$(pwd))"
	@echo "***********************************************************************"
	@FILE_PATHS=$$(find $(ROOT_DIR)/Projects -type f -name "$(FILE)" -not -path "$$(pwd)/*"); \
	echo "$$FILE_PATHS" | sed "s|$(ROOT_DIR)/Projects/||"; \
	echo "Total count: $$(echo "$$FILE_PATHS" | wc -l)"; \
	for dest_file in $$FILE_PATHS; do \
		rel_path="$$(realpath --relative-to=$(ROOT_DIR)/Projects "$$dest_file")"; \
		src_file="$$(find $(shell pwd) -type f -name "$$(basename "$$dest_file")" | head -n 1)"; \
		if [ -n "$$src_file" ]; then \
			echo "Replacing '$(ROOT_DIR)/Projects/$$rel_path' with '$$src_file'"; \
			cp "$$src_file" "$(ROOT_DIR)/Projects/$$rel_path"; \
		else \
			echo "Source file for '$(ROOT_DIR)/Projects/$$rel_path' not found, skipping."; \
		fi; \
	done
	@echo "***********************************************************************"

# Include dependency files
-include $(OBJS:.o=.d)

.PHONY: clean generate_c_cpp_properties_json all flash erase_flash
