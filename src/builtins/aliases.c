#include "aliases.h"
#include "builtins.h"
#include "../ast/ast.h"
#include "../struct.h"
#include <string.h>

extern s_global *g_global;
int my_alias(s_list *ast)
{
    char *value = NULL;
    char *name = NULL;
    if (ast)
        name = ast->node->str;
    else
        return 0;

    if (!ast->brothers)
        return 0;
    s_list *tmp = ast->brothers->brothers;
    while (tmp)
    {
        if (value)
            value = strcat(value, tmp->node->str);
        else
            value = tmp->node->str;
        tmp = tmp->brothers;
    }
    if (name && value)
        add_alias(name, value);
    return 0;
}

int my_unalias(s_list *ast)
{
    char *name = NULL;
    if (ast)
        name = ast->node->str;
    else
        return 0;
    unalias(name);
    return 0;
}
