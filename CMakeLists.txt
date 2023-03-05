cmake_minimum_required(VERSION 3.18.2 FATAL_ERROR)

enable_testing()

#
# Project
#
set(PROJECT_NAME odnn)
project(${PROJECT_NAME} LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#
# CMake Settings
#

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
  set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()

#
# C/CXX settings
#

# CXX standards
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default to Debug build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      Debug
      CACHE STRING "Build type" FORCE)
endif()

#
# 3rdparty
#
include(FetchContent)

# googletest
include(${PROJECT_SOURCE_DIR}/cmake/modules/GoogleTest.cmake)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.tar.gz)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#
# Project settings
#
set(ODNN_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
set(ODNN_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(ODNN_CXX_FLAGS "-Wall" "-Wno-uninitialized" "-Wno-unused-function"
                   "-Wno-unknown-pragmas")

# Logging
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

#
# src
#
add_subdirectory(src)

#
# tests
#
add_subdirectory(test)
