#include "exec.h"

int exec_pipeline(s_list *ast)
{
    int ret = 0;

    if (ast->node->type == NEG)
        ret = -(exec_command(ast->brothers) + 1);
    else
        ret = exec_command(ast->node->son_list);

    return ret;
    //NEED TO HANDLE PIPED COMMANDS
}
