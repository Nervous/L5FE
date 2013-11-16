#include "exec.h"

void exec_pipeline(s_list *ast)
{
    if (ast->node->son_list->node->type == BANG)
        exec_command(ast->node->son_list->brothers, 1);
    else
        exec_command(ast->node->son_list, 0);

    //NEED TO HANDLE PIPED COMMANDS
}
