include_guard(GLOBAL)

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

    message(STATUS "====================================================================================")
    message(STATUS "Library")
    message(STATUS "====================================================================================")

    set(selected_driver_sources "")
    set(selected_driver_includes "")

    foreach(module_name IN LISTS module_names)
        set(DRIVER_MODULE_DIR ${DRIVER_ROOT}/${module_name})
        if(EXISTS ${DRIVER_MODULE_DIR})
            file(GLOB module_sources CONFIGURE_DEPENDS ${DRIVER_MODULE_DIR}/Src/*.c)
            list(APPEND selected_driver_sources ${module_sources})

            if(EXISTS ${DRIVER_MODULE_DIR}/Inc)
                list(APPEND selected_driver_includes ${DRIVER_MODULE_DIR}/Inc)
            endif()

            message(STATUS "-- ${module_name}")

            if(EXISTS ${DRIVER_MODULE_DIR}/Inc)
                message(STATUS "   |-- Inc")
                file(GLOB module_headers CONFIGURE_DEPENDS ${DRIVER_MODULE_DIR}/Inc/*.h)
                list(SORT module_headers)
                foreach(hdr IN LISTS module_headers)
                    if(show_full_path)
                        message(STATUS "   |    |-- ${hdr}")
                    else()
                        get_filename_component(filename ${hdr} NAME)
                        message(STATUS "   |    |-- ${filename}")
                    endif()
                endforeach()
                message(STATUS "   |")
            endif()

            if(EXISTS ${DRIVER_MODULE_DIR}/Src)
                message(STATUS "   |-- Src")
                file(GLOB module_sources CONFIGURE_DEPENDS ${DRIVER_MODULE_DIR}/Src/*.c)
                list(SORT module_sources)
                foreach(src IN LISTS module_sources)
                    if(show_full_path)
                        message(STATUS "        |-- ${src}")
                    else()
                        get_filename_component(filename ${src} NAME)
                        message(STATUS "        |-- ${filename}")
                    endif()
                endforeach()
            endif()
        else()
            message(WARNING "Driver module ${module_name} not found at ${DRIVER_MODULE_DIR}")
        endif()
    endforeach()

    message(STATUS "====================================================================================")
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
