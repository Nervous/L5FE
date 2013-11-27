#include "parser.h"

extern s_global *g_global;

static void getandeat(s_token **tok)
{
    *tok = eat_token(*tok);
    *tok = get_token(EOL);
}

int parse_function(s_token **tok)
{
    ast_add_step("Funcdec");
    if ((*tok)->type != FUNC)
    {
        climb_ast(1);
        return -1;
    }

    *tok = eat_token(*tok);
    *tok = get_token(WORD);
    climb_ast(1);
    if ((*tok)->type != WORD)
        parse_error("PARSE ERROR : Expected a WORD");
    getandeat(tok);
    climb_ast(1);
    if ((*tok)->type != LEFT_PAR)
        parse_error("PARSE ERROR : Expected a '('");
    getandeat(tok);

    climb_ast(1);
    if ((*tok)->type != RIGHT_PAR)
        parse_error("PARSE ERROR : Expected a ')'");
    getandeat(tok);

    climb_ast(1);
    parse_loop_EOL(tok);
    if (parse_shellcommand(tok) == -1)
        parse_error("PARSE ERROR : Expected a shell command !");
    return 0;
}
