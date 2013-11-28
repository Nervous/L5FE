#include "fn_match.h"

static int check_nodes(s_node *node)
{
    while (node != NULL)
    {
        if (node->is_star == 0)
            return 1;
        node = node->next;
    }
    return 0;
}

static int loop_star(s_node *node, const char *str, int i)
{
    s_node *tmp = node->next;

    while (str[i] != '\0')
    {
        if (match(tmp, &str[i]) == 0)
            return 0;
        i++; // the star match 1 more character.
    }
    return check_nodes(node);
}

int match(s_node *node, const char *str)
{
    int i = 0;

    while (node != NULL && str[i] != '\0')
    {
        int index = str[i];
        if (node->is_star)
        {
            return loop_star(node, str, i);
        }
        else if (node->array_char[index] == 0)
            return 1;
        node = node->next;
        i++;
    }

    if (node != NULL)
        return check_nodes(node);
    else if (str[i] != '\0')
        return 1;
    else
        return 0;
}
