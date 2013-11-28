#include "fn_match.h"

s_queue *init_queue(void)
{
    s_queue *queue = NULL;

    if (!(queue = malloc(sizeof (s_queue))))
        return NULL;

    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

int add_queue(s_queue *queue, int boolean)
{
    s_node *node = NULL;
    if (!(node = malloc(sizeof (s_node))))
        return 4;

    node->is_star = boolean;
    node->next = NULL;
    for (int i = 0; i < 128; i++)
        node->array_char[i] = 0;

    if (queue->head == NULL)
    {
        queue->tail = node;
        queue->head = node;
        return 0;
    }
    queue->tail->next = node;
    queue->tail = node;
    return 0;
}

void free_queue_match(s_queue *queue)
{
    s_node *node = NULL;
    node = queue->head;
    s_node *save = NULL;
    while (node != NULL)
    {
        save = node;
        node = node->next;
        free(save);
    }
}
