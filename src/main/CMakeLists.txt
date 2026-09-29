add_library(${PROJECT_NAME} SHARED
    dllapi.cpp
    engine_api.cpp
    h_export.cpp
    meta_api.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    core
    hooks
    util
    hlsdk
    config
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    dl
    m
)

target_link_options(${PROJECT_NAME} PRIVATE
    -m32
    -static-libgcc
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    OUTPUT_NAME "${PROJECT_NAME}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
)
