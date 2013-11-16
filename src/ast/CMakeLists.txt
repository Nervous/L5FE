set(ast_printer_source_files
    ast.c
    ast.h
    print_ast.c
)

add_library(ast_printer ${ast_printer_source_files})
