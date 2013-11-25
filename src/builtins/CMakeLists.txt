set(builtins_source_files
    echo.c
    tools.c
    source.c
    builtins.h
    exit.c
    cd.c
    aliases.h
    alias_tools.c
    aliases.c
    shopt.c
    export.c
    history.c
)

add_library(builtins ${builtins_source_files})
