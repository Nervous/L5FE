#include "ast.h"
#include <string.h>
#include <stdlib.h>
extern s_global *g_global;

static void release_node(s_list *node)
{
    if (!node)
        return;
    if (node->son_list)
        release_node(node->son_list);
    if (node->node->str)
        free(node->node->str);
    free(node->node);
    free(node);
}

static void release_node2(s_list *node)
{
    if (!node)
        return;
    if (node->node->str)
        free(node->node->str);
    free(node->node);
    free(node);
}

void release_ast(s_list *ast)
{
    if (!ast)
        return;
    release_ast(ast->son_list);
    release_ast(ast->brothers);
    release_node2(ast);
    g_global->current_node = NULL;
}

static void remove_node_aux(s_list *tmp, s_list *previous,
                            s_list *first_son, s_list *node)
{
  s_list *next = NULL;
  if (tmp->son_list->brothers)
    next = tmp->son_list->brothers;
  while (tmp)
  {
    if (tmp->son_list->id == node->id)
    {
      if (previous)
      {
        tmp->son_list = first_son;
        previous->brothers = next;
      }
      else
        tmp->son_list = next;
      break;
    }
    tmp->son_list = tmp->son_list->brothers;
    if (tmp->son_list)
        next = tmp->son_list->brothers;
  }
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
        s_list *first_son = node->father->son_list;
        while (tmp_son->son_list
               && tmp_son->son_list->id != node->id)
        {
            previous = tmp_son->son_list;
            tmp_son->son_list = tmp_son->son_list->brothers;
        }
        remove_node_aux(tmp, previous, first_son, node);
        release_node(node);
        g_global->current_node = current_node_tmp;
    }
    g_global = g_global;
}
