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
    )

    add_compile_definitions(LH_DEBUG_LOG)
endif()

if(LOG_TO_REMOTE_SERVER)
    add_compile_definitions(LH_LOG_TO_REMOTE_SERVER)
endif()
