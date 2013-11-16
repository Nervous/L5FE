set(lexer_source_files
    lexer.h
    lexer.c
    token.c
    token.h
)

add_library(lexer ${lexer_source_files})
