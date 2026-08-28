include_guard(GLOBAL)

# This module converts the requested Driver names into target-owned components.
# Applications retain the compact DRIVER_MODULES interface while every Core and
# Driver target owns its sources, include directories, and direct dependencies.

# Direct Driver dependencies form one downward build graph. Transitive modules
# are resolved automatically, so an application selects capabilities instead of
# repeating the implementation dependencies of each capability. BSP exposes
# independently selectable GPIO, USART, and Timer capability targets because
# their hardware requirements differ. The aggregate BSP component remains
# available for compatibility and deliberately selects every capability.
set(STM32_DRIVER_ADC_DEPENDENCIES GPIO)
set(STM32_DRIVER_BSP_DEPENDENCIES BSP_GPIO BSP_USART BSP_TIMER)
set(STM32_DRIVER_BSP_SOURCES "")
set(STM32_DRIVER_BSP_GPIO_DIRECTORY BSP)
set(STM32_DRIVER_BSP_GPIO_DEPENDENCIES GPIO)
set(STM32_DRIVER_BSP_GPIO_SOURCES Src/bsp_gpio.c)
set(STM32_DRIVER_BSP_GPIO_COMPILE_DEFINITIONS BSP_GPIO_CAPABILITY_ENABLED=1)
set(STM32_DRIVER_BSP_USART_DIRECTORY BSP)
set(STM32_DRIVER_BSP_USART_DEPENDENCIES GPIO USART)
set(STM32_DRIVER_BSP_USART_SOURCES Src/bsp_usart.c)
set(STM32_DRIVER_BSP_USART_COMPILE_DEFINITIONS BSP_USART_CAPABILITY_ENABLED=1)
set(STM32_DRIVER_BSP_TIMER_DIRECTORY BSP)
set(STM32_DRIVER_BSP_TIMER_DEPENDENCIES Timer)
set(STM32_DRIVER_BSP_TIMER_SOURCES Src/bsp_timer.c)
set(STM32_DRIVER_BSP_TIMER_COMPILE_DEFINITIONS BSP_TIMER_CAPABILITY_ENABLED=1)
set(STM32_DRIVER_DMA_DEPENDENCIES "")
set(STM32_DRIVER_GPIO_DEPENDENCIES RCC)
set(STM32_DRIVER_I2C_DEPENDENCIES RCC)
set(STM32_DRIVER_NVIC_DEPENDENCIES "")
set(STM32_DRIVER_RCC_DEPENDENCIES "")
set(STM32_DRIVER_Ring_Buffer_DEPENDENCIES "")
set(STM32_DRIVER_SSD1306_DEPENDENCIES I2C Ring_Buffer)
set(STM32_DRIVER_SysTick_DEPENDENCIES "")
set(STM32_DRIVER_Timer_DEPENDENCIES RCC)
set(STM32_DRIVER_USART_DEPENDENCIES RCC GPIO)

function(stm32_get_driver_module_directory module_name output_variable)
    set(module_directory_name "${module_name}")
    set(module_directory_variable "STM32_DRIVER_${module_name}_DIRECTORY")

    # A capability target may own sources under an established Driver directory
    # without duplicating public headers or creating a synthetic Driver folder.
    if(DEFINED ${module_directory_variable})
        set(module_directory_name "${${module_directory_variable}}")
    endif()

    set(${output_variable} "${DRIVER_ROOT}/${module_directory_name}" PARENT_SCOPE)
endfunction()

function(stm32_tree_emit_line prefix is_last label)
    if(is_last)
        message(STATUS "${prefix}└── ${label}")
    else()
        message(STATUS "${prefix}├── ${label}")
    endif()
endfunction()

function(stm32_resolve_driver_modules output_variable)
    set(resolved_modules ${DRIVER_MODULES})
    set(module_index 0)
    list(LENGTH resolved_modules module_count)

    # Process appended dependencies in the same loop until the complete
    # transitive closure is known. list(FIND) preserves first-requested order.
    while(module_index LESS module_count)
        list(GET resolved_modules ${module_index} module_name)
        stm32_get_driver_module_directory("${module_name}" module_directory)
        if(NOT IS_DIRECTORY "${module_directory}")
            message(FATAL_ERROR "Unknown Driver module '${module_name}': ${module_directory}")
        endif()

        set(dependency_variable "STM32_DRIVER_${module_name}_DEPENDENCIES")
        foreach(dependency_name IN LISTS ${dependency_variable})
            list(FIND resolved_modules "${dependency_name}" dependency_index)
            if(dependency_index EQUAL -1)
                list(APPEND resolved_modules "${dependency_name}")
            endif()
        endforeach()

        math(EXPR module_index "${module_index} + 1")
        list(LENGTH resolved_modules module_count)
    endwhile()

    set(${output_variable} "${resolved_modules}" PARENT_SCOPE)
