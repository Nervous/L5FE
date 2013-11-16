#include "parser.h"
extern s_global *g_global;
static int do_group(s_token **tok)
{
    ast_add_step("Do_group");
    if ((*tok)->type != DO)
        parse_error("PARSE ERROR : Expected a DO keyword");
    *tok = eat_token(*tok);
    *tok = get_token(EOL);
    climb_ast(1);
    if (parse_compoundlist(tok, true) == -1)
        parse_error("PARSE ERROR : Expected a coumpound list");
    //climb_ast(1);
    if ((*tok)->type != DONE)g
        parse_error("PARSE ERROR : Expected a DONE keyword");
    *tok = eat_token(*tok);
    *tok = get_token(EOL);
    climb_ast(1);
    return 0;
}

static void check_in_rulefor(s_token **tok)
{
    if ((*tok)->type != IN)
        return;
    *tok = eat_token(*tok);
    *tok = get_token(WORD | SEMICOLON | EOL);
    climb_ast(1);
    parse_loop_WORD(tok);
    if ((*tok)->type != SEMICOLON && (*tok)->type != EOL)
        parse_error("PARSE ERROR : Expected a ';' or a '\\n'");
    *tok = eat_token(*tok);
    *tok = get_token(EOL | SEMICOLON);
    parse_loop_EOL(tok);
}

int parse_rulefor(s_token **tok)
{
    if ((*tok)->type != FOR)
        return -1;
    ast_add_step("Rule_for");
    *tok = eat_token(*tok);
    *tok = get_token(WORD);
    climb_ast(1);
    if ((*tok)->type != WORD)
        parse_error("PARSE ERROR : Expected a WORD");
    *tok = eat_token(*tok);
    *tok = get_token(EOL | IN);
    climb_ast(1);
    parse_loop_EOL(tok);
    check_in_rulefor(tok);
    return do_group(tok);
}

int parse_rulewhile(s_token **tok)
{
    if ((*tok)->type != WHILE)
        return -1;
    ast_add_step("Rule_while");
    *tok = eat_token(*tok);
    *tok = get_token(EOL | IN);
    climb_ast(1);
    if (parse_compoundlist(tok, true) != 0)
        parse_error("PARSE ERROR : Expected a compound list");
    return do_group(tok);
}

int parse_ruleuntil(s_token **tok)
{
    if ((*tok)->type != UNTIL)
        return -1;
    ast_add_step("Rule_until");
    *tok = eat_token(*tok);
    *tok = get_token(EOL | IN);
    climb_ast(1);
    if (parse_compoundlist(tok, true) != 0)
        parse_error("PARSE ERROR : Expected a WHILE keyword");
    return do_group(tok);
}
