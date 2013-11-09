#include "parser.h"

extern s_global *g_global;
static void parse_otherconditions(s_token **tok, bool mandatory)
{
    while (true)
    {
        if (!((*tok)->type == AND_DOUBLE || (*tok)->type == PIPE_DOUBLE))
            break;
        climb_ast(1);
        *tok = eat_token(*tok);
        *tok = get_token(EOL);
        climb_ast(1);
        parse_loop_EOL(tok);
        if (parse_pipeline(tok, mandatory) == -1)
            parse_error("PARSE ERROR : Expected a pipeline here");
    }
}
a
int parse_andor(s_token **tok, bool mandatory)
{
    ast_add_step("AND_OR");
    if (parse_pipeline(tok, mandatory) == -1)
    {
        remove_node(g_global->current_node);
        return -1;
    }
    parse_otherconditions(tok, mandatory);
    climb_ast(1);
    return 0;
}
