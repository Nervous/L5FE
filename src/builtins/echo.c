#include <unistd.h>
#include <stdio.h>
#include "builtins.h"
#include "../exec/exec.h"
#include "../expansion/expansion.h"
#include "../fnmatch/my_fnmatch.h"

static void fill_buf(s_list *ast, int j, char *buf, int *trail)
{
    for (int i = 0; ast->node->str[i]; i++)
    {
        if (ast->node->str[i] == '\\' && ast->node->str[i + 1])
        {
            i++;
            if (ast->node->str[i] == 'b' && ast->node->str[i + 1])
            {
                i++;
                if (j > 0)
                    buf[j - 1] = ast->node->str[i];
            }
            else if (ast->node->str[i] == 'n' && ast->node->str[i + 1])
                buf[j++] = '\n';
            else if (ast->node->str[i] == 'c')
            {
                *trail = 1;
                break;
            }
            else if (ast->node->str[i] == '\\')
                buf[j++] = '\\';
        }
        else if (ast->node->str[i] != '\'')
            buf[j++] = ast->node->str[i];
    }
    buf[j] = '\0';
    my_puts(buf);
}

static int expanded_echo(s_list *ast)
{
    if (!ast)
        return -1;
    char *buf = malloc(sizeof (char) * strlen(ast->node->str) + 1);
    int j = 0;
    int trail = 0;
    fill_buf(ast, j, buf, &trail);
    free(buf);
    if (trail == 0)
        my_puts("\n");
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
            tilde_handler(&(ast->node->str));
            my_puts(ast->node->str);
        if (ast->brothers)
            my_puts(" ");
        ast = ast->brothers;
    }
    if (!option_n)
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
