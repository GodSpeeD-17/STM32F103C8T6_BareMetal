include_guard(GLOBAL)

# Shared STM32 build pipeline entrypoint.
# Projects are expected to populate paths/options first via
# `stm32f103_configure_project()`, then this file wires together the
# validation, diagnostics, source discovery, and target creation steps.

include("${CMAKE_ROOT}/STM32F103Diagnostics.cmake")
include("${CMAKE_ROOT}/Modules/STM32F103Validation.cmake")
include("${CMAKE_ROOT}/Modules/STM32F103Tooling.cmake")
include("${CMAKE_ROOT}/Modules/STM32F103Flags.cmake")
include("${CMAKE_ROOT}/Modules/STM32F103Paths.cmake")
include("${CMAKE_ROOT}/Modules/STM32F103Sources.cmake")
include("${CMAKE_ROOT}/Modules/STM32F103Targets.cmake")
include("${CMAKE_ROOT}/Modules/STM32F103UtilityTargets.cmake")

# Keep the configure flow explicit: validate inputs first, then derive
# tool/flag/output state, then collect sources and register targets.
stm32_validate_project_inputs()
stm32_apply_project_defaults()
stm32_print_path_summary()
stm32_configure_host_tools()
stm32_configure_build_flags()
stm32_configure_output_paths()
stm32_print_configuration_summary()
stm32_collect_sources()
stm32_add_firmware_target()
stm32_add_vscode_targets()
stm32_add_flash_targets()
stm32_add_maintenance_targets()
