set(builtins_source_files
    echo.c
    tools.c
    source.c
    builtins.h
)

add_library(builtins ${builtins_source_files})
