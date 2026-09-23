cmake_minimum_required(VERSION 3.16)

project(guns_recoil_mm_i386 LANGUAGES C CXX)

option(RELEASE "Build optimized release version" OFF)
option(LOG_TO_REMOTE_SERVER "Enable logging to server file" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(METAMOD "${CMAKE_SOURCE_DIR}/metamod-p")
set(HLSDK "${METAMOD}/hlsdk")

add_library(hlsdk INTERFACE)

target_include_directories(hlsdk INTERFACE
    "${HLSDK}/common"
    "${HLSDK}/dlls"
    "${HLSDK}/engine"
    "${METAMOD}/metamod"
)

include(cmake/CompilerOptions.cmake)

add_subdirectory(src)
