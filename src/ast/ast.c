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

s_list *get_root(s_list *current_node)
{
    if (!current_node)
        return NULL;
    s_list *tmp = current_node;
    while (tmp->father)
        tmp = tmp->father;
    return tmp;
}
/**
** Add a brother to the last son of
** the current node
*/
static void node_add_son(s_list *node)
{
    if (!g_global->current_node->node->son_list)
        g_global->current_node->node->son_list = node;
    else
    {
        s_list *son_list = g_global->current_node->node->son_list;
        while (son_list)
        {
            if (son_list->brothers)
                son_list = son_list->brothers;
            else
            {
                son_list->brothers = node;
                break;
            }
        }
    }
    g_global->current_node = node;
}

static s_token *copy_token(s_token *token)
{
    if (!token)
        return NULL;
    s_token *new_node = NULL;
    if (!(new_node = malloc(sizeof (s_token))))
        return NULL;
    new_node->type = token->type;
    if (strcmp(token->str, ";") == 0)
    {
        if (!(new_node->str = malloc(sizeof (char) * 3)))
            return NULL;
        strcpy(new_node->str, "\";\"");
    }
    else if (strcmp(token->str, "(") == 0)
    {
        if (!(new_node->str = malloc(sizeof (char) * 3)))
            return NULL;
        strcpy(new_node->str, "\"(\"");
    }
    else if (strcmp(token->str, ")") == 0)
    {
        if (!(new_node->str = malloc(sizeof (char) * 3)))
            return NULL;
        strcpy(new_node->str, "\")\"");
    }
    else if (strcmp(token->str, "|") == 0)
    {
        if (!(new_node->str = malloc(sizeof (char) * 3)))
            return NULL;
        strcpy(new_node->str, "\"|\"");
    }
    else if (strcmp(token->str, "||") == 0)
    {
        if (!(new_node->str = malloc(sizeof (char) * 4)))
            return NULL;
        strcpy(new_node->str, "\"||\"");
    }
    else if (strcmp(token->str, "&") == 0)
    {
        if (!(new_node->str = malloc(sizeof (char) * 3)))
            return NULL;
        strcpy(new_node->str, "\"&\"");
    }
    else if (strcmp(token->str, "&&") == 0)
    {
        if (!(new_node->str = malloc(sizeof (char) * 4)))
            return NULL;
        strcpy(new_node->str, "\"&&\"");
    }
    else
    {
        if (!(new_node->str = malloc(sizeof (char) * strlen(token->str))))
            return NULL;
        strcpy(new_node->str, token->str);
    }
   // new_node->son_list = list_copy(token->son_list);
    new_node->son_list = token->son_list;
    return new_node;
}
s_list *list_copy(s_list *list)
{
    if (!list)
        return NULL;
    s_list *new_list = NULL;
    if (!(new_list = malloc(sizeof (s_list))))
        return NULL;
    new_list->id = list->id;
    new_list->linked = list->linked;
    new_list->abstract = list->abstract;
    new_list->node = copy_token(list->node);
    new_list->father = list_copy(list->father);
    return new_list;
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
    if (!node->father)
        release_node(node);
    else
    {
        s_list *current_node_tmp = node->father;
        s_list *tmp = node->father;
        s_list *previous = NULL;
        s_list *next = NULL;
        while (tmp)
        {
            if (tmp->node->son_list->id == node->id)
            {
                tmp->node->son_list = previous;
                if (tmp->node->son_list)
                    tmp->node->son_list->brothers = next;
                break;
            }
            previous = tmp->node->son_list;
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
/**
** Add a node to the ast, whose father
** will be the current_node global variable
*/
void ast_add_node(s_token *token)
{
    s_list *new_node = NULL;
    if (!(new_node = malloc(sizeof (s_list))))
        return;
    new_node->father = g_global->current_node;
    new_node->brothers = NULL;
    new_node->node = copy_token(token);
    g_global->last_node_id += 1;
    new_node->id = g_global->last_node_id;
    new_node->linked = 0;
    new_node->abstract = 0;
    new_node->node->son_list = NULL;
    if (g_global->current_node)
        node_add_son(new_node);
    g_global->current_node = new_node;
}
void ast_add_step(char *stepName)
{
    s_list *new_node = NULL;
    if (!(new_node = malloc(sizeof (s_list))))
        return;
    new_node->father = g_global->current_node;
    new_node->brothers = NULL;
    s_token *new_token = NULL;
    g_global->last_node_id += 1;
    new_node->id = g_global->last_node_id;
    if (!(new_token = malloc(sizeof (s_token))))
        return;
    new_token->type = ABSTRACT;
    if (!(new_token->str = malloc(sizeof (char) * strlen(stepName) + 1)))
        return;
    strcpy(new_token->str, stepName);
    new_token->son_list = NULL;
    new_node->node = new_token;
    new_node->linked = 0;
    new_node->abstract = 1;
    if (g_global->current_node)
        node_add_son(new_node);
    g_global->current_node = new_node;
}
