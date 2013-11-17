#include "exec.h"

extern s_global *g_global;

int exec_andor(s_list *ast)
{
    int ret = 0;

    ret = exec_pipeline(ast->node->son_list);

    while (ast->brothers)
    {
        if (ast->brothers->node->type == AND_DOUBLE)
            if (ret == 1)
                ret = exec_pipeline(ast->brothers->brothers->node->son_list);
        if (ast->brothers->node->type == PIPE_DOUBLE)
            if (ret == 0)
                ret = exec_pipeline(ast->brothers->brothers->node->son_list);

        ast = ast->brothers->brothers;
    }

    return ret;
}
