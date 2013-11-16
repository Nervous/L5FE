#include "parser.h"

extern s_global *g_global;
int parse_redirection(s_token **tok)
{
       if (my_isdigit((*tok)->str))
       {
            *tok = eat_token(*tok);
            *tok = get_token(REDIRECTION);
            climb_ast(1);
       }

       if ((*tok)->type != TOKEN_REDIR)
           return -1;

       *tok = eat_token(*tok);
       *tok = get_token(WORD);
       climb_ast(1);
        return 0;
}

int parse_element(s_token **tok)
{
    if ((*tok)->type == WORD)
    {
        *tok = eat_token(*tok);
        *tok = get_token(WORD);
        if (g_global->current_node->father)
            g_global->current_node = g_global->current_node->father;
        return 0;
    }
    return parse_redirection(tok);
}

int parse_prefix(s_token **tok)
{
    if ((*tok)->type == ASSIGNMENT_WORD)
    {
        *tok = eat_token(*tok);
        *tok = get_token(EOL);
        if (g_global->current_node->father)
            g_global->current_node = g_global->current_node->father;
        return 0;
    }

    return parse_redirection(tok);
}
