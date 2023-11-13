
cmake_minimum_required(VERSION 3.10)

project(i18n VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(i18n main.c)

set_target_properties(
    i18n PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../bin"
)

