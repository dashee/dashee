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
# TODO this is not working!
set_target_properties(dasheetest PROPERTIES CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-constant-conversion")
target_include_directories(dasheetest PUBLIC tests include)
target_link_libraries(dasheetest dashee cppunit)

##
# Add the executables
#
add_executable(servod src/servod.cpp)
target_link_libraries(servod dashee pthread)

##
# Generate the test Executables
#
add_executable(testThreads tests/testThreads.cpp)
target_include_directories(testThreads PRIVATE tests/)
target_link_libraries(testThreads dashee dasheetest cppunit pthread)

add_executable(testPoint tests/testPoint.cpp)
target_include_directories(testPoint PRIVATE tests/)
target_link_libraries(testPoint dashee dasheetest cppunit pthread)

add_executable(testI2C tests/testI2C.cpp)
target_include_directories(testI2C PRIVATE tests/)
target_link_libraries(testI2C dashee dasheetest cppunit pthread)

add_executable(testConfig tests/testConfig.cpp)
target_include_directories(testConfig PRIVATE tests/)
target_link_libraries(testConfig dashee dasheetest cppunit pthread)

add_executable(testBuffer tests/testBuffer.cpp)
target_include_directories(testBuffer PRIVATE tests/)
target_link_libraries(testBuffer dashee dasheetest cppunit pthread)

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
        TARGET servod
)
message("${PROJECT_SOURCE_lDIR}/scripts/runtest.sh")
message("${PROJECT_BINARY_DIR}/runtest.sh")

add_custom_command(
        OUTPUT ${PROJECT_BINARY_DIR}/runtest.sh
        COMMAND install -m 775 ${PROJECT_SOURCE_DIR}/scripts/runtest.sh ${PROJECT_BINARY_DIR}/runtest.sh
        COMMENT "Installing runtest.sh"
)
add_custom_target(runtest ALL DEPENDS runtest.sh)