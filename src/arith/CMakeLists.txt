set(arith_source_files
    evalexpr.c
    pos_eval.c
    inftopos.c
    parse.c
    stack.c
    queue.c
    free_stack.c
    std.h eval.h
)

add_library(arith ${arith_source_files})
