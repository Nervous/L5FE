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
    {
        name = malloc(sizeof (char) * strlen(ast->node->str) + 1);
        name = strcpy(name, ast->node->str);
        name[strlen(name)] = '\0';
    }
    else
        return 0;

    if (!ast->brothers)
        return 0;
    s_list *tmp = ast->brothers;
    while (tmp)
    {
        if (value)
        {
            value = realloc(value, sizeof (char) * (strlen(value)
                                  + strlen(tmp->node->str) + 1));
            value = strcat(value, tmp->node->str);
            value[strlen(value)] = '\0';
        }
        else
        {
            value = malloc(sizeof (char) * strlen(tmp->node->str) + 1);
            value = strcpy(value, tmp->node->str);
            value[strlen(value)] = '\0';
        }
        tmp = tmp->brothers;
    }
    if (name && value)
        add_alias(name, value);
    return 0;
}

int my_unalias(s_list *ast)
{
    char *name = NULL;
    if (!(name = malloc(sizeof (char) * strlen(ast->node->str) + 1)))
        return -1;
    if (ast)
        name = strcpy(name, ast->node->str);
    else
        return 0;
    unalias(name);
    return 0;
}
