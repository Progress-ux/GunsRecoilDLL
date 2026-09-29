add_library(weapon STATIC
    weapon_info.c
)

target_include_directories(weapon PUBLIC
    "${CMAKE_SOURCE_DIR}/src"
)
