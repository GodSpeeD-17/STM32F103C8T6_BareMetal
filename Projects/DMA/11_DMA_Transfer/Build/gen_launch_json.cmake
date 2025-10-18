
file(WRITE /home/shrey_shah/STM32F103C8T6_BareMetal/Projects/DMA/11_DMA_Transfer/.vscode/launch.json "{
  \"version\": \"0.2.0\",
  \"configurations\": [
	{
	  \"name\": \"Debug: 11_DMA_Transfer\",
	  \"executable\": \"/home/shrey_shah/STM32F103C8T6_BareMetal/Projects/DMA/11_DMA_Transfer/Build/11_DMA_Transfer.elf\",
	  \"request\": \"launch\",
	  \"type\": \"cortex-debug\",
	  \"servertype\": \"openocd\",
	  \"device\": \"STM32F103C8\",
	  \"configFiles\": [
		\"/home/shrey_shah/STM32F103C8T6_BareMetal/BareMetal/Core/Src/stlink.cfg\",
		\"/home/shrey_shah/STM32F103C8T6_BareMetal/BareMetal/Core/Src/stm32f1x.cfg\"
	  ],
	  \"svdFile\": \"/home/shrey_shah/STM32F103C8T6_BareMetal/BareMetal/Core/Src/stm32f103c8t6.svd\",
	  \"runToEntryPoint\": \"main\", // Entry point is main
	  // \"runToEntryPoint\": \"Reset_Handler\", // Entry point is Reset_Handler
	  \"preLaunchTask\": \"Build Project\"
	}
  ]
}")
