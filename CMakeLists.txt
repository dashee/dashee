cmake_minimum_required(VERSION 3.5)
project(dashee)

if (APPLE)
    set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-5")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)

file(GLOB_RECURSE SRC_FILES src/*)
file(GLOB_RECURSE INCLUDE_FILES include/*)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(
        dashee
        SHARED
        ${SRC_FILES}
        ${INCLUDE_FILES}
)

add_executable(servod src/servod.cpp)
target_link_libraries(servod dashee)

add_custom_command(
        COMMAND cp ${PROJECT_SOURCE_DIR}/files/examples/servod-dummy.conf .
        POST_BUILD
        TARGET servod
)
add_custom_command(
        COMMAND mkdir -p data
        COMMAND dd if=/dev/zero of=data/Servo.bin bs=1 count=0 seek=74 2>/dev/null
        POST_BUILD
        TARGET servod
)
