#include "exec.h"
#include "../builtins/builtins.h"
int check_builtin(s_list *ast)
{
    if (!ast)
        return -1;
    if (strcmp(ast->node->str, "echo") == 0)
    {
        my_echo(ast->brothers);
        return 0;
    }
    else
        return -1;
}
