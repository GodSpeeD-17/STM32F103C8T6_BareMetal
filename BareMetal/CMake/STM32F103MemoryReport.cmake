#
# Post-build memory reporter for the ELF artifact.
# It parses `arm-none-eabi-size --format=berkeley` output and renders a
# structured terminal summary that separates region usage from section roles.
#

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
    # Keep the numeric KiB value deterministic so it can be paired with the
    # exact byte count in one self-contained table cell.
    math(EXPR kib_whole "${bytes} / 1024")
    math(EXPR kib_frac "(${bytes} % 1024) * 100 / 1024")
    if(kib_frac LESS 10)
        set(kib_frac_str "0${kib_frac}")
    else()
        set(kib_frac_str "${kib_frac}")
    endif()
    set(formatted_value "${kib_whole}.${kib_frac_str}")
    set(${out_var} "${formatted_value}" PARENT_SCOPE)
endfunction()

function(stm32_format_percent used total out_var)
    # CMake integer math only supports whole numbers, so percentages are
    # computed as x100 and then split into integer/fractional parts.
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

function(stm32_format_integer value out_var)
    # Group decimal digits from the right so byte counts remain quickly
    # scannable without altering the exact integer value.
    set(formatted_value "")
    string(LENGTH "${value}" value_length)
    set(digit_index 0)
    while(digit_index LESS value_length)
        if(digit_index GREATER 0)
            math(EXPR remaining_digits "${value_length} - ${digit_index}")
            math(EXPR group_remainder "${remaining_digits} % 3")
            if(group_remainder EQUAL 0)
                string(APPEND formatted_value ",")
            endif()
        endif()

        string(SUBSTRING "${value}" ${digit_index} 1 digit)
        string(APPEND formatted_value "${digit}")
        math(EXPR digit_index "${digit_index} + 1")
    endwhile()
    set(${out_var} "${formatted_value}" PARENT_SCOPE)
endfunction()

function(stm32_pad_right input width out_var)
    set(result "${input}")
    string(LENGTH "${result}" result_length)
    math(EXPR pad_count "${width} - ${result_length}")
    while(pad_count GREATER 0)
        string(APPEND result " ")
        math(EXPR pad_count "${pad_count} - 1")
    endwhile()
    set(${out_var} "${result}" PARENT_SCOPE)
endfunction()

function(stm32_pad_left input width out_var)
    set(result "${input}")
    string(LENGTH "${result}" result_length)
    math(EXPR pad_count "${width} - ${result_length}")
    set(prefix "")
    while(pad_count GREATER 0)
        string(APPEND prefix " ")
        math(EXPR pad_count "${pad_count} - 1")
    endwhile()
    set(${out_var} "${prefix}${result}" PARENT_SCOPE)
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

# GNU size's Berkeley `text` category contributes the FLASH-resident code and
# read-only payload. Its `data` category contributes both a FLASH load image and
# a RAM runtime image, while `bss` contributes only zero-initialized RAM.
math(EXPR flash_used "${text_size} + ${data_size}")
math(EXPR ram_used "${data_size} + ${bss_size}")
math(EXPR flash_free "${FLASH_SIZE_BYTES} - ${flash_used}")
math(EXPR ram_free "${RAM_SIZE_BYTES} - ${ram_used}")
if(flash_free LESS 0)
    set(flash_free 0)
endif()
if(ram_free LESS 0)
    set(ram_free 0)
endif()

stm32_format_percent(${flash_used} ${FLASH_SIZE_BYTES} flash_percent)
stm32_format_percent(${ram_used} ${RAM_SIZE_BYTES} ram_percent)
stm32_format_kib(${flash_used} flash_used_kib)
stm32_format_kib(${ram_used} ram_used_kib)
stm32_format_kib(${flash_free} flash_free_kib)
stm32_format_kib(${ram_free} ram_free_kib)
stm32_format_kib(${FLASH_SIZE_BYTES} flash_capacity)
stm32_format_kib(${RAM_SIZE_BYTES} ram_capacity)
stm32_format_integer(${flash_used} flash_used_bytes)
stm32_format_integer(${flash_free} flash_free_bytes)
stm32_format_integer(${FLASH_SIZE_BYTES} flash_capacity_bytes)
stm32_format_integer(${ram_used} ram_used_bytes)
stm32_format_integer(${ram_free} ram_free_bytes)
stm32_format_integer(${RAM_SIZE_BYTES} ram_capacity_bytes)

stm32_pad_right("Region" 6 region_header)
stm32_pad_right("Used" 21 used_header)
stm32_pad_right("Free" 21 free_header)
stm32_pad_right("Capacity" 21 capacity_header)
stm32_pad_right("Utilized" 8 utilization_header)
stm32_pad_right("Composition" 11 composition_header)

stm32_pad_right("FLASH" 6 flash_region)
stm32_pad_left("${flash_used_bytes} B (${flash_used_kib} KiB)" 21 flash_used_value)
stm32_pad_left("${flash_free_bytes} B (${flash_free_kib} KiB)" 21 flash_free_value)
stm32_pad_left("${flash_capacity_bytes} B (${flash_capacity} KiB)" 21 flash_capacity_value)
stm32_pad_left("${flash_percent}%" 8 flash_utilization_value)
stm32_pad_right("text + data" 11 flash_composition)

stm32_pad_right("RAM" 6 ram_region)
stm32_pad_left("${ram_used_bytes} B (${ram_used_kib} KiB)" 21 ram_used_value)
stm32_pad_left("${ram_free_bytes} B (${ram_free_kib} KiB)" 21 ram_free_value)
stm32_pad_left("${ram_capacity_bytes} B (${ram_capacity} KiB)" 21 ram_capacity_value)
stm32_pad_left("${ram_percent}%" 8 ram_utilization_value)
stm32_pad_right("data + bss" 11 ram_composition)

message("")
message("[Memory Usage]")
message("  Target : ${PROJECT_LABEL}")
message("")
message("  Memory Regions")
message("  ┌────────┬───────────────────────┬───────────────────────┬───────────────────────┬──────────┬─────────────┐")
message("  │ ${region_header} │ ${used_header} │ ${free_header} │ ${capacity_header} │ ${utilization_header} │ ${composition_header} │")
message("  ├────────┼───────────────────────┼───────────────────────┼───────────────────────┼──────────┼─────────────┤")
message("  │ ${flash_region} │ ${flash_used_value} │ ${flash_free_value} │ ${flash_capacity_value} │ ${flash_utilization_value} │ ${flash_composition} │")
message("  │ ${ram_region} │ ${ram_used_value} │ ${ram_free_value} │ ${ram_capacity_value} │ ${ram_utilization_value} │ ${ram_composition} │")
message("  └────────┴───────────────────────┴───────────────────────┴───────────────────────┴──────────┴─────────────┘")
