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
INCFLAGS := -I$(PROJECT_DIR)/Core/Inc \
            -I$(PROJECT_DIR)/Driver/Inc \
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
SRCS := $(wildcard $(PROJECT_DIR)/Core/Src/*.c) \
        $(wildcard $(PROJECT_DIR)/Driver/Src/*.c) \
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
	@echo "Build Successful"
	@echo "***********************************************************************"

# Clean target
clean:
	rm -r $(BUILD_DIR) || true
	@echo "***********************************************************************"
	@echo "Cleaned Project"
	@echo "***********************************************************************"

# Include dependency files
-include $(OBJS:.o=.d)

.PHONY: clean all flash erase_flash
