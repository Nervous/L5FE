#ifndef STRUCT_H
# define STRUCT_H
# include <stdio.h>
# include <termios.h>
# include "exec/variable.h"
# include "exec/function.h"

void init_global(void);

enum e_context
{
    INPUT,
    PIPELINE,
    REDIRECTION,
    SIMPLE_COMMAND
};

enum e_type
{
    EOL,
    E_EOF,
    ASSIGNMENT_WORD,
    CASE,
    ESAC,
    DO,
    DONE,
    IF,
    THEN,
    ELSE,
    ELIF,
    FI,
    FOR,
    IN,
    WHILE,
    UNTIL,
    FUNC,
    PIPE_DOUBLE,
    AND_DOUBLE,
    TOKEN_REDIR,
    SHARP,
    NEG,
    BIT_PIPE,
    BIT_AND,
    DOLLAR,
    S_QUOTE,
    D_QUOTE,
    B_QUOTE,
    SEMICOLON,
    D_SEMICOLON,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    LEFT_PAR,
    RIGHT_PAR,
    B_SLASH,
    SLASH,
    IONUMBER,
    WORD,
    ERROR,
    ABSTRACT
};

typedef struct token
{
    enum e_type type;
    char *str;
    int pos;
} s_token;

typedef struct list
{
    int id;
    int linked;
    int abstract;
    s_token *node;
    struct list *father;
    struct list *brothers;
    struct list *son_list;
} s_list;

typedef struct global
{
    s_list *current_node;
    int last_node_id;
    unsigned int pos;
    int ast;
    int norc;
    int file;
    char *readline;
    char *hist_file;
    struct termios attribute;
    s_var *var;
    struct function *func;
    char **hist_arr;
    int hist_ind;
    int parse_error;
    int ret;
    int break_nb;
} s_global;

#endif /* !STRUCT_H */
