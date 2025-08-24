# Generate launch.json
file(WRITE ${PROJ_DIR}/.vscode/launch.json
"{
  \"version\": \"0.2.0\",
  \"configurations\": [
	{
	  \"name\": \"Debug: ${PROJECT_NAME}\",
	  \"executable\": \"${BUILD_OUTPUT_DIR}/${PROJECT_NAME}.elf\",
	  \"request\": \"launch\",
	  \"type\": \"cortex-debug\",
	  \"servertype\": \"openocd\",
	  \"device\": \"STM32F103C8\",
	  \"configFiles\": [
		\"${CORE_ROOT}/Src/stlink.cfg\",
		\"${CORE_ROOT}/Src/stm32f1x.cfg\"
	  ],
	  \"svdFile\": \"${CORE_ROOT}/Src/STM32F103.svd\",
	  \"runToEntryPoint\": \"main\",
	  \"preLaunchTask\": \"Build Project\"
	}
  ]
}")

# Generate settings.json
file(WRITE ${PROJ_DIR}/.vscode/settings.json
"{
	\"cortex-debug.gdbPath\": \"/usr/bin/gdb-multiarch\",
	\"cortex-debug.openocdPath\": \"/usr/local/bin/openocd\",
	\"cortex-debug.stutilPath\": \"/usr/bin/st-util\",
	\"cortex-debug.variableUseNaturalFormat\": false
}")

# Generate tasks.json
file(WRITE ${PROJ_DIR}/.vscode/tasks.json
"{
	\"version\": \"2.0.0\",
	\"tasks\": [
		{
			\"label\": \"Build Project\",
			\"type\": \"shell\",
			\"command\": \"cmake\",
			\"args\": [\"--build\", \"Build\"],
			\"group\": {
				\"kind\": \"build\",
				\"isDefault\": true
			},
			\"problemMatcher\": [\"$gcc\"],
			\"detail\": \"Build the current project using CMake\"
		},
		{
			\"label\": \"Clean Project\",
			\"type\": \"shell\",
			\"command\": \"cmake\",
			\"args\": [\"--build\", \"Build\", \"--target\", \"clean_all\"],
			\"group\": \"build\",
			\"problemMatcher\": [],
			\"detail\": \"Clean the build directory\"
		}
	]
}")

# Generate c_cpp_properties.json
file(WRITE ${PROJ_DIR}/.vscode/c_cpp_properties.json
"{
	\"configurations\": [
		{
			\"name\": \"Linux\",
			\"includePath\": [
				\"${CORE_ROOT}/Inc/**\",
				\"${DRIVER_ROOT}/*/Inc/**\",
				\"${PROJ_DIR}/Inc/**\"
			],
			\"defines\": [\"STM32F103C8T6\"],
			\"compilerPath\": \"/usr/bin/arm-none-eabi-gcc\",
			\"cStandard\": \"c11\",
			\"cppStandard\": \"gnu++17\",
			\"intelliSenseMode\": \"linux-gcc-arm\"
		}
	],
	\"version\": 4
}")