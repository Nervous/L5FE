#include "parser.h"

extern s_global *g_global;
static int check_shellcommand_bracket(s_token **tok)
{
    if ((*tok)->type == LEFT_BRACKET)
    {
        *tok = eat_token(*tok);
        *tok = get_token(EOL);
        if (g_global->current_node->father)
            g_global->current_node = g_global->current_node->father;
        parse_compoundlist(tok, true);
        if ((*tok)->type != RIGHT_BRACKET)
            parse_error("PARSE ERROR : Expected a right bracket");
        *tok = eat_token(*tok);
        *tok = get_token(EOL);
        if (g_global->current_node->father)
            g_global->current_node = g_global->current_node->father;
        return 0;
    }
    return -1;
}

static int check_shellcommand_par(s_token **tok)
{
    if ((*tok)->type == LEFT_PAR)
    {
        *tok = eat_token(*tok);
        *tok = get_token(EOL);
        climb_ast(1);
        parse_compoundlist(tok, true);
        if ((*tok)->type != RIGHT_PAR)
            parse_error("PARSE ERROR : Expected a right parenthesis");
        *tok = eat_token(*tok);
        *tok = get_token(EOL);
        return 0;
    }
    return -1;
}

int parse_shellcommand(s_token **tok)
{
    ast_add_step("Shell_command");
    if ((check_shellcommand_bracket(tok) == 0)
        || (check_shellcommand_par(tok) == 0)
        || (parse_rulefor(tok) == 0)
        || (parse_rulewhile(tok) == 0)
        || (parse_ruleuntil(tok) == 0)
        || (parse_rulecase(tok) == 0)
        || (parse_ruleif(tok) == 0))
    {
        climb_ast(1);
        return 0;
    }
    else
    {
        remove_node(g_global->current_node);
        return -1;
    }
}

