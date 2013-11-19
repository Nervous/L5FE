#include "exec.h"

int exec_list(s_list *ast)
{
    if (!ast)
        return -1;
    int ret = 0;
    ret = exec_andor(ast->son_list);
    while (ast->brothers)
    {
        if (ast->brothers->node->type == BIT_AND)
            ret = exec_andor(ast->brothers->brothers->son_list);
        /* HANDLE '&' EXECUTION */

        if (ast->brothers->node->type == SEMICOLON)
        {
            if (ast->brothers->brothers)
                ret = exec_andor(ast->brothers->brothers->son_list);
            else
                return ret;
        }
        if (!ast->brothers || !ast->brothers->brothers)
            break;
        ast = ast->brothers->brothers;
    }

    return ret;
}
