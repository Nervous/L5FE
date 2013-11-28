set(fnmatch_source_files
    getdir.c
    fn_match.h
    match.c
    my_fnmatch.c
    my_fnmatch.h
    parser.c
    queue.c
    path_exp.c
)

add_library(fnmatch ${fnmatch_source_files})
