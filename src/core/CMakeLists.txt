add_library(core STATIC
    guns_recoil.cpp
    recoil_math.cpp
    config.c
)

target_include_directories(core PUBLIC
    "${CMAKE_SOURCE_DIR}/src"
)

target_link_libraries(core PRIVATE
    config
    util
    hlsdk
)
