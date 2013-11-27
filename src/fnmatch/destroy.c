#include "fifo.h"

void destroy(s_fifo *fifo)
{
    s_list22 *save;
    s_list22 *parse = fifo->head;

    while (parse != NULL)
    {
        save = parse;
        parse = parse->next;
        free(save);
    }

    free(fifo);
}
