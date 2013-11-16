#include "parser.h"

extern s_global *g_global;
static int parse_list(s_token **tok)
{
    ast_add_step("List");

    bool no_andor = false;

    if (parse_andor(tok, true) == -1)
        return parse_error("PARSE ERROR : Expected an ANDOR structure");

    while (true)
    {
        if (!((*tok)->type == SEMICOLON || (*tok)->type == BIT_AND))
            break;
        climb_ast(1);
        *tok = eat_token(*tok);
        *tok = get_token(EOL);
        climb_ast(1);
        if ((*tok)->type == E_EOF)
            return 0;
        if (parse_andor(tok, false) == -1)
        {
            no_andor = true;
            //climb_ast(1);
            break;
        }
    }
    no_andor = no_andor; // CHECK HERE IN CASE OF PROBLEM
    if (g_global->current_node->father)
        g_global->current_node = g_global->current_node->father;
    return 0;
}

static int parse_input(void)
{
    s_token *tok = get_token(INPUT);
    if (tok->type == EOL)
        return 0;
    else if (tok->type == E_EOF)
        return 0;
    else
    {
        ast_add_step("Input");
        if (parse_list(&tok) == -1)
            return parse_error("PARSE ERROR : Expected a list");
        if (tok->type == EOL || tok->type == E_EOF)
            eat_token(tok);
        else
            return parse_error("PARSE ERROR : Expected '\\n' or EOF");
        return 0;
    }
}

int parse(void)
{
    return parse_input();
}
