#include "variable.h"
#include <stdlib.h>
#include <string.h>

s_var *search_var(s_var *list, char *key)
{
    s_var *tmp = list;
    while (tmp != NULL)
    {
        if (!strcmp(tmp->key, key))
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

s_var *add_var(s_var *list, char *key, char *value)
{
    s_var *tmp = NULL;
    if ((tmp = search_var(list, key)) == NULL)
    {
        s_var *head = malloc(sizeof (s_var));
        head->key = key;
        head->value = value;
        head->next = list;
    }
    else
    {
        free(tmp->value);
        tmp->value = value;
    }
}

void free_var(s_var *list)
{
    s_var *tmp = list;
    while (tmp != NULL)
    {
        free(tmp->key);
        free(tmp->value);
        s_var *last = tmp;
        tmp = tmp->next;
        free(last);
    }
}
