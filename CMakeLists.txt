cmake_minimum_required(VERSION 3.0)
project(dashee)

# Set the RASPBERRY_PI Variable if we detect that the system
# is running on a Pi
include(CheckIncludeFile)
CHECK_INCLUDE_FILE("/opt/vc/include/bcm_host.h" RASPBERRY_PI)

##
# Dependant on operating system type we set the flags
# Accordingly
#
if (EXISTS "/opt/vc/include/bcm_host.h")
    set(CMAKE_SYSTEM_NAME RaspberryPi)
elseif(APPLE)
    set(CMAKE_SYSTEM_NAME Darwin)
else()
    set(CMAKE_SYSTEM_NAME Linux)
endif()
message(STATUS "Detected system as: ${CMAKE_SYSTEM_NAME}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(include)
link_directories(/usr/local/lib/)

# Create a list of Files
file(GLOB_RECURSE LIB_FILES src/*)
list(REMOVE_ITEM LIB_FILES src/servod.cpp)
file(GLOB_RECURSE INCLUDE_FILES include/*)
file(GLOB_RECURSE TEST_LIB_FILES tests/*)
file(GLOB_RECURSE TEST_FILES tests/test*.cpp)
list(REMOVE_ITEM TEST_LIB_FILES ${TEST_FILES})

##
# Libraries
#
add_library(
        dashee
        SHARED
        ${LIB_FILES}
        ${INCLUDE_FILES}
)

add_library(
        dasheetest
        SHARED
        ${TEST_LIB_FILES}
)
set_target_properties(dasheetest PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Wno-constant-conversion")
target_include_directories(dasheetest PUBLIC tests include)
target_link_libraries(dasheetest dashee cppunit)

##
# Add the executables
#
add_executable(servod src/servod.cpp)
target_link_libraries(servod dashee pthread)

file(GLOB TEST_SOURCES tests/test*.cpp)
foreach( testsourcefile ${TEST_SOURCES} )
    # I used a simple string replace, to cut off .cpp.
    get_filename_component(TEST_FILE_NAME ${testsourcefile} NAME)
    string( REPLACE ".cpp" "" TEST_NAME ${TEST_FILE_NAME} )
    message(STATUS "Detected test: ${TEST_NAME}")

    add_executable( ${TEST_NAME} tests/${TEST_FILE_NAME} )
    target_include_directories(${TEST_NAME} PRIVATE tests/)
    target_link_libraries(${TEST_NAME} dashee dasheetest cppunit pthread)
endforeach( testsourcefile ${TEST_SOURCES} )

##
# Some custom commands that are helpful when debugging
#
add_custom_command(
        COMMAND cp -r ${PROJECT_SOURCE_DIR}/files .
        COMMENT "Copying test files."
        POST_BUILD
        TARGET servod
)
add_custom_command(
        COMMAND mkdir -p data
        COMMENT "Creating binary data file."
        COMMAND dd if=/dev/zero of=data/Servo.bin bs=1 count=0 seek=74 2>/dev/null
        POST_BUILD
        TARGET servod testVehicle testVehicleCar testVehicleMultirotorQuadX
)

add_custom_command(
        OUTPUT ${PROJECT_BINARY_DIR}/runtest.sh
        COMMAND install -m 775 ${PROJECT_SOURCE_DIR}/scripts/runtest.sh ${PROJECT_BINARY_DIR}/runtest.sh
        COMMENT "Installing runtest.sh"
)
add_custom_target(runtest ALL DEPENDS runtest.sh)