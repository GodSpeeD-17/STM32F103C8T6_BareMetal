
file(WRITE /home/shrey_shah/STM32F103C8T6/Projects/GPIO/01_OB_LED/.vscode/launch.json "{
  \"version\": \"0.2.0\",
  \"configurations\": [
	{
	  \"name\": \"Debug: 01_OB_LED\",
	  \"executable\": \"/home/shrey_shah/STM32F103C8T6/Projects/GPIO/01_OB_LED/Build/01_OB_LED.elf\",
	  \"request\": \"launch\",
	  \"type\": \"cortex-debug\",
	  \"servertype\": \"openocd\",
	  \"device\": \"STM32F103C8\",
	  \"configFiles\": [
		\"/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Src/stlink.cfg\",
		\"/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Src/stm32f1x.cfg\"
	  ],
	  \"svdFile\": \"/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Src/stm32f103c8t6.svd\",
	  \"runToEntryPoint\": \"main\", // Entry point is main
	  // \"runToEntryPoint\": \"Reset_Handler\", // Entry point is Reset_Handler
	  \"preLaunchTask\": \"Build Project\"
	}
  ]
}")
