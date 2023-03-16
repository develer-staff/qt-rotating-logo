cmake_minimum_required(VERSION 3.16)

project(QtTestApplication DESCRIPTION "Qt Test Application")

include(cmake/clang_tidy_qt_workaround.cmake)
include(cmake/windeployqt.cmake)

#
# Find Packages
#

find_package(Git REQUIRED)

# Speed-up searching for Python.
set(Python3_FIND_IMPLEMENTATIONS CPython)
set(Python3_FIND_REGISTRY NEVER)
set(Python3_FIND_STRATEGY LOCATION)

find_package(Python3 REQUIRED)

find_package(Qt6 REQUIRED COMPONENTS QuickWidgets Test Widgets)

#
# Version
#

execute_process(
    COMMAND_ERROR_IS_FATAL ANY
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/script/print-version.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE BUILD_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(
    COMMAND_ERROR_IS_FATAL ANY
    COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE BUILD_COMMIT
    OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(
    COMMAND_ERROR_IS_FATAL ANY
    COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE BUILD_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE)

message(STATUS "Building version: ${BUILD_VERSION}")
message(STATUS "Git commit: ${BUILD_COMMIT}")
message(STATUS "Git branch: ${BUILD_BRANCH}")

#
# Build Options
#

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(/W3 /WX)

#
# Enable unit tests
#

include(CTest)
enable_testing()

#
# Build sub-projects
#

clang_tidy_qt_workaround()

add_subdirectory(libcommon)
add_subdirectory(application)
add_subdirectory(tests)
