set(struct_source_files
    parser.h
    parser.c
    parser_andor.c
    parser_command.c
    parser_compoundlist.c
    parser_function.c
    parser_loops.c
    parser_other.c
    parser_rule.c
    parser_rule_condition.c
    parser_shellcommand.c
)

add_library(struct ${struct_source_files})
