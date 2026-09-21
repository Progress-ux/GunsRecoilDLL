add_library(hooks STATIC
    regame_context.cpp
    regame_hooks.cpp
    regame_loader.cpp
)

target_include_directories(hooks PUBLIC
    "${CMAKE_SOURCE_DIR}/src"
)

target_link_libraries(hooks PRIVATE
    core
    hlsdk
)
