#
# Helper script used by the `erase_flash` target.
# It first attempts a normal ST-Link erase and automatically retries with
# `--connect-under-reset` for boards that cannot be attached in a live state.
#

if(NOT DEFINED ST_FLASH)
    message(FATAL_ERROR "ST_FLASH is required")
endif()

message(STATUS "")
message(STATUS "[Erase Flash]")
message(STATUS "  Probe Tool       : ${ST_FLASH}")

execute_process(
    COMMAND "${ST_FLASH}" erase
    RESULT_VARIABLE erase_result
)

if(erase_result EQUAL 0)
    message(STATUS "  Result           : erase completed successfully")
    return()
endif()

message(WARNING "  Normal erase failed. Retrying with connect-under-reset.")

execute_process(
    COMMAND "${ST_FLASH}" --connect-under-reset erase
    RESULT_VARIABLE erase_under_reset_result
)

if(erase_under_reset_result EQUAL 0)
    message(STATUS "  Result           : erase completed successfully via connect-under-reset")
    return()
endif()

message(FATAL_ERROR "Erase failed in both normal and connect-under-reset modes.")
