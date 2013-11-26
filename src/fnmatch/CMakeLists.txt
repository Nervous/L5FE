set(fnmatch_source_files
    destroy.c
    init_fifo.c
    my_fnmatch.c
    parse.c
    compare.c
    fifo.h
    main.c
    my_fnmatch.h
    push.c
    getdir.c
    path_exp.c
)

add_library(fnmatch ${fnmatch_source_files})
