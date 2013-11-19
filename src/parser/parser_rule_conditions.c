#include "parser.h"

extern s_global *g_global;
static void parse_oritem(s_token **tok)
{
    while ((*tok)->type == BIT_PIPE)
    {
        *tok = eat_token(*tok);
        *tok = get_token(WORD);
        climb_ast(1);
        if ((*tok)->type != WORD)
            parse_error("PARSE ERROR : Expected a WORD");
        *tok = eat_token(*tok);
        *tok = get_token(BIT_PIPE);
        climb_ast(1);
    }
}

static int parse_caseitem(s_token **tok)
{
    bool started = false;
    if ((*tok)->type == LEFT_PAR)
    {
        *tok = eat_token(*tok);
        *tok = get_token(WORD);
        started = true;
    }

    if ((*tok)->type != WORD && !started)
        return -1;
    else if (started)
        parse_error("PARSE ERROR : Expected a WORD");

    *tok = eat_token(*tok);
    *tok = get_token(IN);
    parse_oritem(tok);
    if ((*tok)->type != RIGHT_PAR)
        parse_error("PARSE ERROR : Expected a ')'");
    *tok = eat_token(*tok);
    *tok = get_token(EOL);
    parse_compoundlist(tok, false);
    return 0;
}

static void parse_caseclause(s_token **tok)
{
    bool no_case = false;
    if (parse_caseitem(tok) == -1)
        return;
    while (true)
    {
        if ((*tok)->type != D_SEMICOLON)
            break;
        *tok = eat_token(*tok);
        *tok = get_token(EOL);
        climb_ast(1);
        parse_loop_EOL(tok);
        if (parse_caseitem(tok) == -1)
        {
            no_case = true;
            break;
        }
    }

    if (no_case == false)
        parse_loop_EOL(tok);
    else if ((*tok)->type == D_SEMICOLON)
        parse_error("PARSE ERROR : Expected a ')'");
    else
        parse_loop_EOL(tok);
}

/**
** @brief Parse a rule_case grammar line
*/

int parse_rulecase(s_token **tok)
{
    if ((*tok)->type != CASE)
        return -1;
    *tok = eat_token(*tok);
    *tok = get_token(WORD);
    climb_ast(1);
    if ((*tok)->type != WORD)
        parse_error("PARSE ERROR : Expected a WORD");
    *tok = eat_token(*tok);
    *tok = get_token(EOL | IN);
    climb_ast(1);
    parse_loop_EOL(tok);
    if ((*tok)->type != IN)
        parse_error("PARSE ERROR : Expected a IN keyword");
    *tok = eat_token(*tok);
    *tok = get_token(WORD);
    climb_ast(1);
    parse_loop_EOL(tok);
    parse_caseclause(tok);
    if ((*tok)->type != ESAC)
        parse_error("PARSE ERROR : Expected a ESAC keyword");
    climb_ast(1);
    return 0;
}

static void parse_elseclause(s_token **tok)
{
    if ((*tok)->type == ELSE)
    {
        ast_add_step("Else_clause");
        *tok = eat_token(*tok);
        *tok = get_token(EOL);
        climb_ast(1);
        parse_compoundlist(tok, true);
        climb_ast(1);
    }
    else if ((*tok)->type == ELIF)
    {
        ast_add_step("Else_clause");
        *tok = eat_token(*tok);
        *tok = get_token(EOL);
        climb_ast(1);
        parse_compoundlist(tok, true);
        if ((*tok)->type != THEN)
            parse_error("PARSE ERROR : Expected a THEN keyword");
        *tok = eat_token(*tok);
        *tok = get_token(EOL);
        climb_ast(1);
        parse_compoundlist(tok, true);
        parse_elseclause(tok);
        climb_ast(1);
    }
}

/**
** @brief Parse an rule_if grammar line
*/
int parse_ruleif(s_token **tok)
{
    if ((*tok)->type != IF)
        return -1;
    ast_add_step("Rule_if");
    *tok = eat_token(*tok);
    *tok = get_token(EOL);
    if (g_global->current_node->father)
        g_global->current_node = g_global->current_node->father;
    parse_compoundlist(tok, true);
    if ((*tok)->type != THEN)
        parse_error("PARSE ERROR : Expected a THEN keyword");
    *tok = eat_token(*tok);
    *tok = get_token(EOL);
    climb_ast(1);
    parse_compoundlist(tok, true);
    parse_elseclause(tok);
    if ((*tok)->type != FI)
        parse_error("PARSE ERROR : Expected a FI keyword");
    *tok = eat_token(*tok);
    *tok = get_token(EOL);
    return 0;
}
