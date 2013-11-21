#include "std.h"

s_stack *s_init(void)
{
    s_stack *s = NULL;
    if ((s = malloc (sizeof (s_stack))) == NULL)
        return NULL;

    s->head = NULL;
    return s;
}

s_stack *stack_add(s_stack *s, s_node *n)
{
    if (s->head == NULL)
    {
        s->head = n;
        n->next = NULL;
        return s;
    }

    n->next = s->head;
    s->head = n;

    return s;
}

s_node *stack_pop(s_stack *s)
{
    s_node *save = NULL;

    assert(s != NULL);

    if (s->head == NULL)
        return NULL;

    save = s->head;
    s->head = s->head->next;

    return save;
}

s_node *stack_top(s_stack *s)
{
    if (s == NULL)
        return NULL;

    return s->head;
}

int stack_isempty(s_stack *s)
{
    if (s == NULL)
        return 1;

    if (s->head == NULL)
        return 1;

    return 0;
}

int stack_size(s_stack *s)
{
    int i = 0;
    s_node *act = NULL;

    assert(s != NULL);
    act = s->head;

    while (act != NULL)
    {
        act = act->next;
        ++i;
    }

    return i;
}

void free_stack(s_stack *s)
{
    s_node *act = NULL;
    s_node *save = NULL;
    if (s != NULL)
    {
        act = s->head;
        while (act != NULL)
        {
            save = act;
            act = act->next;
            free(save);
        }

        free(s);
    }
}
