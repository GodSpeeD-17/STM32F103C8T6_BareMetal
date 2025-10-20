
file(WRITE /home/shrey_shah/STM32F103C8T6/Projects/GPIO/01_OB_LED/.vscode/tasks.json "{
  \"version\": \"2.0.0\",
  \"tasks\": [
	{
	  \"label\": \"Build Project\",
	  \"type\": \"shell\",
	  \"command\": \"cmake\",
	  \"args\": [\"--build\", \"/home/shrey_shah/STM32F103C8T6/Projects/GPIO/01_OB_LED/Build\"],
	  \"group\": { \"kind\": \"build\", \"isDefault\": true },
	  \"problemMatcher\": [\"\$gcc\"],
	  \"detail\": \"Build the current project using CMake\"
	},
	{
	  \"label\": \"Clean Project\",
	  \"type\": \"shell\",
	  \"command\": \"cmake\",
	  \"args\": [\"--build\", \"/home/shrey_shah/STM32F103C8T6/Projects/GPIO/01_OB_LED/Build\", \"--target\", \"clean_all\"],
	  \"group\": \"build\",
	  \"problemMatcher\": [],
	  \"detail\": \"Clean the build directory\"
	}
  ]
}")
