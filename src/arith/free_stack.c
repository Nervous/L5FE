#include "std.h"
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
