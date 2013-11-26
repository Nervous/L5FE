#include "builtins.h"
#include "../struct.h"
#include <string.h>

extern s_global *g_global;

int modify_opt(char *name, int activate)
{
    int found = 0;
    for (int i = 0; i < 8; i++)
    {
        if (strcmp(name, g_global->options[i]->name) == 0)
        {
            found = 1;
            g_global->options[i]->activated = activate;
        }
    }
    if (!found)
    {
        my_puts("42sh: shopt: ");
        my_puts(name);
        my_puts(": invalid shell option name\n");
        return 1;
    }
    else
        return 0;
}

static int check_activated(s_list *ast)
{
    int found = 0;
    while (ast)
    {
        for (int i = 0; i < 8; i++)
        {
            if (strcmp(ast->node->str, g_global->options[i]->name) == 0)
            {
                if (!g_global->options[i]->activated)
                    return 1;
            }
        }
        if (!found)
        {
            my_puts("42sh: shopt: ");
            my_puts(ast->node->str);
            my_puts(": invalid shell option name\n");
            return 1;
        }
        ast = ast->brothers;
    }
    return 0;
}

static void print_options(void)
{
    int spaces = 16;
    for (int i = 0; i < 8; i++)
    {
        my_puts(g_global->options[i]->name);
        spaces = 16 - strlen(g_global->options[i]->name);
        while (spaces > 0)
        {
            my_puts(" ");
            spaces--;
        }
        if (g_global->options[i]->activated)
            my_puts("on");
        else
            my_puts("off");
        my_puts("\n");
    }
}

static int mod_opt(s_list *ast, int activation)
{
    if (!ast)
    {
        for (int i = 0; i < 8; i++)
            g_global->options[i]->activated = activation;
        print_options();
        return 0;
    }
    else
    {
        int val = 0;
        while (ast)
        {
            val = modify_opt(ast->node->str, activation);
            if (val)
                return 1;
            ast = ast->brothers;
        }
    }
    return 0;
}

int my_shopt(s_list *ast)
{
    int ret = 0;
    if (!ast)
        print_options();
    else if (strcmp(ast->node->str, "-u") == 0)
        ret = mod_opt(ast->brothers, 0);
    else if (strcmp(ast->node->str, "-s") == 0)
        ret = mod_opt(ast->brothers, 1);
    else if (strcmp(ast->node->str, "-q") == 0)
        ret = check_activated(ast->brothers);
    return ret;
}
