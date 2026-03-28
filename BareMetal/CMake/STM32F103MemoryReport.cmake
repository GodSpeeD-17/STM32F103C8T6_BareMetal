if(NOT DEFINED SIZE_TOOL)
    message(FATAL_ERROR "SIZE_TOOL is required")
endif()

if(NOT DEFINED ELF_FILE)
    message(FATAL_ERROR "ELF_FILE is required")
endif()

if(NOT DEFINED PROJECT_LABEL)
    message(FATAL_ERROR "PROJECT_LABEL is required")
endif()

if(NOT DEFINED FLASH_SIZE_BYTES)
    message(FATAL_ERROR "FLASH_SIZE_BYTES is required")
endif()

if(NOT DEFINED RAM_SIZE_BYTES)
    message(FATAL_ERROR "RAM_SIZE_BYTES is required")
endif()

function(stm32_format_kib bytes out_var)
    math(EXPR kib_whole "${bytes} / 1024")
    math(EXPR kib_frac "(${bytes} % 1024) * 100 / 1024")
    if(kib_frac LESS 10)
        set(kib_frac_str "0${kib_frac}")
    else()
        set(kib_frac_str "${kib_frac}")
    endif()
    set(formatted_value "${kib_whole}.${kib_frac_str} KiB")
    set(${out_var} "${formatted_value}" PARENT_SCOPE)
endfunction()

function(stm32_format_percent used total out_var)
    if(total EQUAL 0)
        set(${out_var} "0.00" PARENT_SCOPE)
        return()
    endif()

    math(EXPR percent_x100 "${used} * 10000 / ${total}")
    math(EXPR percent_whole "${percent_x100} / 100")
    math(EXPR percent_frac "${percent_x100} % 100")
    if(percent_frac LESS 10)
        set(percent_frac_str "0${percent_frac}")
    else()
        set(percent_frac_str "${percent_frac}")
    endif()
    set(formatted_value "${percent_whole}.${percent_frac_str}")
    set(${out_var} "${formatted_value}" PARENT_SCOPE)
endfunction()

function(stm32_make_usage_bar used total out_var)
    set(bar_width 28)

    if(total EQUAL 0)
        set(${out_var} "[............................]" PARENT_SCOPE)
        return()
    endif()

    math(EXPR filled "${used} * ${bar_width} / ${total}")
    if(filled GREATER bar_width)
        set(filled ${bar_width})
    endif()
    math(EXPR empty "${bar_width} - ${filled}")

    set(bar "[")
    while(filled GREATER 0)
        string(APPEND bar "#")
        math(EXPR filled "${filled} - 1")
    endwhile()
    while(empty GREATER 0)
        string(APPEND bar ".")
        math(EXPR empty "${empty} - 1")
    endwhile()
    string(APPEND bar "]")

    set(${out_var} "${bar}" PARENT_SCOPE)
endfunction()

execute_process(
    COMMAND "${SIZE_TOOL}" --format=berkeley "${ELF_FILE}"
    OUTPUT_VARIABLE size_output
    ERROR_VARIABLE size_error
    RESULT_VARIABLE size_result
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT size_result EQUAL 0)
    message(FATAL_ERROR "Failed to run size tool:\n${size_error}")
endif()

string(REPLACE "\n" ";" size_lines "${size_output}")
list(LENGTH size_lines size_line_count)
if(size_line_count LESS 2)
    message(FATAL_ERROR "Unexpected size output:\n${size_output}")
endif()

list(GET size_lines 1 size_values_line)
string(REGEX MATCHALL "[0-9]+" size_values "${size_values_line}")
list(LENGTH size_values value_count)
if(value_count LESS 3)
    message(FATAL_ERROR "Unable to parse size output:\n${size_output}")
endif()

list(GET size_values 0 text_size)
list(GET size_values 1 data_size)
list(GET size_values 2 bss_size)

math(EXPR flash_used "${text_size} + ${data_size}")
math(EXPR ram_used "${data_size} + ${bss_size}")
math(EXPR flash_free "${FLASH_SIZE_BYTES} - ${flash_used}")
math(EXPR ram_free "${RAM_SIZE_BYTES} - ${ram_used}")

stm32_format_percent(${flash_used} ${FLASH_SIZE_BYTES} flash_percent)
stm32_format_percent(${ram_used} ${RAM_SIZE_BYTES} ram_percent)
stm32_format_kib(${FLASH_SIZE_BYTES} flash_capacity)
stm32_format_kib(${RAM_SIZE_BYTES} ram_capacity)
stm32_make_usage_bar(${flash_used} ${FLASH_SIZE_BYTES} flash_bar)
stm32_make_usage_bar(${ram_used} ${RAM_SIZE_BYTES} ram_bar)

message(STATUS "")
message(STATUS "+--------------------------------------------------------------------+")
message(STATUS "| Memory Usage: ${PROJECT_LABEL}")
message(STATUS "+--------------------------------------------------------------------+")
message(STATUS "| FLASH | ${flash_bar} | ${flash_percent}% | used ${flash_used} B / ${FLASH_SIZE_BYTES} B")
message(STATUS "|       |                              | free ${flash_free} B   (${flash_capacity})")
message(STATUS "| RAM   | ${ram_bar} | ${ram_percent}% | used ${ram_used} B / ${RAM_SIZE_BYTES} B")
message(STATUS "|       |                              | free ${ram_free} B     (${ram_capacity})")
message(STATUS "|")
message(STATUS "| Sections")
message(STATUS "|   text : ${text_size} B")
message(STATUS "|   data : ${data_size} B")
message(STATUS "|   bss  : ${bss_size} B")
message(STATUS "+--------------------------------------------------------------------+")
