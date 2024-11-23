#*******************************************************************************
	# - Filename: Makefile
	# - Author: Shrey Shah
	# - Date: 06/10/2024

	# Argument(s)
		# -mcpu {Machine CPU} 
		# -mthumb {Thumb Instruction Set [ARM CORTEX Mx supports only Thumb Instruction Set]}
		# -O {Optimization Level, 0 is no optimization}
		# -std {C Standard to be used for Compilation}
	# Basic Commands:
		# make all: All the folders
		# make clean: All the folders
		# make src: Only BareMetal/Src
		# make clean_src: Only BareMetal/Src
		# make startup: Only BareMetal/Startup
		# make clean_startup: Only BareMetal/Startup
		# make user: Only App_Src
		# make clean_user: Only App_Src
		# make linker: Only Linker
		# make clean_linker: Only Linker
		# make get_info: Blue Pill Specifications Descriptions on connection
		# make bin_file: Creates a .bin file from .elf file 
		# make flash: Uploads the .bin file at 0x08000000 
	
	# Reference STM32F103 Blue Pill Description
	# shrey_shah@Shrey:~$ st-info --probe
	# Found 1 stlink programmers
	#     version:    V2J42S7
	#     serial:     B55B5A1A000000006F82EF01
	#     flash:      65536 (pagesize: 1024)                    #### 64kB
	#     sram:       20480                                     #### 20kB
	#     chipid:     0x0410
	#     descr:      F1xx Medium-density
#*******************************************************************************
# ARM Cross Compiler (CC)
CC = arm-none-eabi-gcc 
# ARM .o Dump (LD)
LD = arm-none-eabi-objdump
LC = arm-none-eabi-objcopy
# ARM Machine Architecture
MACHINE = cortex-m3
# Include Directory
INC_DIR = ../../BareMetal/Inc
# Source Directory
SRC_DIR = ../../BareMetal/Src
# Startup Directory
STARTUP_DIR = ./Startup
# Linker Directory
LINKER_DIR = ./Linker
# User Include Directory
USER_INC_DIR = ./App_Inc
# User Source Directory
USER_SRC_DIR = ./App_Src
# Include Path Updation
INCLUDES = -I $(INC_DIR)
# Optimization Level
OPT_LEVEL = -O0
# C Standard
C_STD = gnu11
# CC Modified Flags (DO NOT ADD SPACE)
CFLAGS = -mcpu=$(MACHINE) -mthumb $(OPT_LEVEL) -std=$(C_STD)
#*******************************************************************************
# All Section

# Compiles all the files to generate .o/.elf files
all: bin_file

# Cleans all the .elf/.o/.s files
clean: clean_src clean_user clean_startup clean_linker

# Cleans the project
clean_project: clean_user clean_startup clean_linker

#*******************************************************************************
# Source Section

