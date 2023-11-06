cmake_minimum_required(VERSION 3.10)

project(rhasher VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)


find_library(RHASH_LIB rhash)
find_library(READLINE_LIB readline)

add_executable(rhasher src/main.c)

target_link_libraries(rhasher PRIVATE ${RHASH_LIB})

if (READLINE_LIB)
    target_link_libraries(rhasher PRIVATE ${READLINE_LIB})
    add_definitions(-DREADLINE_ENABLED)
endif()


set_target_properties(
    rhasher PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../bin"
)