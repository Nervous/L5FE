#include "eval.h"

int evalexpr(char *str)
{
    s_queue *inf = q_init();
    s_queue *pos = NULL;
    int value = 0;
    int error = parse_eval(str, inf);
    if (error != 0)
    {
        free_queue(inf);
        return error;
    }

    pos = get_postfix(inf);
    error = eval(pos, &value);
    return value;
}
