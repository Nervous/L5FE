#include "fifo.h"

void destroy(s_fifo *fifo)
{
  s_list *save;
  s_list *parse = fifo->head;

  while (parse != NULL)
    {
      save = parse;
      parse = parse->next;
      free(save);
    }

  free(fifo);
}
