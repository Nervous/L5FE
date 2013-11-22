#include "exec.h"
#include "../builtins/builtins.h"
#include <string.h>
#include "exec.h"
#include <stdio.h>
extern s_global *g_global;

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
    else if (strcmp(ast->node->str, "exit") == 0)
    {
        if (ast->brothers)
            exit_builtin(atoi(ast->brothers->node->str));
        else
            exit_builtin(g_global->ret);
    }
    else if (strcmp(ast->node->str, "break") == 0)
    {
        if (ast->brothers)
            g_global->break_nb = atoi(ast->brothers->node->str);
        else
            g_global->break_nb = 1;
        return 0;
    }
    else
        return -1;
    return ret;
}
