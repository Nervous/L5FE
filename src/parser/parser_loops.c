#include "parser.h"

extern s_global *g_global;
void parse_loop_EOL(s_token **tok)
{
    while ((*tok)->type == EOL)
    {
        *tok = eat_token(*tok);
        *tok = get_token(EOL);
    }
}

void parse_loop_WORD(s_token **tok)
{
    while ((*tok)->type == WORD)
    {
        *tok = eat_token(*tok);
        *tok = get_token(WORD);
        climb_ast(1);
    }
}
