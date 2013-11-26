#include "my_fnmatch.h"
#include <stdio.h>

int fnmatch(int argc, char **argv)
{
  argc = argc;

  s_fifo *fifo = init_fifo();
  parse(fifo, argv[1]);
  int result = compare(fifo->head, argv[2], 0);
  printf("%d\n", result);
  destroy(fifo);
  return result;
}
