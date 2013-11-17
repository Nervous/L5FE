#include "ast.h"
#include <string.h>
#include <stdlib.h>

extern s_global *g_global;
static void release_all_brothers(s_list *ast)
{
    if (!ast)
        return;
    if (ast->brothers)
        release_all_brothers(ast->brothers);
    remove_node(ast);
}
void release_ast(s_list *ast)
{
    if (!ast)
        return;
    release_ast(ast->node->son_list);
    release_all_brothers(ast);
}
static void release_node(s_list *node)
{
    if (!node)
        return;
    if (node->node->str && node->abstract == 0)
        free(node->node->str);
    if (node->node->son_list)
        remove_node(node->node->son_list);
    free(node);
}

void remove_node(s_list *node)
{
    if (!node)
        return;
    if (!node->father)
        release_node(node);
    else
    {
        s_list *current_node_tmp = node->father;
        s_list *tmp = node->father;
        s_list *tmp_son = node->father;
        s_list *previous = NULL;
        s_list *first_son = node->father->node->son_list;
        while (tmp_son->node->son_list
               && tmp_son->node->son_list->id != node->id)
        {
            previous = tmp_son->node->son_list;
            tmp_son->node->son_list = tmp_son->node->son_list->brothers;
        }
        s_list *next = NULL;
        if (tmp->node->son_list->brothers)
        while (tmp)
        {
            if (tmp->node->son_list->id == node->id)
            {
                if (previous)
                {
                    tmp->node->son_list = first_son;
                    previous->brothers = next;
                }
                else
                    tmp->node->son_list = next;
                break;
            }
            tmp->node->son_list = tmp->node->son_list->brothers;
            if (tmp->node->son_list)
                next = tmp->node->son_list->brothers;
        }
        release_node(node);
        g_global->current_node = current_node_tmp;
        g_global->current_node->node = copy_token(current_node_tmp->node);
    }
    g_global = g_global;
}
