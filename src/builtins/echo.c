#include <unistd.h>
#include <stdio.h>
#include "builtins.h"
#include "../exec/exec.h"

static int expanded_echo(s_list *ast)
{
    /** TODO */
    if (!ast)
        return -1;
//    printf("%s\n", ast->node->str);
    return 0;
}

static int print_array(s_list *ast, int option_n)
{
    if (!ast)
        return -1;
    while (ast)
    {
        if (strcmp(ast->node->str, "$") == 0)
            expand_var(ast);
        if (ast->brothers)
        {
            my_puts(ast->node->str);
            my_puts(" ");
        }
        else
            my_puts(ast->node->str);
        ast = ast->brothers;
    }

    if (!option_n) /** TODO: Doesn't work with our shell (save string? wtf)*/
        my_puts("\n");
    return 0;
}

int my_echo(s_list *ast)
{
    if (!ast)
        return -1;
    int ret = 0;
    if (strcmp(ast->node->str, "-n") == 0)
        ret = print_array(ast->brothers, 1);
    else if (strcmp(ast->node->str, "-E") == 0)
        ret = print_array(ast->brothers, 0);
    else if (strcmp(ast->node->str, "-e") == 0)
        ret = expanded_echo(ast->brothers);
    else
        ret = print_array(ast, 0);
    return ret;
}