endfunction()

function(stm32_register_core_target)
    file(GLOB_RECURSE core_headers CONFIGURE_DEPENDS
        "${CORE_ROOT}/Inc/*.h"
        "${CORE_ROOT}/Inc/*.hpp"
        "${CORE_ROOT}/Inc/*.hxx"
    )
    file(GLOB_RECURSE core_sources CONFIGURE_DEPENDS
        "${CORE_ROOT}/Src/*.c"
        "${CORE_ROOT}/Src/*.cpp"
        "${CORE_ROOT}/Src/*.cxx"
        "${CORE_ROOT}/Src/*.s"
        "${CORE_ROOT}/Src/*.S"
    )
    list(SORT core_headers)
    list(SORT core_sources)

    # Core is currently header-only, but the OBJECT/INTERFACE split allows a
    # future shared Core source to remain owned by this same stable target.
    if(core_sources)
        add_library(stm32_core OBJECT ${core_sources})
        target_include_directories(stm32_core PUBLIC "${CORE_ROOT}/Inc")
        target_link_libraries(stm32_core PUBLIC stm32::build_options)
    else()
        add_library(stm32_core INTERFACE)
        target_include_directories(stm32_core INTERFACE "${CORE_ROOT}/Inc")
        target_link_libraries(stm32_core INTERFACE stm32::build_options)
    endif()
    add_library(stm32::core ALIAS stm32_core)

    set(CORE_HEADERS "${core_headers}" PARENT_SCOPE)
    set(CORE_SOURCES "${core_sources}" PARENT_SCOPE)
endfunction()

function(stm32_print_file_tree module_name module_index module_count module_headers module_sources)
    if(module_index EQUAL module_count)
        set(module_is_last TRUE)
        set(module_child_prefix "    ")
    else()
        set(module_is_last FALSE)
        set(module_child_prefix "│   ")
    endif()

    stm32_tree_emit_line("  " ${module_is_last} "${module_name}")

    set(section_names Inc Src)
    foreach(section_name IN LISTS section_names)
        if(section_name STREQUAL "Inc")
            set(section_items ${module_headers})
            set(section_is_last FALSE)
        else()
            set(section_items ${module_sources})
            set(section_is_last TRUE)
        endif()

        stm32_tree_emit_line("  ${module_child_prefix}" ${section_is_last} "${section_name}")
        if(section_is_last)
            set(item_prefix "  ${module_child_prefix}    ")
        else()
            set(item_prefix "  ${module_child_prefix}│   ")
        endif()

        if(section_items)
            list(LENGTH section_items section_item_count)
            set(section_item_index 0)
            foreach(item IN LISTS section_items)
                math(EXPR section_item_index "${section_item_index} + 1")
                if(DRIVER_MODULE_TREE STREQUAL "SHOW_FULL_PATH")
                    set(display_item "${item}")
                else()
                    get_filename_component(display_item "${item}" NAME)
                endif()

                if(section_item_index EQUAL section_item_count)
                    set(item_is_last TRUE)
                else()
                    set(item_is_last FALSE)
                endif()
                stm32_tree_emit_line("${item_prefix}" ${item_is_last} "${display_item}")
            endforeach()
        else()
            stm32_tree_emit_line("${item_prefix}" TRUE "<none>")
        endif()
    endforeach()
endfunction()

