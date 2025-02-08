# Makefile for STM32F103C8T6 Baremetal Programming

# Root directory
PROJECT_DIR := /home/shrey_shah/Desktop/STM32/STM32F103C8T6

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
INCFLAGS := -I$(PROJECT_DIR)/BareMetal/Core/Inc \
			-I$(PROJECT_DIR)/BareMetal/Driver/Inc \
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
SRCS := $(wildcard $(PROJECT_DIR)/BareMetal/Driver/Src/*.c) \
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
all: $(BUILD_DIR)/$(TARGET).bin
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


# # Debug
debug: $(BUILD_DIR)/$(TARGET).elf vscode generate_launch_json generate_settings_json generate_tasks_json
	@echo "***********************************************************************"
	@echo "Debug Configurations Ready!"
	@echo "***********************************************************************"

# Ensure the .vscode directory exists
vscode:
	@mkdir -p ./.vscode

# launch.json
generate_launch_json:
	@echo '{' > .vscode/launch.json
	@echo '  "version": "0.2.0",' >> .vscode/launch.json
	@echo '  "configurations": [' >> .vscode/launch.json
	@echo '    {' >> .vscode/launch.json
	@echo '      "name": "Cortex-M3 Debug (STM32F103C8)",' >> .vscode/launch.json
	@echo '      "executable": "$(BUILD_DIR)/$(TARGET).elf",' >> .vscode/launch.json
	@echo '      "request": "launch",' >> .vscode/launch.json
	@echo '      "type": "cortex-debug",' >> .vscode/launch.json
	@echo '      "servertype": "openocd",' >> .vscode/launch.json
	@echo '      "device": "STM32F103C8",' >> .vscode/launch.json
	@echo '      "configFiles": [' >> .vscode/launch.json
	@echo '        "$(PROJECT_DIR)/BareMetal/Core/Src/stlink.cfg",' >> .vscode/launch.json
	@echo '        "$(PROJECT_DIR)/BareMetal/Core/Src/stm32f1x.cfg"' >> .vscode/launch.json
	@echo '      ],' >> .vscode/launch.json
	@echo '      "svdFile": "$(PROJECT_DIR)/BareMetal/Core/Src/STM32F103.svd",' >> .vscode/launch.json
	@echo '      "runToEntryPoint": "main",' >> .vscode/launch.json
	@echo '    }' >> .vscode/launch.json
	@echo '  ]' >> .vscode/launch.json
	@echo '}' >> .vscode/launch.json

# settings.json
generate_settings_json:
	@echo '{' > .vscode/settings.json
	@echo '    "cortex-debug.gdbPath": "/usr/bin/gdb-multiarch",' >> .vscode/settings.json
	@echo '    "cortex-debug.openocdPath": "/usr/local/bin/openocd",' >> .vscode/settings.json
	@echo '    "cortex-debug.stutilPath": "/usr/bin/st-util",' >> .vscode/settings.json
	@echo '    "cortex-debug.variableUseNaturalFormat": false' >> .vscode/settings.json
	@echo '}' >> .vscode/settings.json

# tasks.json
generate_tasks_json:
	@mkdir -p .vscode
	@echo '{' > .vscode/tasks.json
	@echo '    "version": "2.0.0",' >> .vscode/tasks.json
	@echo '    "tasks": [' >> .vscode/tasks.json
	@echo '        {' >> .vscode/tasks.json
	@echo '            "label": "Build Project",' >> .vscode/tasks.json
	@echo '            "type": "shell",' >> .vscode/tasks.json
	@echo '            "command": "make",' >> .vscode/tasks.json
	@echo '            "args": ["all"],' >> .vscode/tasks.json
	@echo '            "group": {' >> .vscode/tasks.json
	@echo '                "kind": "build",' >> .vscode/tasks.json
	@echo '                "isDefault": true' >> .vscode/tasks.json
	@echo '            },' >> .vscode/tasks.json
	@echo '            "problemMatcher": ["$$gcc"],' >> .vscode/tasks.json
	@echo '            "detail": "Build the current project using Makefile"' >> .vscode/tasks.json
	@echo '        },' >> .vscode/tasks.json
	@echo '        {' >> .vscode/tasks.json
	@echo '            "label": "Clean Project",' >> .vscode/tasks.json
	@echo '            "type": "shell",' >> .vscode/tasks.json
	@echo '            "command": "make",' >> .vscode/tasks.json
	@echo '            "args": ["clean"],' >> .vscode/tasks.json
	@echo '            "group": "build",' >> .vscode/tasks.json
	@echo '            "problemMatcher": [],' >> .vscode/tasks.json
	@echo '            "detail": "Clean the build directory"' >> .vscode/tasks.json
	@echo '        }' >> .vscode/tasks.json
	@echo '    ]' >> .vscode/tasks.json
	@echo '}' >> .vscode/tasks.json

# Include dependency files
-include $(OBJS:.o=.d)

.PHONY: clean all flash erase_flash
