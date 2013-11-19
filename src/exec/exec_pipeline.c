#include "exec.h"

int exec_pipeline(s_list *ast)
{
    int ret = 0;
    if (ast->brothers->node->type != BIT_PIPE)
    {
        if (ast->node->type == NEG)
            ret = -(exec_command(ast->brothers) + 1);
        else
            ret = exec_command(ast->son_list);
    }
    else
        ret = exec_pipe(ast);
    return ret;
}