function(stm32_print_local_tree local_headers local_sources)
    set(section_names Inc Src)
    foreach(section_name IN LISTS section_names)
        if(section_name STREQUAL "Inc")
            set(section_items ${local_headers})
            set(section_is_last FALSE)
            set(item_prefix "  │   ")
        else()
            set(section_items ${local_sources})
            set(section_is_last TRUE)
            set(item_prefix "      ")
        endif()

        stm32_tree_emit_line("  " ${section_is_last} "${section_name}")

        if(section_items)
            list(LENGTH section_items section_item_count)
            set(section_item_index 0)
            foreach(item IN LISTS section_items)
                math(EXPR section_item_index "${section_item_index} + 1")
                if(DRIVER_MODULE_TREE STREQUAL "SHOW_FULL_PATH")
                    set(display_item "${item}")
                else()
                    get_filename_component(display_item "${item}" NAME)
                endif()

                if(section_item_index EQUAL section_item_count)
                    set(item_is_last TRUE)
                else()
                    set(item_is_last FALSE)
                endif()
                stm32_tree_emit_line("${item_prefix}" ${item_is_last} "${display_item}")
            endforeach()
        else()
            stm32_tree_emit_line("${item_prefix}" TRUE "<none>")
        endif()
    endforeach()
endfunction()

function(stm32_register_driver_targets)
    stm32_resolve_driver_modules(resolved_driver_modules)
    set(selected_driver_headers "")
    set(selected_driver_sources "")
    set(selected_driver_includes "")
    set(selected_driver_targets "")

    stm32_join_list(requested_driver_text ${DRIVER_MODULES})
    stm32_join_list(resolved_driver_text ${resolved_driver_modules})
    list(LENGTH resolved_driver_modules module_count)
    stm32_print_section("Driver Modules")
    stm32_print_kv("Requested" "${requested_driver_text}")
    stm32_print_kv("Resolved" "${resolved_driver_text}")
    stm32_print_kv("Module Count" "${module_count}")

    set(module_index 0)
    foreach(module_name IN LISTS resolved_driver_modules)
        math(EXPR module_index "${module_index} + 1")
        stm32_get_driver_module_directory("${module_name}" module_directory)
        set(module_include_directory "${module_directory}/Inc")
        set(module_target "stm32_driver_${module_name}")

        file(GLOB module_headers CONFIGURE_DEPENDS "${module_include_directory}/*.h")
        set(module_sources "")
        set(module_sources_variable "STM32_DRIVER_${module_name}_SOURCES")
        if(DEFINED ${module_sources_variable})
            foreach(module_source_relative_path IN LISTS ${module_sources_variable})
                set(module_source_path "${module_directory}/${module_source_relative_path}")
                if(NOT EXISTS "${module_source_path}")
                    message(FATAL_ERROR "Driver source for '${module_name}' does not exist: ${module_source_path}")
                endif()
                list(APPEND module_sources "${module_source_path}")
            endforeach()
        else()
            file(GLOB module_sources CONFIGURE_DEPENDS
                "${module_directory}/Src/*.c"
                "${module_directory}/Src/*.cpp"
                "${module_directory}/Src/*.cxx"
                "${module_directory}/Src/*.s"
                "${module_directory}/Src/*.S"
            )
        endif()
        list(SORT module_headers)
        list(SORT module_sources)

        # A component with sources becomes an OBJECT library so every selected
        # object reaches the firmware link. Header-only components retain the
        # same usage contract through an INTERFACE library.
        if(module_sources)
            add_library(${module_target} OBJECT ${module_sources})
            target_link_libraries(${module_target} PUBLIC stm32::core)
            if(IS_DIRECTORY "${module_include_directory}")
                target_include_directories(${module_target} PUBLIC "${module_include_directory}")
            endif()
        else()
            add_library(${module_target} INTERFACE)
            target_link_libraries(${module_target} INTERFACE stm32::core)
            if(IS_DIRECTORY "${module_include_directory}")
                target_include_directories(${module_target} INTERFACE "${module_include_directory}")
            endif()
        endif()

        # Capability-owned public headers may expose only the API families that
        # the selected component actually links. This is a build-component
        # contract, never an application feature macro consumed by BSP code.
        set(module_compile_definitions_variable "STM32_DRIVER_${module_name}_COMPILE_DEFINITIONS")
        if(DEFINED ${module_compile_definitions_variable})
            get_target_property(module_target_type ${module_target} TYPE)
            if(module_target_type STREQUAL "INTERFACE_LIBRARY")
                target_compile_definitions(${module_target} INTERFACE ${${module_compile_definitions_variable}})
            else()
                target_compile_definitions(${module_target} PUBLIC ${${module_compile_definitions_variable}})
            endif()
        endif()
        add_library(stm32::driver::${module_name} ALIAS ${module_target})

        list(APPEND selected_driver_targets ${module_target})
        list(APPEND selected_driver_headers ${module_headers})
        list(APPEND selected_driver_sources ${module_sources})
        if(IS_DIRECTORY "${module_include_directory}")
            list(APPEND selected_driver_includes "${module_include_directory}")
        endif()

        stm32_print_file_tree(
            "${module_name}"
            ${module_index}
            ${module_count}
            "${module_headers}"
            "${module_sources}"
        )
    endforeach()

    # Attach direct component relationships after all targets exist. The final
    # executable links every resolved target directly, so dependency objects and
    # their transitive include requirements are both retained exactly once.
    foreach(module_name IN LISTS resolved_driver_modules)
        set(module_target "stm32_driver_${module_name}")
        set(dependency_variable "STM32_DRIVER_${module_name}_DEPENDENCIES")
        get_target_property(module_target_type ${module_target} TYPE)
        foreach(dependency_name IN LISTS ${dependency_variable})
            if(module_target_type STREQUAL "INTERFACE_LIBRARY")
                target_link_libraries(${module_target} INTERFACE stm32_driver_${dependency_name})
            else()
                target_link_libraries(${module_target} PUBLIC stm32_driver_${dependency_name})
            endif()
        endforeach()
    endforeach()

    # Capability modules can share one physical include directory. Keep the
    # summary file/path counts unique even though each capability tree remains
    # explicit about the interface it exposes.
    list(REMOVE_DUPLICATES selected_driver_headers)
    list(REMOVE_DUPLICATES selected_driver_sources)
    list(REMOVE_DUPLICATES selected_driver_includes)
    list(SORT selected_driver_headers)
    list(SORT selected_driver_sources)
    list(SORT selected_driver_includes)

    set(RESOLVED_DRIVER_MODULES "${resolved_driver_modules}" PARENT_SCOPE)
    set(SELECTED_DRIVER_TARGETS "${selected_driver_targets}" PARENT_SCOPE)
    set(SELECTED_DRIVER_HEADERS "${selected_driver_headers}" PARENT_SCOPE)
    set(SELECTED_DRIVER_SOURCES "${selected_driver_sources}" PARENT_SCOPE)
    set(SELECTED_DRIVER_INCLUDES "${selected_driver_includes}" PARENT_SCOPE)
