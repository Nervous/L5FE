#include "my_fnmatch.h"

int my_fnmatch(const char *pattern, const char *string)
{
  s_fifo *fifo = init_fifo();
  parse(fifo, pattern);
  int result = compare(fifo->head, string, 0);
  destroy(fifo);
  return result;
}
