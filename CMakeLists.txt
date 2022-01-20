cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

include(cmake/CPM.cmake)

project(Examples LANGUAGES CXX)

# set build type
if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Build type not set - defaulting to Release")
  set(CMAKE_BUILD_TYPE
      "Release"
      CACHE STRING "Choose the type of build from: Debug Release RelWithDebInfo MinSizeRel" FORCE
  )
endif()

# set cxx standard
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

CPMAddPackage("gh:fmtlib/fmt#8.1.1")

add_subdirectory(example1)