endfunction()

function(stm32_collect_sources)
    file(GLOB_RECURSE project_headers CONFIGURE_DEPENDS
        "${PROJ_DIR}/Inc/*.h"
        "${PROJ_DIR}/Inc/*.hpp"
        "${PROJ_DIR}/Inc/*.hxx"
    )
    file(GLOB_RECURSE project_sources CONFIGURE_DEPENDS
        "${PROJ_DIR}/Src/*.c"
        "${PROJ_DIR}/Src/*.cpp"
        "${PROJ_DIR}/Src/*.cxx"
        "${PROJ_DIR}/Src/*.s"
        "${PROJ_DIR}/Src/*.S"
    )
    if(NOT project_sources)
        message(FATAL_ERROR "No application sources found under ${PROJ_DIR}/Src")
    endif()
    list(SORT project_headers)
    list(SORT project_sources)

    set(PROJECT_HEADERS "${project_headers}")
    set(PROJECT_SOURCES "${project_sources}")

    stm32_print_section("Local")
    stm32_print_local_tree("${PROJECT_HEADERS}" "${PROJECT_SOURCES}")

    stm32_register_core_target()
    stm32_register_driver_targets()
    stm32_print_source_summary()

    set(PROJECT_HEADERS "${PROJECT_HEADERS}" PARENT_SCOPE)
    set(PROJECT_SOURCES "${PROJECT_SOURCES}" PARENT_SCOPE)
    set(CORE_HEADERS "${CORE_HEADERS}" PARENT_SCOPE)
    set(CORE_SOURCES "${CORE_SOURCES}" PARENT_SCOPE)
    set(RESOLVED_DRIVER_MODULES "${RESOLVED_DRIVER_MODULES}" PARENT_SCOPE)
    set(SELECTED_DRIVER_TARGETS "${SELECTED_DRIVER_TARGETS}" PARENT_SCOPE)
    set(SELECTED_DRIVER_HEADERS "${SELECTED_DRIVER_HEADERS}" PARENT_SCOPE)
    set(SELECTED_DRIVER_SOURCES "${SELECTED_DRIVER_SOURCES}" PARENT_SCOPE)
    set(SELECTED_DRIVER_INCLUDES "${SELECTED_DRIVER_INCLUDES}" PARENT_SCOPE)
endfunction()
