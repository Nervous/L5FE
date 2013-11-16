#include "exec.h"

void exec_input(s_list *ast)
{
    if (ast)
        exec_list(ast->node->son_list);
}
