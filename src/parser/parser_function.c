#include "parser.h"

extern s_global *g_global;

/**
** @brief Parse an and_or grammar line
*/

int parse_function(s_token **tok)
{
    ast_add_step("Funcdec");
    if ((*tok)->type != FUNC)
    {
        climb_ast(1);
        return -1;
    }
    else
    {
        ast_add_step("function");
        climb_ast(1);
    }
    *tok = eat_token(*tok);
    *tok = get_token(WORD);
    climb_ast(1);
    if ((*tok)->type != WORD)
        parse_error("PARSE ERROR : Expected a WORD");
    *tok = eat_token(*tok);
    *tok = get_token(LEFT_PAR);
    climb_ast(1);
    if ((*tok)->type != LEFT_PAR)
        parse_error("PARSE ERROR : Expected a '('");
    *tok = eat_token(*tok);
    *tok = get_token(RIGHT_PAR);

    climb_ast(1);
    if ((*tok)->type != RIGHT_PAR)
        parse_error("PARSE ERROR : Expected a ')'");
    *tok = eat_token(*tok);
    *tok = get_token(EOL);

    climb_ast(1);
    parse_loop_EOL(tok);
    if (parse_shellcommand(tok) == -1)
        parse_error("PARSE ERROR : Expected a shell command !");
    return 0;
}
