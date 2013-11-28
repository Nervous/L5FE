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
