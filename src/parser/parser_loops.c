#include "parser.h"

extern s_global *g_global;

/**
** @brief Eat tokens until get_token doesn't give a EOL anymore
*/
void parse_loop_EOL(s_token **tok)
{
    while ((*tok)->type == EOL)
    {
        *tok = eat_token(*tok);
        *tok = get_token(EOL);
    }
}

/**
** @brief Eat tokens until get_token doesn't give a WORD anymore
*/

void parse_loop_WORD(s_token **tok)
{
    while ((*tok)->type == WORD)
    {
        *tok = eat_token(*tok);
        *tok = get_token(WORD);
        climb_ast(1);
    }
}
