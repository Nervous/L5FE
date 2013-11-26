#ifndef FIFO_H
# define FIFO_H

# include <stdlib.h>
# include <assert.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct list2 s_list22;
struct list2
{
  char array[128];
  bool star;
s_list22 *next;
};

typedef struct fifo
{
  s_list22 *head;
  s_list22 *tail;
} s_fifo;

s_fifo *init_fifo(void);
void push(s_fifo *fifo, bool star);
void destroy(s_fifo *fifo);
int compare(s_list22 *list2, const char *str, int i);
void parse(s_fifo *fifo, const char *str);

#endif /* !FIFO_H */
