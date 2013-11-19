#include "parser.h"

extern s_global *g_global;
static void loop_coumpoundlist(s_token **tok, bool mandatory)
{
   while (true)
   {
       if (!((*tok)->type == EOL || (*tok)->type == BIT_AND
                   || (*tok)->type == SEMICOLON))
       {
            climb_ast(1);
            if (!mandatory)
                return;
            else
                parse_error("PARSE ERROR: Expected an '\\n' or '|' or ';' 2");
       }
        if ((*tok)->type == SEMICOLON)
        {
            climb_ast(1);
        }
        *tok = eat_token(*tok);
        *tok = get_token(EOL);
            climb_ast(1);
        parse_loop_EOL(tok);
        if (parse_andor(tok, false) == -1)
            break;
   }
}

static void check_end_coumpoundlist(s_token **tok)
{
    if (!((*tok)->type == EOL || (*tok)->type == BIT_AND
                || (*tok)->type == SEMICOLON))
        return;
    *tok = eat_token(*tok);
    *tok = get_token(EOL);
    climb_ast(1);
    parse_loop_EOL(tok);
}

/**
** @brief Parse a compoundlist
*/

int parse_compoundlist(s_token **tok, bool mandatory)
{
    ast_add_step("Compound_list");
    parse_loop_EOL(tok);
    if (parse_andor(tok, false) == -1)
    {
        remove_node(g_global->current_node);
        if (!mandatory)
            return -1;
        else
            parse_error("PARSE ERROR: Expected an and_or structure");
    }

    loop_coumpoundlist(tok, false);
    check_end_coumpoundlist(tok);
    climb_ast(1);
    return 0;
}
