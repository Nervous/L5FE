#include "exec.h"

int exec_list(s_list *ast)
{
    int ret = 0;
    ret = exec_andor(ast->node->son_list);

    while (ast->brothers)
    {
        if (ast->brothers->node->type == BIT_AND)
            ret = exec_andor(ast->brothers->brothers->node->son_list);
        /* HANDLE '&' EXECUTION */

        if (ast->brothers->node->type == SEMICOLON)
            ret = exec_andor(ast->brothers->brothers->node->son_list);

        ast = ast->brothers->brothers;
    }

    return ret;
}
