#include "builtins.h"
#include <unistd.h>

extern char **environ;
extern s_global *g_global;
static int display_env(void)
{
    for (int i = 0; environ[i]; i++)
    {
        my_puts(environ[i]);
        my_puts("\n");
    }
    return 0;
}

static int export_count(s_list *ast)
{
    int count1 = 0;
    for (int i = 0; ast->node->str[i]; i++)
    {
        if (ast->node->str[i] == '=')
            break;
        else
            count1++;
    }
    return count1;
}

static void display_export(char *name, char *value)
{
    my_puts(name);
    my_puts("=");
    my_puts(value);
    my_puts("\n");
}
static int my_export2(s_list *ast, int display)
{
    if (!ast)
        return 0;
    char *name = NULL;
    char *value = NULL;
    int count1 = export_count(ast);
    int count2 = strlen(ast->node->str) - 1 - count1;
    name = malloc(sizeof (char) * (count1 + 1));
    value = malloc(sizeof (char) * (count2 + 1));
    int j = 0;
    int k = 0;
    for (int i = 0; ast->node->str[i]; i++)
    {
        if (i < count1)
            name[j++] = ast->node->str[i];
        else if (i > count1)
            value[k++] = ast->node->str[i];
    }
    name[j] = '\0';
    value[k] = '\0';
    setenv(name, value, 1);
    if (display)
        display_export(name, value);
    free(name);
    free(value);
    return 0;
}

static int check_equal(s_list *ast)
{
    for (int i = 0; ast->node->str[i]; i++)
    {
        if (ast->node->str[i] == '=')
            return 0;
    }
    return 1;
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
    s_var *var = NULL;
    name = ast->node->str;
    if (check_equal(ast) == 0)
        return my_export2(ast, display);
    else if ((var = search_var(g_global->var, name)) != NULL)
        value = var->value;
    if (value)
        setenv(name, value, 1);
    else
        setenv(name, "\'\'", 1);
    if (display)
        display_export(name, value);
    return 0;
}
