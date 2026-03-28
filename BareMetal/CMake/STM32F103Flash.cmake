#
# Helper script used by the `flash` target.
# The second attempt with `--connect-under-reset` is a recovery path for
# firmware states that block a regular ST-Link attach.
#

if(NOT DEFINED ST_FLASH)
    message(FATAL_ERROR "ST_FLASH is required")
endif()

if(NOT DEFINED BINARY_FILE)
    message(FATAL_ERROR "BINARY_FILE is required")
endif()

if(NOT DEFINED FLASH_ADDRESS)
    message(FATAL_ERROR "FLASH_ADDRESS is required")
endif()

if(NOT EXISTS "${BINARY_FILE}")
    message(FATAL_ERROR "Binary file not found: ${BINARY_FILE}")
endif()

message(STATUS "")
message(STATUS "[Flash]")
message(STATUS "  Binary           : ${BINARY_FILE}")
message(STATUS "  Flash Address    : ${FLASH_ADDRESS}")
message(STATUS "  Probe Tool       : ${ST_FLASH}")

execute_process(
    COMMAND "${ST_FLASH}" --reset write "${BINARY_FILE}" "${FLASH_ADDRESS}"
    RESULT_VARIABLE flash_result
)

if(flash_result EQUAL 0)
    message(STATUS "  Result           : flashed successfully")
    return()
endif()

message(WARNING "  Normal flash failed. Retrying with connect-under-reset.")

execute_process(
    COMMAND "${ST_FLASH}" --connect-under-reset --reset write "${BINARY_FILE}" "${FLASH_ADDRESS}"
    RESULT_VARIABLE flash_under_reset_result
)

if(flash_under_reset_result EQUAL 0)
    message(STATUS "  Result           : flashed successfully via connect-under-reset")
    return()
endif()

message(FATAL_ERROR "Flashing failed in both normal and connect-under-reset modes.")
