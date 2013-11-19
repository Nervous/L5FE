set(readline_source_files
    history.c
    functionkey.c
    readline.c
    arrowkey.c
    putchar.c
    )

add_library(readline ${readline_source_files})

include_directories(/usr/include)

link_directories(/usr/lib)

target_link_libraries(

    readline

    termcap

    )
