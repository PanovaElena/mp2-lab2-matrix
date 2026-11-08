cmake_minimum_required(VERSION 3.30)

# disable googlemock
option(BUILD_GMOCK "Builds the googlemock subproject" OFF)

option(BUILD_SAMPLES "Builds all samples" ON)

set(PROJECT_NAME matrix)
project(${PROJECT_NAME})

include(CTest)
enable_testing()  # defines BUILD_TESTING

set(MP2_TESTS   "test_${PROJECT_NAME}")
set(MP2_CUSTOM_PROJECT "${PROJECT_NAME}")
set(MP2_INCLUDES "${PROJECT_SOURCE_DIR}/include")

# Header-only library
set(MP2_LIBRARY ${MP2_CUSTOM_PROJECT})
add_library(${MP2_LIBRARY} INTERFACE)
target_include_directories(${MP2_LIBRARY} INTERFACE "${MP2_INCLUDES}")

add_subdirectory(include)
add_subdirectory(samples)

# add googletest, version 1.18.0
add_subdirectory("${PROJECT_SOURCE_DIR}/gtest/googletest-1.18.0")
set(MP2_GTEST_INCLUDES "${gtest_SOURCE_DIR}/include/gtest")
add_subdirectory(test)

# REPORT
message( STATUS "")
message( STATUS "General configuration for ${PROJECT_NAME}")
message( STATUS "======================================")
message( STATUS "")
message( STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message( STATUS "")
