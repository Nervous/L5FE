#include <string.h>
#include <stdlib.h>
#include "../struct.h"
#include "../ast/ast.h"
#include "function.h"

extern s_global *g_global;

static char *my_strcpy(char *str)
{
    char *new_str = malloc(sizeof (char) * (strlen(str) + 1));
    int i = 0;
    for (i = 0; str[i]; i++)
    {
        new_str[i] = str[i];
    }
    new_str[i] = '\0';
    return new_str;
}

/**
** @brief this function will try to retrieve the function with the name (name)
** in the registered functions
*/
s_function *search_function(char *name)
{
    s_function *tmp = g_global->func;
    while (tmp != NULL)
    {
        if (strcmp(tmp->name, name) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

/**
** @brief This function will copy the whole structure of an ast
*/
s_list *cpy_list(s_list *src, s_list *father)
{
    if (src == NULL)
        return NULL;

    s_list *list = malloc(sizeof (s_list));
    list->id = src->id;
    list->linked = src->linked;
    list->abstract = src->abstract;

    list->node = malloc(sizeof (s_token));
    list->node->type = src->node->type;
    list->node->str = my_strcpy(src->node->str);
    list->node->pos = src->node->pos;
    list->son_list = cpy_list(src->son_list, list);

    list->father = father;
    list->brothers = cpy_list(src->brothers, list);

    return list;
}

/**
** @brief This function will add a new (function) struct to the memory
*/
void add_function(char *name, s_list *ast)
{
    s_function *tmp = NULL;
    if ((tmp = search_function(name)) == NULL)
    {
        s_function *new_func = malloc(sizeof (s_function));
        new_func->name = my_strcpy(name);
        new_func->node = cpy_list(ast, NULL);
        new_func->next = g_global->func;
        g_global->func = new_func;
    }
    else
    {
        //todo FREE AST
        tmp->node = cpy_list(ast, NULL);
    }
}

void free_function(void)
{
    s_function *tmp = g_global->func;
    s_function *last = tmp;

    while (tmp != NULL)
    {
        last = tmp;
        tmp = tmp->next;
        release_ast(get_root(last->node));
        free(last->name);
        free(last);
    }
}
