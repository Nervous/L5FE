#include "fifo.h"

static int only_stars(s_list22 *list2)
{
    while (list2 != NULL && list2->star == 1)
        list2 = list2->next;

    if (list2 == NULL)
        return 0;
    else
        return 1;
}

static int star_loop(s_list22 *list2, const char *str, int index)
{

    if (!compare(list2->next, str, index))
        return 0;
    else
    {
        if (str[index] == '\0')
            return 1;
        return star_loop(list2, str, index + 1);
    }
}

int compare(s_list22 *list2, const char *str, int i)
{
    while (list2 != NULL && str[i] != '\0')
    {
        if (list2->star)
            return star_loop(list2, str, i);

        int index = str[i];
        if (list2->array[index] == 0)
            return 1;
        list2 = list2->next;
        i++;
    }

    if (list2 != NULL)
        return only_stars(list2);
    else if (str[i] != '\0')
        return 1;
    else
        return 0;
}
