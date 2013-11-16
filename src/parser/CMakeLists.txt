set(parser_source_files
    parser.h
    parser.c
    parser_andor.c
    parser_command.c
    parser_compoundlist.c
    parser_function.c
    parser_loops.c
    parser_other.c
    parser_rule.c
    parser_rule_conditions.c
    parser_shellcommand.c
    utils_error.c
    utils_error.h
    utils_string.c
    utils_string.h
)

add_library(parser ${parser_source_files})
target_link_libraries(parser ast)
target_link_libraries(parser lexer)
