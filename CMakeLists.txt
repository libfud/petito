# TODO: Determine the lowest version of CMake allowable
cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(petito LANGUAGES C CXX VERSION 0.0.1)
# configure_file (
#     "${PROJECT_SOURCE_DIR}/petito_config.hpp.in"
#     "${PROJECT_SOURCE_DIR}/petito_config.hpp"
# )
enable_testing()
include(CTest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CXX_CPPCHECK "project=target/debug/compile_commands.json;enable=information;force")

include(GoogleTest)
include(cmake/cmake_functions.cmake)

find_package(GTest REQUIRED)
# Require dot, treat the other components as optional
find_package(Doxygen
             REQUIRED dot
             OPTIONAL_COMPONENTS mscgen dia)

option(COVERAGE "Add coverage compilation and link options." OFF)
if (${COVERAGE})
  add_compile_options("--coverage")
  add_link_options("--coverage")
endif()

add_subdirectory(src)
add_subdirectory(data)
add_subdirectory(apps)
