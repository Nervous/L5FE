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
            break;
        }
        no_andor = no_andor;
    }
    climb_ast(2);
    return 0;
}

static void getandeat(s_token **tok)
{
    *tok = eat_token(*tok);
    *tok = get_token(EOL);
}

static int parse_input(void)
{
    ast_add_step("Input");
    s_token *tok = get_token(INPUT);
    while (tok->type != E_EOF)
    {
        if (tok->type == EOL)
            getandeat(&tok);
        else if (tok->type == E_EOF)
            break;
        else
        {
            if (parse_list(&tok) == -1)
                return parse_error("PARSE ERROR : Expected a list");
            if (tok->type == EOL || tok->type == E_EOF)
                getandeat(&tok);
            else
                return parse_error("PARSE ERROR : Expected '\\n' or EOF");
        }
        climb_ast(1);
    }
    tok = eat_token(tok);
    return 0;
}

/**
** @brief Starts the parsing of an input
** @return Returns -1 if parses fail, 0 otherwise
*/

int parse(void)
{
    g_global->parse_error = 0;
    int ret = parse_input();
    if (ret != g_global->parse_error)
        return g_global->parse_error;
    return ret;
}
