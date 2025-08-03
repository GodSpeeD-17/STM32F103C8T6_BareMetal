# ---------------------- Configuration ----------------------
MCU_MODEL      := STM32F103xB
FLASH_TOTAL_KB := 64
RAM_TOTAL_KB   := 20
# ---------------------- Path Definitions ----------------------
ROOT_DIR       := /home/shrey_shah/Desktop/STM32/STM32F103C8T6
DRIVER_BASE    := $(ROOT_DIR)/BareMetal/Driver
BUILD_DIR      := $(shell pwd)/Build
TARGET         := main
# ---------------------- Toolchain ----------------------
TRIPLE         := arm-none-eabi
CC             := $(TRIPLE)-gcc
OBJCOPY        := $(TRIPLE)-objcopy
SIZE           := $(TRIPLE)-size
# ---------------------- Include Directories ----------------------
INCLUDES       := -I$(ROOT_DIR)/BareMetal/Core/Inc \
				  -I$(DRIVER_BASE) \
				  $(addprefix -I, $(wildcard $(DRIVER_BASE)/*/Inc)) \
				  -I$(shell pwd)/Inc
# ---------------------- Compiler Flags -----------------------
CFLAGS         := -mcpu=cortex-m3 -mfloat-abi=soft -mthumb --specs=nano.specs -lc -lm $(INCLUDES) -std=gnu11 -O0 -Wall \
				  -fstack-usage -fdata-sections -ffunction-sections -D$(MCU_MODEL) -MMD -MP -g -gdwarf-2
# ---------------------- Assembler Flags ----------------------
ASFLAGS        := -mcpu=cortex-m3 -mfloat-abi=soft -mthumb --specs=nano.specs -lc -lm $(INCFLAGS) -x assembler-with-cpp -MMD -MP
# ---------------------- Linker Flags ----------------------
LDFLAGS        := -mcpu=cortex-m3 -mfloat-abi=soft -mthumb --specs=nano.specs -lc -lm $(INCFLAGS)
# ---------------------- Dependency Placeholders ----------------------
DEPENDENCY_OUTPUT :=
DEPENDENCY_HEADERS :=
DRIVER_SRCS :=
SRCS := 
OBJS :=
# Dependency mk file
DEPENDENCY_FILE := $(BUILD_DIR)/dependency.mk
# Include generated dependencies early
-include $(DEPENDENCY_FILE)
# ---------------------- Build Rules ----------------------
# Ensure Build Directory Exists
$(BUILD_DIR):
	@mkdir -p $@

# Rule to compile C source files to object files
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link Object files to produce ELF file
$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -T $(shell pwd)/Startup/stm32f1_ls.ld \
	-Wl,-Map="$(BUILD_DIR)/$(TARGET).map",--gc-sections -static

# Convert ELF to binary
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# ---------------------- Memory Usage Report ----------------------
define memory_report
	@echo "\033[1;36m"
	@echo "╔══════════════════════════════════════════════════════════╗"
	@echo "║                 STM32 Memory Usage Report                ║"
	@echo "╠══════════════════════════════════════════════════════════╣"
	@$(SIZE) $(BUILD_DIR)/$(TARGET).elf | awk -v flash_kb=$(FLASH_TOTAL_KB) -v ram_kb=$(RAM_TOTAL_KB) '\
	NR==2 { \
		text = $$1; data = $$2; bss = $$3; \
		flash_used = text + data; \
		ram_used = data + bss; \
		flash_pct = (flash_used / (flash_kb * 1024)) * 100; \
		ram_pct = (ram_used / (ram_kb * 1024)) * 100; \
		\
		printf("║         %-5s (%2d kB)       ║        %-3s (%2d kB)         ║\n", \
			   "Flash", flash_kb, \
			   "RAM", ram_kb); \
		printf("╠═════════════════════════════║════════════════════════════╣\n"); \
		printf("║ %-7s %5.2f kB            ║ %-7s %5.2f kB           ║\n", \
			   "Text", text/1024, \
			   "BSS", bss/1024); \
		printf("║ %-7s %5.2f kB            ║ %-7s %5.2f kB           ║\n", \
			   "Data", data/1024, \
			   "Data", data/1024); \
		printf("║═════════════════════════════║════════════════════════════║\n"); \
		printf("║ %-7s %5.2f kB (%5.2f %)  ║ %-7s %5.2f kB (%5.2f %) ║\n", \
			   "Total", flash_used/1024, flash_pct, \
			   "Total", ram_used/1024, ram_pct); \
		printf("╚═════════════════════════════╩════════════════════════════╝\n"); \
		if (flash_pct > 90.0) \
			print "\033[1;31m⚠ FLASH usage exceeds 90%\033[0m"; \
		if (ram_pct > 80.0) \
			print "\033[1;31m⚠ RAM usage exceeds 80%\033[0m"; \
	}'
	@echo "\033[0m"
endef
# ---------------------- Dynamic Dependency Resolution ----------------------
# This rule extracts dependencies and stores them in dependency.mk inside Build/
dependency:
	@echo "\033[1;36m============================== Resolving Dependencies ==============================\033[0m"
	$(eval DEPENDENCY_OUTPUT := $(shell $(CC) $(INCLUDES) -M -MF - -MG -MM $(shell pwd)/Src/main.c))
	$(eval DEPENDENCY_HEADERS := $(filter %.h, $(subst \,,$(wordlist 2,999,$(DEPENDENCY_OUTPUT)))))
	$(eval DRIVER_SRCS := $(sort $(foreach hdr, $(DEPENDENCY_HEADERS), \
		$(if $(findstring $(DRIVER_BASE),$(hdr)), \
			$(wildcard $(subst /Inc/,/Src/,$(dir $(hdr)))*.c), \
		))))
	$(eval LOCAL_DEP_SRCS := $(sort $(foreach hdr, $(DEPENDENCY_HEADERS), \
		$(if $(findstring $(shell pwd)/Inc,$(hdr)), \
			$(wildcard $(shell pwd)/Src/*.c), \
		))))
	$(eval STARTUP_SRCS := $(wildcard $(shell pwd)/Startup/*.c))
	$(eval SRCS := $(DRIVER_SRCS) $(LOCAL_DEP_SRCS) $(STARTUP_SRCS))
	$(eval OBJS := $(addprefix $(BUILD_DIR)/,$(notdir $(SRCS:%.c=%.o))))
	$(eval vpath %.c $(sort $(dir $(SRCS))))

	@mkdir -p $(BUILD_DIR)
	@echo "SRCS := $(SRCS)" > $(DEPENDENCY_FILE)
	@echo "OBJS := $(OBJS)" >> $(DEPENDENCY_FILE)
	@echo "vpath %.c $(sort $(dir $(SRCS)))" >> $(DEPENDENCY_FILE)

	@echo "\033[1;33m→ Driver Sources:\033[0m"
	@echo "$(DRIVER_SRCS)" | tr ' ' '\n' | sed 's/^/   - /'

	@echo "\033[1;33m→ Local Sources:\033[0m"
	@echo "$(LOCAL_DEP_SRCS)" | tr ' ' '\n' | sed 's/^/   - /'

	@echo "\033[1;33m→ Startup Sources:\033[0m"
	@echo "$(STARTUP_SRCS)" | tr ' ' '\n' | sed 's/^/   - /'

	@echo "\033[1;32m✔ Final Source List:\033[0m"
	@echo "$(SRCS)" | tr ' ' '\n' | sed 's/^/   - /'
	@echo "\033[1;36m=====================================================================================\033[0m"


# ---------------------- Main Targets ----------------------
# Full Build Flow
all:
	@$(MAKE) dependency
	@$(MAKE) build

# ---------------------- Build Target (Post Dependency Resolution) ----------------------
build: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET).bin
	@echo "\033[1;35m╔══════════════════════════════════════════════════════════╗\033[0m"
	@echo "\033[1;35m║               🔥 Compiling Project 🔥                    ║\033[0m"
	@echo "\033[1;35m╚══════════════════════════════════════════════════════════╝\033[0m"
	@$(memory_report)
	@echo "\033[1;35m╔══════════════════════════════════════════════════════════╗\033[0m"
	@echo "\033[1;35m║\033[0m               🔥 \033[1;33mProject Compiled\033[0m 🔥                     \033[1;35m║\033[0m"
	@echo "\033[1;35m║\033[0m ✔✔✔ \033[1;32mBuild Completed Successfully!\033[0m                        \033[1;35m║\033[0m"
	@echo "\033[1;35m║\033[0m 💡 \033[1;34mFlash your binary with: make flash\033[0m                    \033[1;35m║\033[0m"
	@echo "\033[1;35m╚══════════════════════════════════════════════════════════╝\033[0m"

# Flash Binary to MCU
flash: all
	@echo "\033[1;34m╔══════════════════════════════════════════════════════════╗\033[0m"
	@echo "\033[1;34m║\033[0m         🚀 \033[1;36mFlashing Binary to STM32 MCU\033[0m 🚀               \033[1;34m║\033[0m"
	@echo "\033[1;34m╚══════════════════════════════════════════════════════════╝\033[0m"
	st-flash --reset write $(BUILD_DIR)/$(TARGET).bin 0x08000000
	@echo "\033[1;35m╔══════════════════════════════════════════════════════════╗\033[0m"
	@echo "\033[1;35m║           🎯 Your binary is now on the STM32 MCU!        ║\033[0m"
	@echo "\033[1;35m╚══════════════════════════════════════════════════════════╝\033[0m"

# ---------------------- Clean Target ----------------------
clean:
	@rm -r $(BUILD_DIR) || true
	@rm -r ./.vscode || true
	@echo "\033[1;35m╔══════════════════════════════════════════════════════════╗\033[0m"
	@echo "\033[1;35m║                    🧹 Project Cleaned                    ║\033[0m"
	@echo "\033[1;35m║      \033[1;32m✔✔✔ Build files and VSCode configs removed ✔✔✔\033[0m      \033[1;35m║\033[0m"
	@echo "\033[1;35m╚══════════════════════════════════════════════════════════╝\033[0m"

# ST-Link Information
info:
	@echo "\033[1;36m╔══════════════════════════════════════════════════════════╗\033[0m"
	@echo "\033[1;36m║\033[0m             🔍 \033[1;33mST-Link Debug Probe Info\033[0m                  \033[1;36m║\033[0m"
	@echo "\033[1;36m╠══════════════════════════════════════════════════════════╣\033[0m"
	@st-info --probe | sed 's/^ *//' | awk '{ printf("\033[1;36m║ %-56s ║\033[0m\n", $$0) }'
	@echo "\033[1;36m╚══════════════════════════════════════════════════════════╝\033[0m"

# Flash Clean Project
erase_flash: clean
	st-flash erase
	@echo "\033[1;35m╔══════════════════════════════════════════════════════════╗\033[0m"
	@echo "\033[1;35m║\033[0m              💥 \033[1;33mFlash Erased Successfully!\033[0m 💥            \033[1;35m║\033[0m"
	@echo "\033[1;35m║            \033[0m ✔✔✔ \033[1;32mMCU Flash memory wiped clean\033[0m             \033[1;35m║\033[0m"
	@echo "\033[1;35m║            \033[0m 💡 \033[1;34mReady to program with: make flash\033[0m         \033[1;35m║\033[0m"
	@echo "\033[1;35m╚══════════════════════════════════════════════════════════╝\033[0m"

# Debug
debug: $(BUILD_DIR)/$(TARGET).elf vscode_files all
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
# 	@printf '{\n  "version": "0.2.0",\n  "configurations": [\n    {\n      "name": "Debug: $(notdir $(shell pwd))",\n      "executable": "$(BUILD_DIR)/$(TARGET).elf",\n      "request": "launch",\n      "type": "cortex-debug",\n      "servertype": "openocd",\n      "device": "STM32F103C8",\n      "configFiles": [\n        "$(ROOT_DIR)/BareMetal/Core/Src/stlink.cfg",\n        "$(ROOT_DIR)/BareMetal/Core/Src/stm32f1x.cfg"\n      ],\n      "svdFile": "$(ROOT_DIR)/BareMetal/Core/Src/STM32F103.svd",\n      "runToEntryPoint": "Reset_Handler",\n      "preLaunchTask": "Build Project"\n    }\n  ]\n}' > .vscode/launch.json

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

# Dependency Files
get_dependency:
	$(CC) $(INCLUDES) -M -MF - -MG -MM $(shell pwd)/Src/main.c

# ---------------------- Dependency Inclusion ----------------------
-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all build flash clean resolve_dependency