cmake_minimum_required(VERSION 3.10)

project(gpt-fast-cpp)
set(CMAKE_CXX_STANDARD 17)
option(ARM "build on ARM" OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm" OR ${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64")
    message(STATUS "ARM detected")
    set(ARM ON)
endif()

if(ARM)
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin-arm)
else()
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    option(TEST "test mode" OFF)
else()
    option(TEST "test mode" ON)
endif()

option(QUANT "quantize tools" ON)
option(FROM_GUFF "convert from gguf" OFF)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

option(DEBUG "debug print" OFF)

if (CMAKE_HOST_UNIX)
    message(STATUS "current platform: Linux ")
elseif (CMAKE_HOST_WIN32)
    message(STATUS "current platform: Windows ")
else ()
    message(STATUS "current platform: unknown ")
endif ()

aux_source_directory(${PROJECT_SOURCE_DIR}/examples EMP_SRC)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/third_party)

if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "^(x86_64|i686|AMD64)$")
    message(STATUS "x86_64 detected")
    add_compile_options(-mf16c)
    add_compile_options(-mavx2)
elseif (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm" OR ${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64")
    message(STATUS "ARM detected")
    add_definitions(-DARM)
    if (APK)
        message(STATUS "Build for Android APK Lib.")
        add_definitions("-DANDROID_API")
    endif ()
endif ()

add_executable(demo_llama ${PROJECT_SOURCE_DIR}/examples/demo_llama.cpp)