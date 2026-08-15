cmake_minimum_required(VERSION 3.20)
project(timer_codec_tests LANGUAGES C)

enable_testing()

add_executable(timer_codec_tests
    timer_codec_test.c
    ../Src/timer_codec.c
)

target_include_directories(timer_codec_tests PRIVATE
    ../Inc
    ../../../Core/Inc
)

target_compile_features(timer_codec_tests PRIVATE c_std_11)
target_compile_options(timer_codec_tests PRIVATE -Wall -Wextra -Werror)

add_test(NAME timer_codec_tests COMMAND timer_codec_tests)
