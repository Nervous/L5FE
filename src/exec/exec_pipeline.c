#include "exec.h"

void exec_pipeline(s_list *ast)
{
    if (ast->node->type == BANG)
        ret = -(exec_command(ast->brothers) + 1);
    else
        exec_command(ast->brothers);

    //NEED TO HANDLE PIPED COMMANDS
}
