#include "parser.h"

extern s_global *g_global;

int parse_redirection(s_token **tok)
{
    bool digit = false;
    if (my_isdigit((*tok)->str))
    {
        *tok = eat_token(*tok);
        *tok = get_token(REDIRECTION);
        digit = true;
        climb_ast(1);
    }

    if ((*tok)->type != TOKEN_REDIR)
    {
        if (!digit)
            return -1;
        else
            return parse_error("Expected a redirection here");
    }

    *tok = eat_token(*tok);
    *tok = get_token(WORD);
    if ((*tok)->type != WORD)
        return -1;
    climb_ast(1);
    *tok = eat_token(*tok);
    *tok = get_token(EOL);
    climb_ast(1);
    return 0;
}

/**
** @brief Parse an element
*/

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

/**
** @brief Parse a prefix
*/

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
