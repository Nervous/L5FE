#include "exec.h"

int exec_list(s_list *ast)
{
    int ret = 0;
    ret = exec_andor(ast);

    while (ast->brothers)
    {
        if (ast->brothers->node->type == BIT_AND)
            ret = exec_andor(ast->brothers->brothers);
        /* HANDLE '&' EXECUTION */

        if (ast->brothers->node->type == SEMICOLON)
            ret = exec_andor(ast->brothers->brothers);

        ast = ast->brothers;
    }

    return ret;
}
