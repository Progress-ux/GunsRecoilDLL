add_library(config STATIC
    config_manager.c
    parser.c
    config_node.c
)

target_include_directories(config PUBLIC
    "${CMAKE_SOURCE_DIR}/src"
)

target_link_libraries(config PRIVATE
    weapon
)
