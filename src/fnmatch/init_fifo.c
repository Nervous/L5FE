#include "fifo.h"

s_fifo *init_fifo(void)
{
  s_list22 *head = NULL;
  s_list22 *tail = NULL;
  s_fifo *fifo = NULL;

  fifo = malloc(sizeof (s_fifo));
  if (fifo == NULL)
    return NULL;

  fifo->head = head;
  fifo->tail = tail;

  return fifo;
}
