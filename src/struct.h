#ifndef STRUCT_H
# define STRUCT_H
# include <stdio.h>
# include <termios.h>
# include "exec/variable.h"

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
    LEFT_SQ_BRACKET,
    RIGHT_SQ_BRACKET,
    B_SLASH,
    SLASH,
    IONUMBER,
    WORD,
    ABSTRACT
};

typedef struct token
{
    enum e_type type;
    char *str;
    int pos;
    struct list *son_list;
} s_token;

typedef struct list
{
    int id;
    int linked;
    int abstract;
    s_token *node;
    struct list *father;
    struct list *brothers;
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
    int prev_return;
    FILE *hist;
    struct termios attribute;
    s_var *var;
} s_global;

#endif /* !STRUCT_H */
