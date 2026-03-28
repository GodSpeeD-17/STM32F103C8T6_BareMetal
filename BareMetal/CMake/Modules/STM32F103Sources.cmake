include_guard(GLOBAL)

function(stm32_tree_emit_line prefix is_last label)
    if(is_last)
        message(STATUS "${prefix}└── ${label}")
    else()
        message(STATUS "${prefix}├── ${label}")
    endif()
endfunction()

function(add_driver_module)
    set(show_full_path OFF)
    set(module_names "")

    foreach(arg IN LISTS ARGN)
        if(arg STREQUAL "SHOW_FULL_PATH")
            set(show_full_path ON)
        elseif(arg STREQUAL "SHOW_FILENAME_ONLY")
            set(show_full_path OFF)
        else()
            list(APPEND module_names ${arg})
        endif()
    endforeach()

    set(selected_driver_sources "")
    set(selected_driver_includes "")
    list(LENGTH module_names module_count)
    stm32_print_section("Driver Modules")
    stm32_print_kv("Module Count" "${module_count}")

    set(module_index 0)
    list(LENGTH module_names total_modules)

    foreach(module_name IN LISTS module_names)
        math(EXPR module_index "${module_index} + 1")
        set(DRIVER_MODULE_DIR ${DRIVER_ROOT}/${module_name})
        if(EXISTS ${DRIVER_MODULE_DIR})
            file(GLOB module_sources CONFIGURE_DEPENDS ${DRIVER_MODULE_DIR}/Src/*.c)
            list(APPEND selected_driver_sources ${module_sources})

            if(EXISTS ${DRIVER_MODULE_DIR}/Inc)
                list(APPEND selected_driver_includes ${DRIVER_MODULE_DIR}/Inc)
            endif()

            if(module_index EQUAL total_modules)
                set(module_is_last TRUE)
                set(module_child_prefix "    ")
            else()
                set(module_is_last FALSE)
                set(module_child_prefix "│   ")
            endif()

            stm32_tree_emit_line("  " ${module_is_last} "${module_name}")

            if(EXISTS ${DRIVER_MODULE_DIR}/Inc)
                file(GLOB module_headers CONFIGURE_DEPENDS ${DRIVER_MODULE_DIR}/Inc/*.h)
                list(SORT module_headers)
            else()
                set(module_headers "")
            endif()

            if(EXISTS ${DRIVER_MODULE_DIR}/Src)
                file(GLOB module_sources CONFIGURE_DEPENDS ${DRIVER_MODULE_DIR}/Src/*.c)
                list(SORT module_sources)
            else()
                set(module_sources "")
            endif()

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
                        if(show_full_path)
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
        else()
            message(WARNING "Driver module ${module_name} not found at ${DRIVER_MODULE_DIR}")
        endif()
    endforeach()
    set(SELECTED_DRIVER_SOURCES "${selected_driver_sources}" PARENT_SCOPE)
    set(SELECTED_DRIVER_INCLUDES "${selected_driver_includes}" PARENT_SCOPE)
endfunction()

function(stm32_collect_sources)
    set(SELECTED_DRIVER_SOURCES "")
    set(SELECTED_DRIVER_INCLUDES "")

    add_driver_module(
        ${DRIVER_MODULE_TREE}
        ${DRIVER_MODULES}
    )

    file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${PROJ_DIR}/Src/*.c")
    file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS "${CORE_ROOT}/Src/*.c")
    set(ALL_SOURCE_FILES
        ${PROJECT_SOURCES}
        ${SELECTED_DRIVER_SOURCES}
        ${CORE_SOURCES}
    )

    stm32_print_source_summary()

    set(PROJECT_SOURCES "${PROJECT_SOURCES}" PARENT_SCOPE)
    set(CORE_SOURCES "${CORE_SOURCES}" PARENT_SCOPE)
    set(SELECTED_DRIVER_SOURCES "${SELECTED_DRIVER_SOURCES}" PARENT_SCOPE)
    set(SELECTED_DRIVER_INCLUDES "${SELECTED_DRIVER_INCLUDES}" PARENT_SCOPE)
    set(ALL_SOURCE_FILES "${ALL_SOURCE_FILES}" PARENT_SCOPE)
endfunction()
