#include "builtins.h"
#include <stdio.h>
#include <stdbool.h>
#include "../get_options.h"
#include "../exec/exec.h"

extern s_global *g_global;
int my_source(s_list *ast)
{
    int ret = 0;
    release_ast(g_global->current_node);
    get_file(ast->node->str, true);
    ret = exec_input(get_root(g_global->current_node));
    release_ast(g_global->current_node);
    g_global->current_node = NULL;
    g_global->pos = 0;
    return ret;
}

