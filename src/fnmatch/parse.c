#include "fifo.h"

static void update_array(s_fifo *fifo, char c)
{
  int index = c;
  fifo->tail->array[index] = 1;
}

static void update_array_range(s_fifo *fifo, int start, int end)
{
  for (int s = start; s < end; s++)
    fifo->tail->array[s] = 1;
}

static void negate_array(s_fifo *fifo)
{
  for (int i = 0; i < 128; i++)
    fifo->tail->array[i] = !fifo->tail->array[i];
}

static void range_loop(s_fifo *fifo, const char *str, int *i)
{
  int negate = 0;
  int is_first = 1;
  *i = *i + 1;

  while (str[*i] != '\0' && (str[*i] != ']' || is_first))
    {
      is_first = 0;
      if (str[*i] == '!' && negate == 0 && str[*i - 1] == '[')
	{
	  negate = 1;
	  is_first = 1;
	}
      else if (str[*i] == '-' && str[*i - 1] != '[' && str[*i + 1] != ']' &&
	       str[*i + 1] != '\0')
	{
	  int s = str[*i - 1];
	  int e = str[*i + 1];
	  update_array_range(fifo, s, e);
	}
      else
	  update_array(fifo, str[*i]);
      *i = *i + 1;
    }

  if (negate)
    negate_array(fifo);
}

static bool is_range(const char *str, int i)
{
  int index = i;
  int next;

  while (str[i] != '\0' && str[i] != ']')
    i++;

  next = i;

  for (; str[i] != '\0'; i++)
    if (str[i] == ']')
      next = i;

  if (str[next] == ']')
    return !(str[index + 1] == '!' && index + 2 == next) && index + 1 != next;
  return false;
}

void parse(s_fifo *fifo, const char *str)
{
  for (int i = 0; str[i] != '\0'; i++)
    {
      if (str[i] == '\\')
	{
	  push(fifo, false);
	  update_array(fifo, str[++i]);
	}
      else if (str[i] == '*')
	push(fifo, true);
      else if (str[i] == '?')
	{
	  push(fifo, false);
	  update_array_range(fifo, 0, 128);
	}
      else if (str[i] == '[' && is_range(str, i))
	{
	  push(fifo, false);
	  range_loop(fifo, str, &i);
	}
      else
	{
	  push(fifo, false);
	  update_array(fifo, str[i]);
	}
    }
}
