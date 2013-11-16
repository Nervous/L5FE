#include "exec.h"

extern s_global *g_global;

static void exec_and(s_list *ast)
{
    if (g_global->prev_return == 0)
        exec_pipeline(ast->brothers);

    if (ast->node->son_list->brothers)
    {
        if (ast->node->son_list->brothers->node->type == AND_DOUBLE)
            exec_and(ast->node->son_list->brothers->brothers);
        if (ast->node->son_list->brothers->node->type == PIPE_DOUBLE)
            exec_or(ast->node->son_list->brothers->brothers);
    }
}

static void exec_or(s_list *ast)
{
    if (g_global->prev_return != 0)
        exec_pipeline(ast->brothers);

    if (ast->node->son_list->brothers)
    {
        if (ast->node->son_list->brothers->node->type == AND_DOUBLE)
            exec_and(ast->node->son_list->brothers->brothers);
        if (ast->node->son_list->brothers->node->type == PIPE_DOUBLE)
            exec_or(ast->node->son_list->brothers->brothers);
    }
}

void exec_andor(s_list *ast)
{
    exec_pipeline(ast->node->son_list);

    if (ast->node->son_list->brothers)
    {
        if (ast->node->son_list->brothers->node->type == AND_DOUBLE)
            exec_and(ast->node->son_list->brothers->brothers);
        if (ast->node->son_list->brothers->node->type == PIPE_DOUBLE)
            exec_or(ast->node->son_list->brothers->brothers);
    }
}