# Compiles all the Source Files
# Sequential Substitution of each .c found (wildcard()) in $(SRC_DIR) to .o (patsubst()), * => All
src: $(patsubst %.c, %.o, $(wildcard $(SRC_DIR)/*.c))

# Source File Compilation Rule
# Target: C_file.o, Dependency: C_file.c (% => Variable)
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(INCLUDES) -I $(STARTUP_DIR) $(CFLAGS) -c $< -o $@

# Cleans the Source Directory
clean_src: 
	rm -f $(SRC_DIR)/*.o
	rm -f $(SRC_DIR)/*.s
#*******************************************************************************
# User Application Section
USER_INCLUDES = -I $(USER_INC_DIR)

# Individual .c file to .o file
$(USER_SRC_DIR)/%.o: $(USER_SRC_DIR)/%.c
	$(CC) $(INCLUDES) $(USER_INCLUDES) $(CFLAGS) -c $< -o $@

# Compiles the User Source Code
user: $(patsubst %.c, %.o, $(wildcard $(USER_SRC_DIR)/*.c))

# Cleans the User Files
clean_user:
	rm -f $(USER_SRC_DIR)/*.o
	rm -f $(USER_SRC_DIR)/*.s
#*******************************************************************************
# Startup Section
STARTUP_FILE = $(STARTUP_DIR)/stm32_startup

# Compiles the startup file
startup:
	$(CC) $(CFLAGS) $(INCLUDES) $(USER_INCLUDES) -I $(LINKER_DIR) -c $(STARTUP_FILE).c -o $(STARTUP_FILE).o

# Cleans the Startup Folder
clean_startup:
	rm -f $(STARTUP_DIR)/*.o
	rm -f $(STARTUP_DIR)/*.s

#*******************************************************************************
# Linker Section
LINKER_FILE = $(LINKER_DIR)/stm32_ls
LFLAGS = -I $(STARTUP_DIR) -nostdlib -T
MAP_FILE = $(LINKER_DIR)/stm32_mf
MAPFLAG = -Wl,-Map=$(MAP_FILE).map
LFLAGS_INC_DIR = $(SRC_DIR)/*.o $(STARTUP_DIR)/*.o $(USER_SRC_DIR)/*.o

# Creates '.elf' file in Linker Directory
linker: clean src startup user
	$(CC) $(LFLAGS) $(LINKER_FILE).ld $(MAPFLAG) $(LFLAGS_INC_DIR) -o $(LINKER_FILE).elf

# Clears the .elf,.map,.bin files
clean_linker:
	rm -f $(LINKER_DIR)/*.elf
	rm -f $(LINKER_DIR)/*.map
	rm -f $(LINKER_DIR)/*.bin

# Dump the content of '.elf' file
linker_dump: linker
	$(LD) -h $(LINKER_FILE).elf	

#*******************************************************************************
# Flash (st-link)
BIN_FILE_FLAGS = -O binary 
FLASH_ADDR = 0x8000000

# Information about ST-LINK Chip (STM32F103)
get_info:
	st-info --probe

# Creates .bin file in the Linker Folder
bin_file: linker
	$(LC) $(BIN_FILE_FLAGS) $(LINKER_FILE).elf $(LINKER_FILE).bin

# Flash the .bin file
flash: bin_file
	st-flash --reset write $(LINKER_FILE).bin $(FLASH_ADDR)

#*******************************************************************************
# Flash (OpenOCD)
OPENOCD_DIR = /usr/share/openocd/scripts
ocd_flash:
	openocd -f $(OPENOCD_DIR)/interface/stlink-v2.cfg -f $(OPENOCD_DIR)/target/stm32f1x.cfg

gdb:
	gdb-multiarch /home/shrey_shah/Desktop/Blue_Pill_Ubuntu/Projects/LED_Project/Linker/stm32_ls.elf
#*******************************************************************************
# Reference Directory
REF_DIR = ../Template
# Reference App_Inc Directory
REF_USER_INC_DIR = $(REF_DIR)/App_Inc
# Reference App_Src Directory
REF_USER_SRC_DIR = $(REF_DIR)/App_Src
# Reference Startup Directory
REF_STARTUP_DIR = $(REF_DIR)/Startup
# Reference Linker Directory
REF_LINKER_DIR = $(REF_DIR)/Linker
# Reference Bin File
REF_LINKER_FILE = $(REF_LINKER_DIR)/stm32_ls
# Reference Startup File
REF_STARTUP_FILE = $(REF_STARTUP_DIR)/stm32_startup
# Reference User Inc Files
REF_USER_INCLUDES = -I $(REF_USER_INC_DIR)
# Reference Includes
REF_INCLUDES = $(REF_USER_INCLUDES) -I $(INC_DIR) -I $(REF_STARTUP_DIR)
REF_LFLAGS = -I $(REF_STARTUP_DIR) -nostdlib -T
REF_MAP_FILE = $(REF_LINKER_DIR)/stm32_mf
REF_MAPFLAG = -Wl,-Map=$(REF_MAP_FILE).map
REF_LFLAGS_INC_DIR = $(SRC_DIR)/*.o $(REF_STARTUP_DIR)/*.o $(REF_USER_SRC_DIR)/*.o

# Individual .c file to .o file
$(REF_USER_SRC_DIR)/%.o: $(REF_USER_SRC_DIR)/%.c
	$(CC) $(REF_INCLUDES) $(REF_USER_INCLUDES) $(CFLAGS) -c $< -o $@

# Compiles the User Source Code
ref_user: $(patsubst %.c, %.o, $(wildcard $(REF_USER_SRC_DIR)/*.c))

# Compiles the startup file
ref_startup:
	$(CC) $(CFLAGS) $(INCLUDES) $(REF_USER_INCLUDES) -I $(REF_LINKER_DIR) -c $(REF_STARTUP_FILE).c -o $(REF_STARTUP_FILE).o

# Creates '.elf' file in ../Reference/Linker
ref_linker: src ref_startup ref_user
	$(CC) $(REF_LFLAGS) $(REF_LINKER_FILE).ld $(REF_MAPFLAG) $(REF_LFLAGS_INC_DIR) -o $(REF_LINKER_FILE).elf

# Creates .bin file in the Linker Folder
ref_bin_file: ref_linker
	$(LC) $(BIN_FILE_FLAGS) $(REF_LINKER_FILE).elf $(REF_LINKER_FILE).bin

# Cleans the User Files in Reference
clean_ref_user:
	rm -f $(REF_USER_SRC_DIR)/*.o
	rm -f $(REF_USER_SRC_DIR)/*.s

# Cleans the Startup Folder in Reference
clean_ref_startup:
	rm -f $(REF_STARTUP_DIR)/*.o
	rm -f $(REF_STARTUP_DIR)/*.s

# Clears the .elf,.map,.bin files in Reference
clean_ref_linker:
	rm -f $(REF_LINKER_DIR)/*.elf
	rm -f $(REF_LINKER_DIR)/*.map
	rm -f $(REF_LINKER_DIR)/*.bin

# Compiles all the files to generate .o/.elf files
all_ref: ref_bin_file

# Clears all files in Reference
clean_ref: clean_ref_linker clean_ref_startup clean_ref_user

# Erase the flash
erase_flash: ref_bin_file clean
	st-flash --reset write $(REF_LINKER_FILE).bin $(FLASH_ADDR)
	rm -f $(REF_LINKER_DIR)/*.elf
	rm -f $(REF_LINKER_DIR)/*.map
	rm -f $(REF_LINKER_DIR)/*.bin
	rm -f $(REF_STARTUP_DIR)/*.o
	rm -f $(REF_STARTUP_DIR)/*.s
	rm -f $(REF_USER_SRC_DIR)/*.o
	rm -f $(REF_USER_SRC_DIR)/*.s
