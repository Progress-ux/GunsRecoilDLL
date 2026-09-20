cmake_minimum_required(VERSION 3.16)

project(guns_recoil_mm_i386 LANGUAGES CXX)

option(RELEASE "Build optimized release version" OFF)
option(LOG_TO_CONSOLE "Enable logging to console" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
    -m32
    -Wall
    -Wno-unknown-pragmas
    -Wno-attributes
    -fPIC
)

if(RELEASE)
    add_compile_options(-O2)
else()
    add_compile_options(
        -Og
        -ggdb3
        -DLH_DEBUG_LOG
    )
endif()

if(LOG_TO_CONSOLE)
    add_compile_definitions(LH_LOG_TO_CONSOLE)
endif()

set(METAMOD "${CMAKE_SOURCE_DIR}/metamod-p")
set(HLSDK "${METAMOD}/hlsdk")

set(SOURCES
    src/main/dllapi.cpp
    src/main/engine_api.cpp
    src/main/h_export.cpp
    src/main/meta_api.cpp

    src/util/logger.cpp
    src/util/sdk_util.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    "${HLSDK}/common"
    "${HLSDK}/dlls"
    "${HLSDK}/engine"
    "${METAMOD}/metamod"
    "${CMAKE_SOURCE_DIR}/src"
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -m32 
    -ggdb3 
    -Wall 
    -Wno-unknown-pragmas 
    -Wno-attributes 
    -fPIC 
)

if(RELEASE)
    target_compile_options(${PROJECT_NAME} PRIVATE -O2)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Og -ggdb3)
    
    target_compile_definitions(${PROJECT_NAME} PRIVATE LH_DEBUG_LOG)
endif()

if(LOG_TO_CONSOLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
        LH_LOG_TO_CONSOLE
    )
endif()

target_link_options(${PROJECT_NAME} PRIVATE
    -m32 
    -shared 
    -static-libgcc
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    dl
    m
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    OUTPUT_NAME "${PROJECT_NAME}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
)
