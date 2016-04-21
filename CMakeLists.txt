cmake_minimum_required(VERSION 3.0)
project(dashee)

##
# Set the variables required for building to ensure
# the build works on all platforms
#
if (APPLE)
    #set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
    SET(CMAKE_SYSTEM_NAME Darwin)
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(include)
link_directories(/usr/local/lib/)

# Create a list of Files
file(GLOB_RECURSE SRC_FILES src/*)
list(REMOVE_ITEM SRC_FILES src/servod.cpp)
file(GLOB_RECURSE INCLUDE_FILES include/*)
file(GLOB_RECURSE TEST_FILES tests/*)
file(GLOB_RECURSE TEST_FILES_EXCLUDE tests/test*.cpp)
list(REMOVE_ITEM TEST_FILES ${TEST_FILES_EXCLUDE})

##
# Libraries
#
add_library(
        dashee
        SHARED
        ${SRC_FILES}
        ${INCLUDE_FILES}
)

add_library(
        dasheetest
        SHARED
        ${TEST_FILES}
)
target_include_directories(dasheetest PUBLIC tests include)
target_link_libraries(dasheetest dashee cppunit)

##
# Add the executables
#
#find_package(Threads REQUIRED)
add_executable(servod src/servod.cpp)
target_link_libraries(servod dashee pthread)

# TODO move this into a forloop
add_executable(testPoint tests/testPoint.cpp)
target_include_directories(testPoint PRIVATE tests/)
target_link_libraries(testPoint dashee dasheetest cppunit pthread)

##
# Some custom commands that are helpful when debugging
#
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