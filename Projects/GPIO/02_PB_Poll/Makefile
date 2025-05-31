# --- Configuration ---
MCU_MODEL      := STM32F103xB
FLASH_TOTAL_KB := 64
RAM_TOTAL_KB   := 20

# Paths
ROOT_DIR       := /home/shrey_shah/Desktop/STM32/STM32F103C8T6
DRIVER_BASE    := $(ROOT_DIR)/BareMetal/Driver
BUILD_DIR      := $(shell pwd)/Build
TARGET         := main
BUILD_TYPE     := Debug

# --- Toolchain ---
TRIPLE         := arm-none-eabi
CC             := $(TRIPLE)-gcc
OBJCOPY        := $(TRIPLE)-objcopy
SIZE           := $(TRIPLE)-size

# Includes (Core, Driver root, and all Driver module Inc directories)
INCLUDES       := -I$(ROOT_DIR)/BareMetal/Core/Inc \
                  -I$(DRIVER_BASE) \
                  $(addprefix -I, $(wildcard $(DRIVER_BASE)/*/Inc)) \
                  -I$(shell pwd)/Inc

# Sources Files
DRIVER_SRCS    := $(wildcard $(DRIVER_BASE)/*/Src/*.c)
LOCAL_SRCS     := $(wildcard $(shell pwd)/Src/*.c) \
                  $(wildcard $(shell pwd)/Startup/*.c)
# Combine all sources
SRCS := $(DRIVER_SRCS) $(LOCAL_SRCS)

# --- Object Files ---
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))

# Add vpath to help Make find matching source files
vpath %.c $(sort $(dir $(SRCS)))

# --- Compiler Flags ---
CFLAGS         := -mcpu=cortex-m3 -mfloat-abi=soft -mthumb --specs=nano.specs $(INCLUDES) -std=gnu11 -O0 -Wall \
                  -fstack-usage -fdata-sections -ffunction-sections -D$(MCU_MODEL) -MMD -MP
# --- Assembler Flags ---
ASFLAGS        := -mcpu=cortex-m3 -mfloat-abi=soft -mthumb --specs=nano.specs $(INCFLAGS) -x assembler-with-cpp
# --- Linker Flags ---
LDFLAGS        := -mcpu=cortex-m3 -mfloat-abi=soft -mthumb --specs=nosys.specs $(INCFLAGS)

# Add debug flags if build type is debug
ifeq ($(BUILD_TYPE), Debug)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP
ASFLAGS += -MMD -MP

# --- Build Rules ---
$(BUILD_DIR):
	@mkdir -p $@

# '.bin' file rules
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# '.elf' rules
$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -T $(shell pwd)/Startup/stm32f1_ls.ld \
	-Wl,-Map="$(BUILD_DIR)/$(TARGET).map",--gc-sections -static

# Compile C Files
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Memory Report ---
define memory_report
	@echo "\033[1;36m=== Memory Usage ===\033[0m"
	@$(SIZE) -A -x $(BUILD_DIR)/$(TARGET).elf | awk -v flash_kb=$(FLASH_TOTAL_KB) -v ram_kb=$(RAM_TOTAL_KB) '\
	  /\.text/ { text=$$2 } \
	  /\.data/ { data=$$2 } \
	  /\.bss/  { bss=$$3 } \
	  END { \
	    flash_used = text + data; \
	    ram_used = data + bss; \
	    printf("Flash: %d/%d KB (%.1f%%)\nRAM:   %d/%d KB (%.1f%%)\n", \
	      flash_used/1024, flash_kb, (flash_used/(flash_kb*1024))*100, \
	      ram_used/1024, ram_kb, (ram_used/(ram_kb*1024))*100); \
	    if (ram_used > ram_kb*1024*0.8) \
	      print "\033[1;31mWARNING: High RAM usage!\033[0m"; \
	  }'
endef
# ST-Link Information
info:
	@echo "***********************************************************************"
	st-info --probe
	@echo "***********************************************************************"

# All target
all: $(BUILD_DIR)/$(TARGET).bin
	@echo "***********************************************************************"
	@echo "*                         Build Successful!                           *"
	@echo "***********************************************************************"
	@echo "*                         Memory Usage Report                         *"
	@echo "***********************************************************************"
	@$(SIZE) ./Build/main.elf | awk 'NR==2 { \
		text=$$1; data=$$2; bss=$$3; \
		flash=text+data; ram=data+bss; \
		printf "|-------------------|-------------------|\n"; \
		printf("|%19s|%19s|\n", "     Flash     ", "      RAM       "); \
		printf "|-------------------|-------------------|\n"; \
		printf "|   (text: %5d)   |   (data: %5d)   |\n", text, data; \
		printf "|   (data: %5d)   |   (bss : %5d)   |\n", data, bss; \
		printf "|-------------------|-------------------|\n"; \
		printf("|%16s   |%16s   |\n", sprintf("%7d bytes", flash), sprintf("%7d bytes", ram)); \
		printf "|-------------------|-------------------|\n"; \
	}'
	@echo "***********************************************************************"

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
replace:
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

# Makefile Alias
replace_makefile:
	$(MAKE) replace FILE="Makefile"

# Startup Alias
replace_startup:
	$(MAKE) replace FILE="stm32f1_startup.c"

# Linker Alias
replace_linker:
	$(MAKE) replace FILE="stm32f1_ls.ld"

# Include dependency files
-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: clean generate_c_cpp_properties_json all flash erase_flash