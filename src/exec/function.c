#include "function.h"
#include <string.h>
#include <stdlib.h>

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
    }
    return NULL;
}

/**
** @brief This function will copy the whole structure of an ast
*/
s_list *cpy_list(s_list *src)
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
    list->node->son_list = cpy_list(src->node->son_list);

    list->father = NULL;
    list->brothers = cpy_list(src->brothers);
}

/**
** @brief This function will add a new (function) struct to the memory
*/
void add_function(char *name, s_list *ast)
{
    if (search_function(name) == NULL)
    {
        s_function *new_func = malloc(sizeof (s_function));
        new_func->name = name;

    }
    else
    {

    }
}

