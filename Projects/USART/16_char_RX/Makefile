#******************************************************************************
# - STM32 Makefile for STM32F103C8T6 Project Template
# - Author: Shrey Shah
# - Date: 06/10/2024
#******************************************************************************
# Compiler/Tools Setup
CC = arm-none-eabi-gcc
LD = arm-none-eabi-objdump
LC = arm-none-eabi-objcopy

# Directories
ROOT_DIR = ~/Desktop/STM32/STM32F103C8T6
BAREMETAL_DIR = $(ROOT_DIR)/BareMetal
PROJECTS_DIR = $(ROOT_DIR)/Projects

APP_INC_DIR = $(shell pwd)/App_Inc
APP_SRC_DIR = $(shell pwd)/App_Src
STARTUP_DIR = $(shell pwd)/Startup
LINKER_DIR = $(shell pwd)/Linker

# Source and Include Directories
CORE_INC_DIR = $(BAREMETAL_DIR)/Inc
CORE_SRC_DIR = $(BAREMETAL_DIR)/Src
CORE_REG_DIR = $(BAREMETAL_DIR)/Core

# Project-Specific Flags
MACHINE = cortex-m3
CFLAGS = -mcpu=$(MACHINE) -mthumb -O0 -std=gnu11 -g -mfloat-abi=softfp -mfpu=fpv4-sp-d16
LDFLAGS = -nostdlib -T $(LINKER_DIR)/stm32_ls.ld
MAPFLAG = -Wl,-Map=$(LINKER_DIR)/stm32_mapfile.map

# File Targets
ELF_FILE = $(LINKER_DIR)/stm32_project.elf
BIN_FILE = $(LINKER_DIR)/stm32_project.bin
HEX_FILE = $(LINKER_DIR)/stm32_project.hex

# Source Files
C_SOURCES = $(wildcard $(APP_SRC_DIR)/*.c) \
            $(wildcard $(CORE_SRC_DIR)/*.c) \
            $(wildcard $(STARTUP_DIR)/*.c)

C_OBJECTS = $(C_SOURCES:%.c=%.o)

# Include Paths
INC_DIRS = -I $(CORE_REG_DIR) -I $(CORE_INC_DIR) -I $(APP_INC_DIR) -I $(STARTUP_DIR) -I $(LINKER_DIR)

# Default Target
all: $(BIN_FILE)
	@echo "***********************************************************************"
	@echo "Build Successful!"
	@echo "***********************************************************************"

# Clean target - Removes build artifacts
clean:
	rm -f $(C_OBJECTS)
	rm -f $(ELF_FILE) $(BIN_FILE) $(HEX_FILE)
	rm -f $(LINKER_DIR)/*.map
	rm -f $(LINKER_DIR)/*.bin
	rm -f $(LINKER_DIR)/*.hex
	rm -f $(LINKER_DIR)/*.elf
	@echo "***********************************************************************"
	@echo "Clean Successful!"
	@echo "***********************************************************************"

# Clean specific directories
clean_src:
	rm -f $(CORE_SRC_DIR)/*.o $(CORE_INC_DIR)/*.o

clean_user:
	rm -f $(APP_SRC_DIR)/*.o $(APP_INC_DIR)/*.o

clean_startup:
	rm -f $(STARTUP_DIR)/*.o

clean_linker:
	rm -f $(LINKER_DIR)/*.map

# Flash with the generated BIN file
flash: $(BIN_FILE)
	st-flash --reset write $(BIN_FILE) 0x08000000
	@echo "***********************************************************************"
	@echo "Flashing Completed Successfully!"
	@echo "***********************************************************************"

# Convert ELF to BIN file
$(BIN_FILE): $(ELF_FILE)
	$(LC) -O binary $(ELF_FILE) $(BIN_FILE)

# Convert ELF to HEX file
$(HEX_FILE): $(ELF_FILE)
	$(LC) -O ihex $(ELF_FILE) $(HEX_FILE)

# Link object files to create ELF file
$(ELF_FILE): $(C_OBJECTS)
	$(CC) $(C_OBJECTS) $(LDFLAGS) $(MAPFLAG) -o $(ELF_FILE)

# Compile C files to object files
%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@

# Flash file erase (optional: for cleaning the flash before writing)
erase_flash: clean
	st-flash erase
	@echo "***********************************************************************"
	@echo "Flash erased successfully!"
	@echo "***********************************************************************"

# Debugging: Dump ELF contents
linker_dump: $(ELF_FILE)
	$(LD) -h $(ELF_FILE)

# Print Blue Pill Specifications
get_info:
	st-info --probe
#******************************************************************************