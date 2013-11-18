set(ast_source_files
    ast.h
    ast.c
    print_ast.c
    release_ast.c
)

add_library(ast ${ast_source_files})
