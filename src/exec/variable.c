#include "../struct.h"
#include "variable.h"
#include <stdlib.h>
#include <string.h>

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
        return head;
    }
    else
    {
        free(tmp->value);
        free(key);
        tmp->value = value;
        return list;
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

int exec_var(char *str)
{
    char *key = NULL;
    char *value = NULL;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '=')
        {
            str[i] = '\0';
            key = my_strcpy(str);
            value = my_strcpy(&str[i + 1]);
        }
    }
    if (key == NULL)
        return -1;
    g_global->var = add_var(g_global->var, key, value);
    return 0;
}
