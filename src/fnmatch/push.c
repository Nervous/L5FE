#include "fifo.h"

void push(s_fifo *fifo, bool star)
{
  assert(fifo != NULL);

  s_list22 *new = NULL;

  new = malloc(sizeof (s_list22));
  if (new == NULL)
    return;

  for (int i = 0; i < 128; i++)
    new->array[i] = 0;
  new->star = star;
  new->next = NULL;

  if (fifo->head == NULL)
    {
      fifo->tail = new;
      fifo->head = new;
    }
  else if (fifo->tail != NULL)
    {
      fifo->tail->next = new;
      fifo->tail = new;
    }
}
