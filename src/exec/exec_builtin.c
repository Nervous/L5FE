#include "exec.h"
#include "../builtins/builtins.h"
#include <string.h>
#include "exec.h"
#include <stdio.h>
extern s_global *g_global;

int check_builtin(s_list *ast)
{
    if (!ast)
        return -1;
    if (strcmp(ast->node->str, "echo") == 0)
    {
        my_echo(ast->brothers);
        return 0;
    }
    else if (strcmp(ast->node->str, "source") == 0
             || strcmp(ast->node->str, ".") == 0)
    {
        return 0;
        my_source(ast->brothers);
    }
    else if (strcmp(ast->node->str, "exit") == 0)
    {
        if (ast->brothers)
            exit_builtin(atoi(ast->brothers->node->str));
        else
            exit_builtin(g_global->ret);
        return 0;
    }
    else if (strcmp(ast->node->str, "break") == 0)
    {
        if (ast->brothers)
            g_global->break_nb = atoi(ast->brothers->node->str);
        else
            g_global->break_nb = 1;
        return 0;
    }
    else if (strcmp(ast->node->str, "continue") == 0)
    {
        if (ast->brothers)
            g_global->continue_nb = 1; /** TODO: Multiple continues */
        else
            g_global->continue_nb = 1;
        return 0;
    }
    else if (strcmp(ast->node->str, "cd") == 0)
    {
        my_cd(ast->brothers);
        return 0;
    }
    else if (strcmp(ast->node->str, "alias") == 0)
        my_alias(ast->brothers);
    else if (strcmp(ast->node->str, "unalias") == 0)
        my_unalias(ast->brothers);
    else if (strcmp(ast->node->str, "export") == 0)
        my_export(ast->brothers);
    else if (strcmp(ast->node->str, "shopt") == 0)
        my_shopt(ast->brothers);
    else if (strcmp(ast->node->str, "history") == 0)
        my_history(ast->brothers);
    else
        return -1;
    return 0;
}
