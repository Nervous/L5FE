#include "builtins.h"

int my_export(s_list *ast)
{
    char *name = NULL;
    char *value = NULL;
    if (!ast)
        return -1;
    name = ast->node->str;
    if (ast->brothers->brothers)
        value = ast->brothers->brothers->node->str;
    setenv(name, value, 1);
    return 0;
}
