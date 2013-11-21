#include "builtins.h"
#include <stdio.h>

extern s_global *g_global;
int my_source(s_list *ast)
{
    int ret = 0;
/*    s_list *tmp_save = g_global->current_node;
    get_file(ast->node->str, true);
    exec_input(get_root(g_global->current_node));*/
    ast = ast;
    return ret;
}

