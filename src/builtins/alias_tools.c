#include "aliases.h"
#include <stdlib.h>
#include <unistd.h>
#include "../struct.h"
#include <string.h>

extern s_global *g_global;

char *alias_get_value(char *name)
{
    if (!g_global->alias_list)
        return NULL;
    s_alias *tmp = g_global->alias_list;
    while (tmp != NULL)
    {
        if (!strcmp(tmp->name, name))
            return tmp->value;
        tmp = tmp->next;
    }
    return NULL;
}

int alias_set_value(char *name, char *value)
{
    s_alias *tmp = g_global->alias_list;
    while (tmp != NULL)
    {
        if (!strcmp(tmp->name, name))
        {
            free(tmp->value);
            tmp->value = malloc(sizeof (char) * strlen(value) + 1);
            tmp->value = strcpy(tmp->value, value);
            return 0;
        }
        tmp = tmp->next;
    }
    return -1;
}
void add_alias(char *name, char *value)
{
    if ((alias_get_value(name)) == NULL)
    {
        s_alias *head = malloc(sizeof (s_alias));
        head->name = name;
        head->value = value;
        head->next = g_global->alias_list;
        g_global->alias_list = head;
    }
    else
        alias_set_value(name, value);
}

void unalias(char *name)
{
    s_alias *tmp = g_global->alias_list;
    s_alias *previous = NULL;
    while (tmp != NULL)
    {
        if (!strcmp(tmp->name, name))
        {
            if (previous)
                previous->next = tmp->next;
            free(tmp->value);
            free(tmp->name);
            free(tmp);
        }
        previous = tmp;
        tmp = tmp->next;
    }
}

void free_alias_list(void)
{
    s_alias *tmp = g_global->alias_list;
    while (tmp != NULL)
    {
        free(tmp->name);
        free(tmp->value);
        s_alias *previous = tmp;
        tmp = tmp->next;
        free(previous);
    }
}
