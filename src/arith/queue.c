#include "std.h"

s_queue *q_init(void)
{
    s_queue *q = NULL;
    q = malloc(sizeof (s_queue));
    if (q == NULL)
        return NULL;

    q->head = NULL;
    q->tail = NULL;

    return q;
}

s_queue *queue_add(s_queue *q, s_node *n)
{
    if (q->tail != NULL)
        q->tail->next = n;
    q->tail = n;

    if (q->head == NULL)
        q->head = n;

    return q;
}

void free_queue(s_queue *q)
{
    s_node *act = NULL;
    s_node *save = NULL;
    act = q->head;

    while (act != NULL)
    {
        save = act;
        act = act->next;
        free(save);
    }
    free(q);
}
