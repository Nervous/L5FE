#include "builtins.h"
#include "unistd.h"
#include "../ast/ast.h"
#include <stdlib.h>
#include "../expansion/expansion.h"
#include "../fnmatch/my_fnmatch.h"

extern s_global *g_global;
int my_cd(s_list *ast)
{
    if (!ast)
    {
        chdir(getenv("HOME"));
        return 0;
    }
    else if (strcmp(ast->node->str, "-") == 0)
    {
        char *tmp_dir = malloc(sizeof (char) * 128);
        tmp_dir = strcpy(tmp_dir, g_global->current_dir);
        chdir(g_global->previous_dir);
        g_global->current_dir = strcpy(g_global->current_dir,
                                       g_global->previous_dir);
        g_global->previous_dir = strcpy(g_global->previous_dir,
                                        tmp_dir);
        free(tmp_dir);
        return 0;
    }
    tilde_handler(&(ast->node->str));
    if (chdir(ast->node->str) != 0)
    {
        my_puts(ast->node->str);
        my_puts(": No such file or directory.\n");
        return -1;
    }
    else
    {
        g_global->previous_dir = strcpy(g_global->previous_dir,
                                        g_global->current_dir);
        g_global->current_dir = getcwd(g_global->current_dir, 128);
    }
    return 0;
}
