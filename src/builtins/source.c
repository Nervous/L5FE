#include "builtins.h"
#include <stdio.h>
#include <stdbool.h>
#include "../get_options.h"
#include "../exec/exec.h"

extern s_global *g_global;
int my_source(s_list *ast)
{
    if (!ast)
        return 2;
    int ret = 0;
    char *readline_saved = g_global->readline;
    release_ast(g_global->current_node);
    g_global->pos = 0;
    get_file(ast->node->str, true);
    ret = exec_input(get_root(g_global->current_node));
    release_ast(g_global->current_node);
    g_global->current_node = NULL;
    g_global->pos = 0;
    g_global->readline = readline_saved;
    return ret;
}

