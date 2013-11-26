#include "builtins.h"
#include <unistd.h>

extern char **environ;
static int display_env(void)
{
    for (int i = 0; environ[i]; i++)
    {
        my_puts(environ[i]);
        my_puts("\n");
    }
    return 0;
}
int my_export(s_list *ast)
{
    char *name = NULL;
    char *value = NULL;
    int display = 0;
    if (!ast)
        return display_env();
    if (strcmp(ast->node->str, "-p") == 0)
    {
        ast = ast->brothers;
        display = 1;
        if (!ast)
            return 0;
    }
    name = ast->node->str;
    value = ast->brothers->node->str;
    setenv(name, value, 1);
    if (display)
    {
        my_puts(name);
        my_puts("=");
        my_puts(value);
        my_puts("\n");
    }
    return 0;
}
