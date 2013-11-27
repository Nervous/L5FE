#include "exec.h"

extern s_global *g_global;
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

        if (ast->brothers->node->type == SEMICOLON)
        {
            if (ast->brothers->brothers)
            {
                g_global->ret = ret;
                ret = exec_andor(ast->brothers->brothers->son_list);
            }
            else
                return ret;
        }
        if (!ast->brothers || !ast->brothers->brothers)
            break;
        ast = ast->brothers->brothers;
    }
    return ret;
}
