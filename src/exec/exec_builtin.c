#include "exec.h"
#include "../builtins/builtins.h"
int check_builtin(s_list *ast)
{
    int ret = 0;
    if (!ast)
        return -1;
    if (strcmp(ast->node->str, "echo") == 0)
        ret = my_echo(ast->brothers);
    else if (strcmp(ast->node->str, "source") == 0
             || strcmp(ast->node->str, ".") == 0)
        ret = my_source(ast->brothers);
    else
        return -1;
    return ret;
}
