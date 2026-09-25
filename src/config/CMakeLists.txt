add_library(config STATIC
    config_manager.c
)

target_include_directories(config PUBLIC
    "${CMAKE_SOURCE_DIR}/src"
)
