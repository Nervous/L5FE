#include "parser.h"

int parse_function(s_token **tok)
{
    if ((*tok)->type != FUNC)
        return -1;
    *tok = eat_token(*tok);
    *tok = get_token(WORD);
    if ((*tok)->type != WORD)
        parse_error("PARSE ERROR : Expected a WORD");
    *tok = eat_token(*tok);
    *tok = get_token(LEFT_PAR);

    if ((*tok)->type != LEFT_PAR)
        parse_error("PARSE ERROR : Expected a '('");
    *tok = eat_token(*tok);
    *tok = get_token(RIGHT_PAR);

    if ((*tok)->type != RIGHT_PAR)
        parse_error("PARSE ERROR : Expected a ')'");
    *tok = eat_token(*tok);
    *tok = get_token(EOL);

    parse_loop_EOL(tok);
    if (parse_shellcommand(tok) == -1)
        parse_error("PARSE ERROR : Expected a shell command !");
    return 0;
}
